#ifndef ATSS_IRS_H
#define ATSS_IRS_H
/*
 * @info        - for your information
 * @check       - kindly re verify
 * @comment     - comment away
 * @uncomment   - view and uncomment
 * @ref         - need reference and cross verification
*/
//------------------------------------------------------------
// internally declared
//------------------------------------------------------------
/// Colored Print Constants __________________________________
//#pragma pack(1)
#define RESET                       "\033[0m"
#define BLACK                       "\033[30m"                          // Black
#define RED                         "\033[31m"                          // Red          //invalids
#define GREEN                       "\033[32m"                          // Green
#define YELLOW                      "\033[33m"                          // Yellow
#define BLUE                        "\033[34m"                          // Blue
#define MAGENTA                     "\033[35m"                          // Magenta
#define CYAN                        "\033[36m"                          // Cyan
#define WHITE                       "\033[37m"                          // White
#define BOLDBLACK                   "\033[1m\033[30m"                   // Bold Black
#define BOLDRED                     "\033[1m\033[31m"                   // Bold Red
#define BOLDGREEN                   "\033[1m\033[32m"                   // Bold Green
#define BOLDYELLOW                  "\033[1m\033[33m"                   // Bold Yellow
#define BOLDBLUE                    "\033[1m\033[34m"                   // Bold Blue
#define BOLDMAGENTA                 "\033[1m\033[35m"                   // Bold Magenta
#define BOLDCYAN                    "\033[1m\033[36m"                   // Bold Cyan
#define BOLDWHITE                   "\033[1m\033[37m"                   // Bold White


/// Generic Print Constants __________________________________
#define LOG_ATSS_INFO                                                   0
#define LOG_CRITICAL                                                    1
#define LOG_INTERNAL                                                    2
#define LOG_EXTRA_IMP                                                   3
#define LOG_EXTRA_NIMP                                                  4
#define LOG_ATSS_ATSD                                                   5
#define LOG_ATSS_AMSM                                                   6
#define LOG_ATSS_PC                                                     7
#define LOG_ATSS_DB                                                     8
#define LOG_EXTRA_NIMP_TTV                                              9
#define LOG_EXTRA_NIMP_TTO                                              10
#define LOG_BROADCAST                                                   11
#define LOG_FILE_ONLY                                                   12
#define LOG_ATSS_ATSS                                                   13

#define MAX_NEW_LINE_COUNT                                              2
#define MAX_TAB_COUNT                                                   5
#define MAX_PRINT_STR                                                   2000
#define MAX_LOG_COUNT_IN_FILE                                           200000
#define MAX_COMMUNICATION_BUFFER_SIZE                                   2000
/// Generic Constants ________________________________________
#define TRUE                                                            1
#define FALSE                                                           0
#define SCHED_RR_PRIORITY                                               17
#define POSIX_FAIL                                                      -1
#define MAX_NUMBER_OF_PACKETS                                           1000
#define MAX_SIZE_PACKET                                                 1500
#define TRACK_NAME_SIZE                                                 10
#define POINT_NAME_SIZE                                                 15


/// Application Specific Constants ___________________________
#define NO_CHANNEL_ACTIVE                                               0
#define CHANNEL_1                                                       1
#define CHANNEL_1_ACTIVE                                                1
#define CHANNEL_2_ACTIVE                                                2
#define CHANNEL_2                                                       2
#define MAX_NO_OF_CHANNELS                                              2
#define MAX_WAIT_FOR_ATS_OPERATIONAL                                    3
#define TCP_CHANNEL_1_PORT                                              8080
#define TCP_CHANNEL_2_PORT                                              8081

//#define ATSS_SEND_TO_ATSD_CHANNEL_PORT                                11001
//#define ATSS_RECV_CHANNEL_PORT                                        11002
//#define ATSS_SEND_TO_DBA_CHANNEL_PORT                                 11005//11003
//#define ATSS_SEND_TO_PC_CHANNEL_PORT                                  11004
//#define ATSS_ATSD_BROADCAST_CHANNEL_PORT                              11001

#define ATSS_SEND_TO_TVSS_CHANNEL_PORT                                  50081
#define ATSS_SEND_TO_RS_CHANNEL_PORT                                    50085
#define ATSS_SEND_TO_PID_PAS_CHANNEL_PORT                               50086
#define ATSS_SEND_TO_TRACTION_CHANNEL_PORT                              50087


/// Basic Constants __________________________________________

//#define                                                           __attribute__ ((packed))
typedef char                                                            INT_8;
typedef unsigned char                                                   UINT_8;
typedef short int                                                       INT_16;
typedef unsigned short int                                              UINT_16;
typedef int                                                             INT_32;
typedef unsigned int                                                    UINT_32;
typedef float                                                           REAL_32;
typedef double                                                          REAL_64;
typedef long double                                                     REAL_80;
typedef long long                                                       INT_64;
typedef unsigned long                                                   ULONG_64;
typedef unsigned long long                                              UINT_64;

//------------------------------------------------------------
// IRS 1.0 2020-11-06
//------------------------------------------------------------

/// Message IDs : as per IDD 1.0 2020-11-06
//#define MAX_NO_OF_CBI_ZONE                                            50

//DBA_ATSS  //verified 2020_11_18
#define DBA_ATSS_SELECT_AUTHORITY_AREA                                  68
#define DBA_ATSS_SYSTEM_SELECTED_AUTHORITY_AREA                         69
#define DBA_ATSS_TIME_TABLE_INFO                                        87
#define DBA_ATSS_RELEASE_AUTHORITY_AREA                                 105
#define DBA_ATSS_SYSTEM_PERFORMANCE_RUNNING_TIME_INFO                   121
#define DBA_ATSS_SYSTEM_ROLLING_STOCK_INFO                              124
#define DBA_ATSS_UPDATE_ROLLING_STOCK_INFO                              125
#define DBA_ATSS_SYSTEM_TRAIN_ID_INFO                                   126
#define DBA_ATSS_SYSTEM_ALARM_PRIORITY                                  127
#define DBA_ATSS_SYSTEM_CREW_INFO                                       128
#define DBA_ATSS_SYSTEM_PLATFORM_DWELL_TIME                             129
//#define DBA_ATSS_SYSTEM_JUNCTION_MODE_INFO                            146 // lalit saini changes
#define DBA_ATSS_UPDATE_TRAIN_ID_INFO                                   132
#define DBA_ATSS_UPDATE_PERFORMANCE_RUNNING_TIME                        136
#define DBA_ATSS_UPDATE_PLATFORM_DWELL_TIME_SET                         145
#define DBA_ATSS_UPDATE_JUNCTION_MODE_INFO                              146
#define DBA_ATSS_SYS_PARAM_INFO                                         147
#define DBA_ATSS_UPDATE_ALARM_PRIORITY                                  148
#define DBA_ATSS_UPDATE_CREW_INFO                                       149
#define DBA_ATSS_SYSTEM_JUNCTION_MODE_INFO                              165 // lalit saini changes
#define DBA_ATSS_SEND_CBI_CONTROL_LIST                                  211
#define DBA_ATSS_SEND_TRAIN_REGULATION_MODE                             213
#define DBA_ATSS_SAFETY_COMMAND_COUNTER                                 226
#define DBA_ATSS_TSR_STATUS_INFO                                        236
#define DBA_ATSS_CMD_STATUS                                             237
#define DBA_ATSS_HEADWAY_MODE_SETTING                                   238
#define DBA_ATSS_PROCESS_DONT_CARE                                      239

#define DBA_ATSS_UPDATE_REGISTRATION_INFO                               995
#define DBA_ATSS_SYSTEM_LOGGED_USER_INFO                                997
#define DBA_ATSS_TRAIN_ID_INFO                                          1001

//ATSD_ATSS  //verified 2020_11_17
#define ATSD_ATSS_GLOBAL_COMMAND                                        1
#define ATSD_ATSS_EMERGENCY_SECTION_COMMAND                             2
#define ATSD_ATSS_PLATFORM_COMMAND                                      3
#define ATSD_ATSS_RAKE_COMMAND                                          7
#define ATSD_ATSS_TVS_COMMAND                                           11
#define ATSD_ATSS_VIRTUL_BLOCK_COMMAND                                  14
#define ATSD_ATSS_CYCLE_COMMAND                                         36
#define ATSD_ATSS_OVERLAP_COMMAND                                       37
#define ATSD_ATSS_PARTICULAR_COMMAND                                    38
#define ATSD_ATSS_POINT_COMMAND                                         39
#define ATSD_ATSS_ROUTE_COMMAND                                         40
#define ATSD_ATSS_SIGNAL_COMMAND                                        41
#define ATSD_ATSS_SPK_AUTHORIZATION_COMMAND                             42
#define ATSD_ATSS_TRACK_COMMAND                                         43
#define ATSD_ATSS_SELECTED_TRAIN_INVENTORY                              56
#define ATSD_ATSS_HEADWAY_MODE_SETTING                                  76
#define ATSD_ATSS_SHELVE_TIMETABLE                                      83
#define ATSD_ATSS_SAVE_AND_VALIDATE_TIME_TABLE	                        84
#define ATSD_ATSS_LOAD_SWITCH_TIME_TABLE_MODE                           93
#define ATSD_ATSS_USER_UPDATE_ONLINE_TIMETABLE                          94
#define ATSD_ATSS_ASSIGN_RAKE_ID                                        200
#define ATSD_ATSS_REQ_FOR_TIMETABLE                                     201                     //85 Modified by Amit as per Rupesh 06 Aug 2020
#define ATSD_ATSS_TSR_COMMAND_ID                                        250
#define ATSD_ATSS_TSR_COMMAND_CONFIRMATION_RES_ID                       254
#define ATSD_ATSS_GLOBAL_TRAIN_HOLD_COMMAND                             259
#define ATSD_ATSS_ONLINE_TIME_TABLE_INFO                                270
#define ATSD_ATSS_JUNCTION_MODE_SETTING                                 271
#define ATSD_ATSS_ACTIVATE_DEACTIVATE_TRACK_CIRCUIT                     173
#define ATSD_ATSS_TRAIN_ID_SWAP                                         272
#define ATSD_ATSS_ENABLE_DISABLE_ATR                                    273 // flag 1-enable 0- disable TRUE by default
#define ATSD_ATSS_ENABLE_DISABLE_HEADWAY_CYCLE                          274

#define ATSD_ATSS_TEMP_USER_LOGIN_LOGOUT                               275 //Amit-16Feb2022 added by Rupesh Rawat for ISA
                                                                            //finally to be done by DB

//AMSM_ATSS  //verified 2020_11_17
#define AMSM_ATSS_CHECKPOINT_REQUEST_ID                                 153
#define AMSM_ATSS_APPLICATION_STATE_ID                                  156
#define AMSM_ATSS_START_SYNCH_ID                                        163
#define AMSM_ATSS_REQUEST_RESTORE_ID                                    3000
#define AMSM_ATSS_START_PROCESSING_ID                                   3001
#define AMSM_ALL_C_ATS_CONNECTIVITY_STATUS                              223


#define PC_ATSS_ATC_STATIONS_RESPONSE                                   2001
#define PC_ATSS_ONBOARD_ATC_ALARM_MESSAGE                               2002
#define PC_ATSS_ROLLING_STOCK_ALARM_MESSAGE                             2003
#define PC_ATSS_TRACK_SIDE_ATC_MESSAGE                                  2004
#define PC_ATSS_ATC_POSITIVE_TRAIN_IDENTIFICATION_MESSAGE               171
#define PC_ATSS_CLOCK_SYNCHRONIZATION_REQUEST_MESSAGE                   172
#define PC_ATSS_TSR_STATUS_MESSAGE                                      2009

