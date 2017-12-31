//
//  main.c
//  TestFork
//
//  Created by shenyuanluo on 2017/12/31.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main ()
{
    pid_t fpid;     // fpid 表示 fork 函数返回的值
    int count = 0;
    fpid = fork();
    if (0 > fpid)   // 新建进程失败
    {
        perror("创建新进程失败 ");
        exit(EXIT_FAILURE);
    }
    else if (0 == fpid)     // 子进程
    {
        fprintf(stdout, "这是子进程 ID = %d；\t我的父进程 ID = %d\n", getpid(), getppid());
        count++;
    }
    else    // 父进程
    {
        fprintf(stdout, "这是父进程 ID = %d；\t我的父进程 ID = %d\n", getpid(), getppid());
        count++;
    }
    fprintf(stdout, "count = : %d\n",count);
    return 0;
}

