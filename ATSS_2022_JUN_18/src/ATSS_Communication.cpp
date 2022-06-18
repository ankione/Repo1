#include "inc/ATSS_Includes.h"

extern ATSS_DBData DBData_obj;
extern ATSS_MessageProcessor msg_processor_obj;

ATSS_Communication :: ATSS_Communication()
{
    //printf("\n ATSS_Communication constructor call");
    c_atss_recv_socket_id = 0;
    c_atss_send_socket_id = 0;
    //application_state     = 1;
    //24Aug2021

    application_state     = CSCI_STATE_TEMP;

    data_logger_alive_flag = false;
    data_logger_not_alive_counter=0;


    //24Aug2021
}

ATSS_Communication::~ATSS_Communication()
{
#ifdef WINDOWS_VER
    closesocket(recv_socket);
    WSACleanup();
#endif
}


void ATSS_Communication :: SetApplicationStateRuntime(int app_state)
{
    INT_8 print_str[MAX_PRINT_STR] = {0};
    INT_32 textcnt = 0;

    textcnt = sprintf(print_str,"\nCurrentAppState\t\t= %d",app_state);



    //    if(app_state == CSCI_STATE_TEMP)
    //    {
    //        /// request state from ACTIVE server
    //        STRUCT_MESSAGE_HEADER msg_hdr;
    //        memset(&msg_hdr, 0, sizeof(msg_hdr));

    //        msg_hdr.dest_id          = CSCI_ATSS;
    //        msg_hdr.source_id        = CSCI_ATSS;
    //        msg_hdr.message_id       = ATSS_ATSS_CHECKPOINT_REQUEST_ID;
    //        msg_hdr.message_length   = sizeof(msg_hdr);
    //        msg_hdr.level_id         = xml_config.GetCurrentATSSId();
    //ip-based - to active
    //        if(msg_hdr.level_id<=MAXIMUM_CENTRAL_ATS_LEVEL)
    //        {
    //            SendDataToUDP((INT_8*)&msg_hdr,sizeof(msg_hdr),DATA_COMM_MODE_CATS_CHECKPOINT); /// for central ATS only
    //        }
    //        else if(msg_hdr.level_id>MAXIMUM_CENTRAL_ATS_LEVEL)
    //        {
    //            SendDataToUDP((INT_8*)&msg_hdr,sizeof(msg_hdr),DATA_COMM_MODE_LATS_CHECKPOINT); /// for LATS only
    //        }
    //    }
}

