
## wait, waitpid, wait3, wait4

```c
#include <sys/wait.h>
#include <sys/types.h>

pid_t	wait(int *statloc);
pid_t	waitpid(pid_t pid, int *statloc, int options);
pid_t	wait3(int *staloc, int options, struct rusage *rus);
pid_t	wait4(pid_t pid, int *statloc, int options, struct rusage *rus);
```

wait 함수 군은 프로세스 동기화를 위해 임의의 혹은 특정 프로세스의 종료를 대기하거나 종료 상태를 확인하는 기능을 제공한다.


### wait

```c
pid_t wait(int *statloc)
```

wait()는 함수를 호출한 현재 프로세스에서 자식 프로세스가 있다면, 자식 프로세스의 종료 시점까지 부모 프로세스를 기다리게 한다. 자식 프로세스의 종료 상태는 함수의 인자로 넣어준 int *staloc 주소값에 저장된다. 

만약 부모 프로세스가 wait()를 호출하기 전에 자식 프로세스가 이미 종료되어있는 상태라면, wait()는 부모 프로세스의 대기시간 없이 즉시 리턴을 한다. 또한, 만약 wait()를 호출한 부모 프로세스가 여러 개의 자식 프로세스를 가지고 있다면, 이들 중 어떤 자식 프로세스라도 종료하면 리턴한다.

성공시 종료된 자식 프로세스의 pid를 리턴한다. -1을 리턴한다면, 현재 프로세스가 가진 자식 프로세스가 하나도 없다는 의미이다.


### waitpid

```c
pid_t	waitpid(pid_t pid, int *statloc, int options);
```

wait()가 종료된 아무 자식 프로세스나 리턴을 한다면, waitpid()는 인자 pid_t pid에 넣어준 프로세스의 종료를 대기한다. wait()와 마찬가지로 int *staloc에 종료 상택값을 저장하며, int options 에 들어간 조건에 따라 리턴한다.

pid_t pid 인자에 들어간 수에 따라 작동로직이 달라지는데, 이는 아래와 같다.

```
if (pid < -1)
	이 경우에는 pid의 절대값과 같은 프로세스 그룹 ID에 속한 자식 프로세스들을 대상으로 임의의 프로세스의 상태값을 요청한다.
if (pid == -1)
	wait() 함수와 동일한 동작을 한다. 임의의 자식 프로세스의 상태값을 요청한다.
if (pid == 0)
	함수를 호출한 프로세스와 같은 프로세스 그룹이 속한 프로세스들을 대상으로 임의의 프로세스의 상태값을 요청한다.
if (pid > 0)
	지정한 pid에 해당하는 프로세스의 상태값을 요청한다.
```

### wait3, wait4

```c
pid_t	wait3(int *staloc, int options, struct rusage *rus);
pid_t	wait4(pid_t pid, int *statloc, int options, struct rusage *rus);
```

자식 프로세스의 종료상태를 기다리며, 종료된 프로세스의 상태와 자원 사용량을 알려주는 rusage 객체를 업데이트 합니다. 성공시 wait 함수군의 다른 함수와 마찬가지로 종료된 자식 프로세스 ID, 실패시 -1을 리턴한다.

### rusage 구조체

rusage 구조체는 프로세스가 사용 중인 리소스에 대한 정보를 담고 있는 구조체이다.

```c
struct rusage {
        struct timeval ru_utime; /* 사용된 유저 시간 */
        struct timeval ru_stime; /* 사용된 시스템 시간 */
        long ru_maxrss;          /* 최대 상주 세트의 사이즈 */
        long ru_ixrss;           /* 공유 테키스트메모리총사이즈 */
        long ru_idrss;           /* 비공유 데이터총사이즈 */
        long ru_isrss;           /* 비공유 스택총사이즈 */
        long ru_minflt;          /* 페이지 재생수 */
        long ru_majflt;          /* 페이지 폴트 */
        long ru_nswap;           /* 스왑 */
        long ru_inblock;         /* 블록 입력 조작 */
        long ru_oublock;         /* 블록 출력 조작 */
        long ru_msgsnd;          /* 송신이 끝난 메세지 */
        long ru_msgrcv;          /* 수신이 끝난 메세지 */
        long ru_nsignals;        /* 수신이 끝난 시그널 */
        long ru_nvcsw;           /* 자발적인 콘텍스트 스위칭 */
        long ru_nivcsw;          /* 비자발적인 콘텍스트 스위칭 */
};
// man getrusage 참고
```

### statloc 구조