#define PC_ATSS_ATC_PLATFORM_RESPONSE                                   6
#define PC_ATSS_ATC_RAKE_RESPONSE_PACKET                                10
#define PC_ATSS_ATC_VIRTUAL_BLOCK_RESPONSE_PACKET                       17
#define PC_ATSS_CBI_POINT_SIGNAL_PLATFORM_STATION_EMERGENCY_RESPONSE    55
#define PC_ATSS_CBI_ROUTE_RESPONSE                                      58
#define PC_ATSS_CBI_TRACK_CYCLE_OVERLAP_RESPONSE                        66
#define PC_ATSS_ATC_STATUS_PACKET                                       71
#define PC_ATSS_HEALTH                                                  131
#define PC_ATSS_RADIO_DESCRIPTION                                       190
#define PC_ATSS_ON_BOARD_RADIO_FAILURE_STATUS                           192 //2021_01_16
#define PC_ATSS_CBI_TRACK_ROUTE_POINT_RESPONSE                          198
#define PC_ATSS_TRAIN_ALARM_MSG                                         220
#define PC_ATSS_PERIODIC_TSR_STATUS                                     228
#define PC_ATSS_SAFETY_RELATED_TIME_MESSAGE                             252
#define PC_ATSS_TSR_LOGGING_ID                                          256
#define PC_ATSS_TSR_REPORT_OF_OPERATION_ID                              257
#define PC_ATSS_ATC_EQUIPMENT_STATUS                                    202
#define PC_ATSS_EXTERNAL_SYSTEM_HEALTH                                  264
#define PC_ATSS_CBI_STATUS                                              266
#define PC_ATSS_CBI_DIAG_DATA                                           270

//ATSS_AMSM
#define ATSS_AMSM_SYNCH_COMPLETED                                       161

// ATSS_PC  //verified 2020_11_18
#define ATSS_PC_ATC_PLATFORM_COMMAND_PACKET                             5
#define ATSS_PC_ATC_RAKE_COMMAND_PACKET                                 9
#define ATSS_PC_ATC_VIRTUAL_BLOCK_COMMAND_PACKET                        16
#define ATSS_PC_CYCLE_COMMAND                                           46
#define ATSS_PC_OVERLAP_COMMAND                                         47
#define ATSS_PC_PARTICULAR_CBI_COMMAND                                  48
#define ATSS_PC_POINT_COMMAND                                           49
#define ATSS_PC_ROUTE_COMMAND                                           50
#define ATSS_PC_SIGNAL_COMMAND                                          51
#define ATSS_PC_SPK_AUTHORIZATION_COMMAND                               52
#define ATSS_PC_TRACK_COMMAND                                           53
#define ATSS_PC_ATC_EM_COMMAND_PACKET                                   82
#define ATSS_PC_TSR_STATUS_MSG                                          167
#define ATSS_PC_ATC_INIT_RESPONSE                                       169
#define ATSS_PC_CLOCK_SYNCH_COMMAND                                     170
#define ATSS_PC_ARRIVAL_PLATFORM                                        176
#define ATSS_PC_PIDS_PAS_CLEAR                                          177
#define ATSS_PC_DEPARTURE_PLATFORM                                      178
#define ATSS_PC_NEXT_THREE_DEPARTURES                                   179
#define ATSS_PC_TRAIN_DESCRIPTION                                       184
#define ATSS_PC_ATC_EQUIPMENT_STATUS                                    171
#define ATSS_PC_TSR_COMMAND_ID                                          251
#define ATSS_PC_TSR_COMMAND_CONFIRMATION_RES_ID                         255
#define ATSS_PC_CLEAR_CHANGE_OVER_STATUS                                269
#define ATSS_PC_SKIP_STATION                                            270
#define ATSS_PC_TRAIN_HOLD                                              271
#define ATSS_PC_KEEP_DOOR_CLOSED                                        272

//ATSS_DBA  //verified 2020_11_18
#define ATSS_DBA_TVS_COMMAND                                            13
#define ATSS_DBA_LOG_ALARM                                              31
#define ATSS_DBA_LOG_EVENT                                              32
#define ATSS_DBA_UPDATE_TRAIN_REGULATION_MODE                           33
#define ATSS_DBA_AUTO_ROUTE_SETTING_STATUS                              45
#define ATSS_DBA_REQUEST_INIT_DATA                                      64
#define ATSS_DBA_HEADWAY_MODE_SETTING                                   78
#define ATSS_DBA_REQ_FOR_TIMETABLE                                      81
#define ATSS_DBA_SAVE_TIME_TABLE                                        92
#define ATSS_DBA_CMD_STATUS                                             215
#define ATSS_DBA_SAFETY_COMMAND_COUNTER                                 224
#define ATSS_DBA_TSR_STATUS_INFO                                        234
#define ATSS_DBA_ENABLE_DISABLE_HEADWAY_CYCLE                           235
#define ATSS_DBA_PROCESS_DONT_CARE                                      236
#define ATSS_DBA_ATR_ENABLE_DISABLE_FLAG                                237

//ATSS_ATSD
#define ATSS_ATSD_ATC_STATIONS_RESPONSE                                 4
#define ATSS_ATSD_ATC_RAKE_RESPONSE_PACKET                              8

#define ATSS_ATSD_TVS_COMMAND                                           12
#define ATSS_ATSD_ATC_VIRTUAL_BLOCK_RESPONSE_PACKET                     15

#define ATSS_ATSD_ACTIVE_SERVER_HEALTH                                  21
#define ATSS_ATSD_GEN_ALARM                                             22
#define ATSS_ATSD_GEN_EVENT                                             23
#define ATSS_ATSD_ONLINE_TIME_TABLE_INFO                                270

#define ATSS_ATSD_PSD_STATUS                                            24
#define ATSS_ATSD_SPAD_INDICATION                                       26
#define ATSS_ATSD_TRACTION_ZONE_INDICATION                              27
#define ATSS_ATSD_TRAIN_RADIO_STATUS                                    28
#define ATSS_ATSD_UPDATE_TRAIN_REGULATION_MODE                          29
#define ATSS_ATSD_AUTO_ROUTE_SETTING_STATUS                             44 //modify flag on STRUCT_CBI_TRACK_CYCLE_OVERLAP_RESP arsd_flag
#define ATSS_ATSD_TRAIN_INVENTORY                                       67
#define ATSS_ATSD_ATC_STATUS_PACKET                                     108

#define ATSS_ATSD_CBI_POINT_SIGNAL_PLATFORM_STATION_EMERGENCY_RESPONSE  54
#define ATSS_ATSD_CBI_ROUTE_RESPONSE                                    59
#define ATSS_ATSD_CBI_TRACK_CYCLE_OVERLAP_RESPONSE                      80
#define ATSS_ATSD_FILE_SENT_ACK                                         87
#define ATSS_ATSD_TIME_TABLE_VALIDITY_RESP                              90
#define ATSS_ATSD_UPDATE_ONLINE_TIMETABLE                               91
#define ATSS_ATSD_PLATFORM_DWELL_TIME_DELAY_ID                          92
#define ATSS_ATSD_CBI_TRACK_ROUTE_POINT_RESPONSE                        199
#define ATSS_ATSD_EQUIPMENT_STATUS                                      203
#define ATSS_ATSD_CMD_STATUS                                            214
#define ATSS_ATSD_TRAIN_ALARM_MSG                                       221
#define ATSS_ATSD_SAFETY_COMMAND_COUNTER                                225
#define ATSS_ATSD_TSR_STATUS_INFO                                       233
#define ATSS_ATSD_DEPARTURE_PLATFORM                                    250
#define ATSS_ATSD_ARRIVAL_PLATFORM                                      251
#define ATSS_ATSD_NEXT_THREE_DEPARTURES                                 252
#define ATSS_ATSD_TSR_COMMAND_CONFIRMATION_ID                           253
#define ATSS_ATSD_CBI_STATUS                                            267
#define ATSS_ATSD_EXTERNAL_SYSTEM_HEALTH                                268 //acc to rupesh sir 01-07-2021
#define ATSS_ATSD_PIDS_PAS_CLEAR                                        269

#define ATSS_BROADCAST_GEN_ALARM                                        22
#define ATSS_BROADCAST_GEN_EVENT                                        23

#define ATSS_ATSS_ADD_REMOVE_TRAIN_OCCUPANCY_ID                         1
#define ATSS_ATSS_HEADWAY_SETTING_ID                                    2
#define ATSS_ATSS_CHEKPOINT_OCCUPANCY_DATA_ID                           3
#define ATSS_ATSS_CHEKPOINT_TIMETABLE_ID                                4
#define ATSS_ATSS_CHECKPOINT_REQUEST_ID                                 5
#define ATSS_ATSS_SYNCH_END                                             6
#define ATSS_ATSD_PERIODIC_TSR_STATUS                                   271
#define ATSS_ATSD_CBI_DIAG_DATA                                         272



#define ATSS_DATA_LOGGER_START_LOGGING_ID       1


//ATSS_AMSM   //verified 2020_11_17
//#define ATSS_AMSM_CHECKPOINT_COMPLETED_ID                               0
//#define ATSS_AMSM_RESTORE_COMPLETED_ID                                  0+1


#define CSCI_ATSD       1
#define CSCI_ATSS       2
#define CSCI_SIM        3
#define CSCI_PC         4
#define CSCI_DBA        5
#define CSCI_AMSM       6
#define ALL_OWS         100

#define CSCI_DATA_LOGGER    99

#define DATA_LOGGER_SEND_PORT                                           10101

#define TRAIN_SPEED                                                     UINT_8
#define MAX_NO_OF_ALARMS                                                UINT_8
#define RUNNING_DIRECTION                                               UINT_8
#define ON_BOARD_ERROR_CODE                                             UINT_8
#define INITIALIZATION_STATUS                                           UINT_8
#define ALARM_ID                                                        UINT_16
#define EVENT_ID                                                        UINT_16
#define VRS_REPORT                                                      UINT_16
#define SC_EB_REASON                                                    UINT_16
#define DISTANCE_TO_MA                                                  UINT_16
#define VOBC_EB_REASON                                                  UINT_16
#define VIRTUAL_BLOCK_ID                                                UINT_16
#define PLATFORM_DOOR_ID                                                UINT_16
#define NO_ENTRY_SETTING                                                UINT_16
#define TRAIN_DOOR_STATUS                                               UINT_16
#define ATO_DRIVING_STATUS                                              UINT_16
#define STATIC_TEST_RESULT                                              UINT_16
#define TSR_SETTING_ANSWER                                              UINT_16
#define TSR_DECLINE_REASON                                              UINT_16
#define WET_DRY_SETTING_ANSWER                                          UINT_16
#define NO_ENTRY_DECLINE_REASON                                         UINT_16
#define NO_ENTRY_SETTING_ANSWER                                         UINT_16
#define MAX_NO_OF_JOURNEY_IN_TIMETABLE                                  UINT_16

#define SECONDS_TO_REQUEST_INIT                                         10
//--------------------------------------------------------------------------------
// MIN and MAX limits of varioius entities
//--------------------------------------------------------------------------------
#define MAX_NUM_OF_SAFETY_COMMAND                                       13
#define MAX_NUM_OF_USERNAME_CHAR                                        25
#define MAX_NUM_OF_ALARMS                                               100
#define MAX_NUM_OF_TRACKS                                               100
#define MAX_NUM_OF_DONT_CARE_TRACKS                                     400
#define MAX_NUM_OF_VIRTUAL_BLOCKS                                       2000

