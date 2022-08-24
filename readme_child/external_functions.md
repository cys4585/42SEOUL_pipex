# external functions

- open(2)
    - NAME
        - open and possibly create a file
    - SYNOPSIS
        
        ```c
        #include <fcntl.h>
        int open(const char *pathname, int flags);
        int open(const char *pathname, int flags, mode_t mode);
        ```
        
    - DESCRIPTION
        - `open()` system call(시스템 호출)은 `pathname`으로 지정된 파일을 연다. 지정된 파일이 존재하지 않는 경우, `open()`을 통해 선택적으로(`flags`에 `O_CREATE`가 지정된 경우) 생성할 수 있다.
        - `open()`의 반환값은 file descriptor(파일 설명자)이며, 프로세스의 열린 file descriptors 테이블에 있는 항목(entry)에 대한 색인(index)인 음수가 아닌 작은 정수이다. file descriptor는 차후에 열린 파일을 참조하기 위해 system calls(read(2), write(2), leaks(2), fcntl(2), etc.)에 사용된다. 성공적인 호출로 반환된 file descriptor는 프로세스에서 현재 열려있지 않은 가장 낮은 번호의 file descriptor가 될 것이다.
        - 기본적으로 새 file descriptor는 ‘execve(2)’에서 열린 상태로 유지되도록 설정된다(즉, fcntl(2)에 설명된 FD_CLOEXEC file descriptor 플래그가 처음에 비활성화된다). 아래 설명된 O_CLOEXEC 플래그를 사용하여 기본값을 변경할 수 있다. file offset(파일 오프셋)은 파일의 시작부분으로 설정된다(lseek(2) 참조).
        - `open()`을 호출하면 열린 파일의 시스템 전체 테이블에 있는 항목인 새로운 open file description(열린 파일 설명)이 생성된다. open file description은 file offset과 file status flags(파일 상태 플래그)를 기록한다(아래 참조). file descriptor는 open file description에 대한 참조이다.  이 참조는 `pathname`이 나중에 제거되거나 다른 파일을 참조하도록 수정되어도 영향을 받지 않는다. 더 나아가 open file description의 자세한 내용은 NOTES를 참고해라.
        - 매개변수 `flags`는 다음 액세스 모드 중 하나를 포함해야 한다: `O_RDONLY, O_WRONLY, O_RDWR)`. 이것들은 각각 파일을 읽기 전용, 쓰기 전용, 읽기/쓰기 모드로 열도록 요청한다.
        - 더해서, 0개 이상의 file creation flags와 file status flags는 플래그에서 비트 OR연산이 될 수 있다. file creation flags는 `O_CLOEXEC, O_CREAT, O_DIRECTORY, O_EXCL, O_NOCTY, O_NOFLOW, O_TMPFILE, O_TRUNC`이다. file status flags는 아래에 나열된 나머지 모든 플래그이다. 이 두 플래그 그룹의 차이(distinction)는 file creation flags는 열린 작업 자체의 의미에 영향을 미치는 반면, file status flags는 차후의 I/O 작업의 의미에 영향을 미친다는 것이다. file status flags는 검색되고 경우에 따라 수정될 수 있다. 자세한 내용은 ‘fcntl(2)’을 참조해라.
        - file creation flags와 file status flags의 전체 목록은 다음과 같다. (자세한 내용은 매뉴얼 페이지 참고)
            - `O_APPEND`
            - `O_ASYNC`
            - `O_CLOEXEC`
            - `O_CREAT`
            - `O_DIRECT`
            - `O_DIRECTORY`
            - `O_DSYNC`
            - `O_EXCL`
            - `O_LARGEFILE`
            - `O_NOATIME`
            - `O_NOCTTY`
            - `O_NOFOLLOW`
            - `O_NONBLOCK` or `O_NDELAY`
            - `O_PATH`
            - `O_SYNC`
            - `O_TMPFILE`
            - `O_TRUNC`
    - RETURN VALUE
        - On success, return the new file descriptor
        - On error, -1 is returned and `errno` is set to indicate(나타내다) the error. (자세한 내용은 매뉴얼 페이지 참고)
- close(2)
    - NAME
        - close a file descriptor
    - SYNOPSIS
        
        ```c
        #include <unistd.h>
        int close(int fd);
        ```
        
    - DESCRIPTION
        - `close()`는 더이상 어느 파일도 참조하지 않고 재사용될 수 있도록 file descriptor를 닫는다. 프로세스에 의해 소유되고 연결된 파일에 보관된 모든 레코드 잠금(fcntl(2) 참고)이 제거된다. (잠금을 가져오는데 사용된 file descriptor와 관계없이)
        - `fd`가 기본 open file description을 참조하는 마지막 file descriptor이면 open file description과 연관된 리소스가 해제되고, file descriptor가 unlink(2)를 사용하여 제거된 파일에 대한 마지막 참조였다면 파일이 삭제된다.
    - RETURN VALUE
        - returns zero on success.
        - On error, -1 is returned, and `errno` is set to indicate(나타내다) the error.
- read(2)
    - NAME
        - read from a file descriptor
    - SYNOPSIS
        
        ```c
        #include <unistd.h>
        ssize_t read(int fd, void *buf, size_t count);
        ```
        
    - DESCRIPTION
        - `read()` `buf`에서 시작하여  `fd` 부터 `count` bytes까지 `buf` 안에 읽기를 시도한다.
        - 검색을 지원하는 파일에서는, file offset에서 읽기 작업이 시작되고, file offset은 읽은 바이트 수만큼 증가된다. 만약 file offset이 파일의 끝에 있거나 파일 끝을 지났다면, 바이트가 읽히지 않고, `read()`는 0을 반환한다.
        - `count`가 0이면, `read()`가 아래에 설명된 에러를 감지할 수도 있다. 어떠한 오류도 없거나, `read()`가 에러를 체크하지 않는 경우, `count`가 0인 `read()` 0을 반환하며 다른 효과는 없다.
        - POSIX.1에 따르면, `count`가 `SSIZE_MAX`보다 크면, 결과는 구현에서 정의된다.
    - RETURN VALUE
        - On success, 읽은 바이트 수가 반환되고(0은 파일의 끝을 나타냄), file position은 이 숫자만큼 진행된다. 이 숫자가 요청된 바이트 수보다 작으면 에러가 아니다. 예를 들어, 당장 사용 가능한 바이트 수가 적기 때문에(파일의 끝에 가까운 경우, 또는 파이프로부터 읽거나 터미널에서 읽은 경우), 또는 signal에 의해 `read()`가 중단되었기 때문에 발생할 수 있다.
        - On error, -1 is returned, `errno`이 에러를 나타내도록 설정된다. 이 경우, file position이 변경되는지 여부는 지정되지 않은 채 남겨진다.
