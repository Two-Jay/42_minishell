## execve

```c
#include <unistd.h>

int execve(const char *file_name, const char **argv, const char **envp);
```

filename이 가리키는 파일을 실행한다. 이 때, 파일은 실행 가능한 파일, 즉 바이너리 파일이거나 스크립트 파일이어야 한다. argv와 envpp는 포인터 배열로 filename을 실행할 때에 인자로 실행된다.

execve()로 프로그램을 실행한다는 것은 filename으로 지정된 파일의 소스코드를 들고와서, 현재 프로세스에 올려놓은 뒤 이를 실행하는 것을 말한다. 따라서 execve()의 호출 이후 현재 실행되고 있는 프로세스의 코드 (프로그램)은 없어지고, filename으로 지정된 파일의 소스코드를 메모리에 적재하여 처음부터 실행하게 된다. 이에 기존 프로그램에서 execve() 호출 이후 별도의 로직이 있다면, 실행되지 않은 채로 없어지니 주의할 것.

매개변수로 넣어주는 argv, envp는 꼭 넣어줄 때 마지막 엘리멘트가 NULL이어야 한다. envp를 따로 지정하는 대신, 이미 설정된 환경변수를 적용하여 사용하려면 environ 전역변수를 그냥 사용하면 된다.

file_name의 경우 execve를 호출하는 프로세스가 path가 설정되어 있는 디렉토리에서 실행중이어도, 절대경로나 상대경로로 정확한 위치를 지정해주어야 한다.

execve() 호출 성공시 대상 프로그램 자체가 실행되기에 성공시 리턴값은 존재하지 않는다. 실패시 -1이 리턴되며, 오류 내용이 전역변수 errno에 설정된다.

### 예제

```c
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
extern char **environ; 

int main(int argc, char *argv[])
{
	char **new_argv;
	char *command = "ls";
	int idx;
	new_argv = (char **)malloc(sizeof(char *) * (argc + 1));
	/* 명령어를 ls로 변경 */
	new_argv[0] = command;
	/* command line으로 넘어온 parameter를 그대로 사용 */
	for(idx = 1; idx < argc; idx++) {
		new_argv[idx] = argv[idx];
	}
	/* argc를 execve 파라미터에 전달할 수 없기 때문에 NULL이 파라미터의 끝을 의미함 */
	new_argv[argc] = NULL;
	if (execve("/usr/bin/ls", new_argv, environ) == -1)
	{
		fprintf(stderr, "프로그램 실행 error: %s\n", strerror(errno));
		return 1;
	}
	/* ls 명령어 binary로 실행로직이 교체되었으므로 이후의 로직은 절대 실행되지 않습니다. */
	printf("이곳이 이제 ls 명령어라 이 라인은 출력이 되지 않습니다.\n");
	return 0;
}

// 출처: https://www.it-note.kr/157 [IT 개발자 Note]
```