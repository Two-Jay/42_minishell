/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 18:45:39 by jiychoi           #+#    #+#             */
/*   Updated: 2021/10/09 17:23:07 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd.h"

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

int	minishell_pipe(char *cmd[], char *param[], char *envp[])
{
	char	*cmd_path;

	cmd_path = pipe_getcmd(cmd, envp);
	if (!cmd_path)
	{
		ft_putstr_fd("Shell: command not found: ", 1);
		ft_putstr_fd(cmd, 1);
	}
}

/* (테스트용 메인문)
int	main(int argc, char *argv[], char *envp[])
{
	pid_t	pid;
	int		fd[2];
	char	*cmd

	path = pipe_getpath(envp);
	ft_free_char2d(path);
	system("leaks a.out");
	// printf("%d\n", getpid());
	// if (pipe(fd) < 0)
	// 	return (0);
	// pid = fork();
	// if (pid)
	// 	pipe_parent(fd[0]);
	// else
	// 	pipe_child(fd[1]);
}
*/
