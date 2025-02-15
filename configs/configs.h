#pragma once

#include "..\sdk\interfaces\IInputSystem.hpp"
#include "..\utils\json.hpp"
#include "..\nSkinz\SkinChanger.h"
#include "..\nSkinz\item_definitions.hpp"

#include <limits>
#include <unordered_map>
#include <array>
#include <algorithm>
#include <vector>

struct item_setting
{
	void update()
	{
		itemId = game_data::weapon_names[itemIdIndex].definition_index;
		quality = game_data::quality_names[entity_quality_vector_index].index;

		const std::vector <SkinChanger::PaintKit>* kit_names;
		const game_data::weapon_name* defindex_names;

		if (itemId == GLOVE_T_SIDE)
		{
			kit_names = &SkinChanger::gloveKits;
			defindex_names = game_data::glove_names;
		}
		else
		{
			kit_names = &SkinChanger::skinKits;
			defindex_names = game_data::knife_names;
		}

		paintKit = (*kit_names)[paint_kit_vector_index].id;
		definition_override_index = defindex_names[definition_override_vector_index].definition_index;
		skin_name = (*kit_names)[paint_kit_vector_index].skin_name;
	}

	int itemIdIndex = 0;
	int itemId = 1;
	int entity_quality_vector_index = 0;
	int quality = 0;
	int paint_kit_vector_index = 0;
	int paintKit = 0;
	int definition_override_vector_index = 0;
	int definition_override_index = 0;
	int seed = 0;
	int stat_trak = 0;
	float wear = 0.0f;
	char custom_name[24] = "\0";
	std::string skin_name;
};

item_setting* get_by_definition_index(const int definition_index);

struct Player_list_data
{
	int i = -1;
	std::string name;

	Player_list_data()
	{
		i = -1;
		name.clear();
	}

	Player_list_data(int i, std::string name) //-V818
	{
		this->i = i;
		this->name = name; //-V820
	}
};

class Color;
class C_GroupBox;
class C_Tab;

using json = nlohmann::json;

class C_ConfigManager
{
public:
	class C_ConfigItem 
	{
	public:
		std::string name;
		void *pointer;
		std::string type;

		C_ConfigItem(std::string name, void *pointer, std::string type)  //-V818
		{
			this->name = name; //-V820
			this->pointer = pointer;
			this->type = type; //-V820
		}
	};

	void add_item(void* pointer, const char* name, const std::string& type);
	void setup_item(int*, int, const std::string&);
	void setup_item(bool*, bool, const std::string&);
	void setup_item(float*, float, const std::string&);
	void setup_item(key_bind*, key_bind, const std::string&);
	void setup_item(Color*, Color, const std::string&);
	void setup_item(std::vector< int >*, int, const std::string&);
	void setup_item(std::vector< std::string >*, const std::string&);
	void setup_item(std::string*, const std::string&, const std::string&);

	std::vector <C_ConfigItem*> items;

	C_ConfigManager() 
	{ 
		setup(); 
	};

	void setup();
	void save(std::string config);
	void load(std::string config, bool load_script_items);
	void remove(std::string config);
	std::vector<std::string> files;
	void config_files();
};

extern C_ConfigManager* cfg_manager;

enum
{
	FLAGS_MONEY,
	FLAGS_ARMOR,
	FLAGS_KIT,
	FLAGS_SCOPED,
	FLAGS_FAKEDUCKING,
	FLAGS_VULNERABLE,
	FLAGS_PING,
	FLAGS_C4
};

enum
{
	BODYAIMCOND_DOUBLETAP,
	BODYAIMCOND_SLOWWALKING,
	BODYAIMCOND_LETHAL,
	BODYAIMCOND_AIR

};

enum
{
	HEADIMCOND_ONSHOT,
	HEADIMCOND_AIR
};

enum 
{
	BUY_GRENADES,
	BUY_ARMOR, 
	BUY_TASER,
	BUY_DEFUSER
};

