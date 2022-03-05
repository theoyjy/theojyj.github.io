[homepage](../index.md)

# IPC:Inter Processes Communication

- 进程是一个独立的资源分配单元，不同进程(这里所说的进程通常指的是用户进程)之间 的资源是独立的，没有关联，不能在一个进程中直接访问另一个进程的资源。
- 但是，进程不是孤立的，不同的进程需要进行信息的交互和状态的传递等，因此需要进程间通信( IPC:Inter Processes Communication )。

## 进程间通信的目的:

- 数据传输:一个进程需要将它的数据发送给另一个进程。
- 通知事件:一个进程需要向另一个或一组进程发送消息，通知它(它们)发生了某种事件(如进程终止时要通知父进程)。
- 资源共享:多个进程之间共享同样的资源。为了做到这一点，需要内核提供互斥和同步机制。
- 进程控制:有些进程希望完全控制另一个进程的执行(如 Debug 进程)，此时控制进程希望能够拦截另一个进程的所有陷入和异常，并能够及时知道它的状态改变。

## Linux 进程间通信方式

<img width="1209" alt="image" src="https://user-images.githubusercontent.com/41602569/156876935-ad5d04f9-333f-4622-9e0b-c1e15e14f4b2.png">

## 匿名管道

- `ls | wc -l`: 统计一个目录中文件的数目，shell创建了两个进程分别来执行`ls` 和 `wc`

<img width="1099" alt="image" src="https://user-images.githubusercontent.com/41602569/156877347-1b2ff5ac-20b7-40f4-975e-f5a1eebcff04.png">

  - `ls` 原先写入终端，现在进程将内容输出匿名管道
  - `wc` 默认从终端读取，现在从管道读取
  - `|` 创建了一个管道

### 管道的特质

- 管道其实是一个在**内核内存中维护的缓冲器**，这个缓冲器的存储能力是有限的，不同的 操作系统大小不一定相同。
-  管道拥**有文件的特质:读操作、写操作**，**匿名管道没有文件实体，有名管道有文件实体**，但**不存储数据**。可以按照操作文件的方式对管道进行操作。
-  一个管道是一个**字节流**，使用管道时**不存在消息或者消息边界的概念**，从管道读取数据的进程可以**读取任意大小的数据块**，而不管写入进程写入管道的数据块的大小是多少。
-  通过管道传递的数据是顺序的，从管道中读取出来的字节的顺序和它们被写入管道的顺序是完全一样的。
-  在管道中的数据的传递方向是单向的，一端用于写入，一端用于读取，管道是**半双工**的。 
-  从管道**读数据是一次性操作，数据一旦被读走，它就从管道中被抛弃**，释放空间以便写更多的数据，在管道中无法使用 lseek() 来随机的访问数据。
- **匿名管道**只能在**具有公共祖先的进程**(*父进程与子进程，或者两个兄弟进程，具有亲缘关系*)之间使用，

<img width="758" alt="image" src="https://user-images.githubusercontent.com/41602569/156878016-ed4f9e87-3951-41de-a79a-d616f4f1279b.png">
- 因为父子进程之间共享文件描述符，可以访问同一管道。
<img width="754" alt="image" src="https://user-images.githubusercontent.com/41602569/156878133-0381d317-9aab-4317-b4af-aeda1e014105.png">

### 管道的数据结构

循环队列

<img width="741" alt="image" src="https://user-images.githubusercontent.com/41602569/156878203-f0ffdbbf-4f02-4a27-9d9d-ecf7f9e5d923.png">

### 匿名管道的使用

![pipe](https://user-images.githubusercontent.com/41602569/156878341-33b28e53-44f7-4979-ad7f-3cf33acfe03b.jpg)

#### int pipe(int pipefd[2])

- 管道默认是**阻塞**的：如果管道中**没有数据，read阻塞，如果管道满了，write阻塞**
- 注意：匿名管道只能用于具有关系的进程之间的通信（父子进程，兄弟进程）

```
#include <unistd.h>
/*
	功能：创建一个匿名管道，用来进程间通信。
	参数：int pipefd[2] 这个数组是一个传出参数。
		pipefd[0] 对应的是管道的读端
		pipefd[1] 对应的是管道的写端
	返回值：
		成功 0
		失败 -1
*/
int pipe(int pipefd[2]);
```

- 应用

```
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    // 在fork之前创建管道
    int pipefd[2];
    int ret = pipe(pipefd);
    if(ret == -1) {
        perror("pipe");
        exit(0);
    }

    // 创建子进程
    pid_t pid = fork();
    if(pid > 0) {
        // 父进程
        printf("i am parent process, pid : %d\n", getpid());

        // 关闭写端
        close(pipefd[1]);
        
        // 从管道的读取端读取数据
        char buf[1024] = {0};
        while(1) {
            int len = read(pipefd[0], buf, sizeof(buf));
            printf("parent recv : %s, pid : %d\n", buf, getpid());
            
            // 向管道中写入数据
            //char * str = "hello,i am parent";
            //write(pipefd[1], str, strlen(str));
            //sleep(1);
        }

    } else if(pid == 0){
        // 子进程
        printf("i am child process, pid : %d\n", getpid());
        // 关闭读端
        close(pipefd[0]);
        // char buf[1024] = {0};
        while(1) {
            // 向管道中写入数据
            char * str = "hello,i am child";
            write(pipefd[1], str, strlen(str));
            //sleep(1);

            // int len = read(pipefd[0], buf, sizeof(buf));
            // printf("child recv : %s, pid : %d\n", buf, getpid());
            // bzero(buf, 1024);
        }
        
    }
    return 0;
}
```
### 查看默认管道大小

- `ulimit -a` 

-  long size = fpathconf(pipefd[0], \_PC_PIPE_BUF);

```
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    int pipefd[2];

    int ret = pipe(pipefd);

    // 获取管道的大小
    long size = fpathconf(pipefd[0], _PC_PIPE_BUF);

    printf("pipe size : %ld\n", size);

    return 0;
}
```

