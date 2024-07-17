---
finished: false
---

[homepage](index.md)

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

## unsigned int alarm(unsigned int seconds);

- 功能：设置定时器（闹钟）。函数调用，开始倒计时，当倒计时数到0的时候，函数会给当前的进程发送一个信号：SIGALARM(动作:终止进程)
- **不阻塞**
- 定时器，与进程的状态无关（自然定时法）。无论进程处于什么状态，alarm都会计时。

```
#include <unistd.h>    
/*

- 参数：
    seconds: 倒计时的时长，单位：秒。如果参数为0，定时器无效（不进行倒计时，不发信号）。
	    取消一个定时器，通过alarm(0)。
- 返回值：
    - 之前没有定时器，返回0
    - 之前有定时器，返回之前的定时器剩余的时间

    - SIGALARM ：默认终止当前的进程，每一个进程都有且只有唯一的一个定时器。
        alarm(10);  -> 返回0
        过了1秒
        alarm(5);   -> 返回9, 但剩余时间是5

    alarm(100) -> 该函数是不阻塞的
*/
unsigned int alarm(unsigned int seconds);
```

- 应用

```
#include <stdio.h>
#include <unistd.h>

int main() {

    int seconds = alarm(5);
    printf("seconds = %d\n", seconds);  // 0 因为第一次设置

    sleep(2);
    seconds = alarm(2);    // 不阻塞 返回3 是上一次计时的剩余时间
    			   // 重新计时为2秒
    printf("seconds = %d\n", seconds);  // 3

    while(1) {
    }

    return 0;
}
```

- 应用 : 1秒钟电脑能数多少个数？

./a.out >> result.txt 结果更快
输出到终端很费时

```
// 
#include <stdio.h>
#include <unistd.h>

/*
    实际的时间 = 内核时间 + 用户时间 + 消耗的时间
    进行文件IO操作的时候比较浪费时间(输出到终端很费时)

    定时器，与进程的状态无关（自然定时法）。无论进程处于什么状态，alarm都会计时。
*/

int main() {    

    alarm(1);

    int i = 0;
    while(1) {
        printf("%i\n", i++);
    }

    return 0;
}
```

## int setitimer(int which, const struct itimerval * new\_value,struct itimerval * old\_value);

功能：设置定时器（闹钟）。可以替代alarm函数。**精度微妙us**，**可以实现周期性定时**<br>
非阻塞的

```
#include <sys/time.h>
/*
	- 参数：
		- which : 定时器以什么时间计时
		  ITIMER_REAL: 真实时间(自然时间)，时间到达，发送 SIGALRM   常用
		  ITIMER_VIRTUAL: 用户时间(该进程所有线程占用CPU的时间)，时间到达，发送 SIGVTALRM
		  ITIMER_PROF: 以该进程在用户态和内核态下所消耗的时间来计算，时间到达，发送 SIGPROF

		- new_value: 设置定时器的属性

		struct itimerval {      // 定时器的结构体
			struct timeval it_interval;  // 每个阶段的时间，间隔时间
			struct timeval it_value;     // 延迟多长时间执行定时器
		};

		struct timeval {        // 时间的结构体
			time_t      tv_sec;     //  秒数     
			suseconds_t tv_usec;    //  微秒    
		};

		过10秒后，每个2秒定时一次

		- old_value ：记录上一次的定时的时间参数，一般不使用，指定NULL

	- 返回值：
		成功 0
		失败 -1 并设置错误号
*/
int setitimer(int which, const struct itimerval *new_value,
                        struct itimerval *old_value);
```

## 信号捕捉

**typedef void ( * sighandler\_t)(int);<br>
sighandler\_t signal(int signum, sighandler\_t handler);<br>**

功能: 设置某个信号的捕捉行为