#define MAX_NUM_OF_PLATFORMS                                            50
#define MAX_NUM_OF_PLATFORMS_DB                                         100
#define MAX_NUM_OF_EMERGENCY_SECTION                                    50
#define MAX_NUM_OF_POINTS                                               90//100
#define MAX_NUM_OF_SIGNALS                                              90//100
#define MAX_NUM_OF_STATIONS                                             100
#define MAX_NUM_OF_PIDS_PAS_STATIONS                                    60

#define MAX_NUM_OF_TIMETABLES                                           50
#define MAX_NUM_OF_CYCLES                                               50
#define MAX_NUM_OF_ACTIVE_CYCLES                                        10
#define MAX_NUM_OF_TUNNELS                                              50
#define MAX_NUM_OF_VIEWS                                                50
#define MAX_NUM_OF_DISPLAYS                                             50
#define MAX_NUM_OF_GLOBAL_COMMANDS                                      50
#define MIN_NUM_OF_ATC_ID                                               50
#define MAX_NUM_OF_ATC_ID                                               50
#define MIN_NUM_OF_RAKE_ID                                              50
#define MAX_NUM_OF_RAKE_ID                                              50
#define MIN_NUM_OF_REAR_BLOCK_ID                                        50
#define MAX_NUM_OF_REAR_BLOCK_ID                                        50
#define MIN_NUM_OF_FWD_BLOCK_ID                                         50
#define MAX_NUM_OF_FWD_BLOCK_ID                                         50
#define MIN_NUM_OF_VRS_ID                                               50
#define MAX_NUM_OF_VRS_ID                                               50
#define MIN_NUM_OF_CBI_ID                                               50
#define MAX_NUM_OF_CBI_ID                                               50
#define MIN_NUM_OF_ROUTE_ID                                             50
#define MAX_NUM_OF_ROUTE_ID                                             50
#define MIN_NUM_OF_TRACK_ID                                             50
#define MAX_NUM_OF_TRACK_ID                                             50
#define MAX_NUM_OF_TRIPS                                                100
#define MAX_NUM_OF_OVERLAPPINGS                                         200
#define MAX_NUM_OF_ROUTES                                               350
#define MAX_NUM_OF_STOPPING_POINTS                                      1000

#define MAX_NUM_OF_ATC                                                  10
#define MAX_NUM_OF_CBI                                                  32
#define MAX_NUM_OF_WORKSTATION                                          10
#define MAX_NUM_OF_WORKSTATIONS_XML                                     20
#define MIN_NUM_OF_RAKES                                                50
#define MAX_NUM_OF_RAKES                                                20
#define MAX_NUM_OF_RAKE_HEADWAY                                         100
#define MAX_NUM_OF_RAKES_INIT                                           100
#define MAX_NUM_OF_ROUTE_SET_COMMANDS                                   50
#define MIN_NUM_OF_JOURNEYS                                             1
#define MAX_NUM_OF_JOURNEYS                                             50
#define MAX_NUM_OF_CONFLICTS                                            20
#define MAX_NUM_OF_TSR                                                  32
#define MAX_NUM_OF_HEADWAY_SETTING                                      100
#define MAX_NUM_OF_TSR_INIT                                             200

#define MAX_NUM_OF_PIDS_PAS                                             5
#define MAX_NUM_OF_RADIO_SERVER                                         5

//string name size
#define STATION_NAME_SIZE                                               15

#define BUFFER_TIME_BETWEEN_STATIONS                                    30
#define UASM_DWELL_TIME                                                 30
#define ZERO                                                            0
#define ONE                                                             1
#define THREE                                                           3
#define STRING_FIVE                                                     5
#define STRING_EIGHT                                                    8
#define STRING_TEN                                                      10
#define STRING_SIXTEEN                                                  16
#define STRING_TWENTY                                                   20
#define STRING_TWENTY_FIVE                                              25
#define STRING_FIFTY                                                    50
#define STRING_TWO_FIFTY                                                250
#define STRING_USER_NAME                                                25
#define SEC_MAX                                                         59
#define MIN_MAX                                                         59
#define HOUR_MAX                                                        23      //doubt if time will be 24 hour format
#define MONTH_MIN                                                       1
#define MONTH_MAX                                                       12
#define DAY_MAX                                                         31
#define YEAR_MIN                                                        2020
#define YEAR_MAX                                                        2050
#define MIN_JOURNEY_ID                                                  1
#define MAX_JOURNEY_ID                                                  50

#define MIN_TRIP_ID                                                     1
#define MAX_TRIP_ID                                                     50
#define MIN_STOPPING_PT                                                 1
#define MAX_STOPPING_PT                                                 50
#define MIN_ATC_ID                                                      2050
#define MAX_ATC_ID                                                      2050
#define MIN_VB_ID                                                       2050
#define MAX_VB_ID                                                       2050
#define MIN_VATC_MODE                                                   2050
#define MAX_VATC_MODE                                                   2050
#define MIN_VATC_MODE                                                   2050
#define MIN_VATC_MODE                                                   2050
#define MIN_VATC_MODE                                                   2050
#define MIN_VATC_MODE                                                   2050
#define MIN_VATC_MODE                                                   2050

#define ROUTE_TYPE                                                      1
#define TRACK_TYPE                                                      2
#define POINT_TYPE                                                      3

#define FREQ_SIXTY_SECONDS                                              60
#define FREQ_TEN_SECONDS                                                10

#define ALARM_STATUS_ACTIVE                                             0
#define ALARM_NOT_ACTIVE                                                1
#define ALARM_STATUS_ACK                                                2
#define ALARM_STATUS_NOT_ACK                                            3

//EVENT_TYPE

//EVENT_TYPE_TRACK
#define EVENT_TYPE_TRACK_TSR_imposed                                    1
#define EVENT_TYPE_TRACK_TSR_removed                                    2
#define EVENT_TYPE_TRACK_Low_Adhesion_imposed                           3
#define EVENT_TYPE_TRACK_Low_Adhesion_removed                           4
#define EVENT_TYPE_TRACK_Track_free                                     5
#define EVENT_TYPE_TRACK_Maintainance_block_set                         6
#define EVENT_TYPE_TRACK_No_Entry_removed                               7
//#define EVENT_TYPE_TRACK_                               8
//#define EVENT_TYPE_TRACK_                               9
//#define EVENT_TYPE_TRACK_                               10
//#define EVENT_TYPE_TRACK_                               11
//#define EVENT_TYPE_TRACK_                               12
//#define EVENT_TYPE_TRACK_                               13

//EVENT_TYPE_POINT
#define EVENT_TYPE_POINT_Normal                                         41
#define EVENT_TYPE_POINT_Reverse                                        42
#define EVENT_TYPE_POINT_Normal_by_User                                 43
#define EVENT_TYPE_POINT_Reverse_by_User                                44
#define EVENT_TYPE_POINT_Normal_in_Emergency mode                       45
#define EVENT_TYPE_POINT_Reverse_in_Emergency mode                      46
#define EVENT_TYPE_POINT_blocked_by_User                                47
#define EVENT_TYPE_POINT_unblocked_by_User                              48
#define EVENT_TYPE_POINT_authorised_for_manual_point_operation          49
#define EVENT_TYPE_POINT_EKT_inhibited_for_manual_point_operation       50
#define EVENT_TYPE_POINT_EKT_taken_out_by_user                          51
#define EVENT_TYPE_POINT_EKT_inserted_by_user                           52
#define EVENT_TYPE_POINT_Authorization_failed                           53
#define EVENT_TYPE_POINT_Authorised_for_self_normalization              54
#define EVENT_TYPE_POINT_out_of_Correspondence                          55
#define EVENT_TYPE_POINT_inhibited_for_self_normalization               56
#define EVENT_TYPE_POINT_flank_protected                                57
#define EVENT_TYPE_POINT_locked_in_route                                58
#define EVENT_TYPE_POINT_out_of_Control                                 59
#define EVENT_TYPE_POINT_EKT_failed                                     60

//to_be_done
//EVENT_TYPE_SIGNAL
#define EVENT_TYPE_SIGNAL_                                              00

//to_be_done
//EVENT_TYPE_PLATFORM
#define EVENT_TYPE_PLATFORM_                                            00

//to be done
#define EVENT_TYPE_STATION_                                             00

//to_be_done
//EVENT_TYPE_EMERGENCY
#define EVENT_TYPE_EMERGENCY_                                           00


//to_be_done
//EVENT_TYPE_ROUTE
#define EVENT_TYPE_ROUTE_                                               00

//to_be_done
//EVENT_TYPE_CYCLE
#define EVENT_TYPE_CYCLE_                                               00

//ENTITY_TYPE critical commands
//EVENT_TYPE_TRACK_CRITICAL
#define ENTITY_TYPE_UNBLOCK_POINT                                       1
#define ENTITY_TYPE_TRACK                                               1
#define ENTITY_TYPE_VIRTUAL_BLOCK                                       2
#define ENTITY_TYPE_PLATFORM                                            3
#define ENTITY_TYPE_RAKE                                                4
#define ENTITY_TYPE_SIGNAL                                              5
#define ENTITY_TYPE_ROUTE                                               6
#define ENTITY_TYPE_POINT                                               7
#define ENTITY_TYPE_CYCLE                                               8
#define ENTITY_TYPE_EMERGENCY_SECTION                                   9
#define ENTITY_TYPE_OVERLAPPING                                         10
#define ENTITY_TYPE_CBI                                                 11
#define ENTITY_TYPE_STATION                                             12

//ALARM_TYPE
#define ALARM_TYPE_Train_Delayed                                        1
#define ALARM_TYPE_Train_Controlled_by_Time_Table                       2
#define ALARM_TYPE_No_One_Control_Area                                  3
#define ALARM_TYPE_PSD_Isolated                                         4
#define ALARM_TYPE_PSD_Bypassed                                         5
#define ALARM_TYPE_Train_Passenger_Emergency_Alarm                      6
#define ALARM_TYPE_Train_Fire_Detected                                  7
#define ALARM_TYPE_No_Entry                                             8
#define ALARM_TYPE_Temporary_Speed_Restriction                          9
#define ALARM_TYPE_Low_Adhesion                                         10
#define ALARM_TYPE_Train_Door_Opened                                    11
#define ALARM_TYPE_Train_Door_Closed                                    12
#define ALARM_TYPE_Train_Short_Stopped                                  13
#define ALARM_TYPE_Train_Skip_Stop                                      14
#define ALARM_TYPE_Train_Overrun                                        15
#define ALARM_TYPE_VOBC_Reset                                           16
#define ALARM_TYPE_Train_ATO_Departure                                  17
#define ALARM_TYPE_Train_Ready_Request_Issued                           18
#define ALARM_TYPE_Train_Docked                                         19
#define ALARM_TYPE_Train_Passed_PO                                      20
#define ALARM_TYPE_Train_Departed                                       21
#define ALARM_TYPE_Train_Static_Test_Completed                          22
#define ALARM_TYPE_Train_Dynamic_Test_Completed                         23

#define TIME_TABLE_MODE                                                 1
#define HEADWAY_MODE                                                    2
#define MANUAL_REGULATION_MODE                                          3
#define ATR_OFF_MODE                                                    4
#define FULL_MODE                                                       5

//#define CSCI_DBA                                                      5
//#define CSCI_PC                                                       4
//#define CSCI_ATSD                                                     1

#define MIN_TT_STATE                                                    1
#define MAX_TT_STATE                                                    10
#define UASM_DEPARTURE_TIME_THRESHOLD_MIN                               300   // 5 minutes
#define UASM_INTERSTATION_STOP_ALARM_THRESHOLD_SEC                      30    //seconds

