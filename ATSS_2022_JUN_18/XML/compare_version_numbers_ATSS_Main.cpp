#include "inc/ATSS_Includes.h"

ATSS_DBData DBData_obj;
ATSS_Communication atss_communication_obj;
ATSS_Utility utility_obj;
ATSS_XMLConfig xml_config;
ATSS_TrainData train_obj;
ATSS_TimeTable time_table_obj;
ATSS_MessageProcessor msg_processor_obj;
ATSS_PIDS_PAS pids_pas_class_obj;
ATSS_POINT_INFO atss_point_info_obj;
ATSS_PTI_PROCESSOR atss_pti_processor_obj;
ATSS_ATC_PROCESSING atss_atc_processing_obj;
ATSS_HEADWAY_MODE atss_headway_mode_obj;
ATSS_USER_AUTHORITY atss_user_authority_obj;


void PrintData(INT_8 *textstr, INT_32 textcount, UINT_8 new_line_count, UINT_8 tab_count, UINT_8 syslog_index=LOG_CRITICAL)
{
    utility_obj.PrintData(textstr, textcount, new_line_count, tab_count, syslog_index);
}

void Test();

void* PISPASThread(void*)
{
    void* k = NULL;

    INT_8 msg[MAX_SIZE_PACKET] = {0};
    INT_8 print_str[MAX_PRINT_STR] = {0};

    UINT_8 syslog = LOG_EXTRA_NIMP_TTO;

    INT_32 textcnt = 0;

    int count = 0;

    ATC_ID_STORAGE atc;
    STRUCT_EQUIPMENT_STATUS_REQUEST equipment;
    STRUCT_ATSS_PC_TSR_STATUS_MSG tsr_status;
    memset(&atc,0,sizeof(atc));
    memset(&tsr_status,0,sizeof(tsr_status));
    memset(&equipment,0,sizeof(equipment));

    count                               = xml_config.getATCCount();
    atc                                 = xml_config.getATCDetails();
    equipment.msg_hdr.dest_id           = CSCI_PC;
    equipment.msg_hdr.source_id         = CSCI_ATSS;
    equipment.msg_hdr.message_id        = ATSS_PC_ATC_EQUIPMENT_STATUS;
    equipment.msg_hdr.message_length    = sizeof(equipment);

    tsr_status.struct_message_header.dest_id           = CSCI_PC;
    tsr_status.struct_message_header.source_id         = CSCI_ATSS;
    tsr_status.struct_message_header.message_id        = ATSS_PC_TSR_STATUS_MSG;
    tsr_status.struct_message_header.no_of_packets     = 1;
    tsr_status.struct_message_header.packet_number     = 1;
    tsr_status.struct_message_header.message_length    = sizeof(tsr_status);

    textcnt = sprintf(print_str,"\n PIDS_PAS_THREAD:\t\t\tstarted");
    PrintData(print_str,textcnt,0,0,LOG_FILE_ONLY);

    UINT_8 check_auto_completion_count = 0;
    UINT_8 sleep_timer = 0;

    while(1)
    {

        /// health msg every MINUTE
        if(sleep_timer%6==0)
        {
            for(int q = 0;q < count; q++)
            {
                /// EQUIPMENT STATUS REQUEST
                equipment.atc_ID = atc.atc_ID[q];
                memcpy(&msg,&equipment,sizeof(equipment));
                //                atss_communication_obj.SendDataToPC(msg,sizeof(equipment),syslog);

                /// TSR STATUS
                tsr_status.atc_id   = atc.atc_ID[q];
                memcpy(&msg,&tsr_status,sizeof(tsr_status));
                //                atss_communication_obj.SendDataToPC(msg,sizeof(tsr_status),syslog);
            }
        }

        /// every 10 seconds
        /// PIDS_PAS messages
        TRAIN_REGULATION_MODE mode = msg_processor_obj.GetTrainRegulationMode();

        if(mode== TRAIN_REGULATION_MODE_TIME_TABLE_MODE)
        {
            pids_pas_class_obj.processNextArrivalPidsPas();
            pids_pas_class_obj.processNextThreeDepartures();
            check_auto_completion_count++;
            if(check_auto_completion_count >= 3)
            {
                time_table_obj.CheckAutoCompletionOnlineTimeTable();
                check_auto_completion_count = 0;
            }
        }
        else if(mode == TRAIN_REGULATION_MODE_HEADWAY)
        {
            pids_pas_class_obj.InitialiseHeadwayNextThreeArrDep();
            pids_pas_class_obj.processHeadwayNextArrivalPidsPas();
            pids_pas_class_obj.processHeadwayNextThreeDepartures();
        }
        /// 10 seconds SLEEP

        if(sleep_timer%3==0)
        {
            STRING_50 comments[STRING_FIFTY] = {};
            STRUCT_DMRC_ITR_STN_CTRL_DATA struct_idr_stn_ctrl;
            bool isc_reponse;

            for(UINT_8 cbi_id=0; cbi_id<CBI_ON_OFF_EVENT_MAX_NUMBER; cbi_id++)
            {
                if(msg_processor_obj.GetCbiOnOffEvent(cbi_id)==CBI_ON_OFF_EVENT_ON)
                {
                    msg_processor_obj.SetCbiOnOffEvent(cbi_id,CBI_ON_OFF_EVENT_OFF);
                }
                else if(msg_processor_obj.GetCbiOnOffEvent(cbi_id)==CBI_ON_OFF_EVENT_OFF)
                {
                    isc_reponse = xml_config.GetItrStnCtrlData(cbi_id+CBI_ON_OFF_EVENT_INIT_SUBTRACT,struct_idr_stn_ctrl);
                    if(isc_reponse==true)
                    {
                        sprintf(comments,"CBI-%s Failure Detected", struct_idr_stn_ctrl.cbi_name);
                    }
                    else
                    {
                        sprintf(comments,"CBI-%d Failure Detected", cbi_id+CBI_ON_OFF_EVENT_INIT_SUBTRACT);
                    }
                    msg_processor_obj.SendEventMessage((cbi_id+CBI_ON_OFF_EVENT_INIT_SUBTRACT), 0, 0, 0,0,comments);
                    msg_processor_obj.SetCbiOnOffEvent(cbi_id,CBI_ON_OFF_EVENT_INIT);
                }
            }
        }


        if(atss_communication_obj.GetDataLoggerFlag()==true)
        {
            if(atss_communication_obj.GetDataLoggerAliveCounter()>=3)
            {
                //Data Logger Alive forced reset
                atss_communication_obj.SetDataLoggerFlag(false);
                atss_communication_obj.SetDataLoggerAliveCounter(0);
                textcnt = sprintf(print_str,"\nCommunication with Data Logger Stopped flag=%d, counter=%d",
                                  atss_communication_obj.GetDataLoggerFlag(),
                                  atss_communication_obj.GetDataLoggerAliveCounter());
                PrintData(print_str,textcnt,0,0,LOG_ATSS_INFO);
            }
            else
            {
                atss_communication_obj.IncrementDataLoggerAliveCounter();
                //                textcnt = sprintf(print_str,"\nIncrementDataLoggerAliveCounter=%d",atss_communication_obj.GetDataLoggerAliveCounter());
                //                PrintData(print_str,textcnt,0,0,LOG_ATSS_INFO);
            }
        }

        sleep_timer++;

        sleep(10);
    }
    return k;
}


void* CommandAckThread(void*)
{
    ///void* k = NULL;
    INT_8 print_str[MAX_PRINT_STR] = {0};
    INT_32 textcnt = 0;

    textcnt = sprintf(print_str,"\n COMMAND_ACK_THREAD:\t\t\tstarted");
    PrintData(print_str,textcnt,0,0,LOG_FILE_ONLY);

    while(1)
    {
        sleep(1);
        msg_processor_obj.checkAllCmdAck();
        route_set_processing_obj.DwellTimeAndInterstationStopInOccupiedTrackMap();
    }
    ///return k;
}

void CommandAckSTDThread(void)
{
    ///void* k = NULL;
    INT_8 print_str[MAX_PRINT_STR] = {0};
    INT_32 textcnt = 0;

    textcnt = sprintf(print_str,"\n COMMAND_ACK_THREAD:\t\t\tstarted");
    PrintData(print_str,textcnt,0,0,LOG_FILE_ONLY);

    while(1)
    {
        sleep(1);
        msg_processor_obj.checkAllCmdAck();
        route_set_processing_obj.DwellTimeAndInterstationStopInOccupiedTrackMap();
    }
    ///return k;
}

void* InitCheckThread(void*)
{
    int timeout = 0;
    void* k = NULL;
    INT_8 print_str[MAX_PRINT_STR] = {0};

    INT_32 textcnt = 0;

    textcnt = sprintf(print_str,"\n INIT_CHECK_THREAD:\t\t\tstarted");
    PrintData(print_str,textcnt,0,0,LOG_FILE_ONLY);

    ///@uncomment
    //while(msg_processor_obj.GetInitializationFlag() != true)
    {
        //initiallization not completed
        sleep(1);
        if(timeout%SECONDS_TO_REQUEST_INIT==0) //every "SECONDS_TO_REQUEST_INIT" seconds a new request
        {
            DBData_obj.RequestInitData();
        }
        timeout++;
    }
    //    textcnt = sprintf(print_str,"\n INIT_CHECK_THREAD:\t\t\tended");
    //    PrintData(print_str,textcnt,0,0,LOG_ATSS_INFO);
    //initiallization thread ends
    return k;
}

void* CBIMsgsThread(void*)
{
    void* k = NULL;
    bool return_flag = false;
    INT_8 print_str[MAX_PRINT_STR] = {0};

}


void* PTIThread(void*)
{
    void* k = NULL;
    //    int time_seconds = 0;

    INT_8 print_str[MAX_PRINT_STR] = {0};
    INT_32 textcnt = 0;

    textcnt = sprintf(print_str,"\n PTI_ACK_THREAD:\t\tstarted");
    PrintData(print_str,textcnt,0,0,LOG_FILE_ONLY);

    while(1)
    {
        msg_processor_obj.CheckTrainInPTIList();

        /*
         * @info just for checking
         * @comment
         *
         * /////////////////////////////////////////////////////////////////////////////////////////////////
         */

        sleep(1);
    }

    return k;
}

void InitCheckSTDThread(void)
{
    int timeout = 0;

    INT_8 print_str[MAX_PRINT_STR] = {0};

    INT_32 textcnt = 0;

    textcnt = sprintf(print_str,"\n INIT_CHECK_THREAD:\t\t\tstarted");
    PrintData(print_str,textcnt,0,0,LOG_FILE_ONLY);

    ///@uncomment
    //while(msg_processor_obj.GetInitializationFlag() != true)
    {
        //initiallization not completed
        sleep(1);
        if(timeout%SECONDS_TO_REQUEST_INIT==0) //every "SECONDS_TO_REQUEST_INIT" seconds a new request
        {
            DBData_obj.RequestInitData();
        }
        timeout++;
    }
    //    textcnt = sprintf(print_str,"\n INIT_CHECK_THREAD:\t\t\tended");
    //    PrintData(print_str,textcnt,0,0,LOG_ATSS_INFO);
    //initiallization thread ends

}
void ReceiveThreadProcedure(void)
{
    INT_8 print_str[MAX_PRINT_STR] = {0};
    INT_32 textcnt = 0;

    textcnt = sprintf(print_str,"\n TIME_TABLE_PROCESSING_THREAD:\t\tstarted");
    PrintData(print_str,textcnt,0,0,LOG_FILE_ONLY);

    while (1)
    {
        msg_processor_obj.GetTimeTableQueueMsg();
        sleep(1);
    }
}
void PTISTDThread(void)
{
    //    int time_seconds = 0;

    INT_8 print_str[MAX_PRINT_STR] = {0};
    INT_32 textcnt = 0;

    textcnt = sprintf(print_str,"\n PTI_ACK_THREAD:\t\tstarted");
    PrintData(print_str,textcnt,0,0,LOG_FILE_ONLY);

    while(1)
    {
        msg_processor_obj.CheckTrainInPTIList();

        /*
         * @info just for checking
         * @comment
         *
         * /////////////////////////////////////////////////////////////////////////////////////////////////
         */

        sleep(1);
    }

}