```
#include <signal.h>
/*
	void (*func)(int);//是一个函数指针: 函数名=func 参数是int 返回值void
*/
typedef void (*sighandler_t)(int);
/*
	- 功能：设置某个信号的捕捉行为
	- 参数：
		- signum: 要捕捉的信号
		- handler: 捕捉到信号要如何处理
			- SIG_IGN ： 忽略信号
			- SIG_DFL ： 使用信号默认的行为(5种)
			- 回调函数 :  这个函数是内核调用，程序员只负责写，捕捉到信号后如何去处理信号。
				回调函数：
					- 需要程序员实现，提前准备好的，函数的类型根据实际需求，看函数指针的定义
					- 不是程序员调用，而是当信号产生，由内核调用
					- 函数指针是实现回调的手段，函数实现之后，将函数名放到函数指针的位置就可以了。

	- 返回值：
		成功，返回上一次注册的信号处理函数的地址。第一次调用返回NULL
		失败，返回SIG_ERR，设置错误号

SIGKILL SIGSTOP不能被捕捉，不能被忽略。
*/
sighandler_t signal(int signum, sighandler_t handler);
```

### 捕捉信号过程:

1. 定义信号回调函数 void (* sighandler\_t)(int)
2. 注册信号捕捉 signal(int sig, sighandler\_t handler)
3. 注册信号捕捉要在设置定时器之前 


```
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// 定义信号回调函数
// num是捕捉到的信号
void myalarm(int num) {
    printf("捕捉到了信号的编号是：%d\n", num);
    printf("xxxxxxx\n");
}

// 过3秒以后，每隔2秒钟定时一次
int main() {

    // 注册信号捕捉
    // signal(SIGALRM, SIG_IGN);
    // signal(SIGALRM, SIG_DFL);
    // void (*sighandler_t)(int); 函数指针，int类型的参数表示捕捉到的信号的值。
    signal(SIGALRM, myalarm);

    struct itimerval new_value;

    // 设置间隔的时间
    new_value.it_interval.tv_sec = 2;
    new_value.it_interval.tv_usec = 0;

    // 设置延迟的时间,3秒之后开始第一次定时
    new_value.it_value.tv_sec = 3;
    new_value.it_value.tv_usec = 0;

    int ret = setitimer(ITIMER_REAL, &new_value, NULL); // 非阻塞的
    printf("定时器开始了...\n");

    if(ret == -1) {
        perror("setitimer");
        exit(0);
    }

    getchar();

    return 0;
}
```

## 信号集

- 许多信号相关的系统调用都需要能表示一组不同的信号，**多个信号**可使用一个称之为信号集的数据结构来表示，其系统数据类型为 **sigset\_t**。
- 在 **PCB** 中有两个非常重要的信号集。一个称之为 “**阻塞信号集**”(被阻塞信号，不能递达，直到接触阻塞之前不能被处理) ，另一个称之为 “**未决信号集**”(所有没有递达的信号)。**这两个信号集都是内核使用位图机制来实现的**。但操作系统不允许我们直接对这两个信号集进行位操作。而**需自定义另外一个集合，借助信号集操作函数来对 PCB 中的这两个信号集进行修改。**
- 信号的 “**未决**” 是一种**状态**，指的是**从信号的产生到信号被处理前的这一段时间**。
- **信号的 “阻塞”** 是一个**开关动作**，指的是**阻止信号被处理，但不是阻止信号产生**。
- 信号的阻塞就是让系统暂时保留信号留待以后发送。由于另外有办法让系统忽略信号，所以**一般情况下信号的阻塞只是暂时的，只是为了防止信号打断敏感的操作。**

### 阻塞信号集和未决信号集:

<img width="1042" alt="image" src="https://user-images.githubusercontent.com/41602569/156894618-7b575597-6607-4468-b35d-ef9f65c63136.png">

- 信号处理过程:
1.用户通过键盘  Ctrl + C, 产生2号信号SIGINT (信号被创建)
2.信号产生但是没有被处理 （未决）
    - 在内核中将所有的没有被处理的信号存储在一个集合中 （未决信号集）
    - SIGINT信号状态被存储在第二个标志位上
        - 这个标志位的值为0， 说明信号不是未决状态
        - 这个标志位的值为1， 说明信号处于未决状态