enum
{
	WATERMARK_NAME,
	WATERMARK_SERVER,
	WATERMARK_PING,
	WATERMARK_TIME,
	WATERMARK_FPS
};

enum
{
	WEAPON_ICON,
	WEAPON_TEXT,
	WEAPON_BOX,
	WEAPON_DISTANCE,
	WEAPON_GLOW,
	WEAPON_AMMO
};

enum
{
	GRENADE_ICON,
	GRENADE_TEXT,
	GRENADE_BOX,
	GRENADE_GLOW
};

enum
{
	PLAYER_CHAMS_VISIBLE,
	PLAYER_CHAMS_INVISIBLE
};

enum
{
	ENEMY,
	TEAM,
	LOCAL
};

enum
{
	REMOVALS_SCOPE,
	REMOVALS_ZOOM,
	REMOVALS_SMOKE,
	REMOVALS_FLASH,
	REMOVALS_RECOIL,
	REMOVALS_LANDING_BOB,
	REMOVALS_POSTPROCESSING,
	REMOVALS_FOGS
};

enum
{
	CHEAT,
	FPS,
	PING,
	TICKS,
	TIME
};

enum
{
	INDICATOR_FAKE,
	INDICATOR_DESYNC_SIDE,
	INDICATOR_CHOKE,
	INDICATOR_HITCHANCE,
	INDICATOR_DAMAGE,
	INDICATOR_SAFE_POINTS,
	INDICATOR_BODY_AIM,
	INDICATOR_DT,
	INDICATOR_HS,
	INDICATOR_DUCK

};

enum 
{
	BAIM_AIR,
	BAIM_HIGH_VELOCITY,
	BAIM_LETHAL,
	BAIM_DOUBLE_TAP,
	BAIM_UNRESOLVED,
	BAIM_PREFER
};

enum
{
	AUTOSTOP_BETWEEN_SHOTS,
	AUTOSTOP_LETHAL,
	AUTOSTOP_VISIBLE,
	AUTOSTOP_CENTER,
	AUTOSTOP_FORCE_ACCURACY,
	AUTOSTOP_PREDICTIVE
};

enum 
{
	EVENTLOG_HIT,
	EVENTLOG_ITEM_PURCHASES,
	EVENTLOG_BOMB
};

enum
{
	EVENTLOG_OUTPUT_CONSOLE,
	EVENTLOG_OUTPUT_CHAT
};

enum 
{
	FAKELAG_SLOW_WALK,
	FAKELAG_MOVE,
	FAKELAG_AIR,
	FAKELAG_PEEK
};

enum
{
	ANTIAIM_STAND,
	ANTIAIM_SLOW_WALK,
	ANTIAIM_MOVE,
	ANTIAIM_AIR,
	ANTIAIM_LEGIT
};

extern std::unordered_map <std::string, float[4]> colors;

struct Config 
{
	struct Legitbot_t
	{
		bool enabled;
		bool friendly_fire;
		bool autopistol;
		bool backtrackl;
		bool legit_resolver;
		bool autoscope;
		bool unscope;
		bool sniper_in_zoom_only;

		bool do_if_local_flashed;
		bool do_if_local_in_air;
		bool do_if_enemy_in_smoke;

		int autofire_delay;
		key_bind autofire_key;
		key_bind key;

		struct weapon_t
		{
			int priority;

			bool auto_stop;

			int fov_type;
			float fov;

			int smooth_type;
			float smooth;

			float silent_fov;

			int rcs_type;
			float rcs;
			float custom_rcs_smooth;
			float custom_rcs_fov;

			int awall_dmg;

			float target_switch_delay;
			int autofire_hitchance;
			float backtrack_ticks;
		} weapon[8];
	} legitbot;

