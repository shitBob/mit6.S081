#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc,char* argv[])
{
    char buf[512];
    char rargv[64];
    char* argm[64];
    int len = read(0,buf,512);
    buf[len] = 0;
    printf("buf : %c",buf[1]);
    int i=0;
    int rargv_num=0;
    for(int i=1;i<argc;i++)
        argm[rargv_num++]=argv[i];
    while(i<len)
    {   int j=0;
        while(i<len && buf[i]!='\n')
            rargv[j++]=buf[i++];
        rargv[j]=0;
        argm[rargv_num]=rargv;

        if(fork()==0)
        {
            exec(argv[1],argm);
        }
        else 
        {
            wait(0);
        }
        i++;

    }
    exit(0);
}