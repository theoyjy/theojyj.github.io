_[homepage](../index.md)_

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

- 作用：
	1. 移动文件指针到文件头`lseek(fd,0,SEEK_SET);`
	2. 获取当前文件指针的位置`lseek(fd,0,SEEK_CUR);`
	3. 获取当前文件长度`lseek(fd,0,SEEK_END);`
	4. **拓展文件的长度，当前文件10b，增加100个字节`lseek(fd,100,SEEK_END);`:用来为大型文件占空间**。

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
作用：获取文件相关的信息
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
- 应用
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
作用：获取软链接文件的信息（stat会获取软链接所指向文件的信息）
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
### 创建软链接`ln -s a.txt b.txt`，b.txt是a.txt的软链接

## [ls-l 模拟实现](./ls-l.cpp)
### 调用函数：
```
#include<pwd.h>	//struct passwd * getpwuid(st.st_uid);
#include<grp.h>	//struct ... * getgrgid(st.st_gid);
#include<time.h> //char * ctime(&st.st_mtime);
#include<string.h> //strncpy(char * dest, char * src, length);
		   //sprintf(char * dest, "formation", argument lists);

	//文件所有者
	char * fileUser = getpwuid(st.st_uid) -> pw_name;

	//文件所在组
	char * fileGroup = getgrgid(st.st_gid)->gr_name;

	//文件大小
	long int fileSize = st.st_size;

	//获取修改时间
	char * time = ctime(&st.st_mtime);//自带回车
	//去掉回车
	char mtime[512] = {0};
	strncpy(mtime, time,strlen(time)-1);

	char buf[1024];
	sprintf(buf,"%s %d %s %s %d %s %s",perms,linkNum,fileUser,fileGroup,fileSize,time,argv[1]);
	printf("%s\n",buf);
```

# 文件属性操作函数
## int access(const char * pathname,int mode); 
### 判断对文件的权限或者文件是否存在
```
#include<unistd.h>
/*
	mode:
		R_OK,W_OK,X_OK
		F_OK:判断文件是否存在
	return val:
		0  success
		-1 failure
*/
int access(const char * pathname,int mode);
```
## int chmod(const char * pathname, mode_t mode);
修改文件权限
```
#include<sys/stat.h>
/*
	mode : 需要修改的权限值，八进制数
	return val : 
		0  success
		-1 failure
*/
int chmod(const char * pathname, mode_t mode);
```
## int chown(const char * pathname, uid_t owner,gid_t group);
修改文件所属的用户或组

## int truncate(const char * path, off_t length)
作用：缩减或者扩展文件的尺寸至指定大小
```
#include<unistd.h>
#include<sys/types.h>
/*
	length：文件最终变成的大小
	return:
		0  success
		-1 failure
*/
int truncate(const char * path, off_t length);

int main(){
	int ret = truncate("a.txt", 5);
	if(ret==-1){
		perror("truncate");
		return -1;
	}
	return 0;
}
```

# 目录操作函数
## int mkdir(const char * path, mode_t mode)等价于指令mkdir
### 用户必须有目录的可执行权限 才可以进入目录
创建目录
```
#include<sys/stat.h>
#Include<sys/types.h>
// mode 八进制值
// return 0 success -1 failure
int mkdir(const char * path, mode_t mode);

int main(){
	int ret = mkdir("aaa",0777);
	//perror
	return 0;
}
```
## int rmdir(const char * path)
删除空目录

## int rename(const char * oldpath, const char * newpath)
```
#include<stdio.h>
int main(){
	int res = rename("aaa","bbb");
	//perror
	return 0;
}
```
## int chdir(const char * path)
修改**进程**的工作目录

## char * getcwd(char * buf, size_t size)
得到进程当前工作目录
```
#include<unistd.h>

int chdir(const char * path);
// return: 返回指向的一块内存，就是buf的地址
char * getcwd(char * buf, size_t size);

int main(){
	//获取当前目录
	char * buf[128] = {0};
	getcwd(buf,sizeof(buf));
	printf("当前工作目录是：%s",buf);
	
	//修改工作目录
	int ret = chdir("home/Linux/lesson13");
	if(ret==-1){
		perror("chidir");
		return -1;
	}
	
	//创建一个新文件,在新目录下
	int fd = open("chdir.txt", O_CREATE | O_RDWR, 0664);
	if(fd==-1){
		perror("open");
		return -1;
	}
	
	//获取当前目录
	char * buf2[128] = {0};
	getcwd(buf2,sizeof(buf2));
	printf("当前工作目录是：%s",buf2);
	return 0;
}

```
## DIR * opendir(const char * name);
作用：打开一个目录 
```
// 打开一个目录
    #include <sys/types.h>
    #include <dirent.h>
    
    参数：
            - name: 需要打开的目录的名称
        返回值：
            DIR * 类型，理解为目录流
            错误返回NULL
	    
    DIR *opendir(const char *name);
```
## struct dirent * readdir(DIR * dirp)
作用：读取目录中的数据
```

    
    #include <dirent.h>
    struct dirent *readdir(DIR *dirp);
        - 参数：dirp是opendir返回的结果
        - 返回值：
            struct dirent，代表读取到的文件的信息
            读取到了末尾或者失败了，返回NULL
```
## int closedir(DIR * dirp)
作用：关闭目录
```
#include <sys/types.h>
#include <dirent.h>
int closedir(DIR *dirp);
```

