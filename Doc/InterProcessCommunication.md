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

### 匿名管道的特质

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

### 匿名管道的数据结构

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
	- 半双工：父读子写，各自close一个fd
	- 全双工：都读都写，不close：(一般不这样用)
		- 子写;sleep(1);子读
		- 父读;父写;sleep(1)
		- 如果子不sleep，就会子读自己刚写的; 父同理
		- 必须保证一个先读，一个先写

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

### 匿名管道通信实例

```
/*
    实现 ps aux | grep xxx 父子进程间通信
    
    子进程： ps aux, 子进程结束后，将数据发送给父进程
    父进程：获取到数据，过滤
    pipe()
    execlp()
    子进程将标准输出 stdout_fileno 重定向到管道的写端。  dup2(fd[1],stdout_fileno)
*/

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>

int main() {

    // 创建一个管道
    int fd[2];
    int ret = pipe(fd);

    if(ret == -1) {
        perror("pipe");
        exit(0);
    }

    // 创建子进程
    pid_t pid = fork();

    if(pid > 0) {
        // 父进程
        // 关闭写端
        close(fd[1]);
        // 从管道中读取
        char buf[1024] = {0};

        int len = -1;
        while((len = read(fd[0], buf, sizeof(buf) - 1)) > 0) {
            // 过滤数据输出
            printf("%s", buf);
            memset(buf, 0, 1024);
        }

        wait(NULL);

    } else if(pid == 0) {
        // 子进程
        // 关闭读端
        close(fd[0]);

        // 文件描述符的重定向 stdout_fileno -> fd[1]
        dup2(fd[1], STDOUT_FILENO);
        // 执行 ps aux
        execlp("ps", "ps", "aux", NULL);
        perror("execlp");
        exit(0);
    } else {
        perror("fork");
        exit(0);
    }


    return 0;
}
```

### 匿名管道的读写特点：

使用管道时，需要注意以下几种特殊的情况（假设都是阻塞I/O操作）
1. 所有的**指向管道写端的文件描述符都关闭**了（管道写端引用计数为0），有进程从管道的读端读数据，那么**管道中剩余的数据被读取以后，再次read会返回0，就像读到文件末尾一样**。

2. 如果有指向管道**写端的文件描述符没有关闭**（管道的写端引用计数大于0），而持有管道写端的进程也**没有往管道中写数据，这个时候有进程从管道中读取数据**，那么管道中剩余的数据被读取后，
再次**read会阻塞，直到管道中有数据可以读了才读取数据并返回**。

3. 如果**所有指向管道读端的文件描述符都关闭**了（管道的读端引用计数为0），这个时候有进程
向管道中**写数据，那么该进程会收到一个信号SIGPIPE, 通常会导致进程异常终止**。

4. 如果有指向管道读端的文件描述符没有关闭（管道的读端引用计数大于0），而持有管道读端的进程
也没有从管道中读数据，这时有进程向管道中写数据，那么在管道**被写满的时候再次write会阻塞，
直到管道中有空位置才能再次写入数据并返回**。

#### 总结：
    - 读管道：
        - 管道中有数据，read返回实际读到的字节数。
        - 管道中无数据：
            - 写端被全部关闭，read返回0（相当于读到文件的末尾）
            - 写端没有完全关闭，read阻塞等待

    - 写管道：
        - 管道读端全部被关闭，进程异常终止（进程收到SIGPIPE信号）
        - 管道读端没有全部关闭：
            - 管道已满，write阻塞
            - 管道没有满，write将数据写入，并返回实际写入的字节数

### 非阻塞管道的读写

```
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
/*
    设置仅读端管道非阻塞
    int flags = fcntl(fd[0], F_GETFL);  // 获取原来的flag
    flags |= O_NONBLOCK;            // 修改flag的值
    fcntl(fd[0], F_SETFL, flags);   // 设置新的flag
*/
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

        int flags = fcntl(pipefd[0], F_GETFL);  // 获取原来的flag
        flags |= O_NONBLOCK;            // 修改flag的值
        fcntl(pipefd[0], F_SETFL, flags);   // 设置新的flag

        while(1) {
            int len = read(pipefd[0], buf, sizeof(buf));
	    //管道为空，return len = -1
            printf("len : %d\n", len);
	    
            printf("parent recv : %s, pid : %d\n", buf, getpid());
            memset(buf, 0, 1024);//清空buff
            sleep(1);
        }

    } else if(pid == 0){
        // 子进程
        printf("i am child process, pid : %d\n", getpid());
        // 关闭读端
        close(pipefd[0]);
        char buf[1024] = {0};
        while(1) {
            // 向管道中写入数据
            char * str = "hello,i am child";
            write(pipefd[1], str, strlen(str));
            sleep(5);
        }
        
    }
    return 0;
}
```

