#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argnum,char * argv[] )
{
	int fd_fw[2];
	int fd_sw[2];
	char  buf[]={'a'};
	pipe(fd_fw);
	pipe(fd_sw);
	int pid=fork();
	if( pid == 0) 
	{

		close(fd_fw[1]);
		close(fd_sw[0]);
		int n=read(fd_fw[0],buf,1);
		if(n!=1)
		{
			printf("son read went wrong\n");
			exit(1);
		}
		printf("%d: received ping\n",getpid());
		n=write(fd_sw[1],"f",1);
		if(n!=1)
		{
			printf("son write went wrong\n");
			exit(1);
		}
		close(fd_fw[0]);
		close(fd_sw[1]);

	}
	else 
	{
		close(fd_fw[0]);
		close(fd_sw[1]);
		int n=write(fd_fw[1],"f",1);
		if(n!=1)
		{
			printf("father write went wrong\n");
			exit(1);
		}
		n=read(fd_sw[0],buf,1);
		if(n!=1)
		{
			printf("father read went wrong\n");
			exit(1);
		}
		printf("%d: received pong\n",getpid());
		close(fd_fw[1]);
		close(fd_sw[0]);

	}
	exit(0);
	return 0;


}	
