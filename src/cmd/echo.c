/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:54:11 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/05 14:51:59 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd.h"

static int	echo_if_nnn(char *flag)
{
	if (*flag != '-')
		return (0);
	flag++;
	while (*flag)
	{
		if (*flag != 'n')
			return (0);
		flag++;
	}
	return (1);
}

static int	echo_noflag(t_token *tree, int fd)
{
	while (tree && tree->type != PIPE && tree->type != REDIRECT)
	{
		ft_putstr_fd(tree->content, fd);
		write(fd, " ", 1);
		tree = tree->next;
	}
	write(fd, "\n", 1);
	if (fd != STDOUT_FILENO)
		close(fd);
	return (0);
}

static int	echo_nflag(t_token *tree, int fd)
{
	while (tree && tree->type != PIPE && tree->type != REDIRECT)
	{
		ft_putstr_fd(tree->content, fd);
		write(fd, " ", 1);
		tree = tree->next;
	}
	if (fd != STDOUT_FILENO)
		close(fd);
	return (0);
}

int	minishell_echo(t_token *input)
{
	int		fd;

	input = input->next;
	fd = get_redir_ofd(input);
	if (fd < 0)
		return (1);
	if (input->type == FLAG && echo_if_nnn(input->content))
	{
		input = input->next;
		return (echo_nflag(input, fd));
	}
	else
		return (echo_noflag(input, fd));
}
