## Liunx I/O
<img width="1230" alt="image" src="https://user-images.githubusercontent.com/41602569/156598820-2420e45d-912c-4e93-a4df-7268ba5422da.png">
<img width="1230" alt="image" src="https://user-images.githubusercontent.com/41602569/156598894-b4b43ed6-648b-4b2d-9907-3e1c0a05f1d0.png">


## 虚拟地址空间

<img width="1230" alt="image" src="https://user-images.githubusercontent.com/41602569/156595438-140b2347-4504-4246-ac84-7087ad30c923.png">

- 内存分为内核去与用户区，CPU中的MMU（内存管理单元 Memory Management Unit），将磁盘空间映射到内存空间
- 受保护地址：NULL, nullpty
- 通过系统调用，进入内核区

<img width="1230" alt="image" src="https://user-images.githubusercontent.com/41602569/156596784-7705d0a6-4dd6-44df-b164-b4af2413d69e.png">

- 文件描述符表(数组[] fd1,fd2...)在内核区，被进程控制块管理(PCB)
- 一个进程可以同时打开多个文件
- 文件描述符表默认是1024，即一个进程最多打开1024个文件
-  Linux中一切皆文件，标准输入/输出/错误，是对应当前到终端的(同一个终端，即对应同一个文件)===> **多个文件描述可以对应同一个文件(图中的0，1，2)**

# LIUNX I/O 系统调用
## open
### int open(const char * pathname,int flags);
```
#include<sys/types.h>
#include<sys/stat.h>  //flags 被定义成宏，在sys/stat.h里
#include<fcntl.h>     //open 声明在fcntl.h
/*
  Parameters:
    - pathname： 文件路径
    - flags: 文件操作权限：O_RDONLY,O_WRONLY,O_RDWR 这三个是互斥的
              还有其他设置      
    - 返回值：返回一个新的文件描述符，-1为打开失败
*/
int open(const char * pathname,int flags);
/*
  flags: 除了以上三个 还有可选项：O_CREAT 当文件不存在，就创建新文件
  mode： 八进制，表示新创建出的文件的操作权限，比如 0775.最终权限是 mode & ~umask
  umask作用：抹去不合理的权限，默认为002
*/
int open(const char * pathname,int flags, mode_t mode);
```
### void perror(const char *s)
```
/*
  errno：属于linux系统函数库，库里的一个全局变量，记录的是最近的错误号
*/
#include<stdio.h>
//  s : 用户描述，比如hello，实际最终输出内容：hello：xxx（实际错误描述）
void perror(const char *s);//用来打印errno对应的错误
```
### void close(int fd);
```
#include<unistd.h>
void close(int fd);
```
## 打开已经存在的文件 open(pathname,flags);
```
int main(){
  int fd = open("a.txt",O_RDONLY);
  if(fd==-1){
    perror("open function error"); // 会输出 open function error: No such file 
  }
  close(fd);
  return 0;
}
```
## 创建新文件 open(pathname,flags,mode)
### int open(const char * pathname,int flags, mode_t mode);
```
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
int main(){
  int fd = open("create.txt",O_RDWD | O_CREATE, 0777);
  if(fd==-1)
    perror("open");
    close(fd);
}
```