void PISPASSTDThread(void)
{

    INT_8 msg[MAX_SIZE_PACKET] = {0};
    INT_8 print_str[MAX_PRINT_STR] = {0};

    UINT_8 syslog = LOG_EXTRA_NIMP_TTO;

    INT_32 textcnt = 0;

    int count = 0;

    ATC_ID_STORAGE atc;
    STRUCT_EQUIPMENT_STATUS_REQUEST equipment;
    STRUCT_ATSS_PC_TSR_STATUS_MSG tsr_status;
    memset(&atc,0,sizeof(atc));
    memset(&tsr_status,0,sizeof(tsr_status));
    memset(&equipment,0,sizeof(equipment));

    count                               = xml_config.getATCCount();
    atc                                 = xml_config.getATCDetails();
    equipment.msg_hdr.dest_id           = CSCI_PC;
    equipment.msg_hdr.source_id         = CSCI_ATSS;
    equipment.msg_hdr.message_id        = ATSS_PC_ATC_EQUIPMENT_STATUS;
    equipment.msg_hdr.message_length    = sizeof(equipment);

    tsr_status.struct_message_header.dest_id           = CSCI_PC;
    tsr_status.struct_message_header.source_id         = CSCI_ATSS;
    tsr_status.struct_message_header.message_id        = ATSS_PC_TSR_STATUS_MSG;
    tsr_status.struct_message_header.no_of_packets     = 1;
    tsr_status.struct_message_header.packet_number     = 1;
    tsr_status.struct_message_header.message_length    = sizeof(tsr_status);

    textcnt = sprintf(print_str,"\n PIDS_PAS_THREAD:\t\t\tstarted");
    PrintData(print_str,textcnt,0,0,LOG_FILE_ONLY);

    UINT_8 check_auto_completion_count = 0;
    UINT_8 sleep_timer = 0;

    while(1)
    {

        /// health msg every MINUTE
        if(sleep_timer%6==0)
        {
            for(int q = 0;q < count; q++)
            {
                /// EQUIPMENT STATUS REQUEST
                equipment.atc_ID = atc.atc_ID[q];
                memcpy(&msg,&equipment,sizeof(equipment));
                //                atss_communication_obj.SendDataToPC(msg,sizeof(equipment),syslog);

                /// TSR STATUS
                tsr_status.atc_id   = atc.atc_ID[q];
                memcpy(&msg,&tsr_status,sizeof(tsr_status));
                //                atss_communication_obj.SendDataToPC(msg,sizeof(tsr_status),syslog);
            }
        }

        /// every 10 seconds
        /// PIDS_PAS messages
        TRAIN_REGULATION_MODE mode = msg_processor_obj.GetTrainRegulationMode();

        if(mode== TRAIN_REGULATION_MODE_TIME_TABLE_MODE)
        {
            pids_pas_class_obj.processNextArrivalPidsPas();
            pids_pas_class_obj.processNextThreeDepartures();
            check_auto_completion_count++;
            if(check_auto_completion_count >= 3)
            {
                time_table_obj.CheckAutoCompletionOnlineTimeTable();
                check_auto_completion_count = 0;
            }
        }
        else if(mode == TRAIN_REGULATION_MODE_HEADWAY)
        {
            pids_pas_class_obj.InitialiseHeadwayNextThreeArrDep();
            pids_pas_class_obj.processHeadwayNextArrivalPidsPas();
            pids_pas_class_obj.processHeadwayNextThreeDepartures();
        }
        /// 10 seconds SLEEP

        if(sleep_timer%3==0)
        {
            STRING_50 comments[STRING_FIFTY] = {};
            STRUCT_DMRC_ITR_STN_CTRL_DATA struct_idr_stn_ctrl;
            bool isc_reponse;

            for(UINT_8 cbi_id=0; cbi_id<CBI_ON_OFF_EVENT_MAX_NUMBER; cbi_id++)
            {
                if(msg_processor_obj.GetCbiOnOffEvent(cbi_id)==CBI_ON_OFF_EVENT_ON)
                {
                    msg_processor_obj.SetCbiOnOffEvent(cbi_id,CBI_ON_OFF_EVENT_OFF);
                }
                else if(msg_processor_obj.GetCbiOnOffEvent(cbi_id)==CBI_ON_OFF_EVENT_OFF)
                {
                    isc_reponse = xml_config.GetItrStnCtrlData(cbi_id+CBI_ON_OFF_EVENT_INIT_SUBTRACT,struct_idr_stn_ctrl);
                    if(isc_reponse==true)
                    {
                        sprintf(comments,"CBI-%s Failure Detected", struct_idr_stn_ctrl.cbi_name);
                    }
                    else
                    {
                        sprintf(comments,"CBI-%d Failure Detected", cbi_id+CBI_ON_OFF_EVENT_INIT_SUBTRACT);
                    }
                    msg_processor_obj.SendEventMessage((cbi_id+CBI_ON_OFF_EVENT_INIT_SUBTRACT), 0, 0, 0,0,comments);
                    msg_processor_obj.SetCbiOnOffEvent(cbi_id,CBI_ON_OFF_EVENT_INIT);
                }
            }
        }


        if(atss_communication_obj.GetDataLoggerFlag()==true)
        {
            if(atss_communication_obj.GetDataLoggerAliveCounter()>=3)
            {
                //Data Logger Alive forced reset
                atss_communication_obj.SetDataLoggerFlag(false);
                atss_communication_obj.SetDataLoggerAliveCounter(0);
                textcnt = sprintf(print_str,"\nCommunication with Data Logger Stopped flag=%d, counter=%d",
                                  atss_communication_obj.GetDataLoggerFlag(),
                                  atss_communication_obj.GetDataLoggerAliveCounter());
                PrintData(print_str,textcnt,0,0,LOG_ATSS_INFO);
            }
            else
            {
                atss_communication_obj.IncrementDataLoggerAliveCounter();
                //                textcnt = sprintf(print_str,"\nIncrementDataLoggerAliveCounter=%d",atss_communication_obj.GetDataLoggerAliveCounter());
                //                PrintData(print_str,textcnt,0,0,LOG_ATSS_INFO);
            }
        }

        sleep_timer++;

        sleep(10);
    }

}

void ReceiveUDPThreadProcedure(void)
{
    INT_8 print_str[MAX_PRINT_STR] = {0};
    INT_32 textcnt = 0;

    textcnt = sprintf(print_str,"\n RECEIVE_UDP_THREAD:\t\tstarted");
    PrintData(print_str,textcnt,0,0,LOG_FILE_ONLY);

    while (1)
    {
        atss_communication_obj.RecieveDataFromUDP();
    }
}

bool CreateInitCheckThread(pthread_attr_t &thread_attr_atss_channel, pthread_t &thread_id_atss_channel)
{
    bool return_flag = true;
    UINT_8 tcnt = 0;
    UINT_8 nlcnt = 1;
    INT_8 print_str[MAX_PRINT_STR] = {0};
    INT_32 textcnt = 0;

    struct sched_param struct_sched_param;
    struct_sched_param.sched_priority = SCHED_RR_PRIORITY;

    if (pthread_attr_init(&thread_attr_atss_channel) == POSIX_FAIL)
    {
        perror("ERROR - ");
        textcnt = sprintf(print_str,"ERROR-thread_attr_atss_channelthread");
        PrintData(print_str,textcnt,nlcnt,tcnt);
        return_flag=false;
    }
    if(return_flag==true)
    {
        pthread_attr_setschedparam(&thread_attr_atss_channel, &struct_sched_param);
        if(pthread_attr_setschedpolicy(&thread_attr_atss_channel, SCHED_RR) == POSIX_FAIL)
        {
            perror("ERROR - ");
            textcnt = sprintf(print_str,"ERROR-thread_attr_atss_channelthread");
            PrintData(print_str,textcnt,nlcnt,tcnt);
            return_flag=false;
        }
    }
    if(return_flag==true)
    {
        if(pthread_create(&thread_id_atss_channel,&thread_attr_atss_channel,&InitCheckThread,NULL) != 0)
        {
            perror("ERROR - ");
            textcnt = sprintf(print_str,"ERROR-Pthread create error for thread_attr_atss_channel");
            PrintData(print_str,textcnt,nlcnt,tcnt);
            return_flag=false;
        }
    }

    return return_flag;
}




///