#define ROUTE_SET_TIME_LIMIT                                            10
#define TRACK_SET_TIME_LIMIT                                            10
#define POINT_SET_TIME_LIMIT                                            10


//------------------------------------------------------------------------

#define STATE_OF_TRAIN_DOOR                              UINT_8
#define REMOTE_COMMAND_ACK                              UINT_8
#define EB_REASON                                       UINT_16
#define STATIC_TEST_RESULT_ONBOARD                      UINT_8
#define STATIC_TEST_RESULT_ROLLING_STOCK                UINT_8
#define DYNAMIC_TEST_RESULT_ONBOARD                     UINT_8
#define TRAIN_DETECTION_MODE                            UINT_8

#define MASTER_SLAVE_ONBOARD                            UINT_8
#define DEPARTURE_DIRECTION                             UINT_8
#define SLEEP_MODE                                      UINT_16
#define RESET_RESULT_ON_BOARD                           UINT_8
#define TYPE_OF_VEHICLE                                 UINT_8
#define DISTANCE_TO_STOPPING_POINT                      UINT_16
#define CBI_TRACK_ROUTE_POINT_RESPONSE_TIME             15

//0- non-stop/skip stop 1- not in service 2- terminated here 3 - normal
#define TRAIN_SITUATION_TYPE_SKIP_STOP                  0
#define TRAIN_SITUATION_TYPE_NOT_IN_SERVICE             2
#define TRAIN_SITUATION_TYPE_TERMINATED_HERE            3
#define TRAIN_SITUATION_TYPE_NORMAL                     4

#define SERVICE_TYPE_AUTO                               1
#define SERVICE_TYPE_IN_SERVICE                         2
#define SERVICE_TYPE_OUT_OF_SERVICE                     3

//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	1-10
//COMMENTS	1- Platform Hold Command
//NO OF BITS	4
#define PLATFORM_NUM    UINT_8
#define PLATFORM_ID    UINT_8
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	1-255
//COMMENTS	
//NO OF BITS	

#define STATION_ID 	UINT_8 
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	
//COMMENTS	0 -   Invalid value

//NO OF BITS	8

#define OWS_ID 	UINT_8 
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	1-255
//COMMENTS	100- For All workstations
//NO OF BITS	8

#define BOOL 	UINT_8 
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	0-1
//COMMENTS	0 : Unlink 
//0 : no command
//If train door is opened, train cannot departure. Then, if ATS commands this command, on-board ATC is possible to become departure status.

//Emergency Status
//"xx" is radio set number.
//RSxx reset

//RSxx FAN Failure status
//This data is shown the FAN failure of each WRSs.
//NO OF BITS	1

#define MAX_NO_OF_STATIONS                                         UINT_16

#define MAX_NO_OF_PLATFORMS 	UINT_8 
//NO OF BITS	4
//COMMENTS	MAX 16 PLATFORMS WITH IN A STATION 

#define CSCI_ID 	UINT_8 
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	1-4
//COMMENTS	1- ATS Display
//4- PC
//NO OF BITS	4

#define CSCI_STATE UINT_8

#define MESSAGE_ID 	UINT_16 
//LEGAL CHECK	1- 256
//UNIT	NUMBER
//PRECISION	1
//RANGE	0-255
//NO OF BITS	16

#define ROUTE_ID 	UINT_16
//PRECISION	1
//UNIT	NUMBER

#define CBI_ID 	UINT_8 
//PRECISION	1
//UNIT	NUMBER
//NO OF BITS	5

#define SIGNAL_ID 	UINT_16
//PRECISION	1
//UNIT	NUMBER

#define MAX_NO_OF_ROUTES 	UINT_8 

#define MAX_NO_OF_SIGNALS                                 UINT_16

#define MAX_NO_OF_POINTS                                   UINT_16

#define MAX_NO_OF_TRACKS                                   UINT_16

#define MAX_NO_OF_OVERLAPPINGS                             UINT_16

#define POINT_ID 	UINT_8 
//PRECISION	1
//UNIT	NUMBER

#define TRACK_ID 	UINT_8 
//PRECISION	1
//UNIT	NUMBER

#define OVERLAP_ID 	UINT_8 
//PRECISION	1
//UNIT	NUMBER




//NO OF BITS	4

#define ALARM_STRING 	UINT_8 
//UNIT	NOT APPLICABLE

#define MESSAGE_LENGTH 	UINT_16 
//LEGAL CHECK	
//UNIT	NUMBER
//PRECISION	1
//RANGE	1-1500
//NO OF BITS	16

#define DISTANCE_IN_METER 	UINT_16 
//LEGAL CHECK	
//UNIT	NUMBER
//PRECISION	1
//RANGE	

#define MAX_NO_OF_RAKES 	UINT_16

#define HOUR 	UINT_8 
//RANGE	NA
//UNIT	HOUR
//PRECISION	1
//LEGAL CHECK	0-23
//COMMENTS	 



//NO OF BITS	5

#define MINUTE 	UINT_8 
//RANGE	NA
//UNIT	MINUTE
//PRECISION	1
//LEGAL CHECK	0-59
//COMMENTS	 



//NO OF BITS	6

#define SECOND 	UINT_8 
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	0-59
//COMMENTS	 
//NO OF BITS	6


#define JOURNEY_ID UINT_8
//NO OF BITS	10

#define MAX_NO_OF_PLANNED_TRIP                      UINT_16

#define FILE_NAME 	UINT_8 
//LEGAL CHECK	20 Characters
//UNIT	STRING

#define INFO_STRING 	UINT_8 
//UNIT	STRING
//LEGAL CHECK	50 Characters long

#define DWELL_TIME_TYPE 	UINT_8 
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	1-3
//NO OF BITS	4

#define TRAIN_PERFORMANCE_REGIME 	UINT_8 
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	0-4
//COMMENTS	00 : no command
//"S" mode is "slow mode". If "S" mode is selected, train runs slower than normal speed.
// "N" mode is "normal mode". If "N" mode is selected, train runs normal speed.
// "F" mode is "fast mode". If "F" mode is selected, train runs faster than normal speed.
//NO OF BITS	2

#define SERVICE_TYPE 	UINT_8 
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	1-3
//COMMENTS	1- Service Auto
//NO OF BITS	2

#define CREW_ID 	UINT_32 //SCP 2021_01_16 16 jan
//PRECISION	1
//UNIT	NUMBER

#define STOPPING_POINT_ID 	UINT_8 
//PRECISION	1
//UNIT	NUMBER
//NO OF BITS	10

#define CYCLE_ID 	UINT_8
#define CYCLE_KEY   UINT_32
//PRECISION	1
//UNIT	NUMBER
//NO OF BITS	4


/// COMMAND_TYPES ////////////////////////////////////////////////////////////////////
//RESPONSE_COMMAND_TYPE
//RANGE         : NA
//UNIT          : NOT APPLICABLE
//PRECISION     : 1
//LEGAL_CHECK   : 0-5
//COMMENTS      :
#define RESPONSE_COMMAND_TYPE                         UINT_8
#define RESPONSE_COMMAND_TYPE_SKIP_STATION_SET        0
#define RESPONSE_COMMAND_TYPE_SKIP_STATION_RELEASE    1
#define RESPONSE_COMMAND_TYPE_KEEP_DOOR_CLOSE_SET     2
#define RESPONSE_COMMAND_TYPE_KEEP_DOOR_CLOSE_RELEASE 3
#define RESPONSE_COMMAND_TYPE_TRAIN_HOLD              4
#define RESPONSE_COMMAND_TYPE_TRAIN_HOLD_RELEASE      5
#define RESPONSE_COMMAND_TYPE_TSR_SET                 6
#define RESPONSE_COMMAND_TYPE_TSR_RELEASE             7

//TSR_COMMAND_TYPE
//RANGE         : NA
//UNIT          : NOT APPLICABLE
//PRECISION     : 1
//LEGAL_CHECK   : 1-2
//COMMENTS      :
#define TSR_COMMAND_TYPE         UINT_8
#define TSR_COMMAND_TYPE_REQUEST 1
#define TSR_COMMAND_TYPE_CONFIRM 2

//PLATFORM_COMMAND_TYPE
//RANGE         : NA
//UNIT          : NOT APPLICABLE
//PRECISION     : 1
//LEGAL_CHECK   : 1-10
//COMMENTS      :
#define PLATFORM_COMMAND_TYPE                           UINT_8
#define PLATFORM_COMMAND_TYPE_HOLD                      1
#define PLATFORM_COMMAND_TYPE_HOLD_RELEASE              2
#define PLATFORM_COMMAND_TYPE_SKIP_STOP                 3
#define PLATFORM_COMMAND_TYPE_SKIP_STOP_RELEASE         4
#define PLATFORM_COMMAND_TYPE_KEEP_DOOR_CLOSED          5 //psd and train doors
#define PLATFORM_COMMAND_TYPE_RECEIVE_KEEP_DOOR_RELEASE 6 //psd and train doors
#define PLATFORM_COMMAND_TYPE_STATION_DOOR_OPEN         7
#define PLATFORM_COMMAND_TYPE_STATION_DOOR_CLOSE        8
#define PLATFORM_COMMAND_TYPE_TRAIN_DOOR_OPEN           9
#define PLATFORM_COMMAND_TYPE_TRAIN_DOOR_CLOSE          10

//RAKE_COMMAND_TYPE
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL_CHECK   : 1-15
//COMMENTS	1:  Manual ATO Departure Command
#define RAKE_COMMAND_TYPE                       UINT_8
#define RAKE_COMMAND_TYPE_MANUAL_ATO_DEPARTURE  1
#define RAKE_COMMAND_TYPE_STOP_NOW              2
#define RAKE_COMMAND_TYPE_EB_RELEASE            3
#define RAKE_COMMAND_TYPE_TRAIN_HOLD            4
#define RAKE_COMMAND_TYPE_RELEASE_TRAIN         5
#define RAKE_COMMAND_TYPE_RESET_VATC            6
#define RAKE_COMMAND_TYPE_OUT_OF_SERVICE        7
#define RAKE_COMMAND_TYPE_WAKE_UP               8
#define RAKE_COMMAND_TYPE_STANDBY               9
#define RAKE_COMMAND_TYPE_KEEP_DOOR_CLOSED      10
#define RAKE_COMMAND_TYPE_L_E_DOOR_CLOSED       11
#define RAKE_COMMAND_TYPE_R_E_DOOR_CLOSED       12
#define RAKE_COMMAND_TYPE_STATIC_TEST           13
#define RAKE_COMMAND_TYPE_DYNAMIC_TEST          14
#define RAKE_COMMAND_TYPE_TRAIN_REMOVE          15


//TRACK_COMMAND_TYPE
//RANGE         : NA
//UNIT          : NOT APPLICABLE
//PRECISION     : 1
//LEGAL_CHECK   : 1-9
//COMMENTS      :
#define TRACK_COMMAND_TYPE                                      UINT_8
#define TRACK_COMMAND_TYPE_SOFT_RESET_COMMAND                   1
#define TRACK_COMMAND_TYPE_MB_SETTIING_REQUEST_COMMAND          2
#define TRACK_COMMAND_TYPE_MB_RELEASE_REQUEST_COMMAND           3
#define TRACK_COMMAND_TYPE_MB_RELEASE_CONFIRMATION_COMMAND      4
#define TRACK_COMMAND_TYPE_MB_RELEASE_TLSR_COMMAND              5 // LINE 8
#define TRACK_COMMAND_TYPE_MB_RELEASE_TRSR_COMMAND              6 // LINE 8
#define TRACK_COMMAND_TYPE_AXLE_COUNTER_RESET_COMMAND           7 // LINE 8
#define TRACK_COMMAND_TYPE_MB_SETTING_REQUEST_COMMAND           8 // LINE 1
#define TRACK_COMMAND_TYPE_MB_SETTING_CONFIRMATION_COMMAND      9 // LINE 1


