/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 19:59:33 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/04 14:55:15 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

int	minishell_pwd(t_token *input)
{
	char	*pwd;
	int		fd;

	if (input->next
		&& (input->next->type != REDIRECT && input->next->type != PIPE))
		return (builtin_error("shell: pwd",
				ft_strjoin(input->next->content, PWD_ERROPT), 1));
	fd = get_redir_fd(input);
	if (fd < 0)
		return (1);
	pwd = getcwd(0, 10);
	if (!pwd)
		return (builtin_error("shell: pwd", ft_strdup(PWD_ERRFAIL), 1));
	ft_putstr_fd(pwd, fd);
	write(fd, "\n", 1);
	free(pwd);
	return (0);
}
