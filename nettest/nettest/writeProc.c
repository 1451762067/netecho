 
#include "nettest.h"

int writeProc(int SockFd, unsigned char *Buf, int Size, int Tout)
{
    int                 i;
    int                 len;
    fd_set              wfds;
    struct timeval      tv;

    tv.tv_sec = Tout;
    tv.tv_usec = 0;
    FD_ZERO( &wfds );
    FD_SET( SockFd, &wfds );

    i = select( SockFd+1, (fd_set *)0,  &wfds, (fd_set *)0, &tv );
    if ( i== -1 )
    {
        E_LOG("select error = [%d-%s]", errno, strerror(errno));
        return -1;
    }
    else if ( i>0 && FD_ISSET( SockFd, &wfds ) )
    {
        len = write(SockFd, Buf, Size);
        if ( len <= 0 )
        {
            E_LOG("write error = [%d-%s]", errno, strerror(errno));
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