//SIGNAL_COMMAND_TYPE
//RANGE         : NA
//UNIT          : NOT APPLICABLE
//PRECISION     : 1
//LEGAL_CHECK   : 1-8
//COMMENTS      :
#define SIGNAL_COMMAND_TYPE                                     UINT_8
#define SIGNAL_COMMAND_TYPE_BLOCK_COMMAND                       1
#define SIGNAL_COMMAND_TYPE_BLOCK_RELEASE_REQUEST_COMMAND       2
#define SIGNAL_COMMAND_TYPE_BLOCK_RELEASE_CONF                  3
#define SIGNAL_COMMAND_TYPE_SIGNAL_OVERRIDE_COMMAND             4
#define SIGNAL_COMMAND_TYPE_SIGNAL_OVERRIDE_RELEASE_REQUEST     5
#define SIGNAL_COMMAND_TYPE_SIGNAL_OVERRIDE_RELEASE_CONF        6
#define SIGNAL_COMMAND_TYPE_AUTOMATIC_ROUTE_SETTING_ENABLE      7
#define SIGNAL_COMMAND_TYPE_AUTOMATIC_ROUTE_SETTING_DISABLE     8

//ROUTE_COMMAND_TYPE
//RANGE         : NA
//UNIT          : NOT APPLICABLE
//PRECISION     : 1
//LEGAL_CHECK   : 1-11
//COMMENTS      :
#define ROUTE_COMMAND_TYPE                                      UINT_8
#define ROUTE_COMMAND_TYPE_ROUTE_BLOCK_REQUEST_COMMAND          1   //block
#define ROUTE_COMMAND_TYPE_ROUTE_BLOCK_CONFIRMATION_COMMAND     11   //block confirm
#define ROUTE_COMMAND_TYPE_UNBLOCK_REQUEST                      2   // unblock
#define ROUTE_COMMAND_TYPE_UNBLOCK_CONFIRMATION                 3   // unblock confirm
#define ROUTE_COMMAND_TYPE_ROUTE_SET_COMMAND                    4
#define ROUTE_COMMAND_TYPE_ROUTE_RELEASE_COMMAND                5
#define ROUTE_COMMAND_TYPE_FLEET_SET_COMMAND                    6
#define ROUTE_COMMAND_TYPE_FLEET_RELEASE_COMMAND                7
#define ROUTE_COMMAND_TYPE_EMERGENCY_ROUTE_SETTING_COMMAND      8
#define ROUTE_COMMAND_TYPE_EMERGENCY_ROUTE_RELEASE_COMMAND      9
//#define ROUTE_COMMAND_TYPE_ROUTE_BLOCK_REQUEST_COMMAND          10  // LINE 8



//#define ROUTE_COMMAND_TYPE                                      UINT_8
//#define ROUTE_COMMAND_TYPE_ROUTE_BLOCK_COMMAND                  1   //block
//#define ROUTE_COMMAND_TYPE_ROUTE_BLOCK_CONFIRMATION_COMMAND     11   //block confirm
//#define ROUTE_COMMAND_TYPE_UNBLOCK_REQUEST                2   // unblock
//#define ROUTE_COMMAND_TYPE_UNBLOCK_CONFIRMATION                   3   // unblock confirm
//#define ROUTE_COMMAND_TYPE_ROUTE_SET_COMMAND                    4
//#define ROUTE_COMMAND_TYPE_ROUTE_RELEASE_COMMAND                5
//#define ROUTE_COMMAND_TYPE_FLEET_SET_COMMAND                    6
//#define ROUTE_COMMAND_TYPE_FLEET_RELEASE_COMMAND                7
//#define ROUTE_COMMAND_TYPE_EMERGENCY_ROUTE_SETTING_COMMAND      8
//#define ROUTE_COMMAND_TYPE_EMERGENCY_ROUTE_RELEASE_COMMAND      9
//#define ROUTE_COMMAND_TYPE_ROUTE_BLOCK_REQUEST_COMMAND          10  // LINE 8


//POINT_COMMAND_TYPE
//RANGE         : NA
//UNIT          : NOT APPLICABLE
//PRECISION     : 1
//LEGAL_CHECK   : 1-16
//COMMENTS      : POINT_BLOCK being used from LINE8 times in LINE1i.e. 3
#define POINT_COMMAND_TYPE                                                      UINT_8
#define POINT_COMMAND_TYPE_POINT_NORMAL                                         1
#define POINT_COMMAND_TYPE_POINT_REVERSE                                        2
#define POINT_COMMAND_TYPE_POINT_BLOCK_REQUEST                                  3 //LINE8
#define POINT_COMMAND_TYPE_POINT_BLOCK_RELEASE_REQUEST                          4
#define POINT_COMMAND_TYPE_POINT_BLOCK_RELEASE_CONF                             5
#define POINT_COMMAND_TYPE_POINT_MANUAL_AUTHORIZATION_COMMAND                   6
#define POINT_COMMAND_TYPE_MANUAL_AUTHORIZATION_RELEASE_REQUEST                 7
#define POINT_COMMAND_TYPE_MANUAL_AUTHORIZATION_RELEASE_CONF                    8
#define POINT_COMMAND_TYPE_SELF_NORMALIZATION_AUTH_CONFORMATION_REQUEST         9
#define POINT_COMMAND_TYPE_SELF_NORMALIZATION_AUTH_CONFORMATION_CONF            10
#define POINT_COMMAND_TYPE_SELF_NORMALIZATION_INHIBIT_CONFORMATION_REQUEST      11
#define POINT_COMMAND_TYPE_SELF_NORMALIZATION_INHIBIT_CONFORMATION_CONF         12
#define POINT_COMMAND_TYPE_EMERGENCY_POINT_OPERATION_COMMAND                    13  //LINE8
#define POINT_COMMAND_TYPE_EMERGENCY_POINT_OPERATION_CONFIRMATION_COMMAND       14  //LINE8
#define POINT_COMMAND_TYPE_POINT_BLOCK_REQUEST_COMMAND                          15  //LINE1
#define POINT_COMMAND_TYPE_POINT_BLOCK_SET_CONFIRMATION_COMMAND                 16  //LINE1


//GLOBAL_COMMAND_TYPE
//RANGE         : NA
//UNIT          : NOT APPLICABLE
//PRECISION     : 1
//LEGAL_CHECK   : 1-16
//COMMENTS      :
#define GLOBAL_COMMAND_TYPE                                 UINT_8
#define GLOBAL_COMMAND_TYPE_ATO_DEPARTURE_COMMAND           1
#define GLOBAL_COMMAND_TYPE_TRAIN_STOP_COMMAND              2
#define GLOBAL_COMMAND_TYPE_EB_RELEASE_COMMAND              3
#define GLOBAL_COMMAND_TYPE_PLATFORM_HOLD_COMMAND           4
#define GLOBAL_COMMAND_TYPE_TSR_COMMAND                     5
#define GLOBAL_COMMAND_TYPE_NO_ENTRY_COMMAND                6
#define GLOBAL_COMMAND_TYPE_LOW_ADHESION_SET_COMMAND        7
#define GLOBAL_COMMAND_TYPE_LOW_ADHESION_RELEASE_COMMAND    8
#define GLOBAL_COMMAND_TYPE_ZONE_TRAIN_STOP_COMMAND         9
#define GLOBAL_COMMAND_TYPE_ZONE_TRAIN_stop_RELEASE_COMMAND 10

//CYCLE_COMMAND_TYPE
//RANGE         : NA
//UNIT          : NOT APPLICABLE
//PRECISION     : 1
//LEGAL_CHECK   : 1-10
//COMMENTS      :
#define CYCLE_COMMAND_TYPE          UINT_8
#define CYCLE_COMMAND_TYPE_SET      1
#define CYCLE_COMMAND_TYPE_RELEASE  2


//TRACK_ROUTE_POINT_COMMAND_TYPE
//RANGE         : NA
//UNIT          : NOT APPLICABLE
//PRECISION     : 1
//LEGAL_CHECK   : 1-8
//COMMENTS      :
#define TRACK_ROUTE_POINT_COMMAND_TYPE                          UINT_8
#define TRACK_ROUTE_POINT_COMMAND_MB_SETTING_COMMAND            1
#define TRACK_ROUTE_POINT_COMMAND_MB_RELEASE_COMMAND            2
#define TRACK_ROUTE_POINT_COMMAND_ROUTE_BLOCK_COMMAND           3
#define TRACK_ROUTE_POINT_COMMAND_ROUTE_UNBLOCK_COMMAND         4
#define TRACK_ROUTE_POINT_COMMAND_POINT_AUTHORIZATION_COMMAND   5
#define TRACK_ROUTE_POINT_COMMAND_POINT_INHIBIT_COMMAND         6
#define TRACK_ROUTE_POINT_COMMAND_POINT_BLOCK_COMMAND           7
#define TRACK_ROUTE_POINT_COMMAND_POINT_UNBLOCK_COMMAND         8
#define TRACK_ROUTE_POINT_COMMAND_GLOBAL_SIGNAL_BLOCK_COMMAND   9
#define TRACK_ROUTE_POINT_COMMAND_GLOBAL_SIGNAL_UNBLOCK_COMMAND 10
//TRACK_ROUTE_POINT_COMMAND_TYPE
//RANGE         : NA
//UNIT          : NOT APPLICABLE
//PRECISION     : 1
//LEGAL_CHECK   : 1-8
//COMMENTS      :
#define TRACK_ROUTE_POINT_COMMAND_INTERNAL_TYPE                          UINT_8
#define TRACK_ROUTE_POINT_COMMAND_INTERNAL_MB_SETTING_COMMAND            51
#define TRACK_ROUTE_POINT_COMMAND_INTERNAL_MB_RELEASE_COMMAND            52
#define TRACK_ROUTE_POINT_COMMAND_INTERNAL_ROUTE_BLOCK_COMMAND           53
#define TRACK_ROUTE_POINT_COMMAND_INTERNAL_ROUTE_UNBLOCK_COMMAND         54
#define TRACK_ROUTE_POINT_COMMAND_INTERNAL_POINT_AUTHORIZATION_COMMAND   55
#define TRACK_ROUTE_POINT_COMMAND_INTERNAL_POINT_INHIBIT_COMMAND         56
#define TRACK_ROUTE_POINT_COMMAND_INTERNAL_POINT_BLOCK_COMMAND           57
#define TRACK_ROUTE_POINT_COMMAND_INTERNAL_POINT_UNBLOCK_COMMAND         58
#define TRACK_ROUTE_POINT_COMMAND_INTERNAL_GLOBAL_SIGNAL_BLOCK_COMMAND   59
#define TRACK_ROUTE_POINT_COMMAND_INTERNAL_GLOBAL_SIGNAL_UNBLOCK_COMMAND 60

