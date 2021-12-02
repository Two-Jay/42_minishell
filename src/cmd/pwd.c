/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 19:59:33 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/03 00:16:23 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

int	minishell_pwd(t_data *data, t_token *input)
{
	char	*pwd;
	int		fd;

	fd = get_redir_fd(input);
	if (fd < 0)
		return (1);
	pwd = getcwd(0, 10);
	if (!pwd)
		return (builtin_error("pwd", ft_strdup(PWD_ERRFAIL), 1));
	ft_putstr_fd(pwd, fd);
	write(fd, "\n", 1);
	free(pwd);
	return (0);
}
