
## wait, waitpid, wait3, wait4

```c
#include <sys/wait.h>
#include <sys/types.h>

pid_t	wait(int *staloc);
pid_t	waitpid(pid_t pid, int *staloc, int options);
pid_t	wait3(int *staloc, int options, struct rusage *rus);
pid_t	wait4(pid_t pid, int *staloc, int options, struct rusage *rus);
```

wait 함수 군은 프로세스 동기화를 위해 임의의 혹은 특정 프로세스의 종료를 대기하거나 종료 상태를 확인하는 기능을 제공한다.

### wait

```c
pid_t wait(int *staloc)
```

wait()는 함수를 호출한 현재 프로세스에서 자식 프로세스가 있다면, 자식 프로세스의 종료 시점까지 부모 프로세스를 기다리게 한다. 자식 프로세스의 종료 상태는 함수의 인자로 넣어준 int *staloc 주소값에 저장된다. 

만약 부모 프로세스가 wait()를 호출하기 전에 자식 프로세스가 이미 종료되어있는 상태라면, wait()는 부모 프로세스의 대기시간 없이 즉시 리턴을 한다. 또한, 만약 wait()를 호출한 부모 프로세스가 여러 개의 자식 프로세스를 가지고 있다면, 이들 중 어떤 자식 프로세스라도 종료하면 리턴한다.

성공시 종료된 자식 프로세스의 pid를 리턴한다. -1을 리턴한다면, 현재 프로세스가 가진 자식 프로세스가 하나도 없다는 의미이다.

### waitpid

```c
pid_t	waitpid(pid_t pid, int *staloc, int options);
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