//1-	Emergency Route (Mid-Way Reversal) Setting
//2-	Emergency Route (Mid-Way Reversal) Release
//3-	Manual Point Authorization Inhibit
//4-	Inhibit point self-normalization
//5-	Point Unblocking
//6-	Signal Unblocking Individually
//7-	Signal Unblocking Globally
//8-	Maintenance Unblocking
//9-	Route Unblocking
//10-	Enable Signal Override
//11-	Emergency Point Operation
//12-	Get Emergency Authority
//13-	Axle Counter Soft Reset
//SAFETY_COMMAND_TYPE
//RANGE         : NA
//UNIT          : NOT APPLICABLE
//PRECISION     : 1
//LEGAL_CHECK   : 1-8
//COMMENTS      :
#define SAFETY_COMMAND_TYPE                             UINT_8
#define SAFETY_COMMAND_TYPE_EMERGENCY_ROUTE_SET         1
#define SAFETY_COMMAND_TYPE_EMERGENCY_ROUTE_RELEASE     2
#define SAFETY_COMMAND_TYPE_MANUAL_POINT_INIHIBIT       3
#define SAFETY_COMMAND_TYPE_SELF_NORM_INHIBIT           4
#define SAFETY_COMMAND_TYPE_POINT_UNBLOCK               5
#define SAFETY_COMMAND_TYPE_SIGNAL_UNBLOCK_INDIVIDUAL   6
#define SAFETY_COMMAND_TYPE_SIGNAL_UNBLOCK_GLOBAL       7
#define SAFETY_COMMAND_TYPE_MAINTENANCE_UNBLOCK         8
#define SAFETY_COMMAND_TYPE_ROUTE_UNBLOCK               9
#define SAFETY_COMMAND_TYPE_SIGNAL_OVERRIDE             10
#define SAFETY_COMMAND_TYPE_EMERGENCY_POINT_OPS         11
#define SAFETY_COMMAND_TYPE_EMERGENCY_AUTHORITY         12
#define SAFETY_COMMAND_TYPE_AXLE_COUNTER_RESET          13


/// COMMAND_TYPES ////////////////////////////////////////////////////////////////////

#define MAX_NO_OF_CYCLES                                            UINT_16

#define USER_NAME 	UINT_8 
//LEGAL CHECK	5 - 25 Characters Alphabets
//Alphabets (A-Z, a-z), Numbers (0-9), spaces
//and underscores are allowed.

#define PASSWORD 	UINT_8 
//LEGAL CHECK	5 - 25 Characters Alphabets
//Alphabets (A-Z, a-z), Numbers (0-9),
//including all special characters. Only one
//space between words/alphabets.

#define LOGIN_LOGOUT 	UINT_8 
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	1-2
//COMMENTS	1- LOG IN

//NO OF BITS	1

#define STRING_50 	INT_8
#define NUM_STRING_50   50
#define ATC_ID 	UINT_8 
//PRECISION	1
//UNIT	NUMBER
//NO OF BITS	5
//LEGAL CHECK	


#define TSR_CODE 	UINT_8
//RANGE	NA
//UNIT	HOUR
//PRECISION	1
//LEGAL CHECK	
//COMMENTS	 0-160 km/h (1km/h unit)
//1bit = 1km/h



#define ENTITY_COMMAND_TYPE 	UINT_8

//NO OF BITS	8

#define ENTITY_TYPE 	UINT_8 
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	1-9
//COMMENTS	1- TRACK

//NO OF BITS	4

#define VIRTUAL_BLOCK_ID 	UINT_16 
//PRECISION	1
//UNIT	NUMBER
//COMMENTS	0 - Invalid value


//NO OF BITS	16

#define TRAIN_ID 	UINT_16
//PRECISION	1
//UNIT	NUMBER
//NO OF BITS	16 
//COMMENTS	Train ID(Upper 1byte)		1 -255: Destination platform ID

//Train ID(Lower 1byte)		1-159: Journey  ID
//other: Invalid value	

#define CONSIST_ID  UINT_8



#define RAKE_ID 	UINT_16 
//PRECISION	1
//UNIT	NUMBER
//COMMENTS	0- Invalid value

//NO OF BITS	16

// #define MAX_NO_OF_ATC_ZONE 	
//NO OF BITS	5
#define ERROR_CODE UINT_8

#define MAX_NO_OF_CBI_ZONE 	UINT_32

#define MAX_NO_OF_AUTHORITIES 	UINT_32

#define AREA_AUTHORITY_TYPE 	UINT_8 
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	1-15
//COMMENTS	1 - Line Overview Configuration
//NO OF BITS	4

#define ACTION_ID 	UINT_8 
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	1-3
//COMMENTS	1 - ADD
//NO OF BITS	2

#define MAX_NO_OF_USER_ACCOUNT 	UINT_32

#define MAX_NO_OF_VIRTUAL_BLOCKS 	UINT_32

#define VIRTUAL_BLOCK_COMMAND_TYPE 	UINT_8 
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	1-6
//COMMENTS	1- TSR APPLY COMMAND


//NO OF BITS	3

#define OPERATING_MODE_COMMAND 	UINT_8 
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	
//COMMENTS	000b-No directive



//NO OF BITS	3

#define LEFT_RIGHT 	UINT_8 
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	0-1
//COMMENTS	0- LEFT
//NO OF BITS	1

#define OCC_REMOTE_COMMAND_ID                   UINT_8
//LEGAL CHECK	
//UNIT	NUMBER
//PRECISION	1
//RANGE	
//COMMENTS	
#define No Command				0
#define Master Clock 			1
// All Panto Down 			2
// Panto Car 5 Down 		3
// Panto Car 2 Down 		4
// All Panto Up 			5
// Panto Car 5 Up			6
// Panto Car 2 Up			7
// Train Sleep set 		8
// Train Wake Up set 		9
// VCB Isolation Car 2 Set	10
// Both VCB Reset  		11
// Both VCB Close  		12
// Both VCB Open  			13
// Panto Car 5 Isolation Reset 	14
// Panto Car 2 Isolation Reset 	15
// Panto Car 5 Isolation Set 		16
// Panto Car 2 Isolation Set  		17
// (Spare)							18
// Parking brake Bypass Reset 		19
// Parking brake Bypass Set  		20
// VCB Trip Bypass Car 5 Reset  	21
// VCB Trip Bypass Car 2 Reset 	22
// VCB Trip Bypass Car 5 Set 		23
// VCB Trip Bypass Car 2 Set 		24
// VCB Isolation Car 5 Set  		25
// HVAC 2 (Car 2) Isolation Reset 	26
// HVAC 1 (Car 2) Isolation Reset 	27
// HVAC 2 (Car 2) Isolation Set 	28
// HVAC 1 (Car 2) Isolation Set 	29
// HVAC 2 (Car 6) Isolation Reset 	42
// HVAC 1 (Car 6) Isolation Reset 	43
// HVAC 2 (Car 6) Isolation Set 	44
// HVAC 1 (Car 6) Isolation Set 	45
// HVAC 2 (Car 5) Isolation Reset 	46
// HVAC 1 (Car 5) Isolation Reset 	47
// HVAC 2 (Car 5) Isolation Set 	48
// HVAC 1 (Car 5) Isolation Set 	49
// Call on light Off 				50
// Call on light On  				51
// Flasher light Off  				52
// Flasher light On 				53
// Dozing mode reset 				54
// Dozing mode set 				55
// Damper Reset  					56
// HVAC Reset  					57
// BPPSR (Brake Pipe Pressure Switch Relay) bypass control for traction bypass reset 	58
// BPPSR (Brake Pipe Pressure Switch Relay) bypass control for traction bypass set	59
#define Wash_Mode_reset  				60
#define Wash_Mode_set  					61
#define PABR_reset_clear  				62
#define PABR_reset  					63
#define Horn_Off  						64
// Horn On  						65
// (Spare)							67
// (Spare)							68
// (Spare)							69
// (Spare)							70
// (Spare)							71
// #define (Spare)							72
#define Door_Isolation_set				73
#define Door_Isolation_reset			74
#define Crew_ID							75  //Crew ID is set in 4 byte unsigned integer.
//#define Invalid							127 //Used in case that multiple bits is set to


//NO OF BITS	8

#define UP_DOWN 	UINT_8 
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	0-1
//COMMENTS	1- UP 0 - DOWN
//NO OF BITS	1

#define ADDITIONAL_INFO UINT_64
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	
//COMMENTS	 ////Bit Assignment of Additional Information for Door Isolation Set////

//    Bit name					byte pos	bit pos
// Car1 Door 8 Isolation set 	1st			0
// Car1 Door 7 Isolation set 				1
// Car1 Door 6 Isolation set				2
// Car1 Door 5 Isolation set 				3
// Car2 Door 8 Isolation set 				4
// Car2 Door 7 Isolation set 				5
// Car2 Door 6 Isolation set				6
// Car2 Door 5 Isolation set 				7
// Car4 Door 4 Isolation set 				4
// Car4 Door 2 Isolation set				6
// Car4 Door 1 Isolation set 				7
// Car5 Door 2 Isolation set				2
// Car5 Door 1 Isolation set 				3
// Car6 Door 4 Isolation set 				4
// Car6 Door 2 Isolation set				6
// Car6 Door 1 Isolation set 				7
// Car1 Door 1 Isolation set 		4th		0
// Car1 Door 2 Isolation set 				1
// Car1 Door 4 Isolation set 				3
// Car2 Door 1 Isolation set 				4
// Car2 Door 2 Isolation set 				5
// Car2 Door 4 Isolation set 				7
// Car4 Door 5 Isolation set 				4
// Car4 Door 6 Isolation set 				5
// Car4 Door 7 Isolation set				6
// Car4 Door 8 Isolation set 				7
// Car5 Door 5 Isolation set 		6th		0
// Car5 Door 6 Isolation set 				1
// Car5 Door 7 Isolation set				2
// Car5 Door 8 Isolation set 				3
// Car6 Door 5 Isolation set 				4
// Car6 Door 6 Isolation set 				5
// Car6 Door 7 Isolation set				6
// Car6 Door 8 Isolation set 				7

//// Bit Assignment of Additional Information for Door Isolation Clear////


// bit name					byte pos	bit pos
// Car1 Door 8 Isolation clear 	1st		0
// Car1 Door 7 Isolation clear 			1
// Car1 Door 6 Isolation clear 			2
// Car1 Door 5 Isolation clear 			3
// Car2 Door 8 Isolation clear 			4
// Car2 Door 7 Isolation clear 			5
// Car2 Door 6 Isolation clear 			6
// Car2 Door 5 Isolation clear 			7
// Car4 Door 4 Isolation clear 			4
// Car4 Door 2 Isolation clear 			6
// Car4 Door 1 Isolation clear 			7
// Car5 Door 2 Isolation clear 			2
// Car5 Door 1 Isolation clear 			3
// Car6 Door 4 Isolation clear 			4
// Car6 Door 2 Isolation clear 			6
// Car6 Door 1 Isolation clear 			7
// Car1 Door 1 Isolation clear 	4th		0
// Car1 Door 2 Isolation clear 			1
// Car1 Door 4 Isolation clear 			3
// Car2 Door 1 Isolation clear 			4
// Car2 Door 2 Isolation clear 			5
// Car2 Door 4 Isolation clear 			7
// Car4 Door 5 Isolation clear 			4
// Car4 Door 6 Isolation clear 			5
// Car4 Door 7 Isolation clear 			6
// Car4 Door 8 Isolation clear 			7
// Car5 Door 5 Isolation clear 	6th		0
// Car5 Door 6 Isolation clear 			1
// Car5 Door 7 Isolation clear 			2
// Car5 Door 8 Isolation clear 			3
// Car6 Door 5 Isolation clear 			4
// Car6 Door 6 Isolation clear 			5
// Car6 Door 7 Isolation clear 			6
// Car6 Door 8 Isolation clear 			7

//NO OF BITS	48

#define VRS_ID 	UINT_16
//PRECISION	1
//UNIT	NUMBER

