/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 02:33:47 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/07 18:31:56 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_shlvl(t_data *data)
{
	t_envlst	*shlvl;
	int			shlvl_n;
	char		*shlvl_s;

	shlvl = find_env("SHLVL", data);
	if (!shlvl)
		return ;
	shlvl_n = ft_atoi(shlvl->value);
	shlvl_n++;
	shlvl_s = ft_itoa(shlvl_n);
	save_env(data, ft_strdup("SHLVL"), shlvl_s, ENV);
}
