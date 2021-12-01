/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exitstatus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 21:01:17 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/01 21:03:44 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	int	pid;
	int	status;

	pid = fork();
	if (!pid)
	{
		printf("child process died. byebye..\n");
		exit(100);
	}
	else
	{
		waitpid(pid, &status, 0);
		printf("status : %d\n", WEXITSTATUS(status));
		return (0);
	}
}
