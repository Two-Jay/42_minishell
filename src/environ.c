/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 17:30:17 by jekim             #+#    #+#             */
/*   Updated: 2021/12/16 01:32:15 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_envlst	*create_node_envlst(char *env_line)
{
	int			len;
	int			equel_idx;
	t_envlst	*tmp;

	tmp = (t_envlst *)ft_calloc(sizeof(t_envlst), 1);
	if (!tmp)
		exit(EXIT_FAILURE);
	len = ft_strlen(env_line);
	equel_idx = indexOf_char(env_line, '=');
	tmp->key = ft_substr(env_line, 0, equel_idx);
	tmp->value = ft_substr(env_line, equel_idx + 1, len - equel_idx);
	return (tmp);
}

int	init_env(char **envp, t_data *data)
{
	int			ix;
	t_envlst	*nptr;

	ix = 0;
	data->envlst = create_node_envlst(envp[ix]);
	nptr = data->envlst;
	while (envp[++ix])
	{
		nptr->next = create_node_envlst(envp[ix]);
		nptr = nptr->next;
	}
	nptr->next = NULL;
	return (0);
}