#define VIRTUAL_BLOCK_OFFSET 	UINT_16
//RANGE	NA
//UNIT	HOUR
//PRECISION	1
//LEGAL CHECK	
//COMMENTS	 



//NO OF BITS	

#define ALARM_PRIORITY 	UINT_8 
//RANGE	NA
//UNIT	NUMBER
//PRECISION	1
//LEGAL CHECK	1-3
//COMMENTS	1- High
//NO OF BITS	2

#define ALARM_TYPE 	UINT_8 
//RANGE	NA
//UNIT	NUMBER
//PRECISION	1
//LEGAL CHECK	1-26
//COMMENTS	1- Train Delayed



//NO OF BITS	5

#define AVERAGE_SPEED 	UINT_8 
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	10-80
//COMMENTS	 



//NO OF BITS	7

#define CREW_NAME 	UINT_8 
//RANGE	NA
//UNIT	HOUR
//PRECISION	1
//LEGAL CHECK	5- 25 Characters
//COMMENTS	 



//NO OF BITS	

#define DAY 	UINT_8 
//RANGE	NA
//UNIT	HOUR
//PRECISION	1
//COMMENTS	 



//NO OF BITS	5

#define DELAY_DETECTION_THRESHOLD 	UINT_16 
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	0-999
//COMMENTS	 



//NO OF BITS	10

#define DEPARTURE_OFFSET 	UINT_16 
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	
//COMMENTS	 



//NO OF BITS	6

#define HEADWAY 	UINT_16 
//RANGE	NA
//UNIT	SECOND
//PRECISION	1
//LEGAL CHECK	90-1800
//COMMENTS	 



//NO OF BITS	11

#define INTERSTATION_STOP_DETECT_TIME 	UINT_16 
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	
//COMMENTS	 



//NO OF BITS	6

#define LINE_NUMBER 	UINT_8 
//PRECISION	1
//UNIT	NUMBER
//LEGAL CHECK	1-20
//NO OF BITS	4

#define MAX_NO_OF_RAKE_ID 	UINT_8 
//PRECISION	1
//UNIT	NUMBER

#define MAX_NO_OF_TRIPS 	UINT_8 
//PRECISION	1
//UNIT	NUMBER

#define MONTH 	UINT_8 
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	1-12
//COMMENTS	1-Jan



//NO OF BITS	4

#define ROLLING_STOCK_PROFILE 	UINT_8 
//RANGE	NA
//UNIT	NUMBER
//PRECISION	1
//LEGAL CHECK	1-4
//COMMENTS	1- 4 Car
//NO OF BITS	2

#define ROUTE_TRIGGER_OFFSET 	UINT_16 
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	0-999
//COMMENTS	 



//NO OF BITS	

#define RUNNING_TIME 	UINT_16 
//RANGE	NA
//UNIT	SECOND
//PRECISION	1
//LEGAL CHECK	0-999
//COMMENTS	 



//NO OF BITS	

#define SIGNAL_POSITION 	UINT_8 
//RANGE	NA
//UNIT	NUMBER
//PRECISION	1
//LEGAL CHECK	1-3
//COMMENTS	1- Left



//NO OF BITS	2

#define TRIP_ID 	UINT_8 
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	
//COMMENTS	
//NO OF BITS	

#define TRIP_NAME 	UINT_8 
//RANGE	NA
//UNIT	STRING
//PRECISION	
//LEGAL CHECK	0-20 char
//COMMENTS	
//NO OF BITS	

#define TUNNEL_LIMIT 	UINT_8 
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	0-3
//COMMENTS	 



//NO OF BITS	

#define WAKEUP_COMMAND_OFFSET 	UINT_16 
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	5- 18000
//COMMENTS	 



//NO OF BITS	

#define YEAR 	UINT_16 
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	1970-9999
//COMMENTS	 


#define CONFLICT_TIME UINT_16
//NO OF BITS	16
#define DWELL_TIME 	UINT_16
//RANGE	NA
//UNIT	SECOND
//PRECISION	1
//LEGAL CHECK	
//COMMENTS	0- invalid.            




//NO OF BITS	10

#define DYNAMIC_TEST_RESULT 	                 UINT_8

#define TSR_SETTING 	                          UINT_8
//COMMENTS	

//NO OF BITS	4
//LEGAL CHECK	

#define PSD_STATUS                          UINT_8
//NO OF BITS	4
//COMMENTS	 xxx1 : All PSD close & lock
// xx1x : All PSD open
// x1xx : Override (Interlock Platform)


#define MAX_NO_OF_EMERGENCY_SECTION 	UINT_16 
//COMMENTS	0- Invalid 
// Valid 1-4095 
//NO OF BITS	12

#define EMERGENCY_SECTION_ID 	UINT_16 
//PRECISION	1
//UNIT	NUMBER
//NO OF BITS	12
//COMMENTS	It is the ID that shows emergency section. 


#define MAX_NO_OF_STOPPING_POINT_IN_TRIP                            UINT_16

#define MAX_NO_OF_CONFLICTS 	UINT_8 

#define SERVER_ID 	UINT_8 
//PRECISION	1
//UNIT	NUMBER

#define HEADWAY_RESET_CYCLE                     0
#define HEADWAY_SET_CYCLE                       1

#define HEADWAY_CYCLE_SET_INTERNAL              1
#define HEADWAY_CYCLE_RESET_INTERNAL            2

#define HEADWAY_OPERATION_TYPE                  UINT_8
#define HEADWAY_OPERATION_TYPE_RESET_ROUTE      0 /// not specified

#define HEADWAY_OPERATION_TYPE_SET_CYCLE        2 /// set routes given
#define HEADWAY_OPERATION_TYPE_RESET_CYCLE      3 /// reset routes given

#define HEADWAY_OPERATION_TYPE_SAVE_SETTING     1 /// save the settings in DB (SAVE_SETTING:ATSD)
#define HEADWAY_OPERATION_TYPE_START_HEADWAY    4 /// start headway
#define HEADWAY_OPERATION_TYPE_END_HEADWAY      5 /// remove headway mode remove FLEET

//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	1-5
//COMMENTS	1 - SUBMIT

//NO OF BITS	3

#define TRAIN_REGULATION_MODE                   UINT_8
#define TRAIN_REGULATION_MODE_CUT_OFF           1
#define TRAIN_REGULATION_MODE_HEADWAY           2
#define TRAIN_REGULATION_MODE_TIME_TABLE_MODE 	3
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	1-3
//COMMENTS
//1 - CUT OFF
//2 - HEADWAY_MODE
//3 - TIME_TABLE_MODE

//NO OF BITS	2

#define ALARM_STATUS 	UINT_8 
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	1-4
//COMMENTS	1 - Active 

//NO OF BITS	2

#define ENTITY_ID 	UINT_16
//PRECISION	1
//UNIT	NUMBER
//NO OF BITS	10

#define EVENT_TYPE 	UINT_16
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	1-52
//COMMENTS	1- Global ATO Departure Command

//NO OF BITS	

#define MAX_NO_OF_EVENTS                UINT_8

#define JUNCTION_MANAGEMENT_MODE 	UINT_8 
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	1-6
//COMMENTS	1- First Come First Serve

//NO OF BITS	3

#define MAX_NO_OF_PACKETS 	UINT_8 
//NO OF BITS	8

#define PACKET_NUMBER 	UINT_8 
//NO OF BITS	8

#define DELAY 	UINT_16 
//LEGAL CHECK	
//UNIT	SECOND
//PRECISION	1
//RANGE	
//NO OF BITS	10

#define MAX_NO_OF_STOPPING_POINT_IN_JOURNEY 	UINT_16
#define MAX_NO_OF_DELAY 	                UINT_16
#define MEAN_DELAY_REPORT_TYPE 	                UINT_8 
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	1-3
//COMMENTS	1- Mean Delay Per Time Range Report

//NO OF BITS	

#define MAX_NO_OF_INTERSTATION_STOP_OCCURRENCE      UINT_16



#define EMERGENCY_SECTION_COMMAND_TYPE 	UINT_8 
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	1-2
//COMMENTS	1- Emergency Mode Set Command

//NO OF BITS	2

#define SIGNAL_TYPE 	UINT_8 
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	1-4
//COMMENTS	1. Physical

//NO OF BITS	2

#define SYSTEM_OPERATION_MODE 	UINT_8 
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	1-9
//COMMENTS	1. UTO Mode

//NO OF BITS	4

#define MAX_NO_OF_CREWS                                     UINT_8

#define REQ_TYPE 	UINT_8 
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	1-7
//COMMENTS	1 - ALL RAKES ID WITH ROLLING STOCK PROFILE INFO 
//NO OF BITS	

#define MAX_NO_OF_HOURS             INT_8

#define MAX_NO_OF_DIRECTION 	    8

#define PLATFORM_REFERENCE 	UINT_16 
//RANGE	NA
//UNIT	NUMBER
//PRECISION	1
//LEGAL CHECK	
//COMMENTS	
//NO OF BITS	

#define POWER_STATUS 	UINT_8 
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	1-3
//COMMENTS	1. Failure
//NO OF BITS	2

#define SPK_ID          UINT_8
//LEGAL CHECK	
//UNIT	NUMBER
//PRECISION	1
//RANGE	

#define SPK_COMMAND_TYPE 	UINT_8 
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	1-3
//COMMENTS	1- SPK Authorization Command




//NO OF BITS	2

#define PARTICULAR_CBI_COMMAND_TYPE 	UINT_8
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	1-5
//COMMENTS	1- All Signal Block Command
//all block 6
//all release 3
#define PARTICULAR_CBI_COMMAND_TYPE_ALL_BLOCK 1
#define PARTICULAR_CBI_COMMAND_TYPE_ALL_RELEASE 2
#define PARTICULAR_CBI_COMMAND_TYPE_ALL_SIGNAL_RELEASE_ACK 3
#define PARTICULAR_CBI_COMMAND_TYPE_ARSD_ALLOWED   4
#define PARTICULAR_CBI_COMMAND_TYPE_ARSD_DENIED    5
#define PARTICULAR_CBI_COMMAND_TYPE_ALL_SIGNAL_BLOCK_ACK   6

//NO OF BITS	3

#define TRACTION_ZONE_ID 	UINT_8 
//PRECISION	1
//UNIT	NUMBER

#define MAX_NO_OF_PLATFORM_DOORS                            UINT_16

#define PLATFORM_DOOR_ID                UINT_16
//LEGAL CHECK	1- 100
//UNIT	NUMBER
//PRECISION	1
//RANGE	0-255

#define TVS_ID              UINT_8
//LEGAL CHECK	1- 100
//UNIT	NUMBER
//PRECISION	1
//RANGE	0-255

#define WET_DRY_SETTING 	UINT_8 
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	
//COMMENTS	0000b : No command.

//NO OF BITS	4

#define REPORT_TYPE 	UINT_8 
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	1-15
//COMMENTS	1. Generate Mileage Report
//NO OF BITS	5

#define DISTANCE_IN_KILOMETER 	UINT_8 
//LEGAL CHECK	
//UNIT	NUMBER
//PRECISION	1
//RANGE	

#define DURATION_IN_MINUTES 	UINT_8 
//RANGE	NA
//UNIT	MINUTE
//PRECISION	1
//LEGAL CHECK	
//COMMENTS	 



//NO OF BITS	8

#define MAX_NO_OF_DAYS_IN_MONTH 	UINT_8 
//NO OF BITS	5

#define DURATION_IN_SECONDS 	UINT_8 
//RANGE	NA
//UNIT	SECOND
//PRECISION	1
//LEGAL CHECK	
//COMMENTS	 