void ATSS_Communication :: SetApplicationState(int app_state)
{
    INT_8 print_str[MAX_PRINT_STR] = {0};
    INT_32 textcnt = 0;

    textcnt = sprintf(print_str,"\nSetAppState\t\t= %d",app_state);



    application_state = app_state;
}
int ATSS_Communication :: GetApplicationState()
{
    return application_state;
}
UINT_8 ATSS_Communication :: InitializeATSSSocket()
{
    INT_8 print_str[MAX_PRINT_STR] = {0};
    UINT_8 return_flag = false;
    UINT_8 nlcnt = 1;
    UINT_8 tcnt = 1;
    INT_32 textcnt = 0;


#ifdef LINUX_VER
    //--------------------------------------------------------------------------------------------------------------------
    // Creation of recv socket
    //--------------------------------------------------------------------------------------------------------------------
    ATS_NODE_CONFIG_COMM_DETAILS config_data = xml_config.get_Comm_Details(xml_config.GetCurrentATSSId(),CSCI_ATSS, xml_config.GetSelfOwsId());

    c_atss_recv_socket.sin_family	= AF_INET;
    c_atss_recv_socket.sin_port		= htons(config_data.port_no);
    c_atss_recv_socket.sin_addr.s_addr	= htons(INADDR_ANY);
    c_atss_recv_socket_id 			= socket(AF_INET,SOCK_DGRAM,0);
    if(c_atss_recv_socket_id<0)
    {
        perror("\nERROR ");
        fflush(stdout);
        textcnt = sprintf(print_str,"\nERROR - ATSS_RECV_PORT");

    }
    else
    {
        if (bind(c_atss_recv_socket_id, (const struct sockaddr *) &c_atss_recv_socket,sizeof(c_atss_recv_socket)) < 0)
        {
            perror("\nERROR ");
            textcnt = sprintf(print_str,"\nERROR - ATSS_RECV_PORT\t= %d",config_data.port_no);

        }
        else
        {
            textcnt = sprintf(print_str,"\n\n ATSS_RECV_PORT\t= %d",config_data.port_no);
            ,LOG_ATSS_INFO);
        }
    }

    //--------------------------------------------------------------------------------------------------------------------
    // Creation of ATSS_SEND_TO_PC_CHANNEL socket
    //--------------------------------------------------------------------------------------------------------------------

    config_data = xml_config.get_Comm_Details(xml_config.GetCurrentATSSId(),CSCI_PC, xml_config.GetSelfOwsId());
    atts_send_PC_socket.sin_family         = AF_INET;
    atts_send_PC_socket.sin_port           = htons(config_data.port_no);
    atts_send_PC_socket.sin_addr.s_addr    = inet_addr(config_data.IPP_ADD);
    c_atss_send_PC_socket_id               = socket(AF_INET,SOCK_DGRAM,0);

    if(c_atss_send_PC_socket_id<0)
    {
        perror("\nERROR ");
        fflush(stdout);
        textcnt = sprintf(print_str,"ERROR PC_PORT\t= %d",config_data.port_no);
        ,LOG_ATSS_PC);
    }
    else
    {
        textcnt = sprintf(print_str,"\n ATSS_PC_PORT\t= %d",config_data.port_no);
        ,LOG_ATSS_PC);
    }


    //--------------------------------------------------------------------------------------------------------------------
    // Creation of ATSS_SEND_TO_DBA_CHANNEL socket
    //--------------------------------------------------------------------------------------------------------------------


    STRUCT_ATSD_BROADCAST_PORT_IP atsd_bcast_port_ip;
    memset(&atsd_bcast_port_ip,0,sizeof(atsd_bcast_port_ip));
    atsd_bcast_port_ip = xml_config.GetATSDBROADCASTportIP();
    config_data = xml_config.get_Comm_Details(xml_config.GetCurrentATSSId(),CSCI_DBA, xml_config.GetSelfOwsId());

    atts_send_DBA_socket.sin_family         = AF_INET;
    atts_send_DBA_socket.sin_port           = htons(config_data.port_no);
    atts_send_DBA_socket.sin_addr.s_addr    = inet_addr(atsd_bcast_port_ip.UDPADDRESS_BROADCAST);

    c_atss_send_DBA_socket_id               = socket(AF_INET,SOCK_DGRAM,0);

    INT_32 brodcast=1;
    if(c_atss_send_DBA_socket_id<0)
    {
        perror("ERROR ");
        fflush(stdout);
        textcnt = sprintf(print_str,"ERROR DBA_PORT\t= %d",config_data.port_no);

    }
    else
    {
        textcnt = sprintf(print_str,"\n ATSS_DBA_PORT\t= %d",config_data.port_no);
        ,LOG_ATSS_DB);
        if(setsockopt(c_atss_send_DBA_socket_id, SOL_SOCKET, SO_BROADCAST, &brodcast, sizeof(brodcast)) == -1)
        {
            perror("\nERROR ");
            textcnt = sprintf(print_str,"ERROR: setsockopt BROADCAST");
            printf(BOLDYELLOW);

            printf(RESET);
        }
    }

    //--------------------------------------------------------------------------------------------------------------------
    // Creation of ATSS_SEND_TO_ATSD_CHANNEL socket
    //--------------------------------------------------------------------------------------------------------------------


    for(int k=0; k<MAX_NUM_OF_WORKSTATIONS_XML;k++)
    {
        config_data = xml_config.get_Comm_Details(xml_config.GetCurrentATSSId(),CSCI_ATSD, k+1);

        if(config_data.port_no!=0)
        {
            atts_send_ATSD_socket[k].sin_family         = AF_INET;
            atts_send_ATSD_socket[k].sin_port           = htons(config_data.port_no);
            atts_send_ATSD_socket[k].sin_addr.s_addr    = inet_addr(config_data.IPP_ADD);
            c_atss_send_ATSD_socket_id[k]               = socket(AF_INET,SOCK_DGRAM,0);

            //printf("\nport %d ip %s s_addr=%d",atsd_port_ip.ATSS_ATSD_PORT,atsd_port_ip.UDPADDRESS_ATSD, atts_send_ATSD_socket[k].sin_addr.s_addr);
            if(c_atss_send_ATSD_socket_id[k]<0)
            {
                perror("\nERROR ");
                fflush(stdout);
                textcnt = sprintf(print_str,"ERROR ATSD_PORT\t= %d",config_data.port_no);

            }
            else
            {
                textcnt = sprintf(print_str,"\n ATSS_ATSD_PORT\t= %d",config_data.port_no);
                ,LOG_ATSS_ATSD);

            }
        }
    }

    //--------------------------------------------------------------------------------------------------------------------
    // Creation of ATSS_SEND_TO_AMSM_CHANNEL socket
    //--------------------------------------------------------------------------------------------------------------------
    atts_send_AMSM_socket.sin_family         = AF_INET;
    atts_send_AMSM_socket.sin_port           = 10001;
    atts_send_AMSM_socket.sin_addr.s_addr    = inet_addr("127.0.0.1");
    c_atss_send_AMSM_socket_id               = socket(AF_INET,SOCK_DGRAM,0);

    //printf("\nport %d ip %s s_addr=%d",atsd_port_ip.ATSS_ATSD_PORT,atsd_port_ip.UDPADDRESS_ATSD, atts_send_ATSD_socket.sin_addr.s_addr);
    if(c_atss_send_AMSM_socket_id<0)
    {
        perror("\nERROR ");
        fflush(stdout);
        textcnt = sprintf(print_str,"ERROR - AMSM_PORT\t= %d",config_data.port_no);

    }
    else
    {
        textcnt = sprintf(print_str,"\n ATSS_AMSM_PORT\t= %d",config_data.port_no);
        ,LOG_ATSS_AMSM);
    }


    //--------------------------------------------------------------------------------------------------------------------
    // Creation of ATSS_SEND_TO_ATSD_BROADCAST_CHANNEL socket
    //--------------------------------------------------------------------------------------------------------------------
    //    STRUCT_ATSD_BROADCAST_PORT_IP atsd_bcast_port_ip;
    //    memset(&atsd_bcast_port_ip,0,sizeof(atsd_bcast_port_ip));

    //    atsd_bcast_port_ip = xml_config.GetATSDBROADCASTportIP();
    atts_send_ATSD_BROADCAST_socket.sin_family         = AF_INET;
    atts_send_ATSD_BROADCAST_socket.sin_port           = htons(atsd_bcast_port_ip.ATSS_ATSD_BROADCAST_PORT);//htons(ATSS_SEND_TO_ATSD_CHANNEL_PORT);
    atts_send_ATSD_BROADCAST_socket.sin_addr.s_addr    = inet_addr(atsd_bcast_port_ip.UDPADDRESS_BROADCAST);//inet_addr("192.168.34.31");
    c_atss_send_BROADCAST_socket_id                    = socket(AF_INET,SOCK_DGRAM,0);


    if(c_atss_send_BROADCAST_socket_id<0)
    {
        perror("\nERROR");
        printf(BOLDYELLOW);
        textcnt = sprintf(print_str,"ERROR:BROADCAST_PORT = %d",atsd_bcast_port_ip.ATSS_ATSD_BROADCAST_PORT);

        printf(RESET);
    }
    else
    {
        textcnt = sprintf(print_str,"\n ATSS_BROADCST_PORT\t= %d",atsd_bcast_port_ip.ATSS_ATSD_BROADCAST_PORT);
        printf(BOLDYELLOW);
        ,LOG_ATSS_INFO);
        printf(RESET);

        if(setsockopt(c_atss_send_BROADCAST_socket_id, SOL_SOCKET, SO_BROADCAST, &brodcast, sizeof(brodcast)) == -1)
        {
            perror("\nERROR ");
            textcnt = sprintf(print_str,"ERROR: setsockopt BROADCAST");
            printf(BOLDYELLOW);

            printf(RESET);
        }
    }

    //  --------------------------------------------------------------------------------------------------------------------
    //   Creation of ATSS_SEND_TO_TVSS_CHANNEL socket
    //  --------------------------------------------------------------------------------------------------------------------
    atts_send_socket.sin_family         = AF_INET;
    atts_send_socket.sin_port           = htons(ATSS_SEND_TO_TVSS_CHANNEL_PORT);
    atts_send_socket.sin_addr.s_addr    = inet_addr("127.0.0.1");
    c_atss_send_socket_id               = socket(AF_INET,SOCK_DGRAM,0);

    if(c_atss_send_socket_id<0)
    {
        perror("\nERROR-Unable to open ATSS_SEND_TO_TVSS_CHANNEL socket - ");	fflush(stdout);
        textcnt = sprintf(print_str,"ERROR-Unable to ATSS_SEND_TO_TVSS_CHANNEL socket"); PrintData(print_str,textcnt,nlcnt,tcnt);
    }
    else
    {

        textcnt = sprintf(print_str,"\n ATSS_TVSS_PORT\t= %d\n",ATSS_SEND_TO_TVSS_CHANNEL_PORT);
        printf(BOLDCYAN);
        ,LOG_ATSS_INFO);
        printf(RESET);
    }


    //--------------------------------------------------------------------------------------------------------------------
    // Creation of ATSS_SEND_TO_RS_CHANNEL socket
    //--------------------------------------------------------------------------------------------------------------------
    //    atts_send_socket.sin_family         = AF_INET;
    //    atts_send_socket.sin_port           = htons(ATSS_SEND_TO_RS_CHANNEL_PORT);
    //    atts_send_socket.sin_addr.s_addr    = inet_addr("127.0.0.1");
    //    c_atss_send_socket_id               = socket(AF_INET,SOCK_DGRAM,0);

    //    if(c_atss_send_socket_id<0)
    //    {
    //        perror("\nERROR-Unable to open ATSS_SEND_TO_RS_CHANNEL socket - ");	fflush(stdout);
    //        textcnt = sprintf(print_str,"ERROR-Unable to ATSS_SEND_TO_RS_CHANNEL socket"); PrintData(print_str,textcnt,nlcnt,tcnt);
    //    }
    //    else
    //    {
    //        textcnt = sprintf(print_str,"ATSS_SEND_TO_RS_CHANNEL socket created successfully for Port = %d",ATSS_SEND_TO_RS_CHANNEL_PORT);
    //        PrintData(print_str,textcnt,nlcnt,tcnt,LOG_ATSS_INFO);
    //    }


    //--------------------------------------------------------------------------------------------------------------------