bool ReadConfigureXML()
{
    INT_32 textcnt  = 0;
    INT_8 print_str[MAX_SIZE_PACKET] = {0};
    // -----------------------------------------------------------------------------------
    // General Config File read start
    // -----------------------------------------------------------------------------------

#ifdef LINE_ONE
    QString setup_id;

    //    switch(xml_config.getSetupId())
    //    {
    //    case 1:
    //        setup_id = "/home/ATS/Line1/ATSS/XML/ATSNodeConfiguration_OCC.xml";
    //        break;
    //    case 2:
    //        setup_id = "/home/ATS/Line1/ATSS/XML/ATSNodeConfiguration_DMRC_LAB.xml";
    //        break;
    //    case 3:
    //        setup_id = "/home/ATS/Line1/ATSS/XML/ATSNodeConfiguration_CRL.xml";
    //        break;
    //    }
    setup_id = "/home/ATS/Line1/ATSS/XML/ATSNodeConfiguration.xml";

#ifdef WINDOWS_VER
    setup_id = "C:\\ATS\\XML\\ATSNodeConfiguration.xml";
#endif

    QFile file1(setup_id);
#endif

    QDomDocument doc1("hisdocument");

    if (!file1.open(QIODevice::ReadOnly))
    {
        textcnt = sprintf(print_str,"\n ERROR1 in XML/ATSNodeConfiguration ");
        PrintData(print_str,textcnt,0,0,LOG_ATSS_INFO);

        return false;
    }
    if (!doc1.setContent(&file1))
    {
        textcnt = sprintf(print_str,"\n ERROR2 in XML/ATSNodeConfiguration ");
        PrintData(print_str,textcnt,0,0,LOG_ATSS_INFO);

        file1.close();
        return false;
    }
    file1.close();

    //    textcnt = sprintf(print_str,"\n Reading : ATSNodeConfiguration.xml");
    //    PrintData(print_str,textcnt,0,0,LOG_ATSS_INFO);

    // -----------------------------------------------------------------------------------
    // ATS Config File read START
    // -----------------------------------------------------------------------------------

    QDomElement docElem1 = doc1.documentElement();

    textcnt = sprintf(print_str,"\n\n-------------------------------------------------------------------------------"
                                "\n\t\t\tATS_NODE_CONFIGURATION :"
                                "\n+-------+-------+-------+-------+-------+-----------------------+-------+-----+"
                                "\n| id\t| level\t| node\t| id\t| name\t| IP\t\t\t| index\t| port|"
                                "\n+-------+-------+-------+-------+-------+-----------------------+-------+-----+");
    utility_obj.PrintData(print_str,textcnt,0,0,LOG_ATSS_INFO);
    xml_config.readATSNodeEntityEntry(docElem1,"COMM_DETAILS");
    xml_config.print_Comm_Details();
    xml_config.readATSNodeEntityEntry(docElem1,"ATC_DETAILS");
    xml_config.readATSNodeEntityEntry(docElem1,"BROADCAST_DETAILS");

    setup_id = "/home/ATS/Line1/ATSS/XML/Configuration1.xml";
#ifdef WINDOWS_VER
    setup_id = "C:\\ATS\\XML\\Configuration1.xml";
#endif
    QFile file2(setup_id);
    QDomDocument doc2("mydocument");

    if (!file2.open(QIODevice::ReadOnly))
    {

        textcnt = sprintf(print_str,"\n ERROR1 in XML/Configuration");
        PrintData(print_str,textcnt,0,0,LOG_ATSS_INFO);

        return false;
    }
    if (!doc2.setContent(&file2))
    {

        textcnt = sprintf(print_str,"\n ERROR2 in XML/Configuration");
        PrintData(print_str,textcnt,0,0,LOG_ATSS_INFO);

        file2.close();
        return false;
    }
    file2.close();

    //    textcnt = sprintf(print_str,"\n Reading : Configuration.xml");
    //    PrintData(print_str,textcnt,0,0,LOG_ATSS_INFO);


    QDomElement docElem = doc2.documentElement();
    xml_config.readEntityEntry(docElem,"tracks");
    xml_config.readEntityEntry(docElem,"signal");
    xml_config.readEntityEntry(docElem,"station");
    xml_config.readEntityEntry(docElem,"platforms");
    xml_config.readEntityEntry(docElem,"routes");
    xml_config.readEntityEntry(docElem,"cycles");
    xml_config.readEntityEntry(docElem,"route_list");
    xml_config.readEntityEntry(docElem,"global_command");
    xml_config.readEntityEntry(docElem,"possible_routes");
    xml_config.readEntityEntry(docElem,"parent_data");
    xml_config.readEntityEntry(docElem,"station_list");
    xml_config.readEntityEntry(docElem,"junction_management");
    xml_config.readEntityEntry(docElem,"conflict_route");
    // 19 Aug
    xml_config.readEntityEntry(docElem,"itr_stn_ctrl");
    xml_config.readEntityEntry(docElem,"platform_conflict");

    // end
    // -----------------------------------------------------------------------------------

    // -----------------------------------------------------------------------------------
    // ATC Platform ID File read START
    // -----------------------------------------------------------------------------------

    setup_id = "/home/ATS/Line1/ATSS/XML/PlatformID.xml";
#ifdef WINDOWS_VER
    setup_id = "C:\\ATS\\XML\\PlatformID.xml";
#endif
    QFile file3(setup_id);
    QDomDocument doc3("");

    if (!file2.open(QIODevice::ReadOnly))
    {
        textcnt = sprintf(print_str,"\n ERROR1 in XML/PlatformID ");
        PrintData(print_str,textcnt,0,0,LOG_ATSS_INFO);

        return false;
    }
    if (!doc3.setContent(&file3))
    {
        textcnt = sprintf(print_str,"\n ERROR2 in XML/PlatformID ");
        PrintData(print_str,textcnt,0,0,LOG_ATSS_INFO);

        file3.close();
        return false;
    }
    file3.close();

    //    textcnt = sprintf(print_str,"\n Reading : PlatformID.xml");
    //    PrintData(print_str,textcnt,0,0,LOG_ATSS_INFO);

    QDomElement docElem2 = doc3.documentElement();
    xml_config.readATCPlatformEntry(docElem2,"Platform");
    // -----------------------------------------------------------------------------------
    // END
    // -----------------------------------------------------------------------------------

    return true;
}
void LoadRegisterTimeTable();
void LoadRegisterTimeTable2();
void SaveValidateTimeTable();
void LoadTimeTable();
void RequestTimeTable();

bool ProcessCBIMsgsThread(pthread_attr_t &thread_attr_time_table, pthread_t &thread_id_time_table)
{
    bool return_flag = true;
    INT_8 print_str[MAX_PRINT_STR];
    INT_32 textcnt=0;
    UINT_8 nlcnt=1;
    UINT_8 tcnt=0;
    struct sched_param struct_sched_param;
    struct_sched_param.sched_priority = SCHED_RR_PRIORITY;
    if (pthread_attr_init(&thread_attr_time_table) == POSIX_FAIL)
    {
        perror("ERROR - ");
        textcnt = sprintf(print_str,"ERROR-thread_attr_time_table");
        PrintData(print_str,textcnt,nlcnt,tcnt);
        return_flag= false;
    }
    if(return_flag==true)
    {
        pthread_attr_setschedparam(&thread_attr_time_table, &struct_sched_param);
        if(pthread_attr_setschedpolicy(&thread_attr_time_table, SCHED_RR) == POSIX_FAIL)
        {
            perror("ERROR - ");
            textcnt = sprintf(print_str,"ERROR-thread_attr_time_table");
            PrintData(print_str,textcnt,nlcnt,tcnt);
            return_flag=false;
        }
    }
    if(return_flag==true)
    {
        if(pthread_create(&thread_id_time_table,&thread_attr_time_table,&CBIMsgsThread,NULL) != 0)
        {
            perror("ERROR - ");
            textcnt = sprintf(print_str,"ERROR-pthread_create error for thread_attr_time_table");
            PrintData(print_str,textcnt,nlcnt,tcnt);
            return_flag=false;
        }
    }
    return return_flag;
}

bool ProcessPTIThread(pthread_attr_t &thread_attr_critical_command, pthread_t &thread_id_critical_command)
{
    bool return_flag = true;
    INT_8 print_str[MAX_PRINT_STR];
    INT_32 textcnt = 0;
    UINT_8 nlcnt = 1;
    UINT_8 tcnt = 0;
    struct sched_param struct_sched_param;
    struct_sched_param.sched_priority = SCHED_RR_PRIORITY;
    if (pthread_attr_init(&thread_attr_critical_command) == POSIX_FAIL)
    {
        perror("ERROR - ");
        textcnt = sprintf(print_str,"ERROR-thread_attr_critical_command");
        PrintData(print_str,textcnt,nlcnt,tcnt);
        return_flag=false;
    }
    if(return_flag==true)
    {
        pthread_attr_setschedparam(&thread_attr_critical_command, &struct_sched_param);
        if(pthread_attr_setschedpolicy(&thread_attr_critical_command, SCHED_RR) == POSIX_FAIL)
        {
            perror("ERROR - ");
            textcnt = sprintf(print_str,"ERROR-thread_attr_critical_command");
            PrintData(print_str,textcnt,nlcnt,tcnt);
            return_flag=false;
        }
    }
    if(return_flag==true)
    {
        if(pthread_create(&thread_id_critical_command,&thread_attr_critical_command,&PTIThread,NULL) != 0)
        {
            perror("ERROR - ");
            textcnt = sprintf(print_str,"ERROR-pthread_create error for thread_attr_critical_command"); PrintData(print_str,textcnt,nlcnt,tcnt);
            return_flag=false;
        }
    }
    return return_flag;
}

bool ProcessPIDSPAS(pthread_attr_t &process_pids_pas_thread_attr, pthread_t &process_pids_pas_thread_id)
{
    bool return_flag = true;
    UINT_8 tcnt = 0;
    UINT_8 nlcnt = 1;
    INT_8 print_str[MAX_PRINT_STR] = {0};
    INT_32 textcnt = 0;

    struct sched_param struct_sched_param;
    struct_sched_param.sched_priority = SCHED_RR_PRIORITY;

    if (pthread_attr_init(&process_pids_pas_thread_attr) == POSIX_FAIL)
    {
        perror("ERROR - ");
        textcnt = sprintf(print_str,"ERROR-process_pids_pas_thread_attrthread");
        PrintData(print_str,textcnt,nlcnt,tcnt);
        return_flag=false;
    }
    if(return_flag==true)
    {
        pthread_attr_setschedparam(&process_pids_pas_thread_attr, &struct_sched_param);
        if(pthread_attr_setschedpolicy(&process_pids_pas_thread_attr, SCHED_RR) == POSIX_FAIL)
        {
            perror("ERROR - ");
            textcnt = sprintf(print_str,"ERROR-process_pids_pas_thread_attrthread");
            PrintData(print_str,textcnt,nlcnt,tcnt);
            return_flag=false;
        }
    }
    if(return_flag==true)
    {
        if(pthread_create(&process_pids_pas_thread_id,&process_pids_pas_thread_attr,&PISPASThread,NULL) != 0)
        {
            perror("ERROR - ");
            textcnt = sprintf(print_str,"ERROR-Pthread create error for process_pids_pas_thread_attr");
            PrintData(print_str,textcnt,nlcnt,tcnt);
            return_flag=false;
        }
    }

    return return_flag;
}


bool ProcessCommandAckThread(pthread_attr_t &process_cmd_ack_thread_attr, pthread_t &process_cmd_ack_thread_id)
{
    bool return_flag = true;
    UINT_8 tcnt = 0;
    UINT_8 nlcnt = 1;
    INT_8 print_str[MAX_PRINT_STR] = {0};
    INT_32 textcnt = 0;

    struct sched_param struct_sched_param;
    struct_sched_param.sched_priority = SCHED_RR_PRIORITY;

    if (pthread_attr_init(&process_cmd_ack_thread_attr) == POSIX_FAIL)
    {
        perror("ERROR - ");
        textcnt = sprintf(print_str,"ERROR-process_cmd_ack_thread_attrthread");
        PrintData(print_str,textcnt,nlcnt,tcnt);
        return_flag=false;
    }
    if(return_flag==true)
    {
        pthread_attr_setschedparam(&process_cmd_ack_thread_attr, &struct_sched_param);
        if(pthread_attr_setschedpolicy(&process_cmd_ack_thread_attr, SCHED_RR) == POSIX_FAIL)
        {
            perror("ERROR - ");
            textcnt = sprintf(print_str,"ERROR-process_cmd_ack_thread_attrthread");
            PrintData(print_str,textcnt,nlcnt,tcnt);
            return_flag=false;
        }
    }
    if(return_flag==true)
    {
        if(pthread_create(&process_cmd_ack_thread_id,&process_cmd_ack_thread_attr,&CommandAckThread,NULL) != 0)
        {
            perror("ERROR - ");
            textcnt = sprintf(print_str,"ERROR-Pthread create error for process_cmd_ack_thread_attr");
            PrintData(print_str,textcnt,nlcnt,tcnt);
            return_flag=false;
        }
    }

    return return_flag;
}



void Test1();
void TestConsecutiveTrack();
void TestpidpasArrival();

void TestTrain();
void TestInterstationStop();
void TestDepotTrack();
void TestTrainRevenue();
void TestNext3Departures();
void Trains(RAKE_ID rake_ID);
void SendDifferentRake();
void SaveSKIP();
void Trains(RAKE_ID rake_ID);
void SaveTTasMaps();
void testHeadway();
void TestArthalaCircuit();
void TrainOnArthala();
void TrainOnJunction();

void Test()
{
    TestConsecutiveTrack();
    //LoadRegisterTimeTable2();
}

void TrainOnJunction()
{
    STRUCT_TRACK_STATUS trk[5];    memset(trk,0,sizeof(trk));

    trk[0].is_free=0U;
    trk[0].track_id = 25;
    trk[0].is_up_direction_route_locked = 0;     trk[0].is_down_direction_route_locked = 1;
    atss_atc_processing_obj.SetOccupiedInfoTest(25,(char*)"TC25A",1,25,101);
    msg_processor_obj.process_Track_Occupancy(trk[0],101);

    trk[0].track_id = 36;
    trk[0].is_up_direction_route_locked = 1;     trk[0].is_down_direction_route_locked = 0;
    atss_atc_processing_obj.SetOccupiedInfoTest(36,(char*)"TC36A",2,36,101);
    msg_processor_obj.process_Track_Occupancy(trk[0],101);

    trk[0].track_id = 27;
    trk[0].is_up_direction_route_locked = 0;     trk[0].is_down_direction_route_locked = 1;
    atss_atc_processing_obj.SetOccupiedInfoTest(27,(char*)"TC27A",1,27,101);
    msg_processor_obj.process_Track_Occupancy(trk[0],101);

    trk[0].track_id = 34;
    trk[0].is_up_direction_route_locked = 1;     trk[0].is_down_direction_route_locked = 0;
    atss_atc_processing_obj.SetOccupiedInfoTest(34,(char*)"TC34A",2,34,101);
    msg_processor_obj.process_Track_Occupancy(trk[0],101);

}

