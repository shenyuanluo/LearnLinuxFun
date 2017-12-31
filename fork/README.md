# fork 函数
> 一个进程，包括代码、数据以及所分配的资源。`fork()` 函数通过系统的调用创建一个与原来进程几乎完全相同的新进程，可以做完全相同的事；但如果初始参数或者传入的变量不同，两个进程也可以做不同的事。

> 一个进程调用 `fork()` 函数后，系统先给新的进程分配资源，例如存储数据和代码的空间。然后把原来的进程的所有值都复制到新的进程中，只有少数值与原来的进程的值不同。相当于克隆了一个自己。


#### 头文件
```
#include <unistd.h>
```

#### 函数原型
```
pid_t fork(void);
```

#### 返回值
```
1. -1， 创建失败。
2.  0， 创建成功，返回子进程。
3. >0， 创建成功，返回子进程 ID 给父进程。
```


#### 功能
通过系统调用创建一个与原来进程几乎完全相同的进程。

#### 例子
``` C
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main ()
{
    pid_t fpid; // fpid 表示 fork 函数返回的值
    int count = 0;
    fpid = fork();
    if (0 > fpid)   // 新建进程失败
    {
        fprintf(stderr, "创建新进程失败！");
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
```

##### 运行结果
``` bash
这是父进程 ID = 7898；	我的父进程 ID = 7899
count = : 1
这是子进程 ID = 7901；	我的父进程 ID = 7898
count = : 1
Program ended with exit code: 0
```





