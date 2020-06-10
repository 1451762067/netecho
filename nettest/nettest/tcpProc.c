/* -------------------------------------------------------
 * FileName  : doProc.c (1.40)
 * Function  :
 * CreateInfo: tangyx @ 2014.12.17 16:59:28
 * ------------------------------------------------------- */
 
#include "nettest.h"

int tcpProc(int SockFd, char *SockAddr)
{
    int         rcvlen;
    char        rcvbuf[BUFF_SIZE];
    int         len;

    /*
     * receive request data from the tcp connection.
     */
    while(1)
    {
        memset(rcvbuf, 0, sizeof(rcvbuf));
        if ( (rcvlen=readProc(SockFd, (unsigned char *)rcvbuf, sizeof(rcvbuf), TimeOut)) <= 0 )
        {
            if(rcvlen == -2)
                continue;
            E_LOG("read error! [%d-%s]", errno, strerror(errno));
            return -1;
        }

        if(strstr(rcvbuf, "TEST"))
        {
            strcpy(rcvbuf, SockAddr);
            rcvlen = strlen(rcvbuf);
        }

        W_LOG("[tcp]read req buf ok, len=[%d]...", rcvlen);
        D_LOG(HEX_FORMAT, rcvbuf, rcvlen);

        if ( (len=writeProc(SockFd, (unsigned char *)rcvbuf, rcvlen, TimeOut)) != rcvlen )
        {
            if(len == -2)
                continue;
            E_LOG("write error! [%d-%s]", errno, strerror(errno));
            return -1;
        }
    }
    return 0;
}
