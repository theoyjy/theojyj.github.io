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

