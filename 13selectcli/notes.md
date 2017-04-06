# select
 `int select(int nfds, fd_set *readfds, fd_set *writefds,
                  fd_set *exceptfds, struct timeval *timeout);` 

* 1：读、写、异常集合fd的文件描述符的最大值+1
* 2：读集合
* 3：写集合
* 4：异常集合
* 5：超时结构体

## 集合操作
void FD_CLR(int fd, fd_set *set);

int  FD_ISSET(int fd, fd_set *set);

void FD_SET(int fd, fd_set *set);

void FD_ZERO(fd_set *set);
