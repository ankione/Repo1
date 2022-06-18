#ifndef ATSS_IDD_H
#define ATSS_IDD_H
//#include "ATSS_Struct.h"
#include "IRS.h"
#include "ATSS_Includes.h"
/// 2020_12_14 -------------------------------------------------------------------------------------------
//#pragma pack(1)
#ifndef STRUCTURES_H
#define STRUCTURES_H
#include <QList>
//#include <QPolygon>
#include <QTime>
#include <QMap>
#include <QFile>
#include <QLine>

#include "IRS.h"
//#include "message_id.h"

#define MAX_NUM_OF_TRACKS_IN_A_ROUTE    100
#define MAX_NO_OF_POINTS_IN_A_TRACK     100
#define MAX_NO_OF_ROUTES_BTW_PLATFORM   10

#define DUMMY_1_BIT UINT_8
#define DUMMY_2_BIT UINT_8
#define DUMMY_3_BIT UINT_8
#define DUMMY_4_BIT UINT_8
#define DUMMY_5_BIT UINT_8
#define DUMMY_6_BIT UINT_8
#define DUMMY_7_BIT UINT_8


//struct _STRUCT_MESSAGE_HEADER
//{
//    UINT_8 source_id:1;
//    UINT_8 dest_id:1;
//    UINT_8 msg_header_dummy:6;
//    UINT_8 message_id;
//    UINT_8 message_length;
//};

//extern ATSS_XMLConfig xml_config;

typedef struct __attribute__((packed))  _STRUCT_MESSAGE_HEADER
{
    UINT_8 source_id;
    UINT_8 dest_id;
    UINT_16 message_id;
    UINT_8 ows_id;
    UINT_16 message_length;
    UINT_8 no_of_packets;
    UINT_8 packet_number;
    UINT_8 level_id;

    //    _STRUCT_MESSAGE_HEADER()
    //    {
    //        level_id = xml_config.GetCurrentATSSId();
    //    }
}STRUCT_MESSAGE_HEADER;

struct STRUCT_CBI_CONTROL_INFO
{
    UINT_8	cbi_id;
    UINT_8	monitor_flag;
    UINT_8	user_name[MAX_NUM_OF_USERNAME_CHAR];
};

struct STRUCT_CBI_CONTROL
{
    UINT_8	no_of_cbi;
    UINT_8	cbi_control_info[MAX_NUM_OF_CBI];
};

struct STRUCT_ATSS_SEND_CBI_CONTROL_LIST
{
    STRUCT_MESSAGE_HEADER	struct_msg_header;
    STRUCT_CBI_CONTROL	struct_cbi_control;
    ATS_FLAG	ats_flag;
};

struct STRUCT_DWELL_TIME_PER_TRAIN
{
    TRAIN_ID	train_id;
    UINT_16	dwell_time;
};

struct STRUCT_ATSS_ATSD_CMD_STATUS
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STATION_ID              station_id;
    RESPONSE_COMMAND_TYPE	response_cmd_type;
};

struct STRUCT_ATSS_DBA_CMD_STATUS
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STATION_ID              station_id;
    RESPONSE_COMMAND_TYPE	response_cmd_type;
};

struct STRUCT_STATION_INFO
{
    STATION_ID platform_id;
};

struct STRUCT_CMD_STATUS
{
    UINT_8 no_of_skip_station;
    STRUCT_STATION_INFO skip_station[MAX_NUM_OF_STATIONS];
    UINT_8 no_of_train_hold_station;
    STRUCT_STATION_INFO train_hold_station[MAX_NUM_OF_STATIONS];
    UINT_8 no_of_kdc_station;
    STRUCT_STATION_INFO kdc_station[MAX_NUM_OF_STATIONS];
};

struct STRUCT_DBA_ATSS_CMD_STATUS
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_CMD_STATUS       response_cmd_type;
};


struct STRUCT_CYCLE_COMMAND
{
    CBI_ID cbi_id;
    CYCLE_ID cycle_id;
    CYCLE_COMMAND_TYPE cycle_command_type;
};
typedef struct _ATSD_ATSS_CYCLE_COMMAND
{
    STRUCT_MESSAGE_HEADER struct_message_header;
    STRUCT_CYCLE_COMMAND struct_cycle_command;
}ATSD_ATSS_CYCLE_COMMAND_MSG;

typedef struct
{
    UINT_8 type;        //normal, Reverse, both
    UINT_8 upDown;      //Up, down
    QLine line;
}STRUCT_POINT_BOUNDARY;


typedef struct _STRUCT_ESP_
{
    _STRUCT_ESP_()
    {
        espStatus=false;
        timeStatus=true;
        timeValue=QTime(0,0);
    }

    //    QString platformID;
    //    QString platformName;
    bool espStatus;  //1-red, 0-gray
    bool timeStatus;  //0-timeExpires(green) 1- Time Value Present(gray)
    QTime timeValue;
}STRUCT_ESP;

typedef struct _Struct_ESP_Data_
{
    int id;
}Struct_ESP_Data;

typedef struct _STRUCT_ROUTE_POINT_
{
    UINT_8 point_id;
    UINT_8 normal;
    UINT_8 reverse;
}STRUCT_ROUTE_POINT;

typedef struct _STRUCT_ROUTE_TRACK_
{

    TRACK_ID            track_id;
    CBI_ID              cbi_id;
    STRUCT_ROUTE_POINT  point_list[MAX_NO_OF_POINTS_IN_A_TRACK];

}STRUCT_ROUTE_TRACK;

typedef struct _STRUCT_DMRC_ROUTE_DATA_
{
    ROUTE_ID            route_id;
    SIGNAL_ID           src_signal;
    SIGNAL_ID           dest_signal;
    CBI_ID              src_signal_cbi_id;
    CBI_ID              dest_signal_cbi_id;
    VIRTUAL_BLOCK_ID    triggering_vb_id;
    UINT_8              route_direction;
    UINT_8              route_name[15];
    STRUCT_ROUTE_TRACK  route_tracks[MAX_NUM_OF_TRACKS_IN_A_ROUTE];
}STRUCT_DMRC_ROUTE_DATA;

typedef struct _STRUCT_DMRC_ROUTE_DATA_CYCLE
{
    ROUTE_ID            route_id;
    SIGNAL_ID           src_signal;
    SIGNAL_ID           dest_signal;
    CBI_ID              src_signal_cbi_id;
    CBI_ID              dest_signal_cbi_id;
    UINT_8              route_direction;
    UINT_8              route_name[15];
}STRUCT_DMRC_ROUTE_DATA_CYCLE;


typedef struct _STRUCT_ROUTE_TRACK_SIGNAL_
{
    ROUTE_ID            route_id;
    SIGNAL_ID           src_signal;
    SIGNAL_ID           dest_signal;
    CBI_ID              src_signal_cbi_id;
    CBI_ID              dest_signal_cbi_id;
    VIRTUAL_BLOCK_ID    triggering_vb_id;
}STRUCT_ROUTE_TRACK_SIGNAL;


struct STRUCT_ID_MAP
{
    CBI_ID cbi_id;
    TRACK_ID track_id;
    PLATFORM_ID platform_id;
    SIGNAL_ID signal_id;
    STATION_ID station_id;
    VIRTUAL_BLOCK_ID virtual_block_id;
    ROUTE_ID route_id;
};

typedef struct _STRUCT_CYCLE_INFO_
{
    CYCLE_ID    cycle_id;
    CBI_ID      cbi_id;
    STATION_ID station_id;
    UINT_8      direction;
    UINT_8      cycleTypeName[15];
    INT_8       cycleName[15];
    int         status;
    UINT_8      no_of_routes;
    PLATFORM_ID start_platform;
    PLATFORM_ID end_platform;
    //STRUCT_DMRC_ROUTE_DATA struct_route_data[4];
    STRUCT_DMRC_ROUTE_DATA_CYCLE struct_route_data[4];
}STRUCT_DMRC_CYCLE_DATA;

typedef struct _STRUCT_VIRTUAL_BLOCK
{
    VIRTUAL_BLOCK_ID    virtual_block_id;
    UINT_8             virtual_block_name[15];
    VIRTUAL_BLOCK_ID      preceeding_virtual_block_id;
    UINT_8             preceeding_virtual_block_name[15];
    TRACK_ID            parent_track_id;
    UINT_8             parent_track_name[15];
    UINT_16             virtual_block_length_mtr;
    UINT_16             parent_ratp_id;
    UINT_8             parent_ratp_name[15];

}STRUCT_VIRTUAL_BLOCK;

typedef struct __attribute__ ((packed))
{
    PLATFORM_ID     platform_id;
    BOOL            is_emergency_stop_plunger_pressed:1;  //1 SET 0 UNSET
    BOOL            is_all_psd_closed:1;
    BOOL            is_psd_isolated:1;
    DUMMY_5_BIT     dummy_5_bits:5;
}STRUCT_PLATFORM_STATUS;

typedef struct _STRUCT_PLATFORM_DATA_
{
    PLATFORM_ID     platform_id;
    UINT_8          up_down_line;        //1-up Line, 2-Down Line;
    STATION_ID      station_id;
    PLATFORM_NUM    platform_number;
    UINT_8          isBetweenTracks;
    CBI_ID          cbi_id;
    TRACK_ID        trackid;
    ATC_ID          atc_id;
    UINT_8          pl_tb_type; // 2 3 = tb; 0 = otherwise
    UINT_8          pl_tb_capacity;
    Struct_ESP_Data esp;
    INT_8           trK_Name[TRACK_NAME_SIZE];
}STRUCT_DMRC_PLATFORM_DATA;

struct STRUCT_TRK_PLATFORM_MAPPING
{
    TRACK_ID    trk;
    CBI_ID      cbi;
    PLATFORM_ID p_ID;
    STATION_ID  s_ID;
};

struct STRUCT_ROUTE_BTW_PLATFORMS
{
    ROUTE_ID route_id;
    CBI_ID cbi_id;
};

struct STRUCT_POSSIBLE_ROUTES
{
    PLATFORM_ID start_platform_id;
    PLATFORM_ID end_platform_id;
    UINT_16 platform_pair_key;
    UINT_8 no_of_paths;
    STRUCT_ROUTE_BTW_PLATFORMS struct_route_btw_platform[MAX_NO_OF_ROUTES_BTW_PLATFORM];
};

typedef struct __attribute__ ((packed))
{
    STATION_ID      station_id;
    POWER_STATUS    npwr:2;
    POWER_STATUS    spwr:2;
    POWER_STATUS    nups:2;
    POWER_STATUS    sups:2;
    POWER_STATUS    pdc:2;
    DUMMY_6_BIT     dummy_6_bits:6;
}STRUCT_STATION_STATUS;

typedef struct _STRUCT_STATION_DATA_
{
    CBI_ID cbi_id;
    UINT_16 station_id;
    UINT_8 view_id;
    UINT_8 station_name[STATION_NAME_SIZE];
    UINT_8 is_depo;
    UINT_8 station_type;

    STRUCT_STATION_STATUS station_status;
    //TODO ids can be stored if required
}STRUCT_DMRC_STATION_DATA;
typedef struct __attribute__ ((packed)) _STRUCT_SIGNAL_STATUS
{
    SIGNAL_ID	signal_id;
    SIGNAL_TYPE	signal_type:2;
    BOOL	is_g_aspect:1;
    BOOL	is_v_aspect:1;
    BOOL	is_ack_for_block_release_request_command:1;
    BOOL	is_block_release_command_feedback:1;
    BOOL	is_signal_block:1;                              // 0- UNBLOCK 1- BLOCK
    BOOL	is_g_lamp_failure:1;
    BOOL	is_v_lamp_failure:1;
    BOOL	is_r_lamp_failure:1;
    BOOL	is_main:1;
    BOOL	is_diversion:1;
    BOOL	is_second_diversion:1;
    BOOL	is_third_diversion:1;
    BOOL	is_fourth_diversion:1;
    BOOL	is_fifth_diversion:1;
    BOOL	is_route_indicator_lamp_failure:1;
    BOOL	is_proceed_aspect:1;
    BOOL	is_proceed_aspect_failure:1;
    BOOL	is_stop_aspect_failure:1;
    BOOL	is_ack_for_override_release_request_command:1;
    BOOL	is_override_release_command_feedback:1;
    BOOL	is_signal_override:1;
    DUMMY_1_BIT    dummy:1;

    bool IsDataSame(_STRUCT_SIGNAL_STATUS obj) //TODO
    {
        if(obj.signal_type==signal_type)
        {
        }
        return false;
    }
}STRUCT_SIGNAL_STATUS;

typedef struct _STRUCT_DMRC_SIGNAL
{
    UINT_8 signal_id;
    UINT_8 view_id;
    UINT_8 track_id;
    UINT_8 point_id;
    UINT_8 cbi_id;
    int type;
    int direction;

    int overlap_direction; // 1: NW, 2: NE, 3: SE, 4: SW, 5: L, 6: R
    int overlap_text_dir;    // 1: R, 2: L, 3: Top, 4: Bottom
    int overlap_percentage_offset; // Percentage of width of track where symbol needs to be placed
    int overlap_y_offset;

    int up_down;

    int x_pos;
    int y_pos;

    int track_width;
    UINT_8 route_to;
    UINT_8 fleet_on_off;				// 0/1
    UINT_8 route_block;
    UINT_8 approach_lock;
    UINT_8 route_controlled;
    //    STRUCT_SIGNAL_PROPERTY property;
    STRUCT_SIGNAL_STATUS status;

    bool shuntingSignal;
    bool emergencyFlag;

    bool isLastSignal;
    bool overlapsetStatus;


    UINT_8 signal_name[15]; //TODO , new config
    VIRTUAL_BLOCK_ID virtual_block_id;
    UINT_8 offset;

}STRUCT_DMRC_SIGNAL;
typedef struct __attribute__ ((packed)) _STRUCT_POINT_STATUS
{
    POINT_ID	point_id;
    BOOL	is_normal_point_operation_command_feedback:1;
    BOOL	is_reverse_point_operation_command_feedback:1;
    BOOL	is_point_locked:1;
    BOOL	is_point_normal:1;
    BOOL	is_point_reverse:1;
    BOOL	is_point_block_release_request_command_ack:1;
    BOOL	is_point_block_release_command_feedback:1;
    BOOL	is_point_block_set:1;
    BOOL	is_manual_authorization_release_request_command_ack:1;
    BOOL	is_manual_authorization_release_command_feedback:1;
    BOOL	is_ekt_authorization_set:1;                         //manual operation INHIBITED
    BOOL	is_ekt_removed:1;
    BOOL	is_self_normalization_authorise_request_command_ack:1;
    BOOL	is_self_normalization_authorise_command_feedback:1;
    BOOL	is_self_normalization_inhibit_request_command_ack:1;
    BOOL	is_self_normalization_inhibit_command_feedback:1;
    BOOL	is_self_normalization_authorise_status:1;
    DUMMY_7_BIT    dummy_7_bit :7;

}STRUCT_POINT_STATUS;

struct STRUCT_PARENT_POINT_INFO
{
    UINT_8 cbi_id;
    UINT_8 pointID;
    UINT_8 position;
    UINT_8 is_inverted;
};

struct STRUCT_PARENT_CBI
{
    UINT_8 p_track;
    UINT_8 p_cbi;
    UINT_8 no_f_point;
    STRUCT_PARENT_POINT_INFO parent_point[5];
};

struct STRUCT_PARENT_TRACK_DATA
{
    UINT_8 track_ID;
    UINT_8 cbi_ID;
    UINT_8 direction;
    UINT_8 no_f_parent;
    STRUCT_PARENT_CBI parent[5];
};

struct STRUCT_PT_COMBINATION_XML
{
    UINT_8 track_ID; //key trk-id*10000 + cbi+10 + direction(1 ,0)
    UINT_8 cbi_ID;
    UINT_8 direction;
    UINT_8 p_track;
    UINT_8 p_cbi;
    UINT_8 pt_cbi_id;
    UINT_8 pointID;
    UINT_8 position;
};

typedef struct _STRUCT_DMRC_TRACK_WITH_POINT
{
    UINT_8 cbi_id;
    UINT_8 pointID;
    UINT_8 trackID;
    //UINT_8 pointLocation; //Left,Right.Centre
    UINT_8 direction; //NE, SE, SW, NW
    UINT_8 status; //normal, reverse
    UINT_8 percentage;
    UINT_16 point_length;
    UINT_32 point_x;
    UINT_32 point_y;
    UINT_32 width;
    UINT_16 pointPerLoc;
    UINT_16 angle;
    UINT_8 extensionLength;

    bool isParentPoint;
    bool isContainChild;
    UINT_8 point_arm_length; //j, for point arm length

    UINT_8 possile_route;
    UINT_8 possile_route_normal;
    UINT_8 possile_route_reverse;

    //For Route Block, Route Display, TSR
    UINT_8 point_route_block;
    UINT_8 point_route_normal;
    UINT_8 point_route_reverse;

    //STRUCT_POINT_PROPERTY property;
    STRUCT_POINT_STATUS point_status;
    STRUCT_POINT_BOUNDARY pointBoundary;

    INT_8 point_name[15];
    //UINT_16 point_id;
    UINT_8 self_normalization_capable;
}STRUCT_DMRC_TRACK_WITH_POINT;

typedef struct __attribute__((packed))
{
    TRACK_ID track_id;
    BOOL is_free:1;                                          //0-occupied  1-free  (2- out of control ?)
    BOOL is_soft_reset_command_feedback:1;                   //axle counter
    BOOL is_maintenance_block_release_request_command_ack:1;
    BOOL is_maintenance_block_release_command_feedback:1;
    BOOL is_maintenance_block_status_set:1;
    BOOL is_up_direction_emergency_route_locked:1;           //not present
    BOOL is_down_direction_emergency_route_locked:1;           //not present
    BOOL is_down_direction_route_locked:1;     //DN and Upline Reverse
    BOOL is_up_direction_route_locked:1;       //DR and Upline Normal
    BOOL is_down_direction_turnback_route_locked:1;           //not present
    BOOL is_up_direction_turnback_route_locked:1;           //not present
    BOOL is_axle_counter_reset_request_command_ack:1;
    BOOL is_axle_counter_reset_command_feedback:1;
    BOOL is_track_out_of_control:1;
    BOOL is_maintainance_block_set_command_ack:1;
    BOOL is_maintainance_block_set_command_set_feedback:1;
    BOOL is_sub_route_clear:1;
    BOOL is_left_traffic_dir_set:1;
    BOOL is_right_traffic_dir_set:1;
    BOOL is_overlap_set:1;
    BOOL is_dont_care:1;
    DUMMY_3_BIT dummy:3;
}STRUCT_TRACK_STATUS;

struct STRUCT_DMRC_TRACK
{
    UINT_8 trackID;
    UINT_8 is_up_or_down;
    UINT_8 view_id;
    UINT_8 cbi_id;
    UINT_8 atc_id;
    UINT_16 trackLength;
    UINT_16 trackHeight;
    UINT_32 x_pos;
    UINT_32 y_pos;
    UINT_8 pointCount;
    UINT_8 vbCount;
    UINT_8 parent_track_id;
    UINT_8 next_track_id;
    UINT_8 parent_cbi_id;
    UINT_8 next_cbi_id;
    STRUCT_DMRC_TRACK_WITH_POINT mpointList[MAX_NUM_OF_POINTS];
    int selected;
    bool possibleRoute;
    UINT_8 route_block;
    char track_name[TRACK_NAME_SIZE];
    STRUCT_TRACK_STATUS track_status;
    STRUCT_VIRTUAL_BLOCK virtual_block[MAX_NUM_OF_VIRTUAL_BLOCKS];
};

struct STRUCT_TRACK_NEXT_TRACK
{
    TRACK_ID  trackID;
    CBI_ID    cbi_id;
    TRACK_ID  next_track_id;
    CBI_ID    nxt_cbi_id;
    UINT_8    point_count;
    char trk_name[TRACK_NAME_SIZE];
    char nx_trk_name[TRACK_NAME_SIZE];
};
struct STRUCT_TRACK_NEXT_TRACK_POINT
{
    TRACK_ID  trackID;
    CBI_ID    cbi_id;
    TRACK_ID  next_track_id;
    CBI_ID    nxt_cbi_id;
    UINT_8    point_count;
    char trk_name[TRACK_NAME_SIZE];
    char nx_trk_name[TRACK_NAME_SIZE];
};


// New Addition
struct STRUCT_ATC_PLATFORM_DETAILS
{
    UINT_8    ID;  // ICBTC IDs
    UINT_8    Dir;
    UINT_8    dir; // LEFT =1 RIGHT =2
    UINT_16   Idn; // ATC platform IDs
};

struct ATC_ID_STORAGE
{
    UINT_8 atc_ID[10];
};

struct ATS_NODE_CONFIG_COMM_DETAILS
{
    LEVEL_ID    Id;
    char        level[STRING_TEN];
    char        node[STRING_TEN];
    MODULE_ID   module_id;
    char        module_name[STRING_TWENTY];
    char        IPP_ADD[STRING_SIXTEEN];
    WS_INDEX    ws_index;
    PORT_NO     port_no;
};

