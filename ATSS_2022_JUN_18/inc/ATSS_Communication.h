#ifndef ATS_UDP_SOCKET_H
#define ATS_UDP_SOCKET_H
#include "inc/ATSS_Includes.h"

class ATSS_Communication
{
private:
    int application_state;
    /* UDP Socket Variables */
    INT_32 c_atss_recv_socket_id;

    INT_32 c_atss_recorder_send_socket_id;
    INT_32 c_atss_send_socket_id;
    INT_32 c_atss_send_DBA_socket_id;
    INT_32 c_atss_send_PC_socket_id;
    INT_32 c_atss_send_AMSM_socket_id;
    INT_32 c_atss_send_ATSD_socket_id[MAX_NUM_OF_WORKSTATIONS_XML];
    INT_32 c_atss_send_BROADCAST_socket_id;

    struct sockaddr_in c_atss_recv_socket;

    struct sockaddr_in atts_recorder_send_socket;
    struct sockaddr_in atts_send_socket;
    struct sockaddr_in atts_send_DBA_socket;
    struct sockaddr_in atts_send_PC_socket;
    struct sockaddr_in atts_send_AMSM_socket;
    struct sockaddr_in atts_send_ATSD_socket[MAX_NUM_OF_WORKSTATIONS_XML];
    struct sockaddr_in atts_send_ATSD_BROADCAST_socket;

    UINT_8 data_logger_alive_flag;
    INT_8 ip_address_data_logger[100];
    UINT_8 data_logger_not_alive_counter;

#ifdef WINDOWS_VER
    WSAData data;
    int recv_socket,send_socket,send_recorder_sock;
    int length;
    struct sockaddr_in recv_addr, send_addr, atss_recorder_addr;
    struct hostent *hp;
    char buffer[256];
#endif

public:
    ATSS_Communication();
    ~ATSS_Communication();

    int GetApplicationState();

    void SetApplicationState(int app_state);
    void SetApplicationStateRuntime(int app_state);

    UINT_8 InitializeATSSSocket();

    UINT_8 RecieveDataFromUDP();

    bool SendDataToPC(INT_8 *received_data, INT_32 data_length,UINT_8 sys_log);
    //UINT_8 SendDataToUDP(INT_8 *received_data, INT_32 data_length, UINT_8 data_comm_mode,char* IP_ADD=nullptr);
    UINT_8 SendDataToUDP(INT_8 *received_data, INT_32 data_length, UINT_8 data_comm_mode,char* IP_ADD=nullptr,PORT_NO port = 0);
    UINT_8 SendDataToDBA(INT_8 *received_data, INT_32 data_length);
    UINT_8 SendAlertEventDataToDBA(INT_8 *received_data, INT_32 data_length);

    UINT_8 SendDataToAMSM(INT_8 *received_data, INT_32 data_length);
    UINT_8 SendDataToATSD(INT_8 *received_data, INT_32 data_length,UINT_8 ows_index);
    UINT_8 SendDataToATSDBROADCAST(INT_8 *received_data, INT_32 data_length);

    UINT_8 SendDataToAllLATS(INT_8 *received_data, INT_32 data_length, char* IP_ADD=nullptr,PORT_NO port = 0);
    UINT_8 SendDataToAllCATS(INT_8 *received_data, INT_32 data_length, char* IP_ADD=nullptr,PORT_NO port = 0);

    void PrintData(INT_8 *textstr, INT_32 textcount, UINT_8 new_line_count, UINT_8 tab_count, UINT_8 syslog_index=LOG_CRITICAL);

    void SetDataLoggerFlag(UINT_8 flag);
    void SendDataToDataLogger(INT_8 *msg, INT_32 recv_len, UINT_8 alive_flag=false);
    void IncrementDataLoggerAliveCounter();
    UINT_8 GetDataLoggerFlag();
    UINT_8 GetDataLoggerAliveCounter();
    void SetDataLoggerAliveCounter(UINT_8 count);
};

#endif // ATS_UDP_SOCKET_H

