[homepage](../index.md)

# Thread

## 定义

- 与进程(process)类似，线程(thread)是允许应用程序并发执行多个任务的一种机制。一个进程可以包含多个线程。同**一个程序中的所有线程均会独立执行相同程序**，且共**享同一份全局内存区域，其中包括初始化数据段、未初始化数据段，以及堆内存段**。(传统意义上的 UNIX 进程只是多线程程序的一个特例，该进程只包含一个线程)
- **进程是 CPU 分配资源的最小单位，线程是操作系统调度执行的最小单位**。
- 线程是**轻量级的进程**(LWP:Light Weight Process)，在 **Linux 环境下线程的本质仍是进程**。
- 查看指定进程的 LWP 号:`ps –Lf pid`
- 进程间的信息难以共享。由于除去只读代码段外，**父子进程并未共享内存，因此必须采用一些进程间通信**方式，在进程间进行信息交换。
- 调用 **fork() 来创建进程的代价相对较高，即便利用写时复制技术**，仍然需要复制诸如**内存页表和文件描述符表之类的多种进程属性**，这意味着 fork() 调用在时间上的**开销依然不菲**。
- **线程之间能够方便、快速地共享信息**。只需**将数据复制到共享(全局或堆)变量中即可**。
- **创建线程**比创建进程通常要**快** 10 倍甚至更多。**线程间是共享虚拟地址空间的，无需采
 用写时复制来复制内存，也无需复制页表**。

### 线程之间共享资源

- 共享资源
	- 进程 ID 和父进程 ID
	- 进程组 ID 和会话 ID
	- 用户 ID 和 用户组 ID
	- 文件描述符表
	- 信号处置
	- 文件系统的相关信息:文件权限掩码(umask)、当前工作目录
	- 虚拟地址空间(除栈、.text)
- 非共享资源 
	- 线程 ID
	- 信号掩码
	- 线程特有数据 
	- error 变量
	- 实时调度策略和优先级
	- 栈，本地变量和函数的调用链接信息

### NPTL
- 当 Linux 最初开发时，在内核中并不能真正支持线程。但是它的确可以通过 clone() 系统调用将进程作为可调度的实体。这个调用创建了调用进程(calling process)的 一个拷贝，这个拷贝与调用进程共享相同的地址空间。LinuxThreads 项目使用这个调用 来完成在用户空间模拟对线程的支持。不幸的是，这种方法有一些缺点，尤其是在信号处 理、调度和进程间同步等方面都存在问题。另外，这个线程模型也不符合 POSIX 的要求。
- 要改进 LinuxThreads，需要内核的支持，并且重写线程库。有两个相互竞争的项目开始 来满足这些要求。一个包括 IBM 的开发人员的团队开展了 NGPT(Next-Generation POSIX Threads)项目。同时，Red Hat 的一些开发人员开展了 NPTL 项目。NGPT 在 2003 年中期被放弃了，把这个领域完全留给了 NPTL。
- NPTL，或称为 Native POSIX Thread Library，是 Linux 线程的一个新实现，它克服了 LinuxThreads 的缺点，同时也符合 POSIX 的需求。与 LinuxThreads 相 比，它在性能和稳定性方面都提供了重大的改进。
- 查看当前 pthread 库版本:`getconf GNU_LIBPTHREAD_VERSION`

## 线程操作

- 编译 `gcc -file.c -o app -ptheard` 使用ptheard库

<img width="1175" alt="image" src="https://user-images.githubusercontent.com/41602569/156916704-bf03b53a-4328-46af-9f5e-4a9f02a08282.png">

### 创建线程 int pthread\_create(pthread\_t * thread, const pthread\_attr\_t * attr, void * ( * start\_routine) (void * ), void * arg);

一般情况下,main函数所在的线程我们称之为主线程（main线程），其余创建的线程
称之为子线程。
程序中默认只有一个进程，fork()函数调用，2个进程
程序中默认只有一个线程，pthread_create()函数调用，2个线程。

- 失败：返回错误号。这个错误号和之前errno不太一样。	
- 获取错误号的信息：  char * strerror(int errnum);

		#include <pthread.h>
        - 功能：创建一个子线程
        - 参数：
            - thread：传出参数，线程创建成功后，子线程的线程ID被写到该变量中。
            - attr : 设置线程的属性，一般使用默认值，NULL
            - start_routine : 函数指针，这个函数是子线程需要处理的逻辑代码
            - arg : 给第三个参数使用，传参
        - 返回值：
            成功：0
            失败：返回错误号。这个错误号和之前errno不太一样。
            获取错误号的信息：  char * strerror(int errnum);
			
	int pthread_create(pthread_t *thread, const pthread_attr_t *attr, 
   						void *(*start_routine) (void *), void *arg);
						
- 应用

```
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

void * callback(void * arg) {
    printf("child thread...\n");
    printf("arg value: %d\n", *(int *)arg);
    return NULL;
}

int main() {

    pthread_t tid;

    int num = 10;

    // 创建一个子线程
    int ret = pthread_create(&tid, NULL, callback, (void *)&num);

    if(ret != 0) {
        char * errstr = strerror(ret);
        printf("error : %s\n", errstr);
    } 

    for(int i = 0; i < 5; i++) {
        printf("%d\n", i);
    }

    sleep(1);

    return 0;   // exit(0);
}
```

**main线程、子线程都结束后，该进程结束**

### 终止线程
让主线程退出,当主线程退出时，不会影响其他正常运行的线程。

```
#include <pthread.h>
void pthread_exit(void *retval);
	功能：终止一个线程，在哪个线程中调用，就表示终止哪个线程
	参数：
		retval:需要传递一个指针，作为一个返回值，可以在pthread_join()中获取到。



pthread_t pthread_self(void);
	功能：获取当前的线程的线程ID

int pthread_equal(pthread_t t1, pthread_t t2);
	功能：比较两个线程ID是否相等
	不同的操作系统，pthread_t类型的实现不一样，有的是无符号的长整型，有的
	是使用结构体去实现的。
```

- 应用

```
#include <stdio.h>
#include <pthread.h>
#include <string.h>

void * callback(void * arg) {
    printf("child thread id : %ld\n", pthread_self());
    return NULL;    // pthread_exit(NULL);
} 

int main() {

    // 创建一个子线程
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, callback, NULL);

    if(ret != 0) {
        char * errstr = strerror(ret);
        printf("error : %s\n", errstr);
    }

    // 主线程
    for(int i = 0; i < 5; i++) {
        printf("%d\n", i);
    }

    printf("tid : %ld, main thread id : %ld\n", tid ,pthread_self());

    // 让主线程退出,当主线程退出时，不会影响其他正常运行的线程。
    pthread_exit(NULL);

    printf("main thread exit\n");

    return 0;   // exit(0);
}
```

## 线程属性

<img width="1171" alt="image" src="https://user-images.githubusercontent.com/41602569/156916718-e807b770-d460-4b53-ada5-8ff9a5da737a.png">


