_[homepage](../index.md)_
# Linux 进程操作

## 进程创建 `pid_t fork(void);`
系统允许一个进程创建新进程，新进程即为子进程，子进程还可以创建新的子进程，形成进程树结构模型。

```
#include <sys/types.h>
#include <unistd.h>
/*
  返回值:
    - 成功:
        子进程中返回      0
        父进程中返回      子进程 ID 
    - 失败:
        返回 -1
  失败的两个主要原因:
    1. 当前系统的进程数已经达到了系统规定的上限，这时 errno 的值被设置为 EAGAIN
    2. 系统内存不足，这时 errno 的值被设置为 ENOMEM
*/
pid_t fork(void);
```

- 应用

```
int main(){
  pid_t pid = fork();
  if(pid > 0){
    //父进程
    printf("i am parent process, pid : %d, ppid : %d\n",getpid(),pid);
  }else if(pid == 0){
    //子进程
    printf("i am child process, pid : %d, ppid: %d\n", getpid(), getppid());
  }
  
  for(int i = 0; i < 3; ++i)
    cout << i <<" "<< getpid() << endl;
  return 0;
}
```

## 父子进程虚地址空间

<img width="534" alt="image" src="https://user-images.githubusercontent.com/41602569/156760567-337d49d5-d037-4cc1-9c9f-90de470cc313.png">

**子进程栈中也复制了父进程的栈，但两者对各自栈里的变量修改，是不会对彼此产生影响的**

### 实际上，更准确来说，Linux 的 fork() 使用是通过写时拷贝 (copy- on-write) 实现。

- 写时拷贝是一种可以推迟甚至避免拷贝数据的技术。内核此时并不复制整个进程的地址空间，而是让父子进程共享同一个地址空间。只用在需要写入的时候才会复制地址空间，从而使各个进行拥有各自的地址空间。
- 也就是说，资源的复制是在需要写入的时候才会进行，在此之前，只有以只读方式共享。
- 比如都有num=10只读，父进程要修改，就会为num重新开辟空间赋值；此时子进程仍然只读num=10，当子进程要修改时，子进程为num开辟空间修改
- 注意：fork之后父子进程共享文件，fork产生的子进程与父进程相同的文件文件描述符指向相同的文件表，引用计数增加，共享文件偏移指针。

### 父子进程之间的关系：
- 区别：
  - fork()函数的返回值不同
  - pcb中的一些数据：
    - pid
    - ppid
    - 信号集 
- 共同点：子进程刚创建时，还没有执行任何写操作时
  - 用户区数据
  - 文件描述符
- 父子进程对变量是不是共享的：
  - 刚开始，是一样的，共享的。如果修改了数据，就不共享
  - 读时共享(子进程被创建，两个进程还没有任何写操作)，写时不共享

## GDB多进程调试

- 默认只调试父进程,增加调试子进程：set follow-fork-mode parent|child
- 设置调试模式  ： set detach-on-fork on|off:
  - on  调试当前进程时，其他进程继续
  - off 调试当前进程时，其他进程被挂起
- info inferiors 显示所有被调试的进程
  - inferior 编号 转去调试另一个进程  
- 使进程脱离GDB调试 detach inferiors 编号

## 进程退出

### exit 与 \_exit
```

#include <stdlib.h>
void exit(int status);

#include <unistd.h>
void _exit(int status);

status参数：是进程退出时的一个状态信息。父进程回收子进程资源的时候可以获取到。

```

## 孤儿进程 Orphan

- **父进程运行结束，但子进程还在运行(未运行结束)**，这样的子进程就称为孤儿进程 (Orphan Process)。
- 每当出现一个孤儿进程的时候，**内核就把孤儿进程的父进程设置为init**，而 init 进程会循环地 wait() 它的已经退出的子进程。这样，当一个孤儿进程凄凉地结束 了其生命周期的时候，init 进程就会代表党和政府出面处理它的一切善后工作。
- 因此孤儿进程并**不会有什么危害**。

```
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {

    // 创建子进程
    pid_t pid = fork();

    // 判断是父进程还是子进程
    if(pid > 0) {

        printf("i am parent process, pid : %d, ppid : %d\n", getpid(), getppid());

    } else if(pid == 0) {
        sleep(1);   //父进程已经结束
        // 当前是子进程 变成孤儿进程
        printf("i am child process, pid : %d, ppid : %d\n", getpid(),getppid());
       
    }

    // for循环
    for(int i = 0; i < 3; i++) {
        printf("i : %d , pid : %d\n", i , getpid());
    }

    return 0;
}
```

## 僵尸进程 Zombie

- 每个进程结束之后, 都会释放自己地址空间中的用户区数据，内核区的 _PCB 没有办法 自己释放掉，需要父进程去释放。_
- **进程终止时，父进程尚未回收，子进程残留资源(PCB)存放于内核中，变成僵尸 (Zombie)进程**。
- 僵尸进程不能被 kill -9 杀死, 但可以杀死父进程来释放子进程
- 这样就会导致一个问题，如果父进程不调用 wait() 或 waitpid() 的话，那么保留的那段信息就不会释放，其进程号就会一直被占用， 但是系统所能使用的进程号是有限的，**如果大量的产生僵尸进程，将因为没有可用的进程号而导致系统不能产生新的进程**，此即为僵尸进程的**危害**，应当避免。

