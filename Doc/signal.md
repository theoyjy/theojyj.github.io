[homepage](../index.md)

# 信号

- 信号是 Linux 进程间通信的最古老的方式之一，是事件发生时**对进程的通知机制**，有时也称之为**软件中**断，它是在软件层次上对中断机制的一种模拟，是一种**异步通信**的方式。信号可以导致一个正在运行的进程被另一个正在运行的异步进程中断，转而处理某一个突发事件。
- 发往进程的诸多**信号，通常都是源于内核**。**引发内核为进程产生信号的各类事件**如下:
	- 对于前台进程，用户可以通过输入特殊的终端字符来给它发送信号。比如输入**Ctrl+C通常会给进程发送一个中断信号**。
	- **硬件发生异常**，即硬件检测到一个错误条件并通知内核，随即再由内核发送相应信号给相关进程。比如执行一条异常的机器语言指令，诸如被 0 除，或者引用了无法访问的内存区域。
	- **系统状态变化**，比如 alarm 定时器到期将引起 SIGALRM 信号，进程执行的 CPU时间超限，或者该进程的某个子进程退出。 
	- 运行 kill 命令或调用 kill 函数。
- 使用信号的两个主要**目的**是:
	- 让进程知道已经发生了一个特定的事情。
	- 强迫进程执行它自己代码中的信号处理程序。
- 信号的**特点**: 
	- 简单
	- 不能携带大量信息
	- 满足某个特定条件才发送 
	- *优先级比较高*
- 查看系统定义的信号列表:`kill –l`

<img width="1129" alt="image" src="https://user-images.githubusercontent.com/41602569/156891892-bd5b5384-8c09-4277-9fff-24992f2e9998.png">

<img width="1160" alt="image" src="https://user-images.githubusercontent.com/41602569/156891927-e43b4939-2197-4d17-8242-0706572e0713.png">

<img width="1149" alt="image" src="https://user-images.githubusercontent.com/41602569/156891930-25d3795b-8e63-4f06-831f-bc6dd9ef766e.png">

<img width="1149" alt="image" src="https://user-images.githubusercontent.com/41602569/156891952-3a6600e6-02c7-460a-abf9-6fe9660681fc.png">


- 前 31 个信号为常规信号，其余为实时信号。
- 查看信号的详细信息:`man 7 signal` 
- 信号的 5 中**默认处理动作**
	- Term 终止进程
	- Ign  当前进程忽略掉这个信号
	- Core 终止进程，并生成一个Core文件
	- Stop 暂停当前进程
	- Cont 继续执行当前被暂停的进程
- 信号的几种状态:产生、未决、递达
- SIGKILL 和 SIGSTOP 信号不能被捕捉、阻塞或者忽略，只能执行默认动作。

```
#include <stdio.h>
#include <string.h>

int main() {

    char * buf;	// 野指针

    strcpy(buf, "hello");	// 段错误，会生成core文件

    return 0;
}
```
- ulimit -a 发现 core file size 默认是0，ulimite -c 1024 设置
- 要成功生成core，编译文件时`gcc test.cpp -g` 生成错误信息
- 运行./a.out
- gdc ./a.out
- core-file core 就可以查看core信息

## int kill(pid_t pid, int sig);

功能：给任何的进程或者进程组pid, 发送任何的信号 sig

```
#include <sys/types.h>
#include <signal.h>
/*  

	- 参数：
		- pid ：
			> 0 : 将信号发送给指定的进程
			= 0 : 将信号发送给当前的进程组
			= -1 : 将信号发送给每一个有权限接收这个信号的进程
			< -1 : 这个pid=某个进程组的ID取反 （-12345）
		- sig : 需要发送的信号的编号或者是宏值，0表示不发送任何信号

	kill(getppid(), 9);	// 给父进程
	kill(getpid(), 9);  // 给自己进程
*/
int kill(pid_t pid, int sig);
```

## int raise(int sig);

功能：给当前进程发送信号

```
/*
	- 
	- 参数：
		- sig : 要发送的信号
	- 返回值：
		- 成功 0
		- 失败 非0
	- 等价于 kill(getpid(), sig);   
*/
int raise(int sig);
```

## void abort(void)

功能： 发送SIGABRT信号给当前的进程，杀死当前进程

```
/* 
	等价于 kill(getpid(), SIGABRT);
*/
void abort(void);
```

- 应用

```
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int main() {

    pid_t pid = fork();

    if(pid == 0) {
        // 子进程
        int i = 0;
        for(i = 0; i < 5; i++) {
            printf("child process，%d\n",i);
            sleep(1);
        }

    } else if(pid > 0) {
        // 父进程
        printf("parent process\n");
        sleep(2);
        printf("kill child process now\n");
		// 子进程没有运行完成就被kill
        kill(pid, SIGINT);
    }

    return 0;
}

```
