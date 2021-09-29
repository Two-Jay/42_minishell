/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 14:52:08 by jekim             #+#    #+#             */
/*   Updated: 2021/09/29 02:09:27 by jekim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
//printf
#include <stdio.h>
//exit
#include <stdlib.h>
//for definition of pid_t
#include <sys/types.h>


int main(void)
{
	pid_t pid;

	// 이런 식으로 fork를 실행하면, 해당 pid가 -1, 0, 0 < pid 인지 체크해서
	// 각 프로세스 별로 어떻게 동작할 지 구성할 수 있다.
	pid = fork();
	if (pid == -1)
	{
		// 에러, fork() 실패
		printf("error!");
		exit(1);
		return (0);
	}
	else if (pid == 0)
	{
		// 자식 프로세스에서는 fork() 가 0을 리턴한다.
		// 즉 이 부분은 자식 프로세스에서 실행되는 영역이다.
		printf("Child : My pid is %d, and i'm a child of %d\n",
			(int)getpid(),
			(int)getppid());
	}
	else
	{
		// pid 가 임의의 양수 (fork()로 생성된 자식 프로세스의 pid)라면
		// fork()를 성공적으로 호출한 부모 프로세스에 이 부분이 실행된다.
		printf("Parent : My pid is %d, and i'm a child of %d\n and My child is %d\n",
			(int)getpid(),
			(int)getppid(),
			(int)pid);
	}
	printf("process end\n");
	return (0);
}