## getcwd

```c
#include <unistd.h>
char *getcwd(char *buffer, int maxlen);
```

현재 디렉토리를 문자열로 리턴한다. 첫번째 인자로는 저장할 버퍼를 받고, 두 번째 인자로는 버퍼의 길이를 받는다. 인자로 널을 준다면, malloc을 이용하여 내부에서 할당한 다음 반환값을 넘겨준다. 

내부적으로 malloc을 이용하여 새로운 버퍼를 할당받은 뒤에 작동하기 때문에, 넘겨준 리턴값에 대해 free를 해야한다.

### 예제
```c
// 아래는 배쉬의 'pwd' 커멘드를 간단하게 구현하여 본 것이다.
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int get_pwd()
{
	char *cwd;
	cwd = getcwd(NULL, 0);
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

int ft_strequel(char *s1, char *s2)
{
	int ix;

	ix = 0;
	while (s1[ix] && s2[ix])
	{
		if (s1[ix] != s2[ix])
			return (1);
		ix++;
	}
	return (0);
}

int main(void)
{
	char *str;

	while (1)
	{
		str = readline(NULL);
		if (!ft_strequel(str, "pwd"))
			get_pwd();
		else
			printf("%s\n", str);
        add_history(str);
		free(str);
	}
	return (system("leaks a"));
}
```
