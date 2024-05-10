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
```c
#include "kernel/types.h"

#include "user/user.h"

  

// CSP: Communicating Sequential Processes

void redirect(int i, int fd[2])

{

    close(i);  

    dup(fd[i]);

    close(fd[0]);

    close(fd[1]);

}

  

void cull(int p)

{

    int n;

    while(read(0, &n, sizeof(n)))

    {

        if(n % p != 0)

        {

            write(1, &n, sizeof(n));

            printf("cull %d to 1\n", n);

        }

    }

  

}

  

void sink()

{

    int fd[2];

    int prime = 2;

    while(1)

    {

        read(fd[0], &prime, sizeof(prime));

        printf("read prime %d from %d\n", prime, fd[0]);

        pipe(fd);

        if(fork() == 0)

        {

            // redirect(0, fd);

            exit(0);

        }

        else

        {

            // redirect(1, fd);

            cull(prime);

            if(prime == 35)

            {

                exit(0);

            }

        }

  

    }

  

}

  

int main()

{

    int i = 2;

    int fd[2];

    pipe(fd);

    if(fork()) // child

    {

        // redirect(0, fd);

        printf("call sink");

        sink();

    }

    else // parent

    {

        // redirect(1, fd);

        for(; i <= 35; ++i)

        {

            write(fd[1], &i, sizeof(i));

            printf("write %d to fd %d\n", i, fd[1]);

        }

    }

  

    exit(0);

}
```


