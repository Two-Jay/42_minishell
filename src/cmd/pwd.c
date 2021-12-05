/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 19:59:33 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/06 02:02:43 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	pwd_getpwd(int ofd)
{
	char	*pwd;

	pwd = getcwd(0, 10);
	if (!pwd)
		return (builtin_error("shell: pwd", ft_strdup(PWD_ERRFAIL), 1));
	ft_putstr_fd(pwd, ofd);
	write(ofd, "\n", 1);
	free(pwd);
	return (0);
}

int	minishell_pwd(t_token *input, int ofd)
{
	if (input->next
		&& (input->next->type != REDIRECT && input->next->type != PIPE))
		return (builtin_error("shell: pwd",
				ft_strjoin(input->next->content, PWD_ERROPT), 1));
	return (pwd_getpwd(ofd));
}