void TrainOnArthala()
{
    STRUCT_TRACK_STATUS trk[5];
    memset(trk,0,sizeof(trk));

    trk[0].is_free=0U;
    trk[0].is_up_direction_route_locked = 0;
    trk[0].is_down_direction_route_locked = 1;

    UINT_8 point_id = 11;
    UINT_8 cbi_id =111 ;
    UINT_32 key = point_id*1000 + cbi_id;
    STRUCT_POINT_PARENT_DATA point_data = xml_config.GetPointDataMap(key);
    atss_point_info_obj.set_Point_Normal(point_data,POINT_POSITION_NORMAL);
    atss_point_info_obj.set_Point_Reverse(point_data,POINT_POSITION_REVERSE);

    trk[0].track_id = 89;
    msg_processor_obj.process_Track_Occupancy(trk[0],111);
    getchar();
}

struct CBI_ROUTE_DATA
{
    ROUTE_ID route_id;
    CBI_ID cbi_id;
    //map<cbi,route>
    //map<trk+cbi,route>
    //map<route+cbi,trk+cbi>

};

void TestTrainRoute()
{

}

void TestArthalaCircuit()
{

    STRUCT_GENERAL_MESSAGE_ATSS gen_msg2;
    gen_msg2.msg_header.source_id = CSCI_ATSD;
    gen_msg2.msg_header.dest_id = CSCI_ATSS;
    gen_msg2.msg_header.message_id = ATSD_ATSS_REQ_FOR_TIMETABLE;
    gen_msg2.msg_header.ows_id = 2;
    gen_msg2.msg_header.no_of_packets = 1;
    gen_msg2.msg_header.packet_number = 1;
    gen_msg2.msg_header.message_length = sizeof (gen_msg2);

    STRUCT_DBA_ATSS_TIME_TABLE_INFO load_time_table2;
    memset(&load_time_table2,0,sizeof(load_time_table2));
    sprintf(load_time_table2.struct_time_table.time_table_name,"ArthalaLoop.csv");
    load_time_table2.is_switch_to_time_table_mode = 1;
    load_time_table2.struct_time_table.date.day = 6;
    load_time_table2.struct_time_table.date.month = 8;
    load_time_table2.struct_time_table.date.year = 2021;
    memcpy(&gen_msg2.body,&load_time_table2.struct_time_table,sizeof(load_time_table2.struct_time_table));
    msg_processor_obj.processInitTimeTableInfoMsg(gen_msg2);

    time_table_obj.printTimeTable();
    sleep(2);

    INT_8 track_name[15];
    STRUCT_TRACK_STATUS trk[5];
    memset(trk,0,sizeof(trk));

    trk[0].is_free=0U;
    trk[0].is_up_direction_route_locked = 0;
    trk[0].is_down_direction_route_locked = 1;

    trk[0].track_id = 83;
    msg_processor_obj.process_Track_Occupancy(trk[0],111);

    trk[0].track_id = 83;
    msg_processor_obj.process_Track_Occupancy(trk[0],111);
    sleep(1);
    trk[0].track_id = 85;
    msg_processor_obj.process_Track_Occupancy(trk[0],111);
    xml_config.GetTrackName(83,111,track_name);    route_set_processing_obj.RemoveTrackFromOccupiedTrackMap(track_name);

    sleep(1);
    trk[0].track_id = 87;
    msg_processor_obj.process_Track_Occupancy(trk[0],111);
    xml_config.GetTrackName(85,111,track_name);    route_set_processing_obj.RemoveTrackFromOccupiedTrackMap(track_name);
    route_set_processing_obj.PrintOccupiedTrackMap();

    sleep(1);
    trk[0].track_id = 89;
    msg_processor_obj.process_Track_Occupancy(trk[0],111);
    xml_config.GetTrackName(87,111,track_name);    route_set_processing_obj.RemoveTrackFromOccupiedTrackMap(track_name);
    route_set_processing_obj.PrintOccupiedTrackMap();


    sleep(1);
    trk[0].is_up_direction_route_locked = 0;
    trk[0].is_down_direction_route_locked = 0;
    trk[0].track_id = 89;
    msg_processor_obj.process_Track_Occupancy(trk[0],111);
    sleep(1);
    trk[0].is_up_direction_route_locked = 1;
    trk[0].is_down_direction_route_locked = 0;
    trk[0].track_id = 87;
    msg_processor_obj.process_Track_Occupancy(trk[0],111);
    xml_config.GetTrackName(89,111,track_name);    route_set_processing_obj.RemoveTrackFromOccupiedTrackMap(track_name);
    route_set_processing_obj.PrintOccupiedTrackMap();
    sleep(1);
    trk[0].track_id = 96;
    msg_processor_obj.process_Track_Occupancy(trk[0],111);
    xml_config.GetTrackName(87,111,track_name);    route_set_processing_obj.RemoveTrackFromOccupiedTrackMap(track_name);
    route_set_processing_obj.PrintOccupiedTrackMap();
    sleep(1);
    trk[0].track_id = 94;
    msg_processor_obj.process_Track_Occupancy(trk[0],111);
    xml_config.GetTrackName(96,111,track_name);    route_set_processing_obj.RemoveTrackFromOccupiedTrackMap(track_name);
    route_set_processing_obj.PrintOccupiedTrackMap();
    sleep(1);
    trk[0].is_down_direction_route_locked= 1;
    trk[0].is_up_direction_route_locked = 0;
    trk[0].track_id = 96;
    msg_processor_obj.process_Track_Occupancy(trk[0],111);
    xml_config.GetTrackName(94,111,track_name);    route_set_processing_obj.RemoveTrackFromOccupiedTrackMap(track_name);
    route_set_processing_obj.PrintOccupiedTrackMap();
    sleep(1);
    trk[0].track_id = 87;
    msg_processor_obj.process_Track_Occupancy(trk[0],111);
    xml_config.GetTrackName(96,111,track_name);    route_set_processing_obj.RemoveTrackFromOccupiedTrackMap(track_name);
    route_set_processing_obj.PrintOccupiedTrackMap();
    sleep(1);
    trk[0].track_id = 89;
    msg_processor_obj.process_Track_Occupancy(trk[0],111);
    xml_config.GetTrackName(87,111,track_name);    route_set_processing_obj.RemoveTrackFromOccupiedTrackMap(track_name);
    route_set_processing_obj.PrintOccupiedTrackMap();
    sleep(1);
    //    atss_point_info_obj.set_Point_Normal(13,111);
    trk[0].track_id = 91;
    msg_processor_obj.process_Track_Occupancy(trk[0],111);
    xml_config.GetTrackName(89,111,track_name);    route_set_processing_obj.RemoveTrackFromOccupiedTrackMap(track_name);
    route_set_processing_obj.PrintOccupiedTrackMap();
}



void testHeadway()
{
    STRUCT_HEADWAY headway;
    headway.no_of_rakes = 1;
    headway.num_of_headway_setting = 1;
    headway.struct_rake_journey[0].rake_id      = 1;
    headway.struct_rake_journey[0].journey_id   = 1;
    //    headway.struct_rake_journey[1].rake_id      = 2;
    //    headway.struct_rake_journey[1].journey_id   = 2;
    headway.struct_headway_setting[0].headway   = 5;
    headway.struct_headway_setting[0].dwell_time        = 3;
    headway.struct_headway_setting[0].left_cycle_id     = 27;
    headway.struct_headway_setting[0].left_cycle_cbi_id = 111;
    headway.struct_headway_setting[0].right_cycle_id    = 30;
    headway.struct_headway_setting[0].right_cycle_cbi_id = 111;
    atss_headway_mode_obj.headwayModeOperation(headway);
}

void SaveSKIP()
{
    STRUCT_ATC_PLATFORM_SKIP_STATION skip;
    skip.atc_id = 10;
    skip.station_id = 12;
    skip.platform_id =3;
    skip.skip_flag = 0;
    msg_processor_obj.SavePlatformSkip(skip);
    skip.station_id = 11;
    skip.platform_id =2;
    skip.skip_flag = 1;
    msg_processor_obj.SavePlatformSkip(skip);
    skip.station_id = 9;
    skip.platform_id =1;
    skip.skip_flag = 0;
    msg_processor_obj.SavePlatformSkip(skip);

    msg_processor_obj.remove_all_train_skip();
}
void SaveValidateTimeTable()
{
    STRUCT_GENERAL_MESSAGE_ATSS gen_msg2;
    gen_msg2.msg_header.ows_id = 1;    gen_msg2.msg_header.message_id =ATSD_ATSS_SAVE_AND_VALIDATE_TIME_TABLE;

    STRUCT_ATSD_ATSS_SAVE_AND_VALIDATE_TIME_TABLE load_time_table2;
    memset(&load_time_table2,0,sizeof(load_time_table2));
    sprintf(load_time_table2.struct_time_table.time_table_name,"NewTimeTable07Jul.csv");
    load_time_table2.is_save_and_validate = TIME_TABLE_SAVE;
    load_time_table2.struct_time_table.date.day = 06;
    load_time_table2.struct_time_table.date.month = 10;
    load_time_table2.struct_time_table.date.year = 2021;
    memcpy(&gen_msg2.body,&load_time_table2.struct_time_table,sizeof(load_time_table2.struct_time_table));
    msg_processor_obj.ProcessTimeTable(gen_msg2);
}
void RequestTimeTable()
{
    STRUCT_GENERAL_MESSAGE_ATSS gen_msg2;
    gen_msg2.msg_header.ows_id = 1;    gen_msg2.msg_header.message_id =ATSD_ATSS_REQ_FOR_TIMETABLE;

    STRUCT_ATSD_ATSS_REQ_FOR_TIMETABLE load_time_table2;
    memset(&load_time_table2,0,sizeof(load_time_table2));
    sprintf(load_time_table2.struct_req_for_time_table.time_table_name,"NewTimeTable07Jul.csv");
    load_time_table2.struct_req_for_time_table.time_table_req_type = REQ_TYPE_REGISTER_TIME_TABLE;
    load_time_table2.struct_req_for_time_table.date.day = 06;
    load_time_table2.struct_req_for_time_table.date.month = 10;
    load_time_table2.struct_req_for_time_table.date.year = 2021;
    memcpy(&gen_msg2.body,&load_time_table2.struct_req_for_time_table,sizeof(load_time_table2.struct_req_for_time_table));
    msg_processor_obj.ProcessTimeTableRequest(gen_msg2);
}
void LoadTimeTable()
{
    STRUCT_GENERAL_MESSAGE_ATSS gen_msg2;
    gen_msg2.msg_header.ows_id = 1;    gen_msg2.msg_header.message_id =ATSD_ATSS_REQ_FOR_TIMETABLE;

    STRUCT_ATSD_ATSS_REQ_FOR_TIMETABLE load_time_table2;
    memset(&load_time_table2,0,sizeof(load_time_table2));
    sprintf(load_time_table2.struct_req_for_time_table.time_table_name,"NewTimeTable07Jul.csv");
    load_time_table2.struct_req_for_time_table.time_table_req_type = REQ_TYPE_LOAD_SWITCH_TO_TIME_TABLE_MODE;
    load_time_table2.struct_req_for_time_table.date.day = 06;
    load_time_table2.struct_req_for_time_table.date.month = 10;
    load_time_table2.struct_req_for_time_table.date.year = 2021;
    memcpy(&gen_msg2.body,&load_time_table2.struct_req_for_time_table,sizeof(load_time_table2.struct_req_for_time_table));
    msg_processor_obj.ProcessTimeTableRequest(gen_msg2);
}

