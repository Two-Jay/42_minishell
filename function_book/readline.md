## readline

```c
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

char *readline(const char *prompt);
```

readline은 터미널에서 라인을 읽어와서 이를 리턴한다. 만약 매개변수 prompt에 아무런 변수도 넣어주지 않으면, 프롬프트에 아무런 내용도 띄우지 않고 입력을 받는다. 그러지 않을 경우, 프롬포트에 매개변수로 넣어준 문자열을 프롬프트에 출력하고 난 후에 출력을 받는다. 성공시 읽어온 라인을 리턴한다.

### 예제

```c
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

// 컴파일을 할 시에 -lreadline 을 붙여야 한다.
// GNU readline : 명령줄 인터페이스의 편집 및 입력, 기록, 저장을 위한 라이브러리

int main(void)
{
	char *str;

	while (1)
	{
		// readline은 입력받은 문자열을 \n을 포함하여 반환한다. 빈 문자열 입력시 \n을 반환함.
		str = readline(NULL);
		if (str)
			printf("%s\n", str);
		else
			break ;
		// readline 을 실행하여 리턴되는 라인은 malloc을 이용하여 메모리가 할당된 상태로 리턴된다.
		// 누수를 방지하기 위해, free를 해주어야 한다.
		free(str);
	}
	return (system("leaks a"));
}
```

## rl_replace_line, rl_on_new_line, rl_redisplay

int	rl_on_new_line(void);
new_line을 업데이트 한 이후, 빈 라인으로 이동했다는 루틴을 알려준다.

int rl_redisplay(void);
현재 스크린에 띄워진 것을 rl_line_buffer에 있는 내용으로 바꾼다.

void rl_replace_line(const char *text, int clear_undo);
rl_line_buffer의 내용을 text로 바꾼다. 매개변수로 넣은 포인터는 가능한 한 보존된다.
clear_undo 가 트루값이면 undo list를 다 비워준다.
