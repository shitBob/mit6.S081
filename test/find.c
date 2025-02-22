#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
char *
getlastname(char *path)
{
   //从一个路径中获取 /前的名字 
   char* p;
   for(p=path+strlen(path);p>path && *p !='/';p--)
   ;
   return p;

}
void 
find(char * path, char * aim)
{
    char buf[512];
    char *p;
    int fd;
    struct dirent de;
    struct stat st;

    if((fd =open(path, 0)) < 0){
        fprintf(2,"find : cannot open %s\n",path);
        return ;
    }

    if(fstat(fd,&st) < 0){
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }
    switch(st.type){
    case T_FILE:
        if(strcmp(getlastname(path),aim)==0)
        {
            fprintf(2,"%s\n",path);
            break;
        }
    case T_DIR:
        strcpy(buf,path);
        p=buf+strlen(path);
        *p++ = '/';
        while(read(fd,&de,sizeof(de))){
            if(de.inum == 0)
                continue;
            if (strlen(path) + 1 + DIRSIZ +1 > 512){
                printf("find: path too long\n");
                break;
            }
        memmove(p,de.name,DIRSIZ);
        p[DIRSIZ] = 0 ;
        find(buf,aim);            
        }
        break;       
    }
    close(fd);
}

int
main(int argc, char *argv[])
{
    if(argc <3){
        fprintf(2,"find: missing operand\n");
        exit(1);
    }
    char buf[512];
    strcpy(buf,argv[1]);
    find(buf,argv[2]);
    exit(0);
} 