void LoadRegisterTimeTable()
{
    STRUCT_GENERAL_MESSAGE_ATSS gen_msg2;
    gen_msg2.msg_header.ows_id = 1;    gen_msg2.msg_header.message_id =DBA_ATSS_TIME_TABLE_INFO;

    STRUCT_DBA_ATSS_TIME_TABLE_INFO load_time_table2;
    memset(&load_time_table2,0,sizeof(load_time_table2));
    sprintf(load_time_table2.struct_time_table.time_table_name,"NBAADSG_18_1_2022_registered.csv");
    load_time_table2.is_switch_to_time_table_mode = 1;
    load_time_table2.struct_time_table.date.day = 06;
    load_time_table2.struct_time_table.date.month = 10;
    load_time_table2.struct_time_table.date.year = 2021;
    memcpy(&gen_msg2.body,&load_time_table2.struct_time_table,sizeof(load_time_table2.struct_time_table));
    msg_processor_obj.processInitTimeTableInfoMsg(gen_msg2);
}

void LoadRegisterTimeTable2()
{
    STRUCT_GENERAL_MESSAGE_ATSS gen_msg2;
    gen_msg2.msg_header.ows_id = 1;    gen_msg2.msg_header.message_id =DBA_ATSS_TIME_TABLE_INFO;

    STRUCT_DBA_ATSS_TIME_TABLE_INFO load_time_table2;
    memset(&load_time_table2,0,sizeof(load_time_table2));
    sprintf(load_time_table2.struct_time_table.time_table_name,"NewTimeTable1_8_10_2021_registered.csv");
    load_time_table2.is_switch_to_time_table_mode = 1;
    load_time_table2.struct_time_table.date.day = 11;
    load_time_table2.struct_time_table.date.month = 8;
    load_time_table2.struct_time_table.date.year = 2021;
    memcpy(&gen_msg2.body,&load_time_table2.struct_time_table,sizeof(load_time_table2.struct_time_table));
    msg_processor_obj.processInitTimeTableInfoMsg(gen_msg2);
}


void TestConsecutiveTrack()
{
    //        atss_point_info_obj.set_Point_Reverse(7,111);
    //        atss_point_info_obj.set_Point_Reverse(5,111);
    //        atss_point_info_obj.set_Point_Reverse(8,111);
    //        atss_point_info_obj.set_Point_Normal(6,111);

    STRUCT_DONT_CARE_TRACK val;
    val.trk_ID = 71;
    val.cbi_ID = 111;
    val.activate_flag = 1;
    msg_processor_obj.addDontCareMap(val);
    val.trk_ID = 73;
    msg_processor_obj.addDontCareMap(val);
    STRUCT_TRACK_STATUS trk[5];
    memset(trk,0,sizeof(trk));
    trk[0].track_id = 69;
    trk[0].is_free = 0U;
    trk[0].is_up_direction_route_locked = 0;
    trk[0].is_down_direction_route_locked = 1;
    msg_processor_obj.process_Track_Occupancy(trk[0],111);
    trk[0].track_id = 71;
    msg_processor_obj.process_Track_Occupancy(trk[0],111);
    trk[0].track_id = 73;
    msg_processor_obj.process_Track_Occupancy(trk[0],111);
    trk[0].track_id = 75;
    msg_processor_obj.process_Track_Occupancy(trk[0],111);

    trk[0].track_id = 69;
    msg_processor_obj.process_Track_Occupancy(trk[0],111);
    trk[0].track_id = 71;
    msg_processor_obj.process_Track_Occupancy(trk[0],111);
    trk[0].track_id = 73;
    msg_processor_obj.process_Track_Occupancy(trk[0],111);
    trk[0].track_id = 75;
    msg_processor_obj.process_Track_Occupancy(trk[0],111);

    route_set_processing_obj.RemoveTrackFromOccupiedTrackMap((char*)"TC69L");
    trk[0].track_id = 71;
    msg_processor_obj.process_Track_Occupancy(trk[0],111);
    trk[0].track_id = 73;
    msg_processor_obj.process_Track_Occupancy(trk[0],111);
    trk[0].track_id = 75;
    msg_processor_obj.process_Track_Occupancy(trk[0],111);

    route_set_processing_obj.RemoveTrackFromOccupiedTrackMap((char*)"TC71L");
    trk[0].track_id = 73;
    msg_processor_obj.process_Track_Occupancy(trk[0],111);
    trk[0].track_id = 75;
    msg_processor_obj.process_Track_Occupancy(trk[0],111);

    trk[0].track_id = 73;
    msg_processor_obj.process_Track_Occupancy(trk[0],111);
    trk[0].track_id = 75;
    msg_processor_obj.process_Track_Occupancy(trk[0],111);

    route_set_processing_obj.RemoveTrackFromOccupiedTrackMap((char*)"TC73L");
    trk[0].track_id = 75;
    msg_processor_obj.process_Track_Occupancy(trk[0],111);
}


void TestDepotTrack()
{

    //    atss_point_info_obj.set_Point_Normal(62,102);
    //    atss_point_info_obj.set_Point_Normal(1,107);
    //    atss_point_info_obj.set_Point_Normal(3,107);
    //    atss_point_info_obj.set_Point_Normal(7,107);
    //    atss_point_info_obj.set_Point_Normal(8,107);
    //    atss_point_info_obj.set_Point_Normal(10,107);
    //    atss_point_info_obj.set_Point_Normal(12,107);
    //    atss_point_info_obj.set_Point_Normal(15,107);
    //    atss_point_info_obj.set_Point_Normal(18,107);
    //    atss_point_info_obj.set_Point_Reverse(22,107);
    //    atss_point_info_obj.set_Point_Normal(23,107);
    //    atss_point_info_obj.set_Point_Normal(24,107);
    //atss_point_info_obj.set_Point_Reverse(point_status.point_id,cbi_id);

    STRUCT_TRACK_STATUS trk[5];
    memset(trk,0,sizeof(trk));
    trk[0].track_id = 26;
    trk[0].is_free=1U;
    trk[0].is_up_direction_route_locked = 0;
    trk[0].is_down_direction_route_locked = 1;
    msg_processor_obj.process_Track_Occupancy(trk[0],102);

    sleep(1);
    trk[0].track_id = 61;
    msg_processor_obj.process_Track_Occupancy(trk[0],102);

    sleep(1);
    trk[0].track_id = 34;
    msg_processor_obj.process_Track_Occupancy(trk[0],107);

    sleep(1);
    trk[0].track_id = 33;
    msg_processor_obj.process_Track_Occupancy(trk[0],107);

    sleep(1);
    trk[0].track_id = 32;
    msg_processor_obj.process_Track_Occupancy(trk[0],107);

    sleep(1);
    trk[0].track_id = 31;
    msg_processor_obj.process_Track_Occupancy(trk[0],107);

    sleep(1);
    trk[0].track_id = 29;
    msg_processor_obj.process_Track_Occupancy(trk[0],107);
    sleep(1);
    trk[0].track_id = 27;
    msg_processor_obj.process_Track_Occupancy(trk[0],107);
    sleep(1);
    trk[0].track_id = 25;
    msg_processor_obj.process_Track_Occupancy(trk[0],107);

    sleep(1);
    trk[0].track_id = 23;
    msg_processor_obj.process_Track_Occupancy(trk[0],107);

    sleep(1);
    trk[0].track_id = 19;
    msg_processor_obj.process_Track_Occupancy(trk[0],107);

    sleep(1);
    trk[0].track_id = 10;
    msg_processor_obj.process_Track_Occupancy(trk[0],107);

    sleep(1);
    trk[0].track_id = 9;
    msg_processor_obj.process_Track_Occupancy(trk[0],107);



}

