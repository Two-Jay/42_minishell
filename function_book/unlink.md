## unlink

```c
#include <unistd.h>

int unlink(const char *file_name);
```

unlink()는 현재 작업 중인 디렉토리에서 매개변수로 지정한 파일의 연결 계수를 1 감소시키는 함수이다. 해당 함수를 호출하면, 해당 디렉토리에 dirent 구조체의 d_inode 값이 1만큼 줄어들게 된다. dirent->d_inode 값이 0이 되었을 때, 파일을 삭제한다. 

만약 d_inode의 값이 1인 임의의 파일을 특정 프로세스에서 사용 중이고, 이 파일의 경로를 인자로 넣어 unlink 함수를 호출한다고 해도 dirent->d_inode 는 0이 되어서 삭제가 되어야하지만 바로 삭제되지는 않는다. 이런 경우 unlink 함수를 호출하는 시점에서 바로 삭제하는 대신, 해당 파일에 접근하고 있는 작업이 모두 완료하고 난 뒤 연결 계수가 0으로 바뀌는 시점에 삭제된다.

### 예제

파일 이름 하나를 인자로 받아 현재 디렉토리에 대해 인자로 받은 파일 이름이 실제로 존재하는 지 확인한 후 이를 삭제하는 프로그램을 만들어보았다.
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

int ft_strequel(const char *s1, const char *s2)
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

int fn_strerr(char *errm, size_t errm_len)
{
	write(2, errm, errm_len);
	exit(EXIT_FAILURE);
}

// 매개변수로 받은 파일이 실제로 현재 작업하는 디렉토리 내에 있는지 검색하는 함수
// readdir 로 dirent 구조체를 받아올 때 더 이상 받아올 파일 정보가 없다면 NULL을 반환하기에 탈출 조건으로 성립
// dirent->d_name, 즉 읽어온 파일 정보 구조체의 파일 이름 정보가 매개변수랑 동일하는 지를 체크 
int fn_search_file(const char *file_name, DIR *dirp)
{
	struct dirent		*direntp;

	direntp = readdir(dirp);
	while (direntp != NULL && ft_strequel(direntp->d_name, file_name))
		direntp = readdir(dirp);
	if (direntp == NULL)
		return (1);
	return (0);
}

int is_directory(mode_t st_mode)
{
	return (((st_mode) & S_IFMT) == S_IFDIR);
}

int main(int argc, char **argv)
{
	char		*current_dir;
	struct stat	statbuf;
	DIR			*dirp;

	// 인자 갯수가 2가 아니라면 에러
	if (argc != 2)
		fn_strerr("insert a file_name you wanna delete\n", 37);

	// 현재 경로를 받아온 뒤에 opendir로 디렉토리 스트림을 열어준다.
	current_dir = getcwd(NULL, 0);
	dirp = opendir(current_dir);

	// - 해당 경로의 파일 유형이 디렉토리라면 에러
	if (fn_search_file(argv[1], dirp))
		fn_strerr("Error : no file\n", 17);
	// - 만약 stat 함수의 동작이 실패한다면 에러
	if (lstat(argv[1], &statbuf) == -1)
		fn_strerr("Error : unknown file\n", 22);
	// - 만약 존재하지 않는 파일이면 에러
	if (is_directory(statbuf.st_mode))
		fn_strerr("Error : this is directory\n", 27);

	// 에러처리 이후 실제로 파일을 unlink 해준다.
	// 여기서 해당 파일의 dirent->d_inode 값이 0이 된다면 파일이 삭제된다.
	unlink(argv[1]);
	printf("file : %s was deleted\n", argv[1]);

	// 디렉토리 스트림을 닫아주고, getcwd로 불러와서 힙에 저장한 경로 문자열을 free 해준다.
	closedir(dirp);
	free(current_dir);
	return (0);
}
```