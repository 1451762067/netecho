/* -------------------------------------------------------
 * FileName  : nettest.h (1.40)
 * Function  :
 * CreateInfo: zhangzh @ 2020.06.09 10:31:06
 * ------------------------------------------------------- */
 
#ifndef _NETTEST_H_
#define _NETTEST_H_
 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <signal.h>
#include <libgen.h>
#include <time.h>
#include <malloc.h>
#include <math.h>
#include <errno.h>
#include <dlfcn.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <setjmp.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <arpa/inet.h>

#include "libbase.h"

#define BUFF_SIZE   1024    /* Buffer Size of UDP/IP */ 

#ifdef _MAIN_
    int                     Debug;
    char                    HostPort[40];
    int                     TimeOut;
    char                    ProgName[30];
    char                    IniFile[256];
    char                    CfgFile[256];
#else
    extern int              Debug;
    extern char             HostPort[];
    extern int              TimeOut;
    extern char             ProgName[];
    extern char             IniFile[];
    extern char             CfgFile[];
#endif

// º¯ÊýÉùÃ÷
extern int getInit(int, char **);
extern int tcpProc(int, char *);
extern int udpProc(int);
extern int readProc(int, unsigned char *, int, int);
extern int writeProc(int , unsigned char *, int , int );

#endif /*  _NETTEST_H_ */