	struct Ragebot_t
	{
		bool enable;
		bool silent_aim;
		int field_of_view;
		bool autowall;
		bool zeus_bot;
		bool knife_bot;
		bool autoshoot;
		bool double_tap;
		int Double_tap_shift;
		bool slow_teleport;
		bool improve_DT;
		bool twoshot;
		bool faster_recharge;
		bool disable_with_knife;
		bool instant_recharge;
		key_bind double_tap_key;
		bool anti_defensive;
		bool anti_anti_defensive;
		int anti_anti_defensive_ticks;
		bool antiaim_correction;
		bool exploit_antiaim_correction;
		bool quick_peek_assist;
		bool nospread;
		bool norecoil;
		bool nosway;
		key_bind safe_point_key;
		key_bind body_aim_key;
		bool pitch_antiaim_correction;
		int double_tap_shift_value;
		int double_tap_speed;
		int Double_tap_offensive_ticks;
		int Double_tap_defensive_ticks;
		int resikmode = 0;
		int dt_mode = 0;
		float res_side = 35.0f;
		float res_side_second = -35.0f;
		float res_side_third = 35.0f;
		int dt_shift = 13;
		int dt_tolerance = 0;
		bool recharge_dt = false;
		bool break_lag_comp;
		bool secret;
		bool teleport_exploit;
		key_bind teleport_exploit_key;
		bool fake_duck_bypass;
		bool fake_duck_nig;

		struct weapon
		{
			bool double_tap_hitchance;
			int double_tap_hitchance_amount;
			bool hitchance;
			int hitchance_amount;
			bool hitchance_override;
			key_bind hitchance_override_key;
			int hitchance_override_amount;
			int minimum_visible_damage;
			int minimum_damage;
			key_bind damage_override_key;
			int minimum_override_damage;
			std::vector <int> hitboxes;
			bool body_aim_conditions;
			bool head_aim_conditions;
			bool multipoints;
			std::vector <int> multipoints_hitboxes;
			float multipoints_scale;
			float stomach_scale;
			bool adaptive_ps;
			std::vector <int> bodyaimcond;
			std::vector <int> headaimcond;
			bool static_point_scale;
			float head_scale;
			float body_scale;
			bool max_misses;
			int max_misses_amount;
			bool rage_aimbot_ignore_limbs;
			bool prefer_safe_points;
			bool autoscope;
			bool prefer_body_aim;
			bool autostop;
			std::vector <int> autostop_modifiers;
			std::vector <int> doubletap_modifiers;
			int selection_type;
			int body_aim_health;
			float Double_tap_ticks_custom;
		} weapon[8];
	} ragebot;

	struct AntiAim_t
	{
		bool enable;
		int antiaim_type;
		bool hide_shots;
		key_bind hide_shots_key;
		int desync;
		int legit_lby_type;
		int lby_type;
		bool static_legs;
		bool freestand;
		bool anti_brute;
		bool pitch_zero_on_land;
		bool invert_spam;
		int freestand_mode;
		key_bind manual_forward;
		key_bind manual_back;
		key_bind manual_left;
		key_bind manual_right;
		key_bind flip_desync;
		bool flip_indicator;
		Color flip_indicator_color;
		bool fakelag;
		std::vector <int> fakelag_enablers;
		int fakelag_type;
		bool weapon_fakelag;
		int fakelag_amount;
		int triggers_fakelag_amount;
		bool double_tap_lag;
		bool hide_shots_lag;
		bool fakelag_disable_revolver;
		key_bind pitch_zero_on_e_key;
		struct type
		{
			int pitch;
			int base_angle;
			int yaw;
			int range;
			int speed;
			int desync;
			int desync_range;
			int inverted_desync_range;
			int body_lean;
			int inverted_body_lean;

			int spin_speed;
			int desync_spin_range;
			int inverted_desync_spin_range;;
		} type[4];
	} antiaim;

