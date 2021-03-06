/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:07:53 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/05 17:05:44 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_envlst	*find_env(char *envname, t_data *data)
{
	t_envlst	*node_env;

	node_env = data->envlst;
	while (node_env)
	{
		if (ft_strequel(envname, node_env->key))
			return (node_env);
		node_env = node_env->next;
	}
	return (NULL);
}

char	*get_env(char *envname, t_data *data)
{
	t_envlst	*node_env;
	char		*var;

	node_env = find_env(envname, data);
	if (!node_env)
		return (NULL);
	var = ft_strdup(node_env->value);
	return (var);
}