void Trains(RAKE_ID rake_ID)
{

    STRUCT_TRACK_STATUS trk[5];
    memset(trk,0,sizeof(trk));
    trk[0].is_free=0U;
    trk[0].is_up_direction_route_locked = 0;
    trk[0].is_down_direction_route_locked = 1;

    trk[0].is_free=0U;
    trk[0].track_id = 65;
    msg_processor_obj.process_Track_Occupancy(trk[0],111);
    atss_atc_processing_obj.SetOccupiedInfoTest(65,(char*)"TC65L",1,65,111);
    sleep(2);
    route_set_processing_obj.DwellTimeAndInterstationStopInOccupiedTrackMap();
    //dwell time actual
    pids_pas_class_obj.processHeadwayNextArrivalPidsPas();
    pids_pas_class_obj.processHeadwayNextThreeDepartures();
    sleep(1);

    route_set_processing_obj.RemoveTrackFromOccupiedTrackMap((char*)"TC65L",ADD_FROM_SELF_ATSS);
    //////////////////////////////////////////////////////////////////////////////////////
    //headway actual

    //    trk[0].is_free=1U;
    //    trk[0].track_id = 65;
    //    msg_processor_obj.process_Track_Occupancy(trk[0],111);
    //    atss_atc_processing_obj.SetOccupiedInfoTest(65,(char*)"TC65L",2,65,111);
    //    route_set_processing_obj.DwellTimeAndInterstationStopInOccupiedTrackMap();
    //    //dwell time
    //    pids_pas_class_obj.processHeadwayNextArrivalPidsPas();
    //    pids_pas_class_obj.processHeadwayNextThreeDepartures();

    //    sleep(5);
    //    route_set_processing_obj.RemoveTrackFromOccupiedTrackMap((char*)"TC65L",CENTRAL_ATS_MODE);
    //////////////////////////////////////////////////////////////////////////////////////
    // ///////////////////////////////////////////////////////////////////////////////////////
    //headway actual

    //    sleep(1);
    //    trk[0].is_free=0U;
    //    trk[0].track_id = 75;
    //    msg_processor_obj.process_Track_Occupancy(trk[0],111);
    //    atss_atc_processing_obj.SetOccupiedInfoTest(75,(char*)"TC75L",1,75,111);sleep(2);
    //    route_set_processing_obj.DwellTimeAndInterstationStopInOccupiedTrackMap();
    //    //dwell time
    //    pids_pas_class_obj.processHeadwayNextArrivalPidsPas();
    //    pids_pas_class_obj.processHeadwayNextThreeDepartures();
    //    sleep(1);

    //    route_set_processing_obj.RemoveTrackFromOccupiedTrackMap((char*)"TC75L",CENTRAL_ATS_MODE);

    //////////////////////////////////////////////////////////////////////////////////////
    //headway actual
    //    sleep(1);
    //    trk[0].is_free=1U;
    //    trk[0].track_id = 75;
    //    msg_processor_obj.process_Track_Occupancy(trk[0],111);
    //    atss_atc_processing_obj.SetOccupiedInfoTest(75,(char*)"TC75L",2,75,111);
    //    route_set_processing_obj.DwellTimeAndInterstationStopInOccupiedTrackMap();
    //    //dwell time
    //    pids_pas_class_obj.processHeadwayNextArrivalPidsPas();
    //    pids_pas_class_obj.processHeadwayNextThreeDepartures();

    //    sleep(11);
    //    route_set_processing_obj.RemoveTrackFromOccupiedTrackMap((char*)"TC75L",CENTRAL_ATS_MODE);
    //////////////////////////////////////////////////////////////////////////////////////
    // ///////////////////////////////////////////////////////////////////////////////////
    //headway actual

    //    sleep(1);
    //    trk[0].is_free=0U;
    //    trk[0].track_id = 89;
    //    msg_processor_obj.process_Track_Occupancy(trk[0],111);
    //    atss_atc_processing_obj.SetOccupiedInfoTest(89,(char*)"TC89L",1,89,111);sleep(2);
    //    route_set_processing_obj.DwellTimeAndInterstationStopInOccupiedTrackMap();
    //    //dwell time
    //    pids_pas_class_obj.processHeadwayNextArrivalPidsPas();
    //    pids_pas_class_obj.processHeadwayNextThreeDepartures();
    //    sleep(1);
    //    route_set_processing_obj.RemoveTrackFromOccupiedTrackMap((char*)"TC89L",CENTRAL_ATS_MODE);

    //////////////////////////////////////////////////////////////////////////////////////
    //    //headway actual
    //    sleep(40);
    //    trk[0].is_free=1U;
    //    trk[0].track_id = 89;
    //    msg_processor_obj.process_Track_Occupancy(trk[0],111);
    //    atss_atc_processing_obj.SetOccupiedInfoTest(89,(char*)"TC89L",2,89,111);
    //    route_set_processing_obj.DwellTimeAndInterstationStopInOccupiedTrackMap();
    //    //dwell time
    //    sleep(11);
    //    route_set_processing_obj.RemoveTrackFromOccupiedTrackMap((char*)"TC89L",CENTRAL_ATS_MODE);
    //////////////////////////////////////////////////////////////////////////////////////
    // ////////////////////////////////////////////////////////////////////////////////
    //headway actual

    //    trk[0].is_up_direction_route_locked = 1;
    //    trk[0].is_down_direction_route_locked = 0;
    //    sleep(1);
    //    trk[0].is_free=0U;
    //    trk[0].track_id = 86;
    //    msg_processor_obj.process_Track_Occupancy(trk[0],111);
    //    atss_atc_processing_obj.SetOccupiedInfoTest(86,(char*)"TC86L",1,86,111);sleep(2);
    //    route_set_processing_obj.DwellTimeAndInterstationStopInOccupiedTrackMap();
    //    pids_pas_class_obj.processHeadwayNextArrivalPidsPas();
    //    pids_pas_class_obj.processHeadwayNextThreeDepartures();
    //dwell time
    //    sleep(1);
    //    route_set_processing_obj.RemoveTrackFromOccupiedTrackMap((char*)"TC86L",CENTRAL_ATS_MODE);
    //////////////////////////////////////////////////////////////////////////////////////
    //headway actual
    //    trk[0].is_free=0U;
    //    trk[0].track_id = 74;
    //    msg_processor_obj.process_Track_Occupancy(trk[0],111);
    //    atss_atc_processing_obj.SetOccupiedInfoTest(74,(char*)"TC74L",1,74,111);sleep(2);
    //    route_set_processing_obj.DwellTimeAndInterstationStopInOccupiedTrackMap();
    //    pids_pas_class_obj.processHeadwayNextArrivalPidsPas();
    //    pids_pas_class_obj.processHeadwayNextThreeDepartures();
    //    //dwell time
    //    sleep(1);
    //    route_set_processing_obj.RemoveTrackFromOccupiedTrackMap((char*)"TC74L",CENTRAL_ATS_MODE);

    //////////////////////////////////////////////////////////////////////////////////////


    trk[0].is_free=0U;
    trk[0].track_id = 64;
    msg_processor_obj.process_Track_Occupancy(trk[0],111);
    atss_atc_processing_obj.SetOccupiedInfoTest(64,(char*)"TC64L",1,64,111);sleep(2);
    route_set_processing_obj.DwellTimeAndInterstationStopInOccupiedTrackMap();
    pids_pas_class_obj.processHeadwayNextArrivalPidsPas();
    pids_pas_class_obj.processHeadwayNextThreeDepartures();
    //dwell time
    sleep(1);
    route_set_processing_obj.RemoveTrackFromOccupiedTrackMap((char*)"TC64L",ADD_FROM_SELF_ATSS);
    // ////////////////////////////////////////////////////////////////////////////////
}

void SendDifferentRake()
{
    UINT_8 point_id = 1;
    UINT_8 cbi_id =101 ;
    UINT_32 key;
    STRUCT_POINT_PARENT_DATA point_info; memset(&point_info,0,sizeof(point_info));


    point_id= 1;
    key = point_id*1000+cbi_id; point_info = xml_config.GetPointDataMap(key); atss_point_info_obj.set_Point_Normal(point_info,POINT_POSITION_NORMAL);
    point_id= 3;
    key = point_id*1000+cbi_id; point_info = xml_config.GetPointDataMap(key); atss_point_info_obj.set_Point_Normal(point_info,POINT_POSITION_NORMAL);
    point_id= 4;
    key = point_id*1000+cbi_id; point_info = xml_config.GetPointDataMap(key); atss_point_info_obj.set_Point_Normal(point_info,POINT_POSITION_NORMAL);
    point_id= 5;
    key = point_id*1000+cbi_id; point_info = xml_config.GetPointDataMap(key); atss_point_info_obj.set_Point_Normal(point_info,POINT_POSITION_NORMAL);
    point_id= 6;
    key = point_id*1000+cbi_id; point_info = xml_config.GetPointDataMap(key); atss_point_info_obj.set_Point_Normal(point_info,POINT_POSITION_NORMAL);
    point_id= 7;
    key = point_id*1000+cbi_id; point_info = xml_config.GetPointDataMap(key); atss_point_info_obj.set_Point_Normal(point_info,POINT_POSITION_NORMAL);
    point_id= 8;
    key = point_id*1000+cbi_id; point_info = xml_config.GetPointDataMap(key); atss_point_info_obj.set_Point_Normal(point_info,POINT_POSITION_NORMAL);
    point_id= 10;
    key = point_id*1000+cbi_id; point_info = xml_config.GetPointDataMap(key); atss_point_info_obj.set_Point_Normal(point_info,POINT_POSITION_NORMAL);


    STRUCT_TRACK_STATUS trk[5];
    memset(trk,0,sizeof(trk));
    trk[0].track_id = 27;
    trk[0].is_free=0U;
    trk[0].is_up_direction_route_locked = 0;
    trk[0].is_down_direction_route_locked = 1;
    msg_processor_obj.process_Track_Occupancy(trk[0],101);
    STRUCT_GENERAL_MESSAGE_ATSS msg; memset(&msg,0,sizeof(msg));
    STRUCT_ATSD_ATSS_ASSIGN_RAKE_ID assign_rake_id;
    assign_rake_id.trk_id = 27;
    assign_rake_id.cbi_id = 101;
    assign_rake_id.rake_id = 3;
    memcpy(&msg,&assign_rake_id,sizeof(assign_rake_id));
    msg_processor_obj.ProcessAssignRakeId(msg);
    msg_processor_obj.process_Track_Occupancy(trk[0],101);

    trk[0].track_id = 29; trk[0].is_down_direction_route_locked = 1;
    msg_processor_obj.process_Track_Occupancy(trk[0],101);
    msg_processor_obj.process_Track_Occupancy(trk[0],101);

    trk[0].track_id = 31; trk[0].is_down_direction_route_locked = 1;
    msg_processor_obj.process_Track_Occupancy(trk[0],101);
    msg_processor_obj.process_Track_Occupancy(trk[0],101);

    trk[0].track_id = 33; trk[0].is_down_direction_route_locked = 1;
    msg_processor_obj.process_Track_Occupancy(trk[0],101);
    msg_processor_obj.process_Track_Occupancy(trk[0],101);

    trk[0].track_id = 35; trk[0].is_down_direction_route_locked = 1;
    msg_processor_obj.process_Track_Occupancy(trk[0],101);
    msg_processor_obj.process_Track_Occupancy(trk[0],101);

    trk[0].track_id = 37; trk[0].is_down_direction_route_locked = 1;
    msg_processor_obj.process_Track_Occupancy(trk[0],101);
    msg_processor_obj.process_Track_Occupancy(trk[0],101);

    trk[0].track_id = 39;trk[0].is_down_direction_route_locked = 1;
    msg_processor_obj.process_Track_Occupancy(trk[0],101);

}

