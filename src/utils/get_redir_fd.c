/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 23:37:57 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/05 14:49:00 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd.h"

t_token	*get_redir_node(t_token *input)
{
	t_token	*node_temp;

	node_temp = input;
	if (!node_temp)
		return (NULL);
	while (node_temp && node_temp->type != CMD && node_temp->type != REDIRECT)
		node_temp = node_temp->next;
	if (!node_temp || node_temp->type == CMD)
		return (NULL);
	return (node_temp);
}

int	get_redir_ifd(t_token *input);

int	get_redir_ofd(t_token *input)
{
	char	*filename;
	int		fd;
	t_token	*node;

	fd = STDOUT_FILENO;
	node = get_redir_node(input);
	if (!node)
		return (fd);
	if (!node->next || node->next->type != FILEPATH)
	{
		ft_putstr_fd("shell: redirection parse error\n", 2);
		return (-1);
	}
	filename = input->next->content;
	if (ft_strequel(input->content, ">"))
		fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	else if (ft_strequel(input->content, ">>"))
		fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0777);
	if (fd < 0)
	{
		ft_putstr_fd("shell: redirection parse error\n", 2);
		return (-1);
	}
	return (fd);
}
