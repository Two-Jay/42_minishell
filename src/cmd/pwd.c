/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 19:59:33 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/02 23:59:21 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

int	minishell_pwd(t_data *data, t_token *input)
{
	char	*pwd;
	int		fd;

	pwd = getcwd(0, 10);
	if (!pwd)
		return (builtin_error(data, "pwd", ft_strdup(PWD_ERRFAIL), 1));
	fd = get_redir_fd(input);
	ft_putstr_fd(pwd, fd);
	write(fd, "\n", 1);
	free(pwd);
	return (0);
}
