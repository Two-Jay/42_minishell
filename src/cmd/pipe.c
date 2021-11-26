/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:04:53 by jiychoi           #+#    #+#             */
/*   Updated: 2021/11/27 01:04:42 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

void	pipe_child(t_token *input, t_pipe *struct_pipe, int fd[2])
{
	char	*cmd_path;
	char	*exec_argv[4];

	if (dup2(struct_pipe->fd_tmp, STDIN_FILENO) < 0)
		exit(builtin_error("pipe", NULL, PIPE_ERR, 1));
	if (struct_pipe->index + 1 < struct_pipe->max_index)
		if (dup2(fd[PIPE_WRITE], STDOUT_FILENO) < 0)
			exit(builtin_error("pipe", NULL, PIPE_ERR, 1));
	if (struct_pipe->index + 1 == struct_pipe->max_index)
		close(fd[PIPE_WRITE]);
	//redirection needed
	close(fd[PIPE_READ]);
	close(struct_pipe->fd_tmp);
	cmd_path = pipe_getcmd(input->content, struct_pipe->envp);
	if (!cmd_path)
		exit(builtin_error("pipe", NULL, PIPE_ERR, 2));
}

int	pipe_makepipe(t_token *input, t_pipe *struct_pipe)
{
	int	fd[2];
	int	pipe_pid;

	if (struct_pipe->index + 1 < struct_pipe->max_index)
		if (pipe(fd) < 0)
			return (-1);
	pipe_pid = fork();
	if (!pipe_pid)
		pipe_child(input, struct_pipe, fd);
	else if (pipe_pid < 0)
		exit(builtin_error("pipe", NULL, PIPE_ERR, 1));
	else
	{
		if (struct_pipe->fd_tmp != STDIN_FILENO)
			close(struct_pipe->fd_tmp);
		struct_pipe->fd_tmp = fd[PIPE_READ];
		close(fd[PIPE_WRITE]);
	}
	return (struct_pipe->last_pid);
}

int	pipe_wait(t_pipe *struct_pipe, t_token *input)
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
		{
			builtin_error("pipe", NULL, PIPE_ERR, 1);
			return (free_token(input, -1));
		}
	}
	return (free_token(input, 0));
}

int	minishell_pipe(t_token *input, char *envp[])
{
	t_token		*input_backup;
	t_pipe	*struct_pipe;
	int			status_save;

	struct_pipe = pipe_struct(input, envp);
	if (!struct_pipe)
	{

		return (free_token(input_backup, -1));
	}
	input_backup = input;
	while (input)
	{
		while (input->type != CMD)
			input = input->next;
		if (pipe_makepipe(input, struct_pipe) < 0)
			return (free_token(input_backup, -1));
		struct_pipe->index++;
	}
	return (pipe_wait(struct_pipe, input_backup));
}

static int	pipe_count_param(t_token *input)
{
	int	count;

	count = 0;
	while (input->type != PIPE && input->type != REDIRECT && input)
	{
		input = input->next;
		count++;
	}
	return (count);
}

// Test Code for Pipe
int	main(int argc, char *argv[], char *envp[])
{
	t_token *input[10];

	for (int i = 0; i < 10; i++)
	{
		input[i] = malloc(sizeof(t_token));
		if (!input[i])
			return (0);
		input[i]->ix = i;
		if (i != 0)
		{
			input[i - 1]->next = input[i];
			input[i]->prev = input[i - 1];
		}
	}
	input[9]->next = NULL;
	input[0]->prev = NULL;
	input[0]->content = ft_strdup("ls");
	input[0]->type = CMD;
	input[1]->content = ft_strdup("|");
	input[1]->type = PIPE;
	input[2]->content = ft_strdup("cat");
	input[2]->type = CMD;
	input[3]->content = ft_strdup("-e");
	input[3]->type = FLAG;
	input[4]->content = ft_strdup("|");
	input[4]->type = PIPE;
	input[5]->content = ft_strdup("cat");
	input[5]->type = CMD;
	input[6]->content = ft_strdup("-e");
	input[6]->type = FLAG;
	input[7]->content = ft_strdup("|");
	input[7]->type = PIPE;
	input[8]->content = ft_strdup("cat");
	input[8]->type = CMD;
	input[9]->content = ft_strdup("-e");
	input[9]->type = FLAG;

	// Test
	//printf("%d\n", pipe_count_cmd(input[0])); //check if pipe_count_cmd works
	printf("%d\n", pipe_count_param(input[0])); //check if pipe_count_cmd works

	for (int i = 0; i < 10; i++)
	{
		free(input[i]->content);
		free(input[i]);
	}

}
