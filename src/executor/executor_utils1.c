/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 18:58:39 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/04 14:42:01 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

static char	**getpath(char *envp[])
{
	int		i;
	char	**path;
	char	*temp;

	i = -1;
	path = NULL;
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

static char	*check_path(char **path, char *cmd)
{
	int		i;
	char	*temp_slash;
	char	*temp_cmd;

	i = -1;
	while (path[++i])
	{
		temp_slash = ft_strjoin(path[i], "/");
		if (!temp_slash)
			return (NULL);
		temp_cmd = ft_strjoin(temp_slash, cmd);
		free(temp_slash);
		if (!temp_cmd)
			return (NULL);
		if (!cmd_access(temp_cmd))
			break ;
		free(temp_cmd);
	}
	if (!path[i])
		return (NULL);
	return (temp_cmd);
}

char	*exec_getcmd(char *cmd, char *envp[])
{
	char	**path;
	char	*cmd_path;

	cmd_path = if_file(cmd);
	if (cmd_path)
		return (cmd_path);
	path = getpath(envp);
	if (!path)
		return (NULL);
	cmd_path = check_path(path, cmd);
	ft_free_char2d(path);
	if (cmd_path)
		return (cmd_path);
	if (!ft_strchr(cmd, '/'))
		child_error("shell", ft_strjoin(cmd, EXEC_ERRNOCMD), 127);
	else if (cmd_access(cmd) == EXEC_ISDIR)
		child_error("shell", ft_strjoin(cmd, EXEC_ERRDIR), 126);
	else
		child_error("shell", ft_strjoin(cmd, EXEC_ERRNODIR), 127);
	return (NULL);
}