struct ATS_NODE_CONFIG_COMM_DETAILS_ATSS_ALL_DATA
{
    UINT_8 count;
    ATS_NODE_CONFIG_COMM_DETAILS atss_comm_data[100];
};

struct STRUCT_JUNCTION_MODE_INFO_INTERNAL{
    STATION_ID	station_id;
    JUNCTION_MANAGEMENT_MODE	junction_manage_mode_type;
};

struct STRUCT_SYSTEM_ALARM_PRIORITY_INTERNAL{
    MAX_NO_OF_ALARMS	no_of_alarms;
    ALARM_PRIORITY	struct_alarm_priority[MAX_NUM_OF_ALARMS];//[no_of_alarms];
};

struct STRUCT_CREW_INFO_INTERNAL{
    CREW_ID	crew_id;
    CREW_NAME	crew_name;
};

struct STRUCT_CREW_INVENTORY_INTERNAL{
    RAKE_ID	rake_id;
    TRAIN_ID	train_id;
    CREW_ID	crew_id;
};

struct STRUCT_SYSTEM_CREW_INFO_INTERNAL{
    MAX_NO_OF_CREWS	no_of_crews;
    STRUCT_CREW_INFO_INTERNAL	struct_crew_details[MAX_NUM_OF_ALARMS];
};

struct STRUCT_SYSTEM_CREW_INVENTORY_INTERNAL{
    MAX_NO_OF_CREWS	no_of_crews;
    STRUCT_CREW_INVENTORY_INTERNAL	struct_crew_inventory[MAX_NUM_OF_ALARMS];//[no_of_crews];
};

struct STRUCT_SYSTEM_JUNCTION_MODE_INFO_INTERNAL{
    MAX_NO_OF_STATIONS	no_of_stations;
    STRUCT_JUNCTION_MODE_INFO_INTERNAL	struct_junction_management_mode[MAX_NUM_OF_ALARMS];//[no_of_stations];
};

struct STRUCT_SYSTEM_LOGGED_USER_INFO_INTERNAL{
    MAX_NO_OF_USER_ACCOUNT	no_of_users;
    USER_NAME	username;//[no_of_users];
};
struct STRUCT_PERFORMANCE_RUNNING_TIME_INTERNAL{
    STATION_ID      from_station_id;
    PLATFORM_ID     from_platform_id;
    STATION_ID      to_station_id;
    PLATFORM_ID     to_platform_id;
    RUNNING_TIME	maximum_performance_running_time;
    RUNNING_TIME	five_percent_coasting_running_time;
    RUNNING_TIME	eight_percent_coasting_running_time;
    RUNNING_TIME	energy_saving_running_time;
    RUNNING_TIME	full_coasting_running_time;
};
struct STRUCT_SYSTEM_PERFORMANCE_RUNNING_TIME_INFO_INTERNAL
{
    MAX_NO_OF_PLATFORMS	no_of_platforms;
    STRUCT_PERFORMANCE_RUNNING_TIME_INTERNAL	struct_running_time[MAX_NUM_OF_PLATFORMS_DB];//[no_of_platforms];
};
struct STRUCT_PLATFORM_DWELL_TIME_SET_INTERNAL{
    STATION_ID	stop_station_id;
    PLATFORM_ID	stop_platform_id;
    DWELL_TIME	set_1_dwell_time;
    DWELL_TIME	set_2_dwell_time;
    DWELL_TIME	set_3_dwell_time;
};

struct STRUCT_SYSTEM_PLATFORM_DWELL_TIME_SET_INTERNAL{
    MAX_NO_OF_PLATFORMS	no_of_platforms;
    STRUCT_PLATFORM_DWELL_TIME_SET_INTERNAL	struct_platform_dwell_time_set[MAX_NUM_OF_PLATFORMS];//[no_of_platforms];
};

struct STRUCT_ROLLING_STOCK_INFO_INTERNAL
{
    RAKE_ID               rake_id;
    bool                  is_rolling_profile_exist;   //tells no of cabs in next field
    ROLLING_STOCK_PROFILE rolling_stock_profile;      //4 6 8 (1,2,3)
};

struct STRUCT_SYSTEM_ROLLING_STOCK_INFO_INTERNAL{
    MAX_NO_OF_RAKES	no_of_rakes;
    STRUCT_ROLLING_STOCK_INFO_INTERNAL	struct_rolling_stock_info[MAX_NUM_OF_RAKES];//[no_of_rakes];
};
struct STRUCT_TRAIN_ID_INFO_INTERNAL
{
    RAKE_ID     rake_id;
    bool        is_train_id_exist;
    TRAIN_ID	train_id;
};

struct STRUCT_SYSTEM_TRAIN_ID_INFO_INTERNAL{
    MAX_NO_OF_RAKES	no_of_rakes;
    STRUCT_TRAIN_ID_INFO_INTERNAL	struct_train_id_info[MAX_NUM_OF_RAKES];//[no_of_rakes];
};

//struct STRUCT_INIT_SYSTEM_SELECTED_AUTHORITY_AREA
//{

//};

struct STRUCT_INIT_SYSTEM_ALARM_PRIORITY_INFO
{
    STRUCT_SYSTEM_ALARM_PRIORITY_INTERNAL	struct_system_alarm_priority;
};

struct STRUCT_INIT_SYSTEM_CREW_INFO
{
    STRUCT_SYSTEM_CREW_INFO_INTERNAL	struct_system_crew_info;
};

struct STRUCT_INIT_SYSTEM_JUNCTION_MODE_INFO
{
    STRUCT_SYSTEM_JUNCTION_MODE_INFO_INTERNAL	struct_system_junction_mode_info;
};

struct STRUCT_INIT_SYSTEM_PERFORMANCE_RUNNING_TIME_INFO
{
    STRUCT_SYSTEM_PERFORMANCE_RUNNING_TIME_INFO_INTERNAL struct_system_performance_running_time_info;
    //@check REQ_TYPE	req_type;
};

struct STRUCT_INIT_SYSTEM_PLATFORM_DWELL_TIME_INFO
{
    STRUCT_SYSTEM_PLATFORM_DWELL_TIME_SET_INTERNAL	struct_system_platform_dwell_time_set;
};

struct STRUCT_INIT_SYSTEM_ROLLING_STOCK_INFO
{
    STRUCT_SYSTEM_ROLLING_STOCK_INFO_INTERNAL	struct_system_rolling_stock_info;
};

struct STRUCT_INIT_SYSTEM_TRAIN_ID_INFO
{
    STRUCT_SYSTEM_TRAIN_ID_INFO_INTERNAL	struct_system_train_id_info;
};

struct STRUCT_INIT_SYSTEM_PARAMETER_INFO
{
    AVERAGE_SPEED                   average_speed;                  //km/hr
    DELAY_DETECTION_THRESHOLD       delay_detection_threshold;      //s
    DEPARTURE_OFFSET                departure_offset;                     //s
    INTERSTATION_STOP_DETECT_TIME   interstation_stop_detect_time;        //s
    ROUTE_TRIGGER_OFFSET            route_trigger_offset;                 //s
    WAKEUP_COMMAND_OFFSET           wakeup_command_offset;        //s
    DWELL_TIME                      minimum_dwell_time;       //s
    DWELL_TIME                      max_dwell_time;       //s
    CONFLICT_TIME                   conflict_time;
    TUNNEL_LIMIT                    tunnel_limit;         //s
    UINT_16                         pti_time;
    UINT_8                          atr_enable_disable_flag;
};

struct STRUCT_DBA_ATSS_SYSTEM_PARAMETER_INFO
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_INIT_SYSTEM_PARAMETER_INFO parameters;
};

struct STRUCT_INITIALIZATION_STATUS
{
    bool system_rolling_stock;
    bool system_crew_info;
    bool system_train_id_info;
    bool system_alarm_priority;
    bool system_junction_mode_info;
    bool system_dwell_time_info;
    bool system_performance_running_info;
    bool system_parameter_info;
    bool selected_system_authority_area;
    bool time_table_info;
    bool safety_cmd_counter;
};

#endif // STRUCTURES_H


/// 2020_12_14 ##########################################################################################


struct STRUCT_ATSS_PORT_IP
{
    UINT_16 ATSS_RECV_PORT;
    INT_8 UDPADDRESS_ATSS[STRING_SIXTEEN];
};

struct STRUCT_PC_PORT_IP
{
    UINT_16 ATSS_PC_PORT;
    INT_8 UDPADDRESS_PC[STRING_SIXTEEN];
};

struct STRUCT_DBA_PORT_IP
{
    UINT_16 ATSS_DBA_PORT;
    INT_8 UDPADDRESS_DBA[STRING_SIXTEEN];
};

struct STRUCT_ATSD_PORT_IP
{
    UINT_16 ATSS_ATSD_PORT;//[MAX_NUM_OF_WORKSTATION];
    INT_8 UDPADDRESS_ATSD[STRING_SIXTEEN];
};

struct STRUCT_ATSD_BROADCAST_PORT_IP
{
    UINT_16 ATSS_ATSD_BROADCAST_PORT;
    INT_8 UDPADDRESS_BROADCAST[STRING_SIXTEEN];
};

struct STRUCT_COMMAND_TYPE_ACK
{
    CBI_ID              cbi_id;
    ENTITY_ID           entity_id;
    ENTITY_TYPE         entity_type;
    ENTITY_COMMAND_TYPE command_type;
    UINT_32             t_sec;
    INT_8               valid_case_string[STRING_FIFTY];
    INT_8               invalid_case_string[STRING_FIFTY];

};

struct STRUCT_GENERAL_MESSAGE_ATSS
{
    _STRUCT_MESSAGE_HEADER msg_header;
    INT_8 body[MAX_COMMUNICATION_BUFFER_SIZE];
};
struct STRUCT_DATE_TIME_INTERNAL
{
    UINT_8  day;
    UINT_8  month;
    UINT_16 year;
    UINT_8  hours;
    UINT_8  minutes;
    UINT_8  seconds;
    UINT_16 millisecond;
};

struct STRUCT_DATE_TIME
{
    UINT_8  day;
    UINT_8  month;
    UINT_16 year;
    UINT_8  hours;
    UINT_8  minutes;
    UINT_8  seconds;
};

//struct STRUCT_DATE
//{
//    UINT_8  day;
//    UINT_8  month;
//    UINT_16 year;
//};
//struct STRUCT_TIME
//{
//    UINT_8  hours;
//    UINT_8  minutes;
//    UINT_8  seconds;
//};


struct STRUCT_NEXT_DEPARTURES
{
    UINT_8 rolling_stock_profile1:4;
    UINT_8 platform_number1:4;
    UINT_8 hours1;
    UINT_8 minutes1;
    UINT_8 seconds1;
    UINT_8 destination_number1;
    UINT_8 train_stopping_and_spare1;
    UINT_8 train_stopping_and_spare2;
    UINT_8 train_stopping_and_spare3;
    UINT_8 train_stopping_and_spare4;
    UINT_8 train_stopping_and_spare5;
};
struct STRUCT_ATSS_PC_NEXT_THREE_DEPARTURES_ID
{
    STRUCT_MESSAGE_HEADER msg_header;
    UINT_8 station_code;
    UINT_8 departures:2;
    UINT_8 departures_dummy:6;
    STRUCT_NEXT_DEPARTURES next_three_departures[THREE];
};

struct STRUCT_PRINT_DATA_INTERNAL
{
    INT_8 print_str[MAX_PRINT_STR];
    UINT_8 nlcnt;
    UINT_8 tcnt;
    INT_32 textcnt;
};

struct STRUCT_VIRTUAL_BLOCKS
{
    UINT_16 vb_id;
    UINT_16 atc_id;
    UINT_16 len_in_meters;
    UINT_16 prev_vb_id;
    UINT_16 vb_name;
};

struct STRUCT_TRACK_DATA
{
    UINT_16 parent_track_id;
    UINT_16 screen_width;
    UINT_16 y_pos;
    UINT_16 x_pos;
    UINT_16 track_name;
    STRUCT_VIRTUAL_BLOCKS struct_virtual_blocks[MAX_NUM_OF_VIRTUAL_BLOCKS];
};

struct STRUCT_XMLCONFIG_DATA
{
    UINT_8 no_of_tracks;
    STRUCT_TRACK_DATA struct_tracK_data[MAX_NUM_OF_TRACKS];

};

///IDD Struct
struct STRUCT_TIME{
    HOUR    hour;
    MINUTE  minute;
    SECOND  second;
};

struct STRUCT_DATE{
    DAY     day;
    MONTH   month:4;
    DUMMMY_4_BIT dummy:4;
    YEAR    year;
};

struct STRUCT_ACTUAL_DWELL_TIME_PER_HOUR{
    STRUCT_TIME	from_time;
    STRUCT_TIME	to_time;
    DWELL_TIME	actual_dwell_time;
    TRAIN_ID	train_id;
};

struct STRUCT_ACTUAL_DWELL_TIME_REPORT{
    STATION_ID                          station_id;
    PLATFORM_ID                         platform_id;
    MAX_NO_OF_HOURS                     no_of_hours;
    STRUCT_ACTUAL_DWELL_TIME_PER_HOUR	struct_actual_dwell_time_per_hour;//[no_of_hours];
};

struct STRUCT_TIME_MSEC
{
    HOUR    hour;
    MINUTE  minute;
    SECOND  second;
    UINT_16 millisec;
};

struct STRUCT_ALARM{
    ALARM_ID        alarm_id;               //generated
    STATION_ID      station_id;             //
    ENTITY_ID       entity_id;              //
    ALARM_TYPE      alarm_type;             //
    USER_NAME       logged_user_name[STRING_TWENTY_FIVE];   //DBA
    //ALARM_STRING    alarm_text[STRING_TWO_FIFTY];         //SyRS
    //UINT_8          comments[STRING_FIFTY];
    UINT_8          comments[101];
    STRUCT_DATE     generation_date;
    STRUCT_TIME_MSEC     generation_time;
    ALARM_PRIORITY  alarm_priority;//:2;       //DBA
    ALARM_STATUS    alarm_status;//:2;         //
    ENTITY_TYPE     entity_type;//:4;          //
};

struct	STRUCT_ALARM_FILTER{
    USER_NAME	logged_user_name;
    ENTITY_ID	entity_id;
    STATION_ID	station_id;
    BOOL	is_alarm_status:1;
    BOOL	is_occurrence_date_time:1;
    BOOL	is_station_id:1;
    BOOL	is_entity_type:1;
    BOOL	is_entity_id:1;
    BOOL	is_logged_user_name:1;
    BOOL	is_priority:1;
    BOOL	reserved:1;
    ALARM_STATUS	alarm_status;
    ALARM_PRIORITY	alarm_priority;
    ENTITY_TYPE	entity_type;
    STRUCT_DATE	from_occurrence_date;
    STRUCT_DATE	to_occurrence_date;
    STRUCT_TIME	from_occurrence_time;
    STRUCT_TIME	to_occurrence_time;
};

struct STRUCT_ALARM_LIST{
    MAX_NO_OF_ALARMS    no_of_alarms;
    STRUCT_ALARM	struct_alarm;//[no_of_alarms];
};

struct STRUCT_ALARM_PRIORITY{
    ALARM_TYPE	alarm_type;
    ALARM_PRIORITY	alarm_priority;
};

struct	STRUCT_EM_COMMAND_PACKET{
    EMERGENCY_SECTION_ID	emergency_section_id;
    ATC_ZONE_EMERGENCY_STOP	own_zone_emergency_stop_command;
    ATC_REMOTE_RESET_COMMAND	sc_remote_reset_command;
    EMERGENCY_MODE_SETTING	emergency_mode_setting_command;
    BOOL	emergency_status:1;
    DUMMY_7_BIT	reserved_7bit;
};

struct STRUCT_ATC_EM_COMMAND_PACKET{
    ATC_ID	atc_id;
    MAX_NO_OF_EMERGENCY_SECTION	no_of_emergency_sections;
    STRUCT_EM_COMMAND_PACKET	struct_em_command_packet;//[no_of_emergency_sections];
};


struct	STRUCT_PLATFORM_COMMAND{
    PLATFORM_ID     platform_id;
    STATION_ID      station_id;                 // not needed ANSHUMAYA SIR platform ID is unique in ICBTC
    PLATFORM_HOLD	platform_hold:2;
    DOOR_DIRECTION	psd_open_command:2;         //line 8
    DOOR_DIRECTION	psd_close_command:2;        //line 8
    PSD_FAILURE     psd_failure:2;              //line 8
    STATION_ID      skip_station_id;            /// 1 - skip stop 0 -no skip stop

    // PLATFORM_COMMAND_TYPE_KEEP_DOOR_CLOSED          5 //psd and train doors LINE 1
    // PLATFORM_COMMAND_TYPE_RECEIVE_KEEP_DOOR_RELEASE 6 //psd and train doors LINE 1
    //#define PLATFORM_COMMAND_TYPE_STATION_DOOR_OPEN         7 LINE 8
    //#define PLATFORM_COMMAND_TYPE_STATION_DOOR_CLOSE        8 LINE 8
    //#define PLATFORM_COMMAND_TYPE_TRAIN_DOOR_OPEN           9 LINE 8
    //#define PLATFORM_COMMAND_TYPE_TRAIN_DOOR_CLOSE          10 LINE 8

};

struct STRUCT_AVG_DWELL_TIME_PER_HOUR{
    STRUCT_TIME	from_time;
    STRUCT_TIME	to_time;
    DWELL_TIME	min_dwell_time;
    DWELL_TIME	max_dwell_time;
    DWELL_TIME	avg_dwell_time;
};

struct STRUCT_AVG_DWELL_TIME_REPORT{
    STATION_ID	station_id;
    MAX_NO_OF_HOURS	no_of_hours;
    STRUCT_AVG_DWELL_TIME_PER_HOUR	struct_avg_dwell_time_per_hour_left_direction;//[no_of_hours];
    STRUCT_AVG_DWELL_TIME_PER_HOUR	struct_avg_dwell_time_per_hour_right_direction;//[no_of_hours];
};

struct STRUCT_CBI_COMMAND{
    CBI_ID	cbi_id;
    PARTICULAR_CBI_COMMAND_TYPE	cbi_command_type;
};
struct STRUCT_OVERLAPPING_STATUS{
    OVERLAP_ID	overlap_id;
    BOOL	is_setting_command_feedback:1;
    BOOL	is_overlap_status_set:1;
    DUMMY_6_BIT dummy_6_bit:6;
};

struct STRUCT_SPK_COMMAND{
    CBI_ID	cbi_id;
    SPK_ID	spk_id;
    SPK_COMMAND_TYPE	spk_command_type;
};

struct STRUCT_SPK_STATUS{
    BOOL	is_spk_authorization_release_command_feedback:1;
    BOOL	is_spk_authorization_release_request_command_ack:1;
    BOOL	is_spk_authorization_set:1;
    BOOL	is_spk_removed:1;
    DUMMY_4_BIT dummy_4_bit:4;
};


struct STRUCT_CYCLE_STATUS{
    CYCLE_ID	cycle_id;
    BOOL        is_cycle_set:1;
    DUMMY_7_BIT dummy_7_bit:7;
};

struct STRUCT_EMERGENCY_SECTION_STATUS{
    EMERGENCY_SECTION_ID	emergency_section_id;
    BOOL is_emergency_mode_set:1;
    DUMMY_7_BIT dummy_7_bit:7;
};

struct STRUCT_RAKE_TIMETABLE_DETAIL{
    RAKE_ID	rake_id;
    DISTANCE_IN_KILOMETER	distance_covered;
    DURATION_IN_MINUTES	time_duration;
};

struct STRUCT_REGISTERED_TIMETABLE{
    STRING_50	timetable_name;
    STRUCT_DATE	date;
};

struct	STRUCT_REGISTRATION_INFO{
    STRING_50	timetable_name;
    STRUCT_DATE	date;
    BOOL	link_unlink:1;
    DUMMY_7_BIT	dummy_7_bit:7;
};

struct STRUCT_ATSS_ATSD_ONLINE_TIME_TABLE
{
    STRUCT_MESSAGE_HEADER msg_header;
    STRING_50             time_table_name[MAX_TIME_TABLE_NAME_STR];
};

struct STRUCT_REQ_FOR_TIME_TABLE{
    STRUCT_DATE           date;
    STRING_50             time_table_name[MAX_TIME_TABLE_NAME_STR];
    TIME_TABLE_REQ_TYPE   time_table_req_type:4;  //0- display 1 - delete 2 -register 3- load switch to tt mode 4 ;load online tt 6 -
    BOOL                  is_date:1;
    BOOL                  is_timetable_name:1;
    DUMMY_2_BIT           dummy_2_bit:2;
};

