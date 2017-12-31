//
//  main.c
//  TestPipe
//
//  Created by shenyuanluo on 2017/12/31.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc ,char *argv[])
{
    int pipefd[2],result;
    char buf[1024];
    int exitFlag = 0;
    pid_t fpid;
    
    result = pipe(pipefd);  // 创建一个管道 （pipefd[0]:用于读取管道 ；pipefd[1]:用于写入管道）
    if(-1 == result)
    {
        perror("创建管道失败: ");
        exit(EXIT_FAILURE);
    }
    
    fpid = fork();      // 创建一个子进程
    if(-1 == fpid)      // 创建进程失败
    {
        perror("创建新进程失败: ");
        exit(EXIT_FAILURE);
    }
    else if(0 == fpid)   // 子进程 （设置只读）
    {
        if(-1 == (close(pipefd[1])))
        {
            perror("关闭可写管道失败: ");
            exit(EXIT_FAILURE);
        }
        while(1)    //循环读取数据
        {
            read(pipefd[0], buf, 1024);   //最多读取1024个字节
            fprintf(stdout, "读取到内容：%s\n", buf);
            if(0 == strcmp(buf, "exit"))     // 如果读取到的字符串是 ‘exit’ ；这时，父进程会接受到一个终止进程的信号，父进程会回收子进程的资源等
            {
                exit(EXIT_SUCCESS);
            }
        }
    }
    else    // 父进程 （设置只写）
    {
        if(-1 == (close(pipefd[0])))
        {
            perror("关闭可读管道失败: ");
            exit(EXIT_FAILURE);
        }
        while(1)    //循环写入内容
        {
            waitpid(fpid, NULL, WNOHANG);    // 等待子进程退出
            
            if(1 == exitFlag)
            {
                exit(EXIT_SUCCESS);
            }
            scanf("%s", buf);
            write(pipefd[1], buf, strlen(buf) + 1);   // 具体写多少个字节
            if(0 == strcmp(buf, "exit"))
            {
                exitFlag = 1;
                sleep(1);   // 睡一会，让子进程完全退出。
            }
        }
    }
    return 1;
}