void TestTrainRevenue()
{

    INT_8 track_Name[TRACK_NAME_SIZE]={};
    TRACK_ID t_ID = 65;
    CBI_ID cbi_ID = 111;
    RAKE_ID rake_ID = 802;
    strncpy(track_Name,"",TRACK_NAME_SIZE);

    STRUCT_GENERAL_MESSAGE_ATSS gen_msg2;
    STRUCT_DBA_ATSS_TIME_TABLE_INFO load_time_table2;
    memset(&load_time_table2,0,sizeof(load_time_table2));
    sprintf(load_time_table2.struct_time_table.time_table_name,"ThreeJrny.csv");
    load_time_table2.is_switch_to_time_table_mode = 1;
    load_time_table2.struct_time_table.date.day = 8;load_time_table2.struct_time_table.date.month = 07;load_time_table2.struct_time_table.date.year = 2021;
    memcpy(&gen_msg2.body,&load_time_table2.struct_time_table,sizeof(load_time_table2.struct_time_table));
    msg_processor_obj.processInitTimeTableInfoMsg(gen_msg2);
    sleep(2);

    STRUCT_TRACK_STATUS trk[5];
    memset(trk,0,sizeof(trk));
    trk[0].track_id = t_ID;
    trk[0].is_free=1U;
    trk[0].is_up_direction_route_locked = 0;
    trk[0].is_down_direction_route_locked = 1;
    //msg_processor_obj.process_Track_Occupancy(trk[0],111);

    STRUCT_PC_ATSS_ATC_PTI_PACKET atss_atsd_pti_packet ;
    atss_atsd_pti_packet.struct_atc_pti_packet.track_id = t_ID;
    atss_atsd_pti_packet.struct_atc_pti_packet.cbi_id = cbi_ID;
    atss_atsd_pti_packet.struct_atc_pti_packet.rake_id =rake_ID;
    atss_atsd_pti_packet.struct_atc_pti_packet.driver_id = 1;
    atss_atsd_pti_packet.struct_atc_pti_packet.driving_mode = 1;
    atss_atsd_pti_packet.struct_atc_pti_packet.train_cab_number =1 ;
    atss_atsd_pti_packet.struct_atc_pti_packet.is_ready_for_departure = 1;
    atss_atsd_pti_packet.struct_atc_pti_packet.consist_id = 1;

    trk[0].track_id = t_ID;
    //    msg_processor_obj.process_Track_Occupancy(trk[0],cbi_ID);
    //    atss_atc_processing_obj.SetOccupiedInfoTest((char*)track_Name,rake_ID,t_ID,cbi_ID);
    atss_atsd_pti_packet.struct_atc_pti_packet.track_id = t_ID;
    //    atss_atc_processing_obj.sendPlatformMessagesToATC(atss_atsd_pti_packet.struct_atc_pti_packet);
    route_set_processing_obj.DwellTimeAndInterstationStopInOccupiedTrackMap();
    //    route_set_processing_obj.TrainDeparturefromPlatform((char*)"TC65L",rake_ID);
    pids_pas_class_obj.processNextArrivalPidsPas();
    pids_pas_class_obj.processNextThreeDepartures();
    time_table_obj.printTimeTable();

    sleep(1);
    trk[0].track_id = t_ID;
    msg_processor_obj.process_Track_Occupancy(trk[0],111);
    //    atss_atc_processing_obj.SetOccupiedInfoTest((char*)"TC75L",rake_ID,75,111);
    atss_atsd_pti_packet.struct_atc_pti_packet.track_id = t_ID;
    //    atss_atc_processing_obj.sendPlatformMessagesToATC(atss_atsd_pti_packet.struct_atc_pti_packet);
    route_set_processing_obj.DwellTimeAndInterstationStopInOccupiedTrackMap();

    pids_pas_class_obj.processNextArrivalPidsPas();
    pids_pas_class_obj.processNextThreeDepartures();

    time_table_obj.printTimeTable();

    sleep(1);
    trk[0].track_id = 89;
    msg_processor_obj.process_Track_Occupancy(trk[0],111);
    //    atss_atc_processing_obj.SetOccupiedInfoTest((char*)"TC89L",rake_ID,89,111);
    atss_atsd_pti_packet.struct_atc_pti_packet.track_id = 89;
    //    atss_atc_processing_obj.sendPlatformMessagesToATC(atss_atsd_pti_packet.struct_atc_pti_packet);
    route_set_processing_obj.DwellTimeAndInterstationStopInOccupiedTrackMap();

    pids_pas_class_obj.processNextArrivalPidsPas();
    pids_pas_class_obj.processNextThreeDepartures();
    time_table_obj.printTimeTable();

    sleep(1);
    trk[0].track_id = 43;
    msg_processor_obj.process_Track_Occupancy(trk[0],110);
    //    atss_atc_processing_obj.SetOccupiedInfoTest((char*)"TC43K",rake_ID,43,110);
    atss_atsd_pti_packet.struct_atc_pti_packet.track_id = 43;    atss_atsd_pti_packet.struct_atc_pti_packet.cbi_id = 110;
    //    atss_atc_processing_obj.sendPlatformMessagesToATC(atss_atsd_pti_packet.struct_atc_pti_packet);
    route_set_processing_obj.DwellTimeAndInterstationStopInOccupiedTrackMap();
    pids_pas_class_obj.processNextArrivalPidsPas();
    pids_pas_class_obj.processNextThreeDepartures();
    time_table_obj.printTimeTable();
    sleep(1);

    trk[0].track_id = 53;
    msg_processor_obj.process_Track_Occupancy(trk[0],110);
    //    atss_atc_processing_obj.SetOccupiedInfoTest((char*)"TC53K",rake_ID,53,110);
    atss_atsd_pti_packet.struct_atc_pti_packet.track_id = 53;    atss_atsd_pti_packet.struct_atc_pti_packet.cbi_id = 110;
    //    atss_atc_processing_obj.sendPlatformMessagesToATC(atss_atsd_pti_packet.struct_atc_pti_packet);
    route_set_processing_obj.DwellTimeAndInterstationStopInOccupiedTrackMap();
    pids_pas_class_obj.processNextArrivalPidsPas();
    pids_pas_class_obj.processNextThreeDepartures();
    time_table_obj.printTimeTable();

    sleep(1);
    trk[0].track_id = 63;
    msg_processor_obj.process_Track_Occupancy(trk[0],110);
    //    atss_atc_processing_obj.SetOccupiedInfoTest((char*)"TC63K",rake_ID,63,110);
    atss_atsd_pti_packet.struct_atc_pti_packet.track_id = 63;    atss_atsd_pti_packet.struct_atc_pti_packet.cbi_id = 110;
    //    atss_atc_processing_obj.sendPlatformMessagesToATC(atss_atsd_pti_packet.struct_atc_pti_packet);
    route_set_processing_obj.DwellTimeAndInterstationStopInOccupiedTrackMap();
    pids_pas_class_obj.processNextArrivalPidsPas();
    pids_pas_class_obj.processNextThreeDepartures();
    time_table_obj.printTimeTable();
}

void TestpidpasArrival()
{

    STRUCT_GENERAL_MESSAGE_ATSS gen_msg2;
    STRUCT_DBA_ATSS_TIME_TABLE_INFO load_time_table2;
    memset(&load_time_table2,0,sizeof(load_time_table2));
    sprintf(load_time_table2.struct_time_table.time_table_name,"ThreeJrny.csv");
    load_time_table2.is_switch_to_time_table_mode = 1;
    load_time_table2.struct_time_table.date.day = 5;load_time_table2.struct_time_table.date.month = 07;load_time_table2.struct_time_table.date.year = 2021;
    memcpy(&gen_msg2.body,&load_time_table2.struct_time_table,sizeof(load_time_table2.struct_time_table));
    msg_processor_obj.processInitTimeTableInfoMsg(gen_msg2);
    sleep(2);

    STRUCT_TRACK_STATUS trk[5];
    memset(trk,0,sizeof(trk));
    trk[0].track_id = 65;
    trk[0].is_free=1U;
    trk[0].is_up_direction_route_locked = 0;
    trk[0].is_down_direction_route_locked = 1;
    msg_processor_obj.process_Track_Occupancy(trk[0],111);


    STRUCT_PC_ATSS_ATC_PTI_PACKET atss_atsd_pti_packet ;
    atss_atsd_pti_packet.struct_atc_pti_packet.track_id = 65;
    atss_atsd_pti_packet.struct_atc_pti_packet.cbi_id = 111;
    atss_atsd_pti_packet.struct_atc_pti_packet.rake_id = 0;
    atss_atsd_pti_packet.struct_atc_pti_packet.driver_id = 1;
    atss_atsd_pti_packet.struct_atc_pti_packet.driving_mode = 1;
    atss_atsd_pti_packet.struct_atc_pti_packet.train_cab_number =1 ;
    atss_atsd_pti_packet.struct_atc_pti_packet.is_ready_for_departure = 1;
    atss_atsd_pti_packet.struct_atc_pti_packet.consist_id = 1;

    //    atss_atc_processing_obj.sendPlatformMessagesToATC(atss_atsd_pti_packet.struct_atc_pti_packet);

    sleep(2);

    pids_pas_class_obj.processNextArrivalPidsPas();
    pids_pas_class_obj.processNextThreeDepartures();
    ////////////////////////////////
    //        STRUCT_TRACK_STATUS trk[5];
    trk[0].track_id = 65;
    trk[0].is_free=0U;
    trk[0].is_up_direction_route_locked = 0;
    trk[0].is_down_direction_route_locked = 0;
    msg_processor_obj.process_Track_Occupancy(trk[0],111);

    INT_8 track_name[15]={};
    xml_config.GetTrackName(trk[0].track_id,111,track_name);
    route_set_processing_obj.RemoveTrackFromOccupiedTrackMap(track_name);

    memset(trk,0,sizeof(trk));
    trk[0].track_id = 67;
    trk[0].is_free=1U;
    trk[0].is_up_direction_route_locked = 0;
    trk[0].is_down_direction_route_locked = 1;
    msg_processor_obj.process_Track_Occupancy(trk[0],111);

    //    atss_atc_processing_obj.sendPlatformMessagesToATC(atss_atsd_pti_packet.struct_atc_pti_packet);

    pids_pas_class_obj.processNextArrivalPidsPas();
    pids_pas_class_obj.processNextThreeDepartures();
}
void TestInterstationStop()
{
    for(;;)
    {
        sleep(1);
        STRUCT_TRACK_STATUS trk[5];
        memset(trk,0,sizeof(trk));
        trk[0].track_id = 65;
        trk[0].is_free=1U;
        trk[0].is_up_direction_route_locked = 1;
        trk[0].is_down_direction_route_locked = 0;
        msg_processor_obj.process_Track_Occupancy(trk[0],111);
        route_set_processing_obj.DwellTimeAndInterstationStopInOccupiedTrackMap();
        //        route_set_processing_obj.PrintOccupiedTrackMap();
    }
}