#endif

#ifdef WINDOWS_VER
    ATS_NODE_CONFIG_COMM_DETAILS config_data;// = xml_config.get_Comm_Details(xml_config.GetCurrentATSSId(),CSCI_ATSS, xml_config.GetSelfOwsId());

    WSAStartup( MAKEWORD( 2, 2 ), &data );
    send_socket =  socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (send_socket < 0)
    {
        perror("SEND socket");
    }

    recv_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (recv_socket < 0)
    {
        perror(" recv_socket");
    }
    ////////////////////////////////////////////////////////
    send_recorder_sock =  socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (send_recorder_sock < 0)
    {
        perror("socket RECORDER");
    }

    ////////////////////////////////////////////////////////////////////////////////////////////
    recv_addr.sin_family       = AF_INET;
    recv_addr.sin_addr.s_addr  = htons(INADDR_ANY);
    recv_addr.sin_port         = htons(config_data.port_no);
    length                     = sizeof(struct sockaddr_in);
    bool bOptVal = 1;
    int bOptLen = sizeof (BOOL);

    if (setsockopt(recv_socket, SOL_SOCKET, SO_REUSEADDR, (char *) &bOptVal, bOptLen) == SOCKET_ERROR)
    {
        //wprintf(L"setsockopt for SO_KEEPALIVE failed with error: %u\n", WSAGetLastError());
        printf("setsockopt for SO_REUSEADDR failed with error\n");
    }
    else
    {
        printf("Set SO_REUSEADDR: ON\n");
    }
    INT_8 ret_flag = bind(recv_socket, (struct sockaddr *)&recv_addr, sizeof(recv_addr));

    if(ret_flag == -1)
    {
        printf("bind problem\n");
        exit(0);
    }

