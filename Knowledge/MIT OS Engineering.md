- [ ] OSE Labs  [start:: 2024-05-07]
	- [x] lab1  [completion:: 2024-05-19]
	- [ ] lab2
	- [ ] lab3
	- [ ] lab4
	- [ ] lab5
	- [ ] lab6
[OS: MIT 6.828 Operating System Lab ](https://github.com/SmallPond/MIT6.828_OS)   ([Lectures](https://pdos.csail.mit.edu/6.828/2018/schedule.html))
[2023版本课程](https://pdos.csail.mit.edu/6.828/2023/tools.html)

>[!Tip] C Pointer
>1. If `int *p = (int*)100`, then `(int)p + 1` and `(int)(p + 1)` are different: the first is 101 but the second is 104(==because pointer increments the address it points to by the size of the type that it points to==)
>2. `p[i]` is the same as `*(p+1)`

# Lab1
## ping pong
>[!Tip] pipeline And fork new process
>```c
>// example pingpong.c
>int main()
>{
>	int fd[2], pid, nBytes = 1;
>	char buf[64];
>	
>	pipe(fd); // always read from fd[1], write to fd[0]
>   
>	pid = fork();
>	if(pid == 0) // child
>	{
>		read(fd[0], buf, nBytes);
>		printf("%d: received ping\n", getpid());
>		write(fd[1], "h", nBytes)
>	}
>	else // parent
>	{
>		write(fd[1], "h", nBytes)
>		read(fd[0], buf, 1);
>		printf("%d: received ping\n", getpid());
>	}
>	exit(0);
>}
>```

## Communication Sequential Processes
>[!INFO] Communicating Sequential Processes (CSP)
>each process takes its first input as a prime, output every number that is not multiple of the prime to its child process

## find
**recursive find a file**
```
$ find . -name b // recursively find all files which name == "b" from current path
```

## xargs
>[!INFO]
>1. treat each previous command's output as its standard input
>2. for each input, append it to the assigned command as following arguments
```
// eg1
$ (echo 1; echo 2) | xargs echo 3
3 1
3 2
// equal to:
$ echo 3 1
$ echo 3 1

// eg2
$ echo hello > b
$ find . b | xargs grep hello
hello
// equals to
$ grep hello ./b
```
# Chapter 1
## 1.1 Process and memory
>[!INFO] : Process (pid)
>Consists of :
>1. instructions, data, stack
>2. pre-process state
>
>Create:
>fork(): gives new process an exact copy of calling process' mem
>```cpp
>	int pid = fork();
>	if(pid > 0)  { }// parent
>	else if(pid == 0){} // child
>	else {} // error
>```

| System call                             |                                                                                                                                                                                                                                                     | example                                            |
| --------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | -------------------------------------------------- |
| int fork()                              |                                                                                                                                                                                                                                                     | int pid = fork();                                  |
| int exit(int status)                    | terminate and report status to wait()                                                                                                                                                                                                               | exit(0);exit(1);                                   |
| int wait(int * status)                  | wait for a child to exit; return child's pid                                                                                                                                                                                                        | wait(0);                                           |
| int kill(int pid)                       | terminate process pid. returns 0, or -1 for error                                                                                                                                                                                                   |                                                    |
| int getpid()                            | current pid                                                                                                                                                                                                                                         |                                                    |
| int sleep(int n)                        | pause for n clock ticks                                                                                                                                                                                                                             |                                                    |
| int exec(char \* file, char \* argv[])  | ==replace the calling process's mem withe a new mem image loaded from a file stored in the file system==<br>when exec succeeds, it does not return to the.<br>only return if error:<br>     if runs successfully, will not run code after exec(..); | exec(comand, argv);                                |
| char \*sbrk(int n)                      | grow process' mem by n bytes. <br>Returns start of new memory                                                                                                                                                                                       |                                                    |
| int open(char \*file, int flags)        |                                                                                                                                                                                                                                                     | int fd = open(path, O_RDONLY)                      |
| int write(int fd, char\* buf, int n)    | write n bytes from buf; returns number read; or 0 if end of file                                                                                                                                                                                    |                                                    |
| int close(int fd)                       | release file descriptor                                                                                                                                                                                                                             | close(fd);                                         |
| int dup(int fd)                         | return a new_fd referring to the same file as fd                                                                                                                                                                                                    |                                                    |
| int pipe(int p[])                       | create pipe, put read/write fds to p[0] and p[1]                                                                                                                                                                                                    | int fd[2];<br>pipe(fd);<br>// see pingpong.c above |
| int chdir(char\*dir)                    | change current dir                                                                                                                                                                                                                                  |                                                    |
| int mkdir(char*dir)                     |                                                                                                                                                                                                                                                     |                                                    |
| int mknod(char\*file, int, int)         | create a device file                                                                                                                                                                                                                                |                                                    |
| int fstat(int fd, struct stat \* st)    | place info about an open file into \*st                                                                                                                                                                                                             |                                                    |
| int stat(char\*file1, struct stat\* st) | place info about a named file into *st*                                                                                                                                                                                                             |                                                    |
| int link(char\* file1, char\* file2)    | create another name(file2) for file1                                                                                                                                                                                                                |                                                    |
| int unlink(char\* file)                 | remove a file                                                                                                                                                                                                                                       |                                                    |
