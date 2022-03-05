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


