/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 18:35:15 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/01 20:00:16 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char *argv[], char *envp[])
{
	struct stat	*buf;

	buf = malloc(sizeof(stat));
	if (!buf)
		return (0);
	if (stat("../cmd", buf) < 0)
		printf("stat error : %s\n", strerror(errno));
	else if (S_ISREG(buf->st_mode))
	{
		printf("file: normal file\n");
		execve("./test", argv, envp);
	}
	else if (S_ISDIR(buf->st_mode))
	{
		printf("directory\n");
	}
}