#endif

    return return_flag;
}

UINT_8 ATSS_Communication :: RecieveDataFromUDP()
{
    int recv_len = 0;
    UINT_8 return_flag = false;

    INT_8 print_str[MAX_PRINT_STR] = {0};

    INT_32 textcnt = 0;
    INT_32 received_bytes = 0;

    STRUCT_GENERAL_MESSAGE_ATSS msg;
    memset(&msg,0,sizeof(msg));

    bool msg_send = true;
    while(true)
    {
#ifdef LINUX_VER
        socklen_t recv_socket_len = sizeof(c_atss_recv_socket);
        struct sockaddr_in struct_atss_recv_socket_temp;
        received_bytes = recvfrom(c_atss_recv_socket_id,(INT_8 *) &msg,MAX_COMMUNICATION_BUFFER_SIZE,
                                  0,(struct sockaddr *) &struct_atss_recv_socket_temp,&recv_socket_len);

        if(received_bytes > 0)
        {
            msg_processor_obj.allATSSIncomingMessage(msg);
        }
        else
        {
            perror("ERROR");
            textcnt = sprintf(print_str,"ERROR: RECEIVED = %d",received_bytes);

        }
#endif

#ifdef WINDOWS_VER
        recv_len = recvfrom(recv_socket,(INT_8*)&msg, MAX_COMMUNICATION_BUFFER_SIZE, 0, (struct sockaddr *)&recv_addr, &length);
        if (recv_len < 0)
        {
            perror("recvfrom");
        }
        else
        {
            if((msg.msg_header.source_id !=CSCI_DATA_LOGGER))
            {
                if(data_logger_alive_flag==true)
                {
                    SendDataToDataLogger((INT_8*)&msg, recv_len);
                }
                if(GetApplicationState()!=CSCI_STATE_TEMP)
                {
                    msg_processor_obj.allATSSIncomingMessage(msg);
                }
                else if((msg.msg_header.source_id ==CSCI_DBA) ||
                        (msg.msg_header.source_id ==CSCI_AMSM) ||
                         (msg.msg_header.source_id ==CSCI_ATSS)
                        )
                {
                    msg_processor_obj.allATSSIncomingMessage(msg);
                }
            }
            else
            {
                strcpy(ip_address_data_logger,inet_ntoa((in_addr)recv_addr.sin_addr));
                if(GetDataLoggerFlag()==false)
                {
                    textcnt = sprintf(print_str,"\nCommunication with DataLogger Started ip-%s",
                                      ip_address_data_logger);

                }
                SetDataLoggerFlag(true);
                SetDataLoggerAliveCounter(0);
                msg.msg_header.source_id = CSCI_ATSS;
                SendDataToDataLogger((INT_8*)&msg, recv_len, true);
            }
        }
#endif
    }
    return return_flag;
}