- 使用
```
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int getFileNum(const char * path);

// 读取某个目录下所有的普通文件的个数
int main(int argc, char * argv[]) {

    if(argc < 2) {
        printf("%s path\n", argv[0]);
        return -1;
    }

    int num = getFileNum(argv[1]);

    printf("普通文件的个数为：%d\n", num);

    return 0;
}

// 用于获取目录下所有普通文件的个数
int getFileNum(const char * path) {

    // 1.打开目录
    DIR * dir = opendir(path);

    if(dir == NULL) {
        perror("opendir");
        exit(0);
    }

    struct dirent *ptr;

    // 记录普通文件的个数
    int total = 0;

    while((ptr = readdir(dir)) != NULL) {

        // 获取名称
        char * dname = ptr->d_name;

        // 忽略掉. 和..
        if(strcmp(dname, ".") == 0 || strcmp(dname, "..") == 0) {
            continue;
        }

        // 判断是否是普通文件还是目录
        if(ptr->d_type == DT_DIR) {
            // 目录,需要继续读取这个目录
            char newpath[256];
            sprintf(newpath, "%s/%s", path, dname);
            total += getFileNum(newpath);
        }

        if(ptr->d_type == DT_REG) {
            // 普通文件
            total++;
        }


    }

    // 关闭目录
    closedir(dir);

    return total;
}
```
## int dup(int oldfd)
作用：复制一个新的文件描述符
```
#include <unistd.h>

fd=3, int fd1 = dup(fd),
fd指向的是a.txt, fd1也是指向a.txt
从空闲的文件描述符表中找一个最小的，作为新的拷贝的文件描述符

int dup(int oldfd);

```
- 应用
```
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main() {

    int fd = open("a.txt", O_RDWR | O_CREAT, 0664);

    int fd1 = dup(fd);

    if(fd1 == -1) {
        perror("dup");
        return -1;
    }

    printf("fd : %d , fd1 : %d\n", fd, fd1);

    close(fd);

    char * str = "hello,world";
    int ret = write(fd1, str, strlen(str));
    if(ret == -1) {
        perror("write");
        return -1;
    }

    close(fd1);

    return 0;
}
```
## int dup2(int oldfd, int newfd)
作用：重定向文件描述符
```
#include <unistd.h>
	oldfd 指向 a.txt, newfd 指向 b.txt
	调用函数成功后：newfd 和 b.txt 做close, newfd 指向了 a.txt
	oldfd 必须是一个有效的文件描述符
	oldfd和newfd值相同，相当于什么都没有做
int dup2(int oldfd, int newfd);
```
- 应用
fd2 = fd1 != fd 但都指向同一个文件
```
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main() {

    int fd = open("1.txt", O_RDWR | O_CREAT, 0664);
    if(fd == -1) {
        perror("open");
        return -1;
    }

    int fd1 = open("2.txt", O_RDWR | O_CREAT, 0664);
    if(fd1 == -1) {
        perror("open");
        return -1;
    }

    printf("fd : %d, fd1 : %d\n", fd, fd1);

    int fd2 = dup2(fd, fd1);
    if(fd2 == -1) {
        perror("dup2");
        return -1;
    }

    // 通过fd1去写数据，实际操作的是1.txt，而不是2.txt
    char * str = "hello, dup2";
    int len = write(fd1, str, strlen(str));

    if(len == -1) {
        perror("write");
        return -1;
    }

    printf("fd : %d, fd1 : %d, fd2 : %d\n", fd, fd1, fd2);

    close(fd);
    close(fd1);

    return 0;
}
```
## int fcntl(int fd, int cmd, ...);
作用:
	1.复制文件描述符
	2.获取指定的文件描述符文件状态flag
	3.设置文件描述符文件状态flag,要与原先的flag或，不然会丢失之前的状态
```
#include <unistd.h>
#include <fcntl.h>

int fcntl(int fd, int cmd, ...);
参数：
	fd : 表示需要操作的文件描述符
	cmd: 表示对文件描述符进行如何操作
		- F_DUPFD : 复制文件描述符,复制的是第一个参数fd，得到一个新的文件描述符（返回值）
			int ret = fcntl(fd, F_DUPFD);

		- F_GETFL : 获取指定的文件描述符文件状态flag
		  获取的flag和我们通过open函数传递的flag是一个东西。

		- F_SETFL : 设置文件描述符文件状态flag
		  必选项：O_RDONLY, O_WRONLY, O_RDWR 不可以被修改
		  可选性：O_APPEND, O_NONBLOCK
			O_APPEND  表示追加数据
			O_NONBLOK 设置成非阻塞

	阻塞和非阻塞：描述的是函数调用的行为。
```
-  应用
```
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main() {

    // 1.复制文件描述符
    // int fd = open("1.txt", O_RDONLY);
    // int ret = fcntl(fd, F_DUPFD);

    // 2.修改或者获取文件状态flag
    int fd = open("1.txt", O_RDWR);
    if(fd == -1) {
        perror("open");
        return -1;
    }

    // 获取文件描述符状态flag
    int flag = fcntl(fd, F_GETFL);
    if(flag == -1) {
        perror("fcntl");
        return -1;
    }
    flag |= O_APPEND;   // flag = flag | O_APPEND

    // 修改文件描述符状态的flag，给flag加入O_APPEND这个标记
    int ret = fcntl(fd, F_SETFL, flag);
    if(ret == -1) {
        perror("fcntl");
        return -1;
    }

    char * str = "nihao";
    write(fd, str, strlen(str));

    close(fd);

    return 0;
}
```
