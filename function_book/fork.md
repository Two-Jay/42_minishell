## fork

```c
#include <unistd.h>

pid_t fork(void);
```

새로운 프로세스를 생성한다. fork 함수로 새로이 생성한 프로세스를 '자식 프로세스'로, fork 함수를 호출한 프로세스는 '부모 프로세스'로 칭한다. fork를 부모 프로세스에서 호출하면 자식 프로세스가 생성되면서, 메모리 공간은 부모 프로세스의 메모리 공간을 그대로 복사하여 (to be duplicated) 생성된다. 생성한 프로세스와 부모 프로세스는 동시에 동작하는데, 이 때 어느 프로세스가 동작하는 지 순서는 보장되지 않으며 운영체제의 스케쥴링에 따라 동작된다.

자식 프로세스는 프로세스가 생성되어서 동작하는 것이기에 부모의 pid가 아닌 자신만의 pid를 갖는다. 동시에, 해당 자식 프로세스를 fork 함수로 생성하면, 그 자식 프로세스의 부모 프로세스, 즉 fork를 호출한 프로세스의 pid 값이 자식 프로세스에게 'PPID'로 전달된다. 자식 프로세스는 PPID로 부모 프로세스가 무엇인지 알 수 있다.

fork 함수는 따로 인자를 받지 않는다. 성공시 부모 프로세스는 자식 프로세스의 pid를, 자식 프로세스에서는 0을 리턴한다. 실패하면 -1을 리턴한다.

### 예제
```c
#include <unistd.h>
#include <stdio.h> //printf
#include <stdlib.h> //exit
#include <sys/types.h> //for definition of pid_t

int main(void)
{
	pid_t pid;

	// 이런 식으로 fork를 실행하면, 해당 pid가 -1, 0, 0 < pid 인지 체크해서
	// 각 프로세스 별로 어떻게 동작할 지 구성할 수 있다.
	pid = fork();
	if (pid == -1)
	{
		// 에러, fork() 실패
		printf("error!");
		exit(1);
		return (0);
	}
	else if (pid == 0)
	{
		// 자식 프로세스에서는 fork() 가 0을 리턴한다.
		// 즉 이 부분은 자식 프로세스에서 실행되는 영역이다.
		printf("Child : My pid is %d, and i'm a child of %d\n",
			(int)getpid(),
			(int)getppid());
	}
	else
	{
		// pid 가 임의의 양수 (fork()로 생성된 자식 프로세스의 pid)라면
		// fork()를 성공적으로 호출한 부모 프로세스에 이 부분이 실행된다.
		printf("Parent : My pid is %d, and i'm a child of %d\n and My child is %d\n",
			(int)getpid(),
			(int)getppid(),
			(int)pid);
	}
	printf("process end\n");
	return (0);
}
```