struct	STRUCT_REQ_REPORT{
    JOURNEY_ID	journey_id;
    STATION_ID	station_id;
    PLATFORM_ID	platform_id;
    CREW_ID	crew_id;
    MONTH	month;
    TRIP_ID	trip_id;
    STRUCT_DATE	time_table_date;
    REPORT_TYPE	report_type:5;
    BOOL	is_time_table_data_exist:1;
    BOOL	is_journey_id_exist:1;
    BOOL	is_trip_id_exist:1;
    BOOL	is_station_id_exist:1;
    BOOL	is_platform_id_exist:1;
    BOOL	is_crew_id_exist:1;
    BOOL	is_month_exist:1;
    DUMMY_4_BIT	dummy_4_bit:4;
};

struct	STRUCT_ROLLING_STOCK_INFO{
    RAKE_ID               rake_id;
    BOOL                  is_rolling_profile_exist:1;
    ROLLING_STOCK_PROFILE rolling_stock_profile:2;
    DUMMY_5_BIT           dummy_5_bit:5;
};

struct STRUCT_ROUTE_COMMAND{

    CBI_ID              cbi_id;
    ROUTE_ID            route_id;
    ROUTE_COMMAND_TYPE	route_command_type;
};


struct STRUCT_SERVER_HEALTH{
    SERVER_ID	server_id;
    BOOL	is_connected;
};

struct STRUCT_SIGNAL_COMMAND{
    CBI_ID	cbi_id;
    SIGNAL_ID	signal_id;
    SIGNAL_COMMAND_TYPE	signal_command_type;
};

struct STRUCT_STATION_COMMAND{
    STATION_ID	station_id;
    MAX_NO_OF_PLATFORMS	no_of_platforms;
    STRUCT_PLATFORM_COMMAND	struct_platform_command;//[no_of_platforms];
};

struct STRUCT_ATC_STATION_COMMAND_PACKET{
    ATC_ID	atc_id;
    MAX_NO_OF_PLATFORMS	no_of_stations;
    STRUCT_STATION_COMMAND	struct_station_command;//[no_of_stations];
};
struct STRUCT_STATION_RESPONSE{
    STATION_ID	station_id;
    MAX_NO_OF_PLATFORMS	no_of_platforms;
    /*RhpBoolean*/BOOL	struct_platform_response;//[no_of_platforms];           //DOUBT
};
struct STRUCT_ATC_STATION_RESPONSE_PACKET{
    ATC_ID	atc_id;
    MAX_NO_OF_PLATFORMS	no_of_stations;
    STRUCT_STATION_RESPONSE	struct_station_response;//[no_of_stations];
};
//struct STRUCT_STATION_STATUS{
//    STATION_ID	station_id;
//    POWER_STATUS	npwr;
//    POWER_STATUS	spwr;
//    POWER_STATUS	nups;
//    POWER_STATUS	sups;
//    POWER_STATUS	pdc;
//};
struct	STRUCT_ROUTE_STATUS{
    ROUTE_ID    route_id;
    BOOL        is_block_release_request_command_ack:1;
    BOOL        is_route_block_release_command_feedback:1;   // 0 - FAIL
    BOOL        is_route_block_set:1;                       //0  - UNBLOCK 1 - BLOCK
    BOOL        is_route_set_release_command_feedback:1;
    BOOL        is_route_not_approach_locked:1;             //signal id needed
    BOOL        is_route_release_no_timer_running:1;
    BOOL        is_fleet_set:1;
    BOOL        is_route_set:1;  //0  - SET 1 -UNSET
    BOOL        is_block_set_request_command_ack:1;
    BOOL        is_block_set_request_command_feedback:1;
    UINT_8      dummy_bit:6;
};


struct STRUCT_CBI_STATUS
{
    BOOL	init_status:1;
    BOOL	ats_mode_command:1;
    BOOL	mode_feedback:1;
    BOOL	health_status:1;
    BOOL	master_slave_status:1;//CBI active
    DUMMY_3_BIT	dummy_3_bit:3;
};
struct STRUCT_CBI_RESPONSE
{
    CBI_ID                          cbi_id;
    BOOL                            is_all_signal_block_release_request_command_ack:1;  //present in alarm pdf
    BOOL                            is_all_signal_block_release_command_feedback:1;
    BOOL                            is_all_signal_block_status:1;
    BOOL                            is_vdu_enable:1;    //IF ENABLED; CHECK FOR CURRENT LEVEL OF ats SERVER AND MESSSAGE TO BE SENT ON CHANGE
    DUMMY_4_BIT                     dummy_4_bit:4;
    STRUCT_CBI_STATUS               struct_cbi_status;                                  //CBI active
    STRUCT_SPK_STATUS               struct_spk_status;
    STRUCT_ROUTE_STATUS             struct_route_status[500];
    STRUCT_TRACK_STATUS             struct_track_status[100];
    STRUCT_POINT_STATUS             struct_point_status[100];
    STRUCT_OVERLAPPING_STATUS       struct_overlapping_status[200];
    STRUCT_SIGNAL_STATUS            struct_signal_status[100];
    STRUCT_CYCLE_STATUS             struct_cycle_status[50];
    STRUCT_EMERGENCY_SECTION_STATUS struct_emergency_section_status[50];
    STRUCT_PLATFORM_STATUS          struct_platform_status[50];
    STRUCT_STATION_STATUS           struct_station_status[100];
};

struct STRUCT_TRAIN_ID
{
    JOURNEY_ID  j_ID;
    RAKE_ID     rake_id;
    TRAIN_ID    train_id;
    INT_8       trip_id[MAX_TRIP_ID_STR_INTERNAL];
    PLATFORM_ID dest_platform;
    STATION_ID  dest_station;
};

struct STRUCT_CURRENT_TRAIN_ID
{
    RAKE_ID rake_id;
    int     train_id;
};

struct STRUCT_CONFLICT
{
    JOURNEY_ID          journey_id_1;
    TRIP_ID             trip_id_1[MAX_TRIP_ID_STR_INTERNAL];
    STOPPING_POINT_ID   stopping_point_id_1;
    JOURNEY_ID          journey_id_2;
    STOPPING_POINT_ID   stopping_point_id_2;
    TRIP_ID             trip_id_2[MAX_TRIP_ID_STR_INTERNAL];
    STRING_50           conflict_string[STRING_FIFTY];
};

struct STRUCT_CREDENTIAL
{
    USER_NAME	username;
    PASSWORD	password;
};

struct STRUCT_CREW_INFO{
    CREW_ID	crew_id;
    CREW_NAME	crew_name;
};

struct STRUCT_CREW_INVENTORY{
    RAKE_ID	rake_id;
    TRAIN_ID	train_id;
    CREW_ID	crew_id;
};
struct STRUCT_CREW_TIMETABLE_DETAIL{
    CREW_ID	crew_id;
    DISTANCE_IN_KILOMETER	distance_covered;
    MAX_NO_OF_RAKES	no_of_rakes;
    STRUCT_RAKE_TIMETABLE_DETAIL	struct_rake_detail;//[no_of_rake_details];
};

struct STRUCT_CREW_KM_RUN_PER_DAY{
    STRUCT_DATE	struct_date;
    MAX_NO_OF_CREWS	no_of_crews;
    STRUCT_CREW_TIMETABLE_DETAIL	struct_crew_timetable_details;//[no_of_crews];
};

struct STRUCT_CREW_KM_RUN_REPORT{
    MAX_NO_OF_DAYS_IN_MONTH	no_of_days;
    STRUCT_CREW_KM_RUN_PER_DAY	struct_crew_km_run_per_day;//[no_of_days];
};


struct	STRUCT_EM_RESPONSE_PACKET{
    EMERGENCY_SECTION_ID	emergency_section_id; ///to update no of bits
    BOOL	own_zone_emergency_status:1;
    BOOL	emergency_status:1;
    ATC_ZONE_EMERGENCY_STOP	own_zone_emergency_stop_status:2;
    EMERGENCY_MODE_SETTING	emergency_mode_setting_status:4;
    ATC_REMOTE_RESET_COMMAND	sc_remote_reset_status:2;
};


struct STRUCT_ATC_EM_RESPONSE_PACKET{
    ATC_ID	atc_id;
    MAX_NO_OF_EMERGENCY_SECTION	no_of_emergency_sections;
    STRUCT_EM_RESPONSE_PACKET	struct_em_response_packet;//[no_of_emergency_sections];
};



struct STRUCT_EVENT{
    EVENT_ID        event_id;
    STATION_ID      station_id;
    ENTITY_ID       entity_id;
    EVENT_TYPE      event_type;
    USER_NAME       logged_user_name[25];
    //ALARM_STRING    event_text[STRING_TWO_FIFTY];
    UINT_8          comments[101];
    STRUCT_DATE     generation_date;
    //STRUCT_TIME     generation_time;
    STRUCT_TIME_MSEC     generation_time;
    ENTITY_TYPE     entity_type:7; /// CHANGED 25_10_2021_WITH MOHIT SIR DBA
    DUMMMY_4_BIT    user_or_system:1;
};


struct	STRUCT_EVENT_FILTER
{
    STATION_ID	station_id;
    ENTITY_ID	entity_id;
    USER_NAME	logged_user_name;
    STRUCT_DATE	from_occurrence_date;
    STRUCT_DATE	to_occurrence_date;
    STRUCT_TIME	from_occurrence_time;
    STRUCT_TIME	to_occurrence_time;
    ENTITY_TYPE	entity_type;
    ALARM_PRIORITY	event_priority;
    BOOL	is_occurrence_date_time;
    BOOL	is_station_id;
    BOOL	is_entity_type;
    BOOL	is_entity_id;
    BOOL	is_logged_user_name;
    BOOL	is_priority;
    DUMMY_4_BIT	dummy_4bit;
};

struct STRUCT_EVENT_LIST
{
    MAX_NO_OF_EVENTS	no_of_events;
    STRUCT_EVENT	struct_event;//[no_of_events];
};

struct STRUCT_RAKE_JOURNEY_DATA
{
    RAKE_ID      rake_id;
    JOURNEY_ID   journey_id;
    //TRAIN_ID   train_id;
    TRAIN_ID     downline_ID;
    TRAIN_ID     upline_ID;
};

struct STRUCT_RAKE_JOURNEY
{
    RAKE_ID     rake_id;
    JOURNEY_ID	journey_id;
};
struct STRUCT_HEADWAY_SETTING
{
    CYCLE_ID    left_cycle_id;
    CBI_ID      left_cycle_cbi_id;
    CYCLE_ID    right_cycle_id;
    CBI_ID      right_cycle_cbi_id;
    HEADWAY     headway;
    DWELL_TIME  dwell_time;
    UINT_8      no_of_trains;
    UINT_8      set_reset_flag; //1- RESET  2 - SET

};
struct STRUCT_HEADWAY
{
    HEADWAY_OPERATION_TYPE  headway_operation_type;
    UINT_8                  num_of_headway_setting;
    STRUCT_HEADWAY_SETTING  struct_headway_setting[MAX_NUM_OF_HEADWAY_SETTING];
    UINT_8                  no_of_rakes;
    STRUCT_RAKE_JOURNEY     struct_rake_journey[MAX_NUM_OF_RAKE_HEADWAY];
};

struct STRUCT_HEADWAY_INTERVAL
{
    TRAIN_ID	train_id;
    STRUCT_TIME	departure_time;
    STRUCT_TIME	arrival_time;
};

struct STRUCT_HEADWAY_INTERVAL_REPORT
{
    PLATFORM_ID	platform_id;
    MAX_NO_OF_TRAINS	no_of_trains;
    STRUCT_HEADWAY_INTERVAL	struct_headway_interval;//[no_of_trains];
};


struct STRUCT_INETRSTATION_RUNTIME{
    STRUCT_TIME	from_time;
    STRUCT_TIME	to_time;
    RUNNING_TIME	minimum_run_time;
    RUNNING_TIME	maximum_run_time;
    RUNNING_TIME	average_run_time;
};

struct STRUCT_INETRSTATION_RUNTIME_REPORT{
    STATION_ID	source_station_id;
    STATION_ID	destination_station_id;
    STRUCT_DATE	journey_date;
    MAX_NO_OF_HOURS	no_of_hours;
    STRUCT_INETRSTATION_RUNTIME	struct_interstation_runtime;//[no_of_hours];
};

struct STRUCT_INTERSTATION_STOP{
    STATION_ID	station_id;
    DURATION_IN_MINUTES	total_stop_time;
    MAX_NO_OF_INTERSTATION_STOP_OCCURRENCE	no_of_occurrences;
    DURATION_IN_SECONDS	stopped_time;//[no_of_occurrences];
};

struct STRUCT_INTERSTATION_STOP_REPORT{
    MAX_NO_OF_STATIONS	no_of_stations;
    STRUCT_INTERSTATION_STOP	struct_interstation_stop_left_direction;//[no_of_stations];
    STRUCT_INTERSTATION_STOP	struct_interstation_stop_right_direction;//[no_of_stations];
};

struct STRUCT_STOPING_POINT_DETAIL{
    STOPPING_POINT_ID           stoping_point_id;
    STATION_ID                  station_id;
    PLATFORM_ID                 platform_id;  //Key different for up journey and down journey
    DISTANCE_IN_METER           distance_from_previous_station;
    STRUCT_TIME                 scheduled_arrival_time;
    STRUCT_TIME                 sched_depart;
    DWELL_TIME                  dwell_time;
    TRAIN_PERFORMANCE_REGIME    performance_regime;
    SERVICE_TYPE                service_type;
    BOOL                        is_crew_linked;
    CREW_ID                     crew_id;
    RAKE_ID                     rake_id;
    BOOL                        is_reconciled;
    STRUCT_TIME                 actual_arrival_time;
    STRUCT_TIME                 actual_departure_time;
    TRAIN_PERFORMANCE_REGIME	actual_performance_regime;
    STRUCT_TIME                 est_arrival_time;
    STRUCT_TIME                 est_departure_time;
};


//struct STRUCT_STOPING_POINT_DETAIL_INTERNAL{
//    STOPPING_POINT_ID           stoping_point_id;
//    STATION_ID                  station_id;
//    PLATFORM_ID                 platform_id;
//    STRUCT_TIME                 scheduled_arrival_time;
//    STRUCT_TIME                 sched_depart;
//    DWELL_TIME                  dwell_time;//ANKIT
//};



struct STRUCT_TRIP_DETAIL{
    TRIP_ID	trip_id;
    MAX_NO_OF_STOPPING_POINT_IN_TRIP	no_of_stopping_point;
    STRUCT_STOPING_POINT_DETAIL	struct_stopping_point_detail[MAX_NUM_OF_STOPPING_POINTS];//[no_of_stopping_point];
};


struct STRUCT_JOURNEY_DETAIL{
    JOURNEY_ID	journey_id;
    MAX_NO_OF_STOPPING_POINT_IN_TRIP	no_of_trips_in_journey;
    STRUCT_TRIP_DETAIL	struct_trip_detail[MAX_NUM_OF_TRIPS];//[no_of_trips_in_journey];
};
struct STRUCT_TRIP_DETAIL_INTERNAL{
    TRIP_ID	trip_id;
    MAX_NO_OF_STOPPING_POINT_IN_TRIP	no_of_stopping_point;
    STOPPING_POINT_ID                   stp_id[MAX_NUM_OF_STOPPING_POINTS];
};
struct STRUCT_JOURNEY_DETAIL_INTERNAL{
    JOURNEY_ID	journey_id;
    MAX_NO_OF_STOPPING_POINT_IN_TRIP	no_of_trips_in_journey;
    TRIP_ID                             trip_id[MAX_NUM_OF_TRIPS];
};

struct STRUCT_MEAN_DELAY_PER_HOUR{
    STRUCT_TIME	from_time;
    STRUCT_TIME	to_time;
    MAX_NO_OF_DELAY	no_of_delays;
    DELAY	average_arrival_delay;
    DELAY	average_departure_delay;
};

struct STRUCT_MEAN_DELAY_PER_LINE{
    STRUCT_TIME	station_id;
    STRUCT_TIME	platform_id;
    PLATFORM_REFERENCE	platform_reference;
    DELAY	average_arrival_delay;
    DELAY	average_departure_delay;
    MAX_NO_OF_DELAY	no_of_delays;
};

struct STRUCT_MEAN_DELAY_PER_LINE_REPORT{
    MAX_NO_OF_PLATFORMS	no_of_platforms;
    STRUCT_MEAN_DELAY_PER_LINE	struct_mean_delay_per_line_left_direction;//[no_of_platforms];
    STRUCT_MEAN_DELAY_PER_LINE	struct_mean_delay_per_line_right_direction;//[no_of_platforms];
};

struct STRUCT_MEAN_DELAY_PER_STATION_TIME_RANGE_REPORT{
    STATION_ID	station_id;
    PLATFORM_ID	platform_id;
    MAX_NO_OF_HOURS	no_of_hours;
    STRUCT_MEAN_DELAY_PER_HOUR	struct_mean_delay_per_hour_left_direction;//[no_of_hours];
    STRUCT_MEAN_DELAY_PER_HOUR	struct_mean_delay_per_hour_right_direction;//[no_of_hours];
};

struct STRUCT_MEAN_DELAY_PER_TIME_RANGE{
    STATION_ID	station_id;
    PLATFORM_ID	platform_id;
    MAX_NO_OF_HOURS	no_of_hours;
    STRUCT_MEAN_DELAY_PER_HOUR	struct_mean_delay_per_hour_left_direction;//[no_of_hours];
    STRUCT_MEAN_DELAY_PER_HOUR	struct_mean_delay_per_hour_right_direction;//[no_of_hours];
};

struct STRUCT_MEAN_DELAY_PER_TIME_RANGE_REPORT{
    MAX_NO_OF_PLATFORMS	no_of_platforms;
    STRUCT_MEAN_DELAY_PER_TIME_RANGE	struct_mean_delay_per_time_range;//[no_of_stopping_point];
};

struct STRUCT_MEAN_DELAY_PER_TRIP{
    JOURNEY_ID	journey_id;
    TRIP_ID	trip_id;
    DELAY	terminus_arrival_delay;
    DELAY	trip_maximum_delay;
};

struct STRUCT_MEAN_DELAY_PER_TRIP_REPORT{
    MAX_NO_OF_TRIPS	no_of_trips;
    STRUCT_MEAN_DELAY_PER_TRIP	struct_mean_delay_per_trip_left_direction;//[no_of_trips];
    STRUCT_MEAN_DELAY_PER_TRIP	struct_mean_delay_per_trip_right_direction;//[no_of_trips];
};

//struct STRUCT_MESSAGE_HEADER{
//    CSCI_ID	source_csci_id;
//    CSCI_ID	dest_csci_d;
//    MESSAGE_ID	message_id;
//    OWS_ID	ows_id;
//    MESSAGE_LENGTH	message_length;
//    MAX_NO_OF_PACKETS	no_of_packets;
//    PACKET_NUMBER	packet_number;
//};

struct STRUCT_MILEAGE_REPORT{
    MAX_NO_OF_RAKES	no_of_rakes;
    STRUCT_RAKE_TIMETABLE_DETAIL	struct_rake_timetable_detail;//[no_of_rakes];
};

struct STRUCT_ONLINE_STOPPING_POINT_DETAIL
{
    JOURNEY_ID                  journey_id;
    STOPPING_POINT_ID           stopping_point_id;
    INT_8                       trip_id_name[MAX_TRIP_ID_STR_INTERNAL];
    STRUCT_TIME                 actual_arrival_time;
    STRUCT_TIME                 actual_departure_time;
    TRAIN_PERFORMANCE_REGIME	actual_performance_regime;
    STRUCT_TIME                 est_arrival_time;
    STRUCT_TIME                 est_departure_time;
    UINT_16                     est_dwell_time;
    TRAIN_PERFORMANCE_REGIME	est_performance_regime;
};

struct STRUCT_OVERLAPPING_COMMAND
{
    OVERLAP_ID	overlap_id;
    POINT_ID	point_id;
    CBI_ID      cbi_id;
};




struct STRUCT_PD_STATUS
{
    PLATFORM_DOOR_ID	platform_door_id;
    BOOL	is_pd_isolated;
    BOOL	is_pd_bypassed;
};

struct STRUCT_PERFORMANCE_RUNNING_TIME
{
    STATION_ID	from_station_id;
    PLATFORM_ID	from_platform_id;
    STATION_ID	to_station_id;
    PLATFORM_ID	to_platform_id;
    RUNNING_TIME maximum_performance_running_time;
    RUNNING_TIME five_percent_coasting_running_time;
    RUNNING_TIME eight_percent_coasting_running_time;
    RUNNING_TIME energy_saving_running_time;
    RUNNING_TIME full_coasting_running_time;
};

struct STRUCT_PLANNED_TRIP_DETAIL
{
    STOPPING_POINT_ID	stopping_point_id;
    STATION_ID	station_id;
    PLATFORM_ID	platform_id;
    DISTANCE_IN_METER	distance_from_previous_station;
};

struct STRUCT_PLANNED_TRIP_INFO{
    TRIP_NAME	planned_trip_name;
    MAX_NO_OF_STOPPING_POINT_IN_TRIP	no_of_stopping_point_in_trip;
    STRUCT_PLANNED_TRIP_DETAIL	struct_planned_trip_detail;//[no_of_stopping_point_in_trip];
};

