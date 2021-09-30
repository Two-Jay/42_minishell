## strerror

```c
#include <string.h>

char *strerror(int errno);
```

errno에 해당하는 오류 메세지 문자열을 가리키는 포인터를 얻어온다. 이 때 리턴되는 포인터는 문자열 리터럴로 정의되어 있어 변경이 불가하다.


## errno

```c
// in <errno.h>
__BEGIN_DECLS
extern int * __error(void);
#define errno (*__error())
__END_DECLS
```

 errno는 errno.h에 광역변수로 정의되어 있는 상수이다. 함수 수행 중 에러가 발생하는 경우 errno에 에러코드가 할당되며, 함수 실행 중 에러없이 실행했다면 0의 값을 가지게 된다.


### 예제

현재 디렉토리에서 인자로 받은 파일명이 있는지 열어보고, 없으면 표준에러출력으로 띄워주는 프로그램을 작성해보았다.

```c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

char	*get_targetpath(const char *file_name)
{
	char	*current_dir;
	char	*ret;
	size_t	cdir_l;
	size_t	fn_l;
	int		ix;

	if (!file_name)
		return (NULL);
	current_dir = getcwd(NULL, 0);
	cdir_l = strlen(current_dir);
	fn_l = strlen(file_name);
	ret = (char *)malloc(sizeof(char) * ((int)cdir_l + (int)fn_l + 2));
	ix = 0;
	while (ix < cdir_l)
		ret[ix++] = *current_dir++;
	ret[ix] = '/';
	ix = 0;
	while (ix < fn_l)
		ret[cdir_l + ix++ + 1] = *file_name++;
	ret[cdir_l + ix + 1] = '\0';
	printf("check : %s\n", ret);
	free(current_dir - cdir_l);
	return (ret);
}

int main(int argc, char *argv[])
{
	char	*target_file;
	int		fd;

	target_file = get_targetpath(argv[1]);
	fd = open(target_file, O_WRONLY, 0);
	if (fd == -1)
	{
		printf("Error : %s\n", strerror(errno));
		return (0);
	}
	printf("the file exists :) \n");
	close(fd);
	free(target_file);
	return (0);
}

```