3.这个未决状态的信号，需要被处理，处理之前需要和另一个信号集（阻塞信号集），进行比较
    - 阻塞信号集默认不阻塞任何的信号
    - 如果想要阻塞某些信号需要用户调用系统的API
4.在处理的时候和阻塞信号集中的标志位进行查询，看是不是对该信号设置阻塞了
    - 如果没有阻塞，这个信号就被处理
    - 如果阻塞了，这个信号就继续处于未决状态，直到阻塞解除，这个信号就被处理

<img width="1197" alt="image" src="https://user-images.githubusercontent.com/41602569/156896026-c2254bea-47ed-49ad-9df6-cf9255d71dd4.png">


### 自定义信号集相关函数:

以下信号集相关的函数都是**对自定义的信号集**进行操作。

#### int sigemptyset(sigset\_t * set); 全0
        - 功能：清空信号集中的数据,将信号集中的所有的标志位置为0
        - 参数：set,传出参数，需要操作的信号集
        - 返回值：成功返回0， 失败返回-1

#### int sigfillset(sigset\_t * set); 全1
        - 功能：将信号集中的所有的标志位置为1
        - 参数：set,传出参数，需要操作的信号集
        - 返回值：成功返回0， 失败返回-1

#### int sigaddset(sigset\_t * set, int signum); 阻塞某信号
        - 功能：设置信号集中的某一个信号对应的标志位为1，表示阻塞这个信号
        - 参数：
            - set：传出参数，需要操作的信号集
            - signum：需要设置阻塞的那个信号
        - 返回值：成功返回0， 失败返回-1

#### int sigdelset(sigset\_t * set, int signum); 不阻塞某信号
        - 功能：设置信号集中的某一个信号对应的标志位为0，表示不阻塞这个信号
        - 参数：
            - set：传出参数，需要操作的信号集
            - signum：需要设置不阻塞的那个信号
        - 返回值：成功返回0， 失败返回-1

#### int sigismember(const sigset\_t * set, int signum); 判断某个信号是否阻塞
        - 功能：判断某个信号是否阻塞
        - 参数：
            - set：需要操作的信号集
            - signum：需要判断的那个信号
        - 返回值：
            1 ： signum被阻塞
            0 ： signum不阻塞
            -1 ： 失败

- 应用:

```
#include <signal.h>
#include <stdio.h>

int main() {

    // 创建一个信号集
    sigset_t set;

    // 清空信号集的内容
    sigemptyset(&set);

    // 判断 SIGINT 是否在信号集 set 里
    int ret = sigismember(&set, SIGINT);
    if(ret == 0) {
        printf("SIGINT 不阻塞\n");
    } else if(ret == 1) {
        printf("SIGINT 阻塞\n");
    }

    // 添加几个信号到信号集中,即阻塞
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGQUIT);

    // 判断SIGINT是否在信号集中
    ret = sigismember(&set, SIGINT);
    if(ret == 0) {
        printf("SIGINT 不阻塞\n");
    } else if(ret == 1) {
        printf("SIGINT 阻塞\n");
    }

    // 判断SIGQUIT是否在信号集中
    ret = sigismember(&set, SIGQUIT);
    if(ret == 0) {
        printf("SIGQUIT 不阻塞\n");
    } else if(ret == 1) {
        printf("SIGQUIT 阻塞\n");
    }

    // 从信号集中删除一个信号
    sigdelset(&set, SIGQUIT);

    // 判断SIGQUIT是否在信号集中
    ret = sigismember(&set, SIGQUIT);
    if(ret == 0) {
        printf("SIGQUIT 不阻塞\n");
    } else if(ret == 1) {
        printf("SIGQUIT 阻塞\n");
    }

    return 0;
}
```