	struct Player_t 
	{
		bool enable;
		int teams;
		bool arrows;
		Color arrows_color;
		int distance;
		int size;
		bool show_multi_points;
		Color show_multi_points_color;
		bool lag_hitbox;
		Color lag_hitbox_color;
		int player_model_t;
		int player_model_ct;
		int local_chams_type;
		bool fake_chams_enable;
		bool visualize_lag;
		bool layered;
		Color fake_chams_color;
		int fake_chams_type;
		bool fake_double_material;
		Color fake_double_material_color;
		int fake_double_material_material;
		bool fake_animated_material;
		Color fake_animated_material_color;
		bool backtrack_chams;
		int backtrack_chams_material;
		Color backtrack_chams_color;
		bool transparency_in_scope;
		float transparency_in_scope_amount;

		struct type
		{
			std::vector <int> flags;
			bool box;
			Color box_color;
			bool name;
			Color name_color;
			bool health;
			bool custom_health_color;
			Color health_color;
			std::vector <int> weapon;
			Color weapon_color;
			bool skeleton;
			Color skeleton_color;
			bool ammo;
			Color ammobar_color;
			bool snap_lines;
			Color snap_lines_color;
			bool footsteps;
			Color footsteps_color;
			int thickness;
			int radius;
			bool glow;
			Color glow_color;
			int glow_type;
			std::vector <int> chams;
			Color chams_color;
			Color xqz_color;
			int chams_type;
			bool double_material;
			Color double_material_color;
			int double_material_material;
			bool animated_material;
			Color animated_material_color;
			bool ragdoll_chams;
			int ragdoll_chams_material;
			Color ragdoll_chams_color;
		} type[3];
	} player;

	struct Player_list_t //-V730
	{
		bool refreshing = false;
		std::vector <Player_list_data> players;

		bool white_list[65];
		bool high_priority[65];
		bool force_safe_points[65];
		bool force_body_aim[65];
		bool low_delta[65];
	} player_list;

	struct Radar_t//-V730
	{
		bool render_local;
		bool render_enemy;
		bool render_team;
		bool render_planted_c4;
		bool render_dropped_c4;
		bool render_health;
	} radar;

	struct Visuals_t
	{
		std::vector <int> indicators;
		Color indicators_left_color;
		Color indicators_right_color;
		std::vector <int> removals;
		bool fix_zoom_sensivity;
		bool velocity_graph;

		bool dynamic_scope_lines;
		bool grenade_prediction;
		bool on_click;
		Color grenade_prediction_color;
		Color grenade_prediction_tracer_color;
		bool projectiles;
		Color projectiles_color;
		bool grenade_timer;
		bool molotov_timer;
		Color molotov_timer_color;
		bool smoke_timer;
		Color smoke_timer_color;
		bool bomb_timer;
		bool bright;
		bool nightmode;
		Color world_color;
		Color props_color;
		int skybox;
		Color skybox_color;
		std::string custom_skybox;
		bool client_bullet_impacts;
		Color client_bullet_impacts_color;
		bool server_bullet_impacts;
		Color server_bullet_impacts_color;
		float bullet_impacts_width;
		bool bullet_tracer;
		Color bullet_tracer_color;
		bool enemy_bullet_tracer;
		Color enemy_bullet_tracer_color;
		bool preserve_killfeed;
		std::vector <int> hitmarker;
		bool hitmarker_test;
		Color hitmarker_color;
		bool hitsound;
		bool killsound;
		bool damage_marker;
		Color damage_marker_color;
		bool kill_effect;
		float kill_effect_duration;
		int fov;
		int viewmodel_fov;
		int viewmodel_x;
		int viewmodel_y;
		int viewmodel_z;
		int viewmodel_roll;
		bool enable_arms_chams;
		bool enable_weapon_chams;
		int arms_overlay_chams;
		int weapon_overlay_chams;
		bool arms_chams;
		int arms_chams_type;
		Color arms_chams_color;
		bool arms_draw_original;
		bool arms_color_modulation;
		bool arms_double_material;
		Color arms_double_material_color;
		bool arms_animated_material;
		Color arms_animated_material_color;
		bool arms_wire_material;
		Color arms_wire_material_color;
		bool weapon_chams;
		int weapon_chams_type;
		Color weapon_chams_color;
		bool weapon_color_modulation;
		bool weapon_double_material;
		Color weapon_double_material_color;
		bool weapon_animated_material;
		Color weapon_animated_material_color;
		bool weapon_wire_material;
		Color weapon_wire_material_color;
		bool fade_wire_material;
		bool taser_range;
		bool show_spread;
		Color show_spread_color;
		bool penetration_reticle;
		bool world_modulation;
		bool weapon_draw_original;
		bool rain;
		float bloom;
		float exposure;
		float ambient;
		bool fog;
		int fog_distance;
		int fog_density;
		Color fog_color;
		std::vector <int> weapon;
		Color box_color;
		Color weapon_color;
		Color weapon_glow_color;
		Color weapon_ammo_color;
		std::vector <int> grenade_esp;
		Color grenade_glow_color;
		Color grenade_box_color;