struct STRUCT_PLANNED_TRIP_INFO_LIST
{
    MAX_NO_OF_PLANNED_TRIP	no_of_planned_trip;
    STRUCT_PLANNED_TRIP_INFO	struct_planned_trip_info;//[no_of_planned_trip];
};

struct STRUCT_PLATFORM_DWELL_TIME_SET
{
    STATION_ID	stop_station_id;
    PLATFORM_ID	stop_platform_id;
    DWELL_TIME	set_1_dwell_time;
    DWELL_TIME	set_2_dwell_time;
    DWELL_TIME	set_3_dwell_time;
};

struct STRUCT_PLATFORM_PSD_STATUS{
    STATION_ID	station_id;
    PLATFORM_ID	platform_id;
    BOOL	is_dftc;
    BOOL	is_dfto;
    BOOL	is_psdf;
    MAX_NO_OF_PLATFORM_DOORS	no_of_platform_doors;
    STRUCT_PD_STATUS	struct_pd_status;//[no_of_platform_doors];
};

struct STRUCT_PLATFORM_RESPONSE
{
    PLATFORM_ID	platform_id;
    BOOL        platform_hold;
    PSD_STATUS	psd_status;
    int         psd_failure;
};



struct STRUCT_POINT_COMMAND
{
    CBI_ID              cbi_id;
    POINT_ID            point_id;
    POINT_COMMAND_TYPE	point_command_type;
};

struct STRUCT_PSD_STATUS
{
    MAX_NO_OF_PLATFORMS	no_of_platforms;
    STRUCT_PLATFORM_PSD_STATUS	struct_platform_psd_status;
};

struct STRUCT_RAKE_COMMAND_PACKET
{
    RAKE_ID                     rake_id;                             //PC
    TRAIN_ID                    train_id;                             //PC
    VIRTUAL_BLOCK_ID            dest_vb_id;
    VIRTUAL_BLOCK_ID            current_vb_id;
    STATION_ID                  next_station_id;
    STATION_ID                  dest_station_id;
    STATION_ID                  current_station_id;
    //    UINT_8                      ato_dept_command:1;
    //    MAX_SPEED_COMMAND           max_speed_command;
    UINT_8                      coasting_command:1;                              //PC
    UINT_8                      skip_next_stop_command:1;                             //PC
    //    DOOR_DIRECTION              direction_of_opening_door_at_next_station:2;
    //    OPERATING_MODE_COMMAND      operating_mode_command:3;                             //PC
    TRAIN_PERFORMANCE_REGIME	train_performance_regime:2;                             //PC
    //    DWELL_TIME                  dwell_time:10;                                         //PC
    //    UINT_8                      wakeup_command:1;
    //    UINT_8                      sleep_command:1;
    //    UINT_8                      emergency_stop_command:1;
    //    UINT_8                      release_emergency_stop_command:1;
    //    SYSTEM_EXCHANGE_COMMAND     system_exchange_command:2;
    //    UINT_8                      reset_onboard_command:1;
    //    UINT_8                      static_test_command:1;
    //    UINT_8                      dynamic_test_command:1;
    //    UINT_8                      train_remove_command:1;
    //    DOOR_DIRECTION              remote_door_open_command:2;
    //    DOOR_DIRECTION              remote_door_close_command:2;
    //    DOOR_DIRECTION              emergency_train_door_releasing_command:2;
    //    PASSENGER_DISPLAY_MESSAGE   passemger_display_message;
    UINT_8                      energy_saving_mode:1;                             //PC
    //    UINT_8                      automatic_turnback_command:1;
    UINT_8                      train_hold_command:1;                             //PC
    //    UINT_8                      vrs_f_reset_command:1;
    //    UINT_8                      vrs_b_reset_command:1;
    UINT_8                      turnback_or_siding_command:1;                             //PC
    //    PLATFORM_CODE               dest_platform_code:2;                             //PC
    //    PLATFORM_CODE               next_platform_code:2;                             //PC
    //    PLATFORM_CODE               current_platform_code:2;                             //PC
    //    UINT_8                      origin_station_command:1;
    //    UINT_8                      leave_now:1;
    //    OCC_REMOTE_COMMAND_ID       occ_remote_command_id;
    //    UINT_8                      out_of_service_command:1;
    UINT_8                      keep_door_close_command:1;                                    //PC
    //    ADDITIONAL_INFO             additional_info:48;
    //    DEPARTURE_DIRECTION         departure_direction:2;                             //PC
    //    REGULATION_SPEED_COMMAND	regulation_speed:4;

    STRUCT_TIME                 departure_time;      //PC
    STRUCT_TIME                 arrival_time;        //PC
};

struct STRUCT_ATC_RAKE_COMMAND_PACKET
{
    ATC_ID atc_id;
    MAX_NO_OF_RAKES no_of_rakes;
    STRUCT_RAKE_COMMAND_PACKET	rake_cmd[MAX_NUM_OF_RAKES];//[no_of_rakes];
};

struct STRUCT_RAKE_RESPONSE_MAINTENANCE
{
    BOOL is_td_status;
    BOOL is_on_board_status;
    BOOL is_abnormal_seperation;
    BOOL is_command_valid;
    BOOL logic_block_status;
    BOOL if_block_status;
    BOOL relay_status;
    BOOL pwm_status;
    BOOL tg_status;
    BOOL ob_antenna_status;
    BOOL dmi_status;
    BOOL tcms_status;
    ON_BOARD_ERROR_CODE on_board_error_code;
    VRS_REPORT vrs_report;
};

struct STRUCT_RAKE_RESPONSE_PACKET_TEST
{
    RAKE_ID	rake_id;
    VIRTUAL_BLOCK_ID	forward_occupied_block_id;
};
struct STRUCT_ATSS_PC_ATC_PTI_INIT_RESPONSE_PACKET
{
    STRUCT_MESSAGE_HEADER   struct_message_header;
    ATC_ID                  atc_id;
    CBI_ID                  cbi_id;
    PLATFORM_ID             platform_id;
    RAKE_ID                 rake_id;  /// to send TRAIN ID
    UINT_16                 driver_id; /// crew id
    UINT_16                 train_cab_number;
};

//    -track circuit number: number of the track circuit including the Down Link beacon where
//     the track circuit number is defined by its number on the signalling plan.
//    -Train to track message identification: see section 4.2.1-
//    -Train cab number: please refer to 4.1.6-.
//    -Train Identity: please refer to 4.1.6-.
//    -Driver number: please refer to 4.1.6
struct STRUCT_ATC_PTI_PACKET
{
    TRACK_ID  track_id;
    RAKE_ID   rake_id;          ///RAKE ID
    UINT_16   driver_id;        //from simulator hard coded to 2000
    UINT_16   train_cab_number;
    CBI_ID    cbi_id;
    UINT_8    driving_mode;
    UINT_8    is_ready_for_departure;
    UINT_8    consist_id;       //from simulator hard coded to 5
};

struct STRUCT_ATC_PTI_PACKET_INTERNAL
{
    int ack_flag;
    char trk_nm[TRACK_NAME_SIZE];
    STRUCT_ATC_PTI_PACKET pti_pack;
};

struct STRUCT_ATC_PLATFORM_HOLD
{
    PLATFORM_ID platform_id;
    STATION_ID station_id;
    ATC_ID atc_id;
    UINT_8 hold_flag;
};

struct STRUCT_ATC_PLATFORM_HOLD_SKIP_KDC
{
    PLATFORM_ID platform_id;
    UINT_8      atc_platform_id;     // to be filled at PTI
    STATION_ID  station_id;
    ATC_ID      atc_id;
    UINT_8      hold_flag;
    UINT_8      skip_flag;
    UINT_8      KDC_flag;
};
struct STRUCT_ATC_PLATFORM_DOOR_CLOSED
{
    PLATFORM_ID platform_id;
    int door_closed_open_flag;
};

struct STRUCT_ATC_PLATFORM_SKIP_STATION
{
    PLATFORM_ID platform_id;
    STATION_ID station_id;
    ATC_ID atc_id;
    UINT_8 skip_flag;
};
struct STRUCT_TRAIN_HOLD
{
    RAKE_ID rake_id;
    TRACK_ID track_id;
    CBI_ID cbi_id;
};

struct STRUCT_RAKE_RESPONSE_PACKET
{
    RAKE_ID                             rake_id; // time table provided                 801,...
    VIRTUAL_BLOCK_ID                    forward_occupied_block_id;  //cbi id
    VIRTUAL_BLOCK_ID                    rear_occupied_block_id;     //cbi id
    VIRTUAL_BLOCK_ID                    occupied_train_pos_forward; //track_id
    VIRTUAL_BLOCK_ID                    occupied_train_pos_rear;    //track_id
    VRS_ID                              timetable_train_id;       //assigned train id station+ journey 3101, 7901,... (DISPLAY)
    VRS_ID                              atss_train_id;          //ATSS provided 9000,... primary key
    VIRTUAL_BLOCK_OFFSET                forward_occupied_block_offset;
    VIRTUAL_BLOCK_OFFSET                rear_occupied_block_offset;
    VIRTUAL_BLOCK_OFFSET                occupied_train_pos_offset_forward;
    VIRTUAL_BLOCK_OFFSET                occupied_train_pos_offset_rear;
    REMOTE_COMMAND_ACK                  remote_command_ack;
    TRAIN_SPEED                         train_speed;
    TRAIN_SPEED                         train_max_speed;
    EB_REASON                           eb_reason;
    STATIC_TEST_RESULT_ONBOARD          result_of_static_test_onboard;
    STATIC_TEST_RESULT_ROLLING_STOCK    result_of_statis_test_rolling_stock;
    DYNAMIC_TEST_RESULT_ONBOARD         result_of_dynamic_test_onboard;
    BOOL sc_status:1;
    BOOL effectiveness_of_axle_counter:1;
    BOOL train_ready_req:1;
    BOOL ack_of_energy_saving:1;
    BOOL automatic_turnback_ok:1;
    BOOL push_of_depart_button:1;
    BOOL skip_next_stop:1;
    BOOL stop_detection:1;
    BOOL dynamic_testable_section:1;
    BOOL voltage_reduction:1;
    BOOL vrs_b_reset:1;
    BOOL vrs_f_reset:1;
    BOOL passing_throgh_ballise:1;
    BOOL overspeed:1;
    BOOL door_enable:1;
    BOOL eb_release_ack:1;
    TRAIN_DETECTION_MODE        train_detection_mode:2;
    INITIALIZATION_STATUS       initialization_status:2;
    MASTER_SLAVE_ONBOARD        master_standby:2;
    DEPARTURE_DIRECTION         running_direction:2;
    SLEEP_MODE                  sleep_mode:2;
    RESET_RESULT_ON_BOARD       result_reset_on_board:2;
    TRAIN_PERFORMANCE_REGIME    train_performance_regime:2;
    STATE_OF_TRAIN_DOOR         state_of_train_door:2;
    OPERATING_MODE_COMMAND      opeartion_mode:3;
    ATO_DRIVING_STATUS          ato_driving_status:3;
    BOOL sleep_ack:1;
    BOOL rescue_train:1;
    TYPE_OF_VEHICLE             type_of_vehicle:6;
    BOOL wakeup_ack:1;
    BOOL on_board_atc_error_info:1;
    DISTANCE_TO_STOPPING_POINT	distance_to_stopping_point;
    BOOL train_removed:1;
    BOOL plat_hold:1;
    BOOL p0_stopped:1;        //@checkto be filled in setautorouteinline1
    BOOL remote_eb_release:1;
    BOOL condition_of_departure_deterrence:1;
    BOOL dummy_bit:3;
    UINT_8      train_consist_id; //PTI
    STATION_ID  next_station_id;  //TT
    STATION_ID  dest_station_id;  //TT
    CREW_ID     crew_id;          //PTI/TT driver_id
    RADIO_ID    radio_id;         //?
    PLATFORM_ID   platform_id;
};

struct STRUCT_ATC_RAKES_RESPONSE_PACKET
{
    ATC_ID              atc_id;
    UINT_8             no_of_rakes;
    STRUCT_RAKE_RESPONSE_PACKET	struct_rake_response_packet[MAX_NUM_OF_RAKES];//[no_of_rakes];
};
struct STRUCT_ATC_RAKES_RESPONSE_PACKET_LINE_ONE
{
    ATC_ID                      atc_id;
    UINT_8             no_of_rakes;
    STRUCT_RAKE_RESPONSE_PACKET	struct_rake_response_packet[MAX_NUM_OF_RAKES];//[no_of_rakes];
};

struct STRUCT_SYSTEM_ALARM_PRIORITY{
    MAX_NO_OF_ALARMS	no_of_alarms;
    ALARM_PRIORITY	struct_alarm_priority;//[no_of_alarms];
};

struct STRUCT_SYSTEM_CREW_INFO{
    MAX_NO_OF_CREWS	no_of_crews;
    STRUCT_CREW_INFO	struct_crew_details;
};

struct STRUCT_SYSTEM_CREW_INVENTORY{
    MAX_NO_OF_CREWS	no_of_crews;
    STRUCT_CREW_INVENTORY	struct_crew_inventory;//[no_of_crews];
};

//struct STRUCT_SYSTEM_JUNCTION_MODE_INFO{
//    MAX_NO_OF_STATIONS	no_of_stations;
//    STRUCT_JUNCTION_MODE_INFO	struct_junction_management_mode;//[no_of_stations];
//};

struct STRUCT_SYSTEM_LOGGED_USER_INFO{
    MAX_NO_OF_USER_ACCOUNT	no_of_users;
    USER_NAME	username;//[no_of_users];
};

struct STRUCT_SYSTEM_PERFORMANCE_RUNNING_TIME_INFO
{
    MAX_NO_OF_PLATFORMS	no_of_platforms;
    STRUCT_PERFORMANCE_RUNNING_TIME	struct_running_time[MAX_NUM_OF_PLATFORMS_DB];//[no_of_platforms];
};

struct STRUCT_SYSTEM_PLATFORM_DWELL_TIME_SET
{
    MAX_NO_OF_PLATFORMS	no_of_platforms;
    STRUCT_PLATFORM_DWELL_TIME_SET	struct_platform_dwell_time_set[100];//MAX_NUM_OF_PLATFORMS];//[no_of_platforms];
};

struct STRUCT_SYSTEM_REGISTRATION_INFO{
    MAX_NO_OF_TIMETABLE	no_of_registered_timetable;
    STRUCT_REGISTERED_TIMETABLE	struct_registered_timetable;//[no_of_registered_timetable];
};

struct STRUCT_SYSTEM_ROLLING_STOCK_INFO{
    //    MAX_NO_OF_RAKES	no_of_rakes;
    UINT_8 no_of_rakes;
    STRUCT_ROLLING_STOCK_INFO	struct_rolling_stock_info[MAX_NUM_OF_RAKES_INIT];//[no_of_rakes];
};
struct STRUCT_TRAIN_ID_INFO{
    RAKE_ID	rake_id;
    BOOL	is_train_id_exist;
    TRAIN_ID	train_id;
};

struct STRUCT_SYSTEM_TRAIN_ID_INFO
{
    MAX_NO_OF_RAKES	no_of_rakes;
    STRUCT_TRAIN_ID_INFO	struct_train_id_info;//[no_of_rakes];
};
struct STRUCT_USER_AUTHORITY_AREA
{
    //USER_NAME	user_name;
    CBI_ID      cbi_id;
    UINT_8      monitor_flag;
    INT_8       user_name[STRING_USER_NAME];
    UINT_8      ats_flag; //0- no control 1 - CATS 2 -LATS
};
struct STRUCT_SYSTEM_USER_AUTHORITY_AREA
{
    UINT_8	no_of_cbi;
    STRUCT_USER_AUTHORITY_AREA	struct_user_authority_area[MAX_NUM_OF_CBI];
};

struct STRUCT_SYSTEM_USER_INFO{
    MAX_NO_OF_USER_ACCOUNT	no_of_users;
    USER_NAME	username;//[no_of_users];
};

struct STRUCT_SYS_PARAM{
    DEPARTURE_OFFSET            departure_offset;
    ROUTE_TRIGGER_OFFSET	route_trigger_offset;
    DWELL_TIME                  minimum_dwell_time;
    DELAY_DETECTION_THRESHOLD	delay_detection_threshold;
    INTERSTATION_STOP_DETECT_TIME	interstation_stop_detect_time;
    TUNNEL_LIMIT                    tunnel_limit;
    WAKEUP_COMMAND_OFFSET	wakeup_command_offset;
    AVERAGE_SPEED               average_speed;
};

struct STRUCT_TCMS_TRAIN_DESCRIPTION{
    RAKE_ID	rake_id;
    CREW_ID	crew_id;
};

struct STRUCT_TIMETABLE_VALIDITY_RESPONSE{
    UINT_8	no_of_conflicts;
    STRUCT_CONFLICT	struct_conflict[MAX_NUM_OF_CONFLICTS];//[no_of_conflicts];
};

/////////////////////////////////////////////////////////////////////
//to_be_done
///////////////////////////////////////////////////////////////////
struct STRUCT_TRIP_DETAILS_NEW{
    //JOURNEY_ID                        j_id;
    TRIP_ID                             trip_id;                        //1
    MAX_NO_OF_STOPPING_POINT_IN_TRIP	no_of_stopping_point;           //2
    STATION_ID                          station_id;                     //1
    PLATFORM_ID                         platform_id;                    //1
    DISTANCE_IN_METER                   distance_from_previous_station; //2
    STRUCT_TIME                         scheduled_arrival_time;         //3
    STRUCT_TIME                         sched_depart;       //3
    DWELL_TIME                          dwell_time;                     //2
    TRAIN_PERFORMANCE_REGIME            performance_regime;             //1
    SERVICE_TYPE                        service_type;                   //1
    BOOL                                is_crew_linked;                 //1
    CREW_ID                             crew_id;                        //8
    RAKE_ID                             rake_id;                        //2
    BOOL                                is_reconciled;                  //1
    STRUCT_TIME                         actual_arrival_time;            //3
    STRUCT_TIME                         actual_departure_time;          //3
    TRAIN_PERFORMANCE_REGIME            actual_performance_regime;      //1= 36 bytes //ANKIT //to_be_done
};
struct STRUCT_JOURNEY_DETAIL_NEW{
    JOURNEY_ID	journey_id;                                             //2
    MAX_NO_OF_STOPPING_POINT_IN_TRIP	no_of_trips_in_journey;         //2
    STRUCT_TRIP_DETAILS_NEW	struct_trip_detail[MAX_NUM_OF_TRIPS];   //36*100 = 3604 bytes    //ANKIT  //to_be_done
};
struct STRUCT_TIME_TABLE_NEW{
    TIMETABLE_STATE                 timetable_state;                            //1
    MAX_NO_OF_JOURNEY_IN_TIMETABLE  no_of_journy_in_timetable;                  //2
    STRUCT_TIME                     start_time;                                 //3
    STRUCT_JOURNEY_DETAIL_NEW       struct_journey_detail[MAX_NUM_OF_JOURNEYS]; //3604*100
    STRING_50                       time_table_name[NUM_STRING_50];             //50
    STRUCT_DATE                     date;                                       //4 = 3,60,460 bytes   //to_be_done
};

////////////////////////////////////////////////////////////////////////////////
//to_be_done
///////////////////////////////////////////////////////////////////

struct STRUCT_TIME_TABLE
{
    STRING_50                        time_table_name[MAX_TIME_TABLE_NAME_STR];
    STRUCT_DATE                      date;
    STRUCT_TIME                      start_time;
    TIMETABLE_STATE                  timetable_state; //0-COMPLETED 1-CREATED 2-ONLINE LOADED 3-REGISTERED
};
struct STRUCT_TIME_TABLE_INTERNAL
{
    TIMETABLE_STATE                 timetable_state;
    MAX_NO_OF_JOURNEY_IN_TIMETABLE  no_of_journy_in_timetable;
    STRUCT_TIME                     start_time;
    JOURNEY_ID                      j_id[MAX_NUM_OF_JOURNEYS];//[no_of_journies];
    STRING_50                       time_table_name[MAX_NUM_OF_TIMETABLES];
    STRUCT_DATE                     date;
};

struct STRUCT_COMBO_DETAIL{
    JOURNEY_ID                  j_id;
    TRIP_ID                     t_id;//unique combo of j t and stopping point id determines the trains current conditions
    STRUCT_STOPING_POINT_DETAIL stp_details;
};

struct STRUCT_ARS_PACKAGE{
    RAKE_ID             rake_id;
    STRUCT_COMBO_DETAIL all_detail[MAX_NUM_OF_STOPPING_POINTS];//[no_of_stopping points]; //all stopping points ofgiven rake id
};


struct STRUCT_TRACK_COMMAND{
    CBI_ID	cbi_id;
    TRACK_ID	track_id;
    TRACK_COMMAND_TYPE	track_command_type;
};



struct STRUCT_TRAIN_INFORMATION_REPORT{
    JOURNEY_ID	journey_id;
    STRUCT_DATE	journey_date;
    MAX_NO_OF_CREWS	no_of_crews;
    STRUCT_CREW_TIMETABLE_DETAIL	struct_crew_timetable_details;//[no_of_crews];
};

