#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc,char* argv[])
{
    char buf[512];
    char rargv[MAXARG][64];
    int len = read(0,buf,512);
    buf[len] = 0;
    int i=0;
    int rargv_num=0;
    int num=0;
    for(int i=1;i<argc;i++)
    {
        for(int j=0;j<strlen(argv[i]);j++)
            rargv[rargv_num][j]=argv[i][j];
        rargv[rargv_num][strlen(argv[i])]=0;
        rargv_num++;
    }
        
    while(i<len)
    {
            int j=0;
           while(i<len && buf[i] !='\n' )
           {
            rargv[rargv_num][j++] = buf[i++];
           }
           rargv_num++;
           i++;
    }
    char * argument[MAXARG];
    for(int i=0;i<rargv_num;i++)
        argument[i]=rargv[i];
    if(fork()==0)
    {
        if(exec(argv[1],argument) == -1)
        {
            printf("son die\n");
             exit(1);
        }
           
    }
    wait(0);
    exit(0);
}