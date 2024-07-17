---
finished: false
---

[homepage](index.md)
# exec
## 作用
- exec 函数族的作用是根据指定的文件名找到可执行文件，并用它来**取代调用进程的内容**，换句话说，就是**在调用进程内部执行一个可执行文件**。
- exec 函数族的函数**执行成功后不会返回**，因为**调用进程的实体，包括代码段，数据 段和堆栈等都已经被新的内容取代**，只留下进程 ID 等一些表面上的信息仍保持原样， 颇有些神似“三十六计”中的“金蝉脱壳”。看上去还是旧的躯壳，却已经注入了新的灵 魂。只有调用失败了，它们才会返回 -1，从原程序的调用点接着往下执行。

## int execl(const char * path, const char * arg, ..., nullptr);
**在指定路径下**
```
#include <unistd.h>
/*  
	- 参数：
		- path:需要指定的执行的文件的路径或者名称
			a.out /home/nowcoder/a.out 推荐使用绝对路径
			./a.out hello world

		- arg:是执行可执行文件所需要的参数列表
			第一个参数一般没有什么作用，为了方便，一般写的是执行的程序的名称 a.out
			从第二个参数开始往后，就是程序执行所需要的的参数列表。
			参数最后需要以NULL结束（哨兵）

	- 返回值：
		只有当调用失败，才会有返回值，返回-1，并且设置errno
		如果调用成功，没有返回值。
*/
int execl(const char *path, const char *arg, ...);
```

## int execlp(const char * file, const char * arg, ... );
**在环境变量中找指定的可执行文件**

```
#include <unistd.h>
/*  
	- 会到环境变量中查找指定的可执行文件，如果找到了就执行，找不到就执行不成功。
	- 参数：
		- file:需要执行的可执行文件的文件名
			a.out
			ps

		- arg:是执行可执行文件所需要的参数列表
			第一个参数一般没有什么作用，为了方便，一般写的是执行的程序的名称
			从第二个参数开始往后，就是程序执行所需要的的参数列表。
			参数最后需要以NULL结束（哨兵）

	- 返回值：
		只有当调用失败，才会有返回值，返回-1，并且设置errno
		如果调用成功，没有返回值。
*/
int execlp(const char *file, const char *arg, ... );
```

### execv, execve
```
//argv是需要的参数的一个字符串数组
int execv(const char *path, char *const argv[]);

char * argv[] = {"ps", "aux", NULL};
execv("/bin/ps", argv);

//自己要定义一个数组储存自己定义的环境变量
int execve(const char *filename, char *const argv[], char *const envp[]);
char * envp[] = {"/home/nowcoder", "/home/bbb", "/home/aaa"};

```

<img width="936" alt="image" src="https://user-images.githubusercontent.com/41602569/156770161-9fe20255-ff88-4609-ae85-1978d75dc8bc.png">
