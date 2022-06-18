
#include "inc/ATSS_Includes.h"

extern ATSS_Communication atss_communication_obj;
extern ATSS_DBData DBData_obj;
extern ATSS_MessageProcessor msg_processor_obj;

bool global_stop_track_process  = true;

ATSS_MessageProcessor :: ATSS_MessageProcessor()
{
    //printf("\n ATSS_MessageProcessor constructor call");

}

// receives messages on UDP and processes according to ID
bool ATSS_MessageProcessor :: allATSSIncomingMessage(STRUCT_GENERAL_MESSAGE_ATSS msg)
{
    bool return_flag=true;
    INT_8 print_str[MAX_PRINT_STR];
    INT_32 textcnt=0;

    //    printf("\nm=%d,s=%d",msg.msg_header.message_id, msg.msg_header.source_id);fflush(stdout);
    if(msg.msg_header.source_id==CSCI_PC)           //PC messages
    {
        if(!((msg.msg_header.message_id == PC_ATSS_CBI_POINT_SIGNAL_PLATFORM_STATION_EMERGENCY_RESPONSE) ||
             (msg.msg_header.message_id == PC_ATSS_CBI_ROUTE_RESPONSE) ||
             (msg.msg_header.message_id == PC_ATSS_CBI_TRACK_CYCLE_OVERLAP_RESPONSE) ||
             (msg.msg_header.message_id == PC_ATSS_ATC_EQUIPMENT_STATUS) ||
             (msg.msg_header.message_id == PC_ATSS_EXTERNAL_SYSTEM_HEALTH) ||
             (msg.msg_header.message_id == PC_ATSS_CBI_STATUS) ||
             (msg.msg_header.message_id == PC_ATSS_TSR_REPORT_OF_OPERATION_ID) ||
             (msg.msg_header.message_id == PC_ATSS_CLOCK_SYNCHRONIZATION_REQUEST_MESSAGE) ||
             (msg.msg_header.message_id == PC_ATSS_CBI_DIAG_DATA)
             ))
        {
            printf(BOLDMAGENTA);
            textcnt = sprintf(print_str, "\nPC-> %04d[%04d]\t",msg.msg_header.message_id,msg.msg_header.message_length);
            printf(RESET);
        }

        switch(msg.msg_header.message_id)
        {
        case PC_ATSS_CBI_POINT_SIGNAL_PLATFORM_STATION_EMERGENCY_RESPONSE:
            //ProcessCBIPointResponsePacket(msg);
            break;

        default:
            break;
        }
    }
    else
    {
        printf(RED);
        textcnt = sprintf(print_str,"\nIN:src=%d,id=%d len =%d",msg.msg_header.source_id,msg.msg_header.message_id,msg.msg_header.message_length);

        printf(RESET);
    }

    return return_flag;
}

