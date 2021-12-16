/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 18:58:39 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/16 16:11:06 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**getpath(t_data *data)
{
	int			i;
	char		**path;
	t_envlst	*env_found;

	i = -1;
	path = NULL;
	env_found = find_env("PATH", data);
	if (!env_found)
	{
		path = malloc(sizeof(char *) * 2);
		path[0] = ft_strdup(".");
		path[1] = NULL;
	}
	else
		path = ft_split(env_found->value, ':');
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

char	*exec_getcmd(t_data *data, char *cmd)
{
	char	**path;
	char	*cmd_path;

	cmd_path = if_file(cmd);
	if (cmd_path)
		return (cmd_path);
	path = getpath(data);
	if (!path)
		return (NULL);
	cmd_path = check_path(path, cmd);
	ft_free_char2d(path);
	if (cmd_path)
		return (cmd_path);
	if (!ft_strchr(cmd, '/'))
		g_dq = builtin_error("shell", ft_strjoin(cmd, EXEC_ERRNOCMD), 127);
	else if (cmd_access(cmd) == EXEC_ISDIR)
		g_dq = builtin_error("shell", ft_strjoin(cmd, EXEC_ERRDIR), 126);
	else
		g_dq = builtin_error("shell", ft_strjoin(cmd, EXEC_ERRNODIR), 127);
	return (NULL);
}
