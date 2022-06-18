#ifndef ATSS_DBA_DATA_H
#define ATSS_DBA_DATA_H
#include "ATSS_Includes.h"

class ATSS_DBData
{
private:
    pthread_mutex_t rolling_stock_lock;
    pthread_mutex_t junction_info_lock;

    STRUCT_INIT_SYSTEM_PERFORMANCE_RUNNING_TIME_INFO    performance_running_time_info;

    STRUCT_INIT_SYSTEM_TRAIN_ID_INFO                    train_id_info;
    STRUCT_INIT_SYSTEM_CREW_INFO                        crew_info;
    STRUCT_INIT_SYSTEM_JUNCTION_MODE_INFO               junction_mode_info;
    STRUCT_SYSTEM_ROLLING_STOCK_INFO                    rolling_stock_info_internal;
    STRUCT_INIT_SYSTEM_ROLLING_STOCK_INFO               rolling_stock_info;
    STRUCT_INIT_SYSTEM_ALARM_PRIORITY_INFO              alarm_priority_info;
    STRUCT_INIT_SYSTEM_PARAMETER_INFO                   parameter_info;

    std::multimap<RAKE_ID,STRUCT_ROLLING_STOCK_INFO>ROLLING_STOCK_MAP;
    std::multimap<UINT_32,STRUCT_PERFORMANCE_RUNNING_TIME>RUNNING_TIME_MAP;
    std::multimap<PLATFORM_ID,STRUCT_PLATFORM_DWELL_TIME_SET>DWELL_TIME_MAP;

    QMap<STATION_ID,STRUCT_JUNCTION_MODE_INFO>JUNCTION_MODE_INFO_MAP;

public:
    ATSS_DBData();

    /* Utility Functions */
    UINT_8 ValidateMessageHeader(STRUCT_GENERAL_MESSAGE_ATSS  &msg, INT_32 &received_bytes, INT_32 expected_length);
    UINT_8 ValidateData(UINT_8 variable, UINT_8 min_value, UINT_8 max_value);

};

#endif
