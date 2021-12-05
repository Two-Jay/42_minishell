/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:04:53 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/05 16:51:06 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd.h"

static void	pipe_child(
		t_data *data, t_token *input, t_pipe *struct_pipe, int fd[2])
{
	if (dup2(struct_pipe->fd_tmp, STDIN_FILENO) < 0)
		exit(builtin_error("pipe", ft_strdup(PIPE_ERR), 1));
	if (struct_pipe->index + 1 < struct_pipe->max_index)
		if (dup2(fd[PIPE_WRITE], STDOUT_FILENO) < 0)
			exit(builtin_error("pipe", ft_strdup(PIPE_ERR), 1));
	if (struct_pipe->fd_tmp != STDIN_FILENO)
		close(struct_pipe->fd_tmp);
	if (struct_pipe->index + 1 < struct_pipe->max_index)
		close(fd[PIPE_WRITE]);
	close(fd[PIPE_READ]);
	if (exec_builtin(data, input) == EXEC_NOTBUILTIN)
		exec_program(data, input, struct_pipe->envp);
}

static int	pipe_makepipe(t_data *data, t_token *input, t_pipe *struct_pipe)
{
	int	fd[2];
	int	pipe_pid;

	if (struct_pipe->index + 1 < struct_pipe->max_index)
		if (pipe(fd) < 0)
			return (-1);
	pipe_pid = fork();
	if (!pipe_pid)
		pipe_child(data, input, struct_pipe, fd);
	else if (pipe_pid < 0)
		return (-1);
	else
	{
		if (struct_pipe->fd_tmp != STDIN_FILENO)
			close(struct_pipe->fd_tmp);
		struct_pipe->fd_tmp = fd[PIPE_READ];
		close(fd[PIPE_WRITE]);
	}
	struct_pipe->last_pid = pipe_pid;
	return (struct_pipe->last_pid);
}

static void	pipe_wait(t_data *data, t_pipe *struct_pipe)
{
	int	status;
	int	status_save;
	int	wait_return_pid;

	while (1)
	{
		wait_return_pid = wait(&status);
		if (wait_return_pid == struct_pipe->last_pid)
			status_save = status;
		if (wait_return_pid < 0)
			return ;
	}
	data->dq = WEXITSTATUS(status_save);
	return ;
}

int	minishell_pipe(t_data *data, char *envp[])
{
	t_token		*input;
	t_pipe		*struct_pipe;

	input = data->input;
	struct_pipe = pipe_struct(input, envp);
	if (!struct_pipe)
		return (builtin_error("pipe", ft_strdup(PIPE_ERR), 1));
	while (struct_pipe->index < struct_pipe->max_index)
	{
		while (input->type != CMD && input)
			input = input->next;
		if (pipe_makepipe(data, input, struct_pipe) < 0)
			return (builtin_error("pipe", ft_strdup(PIPE_ERR), 1));
		input = input->next;
		struct_pipe->index++;
	}
	pipe_wait(data, struct_pipe);
	free(struct_pipe);
	return (free_token(data->input, 0));
}
