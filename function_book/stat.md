## stat 함수군

해당 포스트에서는 아래의 함수들에 대해서 다룹니다.

```c
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int stat(const char *file_path, struct stat *statbuf);
int fstat(int fd, struct stat *statbuf);
int lstat(const char *file_path, struct stat *statbuf);
```

stat 함수군은 공통적으로 지정한 파일의 정보가 담긴 stat 구조체를 가져오는 시스템 함수들로 이루어져 있다.

매개변수 file_name 에는 stat을 얻고자 하는 파일의 경로를, statbuf는 stat을 저장할 포인터를 인자로 넣는다. fstat의 fd는 stat을 얻고자 하는 파일의 파일 디스크립터를 넣으면 된다.

공통적으로 성공시 0을 리턴하고, 에러시 -1 리턴을 하며 errno를 설정한다.

***

### stat 구조체

```c
struct stat {
    dev_t st_dev;  // 디바이스 번호
    ino_t st_ino;  // inode 번호
    mode_t st_mode;  // 모드 (접근권한)
    nlink_t st_nlink;  // 하드링크 수
    uid_t st_uid;  // 소유자의 사용자 아이디
    gid_t st_gid;  // 소유자의 그룹 아이디
    dev_t st_rdev;  // 디바이스 아이디 (특수 파일인 경우)
    off_t st_size;  // 파일 크기(바이트)
    blksize_t st_blksize;  // 블록 크기
    blkcnt_t st_blocks;  // 512바이트 블록 갯수
    time_t st_atime;  // 최종 접근 시간 (access time)
    time_t st_mtime;  // 최종 수정 시간 (modification time)
    time_t st_ctime;  // 최종 상태 변경 시간 (change time)
};
```

stat 구조체 중 st_mode가 가장 주목할 부분이다. 이 부분에서의 mode_t 변수의 값을 통해서 이 파일이 어떤 파일이며, 권한 설정은 어떻게 되어있는지 알 수 있다.