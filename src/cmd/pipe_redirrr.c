/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redirrr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 18:45:39 by jiychoi           #+#    #+#             */
/*   Updated: 2021/10/10 15:34:02 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd.h"

void	pipe_execute(t_pipe_arr *s_pipe, int fd, int index)
{
	char	*cmd_path;
	char	*exec_argv[3];

	cmd_path = pipe_getcmd(s_pipe->cmd[index],
			s_pipe->flags[index], s_pipe->envp);
	if (!cmd_path)
		return ;
	exec_argv[0] = cmd_path;
	exec_argv[1] = s_pipe->flags[index];
	exec_argv[2] = s_pipe->str[index];
	dup2(fd, STDOUT_FILENO);
	close(fd);
	execve(cmd_path, exec_argv, s_pipe->envp);
}

int	pipe_child(t_pipe_arr *s_pipe, int fd, int index)
{
	int	fd_child[2];
	int	pipe_pid;
	int	stat_loc;

	if (!s_pipe->cmd[index + 1]
		|| !s_pipe->flags[index + 1] || !s_pipe->str[index + 1])
		pipe_execute(s_pipe, fd, index);
	else
	{
		if (pipe(fd_child) < 0)
			return (0);
		pipe_pid = fork();
		if (!pipe_pid)
			pipe_child(s_pipe, fd_child[1], index + 1);
		else if (pipe_pid > 0)
		{
			wait(&stat_loc);
			dup2(fd_child[0], STDIN_FILENO);
			dup2(fd, STDOUT_FILENO);
			close(fd_child[0]);
			close(fd);
		}
	}
	dup2(fd, STDOUT_FILENO);
}

int	pipe_parent(int fd)
{

}

t_pipe_arr	*pipe_struct(char *cmd[], char *flags[], char *envp[], int if_redir)
{
	t_pipe_arr	*struct_pipe;

	struct_pipe = malloc(sizeof(t_pipe_arr));
	if (!struct_pipe)
		return (0);
	struct_pipe->cmd = cmd;
	struct_pipe->flags = flags;
	struct_pipe->envp = envp;
	struct_pipe->index = 0;
	struct_pipe->if_redir = if_redir;
	return (struct_pipe);
}

int	minishell_pipe(char *cmd[], char *param[], char *envp[], int if_redir)
{
	int			pipe_pid;
	int			stat_loc;
	t_pipe_arr	*struct_pipe;
	int			fd[2];

	if (!cmd || !param)
		return (0);
	struct_pipe = pipe_struct(cmd, param, envp, if_redir);
	if (!struct_pipe || pipe(fd) < 0)
		return (0);
	pipe_pid = fork();
	if (!pipe_pid)
		pipe_child(struct_pipe, fd[1], 0);
	else if (pipe_pid > 0)
	{
		dup2(fd, STDIN_FILENO);
		wait(&stat_loc);
	}
	free(struct_pipe);
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
