/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 19:59:33 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/05 14:06:45 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd.h"

static int	pwd_getpwd(t_token *input)
{
	char	*pwd;
	int		fd;

	fd = get_redir_fd(input);
	if (fd < 0)
		return (1);
	pwd = getcwd(0, 10);
	if (!pwd)
		return (builtin_error("shell: pwd", ft_strdup(PWD_ERRFAIL), 1));
	ft_putstr_fd(pwd, fd);
	write(fd, "\n", 1);
	free(pwd);
	if (fd != STDOUT_FILENO)
		close(fd);
	return (0);
}

int	minishell_pwd(t_token *input)
{
	if (input->next
		&& (input->next->type != REDIRECT && input->next->type != PIPE))
		return (builtin_error("shell: pwd",
				ft_strjoin(input->next->content, PWD_ERROPT), 1));
	return (pwd_getpwd(input->next));
}
