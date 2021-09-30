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


## read

```c
#include <unistd.h>

int read(int fd, void *buf, size_t buf_size);
```


## write

```c
#include <unistd.h>

int write(int fd, char *buf, size_t buf_size);
```


## close

```c
#include <unistd.h>

int close(int fd);
```


