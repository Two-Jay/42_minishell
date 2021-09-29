## dir 함수군

해당 포스트에서는 아래의 함수들에 대해서 다룬다.

```c
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

int chdir(const char *path_name);
DIR *opendir(const char *path_name);
struct dirent *readdir(DIR *dirp);
int closedir(DIR *dirp);
```

***

## chdir

```c
#include <unistd.h>

int chdir(const char *path_name);
```

현재 프로세스의 작업 디렉토리를 변경한다. 인자로 새로운 작업 디렉토리의 경로를 받는다. 성공시 0을 리턴하고, 실패시 -1을 리턴하며 errno을 설정한다.

### 예제 - chdir

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int fn_strerr(char *errm, size_t errm_len)
{
	write(2, errm, errm_len);
	exit(EXIT_FAILURE);
}

// 실행하면 현재 dir을 출력하고
// 환경 변수 HOME을 출력하며 현재 디렉토리를 HOME으로 바꾸어준다.
int main(void)
{
	char *currentdir;
	char *homedir;

	currentdir = getcwd(NULL, 0);
	if (!currentdir)
		fn_strerr("Error : malloc failed\n", 23);
	printf("current directory : %s\n", currentdir);
	homedir = getenv("HOME");
	if (chdir(homedir) == -1)
		fn_strerr("Error : chdir failed\n", 22);
	else
	{
		free(currentdir);
		currentdir = getcwd(NULL, 0);
		printf("changed directory : %s\n", currentdir);
	}
	free(currentdir);
	return (0);
}
```

***

## opendir

```c
#include <dirent.h>

DIR *opendir(const char *path_name);
```

인자로 넘겨준 path_name을 경로로 하는 디렉토리를 열어서, 프로그램 내에서 해당 디렉토리를 검색한다. 이는 path_name에 해당하는 디렉토리 스트림을 열어서, 디렉토리 스트림에 대한 포인터를 반환하는 것을 의미한다.

성공시 디렉토리 정보 구조체인 DIR 포인터를 반환하고, 실패하면 NULL을 반환한다. 

### struct DIR

디렉토리 정보 읽기에 사용되는 구조체이다. 실제로는 아래와 같이 구성되어 있지만, 라이브러리 함수들의 내부 동작을 위해 참조하는 것으로, 직접 참조할 일은 많지 않다. 반환된 DIR 포인터를 이용해서, readdir()과 closedir()을 사용하는 게 핵심이다.

```c
typedef struct
{
	struct _finddata_t	dd_dta; /* disk transfer area for this dir */
	struct dirent		dd_dir;
	intptr_t		    dd_handle;  /* _findnext handle */

	/*
	 * Status of search:
	 *   0 = not started yet (next entry to read is first entry)
	 *  -1 = off the end
	 *   positive = 0 based index of next entry
	 */
	int			        dd_stat;
	char			    dd_name[1];
}       DIR;
```

***

## closedir

```c
#include <sys/types.h>
#include <dirent.h>

int closedir(DIR *dirp);
```

매개변수로 넣은 DIR 포인터를 이용하여 열려있는 디렉토리 스트림을 닫는다. 디렉토리 스트림을 닫을 때, 디렉토리 스트림과 연관되어 있는 fd 또한 닫는다. closedir()을 호출하면 디렉토리 스트림 지정자에 대해서 동일한 경로를 매개변수로 opendir()을 불러오기 전에는 다시 사용할 수 없다.

성공시 0을 리턴하며, 실패시 -1을 리턴하고 errno을 설정한다.

***

## readdir

```c
#include <dirent.h>

struct dirent *readdir(DIR *dirp);
```

매개변수로 넣은 DIR 포인터에서 지정하는 디렉토리 스트림의 다음 디렉토리 엔트리를 불러온다. 디렉토리 엔트리는 struct dirent 구조체의 형식으로 가져온다. 반환된 dirent 구조체 포인터는 해당 디렉토리 스트림의 가장 첫번째 파일을 가리키고 있다. 디렉토리 엔트리의 정보를 이용해서 각 디렉토리의 파일과 폴더의 정보를 읽고 컨트롤할 수 있다.

성공하면 dirent 구조체의 포인터를 리턴하며, 디렉토리 스트림에서 더 이상 읽어올 디렉토리 엔트리 정보가 없는 경우 NULL을 리턴한다. 이 경우 errno는 설정하지 않는다.

### dirent 구조체

dirent 구조체의 상세는 아래와 같다. 디렉토리 파일은 디렉토리에 속하는 파일들의 이름과 inode 번호로 구성되어 있고, 이를 트리 구조로 활용하고 있다.

readdir()을 이용해서 받아오는 디렉토리 엔트리에는 삭제된 파일들의 정보도 담겨져 있다. 이는 inode가 0인지 아닌지 판단하면 되는데, 만약 dirent->d_ino 의 값이 0이라면 삭제된 파일로 간주하고 처리하면 된다.

```c
struct dirent
{
	long	d_ino;	// inode 번호
	off_t	d_off;	// offset, 현재 디렉토리 DIR 스트림 내에서의 위치를 의미
	unsigned short	d_reclen;	// d_name 길이
	char d_name[NAME_MAX + 1];	// 파일 이름
}
```

### 예제 - opendir, readdir, closedir

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

// 실행하면 현재 dir을 출력하고
// 현재 dir 스트림을 연 다음에
// readdir 을 이용해서 현재 디렉토리에 있는 파일 이름을 하나씩 전개한다.
int main(void)
{
	char			*currentdir;
	DIR				*dirstr;
	struct dirent	*dir_entry;

	currentdir = getcwd(NULL, 0);
	if (!currentdir)
		fn_strerr("Error : malloc failed\n", 23);
	dirstr = opendir(currentdir);
	if (dirstr != NULL)
	{
		dir_entry = readdir(dirstr);
		while(dir_entry != NULL)
		{
			printf("%s\n", dir_entry->d_name);
			dir_entry = readdir(dirstr);
		}
		closedir(dirstr);
	}
	free(currentdir);
	return (0);
}
```
