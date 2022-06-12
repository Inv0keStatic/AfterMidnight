#include "animation_system.h"
#include "..\ragebot\aim.h"
#include "resolver_functions.h"

void resolver::initialize(player_t* e, adjust_data* record, const float& goal_feet_yaw, const float& pitch)
{
	player = e;
	player_record = record;

	original_goal_feet_yaw = math::normalize_yaw(goal_feet_yaw);
	original_pitch = math::normalize_pitch(pitch);
}

void resolver::reset()
{
	player = nullptr;
	player_record = nullptr;

	original_goal_feet_yaw = 0.0f;
	original_pitch = 0.0f;
}

/* Detect side */
int resolver::detect_side(player_t* player, int side)
{
	/* Vars */
	auto first_visible = util::visible(g_ctx.globals.eye_pos, player->hitbox_position_matrix(HITBOX_HEAD, player_record->matrixes_data.first), player, g_ctx.local());
	auto second_visible = util::visible(g_ctx.globals.eye_pos, player->hitbox_position_matrix(HITBOX_HEAD, player_record->matrixes_data.second), player, g_ctx.local());

	if (first_visible != second_visible)
	{
		return side = second_visible;
		lock_side = m_globals()->m_curtime;
	}
	else
	{
		auto first_position = g_ctx.globals.eye_pos.DistTo(player->hitbox_position_matrix(HITBOX_HEAD, player_record->matrixes_data.first));
		auto second_position = g_ctx.globals.eye_pos.DistTo(player->hitbox_position_matrix(HITBOX_HEAD, player_record->matrixes_data.second));

		if (fabs(first_position - second_position) > 1.0f)
			return side = first_position > second_position;
	}
}

float GetBackwardYaw(player_t* player) { return math::calculate_angle(g_ctx.local()->GetAbsOrigin(), player->GetAbsOrigin()).y; }

int resolver::detect_freestanding(player_t* player)
{
	Vector src3D, dst3D, forward, right, up, src, dst;
	float back_two, right_two, left_two;
	trace_t tr;
	Ray_t ray, ray2, ray3, ray4, ray5;
	CTraceFilter filter;

	math::angle_vectors(Vector(0, GetBackwardYaw(player), 0), &forward, &right, &up);

	filter.pSkip = player;
	src3D = player->get_shoot_position();
	dst3D = src3D + (forward * 380);

	ray.Init(src3D, dst3D);
	m_trace()->TraceRay(ray, MASK_SHOT, &filter, &tr);
	back_two = (tr.endpos - tr.startpos).Length();

	ray2.Init(src3D + right * 35, dst3D + right * 35);
	m_trace()->TraceRay(ray2, MASK_SHOT, &filter, &tr);
	right_two = (tr.endpos - tr.startpos).Length();

	ray3.Init(src3D - right * 35, dst3D - right * 35);
	m_trace()->TraceRay(ray3, MASK_SHOT, &filter, &tr);
	left_two = (tr.endpos - tr.startpos).Length();

	if (left_two > right_two)
		return -1;
	else if (right_two > left_two)
		return 1;
	else
		return 0;
}

/* Calculating targeted players desync */
float resolver::calculate_desync()
{
	if (detect_freestanding(player) == -1 || detect_freestanding(player) == 1)
		return 0;

	/* Vars */
	player_t* ent;
	adjust_data* record;
	player_info_t player_info;
	auto m_flDesyncDelta = 0;
	int m_flSide = 0;

	if (player_record->layers[3].m_flCycle == 0.f && player_record->layers[3].m_flWeight == 0.f)
		m_flDesyncDelta = math::normalize_yaw(CalculatedSide ? player->m_angEyeAngles().y + 60 : player->m_angEyeAngles().y - 60);
	else if (record->m_flHighDelta)
	{
		m_flDesyncDelta = math::normalize_yaw(CalculatedSide ? player->m_angEyeAngles().y + player->get_max_desync_delta() : player->m_angEyeAngles().y - player->get_max_desync_delta());
	}
	else if (record->m_flLowDelta)
	{
		m_flDesyncDelta = math::normalize_yaw(CalculatedSide ? player->m_angEyeAngles().y + player->get_max_desync_delta() / 2 : player->m_angEyeAngles().y - player->get_max_desync_delta() / 2);
	}
	else
	{
		switch (g_ctx.globals.missed_shots[player->EntIndex()] % 4)
		{
		case 0:
			m_flDesyncDelta = math::normalize_yaw(CalculatedSide ? player->m_angEyeAngles().y + player->get_max_desync_delta() : player->m_angEyeAngles().y - player->get_max_desync_delta());
			record->m_flHighDelta = true;
			record->m_flLowDelta = false;
			break;
		case 1:
			m_flDesyncDelta = math::normalize_yaw(CalculatedSide ? player->m_angEyeAngles().y + player->get_max_desync_delta() / 2 : player->m_angEyeAngles().y - player->get_max_desync_delta() / 2);
			record->m_flHighDelta = false;
			record->m_flLowDelta = true;
			break;
		case 2:
			m_flDesyncDelta = math::normalize_yaw(player->m_angEyeAngles().y + 8);
			record->m_flHighDelta = false;
			record->m_flLowDelta = false;
			break;
		case 3:
			m_flDesyncDelta = math::normalize_yaw(player->m_angEyeAngles().y - 8);
			record->m_flHighDelta = false;
			record->m_flLowDelta = false;
			break;
		}
	}

	return m_flDesyncDelta;
}

void resolver::initiate(player_info_t player_info)
{
	scanned_target final_target;

	if (g_cfg.ragebot.antiaim_correction && g_ctx.local()->is_alive() && player->m_iTeamNum() != g_ctx.local()->m_iTeamNum())
	{
		if (g_cfg.ragebot.exploit_antiaim_correction)
		{
			if (final_target.data.hitbox != HITBOX_HEAD)
			{
			if (resolver::calculate_desync() > 0.1)
				player->get_animation_state()->m_flGoalFeetYaw + resolver::calculate_desync();
			else if (resolver::calculate_desync() < -0.1)
				player->get_animation_state()->m_flGoalFeetYaw - resolver::calculate_desync();
			}
		}
		else if (resolver::calculate_desync() > 0.1)
			player->get_animation_state()->m_flGoalFeetYaw + resolver::calculate_desync();
		else if (resolver::calculate_desync() < -0.1)
			player->get_animation_state()->m_flGoalFeetYaw - resolver::calculate_desync();
	}
}

float resolver::resolve_pitch()
{
	if (fabs(original_pitch) > 83.0f)
		return original_pitch = 83.0f;

	return original_pitch;
}