wait 함수군에서 자식프로세스의 종료 상태를 담아주는 statloc 은 16비트로 이루어진 정수값을 담고있다. 그 값은 자식 프로세스가 어떠한 방식으로 종료되었는지 상태에 따라 다른 구성을 가지게 된다.

```
	- 자식 프로세스가 exit() 호출시, 첫 8비트에는 exit()에 넣어준 인자가 들어오고, 이후 8비트는 0x00 으로 마스킹된다.
	- 자식 프로세스가 시그널에 의해서 종료되었다면, 첫 8비트는 0x00 으로 마스킹되고, 이후 1비트는 core 파일이 생성되었는지 알려주는 core flag 값이 들어오며, 나머지 7비트는 종료시킨 시그널의 signo가 들어온다.
	- 자식 프로세스가 SIGSTP, SIGSTOP 등에 의해 잠시 중단된 상태라면, 첫 8비트에 시그널 넘버가 저장되고, 이후 8비트는 0x7f가 마스킹된다.
```

또한 리눅스 시스템환경에서는 statloc을 이용하여 종료상태와 관련된 매크로 함수를 제공하는데, 이는 아래와 같다.

```
	- WIFEXITED(status) : 정상 종료일 때 참 반환
	- WEXITSTATUS(status) : 정상 종료일 때 하위 8비트 값 반환
	- WIFSIGNALED(status) : 시그널에 의해 종료되었을 시 참 반환
	- WTERMSIG(status) : 시그널에 의해 종료되었을 시 signo 반환
	- WCOREDUMP(status) : 코어 파일 발생 여부
	- WIFSTOPPED(status) : 일시 중단일 시 참 반환
	- WSTOPSIG(status) : 일시 중단시킨 signo 반환
```

### Options

아래의 키워드로 원하는 옵션을 설정할 수 있으며, '||' 로 2가지 이상의 옵션을 설정할 수 있다.

```
	- WCONTINUED : 중지되었다가 실행을 재개한 이후, 상태가 아직 보고되지 않은 자식 프로세스도 리턴함
	- WNOHANG : 종료 상태를 즉시 회수할 수 없는 상황이라면, 대기하지 않고 즉시 0을 리턴함
	- WUNTRACED : 중지되었으나 그 상태가 아직 보고되지 않은 자식도 리턴함
```







### 예제
```c
// 자식 프로세스를 생성하여, 자식프로세스에서 매개변수가 음의 정수인지 양의 정수인지 판별 후
// 양의 정수이면 자식 프로세스에서 해당 매개변수의 피보나치 수를 구하고,
// 부모 프로세스에서 wait 한 뒤 종료상태 값을 받아오는 예제코드를 구현해 보았다. 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

unsigned long fibonacci(int n)
{
	if (n == 0 || n == 1)
		return (1);
	else
		return (fibonacci(n - 1) + fibonacci(n - 2));
}

int main(int argc, char *argv[])
{
	int		exit_code;
	int		value;
	pid_t	pid;

	// 이런 식으로 fork를 실행하면, 해당 pid가 -1, 0, 0 < pid 인지 체크해서
	// 각 프로세스 별로 어떻게 동작할 지 구성할 수 있다.
	if (argc != 2)
		return (0);
	value = atoi(argv[1]);
	if (value > 50)
		return (0);
	exit_code = 0;
	pid = fork();
	if (pid == -1)
	{
		// 에러, fork() 실패
		printf("error!");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		printf("Child : My pid is %d, and i'm a child of %d\n",
			(int)getpid(),
			(int)getppid());
		if (value > 0)
		{
			printf("Child : I told to ma parent that argv is bigger than 0\n");
			// fibonacci 함수에 4~50 정도 넣으면 무슨 일이 일어날까...?
			printf("Child : you wish %lu, right?\n", fibonacci(value));
			exit(EXIT_SUCCESS);
		}
		else if (value <= 0)
		{
			printf("Child : I told to ma parent that argv is not bigger than 0\n");
			exit(EXIT_FAILURE);
		}

	}
	else
	{
		printf("Parent : My pid is %d, and i'm a child of %d\n and My child is %d\n",
			(int)getpid(),
			(int)getppid(),
			(int)pid);
		waitpid(pid, &exit_code, 0);
		printf("child %d send me exit_code : %d\n", pid, exit_code);
		// 자식 프로세스가 종료 상태코드 1로 종료시 부모 프로세스의 waitpid에서 받아내는 종료상태값은 256이 될 것이다. 설명가능?
	}
	printf("process end\n");
	return (0);
}
```