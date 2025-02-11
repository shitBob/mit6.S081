#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argnum,char * argv[] )
{
	if(argnum<2)
	{
		printf("sleep: missing operand");
		exit(1);
	}
	else
	{
		sleep(atoi(argv[1]));
		exit(0);
	}
	

}
