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