void ATSS_Communication :: SetDataLoggerFlag(UINT_8 flag)
{
    data_logger_alive_flag = flag;
}

UINT_8 ATSS_Communication :: GetDataLoggerFlag()
{
    return data_logger_alive_flag;
}

void ATSS_Communication :: IncrementDataLoggerAliveCounter()
{
    data_logger_not_alive_counter++;
}

void ATSS_Communication :: SetDataLoggerAliveCounter(UINT_8 count)
{
    data_logger_not_alive_counter = count;
}

UINT_8 ATSS_Communication :: GetDataLoggerAliveCounter()
{
    return data_logger_not_alive_counter;
}

void ATSS_Communication :: SendDataToDataLogger(INT_8 *msg, INT_32 recv_len, UINT_8 alive_flag)
{
    INT_8 print_str[MAX_PRINT_STR] = {0};

    UINT_8 nlcnt    = 1;
    UINT_8 tcnt     = 2;

    INT_32 textcnt  = 0;
    INT_32 sent_bytes = 0;

    atts_send_socket.sin_family         = AF_INET;
    atts_send_socket.sin_addr.s_addr    = inet_addr("127.0.0.1");
    atts_send_socket.sin_port           = htons(DATA_LOGGER_SEND_PORT);
    sent_bytes = sendto(send_socket, msg, recv_len, 0,(const sockaddr*) &atts_send_socket,sizeof(atts_send_socket));
    if(alive_flag==true)
    {
        textcnt = sprintf(print_str,"Alive2DL,");
                          //inet_ntoa((in_addr)atts_send_socket.sin_addr));

    }
}


