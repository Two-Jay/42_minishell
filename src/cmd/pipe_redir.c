/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 18:45:39 by jiychoi           #+#    #+#             */
/*   Updated: 2021/10/09 21:50:02 by jiychoi          ###   ########.fr       */
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

char	**pipe_getcmd(char *cmd, char *flag, char *envp[])
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

int	pipe_child(t_pipe_arr *s_pipe, int fd, int index)
{
	char	*cmd_path;
	char	*exec_argv[3];

	if (!s_pipe->cmd[index] || !s_pipe->flags[index] || !s_pipe->str[index])
		exit(1);
	cmd_path = pipe_getcmd(s_pipe->cmd[index],
			s_pipe->flags[index], s_pipe->envp);
	exec_argv[0] = cmd_path;
	exec_argv[1] = s_pipe->flags[index];
	exec_argv[2] = s_pipe->str[index];
	dup2(fd, STDOUT_FILENO);
	execve(cmd_path, exec_argv, s_pipe->envp);
}

int	pipe_parent(int fd)
{
	dup2(fd, STDIN_FILENO);

}

t_pipe_arr	*pipe_struct(char *cmd[], char *flags[], char *envp[])
{
	t_pipe_arr	*struct_pipe;

	struct_pipe = malloc(sizeof(t_pipe_arr));
	if (!struct_pipe)
		return (0);
	struct_pipe->cmd = cmd;
	struct_pipe->flags = flags;
	struct_pipe->envp = envp;
	return (struct_pipe);
}

int	minishell_pipe(char *cmd[], char *param[], char *envp[])
{
	int			pipe_pid;
	int			stat_loc;
	t_pipe_arr	*struct_pipe;
	int			fd[2];

	if (!cmd || !param)
		return (0);
	struct_pipe = pipe_struct(cmd, param, envp);
	if (!struct_pipe || pipe(fd) < 0)
		return (0);
	pipe_pid = fork();
	if (!pipe_pid)
		pipe_child(struct_pipe, fd[1], 0);
	else if (pipe_pid > 0)
	{
		wait(&stat_loc);
	}
}

//테스트용 메인문
int	main(int argc, char *argv[], char *envp[])
{
	pid_t	pid;
	int		fd[2];
	char	*cmd

	path = pipe_getpath(envp);
	ft_free_char2d(path);
	system("leaks a.out");
}
