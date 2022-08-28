# subject_translate

# Pipex

## 요약: Summary

이 프로젝트를 통해 이미 프로그램에서 사용해봐서 알고 있는 UNIX 메커니즘을 자세히 발견(discover) 수 있다.

> This project will let you discover in detail a UNIX mechanism that you already know by using it in your program.
> 

---

## 서문: Foreword

Cristina: “Go dance salsa somewhere :)”

---

## 공통 지침: Common Instructions

- 프로젝트는 C로 작성되어야 한다.
- 프로젝트는 ‘Norm’을 준수하여 작성되어야 한다. 만약 보너스 파일/함수가 있다면, 그것들도 ‘norm check’에 포함되어야 한다. 내부에 ‘norm error’가 있으면 0을 받을 것이다.
- 함수들은 ‘undefined behavior’를 제외하고(apart from) 예기치않게(unexpectedly) 종료(quit)되지 않아야 한다 (segmentation fault, bus error, double free, etc). 이 경우, 프로젝트는 ‘non functional’로 간주될(be considered) 것이고, 평가 중에 0을 받을 것이다.
- heap에 할당된(allocated) 모든 메모리 공간은 필요할 때 적절하게(properly) 해제(freed)되어야 한다. 누출(leaks)은 허용(tolerated)되지 않는다.
- subject가 요구하는 경우, `-Wall -Wextra -Werror` flags와 함께 `cc`를 사용하여 소스 파일을 요구되는 출력(output)으로 컴파일 할 Makefile을 제출해야 하며, Makefile은 relink되지 않아야 한다.
- Makefile은 적어도 `$(NAME), all, clean, fclean, re` rules를 포함(contain)해야 한다.
- 프로젝트에 보너스를 제출(turn in)하려면, Makefile에 “프로젝트의 main part에서 금지된 모든 다양한(various) headers, libraries or functions를 추가하는” `bonus` rule을 포함(include)해야 한다. subject가 다른 항목을 명시(specify)하지 않은 경우 보너스는 다른 파일인 `_bonus.{c/h}`에 있어야 한다. mandatory part와 bonus part는 별도로(separately) 진행된다.
- 프로젝트가 libft를 사용하는 것을 허용한 경우, 소스 및 연결된(associated) Makefile을 `libft` 폴더에 복사해야 한다. 프로젝트의 Makefile은 libft의 Makefile을 사용하여 library를 컴파일 해야한 다음, 프로젝트를 컴파일 해야 한다.
- 비록 이 작업(테스트 프로그램)은 제출되지 않아도 되고 점수를 메기지 않을지라도(even though), 프로젝트를 테스트 프로그램을 만들 것을 권장(encourage)한다. 그것은 너의 일과 peer의 일을 쉽게 테스트 할 기회를 줄 것이다. 디펜스 동안에 특별히(especially) 유용한 검사라는 것을 알게될 것이다. 실제로(indeed), 디펜스 동안에, 너의 테스트 및/또는 평가 중인 peer의 테스트를 사용하는 것은 자유이다.
- 할당된 git repository에 작업물을 제출해라. git repository에 있는 작업물만 평가를 받는다(be graded). 너의 작업물을 평가하기위해 ‘Deepthought’가 배정(assign)된다면, 그것은 당신의 peer 평가 이후에 이루어질 것이다. ‘Deepthought’ 평가중에 너의 작업물 중 어느 부분(section)에서라도 error가 발생한다면, 평가는 중지된다.

---

## Mandatory part

| Program name | pipex |
| --- | --- |
| Turn in files | Makefile, *.h, *.c |
| Makefile | NAME, all, clean, fclean, re |
| Arguments | file1 cmd1 cmd2 file2 |
| External functs. | - open, close, read, write, malloc, free, perror, strerror, access, dup, dup2, execve, exit, fork, pipe, unlink, wait, waitpid
- ft_printf and any equivalent YOU coded |
| Libft authroized | Yes |
| Description | This project is about handling pipes. |
- 프로그램은 다음과 같이 실행(execute)된다.
: `./pipex file1 cmd1 cmd2 file2`
- 프로그램은 4개의 인자(argument)를 가진다.
    - `file1` and `file2` are file names.
    - `cmd1` and `cmd2` are shell commands with their parameters.
- 프로그램은 아래의 shell command와 정확히 동일하게 동작해야 한다.
: `$> < file1 cmd1 | cmd2 > file2`

### 1. Examples

`./pipex infile "ls -l" "wc -l" outfile` == `< infile ls -l | wc -l > outfile`

`./pipex infile "grep a1" "wc -w" outfile` == `< infile grep a1 | wc -w > outfile`

### 2. Requirements

프로젝트는 다음 규칙들을 준수해야 한다.

- 소스 파일들을 컴파일할 Makefile을 제출해야 한다. ‘relink’가 발생하지 않아야 한다.
- errors를 철저히(thoroughly) 처리해야 한다. 결코(in no way) 프로그램이 예기치않게(unexpectedly) 종료되지 않아야 한다 (segmentaion fault, bus error, double free, and so forth).
- 프로그램은 메모리 누수(leaks)가 절대 없어야 한다.
- 의심(doubt)이 있다면, shell command처럼 errors를 처리해라
: `< file cmd1 | cmd2 > file2`

---

## Bonus part

아래와 같이 하면 추가 점수를 얻을 것이다

- 다중 파이프 처리
    - `./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2` == `< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2`
- 첫번째 매개변수가 “here_doc”일시, `<<` 와 `>>` 를 지원
    - `./pipex here_doc LIMITER cmd cmd1 file` == `cmd << LIMITER | cmd1 >> file`

(Warning) 보너스 파트는 만다토리 파트가 완벽한 경우에만 평가(assess)될 것이다. 완벽하다는 것은 만다토리 파트가 완전하게(integrally) 수행되었으며 오작동(malfunctioning) 없이 작동함을 의미한다. 필수 요구사항을 모두 통과하지 못한 경우, 보너스 파트는 전혀(not at all) 평가되지 않는다.

---

## Submission and peer-evaluation

평소처럼(as usual) Git repository에 과제(assignment)를 제출한다. 디펜스 동안 repository 내부의 작업만 평가될 것이다. 파일의 이름이 올바른지 보장(ensure)하기 위해 두 번 확인하는 것을 주저하지(hesitate) 마라.
