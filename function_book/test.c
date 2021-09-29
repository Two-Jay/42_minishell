/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 14:52:08 by jekim             #+#    #+#             */
/*   Updated: 2021/09/29 15:01:11 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

unsigned long fibonacci(int n)
{
	if (n == 0 || n == 1)
		return (1);
	else
		return (fibonacci(n - 1) + fibonacci(n - 2));
}

int main(int argc, char *argv[])
{
	int		exit_code;
	int		value;
	pid_t	pid;

	// 이런 식으로 fork를 실행하면, 해당 pid가 -1, 0, 0 < pid 인지 체크해서
	// 각 프로세스 별로 어떻게 동작할 지 구성할 수 있다.
	if (argc != 2)
		return (0);
	value = atoi(argv[1]);
	if (value > 50)
		return (0);
	exit_code = 0;
	pid = fork();
	if (pid == -1)
	{
		// 에러, fork() 실패
		printf("error!");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		printf("Child : My pid is %d, and i'm a child of %d\n",
			(int)getpid(),
			(int)getppid());
		if (value > 0)
		{
			printf("Child : I told to ma parent that argv is bigger than 0\n");
			// fibonacci 함수에 4~50 정도 넣으면 무슨 일이 일어날까...?
			printf("Child : you wish %lu, right?\n", fibonacci(value));
			exit(EXIT_SUCCESS);
		}
		else if (value <= 0)
		{
			printf("Child : I told to ma parent that argv is not bigger than 0\n");
			exit(EXIT_FAILURE);
		}

	}
	else
	{
		printf("Parent : My pid is %d, and i'm a child of %d\n and My child is %d\n",
			(int)getpid(),
			(int)getppid(),
			(int)pid);
		waitpid(pid, &exit_code, 0);
		printf("child %d send me exit_code : %d\n", pid, exit_code);
		// 자식 프로세스가 종료 상태코드 1로 종료시 부모 프로세스의 waitpid에서 받아내는 종료상태값은 256이 될 것이다. 설명가능?
	}
	printf("process end\n");
	return (0);
}