### 内核信号集相关函数

#### int sigprocmask(int how, const sigset\_t * set, sigset\_t * oldset);

功能：将自定义信号集中的数据设置到内核中（设置阻塞，解除阻塞，替换）

	- 参数：
		- how : 如何对内核阻塞信号集进行处理
			SIG_BLOCK: 将用户设置的阻塞信号集添加到内核中，内核中原来的数据不变
				假设内核中默认的阻塞信号集是mask， mask | set
			SIG_UNBLOCK: 根据用户设置的数据，对内核中的数据进行解除阻塞
				mask &= ~set
			SIG_SETMASK:覆盖内核中原来的值

		- set ：已经初始化好的用户自定义的信号集
		- oldset : 保存设置之前的内核中的阻塞信号集的状态，可以是 NULL
	- 返回值：
		成功：0
		失败：-1
			设置错误号：
				EFAULT : 传入的set或者oldset的地址不在本进程空间(地址非法)
				EINVAL : 传入的how非法或者内核不支持传入的set大小

#### int sigpending(sigset_t * set);
功能：获取内核中的未决信号集
	- 参数：set,传出参数，保存的是内核中的未决信号集中的信息。

- 应用

编写一个程序，把所有的常规信号（1-31）的未决状态打印到屏幕<br>
设置某些信号是阻塞的，通过键盘产生这些信号

```
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

    // 设置2、3号信号阻塞
    sigset_t set;
    sigemptyset(&set);
    // 将2号和3号信号添加到信号集中
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGQUIT);

    // 修改内核中的阻塞信号集
    sigprocmask(SIG_BLOCK, &set, NULL);

    int num = 0;

    while(1) {
        num++;
        // 获取当前的未决信号集的数据
        sigset_t pendingset;
        sigemptyset(&pendingset);
        sigpending(&pendingset);

        // 遍历前32位
        for(int i = 1; i <= 31; i++) {
            if(sigismember(&pendingset, i) == 1) {
                printf("1");
            }else if(sigismember(&pendingset, i) == 0) {
                printf("0");
            }else {
                perror("sigismember");
                exit(0);
            }
        }

        printf("\n");
        sleep(1);
        if(num == 10) {
            // 解除阻塞
            sigprocmask(SIG_UNBLOCK, &set, NULL);
        }

    }


    return 0;
}
```

### 信号捕捉 sigaction

**int sigaction(int signum, const struct sigaction * act, struct sigaction * oldact);**

- 功能：检查或者改变信号的处理。信号捕捉
- 在处理信号时可以阻塞一些信号以防止被别的信号干扰


	#include <signal.h>
        - 参数：
            - signum : 需要捕捉的信号的编号或者宏值（信号的名称）
            - act ：捕捉到信号之后的处理动作
            - oldact : 上一次对信号捕捉相关的设置，一般不使用，传递NULL
        - 返回值：
            成功 0
            失败 -1
	int sigaction(int signum, const struct sigaction * act,struct sigaction * oldact);
	
	struct sigaction {
        // 函数指针，指向的函数就是信号捕捉到之后的处理函数
        void     (*sa_handler)(int);
        // 不常用
        void     (*sa_sigaction)(int, siginfo_t *, void *);
        // 临时阻塞信号集，在信号捕捉函数执行过程中，临时阻塞某些信号。
        sigset_t   sa_mask;
        // 使用哪一个信号处理对捕捉到的信号进行处理
        // 这个值可以是0，表示使用sa_handler,也可以是SA_SIGINFO表示使用sa_sigaction
        int        sa_flags;
        // 被废弃掉了
        void     (*sa_restorer)(void);
    };