## 有名管道 FIFO

- 匿名管道，由于没有名字，只能用于亲缘关系的进程间通信。为了克服这个缺点，提 出了有名管道(FIFO)，也叫命名管道、FIFO文件。
- 有名管道(FIFO)不同于匿名管道之处在于它**提供了一个路径名与之关联，以 FIFO 的文件形式存在于文件系统中**，并且其打开方式与打开一个普通文件是一样的，这样即使与 FIFO 的创建进程不存在亲缘关系的进程，**只要可以访问该路径，就能够彼此通过 FIFO 相互通信，因此，通过 FIFO 不相关的进程也能交换数据。**
- 一旦打开了 FIFO，就能在它上面使用与操作匿名管道和其他文件的系统调用一样的 I/O系统调用了(如read()、write()和close())。与管道一样，FIFO 也有一个写入端和读取端，并且从管道中读取数据的顺序与写入的顺序是一样的。FIFO 的名称也由此而来:**先入先出**。

## 有名管道(FIFO)和匿名管道(pipe)，不同点:
	1. FIFO 在文件系统中作为一个特殊文件存在，但 FIFO 中的内容却存放**在内存中**。 
	2. 当**使用 FIFO 的进程退出后，FIFO 文件将继续保存在文件系统中以便以后使用**。 
	3. FIFO 有名字，**不相关的进程可以通过打开有名管道进行通信**。

### 创建FIFO文件

1.通过命令： 命令行 `mkfifo 名字`
2.通过函数：int mkfifo(const char * pathname, mode_t mode);
	- 一旦使用 mkfifo 创建了一个 FIFO，就可以使用 open 打开它，常见的文件 I/O 函数都可用于 fifo。如:close、read、write、unlink 等。
	- FIFO 严格遵循先进先出(First in First out)，对管道及 FIFO 的读总是从开始处返回数据，对它们的写则把数据添加到末尾。它们不支持诸如 lseek() 等文件定位操作。
```
#include <sys/types.h>
#include <sys/stat.h>
/*
	参数：
		- pathname: 管道名称的路径
		- mode: 文件的权限 和 open 的 mode 是一样的
				是一个八进制的数
	返回值：成功返回0，失败返回-1，并设置错误号
*/
int mkfifo(const char *pathname, mode_t mode);
```

- 应用 mkfifo

```
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // 判断文件是否存在
    int ret = access("fifo1", F_OK);
    if(ret == -1) {
	
        printf("管道不存在，创建管道\n");
        
        ret = mkfifo("fifo1", 0664);

        if(ret == -1) {
            perror("mkfifo");
            exit(0);
        }       
    }
    return 0;
}
```

### 有名管道读写：

- 有名管道的注意事项：
	1.为只读而打开管道的进程会阻塞，直到另外一个进程为只写打开管道
	2.为只写而打开管道的进程会阻塞，直到另外一个进程为只读打开管道

- 读管道：
	- 管道中有数据，read返回实际读到的字节数
	- 管道中无数据：
		- 管道写端被全部关闭，read返回0，（相当于读到文件末尾）
		- 写端没有全部被关闭，read阻塞等待

- 写管道：
	- 管道读端被全部关闭，进行异常终止（收到一个SIGPIPE信号）
	- 管道读端没有全部关闭：
		- 管道已经满了，write会阻塞
		- 管道没有满，write将数据写入，并返回实际写入的字节数。

#### 写入FIFO

```
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {

    // 1.判断文件是否存在
    int ret = access("test", F_OK);
    if(ret == -1) {
        printf("管道不存在，创建管道\n");
        
        // 2.创建管道文件
        ret = mkfifo("test", 0664);

        if(ret == -1) {
            perror("mkfifo");
            exit(0);
        }       

    }

    // 3.以只写的方式打开管道
    int fd = open("test", O_WRONLY);
    if(fd == -1) {
        perror("open");
        exit(0);
    }

    // 写数据
    for(int i = 0; i < 100; i++) {
        char buf[1024];
        sprintf(buf, "hello, %d\n", i);
        printf("write data : %s\n", buf);
        write(fd, buf, strlen(buf));
        sleep(1);
    }

    close(fd);

    return 0;
}
```

