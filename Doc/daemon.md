---
finished: false
---

[homepage](../index.md)

# DAEMON

## 终端

- 在 UNIX 系统中，用户**通过终端**登录系统后**得到一个 shell 进程**，**这个终端成为 shell 进程的控制终端(Controlling Terminal)**，进程中，控制终端是保存在 PCB 中的信息，而 fork() 会复制 PCB 中的信息(即通过终端运行的其他app，要么是fork(),exec..())，因此由 shell 进程启动的其它进程的控制终端也是这个终端。
- 默认情况下(没有重定向dup2)，每个进程的**标准输入、标准输出和标准错误输出都指向控制终端**，进程从标准输入读也就是读用户的键盘输入，进程往标准输出或标准 错误输出写也就是输出到显示器上。
- 在**控制终端输入一些特殊的控制键可以给前台进程发信号**，例如 Ctrl + C 会产 生 SIGINT 信号，Ctrl + \ 会产生 SIGQUIT 信号。

## 进程组

- 进程组和会话在进程之间形成了一种两级层次关系:**进程组是一组相关进程的集合**， **会话是一组相关进程组的集合**。 进程组和会话**是为支持 shell 作业控制而定义的抽象概念**，用户通过 shell 能够交互式地在前台或后台运行命令。
- 进行组由一个或多个共享同一进程组标识符(PGID)的进程组成。一个进程组拥有一个**进程组首进程，该进程是创建该组的进程，其进程 ID 为该进程组的 ID**，新进程会继承其父进程所属的进程组 ID。
- **进程组**拥有一个**生命周期**，其**开始时间为首进程创建组的时刻**，**结束时间为最后一个 成员进程退出组的时刻**。一个进程可能会因为终止而退出进程组，也可能会因为加入了另外一个进程组而退出进程组。**进程组首进程无需是最后一个离开进程组的成员**。

## 会话

- 会话是一组进程组的集合。**会话首进程是创建该新会话的进程，其进程 ID 会成为会话 ID**。新进程会继承其父进程的会话 ID。
- 一个**会话中的所有进程共享单个控制终端**。**控制终端会在会话首进程首次打开一个终端设备时被建立**。一个终端最多可能会成为一个会话的控制终端。
- 在任一时刻，会话中的**其中一个进程组会成为终端的前台进程组**，**其他进程组会成为后台进程组**。**只有前台进程组中的进程才能从控制终端中读取输入**。**当用户在控制终端中输入终端字符生成信号后，该信号会被发送到前台进程组中的所有成员**。
- 当控制终端的连接建立起来之后，**会话首进程会成为该终端的控制进程**。

## 实例

<img width="872" alt="image" src="https://user-images.githubusercontent.com/41602569/156899101-5a0c5d44-12ce-4cbe-8e9e-25b381931496.png">

## 进程组、会话操作函数

- pid_t getpgrp(void);                //当前进程的组id
- pid_t getpgid(pid_t pid);           //指定进程的组id
- int setpgid(pid_t pid, pid_t pgid); //设置进程的组id
- pid_t getsid(pid_t pid);            //指定进程的会话组id
- pid_t setsid(void);                 //当前进程的会话组id

## 守护进程

- 守护进程(Daemon Process)，也就是通常说的 Daemon 进程(精灵进程)，是 Linux 中的**后台服务进程**。它是一个生存期较长的进程，**通常独立于控制终端并且周期性地执行某种任务或等待处理某些发生的事件**。一般采用以 d 结尾的名字。
- 守护进程具备下列特征:
  - **生命周期很长**，守护进程会在系统启动的时候被创建并**一直运行直至系统被关闭**。 
  - 它在后台运行并且**不拥有控制终端。没有控制终端确保了内核永远不会为守护进程自动生成任何控制信号以及终端相关的信号(如 SIGINT、SIGQUIT)**。
- Linux 的**大多数服务器就是用守护进程**实现的。比如，Internet 服务器 inetd，Web 服务器 httpd 等。

### 守护进程的创建步骤
	
1. **执行一个 fork()，之后父进程退出，子进程继续执行**。
	- 不退出父进程，父进程死的时候会输出终端的提示符
	- fork可以确保daemon不会是当前任何一个进程组的首进程
	- 以成功让子进程建立新会话⬇️
2. **子进程调用 setsid() 开启一个新会话**。
	- 这样此进程就是进程组和会话组的首进程
	- 这样就没有控制终端，成功脱离控制终端，但仍然有终端，确保内核不会为进程生成任何信号
	- 为什么不在父进程里开启新会话：
		- 若该父进程就是它所属会话的首进程，那所属会话组的id就是它的id
		- 新创建的会话组将会拥有相同的id
3. 清除进程的 umask 以确保当守护进程创建文件和目录时拥有所需的权限。 
4. 修改进程的当前工作目录，通常会改为根目录(/)。 
	- 若守护进程运行在U盘目录里，U盘就不能卸载了
	- 根目录一般不会卸载
5. 关闭守护进程从其父进程继承而来的所有打开着的文件描述符。 
	- 脱离了控制终端，但还是有终端
	- 不然会不小心操作，使得终端不小心显示数据
6. 在关闭了文件描述符0、1、2之后，守护进程通常会打开/dev/null(丢弃) 并使用dup2() 使所有这些描述符指向这个设备。
7. 核心业务逻辑

### 守护进程案例

写一个守护进程，每隔2s获取一下系统时间，将这个时间写入到磁盘文件中。

```
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void work(int num) {
    // 捕捉到信号之后，获取系统时间，写入磁盘文件
    time_t tm = time(NULL);
    struct tm * loc = localtime(&tm);
    // char buf[1024];

    // sprintf(buf, "%d-%d-%d %d:%d:%d\n",loc->tm_year,loc->tm_mon
    // ,loc->tm_mday, loc->tm_hour, loc->tm_min, loc->tm_sec);

    // printf("%s\n", buf);

    char * str = asctime(loc);
    int fd = open("time.txt", O_RDWR | O_CREAT | O_APPEND, 0664);
    write(fd ,str, strlen(str));
    close(fd);
}

int main() {

    // 1.创建子进程，退出父进程
    pid_t pid = fork();

    if(pid > 0) {
        exit(0);
    }

    // 2.将子进程重新创建一个会话
    setsid();

    // 3.设置掩码
    umask(022);

    // 4.更改工作目录
    chdir("/home/nowcoder/");

    // 5. 关闭、重定向文件描述符
    int fd = open("/dev/null", O_RDWR);
    dup2(fd, STDIN_FILENO);
    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDERR_FILENO);

    // 6.业务逻辑

    // 捕捉定时信号
    struct sigaction act;
    act.sa_flags = 0;
    act.sa_handler = work;
    sigemptyset(&act.sa_mask);
    sigaction(SIGALRM, &act, NULL);

    struct itimerval val;
    val.it_value.tv_sec = 2;
    val.it_value.tv_usec = 0;
    val.it_interval.tv_sec = 2;
    val.it_interval.tv_usec = 0;

    // 创建定时器
    setitimer(ITIMER_REAL, &val, NULL);

    // 不让进程结束
    while(1) {
        sleep(10);
    }

    return 0;
}
```


