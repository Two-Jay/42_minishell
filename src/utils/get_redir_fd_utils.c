/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir_fd_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 20:05:42 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/19 20:17:24 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ifd_if_condition(t_token *input, int fd)
{
	t_token	*temp;

	if (input->next->next && input->next->next->type == REDIRECT)
	{
		temp = input->next->next;
		if (ft_strequel(temp->content, "<") || ft_strequel(temp->content, "<<"))
			if (fd != STDOUT_FILENO && fd != STDIN_FILENO)
				return (1);
	}
	return (0);
}

int	ofd_if_condition(t_token *input, int fd)
{
	t_token	*temp;

	if (input->next->next && input->next->next->type == REDIRECT)
	{
		temp = input->next->next;
		if (ft_strequel(temp->content, ">") || ft_strequel(temp->content, ">>"))
			if (fd != STDOUT_FILENO && fd != STDIN_FILENO)
				return (1);
	}
	return (0);
}

int	ifd_equal_str(char *str)
{
	if (ft_strequel(str, "<") || ft_strequel(str, "<<"))
		return (1);
	return (0);
}

int	ofd_equal_str(char *str)
{
	if (ft_strequel(str, ">") || ft_strequel(str, ">>"))
		return (1);
	return (0);
}