#### 从FIFO中读取

```
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

// 从管道中读取数据
int main() {

    // 1.打开管道文件
    int fd = open("test", O_RDONLY);
    if(fd == -1) {
        perror("open");
        exit(0);
    }

    // 读数据
    while(1) {
        char buf[1024] = {0};
        int len = read(fd, buf, sizeof(buf));
        if(len == 0) {
            printf("写端断开连接了...\n");
            break;
        }
        printf("recv buf : %s\n", buf);
    }

    close(fd);

    return 0;
}
```

### 有名管道实现简单聊天功能

通过两个FIFO，两个进程都对一个只读另一个只写
chatA.c:

```
int main() {

    // 1.判断有名管道文件是否存在
    int ret = access("fifo1", F_OK);
    if(ret == -1) {
        // 文件不存在
        printf("管道不存在，创建对应的有名管道\n");
        ret = mkfifo("fifo1", 0664);
        if(ret == -1) {
            perror("mkfifo");
            exit(0);
        }
    }

    ret = access("fifo2", F_OK);
    if(ret == -1) {
        // 文件不存在
        printf("管道不存在，创建对应的有名管道\n");
        ret = mkfifo("fifo2", 0664);
        if(ret == -1) {
            perror("mkfifo");
            exit(0);
        }
    }

    // 2.以只写的方式打开管道fifo1
    int fdw = open("fifo1", O_WRONLY);
    if(fdw == -1) {
        perror("open");
        exit(0);
    }
    printf("打开管道fifo1成功，等待写入...\n");
    // 3.以只读的方式打开管道fifo2
    int fdr = open("fifo2", O_RDONLY);
    if(fdr == -1) {
        perror("open");
        exit(0);
    }
    printf("打开管道fifo2成功，等待读取...\n");

    char buf[128];

    // 4.循环的写读数据
    while(1) {
        memset(buf, 0, 128);
        // 获取标准输入的数据
        fgets(buf, 128, stdin);
        // 写数据
        ret = write(fdw, buf, strlen(buf));
        if(ret == -1) {
            perror("write");
            exit(0);
        }

        // 5.读管道数据
        memset(buf, 0, 128);
        ret = read(fdr, buf, 128);
        if(ret <= 0) {
            perror("read");
            break;
        }
        printf("buf: %s\n", buf);
    }

    // 6.关闭文件描述符
    close(fdr);
    close(fdw);

    return 0;
}
```

## 内存映射

<img width="1348" alt="image" src="https://user-images.githubusercontent.com/41602569/156887815-c298ddc1-7e83-4a27-9205-f244e82e227f.png">

### void * mmap(void * addr, size_t length, int prot, int flags,int fd, off_t offset);

功能：将一个文件或者设备的数据映射到内存中

```
#include <sys/mman.h>
/*
	- 参数：
	    - void *addr: NULL, 由内核指定
	    - length : 要映射的数据的长度，这个值不能为0。建议使用文件的长度。
		    获取文件的长度：stat lseek
	    - prot : 对申请的内存映射区的操作权限
		-PROT_EXEC ：可执行的权限
		-PROT_READ ：读权限
		-PROT_WRITE ：写权限
		-PROT_NONE ：没有权限
		要操作映射内存，必须要有读的权限。
		PROT_READ、PROT_READ|PROT_WRITE
	    - flags :
		- MAP_SHARED : 映射区的数据会自动和磁盘文件进行同步，进程间通信，必须要设置这个选项
		- MAP_PRIVATE ：不同步，内存映射区的数据改变了，对原来的文件不会修改，会重新创建一个新的文件。（copy on write）
	    - fd: 需要映射的那个文件的文件描述符
		- 通过open得到，open的是一个磁盘文件
		- 注意：文件的大小不能为0，open指定的权限不能和prot参数有冲突。
		    prot: PROT_READ                open:只读/读写 
		    prot: PROT_READ | PROT_WRITE   open:读写
	    - offset：偏移量，一般不用。必须指定的是4k的整数倍，0表示不便宜。
	- 返回值：返回创建的内存的首地址
	    失败返回MAP_FAILED，(void *) -1
*/
void * mmap(void *addr, size_t length, int prot, int flags,int fd, off_t offset);
```

### int munmap(void * addr, size_t length);
功能：释放内存映射

```
/*
	- 参数：
		- addr : 要释放的内存的首地址
		- length : 要释放的内存的大小，要和mmap函数中的length参数的值一样。
*/
int munmap(void *addr, size_t length);	    
```



