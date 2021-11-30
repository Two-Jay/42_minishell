/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 18:58:39 by jiychoi           #+#    #+#             */
/*   Updated: 2021/11/30 19:43:10 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

static int	cmd_if_dir(char *path, char *cmd)
{
	struct stat	*buf;

	buf = malloc(sizeof(struct stat));
	if (!buf)
		return (-1);
	if (stat(path, buf) < 0)
	{
		free(buf);
		return (-1);
	}
	else if (S_ISDIR(buf->st_mode))
	{
		free(buf);
		builtin_error(cmd, ft_strjoin(cmd, EXEC_ERRDIR), 126);
		return (-1);
	}
	return (0);
}

static int	cmd_access(char *path)
{
	struct stat	*buf;

	buf = malloc(sizeof(struct stat));
	if (!buf)
		return (-1);
	if (stat(path, buf) < 0 || !S_ISREG(buf->st_mode))
	{
		free(buf);
		return (-1);
	}
	return (0);
}

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

static char	*if_relative(char *cmd)
{
	char	*cwd;
	char	*temp_slash;
	char	*temp_cmd;

	if (!cmd_access(cmd))
		return (cmd);
	if (cmd_if_dir(cmd, cmd))
		return (NULL);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	temp_slash = ft_strjoin(cwd, "/");
	if (!temp_slash)
		return (NULL);
	temp_cmd = ft_strjoin(temp_slash, cmd);
	if (!temp_cmd)
		return (NULL);
	free(temp_slash);
	if (!cmd_access(temp_cmd))
		return (temp_cmd);
	if (cmd_if_dir(temp_cmd, cmd))
		return (NULL);
	return (NULL);
}

char	*getcmd(char *cmd, char *envp[])
{
	int		i;
	char	**path;
	char	*temp_slash;
	char	*temp_cmd;

	i = -1;
	if (if_relative(cmd))
		return (cmd);
	path = getpath(envp);
	while (path[++i])
	{
		temp_slash = ft_strjoin(path[i], "/");
		if (!temp_slash)
			return (0);
		temp_cmd = ft_strjoin(temp_slash, cmd);
		if (!temp_cmd)
			return (0);
		free(temp_slash);
		if (!cmd_access(temp_cmd))
			break ;
	}
	if (!path[i])
		return (0);
	ft_free_char2d(path);
	return (temp_cmd);
}
