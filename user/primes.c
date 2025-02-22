#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#define READ_END 0
#define WRITE_END 1
int prime[36];
void dfs(int cnt) //cnt 即质数筛中数字总数
{
	if(cnt<1)
	{
		exit(0);
	}
	printf("prime %d\n",prime[0]); //第一个未被筛走的数字必定是质数 
	
	int fd[2];
	pipe(fd);
    int pid=fork();
	if(pid == 0) // 子进程
	{
        close(fd[WRITE_END]); //必须关闭，否则read会一直阻塞 
		int num=0;
		while(read(fd[READ_END],&(prime[num++]),sizeof(int)));	
		num--;// 最后一次会读到EOF ,但也会 ++
        close(fd[READ_END]); //关闭减少占用 
		dfs(num);

	}
	else
	{
        close(fd[READ_END]); //关闭减少占用 
		for(int i=1;i<cnt;i++)
			if(prime[i] % prime[0] !=0)
				write(fd[WRITE_END],&prime[i],sizeof(int));
        close(fd[WRITE_END]); //必须关闭，否则read会一直阻塞 
       
	}
     wait(0); //父进程必须等待，否则exit会连带子进程也exit
    exit(0);
	

}

int main(int argnum,char * argv[] )
{
	for(int i=0;i<34;i++)   // 0-33    2-35  初始化质数筛
		prime[i]=i+2;
	dfs(34);
	exit(0);
}