struct STRUCT_TRAIN_INVENTORY{
    RAKE_ID	rake_id;
    TRAIN_SPEED	train_speed;
    TRAIN_ID	train_id;
    VIRTUAL_BLOCK_ID	forward_occupied_block_id;
    VIRTUAL_BLOCK_OFFSET	forward_occupied_block_offset;
    VIRTUAL_BLOCK_ID	rear_occupied_block_id;
    VIRTUAL_BLOCK_OFFSET	rear_occupied_block_offset;
    STATION_ID	last_station_id;
    STATION_ID	next_station_id;
    ROLLING_STOCK_PROFILE	no_of_cars;
    VRS_ID	vrs_id;
    CREW_ID	crew_id;
    SYSTEM_OPERATION_MODE	system_operation_mode;
};

struct STRUCT_TRAIN_PERFORMANCE{
    STATION_ID	station_id;
    PLATFORM_ID	platform_id;
    STRUCT_TIME	actual_arrival_time;
    STRUCT_TIME	actual_departure_time;
    DELAY	arrival_delay;
    DELAY	departure_delay;
};

struct STRUCT_TRAIN_PERFORMANCE_REPORT{
    JOURNEY_ID	journey_id;
    TRIP_ID	trip_id;
    MAX_NO_OF_STOPPING_POINT_IN_TRIP	no_of_stopping_point_in_trip;
    STRUCT_TRAIN_PERFORMANCE	struct_train_performance;//[no_of_stopping_point_in_trip];
};



struct STRUCT_UPDATE_ONLINE_TIME_TABLE{
    MAX_NO_OF_RAKES	no_of_stop_pts;
    STRUCT_ONLINE_STOPPING_POINT_DETAIL	stop_pt_data[MAX_UPDATE_ONLINE_TIMETABLE];//[no_of_updated_stopping_points];
};

/*
struct STRUCT_UPDATE_ROLLING_STOCK_INFO{
    ACTION_ID	action_id;
    RAKE_ID	rake_id;
    BOOL	is_rolling_profile_exist;
    ROLLING_STOCK_PROFILE	rolling_stock_profile;
};
*/
//Amit-15Sep2021
struct	STRUCT_UPDATE_ROLLING_STOCK_INFO{
    RAKE_ID               rake_id;
    ACTION_ID	action_id:2;
    BOOL                  is_rolling_profile_exist:1;
    ROLLING_STOCK_PROFILE rolling_stock_profile:2;
    DUMMY_5_BIT           dummy_5_bit:3;
};

struct STRUCT_TSR
{
    TSR_CODE	tsr_code_up_direction;
    TSR_CODE	tsr_code_down_direction;
    UINT_8	system_request_tsr; //
    UINT_8	tsr_user_profile;   //
    UINT_8	operator_name[8];   //
    UINT_32	safety_checksum_field_1;
    UINT_32	safety_checksum_field_2;
    UINT_32	transaction_no;
    UINT_32	safety_related_time;
    UINT_16	report;
    UINT_32	report_32bit;
    TSR_SETTING	tsr_setting_for_up_direction;
    TSR_SETTING	tsr_setting_for_down_direction;
    WET_DRY_SETTING	wet_dry_setting;
    BOOL	wet_dry;
    BOOL	tsr_presence;
    BOOL	is_tsr_command_ack;
    BOOL	is_tsr_command_feedback;
};

struct STRUCT_VIRTUAL_BLOCKS_RESPONSE_PACKET{
    VIRTUAL_BLOCK_ID	vb_id;
    BOOL	is_tsr_set;
    TSR_CODE	left_tsr_value;
    TSR_CODE	right_tsr_value;
    TSR_DECLINE_REASON	tsr_decline_reason;
    BOOL	is_no_entry_applied;
    NO_ENTRY_DECLINE_REASON	no_entry_decline_reason;
    BOOL	is_wet;
    TSR_SETTING_ANSWER	left_tsr_setting_answer;
    TSR_SETTING_ANSWER	right_tsr_setting_answer;
    WET_DRY_SETTING_ANSWER	wet_dry_setting_answer;
    NO_ENTRY_SETTING_ANSWER	no_entry_setting_answer;
};

struct STRUCT_ATC_VIRTUAL_BLOCK_RESPONSE_PACKET
{
    ATC_ID	atc_id;
    MAX_NO_OF_VIRTUAL_BLOCKS	no_of_vb;
    STRUCT_VIRTUAL_BLOCKS_RESPONSE_PACKET	struct_virtual_block_response_packet;//[no_of_vb];
};

//#ifdef LINE_ONE
//struct STRUCT_VIRTUAL_BLOCK_COMMAND_TYPE
//{
//    VIRTUAL_BLOCK_ID           vb_id;
//    TSR_CODE                   tsr_value;
//    VIRTUAL_BLOCK_COMMAND_TYPE	vb_command_type;
//    UINT_8                     sys_request_tsr;
//    UINT_8                     tsr_user_profile;
//    UINT_8                     op_name[STRING_EIGHT];
//    TSR_COMMAND_TYPE           tsr_cmd_type;

//};
//#endif
//#ifdef LINE_EIGHT
//struct STRUCT_VIRTUAL_BLOCK_COMMAND_TYPE
//{
//    VIRTUAL_BLOCK_ID           vb_id;
//    VIRTUAL_BLOCK_COMMAND_TYPE	vb_command_type;
//    TSR_CODE                   tsr_value;
//};
//#endif

struct STRUCT_NO_ENTRY_PRESET
{
    RAKE_ID     rake_id_1;
    RAKE_ID     rake_id_2;
    NO_ENTRY_PRESET_SETTING     setting;
    DEPARTURE_DIRECTION     train_body_direction_1;
    DEPARTURE_DIRECTION     train_body_direction_2;

};

struct STRUCT_VIRTUAL_BLOCK_COMMAND_PACKET
{
    VIRTUAL_BLOCK_ID	vb_id;
    UINT_8	sector;
    DUMMY_3_BIT	dummy3_bit;
    UINT_8	section;
    DUMMY_3_BIT	dummy_3_bit;
    UINT_8	subsection;
    UINT_8	branch;
    DUMMY_2_BIT	dummy_2_bit;
    UINT_8	abscissa;
    TSR_COMMAND_TYPE	tsr_cmd_type;
    STRUCT_TSR	struct_tsr;
    STRUCT_NO_ENTRY_PRESET	struct_no_entry;
    STRUCT_NO_ENTRY_PRESET	struct_preset;
};

struct STRUCT_VIRTUAL_BLOCK_COMMAND_TYPE
{
    VIRTUAL_BLOCK_ID vb_id;
    TSR_CODE tsr_value;
    VIRTUAL_BLOCK_COMMAND_TYPE vb_command_type;
    UINT_8 system_request_tsr;
    UINT_8 tsr_user_profile;        //Line-1
    UINT_8 operator_name[8];        //Line-1
    TSR_COMMAND_TYPE tsr_cmd_type;  //Line-1
    UINT_8 tsr_length;
    UINT_8 sector;              //Line-1
    DUMMY_3_BIT dummy3_bit3;
    UINT_8 section;             //Line-1
    DUMMY_3_BIT dummy_3_bit3;
    UINT_8 subsection;          //Line-1
    UINT_16 branch;             //Line-1
    DUMMY_2_BIT dummy_2_bit;
    UINT_8 abscissa;            //Line-1
};

struct STRUCT_VIRTUAL_BLOCK_COMMAND
{
    UINT_16 no_of_vb;
    STRUCT_VIRTUAL_BLOCK_COMMAND_TYPE struct_virtual_block_command_type[MAX_NUM_OF_VIRTUAL_BLOCKS];
};

//struct STRUCT_VIRTUAL_BLOCK_COMMAND
//{
//    MAX_NO_OF_VIRTUAL_BLOCKS	no_of_vb;
//    STRUCT_VIRTUAL_BLOCK_COMMAND_TYPE	struct_virtual_block_command_type;//[no_of _vb];
//};

//LINE 8
//struct STRUCT_VIRTUAL_BLOCK_COMMAND_PACKET
//{
//   VIRTUAL_BLOCK_ID	vb_id;
//   BOOL	is_tsr_set;
//   TSR_CODE	tsr_code_up_direction;
//   TSR_CODE	tsr_code_down_direction;
//   TSR_SETTING	tsr_setting_for_up_direction;
//   TSR_SETTING	tsr_setting_for_down_direction;
//   BOOL	wet_dry;
//   WET_DRY_SETTING	wet_dry_setting;
//   NO_ENTRY_SETTING	is_no_entry_applied;
//};

struct STRUCT_ATC_VIRTUAL_BLOCKS_COMMAND_PACKET
{
    ATC_ID	atc_id;
    MAX_NO_OF_VIRTUAL_BLOCKS	no_of_vb;
    STRUCT_VIRTUAL_BLOCK_COMMAND_PACKET	struct_virtual_block_command_packet[MAX_NUM_OF_VIRTUAL_BLOCKS];//[no_of_vb];
};



struct STRUC_USER_INFO
{
    USER_NAME	username;
    PASSWORD	password;
    ACOUNT_TYPE	account_type;
    MAX_NO_OF_CBI_ZONE	no_of_cbi_zones;
    CBI_ID	cbi_id_list;//[no_of_cbi_zones];
    MAX_NO_OF_AUTHORITIES	no_of_authorities;
    AREA_AUTHORITY_TYPE	authorities_list;//[no_of_authorities];
};

/// IDD
struct STRUCT_ATSD_ATSS_CYCLE_COMMAND
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_CYCLE_COMMAND	struct_cycle_command;
};

struct STRUCT_ATSD_ATSS_EMERGENCY_SECTION_COMMAND
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    EMERGENCY_SECTION_ID	emergency_section_id;
    EMERGENCY_SECTION_COMMAND_TYPE	emergency_section_command_type;
};

struct STRUCT_ATSD_ATSS_GLOBAL_COMMAND
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    GLOBAL_COMMAND_TYPE	global_command_type;
};

struct STRUCT_ATSD_ATSS_HEADWAY_MODE_SETTING
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_HEADWAY	struct_headway;
};


struct STRUCT_ATSS_ATSS_HEADWAY_MODE_SETTING
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_HEADWAY	struct_headway;
};

struct STRUCT_ATSD_ATSS_OVERLAP_COMMAND
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_OVERLAPPING_COMMAND	struct_overlap_command;
};

struct STRUCT_ATSD_ATSS_PARTICULAR_CBI_COMMAND
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_CBI_COMMAND	struct_cbi_command;
};

struct STRUCT_ATC_PLATFORM_RESPONSE
{
    PLATFORM_ID	platform_id;
    STATION_ID	station_id;
    PLATFORM_HOLD	platform_hold;
    ERROR_CODE	error_code;
    PSD_STATUS	psd_status;
    DUMMY_4_BIT	dummy_4_bit;
};
struct STRUCT_ATC_PLATFORM_COMMAND_PACKET
{
    ATC_ID atc_id;
    UINT_8 no_of_platforms;
    STRUCT_PLATFORM_COMMAND platform_command[MAX_NUM_OF_PLATFORMS];
};

struct STRUCT_ATSS_PC_PLATFORM_COMMAND
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_ATC_PLATFORM_COMMAND_PACKET	platform_command_type;
};

struct STRUCT_ATSS_PC_TSR_STATUS_MSG
{
    STRUCT_MESSAGE_HEADER	msg_hdr;
    ATC_ID atc_id;
};

struct STRUCT_ATSD_ATSS_PLATFORM_COMMAND
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    PLATFORM_ID	platform_id;
    PLATFORM_COMMAND_TYPE	platform_command_type;
};

struct STRUCT_ATSD_ATSS_POINT_COMMAND
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_POINT_COMMAND	struct_point_command;
};

struct STRUCT_ATSD_ATSS_RAKE_COMMAND
{
    STRUCT_MESSAGE_HEADER struct_message_header;
    RAKE_ID               rake_id;
    RAKE_COMMAND_TYPE     rake_command_type;
};

struct STRUCT_ATSD_ATSS_ROUTE_COMMAND
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_ROUTE_COMMAND	struct_route_command;
};

struct STRUCT_ATSD_ATSS_SAVE_AND_VALIDATE_TIME_TABLE
{
    STRUCT_MESSAGE_HEADER   struct_message_header;
    STRUCT_TIME_TABLE       struct_time_table;
    BOOL                    is_save_and_validate:1; //0-validate 1-save
    UINT_8                  dummy_7:7;
};

struct STRUCT_ATSD_ATSS_SELECTED_TRAIN_INVENTORY
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    RAKE_ID	rake_id;
};

struct STRUCT_ATSD_ATSS_SHELVE_TIMETABLE
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
};

struct STRUCT_ATSD_ATSS_SIGNAL_COMMAND
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_SIGNAL_COMMAND	struct_signal_command;
};

struct STRUCT_ATSD_ATSS_SPK_AUTHORIZATION_COMMAND
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_SPK_COMMAND	struct_spk_command;
};

struct STRUCT_ATSD_ATSS_TRACK_COMMAND
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_TRACK_COMMAND	struct_track_command;
};

struct STRUCT_ATSD_ATSS_TVS_COMMAND
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    TVS_ID	tvs_id;
    BOOL	is_enable;
};

struct STRUCT_ATSD_ATSS_VIRTUAL_BLOCK_COMMAND
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_VIRTUAL_BLOCK_COMMAND	struct_virtual_block_command;
};

struct STRUCT_ATSD_DBA_ALARM_FILTER_REQ
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_ALARM_FILTER	struct_alarm_filter;
};

struct STRUCT_ATSD_DBA_CREATE_RAKE_ID
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    MAX_NO_OF_RAKES	no_of_rakes;
    LINE_NUMBER	line_number;
};

struct STRUCT_ATSD_DBA_DELETE_USER
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    USER_NAME	user_name;
};

struct STRUCT_ATSD_DBA_EVENT_FILTER_REQ
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_EVENT_FILTER	struct_event_filter;
};

struct STRUCT_ATSD_DBA_RELEASE_AUTHORITY_AREA
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_USER_AUTHORITY_AREA	struct_user_authority_area;
};

struct STRUCT_ATSD_DBA_REQ_FOR_TIMETABLE
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_REQ_FOR_TIME_TABLE	struct_req_for_time_table;
};

struct STRUCT_ATSD_DBA_REQ_HEADWAY_MODE_SETTING
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
};

struct STRUCT_ATSD_DBA_REQ_LOGIN
{
    STRUCT_MESSAGE_HEADER	struct_mesage_header;
    STRUCT_CREDENTIAL	struct_credential;
};

struct STRUCT_ATSD_DBA_REQ_LOGOUT
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
};

struct STRUCT_ATSD_DBA_REQ_REPORT
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_REQ_REPORT	struct_req_report;
};

struct STRUCT_ATSD_DBA_REQ_SELECTED_USER_INFO
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    USER_NAME	user_name;
};

struct STRUCT_ATSD_DBA_REQUEST_DATA
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    REQ_TYPE	req_type;
};

struct STRUCT_ATSD_DBA_SAVE_PLANNED_TRIP
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_PLANNED_TRIP_INFO	struct_planned_trip_info;
};

struct STRUCT_ATSD_DBA_SAVE_USER_INFO
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    ACTION_ID	action_id;
    STRUC_USER_INFO	struct_user_info;
};

struct STRUCT_ATSD_DBA_SELECT_AUTHORITY_AREA
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_USER_AUTHORITY_AREA	struct_user_authority_area;
};

struct STRUCT_ATSD_DBA_UPDATE_ALARM_PRIORITY
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_SYSTEM_ALARM_PRIORITY	struct_system_alarm_priority;
};

struct STRUCT_ATSD_DBA_UPDATE_ALARM_STATUS
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    ALARM_ID	alarm_id;
    ALARM_STATUS	alarm_status;
};

struct STRUCT_ATSD_DBA_UPDATE_CREW_INFO
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    ACTION_ID	action_id;
    STRUCT_CREW_INFO	struct_crew_info;
};


struct STRUCT_ATSD_DBA_UPDATE_PERFORMANCE_RUNNING_TIME
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_SYSTEM_PERFORMANCE_RUNNING_TIME_INFO	struct_system_performance_running_time;
};

struct STRUCT_ATSD_DBA_UPDATE_PLATFORM_DWELL_TIME_SET
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_SYSTEM_PLATFORM_DWELL_TIME_SET	struct_system_platform_dwell_time_set;
};

struct STRUCT_ATSD_DBA_UPDATE_ROLLING_STOCK_INFO
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_UPDATE_ROLLING_STOCK_INFO	struct_update_rolling_stock_info;
};

struct STRUCT_ATSD_DBA_UPDATE_SYS_PARAM_INFO
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_SYS_PARAM	struct_sys_param;
};

struct STRUCT_ATSD_DBA_UPDATE_TRAIN_ID_INFO
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_TRAIN_ID_INFO	struct_train_id_info;
};

struct STRUCT_ATSS_ATSD_ACTIVE_SERVER_HEALTH
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_SERVER_HEALTH	struct_server_health;
};

struct STRUCT_ATSS_ATSD_ATC_RAKE_RESPONSE_PACKET_LINE_EIGHT
{
    STRUCT_MESSAGE_HEADER               struct_message_header;
    STRUCT_ATC_RAKES_RESPONSE_PACKET	struct_atc_rake_response_packet;
};

struct STRUCT_ATSS_ATSD_ATC_RAKE_RESPONSE_PACKET_LINE_ONE
{
    STRUCT_MESSAGE_HEADER               struct_message_header;
    STRUCT_ATC_RAKES_RESPONSE_PACKET	struct_atc_rake_response_packet;
};
struct STRUCT_ATSS_ATSD_ATC_STATIONS_RESPONSE
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_ATC_STATION_RESPONSE_PACKET	struct_atc_station_response_packet;
};

struct STRUCT_ATSS_ATSD_ATC_VIRTUAL_BLOCK_RESPONSE_PACKET
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_ATC_VIRTUAL_BLOCK_RESPONSE_PACKET	struct_atc_virtual_block_response_packet;
};

struct STRUCT_ATSS_ATSD_AUTO_ROUTE_SETTING_STATUS
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    CBI_ID	cbi_id;
    BOOL	is_auto_route_setting_allowed;
};

struct STRUCT_ATSS_ATSD_CBI_RESPONSE
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_CBI_RESPONSE	struct_cbi_response;
};

struct STRUCT_ATSS_ATSD_GENERATE_ALARM
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_ALARM	struct_alarm;
};

struct STRUCT_ATSS_ATSD_GENERATE_EVENT
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_EVENT	struct_event;
};

struct STRUCT_ATSS_ATSD_PSD_STATUS
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_PSD_STATUS	struct_psd_status;
};

struct STRUCT_ATSS_ATSD_RESPONSE_STRING
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRING_50	response_string;
};

struct STRUCT_ATSS_ATSD_SPAD_INDICATION
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    SIGNAL_ID	signal_id;
};
struct STRUCT_TRAIN_DESCRIPTION
{
    TRAIN_ID train_id;
    RAKE_ID rake_id;
    TRACK_ID track_id;
    CREW_ID crew_id;
    ONEB_FLAG up_down_flag;
    ACTIVE_CAB_DIRECTION active_cab_direction;  //line_8
    UINT_8 atp_car_no;                          //line_1
    ROLLING_STOCK_PROFILE consist_id;           //line_1
};
struct STRUCT_ATSS_ATSD_TRAIN_DESCRIPTION
{
    STRUCT_MESSAGE_HEADER	msg_hdr;
    STRUCT_TRAIN_DESCRIPTION	train_description;
};

struct STRUCT_ATSS_ATSD_TIME_TABLE_VALIDITY_RESP
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_TIMETABLE_VALIDITY_RESPONSE	struct_timetable_validity_response;
};

struct STRUCT_ATSS_ATSD_TRACTION_ZONE_INDICATION
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    TRACTION_ZONE_ID	traction_zone_id;
    POWER_STATUS	supply_status;
};

struct STRUCT_ATSS_ATSD_TRAIN_INVENTORY
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_TRAIN_INVENTORY	struct__train_inventory;
};

struct STRUCT_ATSS_ATSD_TRAIN_RADIO_STATUS
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    TRAIN_ID                train_id;
    RAKE_ID                 rake_id;
    BOOL	is_pa_pis_link_ok;
    BOOL	is_front_back_link_ok;
    BOOL	is_radio_link_ok;
    BOOL	is_tcms_link_ok;
};

struct STRUCT_ATSS_ATSD_TVS_COMMAND
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    TVS_ID	tvs_id;
    BOOL	is_enable;
};

struct STRUCT_ATSS_ATSD_UPDATE_ONLINE_TIMETABLE
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_UPDATE_ONLINE_TIME_TABLE	update_online_tt;
};

struct STRUCT_ATSS_ATSD_UPDATE_TRAIN_REGULATION_MODE
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    TRAIN_REGULATION_MODE	train_regulation_mode;
};