//NO OF BITS	8

#define MAX_NO_OF_TRAINS           UINT_16

#define MAX_SPEED_COMMAND 	UINT_8 
//NO OF BITS	8
//COMMENTS	0 : is invalid.


#define DOOR_DIRECTION 	UINT_8 
//NO OF BITS	2
//COMMENTS	00 : not open the door



#define SYSTEM_EXCHANGE_COMMAND 	UINT_8 
//NO OF BITS	2
//COMMENTS	00 : not change




#define PASSENGER_DISPLAY_MESSAGE 	UINT_16 
//NO OF BITS	16
//COMMENTS	0  - Text Message nothing

#define NO_ENTRY_PRESET_SETTING UINT_8
//0000  no setting
//1000  no entry setting request
//1001  execute no entry request
//1101  no entry setting request cancel
//1011  no entry release request
//1010  excute no entry release
//1110  no entry release request cancel
// //////////////////////////////////////

#define DEPARTURE_DIRECTION 	UINT_8 
//NO OF BITS	2
//COMMENTS	00 : unknown




#define REGULATION_SPEED_COMMAND 	UINT_8 
//NO OF BITS	4
//COMMENTS	15-85 km/h (5km/h unit)


#define PLATFORM_CODE 	UINT_8 
//NO OF BITS	2
//COMMENTS	0: Invalid, or current platform is turnback section




#define ACOUNT_TYPE 	UINT_8 
//RANGE	NA
//UNIT	NOT APPLICABLE
//PRECISION	1
//LEGAL CHECK	1-15
//COMMENTS	1- OCC Chief Controller
//NO OF BITS	4

#define PSD_FAILURE 	UINT_8 
//NO OF BITS	2
//COMMENTS	00 : PSD failure 




#define PLATFORM_HOLD 	UINT_8 
//NO OF BITS	2
//COMMENTS	00 no suspend





#define ATC_ZONE_EMERGENCY_STOP 	UINT_8 
//NO OF BITS	2
//COMMENTS	00 no command (default)




#define ATC_REMOTE_RESET_COMMAND 	UINT_8 
//NO OF BITS	2
//COMMENTS	00  no command (default)





#define EMERGENCY_MODE_SETTING 	UINT_8 
//NO OF BITS	4
//COMMENTS	0000 no setting






#define DOOR_DIRECTION_copy 	UINT_8 
//NO OF BITS	2
//COMMENTS	00 : not open the door



#define TIME_TABLE_REQ_TYPE 	UINT_8 
//NO OF BITS	4
//COMMENTS	00  Display Time Table- command for Draft , Completed and Registered timetables .

#define ONEB_FLAG   UINT_8
#define ATS_FLAG    UINT_8 // 0- NA 1-CATS 2-LATS

#define MAX_NO_OF_TIMETABLE             UINT_16

#define TIMETABLE_STATE                 UINT_8
//NO OF BITS	2
//COMMENTS	00  Completed

#define MAX_TRIP_ID_STR_INTERNAL        10
#define MAX_JOURNEY_ID_STR_INTERNAL     10
#define MAX_TIME_TABLE_NAME_STR         250

#define COL_JOURNEY_TRIP_TRAIN_ID           1
#define COL_JOURNEY_TRIP_TRIP_ID            2
#define COL_JOURNEY_TRIP_STATION_ID         3
#define COL_JOURNEY_TRIP_PLATFORM_ID        4
#define COL_JOURNEY_TRIP_CREW_ID            5
#define COL_JOURNEY_TRIP_SCHD_ARR           6
#define COL_JOURNEY_TRIP_SCHD_DEP           7
#define COL_JOURNEY_TRIP_DWELL_TIME         8
#define COL_JOURNEY_TRIP_PERFOR_REG         9
#define COL_JOURNEY_TRIP_SERV_TYPE          10
#define COL_JOURNEY_TRIP_ACT_ARR            11
#define COL_JOURNEY_TRIP_ACT_DEP            12
#define COL_JOURNEY_TRIP_ACT_PERFOR_REG     13
#define COL_JOURNEY_TRIP_DIRECTION          14
#define COL_JOURNEY_TRIP_EST_ARR            15
#define COL_JOURNEY_TRIP_EST_DEP            16


#define SUBCOL_JOURNEY_TRIP_HOUR            1
#define SUBCOL_JOURNEY_TRIP_MIN             2
#define SUBCOL_JOURNEY_TRIP_SEC             3

#define SHELVE_TIME_TABLE               0
#define AUTO_COMPLETION_TIME_TABLE      1
#define INTERMEDIATE_TIME_TABLE         2

#define MAX_JOUNERY_ID_IRS              200
#define MAX_NO_OF_ROWS_PER_JOURNEY      2000
#define MAX_NO_OF_TRIPS_PER_JOURNEY     200
#define MAX_NO_OF_STOPPING_POINT_ID     286 //200 //@info : changed as a result of shivani mam and DMRC discussion
#define MAX_TRIP_ID_NAME_TTV            5
#define DUMMMY_4_BIT                    UINT_8

#define MAX_UPDATE_ONLINE_TIMETABLE             50
#define DISPLAY_TIME_TABLE                      0
#define DELETE_TIME_TABLE                       1
#define REQ_TYPE_REGISTER_TIME_TABLE            2
#define REQ_TYPE_LOAD_SWITCH_TO_TIME_TABLE_MODE 3

#define TIME_TABLE_SAVE         1

#define DWELLTIMEVALUESET1  30
#define DWELLTIMEVALUESET2  45
#define DWELLTIMEVALUESET3  60

#define TRACK_PASSAGE_THRESHOLD     600//50

#define POINT_POSITION_NORMAL           1
#define POINT_POSITION_REVERSE          2

#define DIRECTION_TIME_TABLE_LEFT       1
#define DIRECTION_TIME_TABLE_RIGHT      2

#define DIRECTION_RIGHT               1
#define DIRECTION_LEFT                2

#define DIRECTION_HEADWAY_RIGHT       1
#define DIRECTION_HEADWAY_LEFT        2

#define DIRECTION_LEFT_XML      1
#define DIRECTION_RIGHT_XML     0

#define DIRECTION_LEFT_ATC_XML      1
#define DIRECTION_RIGHT_ATC_XML     2

#define IS_TRK_ON_DOWNLINE  1
#define IS_TRK_ON_UPLINE    2

#define IS_PLAT_ON_UPLINE    1
#define IS_PLAT_ON_DOWNLINE  2

#define DOWNLINE            1  //used interchangebly for right side movement and physical track line called downline
#define UPLINE              2  //used interchangebly for left side movement and physical track line called upline

#define DOWNLINE_NORMAL             1
#define DOWNLINE_REVERSE            2
#define UPLINE_NORMAL               3
#define UPLINE_REVERSE              4
#define CROSSOVER                   5
#define INTERSTATION_STOP_TIME      5//60

#define TRAIN_CAB                       UINT_16
#define ACTIVE_CAB_DIRECTION            UINT_8
#define RADIO_ID                        UINT_64
#define PERCENTAGE                      UINT_8

#define SERVER_HEALTH_STATUS            UINT_8
#define PIDS_PAS_ID                     UINT_8
#define RADIO_SERVER_ID                 UINT_8
#define CBI_UNIT_STATUS                 UINT_8
#define CBI_CHANGEOVER_STATUS           UINT_8
//#define RADIO_SERVER_ID                 UINT_8
#define DEFAULT_P0_STOPPED_TIME         1//21
//#define CENTRAL_ATS_MODE                1   //As per IRS
//#define LOCAL_ATS_MODE                  2   //As per IRS
#define LOCAL_ATS_MODE_CENTRAL_HEALTHY          3   //Local Constant - Not as per IRS
#define LOCAL_ATS_MODE_CENTRAL_UNHEALTHY        4   //Local Constant - Not as per IRS

#define ADD_OCCPANCY        0
#define REMOVE_OCCPANCY     1

#define ADD_FROM_SELF_ATSS          0
#define ADD_FROM_REMOTE_ATSS        1
#define ADD_FROM_RAKE_ASSIGN        2


//16Aug2021
#define MAXIMUM_CENTRAL_ATS_LEVEL               10
#define ATS_NO_CONTROL_WITH_CATS_OR_LATS       0
#define ATS_CONTROL_WITH_CATS                  1
#define ATS_CONTROL_WITH_LATS                  2

#define ROUTE_NAME_SIZE                         15

#define PL_TB_TYPE_NORMAL       0
#define PL_TB_TYPE_SIDING       2
#define PL_TB_TYPE_TURNBACK     3

#define LEVEL_ID        UINT_16
#define MODULE_ID       UINT_16
#define WS_INDEX        UINT_16
#define PORT_NO         UINT_16
//24Aug2021
#define MAX_CHECKPOINT_OCCUPANY_DATA            25
//data_comm_mode for SendDataToUDP
#define DATA_COMM_MODE_REMOTE                   1
#define DATA_COMM_MODE_CATS_CHECKPOINT          2
#define DATA_COMM_MODE_LATS_CHECKPOINT          3
#define DATA_COMM_MODE_SPECIFIC_IP              4
//applicate_state
#define CSCI_STATE_TEMP                         2
#define CSCI_STATE_ACTIVE                       1
#define CSCI_STATE_PASSIVE                      0
//24Aug2021
#define MAX_CHECKPOINT_OCCUPANY_DATA            25

#define ROUTE_NAME_SIZE                         15

#define MAX_NUM_OF_COMMAND_TYPES                20

#define ATR_MODE_OFF 0
#define ATR_MODE_ON  1






/// CBI BITs ENUMERATIONS

#define CBI_TRK_OCCUPIED                    0
#define CBI_TRK_FREE                        1

#define MB_SET                              0
#define MB_FREE                             1

#define FLEET_SET                           1
#define FLEET_UNSET                         0

#define ROUTE_SET                           1
#define ROUTE_UNSET                         0

#define ROUTE_BLOCK                         0
#define ROUTE_UNBLOCK                       1

#define POINT_BLOCK                         0
#define POINT_UNBLOCK                       1

#define SELF_NORM_BIT_SET                   1
#define SELF_NORM_BIT_UNSET                 0

#define GSB_SET                             0
#define GSB_UNSET                           1

#define UPS_OPERATIONAL                     0
#define UPS_INACTIVE                        1
#define UPS_NOT_AVAILABLE                   2

#define EKT_INSERTED                        1
#define EKT_RELEASED                        0

#define MAX_NUM_PLATFORM_PAIR_TB            5


#define CBI_ON_OFF_EVENT_INIT               0
#define CBI_ON_OFF_EVENT_ON                 1
#define CBI_ON_OFF_EVENT_OFF                2
#define CBI_ON_OFF_EVENT_MAX_NUMBER         20
#define CBI_ON_OFF_EVENT_INIT_SUBTRACT      100

#define COMM_DETAILS_CATS                    1
#define COMM_DETAILS_LATS                    2
#define COMM_DETAILS_ALL                     3

#define TSR_PERIODIC_DETAILS                 4
#define SHELVE_OWS_ID                           200
#define CHECKPOINT_OWS_ID                       0

#define DEFAULT_RUNNING_TIME_BETWEEN_PLATFORMS  90
#define DEFAULT_DWELL_TIME_PLATFORM             30
#define DWELL_TIME_SET1                         1
#define DWELL_TIME_SET2                         2
#define DWELL_TIME_SET3                         3


#define EVENT_STRING_SYSTEM                     0
#define EVENT_STRING_USER                       1

#define DONT_CARE_ACTIVATED                        1
#define DONT_CARE_DEACTIVATED                      0

#endif