		/* Prop chams */
		bool drugsmod;
		Color drugsmod_color;
		int drugsmod_type;
		bool drugsmod_double_material;
		Color drugsmod_double_material_color;
		bool drugsmod_wire_material;

		bool drugsmod_orig_material;

		Color drugsmod_wire_material_color;
		bool drugsmod_animated_material;
		Color drugsmod_animated_material_color;

		int proximity_tracers_width;
		Color grenade_proximity_tracers_colors;
		bool offscreen_proximity;
		Color grenade_proximity_warning_progress_color;
		bool grenade_proximity_warning;

		int grenade_proximity_tracers_mode;
	} esp;

	struct Misc_t
	{
		key_bind thirdperson_toggle;
		bool thirdperson_when_spectating;
		int thirdperson_distance;
		bool spectators_list;
		bool ingame_radar;
		bool ragdolls;
		bool bunnyhop;
		int airstrafe;
		bool crouch_in_air;
		key_bind automatic_peek;
		Color automatic_peek_color;
		key_bind edge_jump;
		bool noduck;
		key_bind fakeduck_key;
		bool fast_stop;
		bool slidewalk;
		int leg_movement;
		key_bind slowwalk_key;
		bool chat;
		std::vector <int> log_output;
		std::vector <int> events_to_log;
		key_bind edgebug;
		key_bind jumpbug;
		bool show_default_log;
		Color log_color;
		bool advanced_logs;
		bool inventory_access;
		bool rank_reveal;
		bool clantag_spammer;
		bool buybot_enable;
		int buybot1;
		int buybot2;
		int region_changer;
		std::vector <int> buybot3;
		bool aspect_ratio;
		float aspect_ratio_amount;
		bool anti_screenshot;
		bool anti_untrusted;
		bool left_knife;
		bool fake_ping;
		float ping;
		Color watermark_color;
		std::vector <int> watermarkadditives;
	} misc;

	struct Skins_t 
	{
		bool rare_animations;
		std::array <item_setting, 36> skinChanger;
		std::string custom_name_tag[36];
	} skins;

	struct Menu_t 
	{
		int size_menu;
		Color menu_color;
		Color menu_theme;
		bool watermark;
		Color watermark_color;
		Color watermark_color_background;
		std::vector <int> watermark_addr;

		bool keybinds;
		float windowsize_x_saved;
		bool customize_theme;
		bool blue_theme;
		bool black_theme;
		float windowsize_y_saved;
		float oldwindowsize_x_saved;
		float oldwindowsize_y_saved;
		float speed;
	} menu;

	struct Scripts_t
	{
		bool developer_mode;
		bool allow_http;
		bool allow_file;
		std::vector <std::string> scripts;
	} scripts;

	int selected_config;

	std::string new_config_name;
	std::string new_script_name;
};

extern Config g_cfg;