UINT_8 ATSS_Communication :: SendDataToDBA(INT_8 *received_data, INT_32 data_length)
{
    INT_8 print_str[MAX_PRINT_STR] = {0};

    UINT_8 nlcnt    = 1;
    UINT_8 tcnt     = 2;
    UINT_8 return_flag  = true;

    INT_32 textcnt  = 0;
    INT_32 sent_bytes = 0;

    UINT_16 id = 0U;
    UINT_16 len = 0U;

    memcpy((void*)&id,&received_data[2],sizeof (UINT_16));
    memcpy((void*)&len,&received_data[5],sizeof (UINT_16));

    /// for state maintenance at local ATSS<-> DBA interface
    //if(GetApplicationState()== CSCI_STATE_ACTIVE)
    {
#ifdef LINUX_VER
        sent_bytes = sendto(c_atss_send_DBA_socket_id, received_data, data_length, 0,(const sockaddr*) &atts_send_DBA_socket,sizeof(atts_send_DBA_socket));

        if(sent_bytes == -1)
        {
            perror("\nERROR");
            fflush(stdout);
            textcnt = sprintf(print_str,"\nERROR :sendto()->DBA:%d (%d)\n",id,len);

            return_flag=false;
        }
        else
        {
            //          textcnt = sprintf(print_str,"\n->DBA:%d (%d)\n",id,len);
            //          ,LOG_ATSS_DB);
        }
#endif
#ifdef WINDOWS_VER
        ATS_NODE_CONFIG_COMM_DETAILS config_data;//= xml_config.get_Comm_Details(xml_config.GetCurrentATSSId(),CSCI_DBA, xml_config.GetSelfOwsId());
        send_addr.sin_family         = AF_INET;
        send_addr.sin_addr.s_addr    = inet_addr(config_data.IPP_ADD);
        send_addr.sin_port           = htons(config_data.port_no);
        length                  = sizeof(struct sockaddr_in);
        sent_bytes = sendto (send_socket, received_data, data_length, 0, (const struct sockaddr *)&send_addr, length);
#endif
    }
    if(sent_bytes == -1)
    {
        perror("\nERROR");
        fflush(stdout);
        textcnt = sprintf(print_str,"\nERROR :sendto()\n%04d (%04d) -> DBA",id,len);

        return_flag=false;
    }
    else
    {
        textcnt = sprintf(print_str,"\n%04d(%04d) -> DBA",id,len);
    }
    return return_flag;
}