- write(2)
    - NAME For a seekable file writing takes place at the file offset, and the file offset is incremented by the number of bytes actually written.
        - write to a file descriptor
    - SYNOPSIS
        
        ```c
        #include <unistd.h>
        
        ssize_t write(int fd, const void *buf, size_t count);
        ```
        
    - DESCRIPTION
        - `write()`는 `buf`에서 시작하는 버퍼로부터 file descriptor `fd`에 의해 참조되는 파일에 `count` 바이트만큼 write한다.
        - 예를 들어, 기본(underlying) 물리적 미디어에 공간이 부족(insufficient)하거나, RLIMIT_FSIZE 리소스 제한이 있거나(setrlimit(2) 참조), 호출이 `count` 바이트보다 적은 바이트를 쓴 후 신호 처리기(signal handler)에 의해 중단(interrupt)되었을 경우, 바이트 수는 `count`보다 적을 수 있다. (pipe(7) 참조)
        - 탐색 가능한(seekable) 파일(예: lseek (2)가 적용(apply)될 수 있는 일반파일)의 경우 file offset에서 쓰기가 발생하며, file offset은 실제로 작성된 바이트 수만큼 증가한다. 파일이 `O_APPEND`로 열린 경우, file offset은 쓰기 전에 먼저 EOF로 설정된다. file offset의 조정(adjustment) 및 쓰기 동작은 원자(atomic) 단계로 수행된다.
        - POSIX는 `write()`가 반환된 후에 발생(occur)한다는 것을 증명(prove)할 수 있는 `read(2)`가 새로운 데이터를 반환할 것을 요구한다. 모든 파일 시스템이 POSIX를 준수(confirming)하는 것은 아니다.
        - POSIX.1에 따르면 `count`가 SSIZE_MAX보다 크면, 구현 정의 결과가 된다.
    - RETURN VALUE
        - On success, 쓰여진 바이트 수가 반환된다.
        - On error, -1이 반환되고 `errno`가 오류를 나타내도록 설정된다.
        - `write()`가 성공하면 전송 바이트 수가 `count` 바이트보다 적을 수 있다. 이러한 부분 쓰기는 다양한(various) 이유로 발생할 수 있는데, 예를 들어 디스크 장치에 요청된 모든 바이트를 쓰기 위한 공간이 부족(insufficient)하거나, 소켓, 파이프 또는 유사한 장치에 대한 차단된 `write()`가 일부 전송 후 요청된 바이트를 모두 전송하기 전에 신호 처리기(signal handler)에 의해 중단(interrupt)되었기 때문이다. 부분 쓰기의 경우, 호출자(caller)는 나머지(remaining) 바이트를 전송하기 위해 다른 `write()` 호출을 할 수 있다. 후속(subsequent) 호출은 추가(further) 바이트를 전송하거나 오류가 발생할 수 있다(예: 디스크가 가득 찬 경우).
        - `count`가 0이고 `fd`가 일반 파일을 참조하는 경우, 아래 오류 중 하나가 감지되면 `write()`가 실패 상태(failture status)를 반환할 수 있다. 오류가 감지되지 않거나, 오류 감지가 수행되지 않으면, 다른 효과를 유발(causing)하지 않고 0이 반환된다. `count`가 0이고 `fd`가 일반 파일이 아닌 파일을 참조하는 경우, 결과가 지정(specify)되지 않습니다.
- malloc(3)
    - NAME
        - allocate dynamic memory
    - SYNOPSIS
        
        ```c
        #include <stdlib.h>
        void *malloc(size_t size);
        ```
        
    - DESCRIPTION
        - `malloc()` 함수는 `size` 바이트를 할당하고 할당된 메모리를 가리키는 포인터를 반환한다. 메모리가 초기화(initialize)되지 않았다. `size`가 0이면 `malloc()`은 `NULL`을 반환하거나 나중에 `free()`에 성공적으로 전달할 수 있는 고유(unique) 포인터 값을 반환한다.
    - RETURN VALUE
        - `malloc()` 함수는 할당된 메모리를 가리키는 포인터를 반환하며, 이는 모든 내장 타입에 적합하게(suitably) 정렬된다. 오류가 발생하면 이러한 함수는 `NULL`을 반환한다. `NULL`은 `size`가 0인 `malloc()`을 성공적으로 호출함에 의해 반환될 수도 있다.
- free(3)
    - NAME
        - free dynamic memory
    - SYNOPSIS
        
        ```c
        #include <stdlib.h>
        void free(void *ptr);
        ```
        
    - DESCRIPTION
        - `free()` 함수는 `ptr`이 가리키는 메모리 공간을 해제하는데, 이는 이전 `malloc()`, `calloc()` 또는 `realloc()` 호출에 의해 반환된 것 이어야한다. 그렇지 않은 경우, 또는 이전에 `free(ptr)`가 이미 호출된 경우, 정의되지 않은 동작(undefined behavior)이 발생한다. `ptr`이 `NULL`이면, 작업이 수행되지 않는다.
    - RETURN VALUE
