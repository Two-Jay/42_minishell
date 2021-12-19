/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 23:37:57 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/19 19:41:06 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	here_doc_child(char *limiter, int fd[2])
{
	char	*input;

	close(fd[PIPE_READ]);
	kill(0, SIGUSR1);
	while (1)
	{
		set_signal_handler_heredoc();
		input = readline("> ");
		if (!input)
			break ;
		if (ft_strequel(input, limiter))
		{
			free(input);
			break ;
		}
		ft_putstr_fd(input, fd[PIPE_WRITE]);
		ft_putstr_fd("\n", fd[PIPE_WRITE]);
		free(input);
	}
	exit(0);
}

static int	here_doc_readline(char *limiter)
{
	int		fd[2];
	int		pipe_pid;
	int		temp_status;

	if (pipe(fd) < 0)
		return (builtin_error("heredoc", ft_strdup(PIPE_ERR), 1));
	pipe_pid = fork();
	if (!pipe_pid)
		here_doc_child(limiter, fd);
	else if (pipe_pid < 0)
		return (builtin_error("heredoc", ft_strdup(PIPE_ERR), 1));
	close(fd[PIPE_WRITE]);
	waitpid(pipe_pid, &temp_status, 0);
	if (WEXITSTATUS(temp_status))
	{
		close(fd[PIPE_READ]);
		if (pipe(fd) < 0)
			return (builtin_error("heredoc", ft_strdup(PIPE_ERR), 1));
		g_dq = 1;
		close(fd[PIPE_WRITE]);
		return (-1);
	}
	return (fd[PIPE_READ]);
}

int	ifd_condition(t_token *input, char *str)
{
	int	fd;

	fd = STDIN_FILENO;
	if (ft_strequel(input->content, "<<"))
	{
		fd = here_doc_readline(str);
		if (fd < 0)
			return (-1);
		if (input->next->next && input->next->next->type == REDIRECT)
			if (fd != STDOUT_FILENO && fd != STDIN_FILENO)
				close(fd);
	}
	else if (ft_strequel(input->content, "<"))
	{
		fd = open(str, O_RDONLY);
		if (fd < 0)
			return (builtin_error("shell", ft_strjoin(str, EXEC_ERRNODIR), 1));
		if (input->next->next && input->next->next->type == REDIRECT)
			if (fd != STDOUT_FILENO && fd != STDIN_FILENO)
				close(fd);
	}
	return (fd);
}

int	get_redir_ifd(t_token *input)
{
	int			fd;

	fd = STDIN_FILENO;
	if (input->type == CMD)
		input = input->next;
	while (input && input->type != CMD && input->type != PIPE)
	{
		if (input->type == REDIRECT)
			fd = ifd_condition(input, input->next->content);
		input = input->next;
	}
	return (fd);
}

int	get_redir_ofd(t_token *input)
{
	char	*filename;
	int		fd;

	fd = STDOUT_FILENO;
	if (input->type == CMD)
		input = input->next;
	while (input && input->type != CMD && input->type != PIPE)
	{
		if (input->type == REDIRECT)
		{
			filename = input->next->content;
			if (ft_strequel(input->content, ">"))
				fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0777);
			else if (ft_strequel(input->content, ">>"))
				fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0777);
			if (fd < 0)
				return (builtin_error("shell", ft_strdup(PIPE_ERR), -1));
			if (input->next->next && input->next->next->type == REDIRECT)
				if (fd != STDOUT_FILENO && fd != STDIN_FILENO)
					close(fd);
		}
		input = input->next;
	}
	return (fd);
}
