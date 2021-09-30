## fd 관련 함수군

해당 포스트에서는 아래의 함수들에 대해서 다룬다.

아래의 함수군은 모두 system call 함수이다.

```c
#include <fcntl.h> // open
#include <unistd.h> // close, read, write

int open(const char *file_name, int flag, mode_t mode);
int read(int fd, void *buf, size_t buf_size);
int write(int fd, char *buf, size_t buf_size);
int close(int fd);
```

## open

```c
#include <fcntl.h>

int open(const char *file_name, int flag, mode_t mode);
```

이미 존재하는 파일을 여는 함수. 옵션에 따라 존재하지 않는 파일을 생성할 수 있거나 권한을 부여할 수도 있다. open()로 열려진 파일은 fd로 OS의 file table에 할당 & 등록된다. 이 때 등록한 fd는 read, write, close 등을 이용하여 활용할 수 있다.

인자로는 파일을 열어서 fd에 등록할 대상 파일의 절대경로 혹은 상대경로를 받는다. flag는 파일을 어떤 목적으로 열 것인지 옵션들을 제공한다. 아래의 상수들을 bit 혹은 or 연산을 통해 여러개 지정할 수 있다. open()을 호출할 시 아래 옵션값 중에서 O_RDONLY, O_WRONLY, O_RDWR 중 하나는 반드시 설정하여야 한다.

mode_t 에서는 파일의 접근 권한을 설정한다.

성공시 파일이 열리고 fd가 할당되는데, 이 fd를 리턴한다. 실패시 -1을 리턴하고, errno를 설정한다.

### open flag

```text
	O_RDONLY		읽기전용으로 파일을 염
	O_WRONLY		쓰기전용으로 파일을 염
	O_RDWR			읽기 쓰기 모두 가능한 상태로 염

	O_NONBLOCK      사용 가능한 시점까지 함수의 동작을 블록시키지 않음
	O_APPEND        해당 옵션으로 열고 write를 하는 경우 끝에서 내용이 덧붙여지도록 함 (중간 내용 수정 x)
	O_CREAT         파일이 없을 시 파일 생성
	O_TRUNC         사이즈 0으로 수정
	O_EXCL          O_CREAT 옵션과 함께 사용하는 경우, 경로로 지정한 파일이 존재할 시 에러로 반환
	O_SHLOCK        atomically obtain a shared lock
	O_EXLOCK        atomically obtain an exclusive lock
	O_NOFOLLOW      경로로 지정한 파일이 심볼릭 링크일 경우 에러로 반환
	O_SYMLINK       심볼릭 링크일 경우에도 open 허용
	O_EVTONLY       descriptor requested for event notifications only
	O_CLOEXEC       mark as close-on-exec
	O_NOFOLLOW_ANY  do not follow symlinks in the entire path.
```

## read

```c
#include <unistd.h>

int read(int fd, void *buf, size_t buf_size);
```

지정한 fd에서 데이터를 읽어온다. 읽어온 데이터는 두번째 인자인 buf 포인터에 저장되며, 한 번 실행시 최대 buf_size 값만큼의 바이트를 읽어온다. 

성공시 읽어온 바이트를 반환한다. 만약 파일을 읽었으나 read_ptr이 EOF에 도달했거나 읽어올 내용이 없다면 0을 반환한다. 이외의 에러일 경우에는 -1을 리턴하고, errno를 설정한다.


## write

```c
#include <unistd.h>

int write(int fd, char *buf, size_t buf_size);
```

지정한 fd에 대해 buf에 있는 문자열을 buf_size 만큼 쓴다. 해당 함수는 파일 뿐만 아니라 표준 입출력에서도 동작한다.

성공시 기록한 바이트 수만큼의 int 값을 리턴한다. 실패시 -1을 리턴하고, errno를 설정한다.


## close

```c
#include <unistd.h>

int close(int fd);
```

open으로 열었던 fd를 닫고 파일테이블 상에서 할당한 해당 fd를 정리하여준다.

***

### 예제

현재 디렉토리 경로에 있는 파일에 대해 실행파일 이름과 함께 입력하면, txt 파일인지 체크한 뒤 이를 표준출력으로 출력하는 프로그램을 만들어 보았다.

```c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define BUFF_SIZE 4096

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
	free(current_dir - cdir_l);
	return (ret);
}

int ft_strequel(char *s1, char *s2)
{
	int ix;

	ix = 0;
	while (s1[ix] && s2[ix])
	{
		if (s1[ix] != s2[ix])
			return (0);
		ix++;
	}
	return (1);
}

int is_txtfile(char *file_name)
{
	int		ix;
	size_t	fn_l;

	fn_l = strlen(file_name);
	ix = fn_l - 4;
	if (!ft_strequel(file_name + ix, ".txt"))
		return (0);
	return (1);
}

int read_data(int fd, char *buffer, int buf_size)
{
	int size;
	int len;

	size = 0;
	while (1)
	{
		len = read(fd, &buffer[size], buf_size - size);
		if (len > 0)
		{
			size += len;
			if (size == buf_size)
				return (size);
		}
		else if (len == 0)
			return (size);
		else
			return (-1);
	}
}

int cat_txtfile(int fd)
{
	char	buf[BUFF_SIZE];
	int check;

	while (1)
	{
		check = read_data(fd, buf, BUFF_SIZE);
		if (check == -1)
		{
			printf("Error : read error - %s\n", strerror(errno));
			return (1);
		}
		else if (check == 0)
			return (0);
		else
			write(1, buf, check);
	}
}

int main(int argc, char *argv[])
{
	char	*target_file;
	int		fd;

	target_file = get_targetpath(argv[1]);
	fd = open(target_file, O_RDONLY, 0);
	if (fd == -1)
	{
		printf("Error : %s\n", strerror(errno));
		exit(errno);
	}
	if (!is_txtfile(argv[1]))
	{
		printf("Error : this is not txt file.\n");
		exit(errno);
	}
	cat_txtfile(fd);
	close(fd);
	free(target_file);
	return (0);
}
```