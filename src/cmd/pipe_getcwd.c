/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_getcwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 00:21:47 by jiychoi           #+#    #+#             */
/*   Updated: 2021/11/27 00:23:16 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd.h"

void	ft_free_char2d(char **arr)
{
	int	index;

	index = 0;
	while (arr[index])
		free(arr[index++]);
	free(arr);
}

static char	**pipe_getpath(char *envp[])
{
	int		i;
	char	**path;
	char	*temp;

	i = -1;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			temp = envp[i] + 5;
			path = ft_split(temp, ':');
			break ;
		}
	}
	return (path);
}

char	*pipe_getcmd(char *cmd, char *envp[])
{
	int		i;
	char	**path;
	char	*temp_slash;
	char	*temp_cmd;

	i = -1;
	path = pipe_getpath(envp);
	while (path[++i])
	{
		temp_slash = ft_strjoin(path[i], "/");
		if (!temp_slash)
			return (0);
		temp_cmd = ft_strjoin(temp_slash, cmd);
		if (!temp_cmd)
			return (0);
		free(temp_slash);
		if (!access(temp_cmd, 0))
			break ;
	}
	if (!path[i])
		return (0);
	ft_free_char2d(path);
	return (temp_cmd);
}
