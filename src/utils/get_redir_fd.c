/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 23:37:57 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/05 19:01:02 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	here_doc_readline(char *limiter, int fd)
{
	char	*input;
	int		fd_rdonly;

	if (fd < 0)
		return (builtin_error("shell", ft_strdup(PIPE_ERR), -1));
	while (1)
	{
		input = readline("> ");
		if (ft_strequel(input, limiter))
		{
			free(input);
			break ;
		}
		ft_putstr_fd(input, fd);
	}
	close(fd);
	fd_rdonly = open("temp", O_RDONLY);
	if (fd_rdonly < 0)
		return (builtin_error("shell", ft_strdup(PIPE_ERR), -1));
	return (fd_rdonly);
}

int	ifd_condition(t_token *input, char *str)
{
	int	fd;

	fd = STDIN_FILENO;
	if (ft_strequel(input->content, "<<"))
	{
		fd = open("temp", O_WRONLY | O_APPEND | O_CREAT, 0777);
		fd = here_doc_readline(str, fd);
		if (fd < 0)
			return (-1);
		if (input->next->next && input->next->next->type == REDIRECT)
		{
			close(fd);
			unlink("temp");
		}
	}
	else if (ft_strequel(input->content, "<"))
	{
		fd = open(str, O_RDONLY);
		if (fd < 0)
			return (builtin_error("shell", ft_strjoin(str, EXEC_ERRNODIR), -1));
		if (input->next->next && input->next->next->type == REDIRECT)
			close(fd);
	}
	return (fd);
}

int	get_redir_ifd(t_token *input)
{
	int			fd;

	fd = STDIN_FILENO;
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
				close(fd);
		}
		input = input->next;
	}
	return (fd);
}