struct STRUCT_ATSS_ATSS_SERVER_HEALTH
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_SERVER_HEALTH	struct_server_health;
};

//ATSS_DB
struct STRUCT_ATSS_DBA_AUTO_ROUTE_SETTING_STATUS
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    CBI_ID	cbi_id;
    BOOL	is_auto_route_setting_allowed;
};

struct STRUCT_ATSS_DBA_HEADWAY_MODE_SETTING
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_HEADWAY          struct_headway;
};

struct STRUCT_ATSS_DBA_ENABLE_DISABLE_HEADWAY_CYCLE
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_HEADWAY_SETTING      headway_setting;
};

struct STRUCT_ATSS_DBA_ENABLE_DISABLE_ATR
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    UINT_8                  atr_flag;
};

struct STRUCT_ATSS_DBA_LOG_ALARM
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_ALARM            struct_alarm;
};

struct STRUCT_ATSS_DBA_LOG_EVENT
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_EVENT	struct_event;
};

struct STRUCT_ATSS_DBA_SAVE_TIME_TABLE
{
    STRUCT_MESSAGE_HEADER   struct_message_header;
    STRUCT_TIME_TABLE       struct_time_table;
    BOOL                    is_save_and_validate:1;
    UINT_8                  dummy7_bit:7;
};

struct STRUCT_ATSS_DBA_TVS_COMMAND
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    TVS_ID	tvs_id;
    BOOL	is_enable;
};

struct STRUCT_ATSS_DBA_UPDATE_ONLINE_TIMETABLE
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_UPDATE_ONLINE_TIME_TABLE	struct_update_online_timetable;
};

struct STRUCT_ATSS_DBA_UPDATE_TRAIN_REGULATION_MODE
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    TRAIN_REGULATION_MODE	train_regulation_mode;
};



//ATSS_PC
struct STRUCT_PLATFORM_COMMAND_PACKET
{
    int a;
};

struct STRUCT_ATSS_PC_ATC_PLATFORM_COMMAND
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_ATC_PLATFORM_COMMAND_PACKET	platform_command;//[100]
};


struct STRUCT_ATSS_PC_ATC_RAKE_COMMAND_PACKET
{
    STRUCT_MESSAGE_HEADER           struct_message_header;
    STRUCT_ATC_RAKE_COMMAND_PACKET	rake_command;
};

struct STRUCT_ATSS_PC_ATC_STATION_COMMAND_PACKET
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_ATC_STATION_COMMAND_PACKET	struct_atc_station_command_packet;
};

struct STRUCT_ATSS_PC_ATC_VIRTUAL_BLOCK_COMMAND_PACKET
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_ATC_VIRTUAL_BLOCKS_COMMAND_PACKET	struct_atc_virtual_block_command_packet;
};

struct STRUCT_ATSS_PC_CYCLE_COMMAND
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_CYCLE_COMMAND	struct_cycle_command;
};

struct STRUCT_ATSS_PC_OVERLAP_COMMAND
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_OVERLAPPING_COMMAND	struct_overlap_command;
};

struct STRUCT_ATSS_PC_PARTICULAR_CBI_COMMAND
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_CBI_COMMAND	struct_cbi_command;
};

struct STRUCT_ATSS_PC_POINT_COMMAND
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_POINT_COMMAND	struct_point_command;
};

struct STRUCT_ATSS_PC_ROUTE_COMMAND
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_ROUTE_COMMAND	struct_route_command;
};

struct STRUCT_ATSS_PC_SIGNAL_COMMAND
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_SIGNAL_COMMAND	struct_signal_command;
};

struct STRUCT_ATSS_PC_SPK_AUTHORIZATION_COMMAND
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_SPK_COMMAND	struct_spk_command;
};

struct STRUCT_ATSS_PC_TRACK_COMMAND
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_TRACK_COMMAND	struct_track_command;
};

//DBA_ATSS
struct STRUCT_DBA_ATSS_RELEASE_AUTHORITY_AREA
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_USER_AUTHORITY_AREA	struct_user_authority_area;
};

struct STRUCT_DBA_ATSS_SELECT_AUTHORITY_AREA
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_USER_AUTHORITY_AREA	struct_user_authority_area;
};

struct STRUCT_DBA_ATSS_SYSTEM_ALARM_PRIORITY
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_SYSTEM_ALARM_PRIORITY	struct_system_alarm_priority;
};

struct STRUCT_DBA_ATSS_SYSTEM_CREW_INFO
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_SYSTEM_CREW_INFO	struct_system_crew_info;
};


struct STRUCT_DBA_ATSS_SYSTEM_PERFORMANCE_RUNNING_TIME_INFO
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_SYSTEM_PERFORMANCE_RUNNING_TIME_INFO	struct_system_performance_running_time_info;
    //@check REQ_TYPE	req_type;
};

struct STRUCT_DBA_ATSS_SYSTEM_PLATFORM_DWELL_TIME
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_SYSTEM_PLATFORM_DWELL_TIME_SET	struct_system_platform_dwell_time_set;
};

struct STRUCT_DBA_ATSS_SYSTEM_ROLLING_STOCK_INFO
{
    STRUCT_MESSAGE_HEADER               struct_message_header;
    STRUCT_SYSTEM_ROLLING_STOCK_INFO	struct_system_rolling_stock_info;
};

struct STRUCT_DBA_ATSS_SYSTEM_SELECTED_AUTHORITY_AREA
{
    STRUCT_MESSAGE_HEADER               struct_message_header;
    STRUCT_SYSTEM_USER_AUTHORITY_AREA	struct_system_user_authority_area;
};

struct STRUCT_DBA_ATSS_SYSTEM_TRAIN_ID_INFO
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_SYSTEM_TRAIN_ID_INFO	struct_system_train_id_info;
};

struct STRUCT_DBA_ATSS_TIME_TABLE_INFO
{
    STRUCT_MESSAGE_HEADER   struct_message_header;
    STRUCT_TIME_TABLE       struct_time_table;
    BOOL                    is_switch_to_time_table_mode; //TRUE- FALSE- ??
};


struct STRUCT_DBA_ATSS_UPDATE_ALARM_PRIORITY
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_SYSTEM_ALARM_PRIORITY	struct_system_alarm_priority;
};

struct STRUCT_DBA_ATSS_UPDATE_CREW_INFO
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    ACTION_ID	action_id;
    STRUCT_CREW_INFO	struct_crew_info;
};


struct STRUCT_DBA_ATSS_UPDATE_PERFORMANCE_RUNNING_TIME
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_SYSTEM_PERFORMANCE_RUNNING_TIME_INFO	struct_system_performance_running_time;
};

struct STRUCT_DBA_ATSS_UPDATE_PLATFORM_DWELL_TIME_SET
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_SYSTEM_PLATFORM_DWELL_TIME_SET	struct_system_platform_dwell_time_set;
};

struct STRUCT_DBA_ATSS_UPDATE_REGISTRATION_INFO
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_REGISTRATION_INFO	struct_registration_info;
};

struct STRUCT_DBA_ATSS_UPDATE_ROLLING_STOCK_INFO
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_UPDATE_ROLLING_STOCK_INFO	struct_update_rolling_stock_info;
};

struct STRUCT_DBA_ATSS_UPDATE_SYS_INFO
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_SYS_PARAM	struct_sys_param;
};

struct STRUCT_DBA_ATSS_UPDATE_TRAIN_ID_INFO
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_TRAIN_ID_INFO	struct_train_id_info;
};

struct STRUCT_DBA_ATSS_SEND_CBI_CONTROL_LIST
{
    STRUCT_MESSAGE_HEADER   struct_msg_header;
    STRUCT_CBI_CONTROL      struct_cbi_control;
    ATS_FLAG                ats_flag;           // 0- NA 1-CATS 2-LATS
};

//PC_ATSS
struct STRUCT_PC_ATSS_ATC_PTI_PACKET
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_ATC_PTI_PACKET	struct_atc_pti_packet;
};

struct STRUCT_PC_ATSS_ATC_RAKE_RESPONSE_PACKET
{
    STRUCT_MESSAGE_HEADER	            struct_message_header;
    STRUCT_ATC_RAKES_RESPONSE_PACKET	struct_atc_rake_response_packet;
};

struct STRUCT_PC_ATSS_ATC_STATIONS_RESPONSE
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_ATC_STATION_RESPONSE_PACKET	struct_atc_station_response_packet;
};

struct STRUCT_PC_ATSS_ATC_VIRTUAL_BLOCK_RESPONSE_PACKET
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_ATC_VIRTUAL_BLOCK_RESPONSE_PACKET	struct_atc_virtual_block_response_packet;
};

struct STRUCT_PC_ATSS_CBI_RESPONSE
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_CBI_RESPONSE	struct_cbi_response;
};
struct STRUCT_PC_ATSS_CBI_TRACK_ROUTE_POINT_RESPONSE
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    CBI_ID  cbi_id;
    ENTITY_TYPE entity_type;
    ENTITY_ID   entity_id;
    TRACK_ROUTE_POINT_COMMAND_TYPE  entity_command_type;
};

//struct STRUCT_PC_ATSS_CBI_TRACK_ROUTE_POINT_RESPONSE
//{
//   STRUCT_MESSAGE_HEADER	struct_message_header;
//   TRAIN_ID	train_id;
//   RAKE_ID	rake_id;
//   ONEB_FLAG	pa_pis_link;
//   ONEB_FLAG	front_back_link;
//   ONEB_FLAG	radio_link;
//   ONEB_FLAG	tcms_link;
//};


//AMSM_ATSS
struct STRUCT_AMSM_ATSS_CHECKPOINT_REQUEST
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
};
struct STRUCT_AMSM_ATSS_APPLICATION_STATE
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    CSCI_STATE  csci_state;
};
struct STRUCT_AMSM_ATSS_REQUEST_RESTORE
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
};
struct STRUCT_AMSM_ATSS_START_PROCESSING
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
};

//ATSS_AMSM
struct STRUCT_ATSS_AMSM_CHECKPOINT_COMPLETED
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
};
struct STRUCT_ATSS_AMSM_RESTORE_COMPLETED
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
};

struct STRUCT_AMSM_ATSS_START_SYNCH
{
    STRUCT_MESSAGE_HEADER	struct_msg_header;
    INT_8                   ip_address[STRING_TWENTY];
    UINT_16 server_id;
    UINT_16 level;
};

struct STRUCT_ATSS_AMSM_SYNCH_COMPLETED
{
    STRUCT_MESSAGE_HEADER	struct_msg_header;
};
struct STRUCT_ATSS_AMSM_APPLICATION_STATE
{
    STRUCT_MESSAGE_HEADER	struct_msg_header;
    CSCI_STATE csci_state;
};


//TVSIF_ATSS
struct STRUCT_TVSIF_ATSS_CHANNEL_STATUS_PACKET
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    TVS_ID                  tvs_id;
    BOOL                    is_enable;
};


struct STRUCT_PIDS_PAS_ATSS_CHANNEL_STATUS_PACKET
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    TVS_ID                  tvs_id;
    BOOL                    is_enable;
};

struct STRUCT_RSIF_ATSS_CHANNEL_STATUS_PACKET
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    TVS_ID                  tvs_id;
    BOOL                    is_enable;
};

struct STRUCT_TIMECALCSECONDS
{
    UINT_8  hour;
    UINT_8  minute;
    UINT_8  second;
    INT_32 calc_secs;
};

struct STRUCT_CBI_ARS_INTERNAL
{
    CBI_ID cbi_id;
    int ars_flag;
};
struct STRUCT_TRAIN_STATE_INTERNAL
{
    TRAIN_ID train_id;
    ROUTE_ID route_id;
    INT_32 delay_in_sec;
    UINT_32 train_at_platform;
};
struct STRUCT_JOURNEY_NAME_INTERNAL
{
    INT_8 journey_id_name[MAX_JOURNEY_ID_STR_INTERNAL];
};
struct STRUCT_JOURNEY_NUM_INTERNAL
{
    INT_8 journey_id_name;///TO incorporate out of order journey IDs from TimeTable  [MAX_JOURNEY_ID_STR_INTERNAL];
};

struct STRUCT_STOPING_POINT_DETAIL_INTERNAL
{
    UINT_16                 rake_id;
    UINT_8                  journey_id;
    INT_8                   trip_id_name[MAX_TRIP_ID_STR_INTERNAL];
    UINT_8                  station_id;
    PLATFORM_ID             platform_id;
    UINT_8                  pl_tb_type;
    CREW_ID                 crew_id;
    STRUCT_TIMECALCSECONDS  sched_arrival;
    STRUCT_TIMECALCSECONDS  sched_depart;
    UINT_16                 dwell_time;
    UINT_8                  performance_regime;
    UINT_8                  service_type;
    UINT_8                  direction;       //1 - left 2- right
    STRUCT_TIMECALCSECONDS  actual_arrival_time;
    STRUCT_TIMECALCSECONDS  actual_departure_time;
    UINT_8                  actual_performance_regime;
    //    STRUCT_TIMECALCSECONDS  est_arrival_time;
    //    STRUCT_TIMECALCSECONDS  est_departure_time;
};

struct STRUCT_TIME_TABLE_ONLINE
{
    STRUCT_STOPING_POINT_DETAIL_INTERNAL    stop_point_validated;
    TRAIN_ID                                train_id;
    CREW_ID                                 crew_id;
    UINT_16                                 estimated_dwell_time;
    STRUCT_TIMECALCSECONDS                  estimated_arrival_time;
    STRUCT_TIMECALCSECONDS                  estimated_departure_time;
    UINT_8                                  estimated_perf_regime;
    INT_32                                  delay_in_departure;
    UINT_8                                  p0_stopped;
    UINT_8                                  time_set_by_manual;    //0-Not Set , 2-Manual
};

struct STRUCT_HEADWAY_RAKE_PLATFORM_DATA
{
    RAKE_ID                 rake_ID;
    JOURNEY_ID              journey_ID;
    UINT_8                  station_id;
    PLATFORM_ID             platform_id;
    CREW_ID                 crew_id;
    STRUCT_TIMECALCSECONDS  sched_arrival_time;
    STRUCT_TIMECALCSECONDS  sched_departure_time;
    UINT_16                     dwell_time;
    TRAIN_PERFORMANCE_REGIME    performance_regime;
    UINT_8                      direction;
    STRUCT_TIMECALCSECONDS  actual_arrival_time;
    STRUCT_TIMECALCSECONDS  actual_departure_time;

    TRAIN_ID                train_id;
    UINT_16                 estimated_dwell_time;
    STRUCT_TIMECALCSECONDS  estimated_arrival_time;
    STRUCT_TIMECALCSECONDS  estimated_departure_time;

    PLATFORM_ID             dest_plat_ID;
    STATION_ID              dest_station_ID;
    UINT_32                 c_ID;
    STRUCT_TIMECALCSECONDS  delay_arrival;
    STRUCT_TIMECALCSECONDS  delay_depart;
    UINT_8                  p0_stopped;
    STRUCT_TIMECALCSECONDS  calculated_headway;
};

struct STRUCT_POINT_PARENT_DATA
{
    UINT_32     key;
    INT_8       point_Name[POINT_NAME_SIZE];
    POINT_ID    point_id;
    CBI_ID      cbi_id;
    UINT_8      is_Normal;
    UINT_8      is_Reverse;
};

struct STRUCT_POINT_STATUS_MAIN
{
    POINT_ID point_id;
    BOOL	is_normal_point_operation_command_feedback:1;
    BOOL	is_reverse_point_operation_command_feedback:1;
    BOOL	is_point_locked:1;
    BOOL	is_point_normal:1;
    BOOL	is_point_reverse:1;
    BOOL	is_point_block_release_request_command_ack:1;
    BOOL	is_point_block_release_command_feedback:1;
    BOOL	is_point_block_set:1;
    BOOL	is_manual_authorization_release_request_command_ack:1;
    BOOL	is_manual_authorization_release_command_feedback:1;
    BOOL	is_ekt_authorization_set:1;
    BOOL	is_ekt_removed:1;
    BOOL	is_self_normalization_authorise_request_command_ack:1;
    BOOL	is_self_normalization_authorise_command_feedback:1;
    BOOL	is_self_normalization_inhibit_request_command_ack:1;
    BOOL	is_self_normalization_inhibit_command_feedback:1;
    BOOL	is_self_normalization_authorise_status:1;
    BOOL	point_failure_status:1;
    BOOL	is_point_out_of_control:1;
    BOOL	is_ekt_out_of_control:1;
    BOOL	is_emergency_operating_command_ack:1;
    BOOL	is_emergency_operating_command_afeedback:1;
    BOOL	is_point_block_set_request_command_ack:1;
    BOOL	is_point_block_set_request_command_feedback:1;
};

//struct STRUCT_SIGNAL_STATUS_MAIN
//{
//    SIGNAL_ID	signal_id;
//    SIGNAL_TYPE	signal_type:2;
//    BOOL	is_g_aspect:1;
//    BOOL	is_v_aspect:1;
//    BOOL	is_ack_for_block_release_request_command:1;
//    BOOL	is_block_release_command_feedback:1;
//    BOOL	is_signal_block:1;
//    BOOL	is_g_lamp_failure:1;

//    BOOL	is_v_lamp_failure:1;
//    BOOL	is_r_lamp_failure:1;
//    BOOL	is_main:1;
//    BOOL	is_diversion:1;
//    BOOL	is_second_diversion:1;
//    BOOL	is_third_diversion:1;
//    BOOL	is_fourth_diversion:1;
//    BOOL	is_fifth_diversion:1;

//    BOOL	is_route_indicator_lamp_failure:1;      //ANY ROUTE INDICATIOR
//    BOOL	is_proceed_aspect:1;                //shunt signal
//    BOOL	is_proceed_aspect_failure:1;       //shunt signal
//    BOOL	is_stop_aspect_failure:1;       //shunt signal
//    BOOL	is_ack_for_override_release_request_command:1;
//    BOOL	is_override_release_command_feedback:1;
//    BOOL	is_signal_override:1;

//    BOOL	is_signal_out_of_service:1;
//    BOOL	is_signal_regulation_set:1;
//    BOOL	is_ack_for_signal_regulation_release:1;
//    BOOL	is_ack_for_signal_regulation_release_feedback:1;
//    BOOL	is_ack_for_signal_block_request_command:1;
//    BOOL	is_signal_block_request_feedback:1;
//    BOOL    is_shunt_on:1;
//    BOOL    is_shunt_off:1;
//    BOOL	dummy_1_bit:1;
//};
/// VIKAS CHANGES
struct STRUCT_SIGNAL_STATUS_MAIN
{
    SIGNAL_ID	signal_id;
    SIGNAL_TYPE	signal_type:2;
    BOOL	is_g_aspect:1;
    BOOL	is_v_aspect:1;
    BOOL	is_ack_for_block_release_request_command:1;
    BOOL	is_block_release_command_feedback:1;
    BOOL	is_signal_block:1;
    BOOL	is_g_lamp_failure:1;
    BOOL	is_v_lamp_failure:1;
    BOOL	is_r_lamp_failure:1;
    BOOL	is_main:1;
    BOOL	is_diversion:1;
    BOOL	is_second_diversion:1;
    BOOL	is_third_diversion:1;
    BOOL	is_fourth_diversion:1;
    BOOL	is_fifth_diversion:1;
    BOOL	is_route_indicator_lamp_failure:1;      //ANY ROUTE INDICATIOR
    BOOL	is_proceed_aspect:1;                //shunt signal
    BOOL	is_proceed_aspect_failure:1;       //shunt signal
    BOOL	is_stop_aspect_failure:1;       //shunt signal
    BOOL	is_ack_for_override_release_request_command:1;
    BOOL	is_approach_lock_set:1;
    BOOL	is_signal_override:1;
    BOOL is_signal_out_of_service:1;
    BOOL is_signal_regulation_set:1;
    BOOL is_ack_for_signal_regulation_release:1;
    BOOL is_signal_regulation_release_feedback:1;
    BOOL is_ack_for_signal_block_request_command:1;
    BOOL is_signal_block_command_feedback:1;
    BOOL is_shunt_on:1;   //TODO
    BOOL is_shunt_off:1;
    BOOL is_signal_stop:1;




};

struct STRUCT_PLATFORM_STATUS_MAIN{
    PLATFORM_ID	platform_id;
    BOOL is_emergency_stop_plunger_pressed:1;
    BOOL is_all_psd_closed:1;                    //PRESENT IN alaram lIST
    BOOL is_psd_isolated:1;
    BOOL is_esp_out_of_order:1;//PRESENT IN alaram lIST
    DUMMY_4_BIT	dummy_4_bit:4;
};

struct STRUCT_STATION_STATUS_MAIN{
    STATION_ID	station_id;
    POWER_STATUS    npwr:2;
    POWER_STATUS	spwr:2;
    POWER_STATUS	nups:2;
    POWER_STATUS	sups:2;
    POWER_STATUS	pdc:2;
    POWER_STATUS	ssps:2;
    DUMMY_4_BIT     dummy_4_bit:4;
};

