/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:54:11 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/03 00:11:58 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

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
	close(fd);
	return (0);
}

int	minishell_echo(t_token *input)
{
	t_token	*tree;
	int		fd;

	tree = input->next;
	fd = get_redir_fd(input);
	if (fd < 0)
		return (1);
	if (tree->type == FLAG && echo_if_nnn(tree->content))
	{
		tree = tree->next;
		return (echo_nflag(tree, fd));
	}
	else
		return (echo_noflag(tree, fd));
}
