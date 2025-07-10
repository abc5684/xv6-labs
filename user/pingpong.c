// #include "kernel/types.h"
// #include "user/user.h"
// int main(int argc,char *argv[])
// {
//     if(argc!=1)
//     {
//         printf("ERROR");
//         exit(-1);
//     }
//     int p1[2],p2[2];
//     pipe(p1);//创建第一个管道p1
//     pipe(p2);//创建第二个管道p2
//     char byte=1;
//     int pid=fork();
//     if(pid==0)
//     {
//       close(p1[1]);//关闭p1写端
//       close(p2[0]);
//       read(p1[0],&byte,sizeof(byte));//从p1读取父进程消息。red（fd,buff缓冲区指针，buff缓冲区大小）
//       printf("%d:received ping\n",getpid());
//       write(p2[1],&byte,sizeof(byte));//通过p2向父进程发送消息
//     }
//     else
//     {
//         close(p1[0]);
//         close(p2[1]);
//         write(p1[1],&byte,sizeof(byte));//通过p1向子进程发送发送消息
//         read(p2[0], &byte, sizeof byte);   // 从 p2 读取子进程的回复
//         printf("%d:received pong\n",getpid());
//         wait(0);//等待子进程结束
//     }
//     exit(0);
// }

#include "kernel/types.h"
#include "user/user.h"

int 
main(int argc, char *argv[])
{
    int p1[2], p2[2];
    pipe(p1);
    pipe(p2);
    char byte = 1;
    int pid = fork();
    if (pid == 0) {
        close(p1[1]);
        close(p2[0]);
        
        read(p1[0], &byte, sizeof byte);
        printf("%d: received ping\n", getpid());
        write(p2[1], &byte, sizeof byte);
    } else {
        close(p1[0]);
        close(p2[1]);

        write(p1[1], &byte, sizeof byte);
        read(p2[0], &byte, sizeof byte);
        printf("%d: received pong\n", getpid());
        wait(0);
    }
    exit(0);
}