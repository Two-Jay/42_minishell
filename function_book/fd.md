## fd 함수군

해당 포스트에서는 아래의 함수들에 대해서 다룬다.

```c
#include <fcntl.h> // open
#include <unistd.h> // close

int open(const char *file_name, int flag, mode_t mode);
int close(int fd);
```