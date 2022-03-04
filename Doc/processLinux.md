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

[进程退出、孤儿进程、僵尸进程](https://github.com/theoyjy/theojyj.github.io/files/8186173/2.7.pdf)