```
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {

    // 创建子进程
    pid_t pid = fork();

    // 判断是父进程还是子进程
    if(pid > 0) {
        // 父进程持续不结束，导致子进程变成僵尸进程
        while(1) {
            printf("i am parent process, pid : %d, ppid : %d\n", getpid(), getppid());
            sleep(1);
        }

    } else if(pid == 0) {
        // 当前是子进程
        printf("i am child process, pid : %d, ppid : %d\n", getpid(),getppid());
        // 子进程结束
    }

    // for循环
    for(int i = 0; i < 3; i++) {
        printf("i : %d , pid : %d\n", i , getpid());
    }

    return 0;
}
```

## 进程回收

- 在每个进程退出的时候，**内核释放该进程所有的资源、包括打开的文件、占用的内存等**。但是仍然为其**保留一定的信息，这些信息主要主要指进程控制块PCB的信息 (包括进程号、退出状态、运行时间等)**。 
- 父进程可以通过调用**wait**或**waitpid** **得到它的退出状态同时彻底清除掉这个进程**。 
- wait() 和 waitpid() 函数的功能一样，区别在于，**wait() 函数会阻塞**， **waitpid() 可以设置不阻塞，waitpid() 还可以指定等待哪个子进程结束**。 注意:一次wait或waitpid调用只能清理一个子进程，清理多个子进程应使用循环。

### pid_t wait(int * wstatus)

功能：**阻塞等待**任意一个子进程结束，如果任意一个子进程结束了，此函数会回收子进程的资源。<br>

**调用wait函数的进程会被挂起（阻塞），直到它的一个子进程退出或者收到一个不能被忽略的信号时才被唤醒（相当于继续往下执行）** :

- 如果没有子进程了，函数立刻返回，返回-1；
- 如果子进程都已经结束了，也会立即返回，返回-1.

```
#include <sys/types.h>
#include <sys/wait.h>
/*
  参数：int *wstatus
      用来接收子进程退出时的状态信息，传入的是一个int类型的地址，传出参数。exit(int);
  返回值：
      - 成功：返回被回收的子进程的id
      - 失败：-1 (所有的子进程都结束，调用函数失败) 
*/
pid_t wait(int *wstatus);
```

- 应用

```
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {

    // 有一个父进程，创建5个子进程（兄弟）
    pid_t pid;

    // 创建5个子进程
    for(int i = 0; i < 5; i++) {
        pid = fork();
        if(pid == 0) {//子进程退出循环，不要继续不要创建
            break;
        }
    }

    if(pid > 0) {
        // 父进程
        while(1) {
            printf("parent, pid = %d\n", getpid());

            // int ret = wait(NULL); //不需要获得子进程退出状态
            
            int st;
            int ret = wait(&st);  // ret == childId 或者 -1

            if(ret == -1) {
                break;
            }
            //WIFEXITED() 是否正常退出
            if(WIFEXITED(st)) {
                // 是不是正常退出
                printf("退出的状态码：%d\n", WEXITSTATUS(st)); 
                //WEXITSTATUE()获取状态码7
            }
            //WIFSIGNALED()是否异常终止
            if(WIFSIGNALED(st)) {
                // 是不是异常终止
                printf("被哪个信号干掉了：%d\n", WTERMSIG(st));
                //WTERMSIG()获取终止子进程的状态码
            }

            printf("child die, pid = %d\n", ret);

            sleep(1);
        }

    } else if (pid == 0){
        // 子进程
         while(1) {
            printf("child, pid = %d\n",getpid());    
            sleep(1);       
         }

        exit(0);
    }

    return 0; // exit(0)
}

```

### 退出信息相关宏函数

- WIFEXITED(status) 非0，进程正常退出
  - WEXITSTATUS(status) 如果上宏为真，获取进程退出的状态(exit的参数) 

- WIFSIGNALED(status) 非0，进程异常终止
  - WTERMSIG(status) 如果上宏为真，获取使进程终止的信号编号：
    - 比如被kill -9 杀掉，则返回90
    
- WIFCONTINUED(status) 非0，进程暂停后已经继续运行
- WIFSTOPPED(status) 非0，进程处于暂停状态
- WSTOPSIG(status) 如果上宏为真，获取使进程暂停的信号的编号 

## pid_t waitpid(pid_t pid, int * wstatus, int options)

功能：回收指定进程号的子进程，可以**设置是否阻塞**。

```
#include <sys/types.h>
#include <sys/wait.h>
/*
    
    参数：
        - pid:
            pid > 0 : 某个子进程的pid
            pid = 0 : 回收当前进程组的所有子进程 （可能会将子进程给别的进程组，此时就不会释放给出去的）
            pid = -1 : 回收所有的子进程，相当于 wait()  （最常用）(即使将子进程给别的组，仍然会释放)
            pid < -1 : 某个进程组的组id的绝对值，回收指定进程组中的子进程
        - options：设置阻塞或者非阻塞
            0 : 阻塞
            WNOHANG : 非阻塞
        - 返回值：
            > 0 : 返回子进程的id
            = 0 : options=WNOHANG, 表示还有子进程或者
            = -1 ：错误，或者没有子进程了
*/
pid_t waitpid(pid_t pid, int *wstatus, int options);
```

