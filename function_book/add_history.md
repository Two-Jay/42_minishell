## add_history

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
void add_history(const char *string)

문자열로 받은 인풋을 히스토리 리스트에 추가한다. stifle_history()를 이용하여 정한 히스토리 엔트리의 최대값을 넘는 경우, 혹은 새로운 히스토리 엔트리가 최대값을 넣는 경우에는, 가장 오래된 히스토리가 사라지게 된다.

* add_history는 수정 중인 라인에 대해서는 히스토리에 올려놓지 않지만, 배쉬에서는 수정 중인 라인에 대해 히스토리에 등록한다.
이는 add_history를 이용하여 구현할 수는 없지만, fd 계열 함수를 이용해 임의로 구현이 가능하다.
(숨김파일에 쓰고, 하나씩 받아온다던가...)

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
		str = readline(NULL);
		if (str)
			printf("%s\n", str);
		else
			break ;
        // readline 으로 받은 라인을 히스토리에 추가한다.
        // 히스토리에 저장한 라인은 위-아래 방향키로 탐색할 수 있다.
        add_history(str);
		free(str);
	}
	return (system("leaks a"));
}
```
