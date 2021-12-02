/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 18:58:39 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/01 21:06:53 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

int	cmd_access(char *path)
{
	struct stat	*buf;

	buf = malloc(sizeof(struct stat));
	if (!buf)
		return (EXEC_NOTFILE);
	if (stat(path, buf) < 0)
	{
		free(buf);
		return (EXEC_NOTFILE);
	}
	if (!S_ISREG(buf->st_mode))
	{
		if (S_ISDIR(buf->st_mode))
		{
			free(buf);
			return (EXEC_ISDIR);
		}
		free(buf);
		return (EXEC_NOTFILE);
	}
	free(buf);
	return (EXEC_ISFILE);
}

char	*if_file(char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		if (cmd_access(cmd) == EXEC_ISFILE)
			return (cmd);
		else
			return (NULL);
	}
	return (NULL);
}
