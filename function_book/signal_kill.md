
## signal & kill

```c
#include <signal.h>

int kill(pid_t pid, int sig); 
void (*signal(int signum, void (*handler)(int)))(int);
```

signal은 UNIX, POSIX 호환 운영체제의 IPC에서 쓰이는 방법 중 하나이며, 프로세스에게 직접적으로 어떤 의미를 전달할 수 있는 신호체계이다. IPC (프로세스 간 통신)은 프로세스들 사이에서 서로 데이터를 주고받는 행위나 체계를 의미하는데, signal은 UNIX, POSIX 호환 운영체제와 Window 운영체제에서 통용되는 방법 중 하나이다.

여기에서는 POSIX 호환 운영체제를 중점으로 설명하며, Window 계열 OS의 경우 <signal.h> 에서 정의하는 기본적인 6종의 시그널 외에는 지원하지 않는다.

### kill

```c
#include <signal.h>

int kill(pid_t pid, int signum); // 성공시 0, 실패시 -1 리턴 
```

특정 프로세스 인식자(pid)에 등록되어 있는 프로세스에게 지정한 시그널 넘버(signum)를 보낸다. pid 유형에 따라 시그널을 보낼 프로세스 대상을 다르게 설정할 수 있다. 

성공시 0을 리턴하고, 실패시 -1을 리턴하며 errno를 설정한다.

사용자의 OS에 따라 보낼 수 있는 signo가 다른데, 이는 터미널에서 **kill -l** 을 입력하면 출력된다.


|pid      |대상               |
|:---------:|:------------------|
|양수|지정한 pid 에만 전송|
|0|함수를 호출하는 pid와 같은 그룹의 모든 프로세스에 전송|
|-1|함수를 호출하는 pid가 전송 가능한 권한을 가진 모든 프로세스에 전송|
|음수|음수인 pid를 절대값으로 바꾸고, 바꾸고 난 뒤의 pid와 같은 그룹에 있는 모든 프로세스에 전송|

***

### signal

```c
#include <signal.h>

void (*signal(int signum, void (*handler)(int)))(int);
```

현재 프로세스에서 signum이 들어왔을 때에 시그널 처리를 위해 동작할 시그널 핸들러를 지정한다. 

첫 번째 인자로 시스템에 설정된 시그널 넘버를, 두 번째 인자로 시그널이 발생할 시 동작할 핸들러 함수를 넣는다. signal 함수를 사용할 때의 2번째 매개변수를 통해 특정 시그널이 발생할 시 아래의 동작을 설정할 수 있다.

성공시 2번째 매개변수인 시그널 핸들러 함수를 리턴한다. 실패시 -1 리턴을 하고 errno를 설정한다.

|매개변수      |동작 내용               |
|:---------:|:------------------|
|SIG_DFL|기존 방법을 따른다. 이미 signal 함수를 통해 변경했다면, 원래 설정으로 초기화한다.|
|SIG_IGN|시그널을 무시한다.|
|함수 포인터|시그널이 발생할 시, 해당 함수를 호출하도록 한다.|

***

## 예제

대표적인 시그널 넘버인 SIGINT(인터럽트)에 대한 동작을 인터럽트 대신 시그널 넘버를 출력하는 핸들러 함수로 바꾸어 준 후, 자기자신에게 인터럽트를 반복해서 보내는 프로그램을 짜보았다. 일정 시간이 지나면 SIGINT에 대한 동작을 다시 원래대로 초기화해주고 종료할 수 있도록 설정했다.

```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

void print_signo(int signum)
{
	printf("Signal catched : %d\n", signum);
}

int main(int argc, char *argv[])
{
	int ix;
	pid_t pid;

	ix = 0;
	pid = getpid();
	signal(SIGINT, print_signo);
	while (++ix)
	{
		kill(pid, SIGINT);
		sleep(2);
		if (ix == 6)
		{
			printf("from now on, you can send interupt signal.\n");
			signal(SIGINT, SIG_DFL);
			while(1)
				pause();
		}
	}
	return (0);
}
```