```
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void myalarm(int num) {
    printf("捕捉到了信号的编号是：%d\n", num);
    printf("xxxxxxx\n");
}

// 过3秒以后，每隔2秒钟定时一次
int main() {

    struct sigaction act;
    act.sa_flags = 0;
    act.sa_handler = myalarm;
    sigemptyset(&act.sa_mask);  // 清空临时阻塞信号集
   
    // 注册信号捕捉
    sigaction(SIGALRM, &act, NULL);

    struct itimerval new_value;

    // 设置间隔的时间
    new_value.it_interval.tv_sec = 2;
    new_value.it_interval.tv_usec = 0;

    // 设置延迟的时间,3秒之后开始第一次定时
    new_value.it_value.tv_sec = 3;
    new_value.it_value.tv_usec = 0;

    int ret = setitimer(ITIMER_REAL, &new_value, NULL); // 非阻塞的
    printf("定时器开始了...\n");

    if(ret == -1) {
        perror("setitimer");
        exit(0);
    }

    // getchar();
    while(1);

    return 0;
}
```

#### signal 与 sigaction:

- sigaction 更广泛的被支持 推荐使用
- 如果正在处理信号1的过程，此时又来信号1，当前处理就会被中断去处理第二个信号1
- 而sigaction在处理信号时可以阻塞一些信号以防止被别的信号干扰
- **未决信号不支持排队**: 未决信号集只能将信号位标记为1不能记录有多少个此信号未决,因此最多记录1个

### 内核实现信号捕捉过程

<img width="996" alt="image" src="https://user-images.githubusercontent.com/41602569/156895722-5e17cb30-7cb7-4de3-836c-8a94aa2ea380.png">

## SIGCHILD 信号

- SIGCHLD信号产生的条件
	- 子进程**终止**时
	- 子进程**接收到 SIGSTOP 信号停止**时
	- 子进程处在停止态，接**收到SIGCONT后唤醒**时
- 以上三种条件都会给父进程发送 SIGCHLD 信号，**父进程默认会忽略**该信号

### 使用SIGCHILD解决僵尸进程

1. 提前设置好阻塞信号集，阻塞SIGCHLD,因为有可能子进程很快结束，父进程还没有注册完信号捕捉，即由于未决信号集会丢弃多个SIGCHILD,从而导致一些子进程没有被回收，变成僵尸进程
2. 阻塞后，子进程不被我们的回调函数处理就不会结束
3. sigaction 设置 回调函数，用waitpid(-1,NULL,WNOHANG)回收所有子进程

```
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/wait.h>

void myFun(int num) {
    printf("捕捉到的信号 ：%d\n", num);
    // 回收子进程PCB的资源
    // while(1) {
    //     wait(NULL); //阻塞等待子进程结束
    // }
    while(1) {
       int ret = waitpid(-1, NULL, WNOHANG);//-1 回收所有子进程 不阻塞
       if(ret > 0) {
           printf("child die , pid = %d\n", ret);
       } else if(ret == 0) {
   // 说明还有子进程或者，但没有SIGCHILD信号
           break;
       } else if(ret == -1) {
           // 没有子进程
           break;
       }
    }
}

int main() {

    // 提前设置好阻塞信号集，阻塞SIGCHLD
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGCHLD);
    sigprocmask(SIG_BLOCK, &set, NULL);

    // 创建一些子进程
    pid_t pid;
    for(int i = 0; i < 20; i++) {
        pid = fork();
        if(pid == 0) {
            break;
        }
    }

    if(pid > 0) {
        // 父进程

        // 捕捉子进程死亡时发送的SIGCHLD信号
        struct sigaction act;
        act.sa_flags = 0;
        act.sa_handler = myFun;
        sigemptyset(&act.sa_mask);
        sigaction(SIGCHLD, &act, NULL);

        // 注册完信号捕捉以后，解除阻塞
        sigprocmask(SIG_UNBLOCK, &set, NULL);

        while(1) {
            printf("parent process pid : %d\n", getpid());
            sleep(2);
        }
    } else if( pid == 0) {
        // 子进程
        printf("child process pid : %d\n", getpid());
    }

    return 0;
}
```


