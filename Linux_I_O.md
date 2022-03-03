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
#include<stdio.h>
/*
	errno：属于linux系统函数库，库里的一个全局变量，记录的是最近的错误号
	s : 用户描述，比如hello，实际最终输出内容：hello：xxx（实际错误描述）
*/
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

## read AND write
### ssize_t read(int fd,void * buf, size_t count)
```
#include<unistd.h>
/*
    参数：
      - fd： open得到的
      - buf：需要读取数据存放的地方，数组的地址（传出参数）
      - count：指定的数组的大小
    返回值：
      - >0:返回实际读取到的字节数
      - =0:文件已经读取玩
      - -1:失败
*/

ssize_t read(int fd, void * fd,size_t count);
```

### ssize_t write(int fd,const void * buf,size_t count)
```
#include<unistd.h>
/*
    参数：
      - fd： open得到的
      - buf：需要读取数据存放的地方，数组的地址（传出参数）
      - count：指定的数组的大小
    返回值：
      - >0:返回实际读取到的字节数
      - =0:文件已经读取玩
      - -1:失败
*/
ssize_t write(int fd,const void * buf,size_t count);
```
## 拷贝文件
```
#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int main(){
  //1.open 要读的文件
  int srcfd = open("a.txt",O_RDONLY);
  if(src==-1){
    perror("open");
    return -1;
  }
  //2.创建一个新的文件去写
  int destfd = open("b.txt",O_WRONLY|_O_CREATE,0664);
  if(destfd==-1){
    perror("open");
    return -1;
  }
  //3.频繁的读写
  char buf[1024] = {0};
  int len = 0;
  while((len= read(srcfd,buf,sizeof(buf))) > 0){
    write(destfd,buf,len);
  }
  //4.关闭文件
  close(srcfd);
  close(destfd);
  
  return 0;
}
```

## lseek 与 fseek
### off_t lseek(int fd, off_t offset, int whence);
```
//LINUX 系统函数
#include<unistd.h>
#include<sys/types.h>
/*
   参数：
      - fd
      - offset：偏移量
      - whence：
          - SEEK_SET
              从文件起始地方开始偏移offset
          - SEEK_CUR
              当前位置+第二个参数offset的值
          - SEEK_END
              文件大小+第二个参数
   返回：指针所指的offset
*/
off_t lseek(int fd, off_t offset, int whence);

//标准C库
#include<stdio.h>
int fseek(FILE * stream,long offset, int whence);
```
### 作用：
1. 移动文件指针到文件头`lseek(fd,0,SEEK_SET);`
2. 获取当前文件指针的位置`lseek(fd,0,SEEK_CUR);`
3. 获取当前文件长度`lseek(fd,0,SEEK_END);`
4. **拓展文件的长度，当前文件10b，增加100个字节`lseek(fd,100,SEEK_END);`:用来为大型文件占空间**
```
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
int main(){
  int fd = open("a.txt",O_RDWR);
  if(fd==-1){
    perror("open");
    return -1;
  }
  
  //拓展文件长度
  int ret = lseek(fd,100,SEEK_END);
  if(ret==-1){
  	  perror("lseek");
	  return -1;
  }
  //写入一个空数据才能拓展成功
  write(fd," ",1);
  
  close(fd);
  return 0;
}
```
## stat AND lstat

<img width="1230" alt="image" src="https://user-images.githubusercontent.com/41602569/156625775-889cdfc9-1749-4949-8415-07a2020a3f48.png">

<img width="1230" alt="image" src="https://user-images.githubusercontent.com/41602569/156625834-2f4d2043-4c18-43bb-ba41-b1545f70d8cc.png">
- st_mode是八进制，以0开始为标志
- 要**获取文件类**：st_mode & S_IFMT
	- S_IFMT = 0170000 =0b1111 0000 0000 0000
	- 将与的结果与具体的文件类型的宏去与
	- e.g. S_IFSOCK & (st_mode & S_IFMT) 判断是否是套接字
- 要获取文件访问权限：想知道哪个就和哪个宏与
	- e.g. 想知道用户是否有写权限(S_IRUSER: is read user?):st_mode & S_IRUSR

### int stat(const char * pathname,struct stat * statbuf);
```
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
/*
参数：
	statbuf：结构体变量，传出参数，用于保存文件信息
返回值：
	成功：返回0
	失败：返回-1，设置errno
*/
int stat(const char * pathname,struct stat * statbuf);
```
### 作用：获取文件相关的信息
```
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>

int main(){
	struct stat statbuf;
	int ret = stat("a.txt",&statbuf);
	if(ret == -1){
		perror("stat");
		return -1;
	}
	printf("size: %ld\n", statbuf.st_size);
	return 0;
}
```
### int lstat(const char * pathname,struct stat * statbuf);
```
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
/*
参数：
	statbuf：结构体变量，传出参数，用于保存文件信息
返回值：
	成功：返回0
	失败：返回-1，设置errno
*/
int lstat(const char * pathname,struct stat * statbuf);
```
### 作用：获取软链接文件的信息（stat会获取软链接所指向文件的信息）
### 创建软链接`ln -s a.txt b.txt`，b.txt是a.txt的软链接
