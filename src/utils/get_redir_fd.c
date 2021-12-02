/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 23:37:57 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/02 23:50:53 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

int	get_redir_fd(t_token *input)
{
	char	*filename;
	int		fd;

	fd = STDOUT_FILENO;
	if (input->type == CMD)
		input = input->next;
	while (input && input->type != CMD && input->type != REDIRECT)
		input = input->next;
	if (!input || input->type == CMD)
		return (fd);
	if (input->type == REDIRECT && input->next && input->next->type == FILEPATH)
	{
		filename = input->next->content;
		if (ft_strequel(input->content, ">"))
			fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0777);
		else if (ft_strequel(input->content, ">>"))
			fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0777);
		return (fd);
	}
	return (fd);
}