- perror(3)
    - NAME
        - print a system error message
    - SYNOPSIS
        
        ```c
        #include <stdio.h>
        void perror(const char *s);
        ```
        
    - DESCRIPTION
        - `perror()` 함수는 system or library function을 호출하는 동안 마주친(encountered) 마지막 에러를 설명하는 표준 에러(standard error) 메시지를 생성한다.
        - 첫 번째로 (`s`가 `NULL`이 아니고 `*s`가 null byte가 아닐 때 (`’\0’`), 인자 문자열 `s`는 출력된다음 콜론과 공백이 인쇄된다. 그러면 `errno`의 현재 값과 줄바꿈(new-line)에 해당하는(corresponding) 에러 메시지가 표시된다.
        - 가장 유용하게 사용되려면, 인자 문자열은 에러가 발생한 함수의 이름을 포함해야 한다.
- strerror(3)
    - NAME
        - return string describing error number
    - SYNOPSIS
        
        ```c
        #include <string.h>
        char *strerror(int errnum);
        ```
        
    - DESCRIPTION
        - `strerror()` 함수는 `errnum` 인자에 전달된 에러 코드를 설명하는 문자열의 포인터를 반환하고, 적절한(appropriate) 언어를 선택하기 위해 현재 로케일의 `LC_MESSAGES` 부분을 사용할 수 있다. (예를 들어, `errnum`이 `EINVAL`이면, 반환된 설명은 “Invalid argument”가 될 것이다.) 이 문자열은 응용 프로그램에 의해서 수정될 수 없지만, `streror()` or `strerror_l()`에 대한 후속(subsequent) 호출에 의해 수정될 수 있다. `perror()`를 포함해 다른 라이브러리 함수는 이 문자열을 수정하지 않는다.
    - RETURN VALUE
        - 적절한(appropriate) 에러 설명 문자열을 반환하거나, error number를 알 수 없는 경우, “Unknown error nnn” 메시지를 반환한다.
- execve(2)
    - NAME
        - execute program
    - SYNOPSIS
        
        ```c
        #include <unistd.h>
        int execve(const char *pathname, char *const argv[], char *const envp[]);
        ```
        
    - DESCRIPTION
        - `execve()` 함수는 `pathname`에 의해 참조되는 프로그램을 실행한다. 이로 인해 호출 프로세스에 의해 현재 실행중인 프로그램은 새로 초기화된 스택, 힙, (초기화된/초기화되지 않은) 데이터 세그먼트를 가진 새로운 프로그램으로 대체된다.
        - `pathname`은 바이너리 실행 파일 또는 아래 형식의 행으로 시작하는 스크립트여야 한다.
            - `#!interpreter [optional-arg]`
        - `argv`는 명령줄(command-line) 인자로 새로운 프로그램에 전달되는 문자열에 대한 포인터 배열이다. 관례적으로, 이 문자열들의 첫 번째(`argv[0]`)는 실행 중인 파일과 연관된 파일 이름을 포함(contain)해야 한다. `argv` 배열은 `NULL` 포인터로 종료돼야 한다. (따라서, 새로운 프로그램에는, `argv[argc]`는 `NULL`이어야 한다.)
        - `envp`는 새로운 프로그램의 환경으로 전달되는 `key=value` 형식의 문자열에 대한 포인터 배열이다. `envp` 배열은 `NULL` 포인터로 종료돼야 한다.
        - 인자 벡터와 환경은 다음과 강티 정의될 때 새 프로그램의 메인 함수에 의해 액세스될 수 있다.
            - `int main(int argc, char *argv[], char *envp[])`
        - 그러나, 메인 함수에 대한 세 번째 인자의 사용은 POSIX.1에 명시(specified)되어 있지 않다. POSIX.1에 따르면, 환경은 외부 변수 `environ(7)`을 통해(via) 액세스돼야 한다.
        - `execve()`는 성공을 반환하지 않으며, 호출 프로세스의 텍스트, 초기화된 데이터, 초기화되지 않은 데이터(bss), 스택은 새로 로드된 프로그램의 내용에 따라 덮어쓰여진다.
        - 현재 프로그램이 프로세스 추적(`ptraced`)되는 중인 경우, 성공적인 `execve()` 후에 SIGTRAP 신호가 전송된다.
        - set-user-ID bit가 `pathname`으로 참조되는 프로그램 파일에 설정된 경우, 호출 프로세스의 유효한(effective) 사용자 ID는 프로그램 파일 소유자의 ID로 변경된다. 마찬가지로, set-group-ID bit가 프로그램 파일에 설정되는, 호출 프로세스의 유효 그룹 ID는 프로그램 파일의 그룹으로 설정된다.
    - RETURN VALUE
        - On success, `execve()` does not return
        - On error -1 is returned, and `errno` is set to indicate(나타내다) the error.
    - EXAMPLE
        
        ```c
        #include <unistd.h>
        #include <stdio.h>
        
        extern char **environ;
        
        int	main(void)
        {
        	char *filepath = "/bin/ls";
        	char *argv[] = {"ls", "-al", NULL};
        
        	execve(filepath, argv, environ);
        	printf("main function of test.c\n");
        	return (0);
        }
        ```
        
- access(2)
    - NAME
        - check user’s permissions for a file
    - SYNOPSIS
        
        ```c
        #include <unistd.h>
        int access(const char *pathname, int mode);
        ```
        
    - DESCRIPTION
        - `access()`는 호출 프로세스가 `pathname` 파일에 액세스 가능한지 확인한다. `pathname`이 symbolic link면, 역참조한다. (원본 파일을 확인)
        - `mode`는 수행할 접근성(accessibility) 확인을 지정하며, 값 `F_OK, R_OK, W_OK, X_OK` 중 하나 이상의 비트 OR로 구성된 마스크이다.
            - `F_OK`: 파일의 존재 여부 테스트
            - `R_OK, W_OK, X_OK`: 각각 파일의 존재 여부를 테스트하고, 읽기, 쓰기 및 실행 권한을 부여
    - RETURN VALUE
        - On success, zero is returned.
            - 요청된 모든 권한이 부여됨
            - `F_OK` 모드이고 파일이 존재
        - On error, -1 is returned, and `errno` is set to indicate(나타내다) the error.
            - 요청된 모든 사용 권한이 ‘거부된 사용 권한을 요청하는 모드’에서 하나 이상의 비트를 부여
            - `F_OK` 모드이고 파일이 존재하지 않음
            - 다른 에러 발생
    - EXAMPLE
        
        ```c
        #include <unistd.h>
        #include <stdio.h>
        
        int	main(void)
        {
        	int access_is_0 = access("testfile", F_OK | R_OK | W_OK);
        	printf("%d\n", access_is_0);
        	return (0);
        }
        ```
        
- dup(2)
    - NAME
        - duplicate a file descriptor
    - SYNOPSIS
        
        ```c
        #include <unistd.h>
        int dup(int oldfd);
        ```
        
    - DESCRIPTION
        - `dup()` 시스템 콜은 descriptor `oldfd`와 동일한 open file description을 참조하는 새로운 file descriptor를 할당한다. 새로운 file descriptor number는 호출 프로세스에서 사용되지 않는 가장 낮은 번호의 file descriptor인 것이 보장된다.
        - 성공적인 반환 이후, the old and new file descriptors는 바꿔서 사용 가능할 것이다. 이 두 file descriptors는 같은 open file description을 참조하기 때문에, 그것들은 file offset과 file status flags를 공유한다. 예를 들어, 두 file descriptors 중 하나서 `lseek(2)`를 사용하여 file offset을 수정하면, 다른 file descriptor에 대해서도 offset이 변경된다.
        - 두 file descriptors는 file descriptor flags(실행 시 닫기 flag)를 공유하지 않는다. 복제된 descriptor에 대한 실행 시 닫기 flag(FD_CLOEXEC; see `fcntl(2)`)는 꺼진다.
    - RETURN VALUE
        - On success, `dup()` system calls return the new file descriptor.
        - On error, -1 is returned, and `errno` is set to indicate(나타내다) the error.
    - EXAMPLE
        
        ```c
        #include <fcntl.h>
        #include <unistd.h>
        #include <stdio.h>
        
        int	main(void)
        {
        	int fd = open("testfile", O_RDONLY);
        	int other_fd = open("testfile", O_RDONLY);
        	int dup_fd = dup(fd);
        
        	char buf[10];
        	int	size = 10;
        	int read_bytes;
        
        	read_bytes = read(fd, buf, size);
        	printf("file descriptor:%d\nbuf: %s\nread_bytes:%d\n\n", fd, buf, read_bytes);
        	read_bytes = read(other_fd, buf, size);
        	printf("file descriptor:%d\nbuf: %s\nread_bytes:%d\n\n", other_fd, buf, read_bytes);
        	read_bytes = read(dup_fd, buf, size);
        	printf("file descriptor:%d\nbuf: %s\nread_bytes:%d\n\n", dup_fd, buf, read_bytes);
        	close(fd);
        	printf("====================close fd====================\n\n");
        	read_bytes = read(dup_fd, buf, size);
        	printf("file descriptor:%d\nbuf: %s\nread_bytes:%d\n\n", dup_fd, buf, read_bytes);
        	close(other_fd);
        	close(dup_fd);
        	return (0);
        }
        ```
        
- dup2(2)
    - NAME
        - duplicate a file descriptor
    - SYNOPSIS
        
        ```c
        #include <unistd.h>
        int dup2(int oldfd, int newfd);
        ```
        
    - DESCRIPTION
        - `dup2()` 시스템 콜은 `dup()`과 같은 작업(task)을 수행(perform)한다. 하지만 가장 낮은 번호의 미사용 file descriptor를 사용하는 것 대신에, `newfd`에 지정된 file descriptor number를 사용한다. 다시 말해서, `oldfd`와 동일한 open file description을 참조하도록 file descriptor `newfd`가 조정된다.
        - file descriptor `newfd`가 이전에(previously) 열려 있었다면, 재사용되기 전에 닫힌다. 닫기는 자동으로 수행된다 (즉, 닫는 동안 `dup2()`에 의한 어느 에러도 보고(report)되지 않음).
        - file descriptor `newfd`를 닫고 재사용하는 단계들이 원자적으로(atomically) 수행(perform)된다. `close(2) and dup()`을 사용해 동일한 기능을 구현하려는 시도는 두 단계 사이에서 `newfd`가 재사용될 수 있다는 경합 조건(race condition)의 대상이 될 것이기 때문에, 이것은 중요하다. 이러한 재사용은 메인 프로그램이 file descriptor를 할당하는 signal handler에 의해서 중단(interrupt)되거나, 병렬 스레드(parallel thread)가 file descriptor를 할당하기 때문에 발생할 수 있다.
        - 다음 사항에 유의해라
            - `oldfd`가 유효한 file descriptor가 아닌 경우, 호출은 실패하고, `newfd`는 닫히지 않는다.
            - `oldfd`가 유효한 file descriptor이고, `newfd`가 `oldfd`와 같은 값을 가지고 있으면, `dup2()`는 아무것도 하지 않고, `newfd`를 반환한다.
    - RETURN VALUE
        - On success, `dup()` system calls return the new file descriptor.
        - On error, -1 is returned, and `errno` is set to indicate(나타내다) the error.
    - EXAMPLE
        
        ```c
        #include <fcntl.h>
        #include <unistd.h>
        #include <stdio.h>
        
        int	main(void)
        {
        	int fd = open("testfile", O_RDONLY);
        	int fd2 = open("testfile2", O_RDONLY);
        
        	char buf[10];
        	int	size = 10;
        	int read_bytes;
        
        	read_bytes = read(fd, buf, size);
        	printf("file descriptor:%d\nbuf: %s\nread_bytes:%d\n\n", fd, buf, read_bytes);
        	read_bytes = read(fd2, buf, size);
        	printf("file descriptor:%d\nbuf: %s\nread_bytes:%d\n\n", fd2, buf, read_bytes);
        	
        	int dup2_fd = dup2(fd, fd2);
        	printf("============dup2(3, 4)==============\n\n");
        	read_bytes = read(fd, buf, size);
        	printf("file descriptor:%d\nbuf: %s\nread_bytes:%d\n\n", fd, buf, read_bytes);
        	read_bytes = read(fd2, buf, size);
        	printf("file descriptor:%d\nbuf: %s\nread_bytes:%d\n\n", fd2, buf, read_bytes);
        	read_bytes = read(dup2_fd, buf, size);
        	printf("file descriptor:%d\nbuf: %s\nread_bytes:%d\n\n", dup2_fd, buf, read_bytes);
        	return (0);
        }
        ```
        
- exit(3)
    - NAME
        - cause normal process termination(정상적인 프로세스 종료 유발)
    - SYNOPSIS
        
        ```c
        #include <stdlib.h>
        noreturn void exit(int status);
        ```
        
    - DESCRIPTION
        - `exit()` 함수는 정상 프로세스 종료유발(cause)하며 최하위 바이트의 상태(즉, 상태 & 0xFF)가 부모에게 반환된다 (`wait(2)` 참조).
        - `atexit(3)`과 `on_exit(3)`로 등록된 모든 함수는 등록의 역순으로 호출된다. (이러한 함수들 중 하나는 `atexit(3)` 또는 `on_exit(3)`를 사용하여 exit processing 동안에 실행할 추가 함수를 등록할 수 있다. 새 등록은 호출할 남은(remain) 함수 리스트의 맨 앞에 추가된다.) 만약 이 함수들 중 하나가 반환하지 않으면(예: `_exit(2)`를 호출하거나 signal로 스스로 죽임), 나머지 함수들 중 아무것도 호출되지 않으며, 추가적인 exit processing(특히, stdio(3) streams의 flushing)은 버려진다(abandoned). `texit(3)` 또는 `on_exit(3)`을 사용하여 함수를 여러번(multiple times) 등록한 경우, 등록된 횟수만큼 호출된다.
        - 열려있는 모든 stdio(3) streams이 플러시(flush)되고 닫힌다. tmpfile(3)에 의해 생성된 파일은 제거된다.
            - Buffer is a region of memory used to temporarily hold data while it is being moved from one place to another.
                - 버퍼는 데이터가 한 위치에서 다른 위치로 이동하는 동안 일시적으로 데이터를 보관하는데 사용되는 메모리 영역이다.
            - Flushing a stream ensures(보장하다) that all data that has been written to that stream is output, including clearing any that may have been buffered.
                - 스트림 플러싱은 (버퍼링되었을 수 있는 모든 데이터를 지우는 것을 포함하여, 해당 스트림에 기록된 모든 데이터가 출력된다는 것)을 보장한다.
        - C 표준은 `exit()`에 전달될 수 있는 두 개의 상수 `EXIT_SUCCESS`와 `EXIT_FAILURE`를 지정한다. 각각(respectively) 성공적 종료, 실패적인 종료를 나타낸다(indicate).
    - RETURN VALUE
        - `exit()` function does not return.
- fork(2)
    - NAME
        - create a child process
    - SYNOPSIS
        
        ```c
        #include <unistd.h>
        pid_t fork(void);
        ```
        
    - DESCRIPTION
        - `fork()`는 호출 프로세스를 복제하여 새로운 프로세스를 생성한다. 새로운 프로세스는 자식 프로세스라고 한다. 호출 프로세스를 부모 프로세스라고 한다.
        - 자식 프로세스와 부모 프로세스는 별도의(separate) 메모리 공간에서 실행된다(run). `fork()` 시에(at the time of `fork()`) 두 메모리 공간은 같은 내용(content)를 갖는다. 프로세스 중 하나에 의해 수행(performed)된 메모리 쓰기(write), 파일 매핑은 다른 프로세스에 영향을 미치지 않는다.
        - 자식 프로세스는 다음 사항을 제외(axcept)하고 부모 프로세스와 정확히(exact) 중복된다.
            - 자식은 고유한 process ID(PID)를 가지고 있으며, 이 PID는 이미 존재하는 어느 프로세스 그룹 또는 세션의 ID와도 일치하지 않는다.
            - 자식 프로세스의 부모 프로세스 ID는 부모 프로세스 ID와 같다.
            - 자식은  부모의 메모리 잠금(`mlcok(2)`, `mlockall(2)`)을 상속(inherit)받지 않는다.
            - 프로세스 리소스 사용률(`getrusage(2)`) 및 CPU 시간 카운터(`times(2)`는 자식에서 0으로 재설정된다.
            - 자식의 보류 중인 시그널 집합은 처음엔 비어있다 (`sigpending(2)`).
            - 자식은 부모로부터 세마포어 조정(adgustment)을 상속(inherit)받지 않는다 (`semop(2)`).
                - A semaphore is an integer variable, shared among multiple processes.
                    - 세마포어는 여러 프로세스 사이에 공유되는 정수 변수이다.
            - 자식은 부모로부터 프로세스 관련(process-associated) 레코드 잠금을 상속받지 않는다. (반면, `fcntl(2)` open file description 잠금과 `flock(2)` 잠금은 부모로부터 상속받는다.)
            - 자식은 부모로부터 타이머를 상속받지 않는다 (`setitimer(2)`, `alarm(2)`, `timer_create(2)`).
            - 자식은 부모로부터 미해결된(outstanding) 비동기(asynchronous) I/O 작업을 상속받지 않는다 (`aio_read(3)`, `aio_write(3)`). 또한, 부모로부터 어떠한 비동기 I/O context도 상속받지 않는다 (see `io_setup(2)`).
    - RETURN VALUE
        - On success, the PID of the child process is returned in the parent, 0 is returned in the child.
        - On failure, -1 is returned in the parent, no child process is created, and `errno` is set to indicate the error.
    - EXAMPLE
        
        ```c
        #include <unistd.h>
        #include <stdio.h>
        
        int	main(void)
        {
        	pid_t ret_fork;
        	int nbr = 100;
        	char *str = "string";
        
        	printf("before fork...\n");
        	ret_fork = fork();
        	printf("after fork...\n");
        	if (ret_fork > 0)
        	{
        		nbr = 200;
        		str = "parent";
        		printf("[parent process]\nPID:%d\nCPID:%d\nnbr:%d\nstr:%s\n\n", getpid(), ret_fork, nbr, str);
        	}
        	else if (ret_fork == 0)
        	{
        		str = "child";
        		printf("[child process]\nPPID:%d\nPID:%d\nnbr:%d\nstr:%s\n\n", getppid(), getpid(), nbr, str);
        	}
        	else
        	{
        		printf("fork failed\n");
        		return (-1);
        	}
        	return (0);
        }
        ```
        
        ```bash
        % ./a.out                                                   
        before fork...
        after fork...
        [parent process]
        PID:89061
        CPID:89062
        nbr:200
        str:parent
        
        after fork...
        [child process]
        PPID:1
        PID:89062
        nbr:100
        str:child
        ```
        
        - child process에서 `getppid()`를 통해 얻은 PID가 1인 이유: 부모 프로세스가 종료되었기 때문. (`wait()`)을 통해 부모 프로세스를 종료시키지 않고 기다리게 할 수 있다.
- wait(2)
    - NAME
        - wait for process to change state
            - 프로세스가 상태를 변경할 때까지 대기
    - SYNOPSIS
        
        ```c
        #include <sys/wait.h>
        pid_t wait(int *wstatus);
        ```
        
    - DESCRIPTION
        - `wait()` 시스템 콜은 호출 프로세스의 자식에서 상태 변경을 기다리고, 상태가 변경된 자식에 대한 정보를 얻는데(obtain) 사용된다. 상태 변경은 다음과 같이 간주된다(be considered).
            - 자식이 종료됨
            - 자식이 signal에 의해 중지됨
            - 자식이 signal에 의해 다시 시작됨(resume)
        - 종료된 자식의 경우(in the case of), wait 수행(performing)은 시스템이 자식과 관련된 리소스를 해제(release)하는 것을 허락한다. 만약 wait이 수행되지 않으면, 종료된 자식은 “zombie” 상태에 남아있는다(remain).
        - `wait()` 시스템 콜은 자식 중 하나가 종료될 때까지 호출 스레드의 실행을 유예한다(suspend).
        - `wait(&wstatus)` == `waitpid(-1, &wstatus, 0)`
        - `wstatus`가 `NULL`이 아닌 경우, `wait()`는 상태 정보를 `wstatus`에 저장한다. 이 정수는 다음과 같은 매크로로 검사(inspect)할 수 있다.
            - `WIFEXITED**(***wstatus***)**`
                - 자식이 정상적으로 종료된 경우 즉, `exit(3)` or `_exit(2)`를 호출하거나 `main()`으로부터 반환된 경우, true를 반환한다.
            - `WEXITSTATUS**(***wstatus***)**`
                - 자식의 종료 상태(exit status)를 반환한다. `WIFEXITED`가 true를 반환한 경우에만 이 매크로를 사용해야 한다.
            - `WIFSIGNALED**(***wstatus***)**`
                - 자식 프로세스가 signal에 의해 종료된 경우 true를 반환한다.
            - `WTERMSIG**(***wstatus***)**`
                - 자식 프로세스의 종료를 야기한 signal의 번호를 반환한다. 이 매크로는 `WIFSIGNALED`가 true를 반환한 경우에만 사용해야 한다.
            - `WCOREDUMP**(***wstatus***)**`
                - 자식에서 코어 덤프가 생성된 경우 true를 반환한다. 이 매크로는 `WIFSIGNALED`가 true를 반환한 경우에만 사용해야 한다.
            - `WIFSTOPPED**(***wstatus***)**`
                - 자식 프로세스가 signal의 전달에 의해 중지된 경우 true를 반환한다. 이는 호출이 `WUNTRACED`를 사용하여 수행 되었거나 자식이 추적되고 있을 때만 가능하다.
            - `WSTOPSIG**(***wstatus***)**`
                - 자식의 중지를 야기한 signal의 번호를 반환한다. 이 매크로는 `WIFSTOPPED`가 true를 반환한 경우에만 사용해야 한다.
            - `WIFCONTINUED**(***wstatus***)**`
                - SIGCONT 전송으로 자식 프로세스가 재개(resume)된 경우 true를 반환한다.
    - RETURN VALUE
        - On success, return the process ID of the terminated child.
        - On failure, -1 is returned, `errno` is set to indicate the error.
    - EXAMPLE
        
        ```c
        #include <unistd.h>
        #include <sys/wait.h>
        #include <errno.h>
        #include <stdio.h>
        #include <stdlib.h>
        
        int	main(void)
        {
        	pid_t ret_fork;
        	pid_t ret_wait;
        	int wstatus;
        	int nbr = 100;
        
        	ret_fork = fork();
        	if (ret_fork > 0)
        	{
        		printf("[parent process]\nPID:%d\nCPID:%d\nnbr:%d\n\n", getpid(), ret_fork, nbr);
        		ret_wait = wait(&wstatus);
        		printf("wait() is done\nret_wait:%d\nwstatus:%d\n", ret_wait, wstatus);
        		if (ret_wait == -1)
        		{
        			printf("%d\n", errno);
        			exit(EXIT_FAILURE);
        		}
        		else
        			if(WIFEXITED(wstatus)) 
                        printf("wait : 자식 프로세스 정상 종료 %d\n",WEXITSTATUS(wstatus));
                    else if(WIFSIGNALED(wstatus)) 
                        printf("wait : 자식 프로세스 비정상 종료 %d\n",WTERMSIG(wstatus));
        		
        	}
        	else if (ret_fork == 0)
        	{
        		printf("[child process]\nPPID:%d\nPID:%d\nnbr:%d\n\n", getppid(), getpid(), nbr);
        		exit(EXIT_SUCCESS);
        	}
        	else
        	{
        		printf("fork failed\n");
        		return (-1);
        	}
        	return (0);
        }
        ```
        
        ```bash
        [parent process]
        PID:84128
        CPID:84129
        nbr:100
        
        [child process]
        PPID:84128
        PID:84129
        nbr:100
        
        wait() is done
        ret_wait:84129
        wstatus:0
        wait : 자식 프로세스 정상 종료 0
        ```
        
- waitpid(2)
    - NAME
        - wait for process to change state
    - SYNOPSIS
        
        ```c
        #include <sys/wait.h>
        pid_t waitpid(pid_t pid, int *wstatus, int options);
        ```
        
    - DESCRIPTION
        - `waitpid()` 시스템 콜은 호출 프로세스의 자식에서 상태 변경을 기다리고, 상태가 변경된 자식에 대한 정보를 얻는데(obtain) 사용된다. 상태 변경은 다음과 같이 간주된다(be considered).
            - 자식이 종료됨
            - 자식이 signal에 의해 중지됨
            - 자식이 signal에 의해 다시 시작됨(resume)
        - 종료된 자식의 경우(in the case of), wait 수행(performing)은 시스템이 자식과 관련된 리소스를 해제(release)하는 것을 허락한다. 만약 wait이 수행되지 않으면, 종료된 자식은 “zombie” 상태에 남아있는다(remain).
        - `waitpid()` 시스템 콜은 매개변수 `pid`에 지정된(specified) 자식이 상태를 변경할 때까지 호출 스레드의 실행을 유예한다(suspend). 기본적으로, `waitpid()`는 종료된 자식만 기다리지만, 이 동작은 아래에 설명된 대로 `options` 인자를 통해 수정할 수 있다.
        - `pid`의 값은 다음과 같이 될 수 있다.
            - `< -1`: 프로세스 그룹 ID가 `pid`의 절대값과 동일한 모든 자식 프로세스를 기다린다.
            - `-1`: 모든 자식 프로세스를 기다린다.
            - `0`: `waitpid()`를 호출 시, 프로세스 그룹 ID가 호출 프로세스와 동일한 모든 자식 프로세스를 기다린다.
            - `> 0`: 프로세스 ID가 `pid`의 값과 동일한 자식을 기다린다.
        - `options`의 값은 다음 상수(constant) 중 0 이상의 OR이다.
            - `WNOHANG`: 자식이 종료되지 않으면 즉시 반환한다.
            - `WUNTRACED`: 자식이 멈춘 경우에도 반환된다.
            - `WCONTINUED`: SIGCONT 전달로 중지된 자식이 재개된 경우에도 반환된다.
        - `wstatus`가 `NULL`이 아닌 경우, `waitpid()`는 상태 정보를 `wstatus`에 저장한다. 이 정수는 다음과 같은 매크로로 검사(inspect)할 수 있다.
            - `WIFEXITED**(***wstatus***)**`
                - 자식이 정상적으로 종료된 경우 즉, `exit(3)` or `_exit(2)`를 호출하거나 `main()`으로부터 반환된 경우, true를 반환한다.
            - `WEXITSTATUS**(***wstatus***)**`
                - 자식의 종료 상태(exit status)를 반환한다. `WIFEXITED`가 true를 반환한 경우에만 이 매크로를 사용해야 한다.
            - `WIFSIGNALED**(***wstatus***)**`
                - 자식 프로세스가 signal에 의해 종료된 경우 true를 반환한다.
            - `WTERMSIG**(***wstatus***)**`
                - 자식 프로세스의 종료를 야기한 signal의 번호를 반환한다. 이 매크로는 `WIFSIGNALED`가 true를 반환한 경우에만 사용해야 한다.
            - `WCOREDUMP**(***wstatus***)**`
                - 자식에서 코어 덤프가 생성된 경우 true를 반환한다. 이 매크로는 `WIFSIGNALED`가 true를 반환한 경우에만 사용해야 한다.
            - `WIFSTOPPED**(***wstatus***)**`
                - 자식 프로세스가 signal의 전달에 의해 중지된 경우 true를 반환한다. 이는 호출이 `WUNTRACED`를 상용하여 수행 되었거나 자식이 추적되고 있을 때만 가능하다.
            - `WSTOPSIG**(***wstatus***)**`
                - 자식의 중지를 야기한 signal의 번호를 반환한다. 이 매크로는 `WIFSTOPPED`가 true를 반환한 경우에만 사용해야 한다.
            - `WIFCONTINUED**(***wstatus***)**`
                - SIGCONT 전송으로 자식 프로세스가 재개(resume)된 경우 true를 반환한다.
    - RETURN VALUE
        - On success
            - 상태가 변경된 자녀의 프로세스 ID를 반환한다.
            - `WNOHANG`이 지정되고 `pid`에 의해 지정된 하나 이상의 자식이 존재하지만, 아직 상태를 변경하지 않은 경우 0이 반환된다.
        - On failure, -1 is returned.
    - EXAMPLE
        
        ```c
        #include <unistd.h>
        #include <sys/wait.h>
        #include <errno.h>
        #include <stdio.h>
        #include <stdlib.h>
        
        int	main(void)
        {
        	pid_t ret_fork;
        	pid_t ret_wait;
        	int wstatus;
        	int nbr = 100;
        
        	ret_fork = fork();
        	if (ret_fork > 0)
        	{
        		printf("[parent process]\nPID:%d\nCPID:%d\nnbr:%d\n\n", getpid(), ret_fork, nbr);
        		ret_wait = waitpid(ret_fork, &wstatus, WUNTRACED | WCONTINUED);
        		printf("wait() is done\nret_wait:%d\nwstatus:%d\n", ret_wait, wstatus);
        		if (ret_wait == -1)
        		{
        			printf("%d\n", errno);
        			exit(EXIT_FAILURE);
        		}
        		else
        			if (WIFEXITED(wstatus))
        				printf("exited, status=%d\n", WEXITSTATUS(wstatus));
        			else if (WIFSIGNALED(wstatus))
        				printf("killed by signal %d\n", WTERMSIG(wstatus));
        			else if (WIFSTOPPED(wstatus))
        				printf("stopped by signal %d\n", WSTOPSIG(wstatus));
        			else if (WIFCONTINUED(wstatus))
        				printf("continued\n");
        	}
        	else if (ret_fork == 0)
        	{
        		printf("[child process]\nPPID:%d\nPID:%d\nnbr:%d\n\n", getppid(), getpid(), nbr);
        		exit(EXIT_SUCCESS);
        	}
        	else
        	{
        		printf("fork failed\n");
        		return (-1);
        	}
        	return (0);
        }
        ```
        
        ```bash
        % ./a.out  
        [parent process]
        PID:93707
        CPID:93708
        nbr:100
        
        [child process]
        PPID:93707
        PID:93708
        nbr:100
        
        wait() is done
        ret_wait:93708
        wstatus:0
        exited, status=0
        ```
        
        - 자식 프로세스를 병렬로 실행하는 법: `waitpid(-1, NULL, 0)`
        
        ```c
        #include <stdio.h>
        #include <sys/wait.h>
        #include <errno.h>
        #include <unistd.h>
        #include <stdlib.h>
        
        void	run_child()
        {
        	pid_t	child;
        	int		wstatus;
        
        	child = fork();
        	if (child == -1)
        		exit(EXIT_FAILURE);
        	if (child > 0)
        	{
        		waitpid(child, &wstatus, WNOHANG);
        		printf("부모: (자식 pid:%d)\n", child);
        	}
        	else if (child == 0)
        	{
        		printf("	자식:%d 시작 / (부모 pid:%d)\n", getpid(), getppid());
        		sleep(1);
        		printf("	자식:%d 종료 / (부모 pid:%d)\n", getpid(), getppid());
        		exit(EXIT_SUCCESS);
        	}
        }
        
        int	main(void)
        {
        	int	i;
        
        	printf("부모 pid:%d\n", getpid());
        	i = 0;
        	while (i < 5)
        	{
        		run_child();
        		i++;
        	}
        	waitpid(-1, NULL, 0);
        	return (0);
        }
        ```
        
        ```bash
        youngcho@c2r10s5 test % ./a.out  
        부모 pid:95659
        부모: (자식 pid:95660)
        부모: (자식 pid:95661)
                자식:95660 시작 / (부모 pid:95659)
        부모: (자식 pid:95662)
                자식:95661 시작 / (부모 pid:95659)
        부모: (자식 pid:95663)
                자식:95662 시작 / (부모 pid:95659)
        부모: (자식 pid:95664)
                자식:95663 시작 / (부모 pid:95659)
                자식:95664 시작 / (부모 pid:95659)
                자식:95660 종료 / (부모 pid:95659)
                자식:95661 종료 / (부모 pid:95659)
                자식:95662 종료 / (부모 pid:95659)
                자식:95663 종료 / (부모 pid:95659)
                자식:95664 종료 / (부모 pid:95659)
        ```
        
- pipe(2)
    - NAME
        - create pipe
    - SYNOPSIS
        
        ```c
        #include <unistd.h>
        int pipe(int pipefd[2]);
        ```
        
    - DESCRIPTION
        - `pipe()`는 프로세스간(interprocess) 통신에 사용될 수 있는 단방향 데이터 채널인 pipe를 생성한다. `pipefd` 배열은 pipe의 끝을 참조하는 두 개의 file descriptors를 반환하는데 사용된다. `pipefd[0]`은 pipe의 읽기 끝(read end)을 나타낸다. `pipefd[1]`은 pipe의 쓰기 끝(write end)을 나타낸다. pipe의 write end에 쓰여진 데이터는 pipe의 read end로부터 읽어질 때까지 커널에 의해 버퍼링된다. 자세한 내용은 `pipe(7)` 참조해라.
    - RETURN VALUE
        - On success, zero is returned.
        - On error, -1 is returned, `errno` is set to indicate the error, and `pipefd` is left unchanged.
    - EXAMPLE
        
        ```c
        #include <unistd.h>
        #include <sys/wait.h>
        #include <errno.h>
        #include <stdio.h>
        #include <stdlib.h>
        #include <string.h>
        
        int	main(int argc, char *argv[])
        {
        	pid_t ret_fork;
        	pid_t ret_wait;
        	int	pipefd[2];
        	int wstatus;
        	char buf;
        
        	if (argc != 2) 
        	{
        		fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        		exit(EXIT_FAILURE);
        	}
        	if (pipe(pipefd) == -1)
        	{
        		perror("pipe");
        		exit(EXIT_FAILURE);
        	}
        	ret_fork = fork();
        	if (ret_fork == -1)
        	{
        		perror("fork");
        		exit(EXIT_FAILURE);
        	}
        	if (ret_fork > 0)
        	{
        		printf("[parent process]\n");
        		close(pipefd[0]);
        		printf("	write argv[1] to buffer of pipefd[1]\n");
        		write(pipefd[1], argv[1], strlen(argv[1]));
        		close(pipefd[1]);
        		printf("	call wait()...\n");
        		ret_wait = wait(&wstatus);
        		printf("	wait() is done\n");
        		if (ret_wait == -1)
        			printf("%d\n", errno);
        		else
        			if(WIFEXITED(wstatus))
                        printf("	wait : 자식 프로세스 정상 종료 WEXITSTATUS: %d\n",WEXITSTATUS(wstatus));
                    else if(WIFSIGNALED(wstatus)) 
                        printf("	wait : 자식 프로세스 비정상 종료 WTERMSIG: %d\n",WTERMSIG(wstatus));
        		printf("[parent process terminate]\n\n");
        		exit(EXIT_SUCCESS);
        	}
        	else
        	{
        		printf("[child process]\n");
        		close(pipefd[1]);
        		printf("	read from pipefd[0]\n	and write it to STDOUT\n");
        		while (read(pipefd[0], &buf, 1) > 0)
        			write(STDOUT_FILENO, &buf, 1);
        		write(STDOUT_FILENO, "\n", 1);
        		close(pipefd[0]);
        		printf("[child process terminate]\n\n");
        		exit(EXIT_SUCCESS);
        	}
        }
        ```
        
        ```bash
        % ./a.out "THIS IS WRRITEN FROM PIPEFD[1] IN PARENT PROCESS"
        [parent process]
                write argv[1] to buffer of pipefd[1]
                call wait()...
        [child process]
                read from pipefd[0]
                and write it to STDOUT
        THIS IS WRRITEN FROM PIPEFD[1] IN PARENT PROCESS
        [child process terminate]
        
                wait() is done
                wait : 자식 프로세스 정상 종료 WEXITSTATUS: 0
        [parent process terminate]
        ```
        
- unlink(2)
    - NAME
        - delete a name and possibly the file it refers to
            - 이름과 그것이 참조하는 파일 삭제
    - SYNOPSIS
        
        ```c
        #include <unistd.h>
        int unlink(const char *pathname);
        ```
        
    - DESCRIPTION
        - `unlink()`는 filesystem에서 name을 삭제한다. 만약 그 name이 file의 last link였고 file을 open한 프로세스가 없는 경우, file은 삭제되고 사용되던 공간은 재사용이 가능하도록 된다.
        - name이 file의 last link였지만 file을 open한 프로세스가 남아있는 경우, file은 그것을 참조하는 마지막 file descriptor가 닫힐 때까지 계속 존재(existence)상태로 남는다(remain).
        - name이 symbolic link를 참조하는 경우, link가 제거된다.
        - name이 socket, FIFO, or device를 참조하는 경우, 그것의 name은 제거되지만 object를 여는 프로세스에서 이 name을 계속 사용할 수 있다.
    - RETURN VALUE
        - On success, zero is returned.
        - On error, -1 is returned, and `errno` is set to indicate the error.

---

# 참고

- each man pages + below

[[Pipex] 사용가능 함수 - perror, strerror, exit](https://velog.io/@kyj93790/Pipex-%EC%82%AC%EC%9A%A9%EA%B0%80%EB%8A%A5-%ED%95%A8%EC%88%98-perror-strerror-exit)

[pipex](https://bigpel66.oopy.io/library/42/inner-circle/8)