/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_temp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 19:14:38 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/05 19:15:20 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	del_temp(void)
{
	int			fd;
	struct stat	*buf;

	buf = NULL;
	if (!stat("temp", buf))
	{
		fd = open("temp", O_WRONLY | O_TRUNC | O_CREAT, 0777);
		close(fd);
		unlink("temp");
		free(buf);
	}
}