struct STRUCT_CBI_POINT_SIGNAL_PLATFORM_STATION_EMERGENCY_RESP
{
    CBI_ID	cbi_id;
    UINT_8	no_of_points;
    UINT_8	no_of_signals;
    UINT_8	no_of_platforms;
    UINT_8	no_of_stations;
    UINT_8	no_of_emergency_sections;
    STRUCT_POINT_STATUS_MAIN	struct_point_status[MAX_NUM_OF_POINTS];
    STRUCT_SIGNAL_STATUS_MAIN	struct_signal_status[MAX_NUM_OF_SIGNALS];
    STRUCT_PLATFORM_STATUS_MAIN	struct_platform_status[MAX_NUM_OF_PLATFORMS];
    STRUCT_STATION_STATUS_MAIN	struct_station_status[MAX_NUM_OF_STATIONS];
    STRUCT_EMERGENCY_SECTION_STATUS	struct_emergency_section_status[MAX_NUM_OF_EMERGENCY_SECTION];
};


struct STRUCT_CBI_TRACK_CYCLE_OVERLAP_RESP
{
    CBI_ID	cbi_id;
    UINT_8	no_of_tracks;
    UINT_8	no_of_overlappings;
    UINT_8	no_of_cycles;

    BOOL is_all_signal_block_release_request_command_ack:1;
    BOOL is_all_signal_block_release_command_feedback:1;
    BOOL is_all_signal_block_status:1;
    BOOL is_vdu_enable:1;
    BOOL is_apb_pressed:1;
    BOOL is_in_ats_mode_control:1;
    BOOL is_all_signal_block_request_command_ack:1;
    BOOL arsd_flag:1; ///auto route set enabled or disabled 0- default; when time table mode off value =0; cutoff always =0 when ARS denied value =1
    //DUMMY_3_BIT dummy_3_bit:1;

    STRUCT_CBI_STATUS           struct_cbi_status;
    STRUCT_SPK_STATUS           struct_spk_status;
    STRUCT_TRACK_STATUS         struct_track_status[MAX_NUM_OF_TRACKS];
    STRUCT_OVERLAPPING_STATUS   struct_overlapping_status[MAX_NUM_OF_OVERLAPPINGS];
    STRUCT_CYCLE_STATUS         struct_cycle_status[MAX_NUM_OF_CYCLES];
};

struct	STRUCT_CBI_ROUTE_RESP
{
    CBI_ID	cbi_id;
    UINT_8	no_of_routes;
    STRUCT_ROUTE_STATUS	struct_route_status[MAX_NUM_OF_ROUTES];
};

struct STRUCT_PC_ATSS_CBI_POINT_SIGNAL_PLATFORM_STATION_EMERGENCY_RESPONSE
{
    STRUCT_MESSAGE_HEADER    message_header;
    STRUCT_CBI_POINT_SIGNAL_PLATFORM_STATION_EMERGENCY_RESP struct_cbi_point_signal_plt_stn_emergency_response;
};

struct  STRUCT_PC_ATSS_CBI_ROUTE_RESPONSE
{
    STRUCT_MESSAGE_HEADER    message_header;
    STRUCT_CBI_ROUTE_RESP    struct_cbi_route_response;
};

struct STRUCT_PC_ATSS_CBI_TRACK_CYCLE_OVERLAP_RESPONSE
{
    STRUCT_MESSAGE_HEADER    message_header;
    STRUCT_CBI_TRACK_CYCLE_OVERLAP_RESP    struct_cbi_track_cycle_ovrlp_station_signal_response;

};

struct STRUCT_TRACK_ROUTE_POINT_RESPONSE
{
    CBI_ID    cbi_id;
    ENTITY_TYPE    entity_type;
    ENTITY_ID    entity_id;
    TRACK_ROUTE_POINT_COMMAND_TYPE    entity_command_type;
};

// ATSS_ATSD
struct STRUCT_ATSS_ATSD_CBI_TRACK_ROUTE_POINT_RESPONSE
{

    STRUCT_MESSAGE_HEADER               message_header;
    CBI_ID                              cbi_id;
    ENTITY_TYPE                         entity_type;
    ENTITY_ID                           entity_id;
    TRACK_ROUTE_POINT_COMMAND_TYPE      entity_command_type;


};

struct STRUCT_ATSS_ATSD_CBI_POINT_SIGNAL_PLATFORM_STATION_EMERGENCY_RESPONSE
{
    STRUCT_MESSAGE_HEADER    message_header;
    STRUCT_CBI_POINT_SIGNAL_PLATFORM_STATION_EMERGENCY_RESP    struct_cbi_point_overlapping_emergency_response;
};

struct STRUCT_ATSS_ATSD_CBI_ROUTE_RESPONSE
{
    STRUCT_MESSAGE_HEADER    message_header;
    STRUCT_CBI_ROUTE_RESP    struct_cbi_route_response;

};

struct STRUCT_ATSS_ATSD_CBI_TRACK_CYCLE_OVERLAP_RESPONSE
{
    STRUCT_MESSAGE_HEADER message_header;
    STRUCT_CBI_TRACK_CYCLE_OVERLAP_RESP trk_cycle_platform_station_signal_response;

};
struct STRUCT_ATSD_ATSS_REQ_FOR_TIMETABLE
{
    STRUCT_MESSAGE_HEADER struct_message_header;
    STRUCT_REQ_FOR_TIME_TABLE struct_req_for_time_table;
};

struct STRUCT_ATSS_DBA_REQ_FOR_TIMETABLE
{
    STRUCT_MESSAGE_HEADER struct_message_header;
    STRUCT_REQ_FOR_TIME_TABLE struct_req_for_time_table;
};

struct STRUCT_PLATFORM_DWELL_TIME_DELAY_SINGLE_RAKE
{
    RAKE_ID rake_id;
    PLATFORM_ID platform_id;
    INT_32  dwell_time_calculated;  /* It must be signed int */
    INT_32 delay_in_sec;
    UINT_32 train_id;
};

struct STRUCT_PLATFORM_DWELL_TIME_DELAY_ALL_RAKES
{
    UINT_8 no_of_rakes;
    STRUCT_PLATFORM_DWELL_TIME_DELAY_SINGLE_RAKE struct_platform_dwell_time_delay[MAX_NUM_OF_RAKES];
};

struct STRUCT_ATSS_ATSD_PLATFORM_DWELL_TIME_DELAY
{
    STRUCT_MESSAGE_HEADER struct_message_header;
    STRUCT_PLATFORM_DWELL_TIME_DELAY_ALL_RAKES struct_platform_dwell_time_delay_all_rakes;
};


struct STRUCT_ATSS_ATSD_FILE_SENT_ACK
{
    STRUCT_MESSAGE_HEADER struct_message_header;
    STRING_50    file_name[MAX_TIME_TABLE_NAME_STR];
    ONEB_FLAG    ack_nack;
};
struct STRUCT_ATSD_ATSS_ASSIGN_RAKE_ID
{
    STRUCT_MESSAGE_HEADER struct_message_header;
    CBI_ID cbi_id;
    TRACK_ID trk_id;
    RAKE_ID rake_id;
};

struct STRUCT_TRACK_OCCUPANCY
{
    INT_8 track_name[STRING_TEN];
    CBI_ID cbi_id;
    TRACK_ID track_id;
    long time_first;
    int stage;
};

struct STRUCT_TRAIN_OCCUPANCY_PACKET
{
    INT_8 track_name[STRING_TEN];
    INT_8 track_next_name[STRING_TEN];
    INT_8 track_next_to_next_name[STRING_TEN];
    CBI_ID cbi_id;
    CBI_ID nxt_cbi;
    CBI_ID nxt_to_nxt_cbi;
    RAKE_ID rake_id;
    TRAIN_ID train_id;
};

struct STRUCT_TRAIN_IDN_PACKET
{
    CBI_ID cbi_id;
    RAKE_ID rake_id;
    TRAIN_ID train_id;
    TRACK_ID track_id;
    TRACK_ID next_track_id;
    TRACK_ID next_to_next_track_id;
    int counter;
    long time_passed;
};

struct STRUCT_HEADWAY_ATR
{
    PLATFORM_ID             platform_ID;
    RAKE_ID                 rake_ID;
    STRUCT_TIMECALCSECONDS  arr_time;
    STRUCT_TIMECALCSECONDS  dept_time;
};

struct STRUCT_OCCUPIED_TRACK
{
    //frequent updation
    INT_8       track_name[STRING_TEN];
    CBI_ID      cbi_id;
    TRACK_ID    track_id;

    //static
    TRAIN_ID    train_id;             //assigned ID/TimeTable ID
    RAKE_ID     rake_id;
    TRAIN_ID    atss_train_id;        //local ID
    UINT_8      consist_id;
    CREW_ID     crew_id;
    RADIO_ID    radio_id;
    TRAIN_CAB   train_cab_number;
    UINT_8      driving_mode;
    UINT_8      is_ready_dept;
    UINT_8      trk_dir;

    //frequent updation
    UINT_8      head;
    UINT_32     time_first;
    PLATFORM_ID platform_ID;
    STATION_ID  next_station;
    STATION_ID  dest_station;
    //UINT_8      t_hold;
    UINT_8      skip_stop;          //Used for sending extra departure msg as per new philosophy - Amit 14Feb2022
    UINT_8      kdc;                //Used for sending extra departure msg as per new philosophy - Amit 14Feb2022
    UINT_8      change_end_request; // whether to check for change req or not

    UINT_16     dwell_time;
    UINT_8      p0_stoppped;
    INT_32     time_p0_stopped;
    UINT_8      interstation_stop;
    INT_32      delay_in_arrival;

    UINT_8      send_auto_pti_flag;
    UINT_8      send_atc_arr_dep_msg;   //Added by Amit-14Feb2022, to stop sending repetitive Arr,Dep in Cut Off mode
};

struct STRUCT_SEND_RAKE_COMMAND_PACKET
{
    RAKE_ID rake_id;
    TRAIN_ID train_id;
    ATC_ID atc_id;
};

struct STRUCT_PLATFORM_STATION_DATA
{
    CBI_ID      cbi_id;
    PLATFORM_ID platform_id;
    STATION_ID  station_id;
    PLATFORM_ID upline_platform;
    PLATFORM_ID downline_platform;
    TRACK_ID    upline_track_id;
    TRACK_ID    downline_track_id;
};

struct STRUCT_PTI_INITIALIZATION_PACKET
{
    int station_id;
    int rake_id;
    int train_id;
    int driver_num;
    int counter;
};

struct STRUCT_ATSS_PC_ATC_PTI_INITIALIZATION_PACKET
{
    STRUCT_MESSAGE_HEADER struct_message_header;
    STRUCT_ATC_PTI_PACKET struct_pti_init;
};



struct STRUCT_ATSS_PC_TRAIN_DESCRIPTION
{
    STRUCT_MESSAGE_HEADER   struct_message_header;
    UINT_8                  location_status_traffic_direction_TD;   //Train Direction 0=RIGHT, 1=LEFT,
    UINT_8                  train_entering_in_occ_TEN;
    UINT_8                  train_exit_in_occ_TEX;
    TRACK_ID                track_id;
    CBI_ID                  cbi_id;
    TRAIN_CAB               train_cab_number;
    TRAIN_ID                train_id;
    CREW_ID                 crew_id;
    RAKE_ID                 rake_id;
    CONSIST_ID              consist_id;
};


struct STRUCT_RADIO_DESCRIPTION
{
    TRAIN_ID    train_id;
    RAKE_ID     rake_id;
    RADIO_ID    radio_id;
    TRACK_ID    track_id;
    CREW_ID     crew_id;
    ONEB_FLAG   up_down_flag;
    UINT_8      atp_car_no;
    CONSIST_ID  consist_id;
};

struct STRUCT_PC_ATSS_RADIO_DESCRIPTION
{
    STRUCT_MESSAGE_HEADER msg_hdr;
    TRAIN_ID train_id;
    RAKE_ID rake_id;
    RADIO_ID radio_id;
    //STRUCT_RADIO_DESCRIPTION struct_radio_description;

};

struct STRUCT_ARRIVAL
{
    STATION_ID              station_id;
    STATION_ID              dest_station_id;
    PLATFORM_ID             platform_id;
    ROLLING_STOCK_PROFILE   rolling_stock_profile;
    STRUCT_TIME             time;
    UINT_8                  arrival_situation;
    DWELL_TIME              dwell_time;
    PERCENTAGE              dm1_load; //line_8
    PERCENTAGE              t1_load; //line_8
    PERCENTAGE              m1_load; //line_8
    PERCENTAGE              m2_load; //line_8
    PERCENTAGE              t2_load; //line_8
    PERCENTAGE              dm2_load;; //line_8
};

struct STRUCT_ATSS_PC_ARRIVAL_PLATFORM
{
    STRUCT_MESSAGE_HEADER struct_message_header;
    STRUCT_ARRIVAL struct_arrival;
};

struct STRUCT_STOPPING_SCHEDULE
{
    UINT_8 station_id;
    UINT_8 is_stop;
};

struct STRUCT_DEPARTURE
{
    STATION_ID                station_id;
    STATION_ID                dest_station_id;
    PLATFORM_ID               platform_id;
    ROLLING_STOCK_PROFILE     rolling_stock_profile;
    STRUCT_TIME               time;
    //UINT_8                    no_of_stations_in_stopping_shedule;
    //STRUCT_STOPPING_SCHEDULE  struct_stopping_shedule[MAX_NUM_OF_STATIONS];

};
struct STRUCT_ATSS_PC_DEPARTURE_PLATFORM
{
    STRUCT_MESSAGE_HEADER struct_message_header;
    STRUCT_DEPARTURE      struct_departure;

};

//13AUg2021
struct STRUCT_DEPARTURE_DISPLAY
{
    STATION_ID                station_id;
    STATION_ID                dest_station_id;
    PLATFORM_ID               platform_id;
    ROLLING_STOCK_PROFILE     rolling_stock_profile;
    STRUCT_TIME               time;
    TRAIN_ID                  train_id;
    //UINT_8                    no_of_stations_in_stopping_shedule;
    //STRUCT_STOPPING_SCHEDULE  struct_stopping_shedule[MAX_NUM_OF_STATIONS];

};

//13AUg2021
struct STRUCT_ATSS_PC_DEPARTURE_PLATFORM_DISPLAY
{
    STRUCT_MESSAGE_HEADER       struct_message_header;
    STRUCT_DEPARTURE_DISPLAY    struct_departure;
};


//13AUg2021
struct STRUCT_ARRIVAL_DISPLAY
{
    STATION_ID              station_id;
    STATION_ID              dest_station_id;
    PLATFORM_ID             platform_id;
    ROLLING_STOCK_PROFILE   rolling_stock_profile;
    STRUCT_TIME             time;
    UINT_8                  arrival_situation;
    DWELL_TIME              dwell_time;
    PERCENTAGE              dm1_load; //line_8
    PERCENTAGE              t1_load; //line_8
    PERCENTAGE              m1_load; //line_8
    PERCENTAGE              m2_load; //line_8
    PERCENTAGE              t2_load; //line_8
    PERCENTAGE              dm2_load;; //line_8

    TRAIN_ID    train_id;
};

//13AUg2021
struct STRUCT_ATSS_PC_ARRIVAL_PLATFORM_DISPLAY
{
    STRUCT_MESSAGE_HEADER struct_message_header;
    STRUCT_ARRIVAL_DISPLAY struct_arrival;
};
struct STRUCT_NEXT_PLATFORM
{
    STATION_ID                  dest_station_id;
    PLATFORM_ID                 platform_id;
    ROLLING_STOCK_PROFILE       rolling_stock_profile;
    STRUCT_TIME                 time;
};
struct STRUCT_NEXT_PLATFORM_DISPLAY
{
    STATION_ID                  dest_station_id;
    PLATFORM_ID                 platform_id;
    ROLLING_STOCK_PROFILE       rolling_stock_profile;
    STRUCT_TIME                 time;
    TRAIN_ID                    train_id;
};
struct STRUCT_NEXT_THREE_DEPARTURE
{
    STATION_ID              station_id;
    UINT_8                  no_of_next_platforms;
    STRUCT_NEXT_PLATFORM    struct_next_platform[3];

};
//13AUg2021
struct STRUCT_NEXT_THREE_DEPARTURE_DISPLAY
{
    STATION_ID                      station_id;
    UINT_8                          no_of_next_platforms;
    STRUCT_NEXT_PLATFORM_DISPLAY    struct_next_platform[3];

};

struct STRUCT_ATSS_PC_NEXT_THREE_DEPARTURES
{
    STRUCT_MESSAGE_HEADER       struct_message_header;
    UINT_8                      pidspasId;
    STRUCT_NEXT_THREE_DEPARTURE struct_next_three_departure;
};
//13AUg2021
struct STRUCT_ATSS_ATSD_NEXT_THREE_DEPARTURES
{
    STRUCT_MESSAGE_HEADER       struct_message_header;// msg_id =179
    UINT_8                      pidspasId;
    //UINT_8                      num_of_stations;
    STRUCT_NEXT_THREE_DEPARTURE_DISPLAY struct_next_three_departure;//[MAX_NUM_OF_PIDS_PAS_STATIONS];
};



struct STRUCT_TRAIN_ALARM
{
    ROLLING_STOCK_PROFILE    unit_coupling_code;
    UINT_8    tims_cpu2_lu_online_status;
    UINT_8    becu_fault_major_event;
    UINT_8    becu_fault_becu_shutdown;
    UINT_8    ac_fault_fr;
    UINT_8    smoke_detected;
    UINT_8    door_fault_fail_to_open_close;
    UINT_8    door_fault_obstacle_circuit_fault;
    UINT_8    air_suspension_fault;
    UINT_8    train_level_fault_in_unit_1;
    UINT_8    train_level_fault_in_unit_4;
    BOOL    tims_rake_id_valid:1;
    BOOL    formation_valid:1;
    DUMMY_6_BIT    dummy_6_bit:6;
    UINT_8    ci1_vvvf1_fault_cifr1_ifr1:4;
    UINT_8    ci2_vvvf2_fault_cifr2_ifr2:4;
    UINT_8    ci1_fault_isocd2:4;
    UINT_8   ci2_fault_isocd2:4;
    UINT_8    ci1_vvvf1_fault_gr:4;
    UINT_8    ci2_vvvf2_fault_gr:4;
    UINT_8    siv_fault_sivfr:4;
    UINT_8    siv_fault_acocd:4;
    UINT_8    siv_fault_acolvd:4;
    UINT_8    siv_fault_stf:4;
    UINT_8    vcb_hb_on_status:4;
    UINT_8    mtr_fault_acocr:4;
    UINT_8    mtr_fault_mtth:4;
    UINT_8    mtr_fault_mtoftr:4;
    UINT_8    atc_active:4;
    UINT_8    train_radio_transmission_error_with_tims:4;
    UINT_8    safety_switches_in_unit_1:4;
    UINT_8    safety_switches_in_unit_2:4;

};

struct STRUCT_PC_ATSS_TRAIN_ALARM_MSG
{
    STRUCT_MESSAGE_HEADER     struct_message_header;
    STRUCT_TRAIN_ALARM     struct_train_alarm;

};

struct STRUCT_ATSS_ATSD_TRAIN_ALARM_MSG
{
    STRUCT_MESSAGE_HEADER struct_message_header;
    STRUCT_TRAIN_ALARM struct_train_alarm;
};

struct STRUCT_TIME_SECONDS
{
    RAKE_ID                     rake_id;
    INT_8                       trip_id_name[MAX_TRIP_ID_STR_INTERNAL];
    PLATFORM_ID                 platform_id;
    STATION_ID                  station_id;
    PLATFORM_ID                 dest_platform_id;
    STATION_ID                  dest_station_id;
    STRUCT_TIMECALCSECONDS      struct_time;  //@info added after discussion Rupesh sir and DMRC    // 01-04-2021
    STRUCT_TIMECALCSECONDS      struct_actual_time;
    STRUCT_TIMECALCSECONDS      struct_atr_time;
    UINT_16                     dwell_time;
    UINT_8                      time_actual_flag;
    TRAIN_PERFORMANCE_REGIME    performance_regime;
    ROLLING_STOCK_PROFILE       rolling_stock_profile;
    UINT_8                      arrival_situation;
    TRAIN_ID                    train_id;
};

struct STRUCT_PLATFORM_TIME_SECONDS
{
    std::multimap<UINT_32,STRUCT_TIME_SECONDS>  sched_arrival;
    std::multimap<UINT_32,STRUCT_TIME_SECONDS>  sched_departure;
};

struct STRUCT_NEXT_THREE_ARR_DEPARTURES
{
    STATION_ID station_id;
    std::multimap<UINT_32,STRUCT_TIME_SECONDS>  sched_arrival;
    std::multimap<UINT_32,STRUCT_TIME_SECONDS>  sched_departure;
};


