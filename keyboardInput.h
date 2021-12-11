#ifndef KEYBOARDINPUT_H
#define KEYBOARDINPUT_H

#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>

static struct termios orig_term;
void u_cleanup(void)
{
	tcsetattr(0, TCSANOW, &orig_term);
}

int u_kbhit(void)
{
	struct termios t;
	int ret;
	fd_set rfd;
	struct timeval to;
	static int first_hit=0;

	if(first_hit==0)
	{
		if(tcgetattr(0, &t)!=0) exit(0);
		orig_term=t;
		cfmakeraw(&t);
	if(tcsetattr(0, TCSANOW, &t)!=0) exit(0);
		atexit(u_cleanup);
		first_hit=1;
	}

	FD_ZERO(&rfd);
	FD_SET(0, &rfd);
	to.tv_sec=0;
	to.tv_usec=0;
	if(select(1, &rfd, NULL, NULL, &to)==1) return 1;
	return 0;
}

int u_getchar(void)
{
	int ret;
	fd_set rfc;
	unsigned char buf;

	if(read(0, &buf, 1)!=1) ret=0;
	else ret=buf;
	return ret;
}

#endif
