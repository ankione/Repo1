#ifndef ATSS_Includes_H
#define ATSS_Includes_H

#include <QCoreApplication>
#include <QUdpSocket>
#include <QDomDocument>
#include <QMap>
#include <QThread>
#include <QDebug>
#include <iostream>
#include <vector>
#include <pthread.h>
#include <math.h>
//#include <thread>
#include <sstream> // std::stringstream
#include <fstream>
#include <unistd.h>
#include <sys/timeb.h>

#ifdef WINDOWS_VER
//#pragma  warning (disable:4786)
//#pragma comment(lib,"ws2_32.lib")
//#include "Afxwin.h"
#include "winsock2.h"
#include <ws2tcpip.h>
#endif

using namespace std;
#pragma pack(1)
#include "IRS.h"
#include "IDD.h"
#include "ATSS_DBData.h"
#include "ATSS_MessageProcessor.h"
#include "ATSS_Communication.h"

//using namespace ATSS;

//extern ATSS::TimeTableValidationDataManager  time_table_validate_data_obj;

#endif // ATSS_Includes_H