struct STRUCT_HEADWAY_TIME_SECONDS
{
    RAKE_ID                     rake_id;
    PLATFORM_ID                 platform_id;
    STATION_ID                  station_id;
    PLATFORM_ID                 dest_platform_id;
    STATION_ID                  dest_station_id;
    STRUCT_TIMECALCSECONDS      struct_time;
    STRUCT_TIMECALCSECONDS      struct_actual_time;
    UINT_16                     dwell_time;
    TRAIN_PERFORMANCE_REGIME    performance_regime;
    ROLLING_STOCK_PROFILE       rolling_stock_profile;
    UINT_8                      arrival_situation;
    TRAIN_ID                    train_id;
};

struct STRUCT_HEADWAY_NEXT_THREE_ARR_DEPARTURES
{
    UINT_32     sequence_num;
    STATION_ID  station_id;
    std::multimap<UINT_32,STRUCT_HEADWAY_TIME_SECONDS>  sched_arrival;
    std::multimap<UINT_32,STRUCT_HEADWAY_TIME_SECONDS>  sched_departure;
};

struct STRUCT_PLATFORM_LIST_HEADWAY
{
    TRACK_ID    trk_ID;
    CBI_ID      cbi_id;
    PLATFORM_ID platform_id;
    STATION_ID  station_id;
    PLATFORM_ID dest_platform;
    STATION_ID  dest_station;
    DWELL_TIME  dwell_time;
    UINT_8 start_cycle_front_crossover;
    UINT_8 end_cycle_front_crossover;

    INT_8       name[STATION_NAME_SIZE];
    ATC_ID      atc_id;
    int         nxt_stn_dist;
    HEADWAY     headway;
};
struct STRUCT_RAKE_JOURNEY_CYCLE
{
    RAKE_ID     rake_ID;
    JOURNEY_ID  journey_ID;
    UINT_32     cycle_key;
    TRAIN_ID    train_ID;
};

struct STRUCT_RAKE_JOURNEY_CYCLE_TEMP
{
    STRUCT_RAKE_JOURNEY_CYCLE cycle[MAX_NUM_OF_ACTIVE_CYCLES];
};

struct STRUCT_ALL_CYCLES
{
    CYCLE_KEY cycle[MAX_NUM_OF_ACTIVE_CYCLES];
};


struct STRUCT_TRACK_PLATFORM_CYCLE_MAP
{
    TRACK_ID    trk_ID;
    CBI_ID      cbi_ID;
    PLATFORM_ID p_ID;
    STATION_ID  s_ID;
    PLATFORM_ID dest_platform;
    STATION_ID  dest_station;
    DWELL_TIME  dwell_time;

    RAKE_ID     rake_ID;
    UINT_32     c_ID;       //start_cycle_key + end_cycle_key
    UINT_8      trk_dir;
};
struct STRUCT_ATSS_PC_CLOCK_SYNCH_MESSAGE
{

    _STRUCT_MESSAGE_HEADER struct_msg_header;
    UINT_8 atc_id;
    STRUCT_DATE date;
    STRUCT_TIME time;
};
struct STRUCT_PC_ATSS_CLOCK_SYNCH_MESSAGE
{
    _STRUCT_MESSAGE_HEADER struct_msg_header;
    UINT_8 atc_id;
};

struct STRUCT_TSR_COMMAND
{
    UINT_8 atc_id;
    UINT_8 tsr_user_profile;//CATS/LATS
    UINT_8 operator_name[8]; //UserName
    TSR_COMMAND_TYPE  tsr_cmd_type;  //Apply/release
    UINT_8 tsr_length;
    UINT_8 tsr_speed;
    UINT_8 abscissa;
    UINT_8 sector;
    UINT_8 section;
    UINT_8 sub_section;
    UINT_8 branch;
};

struct STRUCT_PC_ATSS_TSR_SAFETY_COMMAND
{
    UINT_8 atc_id;
    UINT_32 safety_related_time;
};

struct STRUCT_TSR_COMMAND_CONFIRMATION_ACK
{
    STRUCT_TSR_COMMAND command;
    UINT_32 safety_related_time;
};

struct STRUCT_TSR_STATUS_DETAILS
{
    UINT_8 tsr_length;
    UINT_8 tsr_speed;
    UINT_8 abscissa;
    UINT_8 sector;
    UINT_8 section;
    UINT_8 sub_section;
    UINT_8 branch;
    UINT_16 report;
};
struct STRUCT_TSR_STATUS_INFO
{
    RESPONSE_COMMAND_TYPE command_type;
    //UINT_8 no_of_tsr;
    STRUCT_TSR_STATUS_DETAILS struct_tsr_status_details;//[MAX_NUM_OF_TSR];
};

struct STRUCT_TSR_STATUS_INIT
{
    UINT_8 no_of_tsr;
    STRUCT_TSR_STATUS_DETAILS struct_tsr_status_details[MAX_NUM_OF_TSR_INIT];
};

struct STRUCT_TSR_COMMAND_CONFIRMATION
{
    STRUCT_TSR_COMMAND command;
    UINT_32 safety_related_CheckSum1; //0
    UINT_32 safety_related_CheckSum2; //0
    UINT_32 safety_related_time;
};

struct ATSD_ATSS_TSR_REQUEST_COMMAND
{
    STRUCT_MESSAGE_HEADER message_header;
    STRUCT_TSR_COMMAND tsr_commmand;
};
struct ATSS_PC_TSR_REQUEST_COMMAND
{
    STRUCT_MESSAGE_HEADER message_header;
    STRUCT_TSR_COMMAND tsr_commmand;
};
struct STRUCT_PC_ATSS_TSR_COMMAND_CONFIRMATION_ACK
{
    STRUCT_MESSAGE_HEADER message_header;
    STRUCT_PC_ATSS_TSR_SAFETY_COMMAND tsr_command_confirmation;
};
struct STRUCT_ATSS_ATSD_TSR_COMMAND_CONFIRMATION_ACK
{
    STRUCT_MESSAGE_HEADER message_header;
    STRUCT_TSR_COMMAND_CONFIRMATION_ACK tsr_command_confirmation;
};
struct STRUCT_ATSD_ATSS_TSR_COMMAND_CONFIRMATION
{
    STRUCT_MESSAGE_HEADER message_header;
    STRUCT_TSR_COMMAND_CONFIRMATION tsr_commmand;
};
struct STRUCT_ATSS_PC_TSR_COMMAND_CONFIRMATION
{
    STRUCT_MESSAGE_HEADER message_header;
    STRUCT_TSR_COMMAND_CONFIRMATION tsr_commmand;
};

struct STRUCT_PC_ATSS_TSR_LOGGING_MESSAGE
{
    STRUCT_MESSAGE_HEADER message_header;
    ATC_ID atc_id;
    STRUCT_TSR_STATUS_DETAILS tsr_details;
    UINT_16 report; //0- 1- 2- 3-
};

struct STRUCT_ATSS_ATSD_TSR_STATUS_INFO
{
    STRUCT_MESSAGE_HEADER message_header;
    STRUCT_TSR_STATUS_INFO tsr_details;
};

struct STRUCT_ATSS_DBA_TSR_STATUS_INFO
{
    STRUCT_MESSAGE_HEADER message_header;
    STRUCT_TSR_STATUS_INFO tsr_details;
};

struct STRUCT_DBA_ATSS_TSR_STATUS_INFO
{
    STRUCT_MESSAGE_HEADER struct_message_header;
    STRUCT_TSR_STATUS_INIT struct_tsr_status_init;
};

struct STRUCT_PC_ATSS_TSR_REPORT_OF_OPERATION
{
    STRUCT_MESSAGE_HEADER struct_message_header;
    ATC_ID atc_id;
    STRUCT_TSR_STATUS_DETAILS tsr_status_details;
    //UINT_16 report;
};


struct STRUCT_SAFETY_COMMAND_COUNTER
{
    SAFETY_COMMAND_TYPE safety_command_type;
    UINT_32 execution_count;
};

struct STRUCT_SAFETY_COMMAND
{
    UINT_8 no_of_safety_command;
    STRUCT_SAFETY_COMMAND_COUNTER safety_command_counter[MAX_NUM_OF_SAFETY_COMMAND];
};

struct STRUCT_ATSS_DBA_SAFETY_COMMAND_COUNTER
{
    STRUCT_MESSAGE_HEADER struct_msg_hdr;
    STRUCT_SAFETY_COMMAND safety_cmd_counter;
};

struct STRUCT_ATSS_ATSD_SAFETY_COMMAND_COUNTER
{
    STRUCT_MESSAGE_HEADER struct_msg_hdr;
    STRUCT_SAFETY_COMMAND safety_cmd_counter;
};

struct STRUCT_DBA_ATSS_SAFETY_COMMAND_COUNTER
{
    STRUCT_MESSAGE_HEADER struct_msg_hdr;
    STRUCT_SAFETY_COMMAND safety_cmd_counter;
};

struct STRUCT_EQUIPMENT_STATUS
{
    UINT_32 computing_channel:3;
    UINT_32 channel_a_fan:2;
    UINT_32 channel_a_psu:2;
    UINT_32 channel_a_id_device:2;
    UINT_32 channel_b_fan:2;
    UINT_32 channel_b_psu:2;
    UINT_32 channel_b_id_device:2;
    UINT_32 channel_c_fan:2;
    UINT_32 channel_c_psu:2;
    UINT_32 channel_c_id_device:2;
    UINT_32 io_psu_a:2;
    UINT_32 io_psu_b:2;
    UINT_32 psu_main:2;
    DUMMY_5_BIT dummmy:5;

};

struct STRUCT_PC_ATSS_EQUIPMENT_STATUS
{
    STRUCT_MESSAGE_HEADER msg_hdr;
    STRUCT_EQUIPMENT_STATUS equipment_status;
};
struct STRUCT_ATSS_ATSD_EQUIPMENT_STATUS
{
    STRUCT_MESSAGE_HEADER msg_hdr;
    STRUCT_EQUIPMENT_STATUS equipment_status;
};

struct STRUCT_PIDS_PAS_HEALTH
{
    PIDS_PAS_ID pids_pas_ID;
    SERVER_HEALTH_STATUS health_status;
};
struct STRUCT_RADIO_SERVER_HEALTH
{
    RADIO_SERVER_ID radio_server_ID;
    SERVER_HEALTH_STATUS health_status;
};

struct STRUCT_EXTERNAL_SYSTEM_HEALTH
{
    UINT_8 num_pids_pas;
    UINT_8 num_radio_server;
    SERVER_HEALTH_STATUS master_clock_status;
    STRUCT_PIDS_PAS_HEALTH pids_pas_health[MAX_NUM_OF_PIDS_PAS];
    STRUCT_RADIO_SERVER_HEALTH radio_server_health[MAX_NUM_OF_RADIO_SERVER];
};
struct STRUCT_ATSS_ATSD_EXTERNAL_SYSTEM_HEALTH
{
    STRUCT_MESSAGE_HEADER msg_hdr;
    STRUCT_EXTERNAL_SYSTEM_HEALTH equipment_status;
};

struct STRUCT_ATSS_ATSD_CBI_STATUS
{
    STRUCT_MESSAGE_HEADER msg_hdr;
    CBI_ID cbi_id;
    CBI_UNIT_STATUS normal_unit_status;
    CBI_UNIT_STATUS reserve_unit_status;
    CBI_CHANGEOVER_STATUS change_over_status;
};

struct STRUCT_ATSS_PC_CLEAR_CHANGE_OVER_STATUS
{
    STRUCT_MESSAGE_HEADER msg_hdr;
    CBI_ID cbi_ID;
};

struct STRUCT_EQUIPMENT_STATUS_REQUEST
{
    STRUCT_MESSAGE_HEADER msg_hdr;
    ATC_ID atc_ID;
};


struct STRUCT_ATSS_ATSD_PIDS_PAS_CLEAR
{
    STRUCT_MESSAGE_HEADER msg_hdr;
    STATION_ID station_ID;
    PLATFORM_ID platform_ID;
};


struct STRUCT_PL_TB_CAPACITY
{
    PLATFORM_ID platform;
    JOURNEY_ID journey;
    UINT_8 capacity_entry;
};

struct STRUCT_ROUTE_SET_THREAD_TEMP
{
    TRACK_ID current_track_id;
    CBI_ID cbi_id;
    RAKE_ID curr_rake;
    char prev_track_name[100];
    char track_name[100];
    int trk_direction;
};

struct STRUCT_ATSS_ATSS_ADD_REMOVE_TRAIN_OCCUPANCY
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    UINT_8 add_delete_flag;
    STRUCT_OCCUPIED_TRACK struct_occupied_track;
};

struct STRUCT_JUNCTION_DATA
{
    CBI_ID junction_management_cbi;
    TRACK_ID junction_trk_id;
    CBI_ID junction_trk_cbi_id;
    TRACK_ID trig_trk_id;
    CBI_ID trig_cbi_id;
    ROUTE_ID route_id;
    CBI_ID route_cbi_id;
};

struct STRUCT_JUNCTION_MANAGEMENT_QUEUE
{
    UINT_32 key;
    ROUTE_ID route_id;
    CBI_ID route_cbi_id;
    RAKE_ID rake;
    INT_32 delay;
    UINT_8 priority;
};

struct STRUCT_CONFLICTING_ROUTE_DATA
{
    UINT_8      route1_name[ROUTE_NAME_SIZE];
    ROUTE_ID    route1_id;
    CBI_ID      route1_cbi_id;
    UINT_8      route2_name[ROUTE_NAME_SIZE];
    ROUTE_ID    route2_id;
    CBI_ID      route2_cbi_id;
};

struct STRUCT_JUNCTION_MODE_INFO
{
    STATION_ID station_id;
    JUNCTION_MANAGEMENT_MODE junction_mode;
};

struct STRUCT_SYSTEM_JUNCTION_MODE_INFO
{
    UINT_8 no_of_stations; //changed from UINT_16 to UINT_8: As per ATSD requirement: Dated: July 28, 2021
    STRUCT_JUNCTION_MODE_INFO junction_data[MAX_NUM_OF_STATIONS];
};

struct STRUCT_ATSD_DBA_UPDATE_JUNCTION_MODE_INFO
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_JUNCTION_MODE_INFO	struct_junction_mode_info;
};
struct STRUCT_DBA_ATSD_SYSTEM_JUNCTION_MODE_INFO {
    STRUCT_MESSAGE_HEADER msg_header;
    STRUCT_SYSTEM_JUNCTION_MODE_INFO struct_system_junction_mode_info;
};
struct STRUCT_DBA_ATSS_SYSTEM_JUNCTION_MODE_INFO
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_SYSTEM_JUNCTION_MODE_INFO	struct_system_junction_mode_info;
};
struct STRUCT_DBA_ATSS_UPDATE_JUNCTION_MODE_INFO
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    STRUCT_JUNCTION_MODE_INFO	struct_junction_mode_info;
};
// 19 Aug
typedef struct _STRUCT_ITR_STN_CTRL_INFO_
{
    INT_8       cbi_name[15];
    UINT_8      cbi_id;  //cbi id

}STRUCT_DMRC_ITR_STN_CTRL_DATA;

//24Aug2021
struct STRUCT_ATSS_ATSS_SYNCH_END
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
};

struct STRUCT_ATSS_ATSS_CHECKPOINT_OCCUPANCY
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    LEVEL_ID level_id;
    int current_train_id;
    UINT_8 no_of_occupancy_data;
    //Approximate Size 50bytes taken for STRUCT_OCCUPIED_TRACK
    STRUCT_OCCUPIED_TRACK struct_occupied_track[MAX_CHECKPOINT_OCCUPANY_DATA];
};

//24Aug2021
struct STRUCT_ATSS_ATSS_CHECKPOINT_TIME_TABLE
{
    STRUCT_MESSAGE_HEADER msg_header;
    STRING_50             time_table_name[MAX_TIME_TABLE_NAME_STR];
};

//24Aug2021
struct STRUCT_TRAIN_DATA_SWAP
{
    VRS_ID  atss_train_id;          //ATSS provided 9000,... primary key
    RAKE_ID rake_id;                // time table provided
    VRS_ID  timetable_train_id;     //assigned train id station+ journey 3101, 7901,... (DISPLAY)
};

//24Aug2021
struct STRUCT_ATSD_ATSS_TRAIN_ID_SWAP
{
    STRUCT_MESSAGE_HEADER msg_header;
    STRUCT_TRAIN_DATA_SWAP struct_train_data_1;
    STRUCT_TRAIN_DATA_SWAP struct_train_data_2;
};


//24Aug2021
struct STRUCT_ATSS_ATSS_CHECKPOINT_REQUEST_ID
{
    STRUCT_MESSAGE_HEADER struct_msg_header;
    ATS_NODE_CONFIG_COMM_DETAILS config_data;
};

struct STRUCT_DONT_CARE_TRACK
{
    CBI_ID cbi_ID;
    TRACK_ID trk_ID;
    UINT_8 activate_flag; //1 - activate 0- deactivate
};
struct STRUCT_ATSS_ATSS_PROCESS_DONT_CARE
{
    STRUCT_MESSAGE_HEADER struct_msg_header;
    STRUCT_DONT_CARE_TRACK dont_care_track;
};

struct STRUCT_ATSS_DBA_PROCESS_DONT_CARE
{
    STRUCT_MESSAGE_HEADER struct_msg_header;
    STRUCT_DONT_CARE_TRACK dont_care_track;
};

struct STRUCT_DBA_ATSS_PROCESS_DONT_CARE
{
    STRUCT_MESSAGE_HEADER struct_msg_header;
    UINT_16 no_of_tracks;
    STRUCT_DONT_CARE_TRACK dont_care_track[MAX_NUM_OF_DONT_CARE_TRACKS];
};

struct STRUCT_PLATFORM_PAIR_TB
{
    PLATFORM_ID platform1;
    PLATFORM_ID platform2;
};

struct STRUCT_CONFLICT_PLATFORM_TB
{
    TRACK_ID    trk_id;
    CBI_ID      cbi_id;
    PLATFORM_ID tb_id;
    UINT_8      num_of_pairs;
    STRUCT_PLATFORM_PAIR_TB platform_tb_pair[MAX_NUM_PLATFORM_PAIR_TB];
};

struct STRUCT_ATSS_PC_SKIP_STATION
{
    STRUCT_MESSAGE_HEADER msg_header;
    UINT_8 atc_platform_id;
    UINT_8 flag;
};
struct STRUCT_ATSS_PC_TRAIN_HOLD
{
    STRUCT_MESSAGE_HEADER msg_header;
    UINT_8 atc_platform_id;
    UINT_8 flag;
};

struct STRUCT_ATSS_PC_KEEP_DOOR_CLOSED
{
    STRUCT_MESSAGE_HEADER msg_header;
    UINT_8 atc_platform_id;
    UINT_8 flag;
};
struct STRUCT_PROCESS_TIME_TABLE_QUEUE
{
    STRUCT_DBA_ATSS_TIME_TABLE_INFO time_table_init;
    STRUCT_ATSS_DBA_REQ_FOR_TIMETABLE req_time_table;
    STRUCT_ATSD_ATSS_SAVE_AND_VALIDATE_TIME_TABLE save_validate_time_table;
};
struct STRUCT_ATSS_PC_PERIODIC_TSR_MSG
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    ATC_ID atc_id;
    STRUCT_TSR_STATUS_DETAILS tsrDetails[TSR_PERIODIC_DETAILS];
};
struct STRUCT_ATSS_ATSD_PERIODIC_TSR_MSG
{
    STRUCT_MESSAGE_HEADER	struct_message_header;
    ATC_ID atc_id;
    STRUCT_TSR_STATUS_DETAILS tsrDetails[TSR_PERIODIC_DETAILS];
};
struct STRUCT_AMSM_ALL_C_ATS_CONNECTIVITY_STATUS
{
    STRUCT_MESSAGE_HEADER      msg_header;
    UINT_16 		       server_id;
    bool isAlive;
};

struct STRUCT_CBI_DIAGNOASTIC_STATUS
{
    CBI_ID cbi_id;
    UINT_16 NU_status:1;
    UINT_16 RU_status:1;
    UINT_16 FEP1_LINK_A:1;
    UINT_16 FEP1_LINK_B:1;
    UINT_16 FEP1_SU_LINK:1;
    UINT_16 FEP1_HeartBeat:1;
    UINT_16 FEP2_LINK_A:1;
    UINT_16 FEP2_LINK_B:1;
    UINT_16 FEP2_SU_LINK:1;
    UINT_16 FEP2_HeartBeat:1;
    UINT_16 spare:6;
};


struct STRUCT_ATSS_ATSD_CBI_DIAG_DATA
{
    STRUCT_MESSAGE_HEADER      msg_header;
    STRUCT_CBI_DIAGNOASTIC_STATUS diag_status;
};
struct STRUCT_PC_ATSS_CBI_DIAG_DATA
{
    STRUCT_MESSAGE_HEADER      msg_header;
    STRUCT_CBI_DIAGNOASTIC_STATUS diag_status;
};

struct STRUCT_TEMP_USER_LOGIN_LOGOUT
{
    STRUCT_MESSAGE_HEADER      msg_header;
    INT_8	user_name[MAX_NUM_OF_USERNAME_CHAR];
    UINT_8 login_logout_flag;   //0-logout, 1-login
};
#endif