void Test1()
{
    STRUCT_GENERAL_MESSAGE_ATSS gen_msg2;
    gen_msg2.msg_header.source_id = CSCI_ATSD;
    gen_msg2.msg_header.dest_id = CSCI_ATSS;
    gen_msg2.msg_header.message_id = ATSD_ATSS_REQ_FOR_TIMETABLE;
    gen_msg2.msg_header.ows_id = 2;
    gen_msg2.msg_header.no_of_packets = 1;
    gen_msg2.msg_header.packet_number = 1;
    gen_msg2.msg_header.message_length = sizeof (gen_msg2);

    STRUCT_DBA_ATSS_TIME_TABLE_INFO load_time_table2;
    memset(&load_time_table2,0,sizeof(load_time_table2));
    sprintf(load_time_table2.struct_time_table.time_table_name,"SmallTrain.csv");
    load_time_table2.is_switch_to_time_table_mode = 1;
    load_time_table2.struct_time_table.date.day = 2;
    load_time_table2.struct_time_table.date.month = 8;
    load_time_table2.struct_time_table.date.year = 2021;
    //    sprintf(load_time_table2.struct_time_table.time_table_name,"TTOnline_2_8_2021_registered.csv");
    //    load_time_table2.struct_time_table.timetable_state = 1;
    //    load_time_table2.struct_time_table.date.day = 2;
    //    load_time_table2.struct_time_table.date.month = 8;
    //    load_time_table2.struct_time_table.date.year = 2021;

    memcpy(&gen_msg2.body,&load_time_table2.struct_time_table,sizeof(load_time_table2.struct_time_table));
    msg_processor_obj.processInitTimeTableInfoMsg(gen_msg2);

    time_table_obj.printTimeTable();
    sleep(2);

    STRUCT_TRACK_STATUS trk[5];
    memset(trk,0,sizeof(trk));
    trk[0].track_id = 5;
    trk[0].is_free=0U;
    trk[0].is_up_direction_route_locked = 0;
    trk[0].is_down_direction_route_locked = 0;
    msg_processor_obj.process_Track_Occupancy(trk[0],104);

    STRUCT_PC_ATSS_ATC_PTI_PACKET atss_atsd_pti_packet ;
    atss_atsd_pti_packet.struct_atc_pti_packet.track_id = 5;
    atss_atsd_pti_packet.struct_atc_pti_packet.cbi_id = 104;
    atss_atsd_pti_packet.struct_atc_pti_packet.rake_id = 1;
    atss_atsd_pti_packet.struct_atc_pti_packet.driver_id = 1;
    atss_atsd_pti_packet.struct_atc_pti_packet.driving_mode = 1;
    atss_atsd_pti_packet.struct_atc_pti_packet.train_cab_number =1 ;
    atss_atsd_pti_packet.struct_atc_pti_packet.is_ready_for_departure = 1;
    atss_atsd_pti_packet.struct_atc_pti_packet.consist_id = 1;

    //    atss_atc_processing_obj.sendPlatformMessagesToATC(atss_atsd_pti_packet.struct_atc_pti_packet);
    sleep(5);

    // pids_pas_class_obj.processDeparturePidsPas();

    time_table_obj.printTimeTable();
}
void SaveTTasMaps()
{
    //  QMap<string,>
    //QMap <JOURNEY_ID,STRUCT_TRIP_NAME>JourneyTripMap;
    //QMap <STRUCT_TRIP_NAME,STRUCT_STOPING_POINT_DETAIL>TripPlatformMap;
    INT_8  time_table_name[1000] = {0};

    UINT_8 return_flag                  = 1U;
    UINT_8 max_journey_column           = 0U;
    UINT_8 journey_data_column          = 0U;
    UINT_8 time_table_name_column       = 0U;
    UINT_8 train_number_data_column     = 0U;

    INT_32 textcnt                      = 0U;

    UINT_32  col_id                     = 0U;
    UINT_32  journey_id                 = 0U;
    UINT_32  read_column                = 0U;
    UINT_32  platform_id                = 0U;
    UINT_32  max_platform_id            = 0U;
    UINT_32  max_no_of_journeys         = 0U;
    UINT_32  time_table_name_length     = 0U;
    UINT_32  max_no_of_rows_per_journey = 0U;
    UINT_32  max_no_of_trips_per_journey= 0U;

    UINT_8 insert_data_flag = 0U;
    UINT_8 row_insert_data_flag = 0U;
    UINT_32 row_id = 0U;
    //UINT_32 col_id = 0U;
    UINT_32 sub_col_id = 0U;
    std::string line, colname, subcolname;

    STRUCT_PRINT_DATA_INTERNAL struct_print_internal;
    STRUCT_STOPING_POINT_DETAIL_INTERNAL struct_stopping_point_detail;

    memset(&struct_print_internal,0,sizeof(struct_print_internal));
    memset(&struct_stopping_point_detail,0,sizeof(struct_stopping_point_detail));

    struct_print_internal.nlcnt = 1U;
    struct_print_internal.tcnt = 0U;

    sprintf(time_table_name,"C:\\ATS\\TimeTable\\%s",(char*)"TenTrainFullLine.csv");
    std::ifstream file(time_table_name);

    if(file.is_open()==1U)
    {
        while((file.eof()==0U) && (return_flag == 1U))
        {
            getline(file, line);
            std::stringstream ss(line);
            col_id=0U;

            while((std::getline(ss, colname, ',')) && (return_flag == 1U))
            {
                col_id++;

                if((time_table_name_column==1U) && (read_column == col_id))
                {
                    INT_8  time_table_name[MAX_TIME_TABLE_NAME_STR] = {0};
                    time_table_name_length = colname.length();
                    strncpy(time_table_name, colname.c_str(), time_table_name_length);
                    return_flag = time_table_validate_data_obj.SetTimeTableName(time_table_name, time_table_name_length);
                    time_table_name_column=0U;
                    max_journey_column=0U;
                    read_column=0U;
                }
                else if((max_journey_column==1U) && (read_column == col_id))
                {
                    max_no_of_journeys = static_cast<UINT_32>(atoi(colname.c_str()));
                    return_flag = time_table_validate_data_obj.SetMaxNumberOfJourneys(max_no_of_journeys);
                    max_journey_column=0U;
                    read_column=0U;
                }
                else if((journey_data_column==1U) && ((read_column+1U) == col_id))
                {
                    if(strcmp(colname.c_str(),"BLANK")!=0)
                    {
                        struct_stopping_point_detail.rake_id = atoi(colname.c_str());
                    }
                }
                else if((journey_data_column==1U) && ((read_column+3U) == col_id))
                {
                    max_no_of_rows_per_journey = atoi(colname.c_str());

                    return_flag = time_table_validate_data_obj.SetRowCountVector(journey_id, max_no_of_rows_per_journey);
                    return_flag = time_table_validate_data_obj.InitializeJourneyVectorTimeTable(journey_id, max_no_of_rows_per_journey);
                    journey_data_column=0U;
                    read_column=0U;
                }
                //////////////////////////////////////////////////
                if((col_id==COL_JOURNEY_TRIP_TRIP_ID)&&(row_insert_data_flag==1U))
                {
                    row_id++;
                    row_insert_data_flag=1U;
                    struct_stopping_point_detail.journey_id = journey_id;
                    memset(struct_stopping_point_detail.trip_id_name,0,sizeof(struct_stopping_point_detail.trip_id_name));
                    strncpy(struct_stopping_point_detail.trip_id_name, colname.c_str(), colname.length());
                    //strcpy(struct_stopping_point_detail.trip_id_name, colname.c_str());
                }
                else if((col_id==COL_JOURNEY_TRIP_STATION_ID)&&(row_insert_data_flag==1U))
                {
                    struct_stopping_point_detail.station_id = atoi(colname.c_str());
                }
                else if((col_id==COL_JOURNEY_TRIP_PLATFORM_ID)&&(row_insert_data_flag==1U))
                {
                    struct_stopping_point_detail.platform_id = atoi(colname.c_str());
                }
                else if((col_id==COL_JOURNEY_TRIP_CREW_ID)&&(row_insert_data_flag==1U))
                {
                    struct_stopping_point_detail.crew_id = atoi(colname.c_str());
                }
                else if((col_id==COL_JOURNEY_TRIP_SCHD_ARR)&&(row_insert_data_flag==1U))
                {
                    std::stringstream ss_temp(colname);
                    sub_col_id = 0U;
                    while(std::getline(ss_temp, subcolname,':'))
                    {
                        sub_col_id++;
                        if(sub_col_id==SUBCOL_JOURNEY_TRIP_HOUR)
                        {
                            struct_stopping_point_detail.sched_arrival.hour = (UINT_8)(atoi(subcolname.c_str()));
                        }
                        else if(sub_col_id==SUBCOL_JOURNEY_TRIP_MIN)
                        {
                            struct_stopping_point_detail.sched_arrival.minute = (UINT_8)(atoi(subcolname.c_str()));
                        }
                        else if(sub_col_id==SUBCOL_JOURNEY_TRIP_SEC)
                        {
                            struct_stopping_point_detail.sched_arrival.second = (UINT_8)(atoi(subcolname.c_str()));
                            struct_stopping_point_detail.sched_arrival.calc_secs =
                                    (struct_stopping_point_detail.sched_arrival.hour * 3600U)
                                    + (struct_stopping_point_detail.sched_arrival.minute * 60U)
                                    + (struct_stopping_point_detail.sched_arrival.second);
                        }
                    }
                }
                else if((col_id==COL_JOURNEY_TRIP_SCHD_DEP)&&(row_insert_data_flag==1U))
                {
                    std::stringstream ss_temp(colname);
                    sub_col_id = 0U;
                    while(std::getline(ss_temp, subcolname, ':'))
                    {
                        sub_col_id++;
                        if(sub_col_id==SUBCOL_JOURNEY_TRIP_HOUR)
                        {
                            struct_stopping_point_detail.sched_depart.hour = (UINT_8)(atoi(subcolname.c_str()));
                        }
                        else if(sub_col_id==SUBCOL_JOURNEY_TRIP_MIN)
                        {
                            struct_stopping_point_detail.sched_depart.minute = (UINT_8)(atoi(subcolname.c_str()));
                        }
                        else if(sub_col_id==SUBCOL_JOURNEY_TRIP_SEC)
                        {
                            struct_stopping_point_detail.sched_depart.second = (UINT_8)(atoi(subcolname.c_str()));
                            struct_stopping_point_detail.sched_depart.calc_secs =
                                    (struct_stopping_point_detail.sched_depart.hour * 3600U)
                                    + (struct_stopping_point_detail.sched_depart.minute * 60U)
                                    + (struct_stopping_point_detail.sched_depart.second);
                        }
                    }
                }
                else if((col_id==COL_JOURNEY_TRIP_DWELL_TIME)&&(row_insert_data_flag==1U))
                {
                    struct_stopping_point_detail.dwell_time = atoi(colname.c_str());
                }
                else if((col_id==COL_JOURNEY_TRIP_PERFOR_REG)&&(row_insert_data_flag==1U))
                {
                    struct_stopping_point_detail.performance_regime = atoi(colname.c_str());
                }
                else if((col_id==COL_JOURNEY_TRIP_SERV_TYPE)&&(row_insert_data_flag==1U))
                {
                    struct_stopping_point_detail.service_type = atoi(colname.c_str());
                }
                else if((col_id==COL_JOURNEY_TRIP_DIRECTION)&&(row_insert_data_flag==1U))
                {
                    struct_stopping_point_detail.direction = atoi(colname.c_str());
                    insert_data_flag = 1U;
                    //                    struct_print_internal.textcnt = sprintf(struct_print_internal.print_str,"LastField insert_data_flag=%d return_flag=%d ",insert_data_flag, return_flag );
                    //                    PrintDataStruct(struct_print_internal,LOG_EXTRA_NIMP_TTV);
                    break;
                }
                ////////////////////////////////////////////////////

                if(return_flag == 1U)
                {
                    if(strcmp(colname.c_str(),"TimeTable_Name")==0)
                    {
                        time_table_name_column=1U;
                        max_journey_column=0U;
                        train_number_data_column=0U;
                        read_column=1;
                        break;
                    }
                    else if(strcmp(colname.c_str(),"No_of_Journey")==0)
                    {
                        time_table_name_column=0U;
                        max_journey_column=1U;
                        train_number_data_column=0U;
                        read_column=1;
                        break;
                    }
                    else if(strcmp(colname.c_str(),"Journey_ID")==0)
                    {
                        journey_id++;
                        ////////////////////////////////////
                        //                        string digit;
                        //                        string str = colname.c_str();
                        //                        for(long unsigned int i = 0; i < colname.length();i++)
                        //                        {
                        //                            if(isdigit(str[i]))
                        //                            {
                        //                                digit.push_back(str[i]);
                        //                            }
                        //                        }

                        //                        journey_id_time_table = stoi(digit);
                        ///////////////////////////////////

                        time_table_name_column=0U;
                        journey_data_column=1U;
                        train_number_data_column=0U;
                        read_column=1U;
                        row_id=0U;
                        col_id=0U;
                        row_insert_data_flag=0U;
                        break;
                    }
                    else if((col_id==1U)&&(strcmp(colname.c_str(),"Train_Number")==0))
                    {
                        row_id=0U;
                        col_id=0U;
                        row_insert_data_flag=1U;
                        break;
                    }
                }
            };
            if((insert_data_flag == 1U)  && (return_flag == 1U))
            {
                return_flag = time_table_validate_data_obj.SetTimeTableVector(struct_stopping_point_detail.journey_id, row_id, struct_stopping_point_detail);
                //row_insert_data_flag=0U;
                insert_data_flag = 0U;
                //struct_print_internal.textcnt = sprintf(struct_print_internal.print_str,"AfterSet insert_data_flag=%d return_flag=%d ",insert_data_flag, return_flag );
                //PrintDataStruct(struct_print_internal,LOG_EXTRA_NIMP_TTV);
                //if(return_flag == 1U){
                ///	return_flag =	SetStoppingPointVector(struct_stopping_point_detail.platform_id, struct_stopping_point_detail);
                //}
            }
        }
        file.close();
    }
}

vector<int> Tokeniser(string s, string del=".")
{
    vector<int> v;
    int start =0;
    int end = s.find(del);
    while (end!=-1)
    {
        string s1 = s.substr(start,end-start);
        v.push_back(std::stoi(s1));
        start = end + del.size();
        end = s.find(del,start);
    }
    string s2 = s.substr(start,end-start);
    v.push_back(std::stoi(s2));
    //cout<<s.substr(start,end-start);
    return v;
}

int test(string s1,string s2)
{
    int result =0;
    int v1=0,v2 =0;

    // s1 consists of numbers and . only
    vector <int > vec1,vec2;
    vec1 = Tokeniser(s1);
    vec2 = Tokeniser(s2);
    int count =0;

    int size = 0;
    int size1 = vec1.size();
    int size2 =vec2.size();
    if(size1>size2)
    {
        size = size1;
    }
    else
        size = size2;
    for(int i=0;i<size;i++)
    {
        if(i<size1)
        {
            v1=vec1[i];
        }
        else
            v1=0;
        if(i<size2)
        {
            v2=vec2[i];
        }
        else
            v2=0;

        if(v1<v2)
        {
            result = -1;
            break;
        }
        else if(v1>v2)
        {
            result =1;
            break;
        }
        cout<<"\n"<<++count<<") v1,v2="<<v1<<" "<<v2<<"result="<<result<<endl;
    }
    cout<<++count<<") v1,v2="<<v1<<" "<<v2<<"result="<<result<<endl;
    return result;
}

int main(int argc, char** argv)
{
    int final_res =  test("1","1.0.11.00");
    cout<<"\n final="<<final_res<<endl;
    return 0;
}
