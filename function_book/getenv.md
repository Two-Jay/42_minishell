## getenv

```c
#include <stdlib.h>
char *getenv(const char *varname);
```

getenv() 함수는 varname에 해당한 항목에 대한 환경변수의 리스트를 검색합니다. 성공시 varname의 값을 포함하여 문자열 포인터를 리턴합니다. 찾을 수 없는 경우에는 null이 리턴되며, errno가 설정됩니다.


```
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    char *pathvar, usrvar, shellvar;

    pathvar = getenv("PATH");
    usrvar = getenv("USER");
    shellvar = getenv("SHELL");
    return (0);
}
```

c 프로그램에서는 environ 이라는 전역 변수가 미리 만들어져 있으며, 이를 통해 환경 변수 목록을 확인할 수 있습니다. 다른 곳에 미리 선언되어 있는 상태이니 extern으로 environ을 참조하면 환경 변수 목록을 확인할 수 있다.
혹은 main에서 argv 와 함께 envp를 선언해도 참조가 가능하다.


```
#include <stdlib.h>
#include <stdio.h>

extern char **environ

int main(void)
{
    int ix;

    ix = 0;
    while (environ[ix])
        printf("%s\n", environ[ix++]);
    return (0);
}
```

