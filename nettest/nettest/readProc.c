 
#include "nettest.h"

int readProc(int SockFd, unsigned char *Buf, int Size, int Tout)
{
    int                 i;
    int                 len;
    fd_set              rfds;
    struct timeval      tv;

    tv.tv_sec = Tout;
    tv.tv_usec = 0;
    FD_ZERO( &rfds );
    FD_SET( SockFd, &rfds );

    i = select( SockFd+1, &rfds, (fd_set *)0, (fd_set *)0, &tv );
    if ( i==-1 )
    {
        E_LOG("select error = [%d-%s]", errno, strerror(errno));
        return -1;
    }
    else if ( i>0 && FD_ISSET( SockFd, &rfds ) )
    {
        len = read(SockFd, Buf, Size);
        if ( len <= 0 )
        {
            E_LOG("read error = [%d-%s]", errno, strerror(errno));
            return -1;
        }
    }
    else /* TimeOut */
    {
        E_LOG("select timeout");
        return -2;
    }

    return len;
}
