/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:24:46 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/10 18:33:58 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	exec_envlen(t_data *data)
{
	t_envlst	*env_start;
	int			length;

	env_start = data->envlst;
	length = 0;
	while (env_start)
	{
		if (env_start->env_state == ENV)
			length++;
		env_start = env_start->next;
	}
	return (length);
}

static char	*exec_joinenv(t_envlst *env)
{
	char	*strtmp;
	char	*str_to_return;

	strtmp = ft_strjoin(env->key, "=");
	if (!strtmp)
		return (NULL);
	str_to_return = ft_strjoin(strtmp, env->value);
	if (!str_to_return)
	{
		free(strtmp);
		return (NULL);
	}
	free(strtmp);
	return (str_to_return);
}

char	**exec_getenvp(t_data *data)
{
	int			len;
	t_envlst	*env_tmp;
	char		**envp_return;
	int			i;

	len = exec_envlen(data);
	envp_return = malloc(sizeof(char *) * (len + 1));
	if (!envp_return)
		return (NULL);
	i = 0;
	env_tmp = data->envlst;
	while (i < len)
	{
		if (env_tmp->env_state == ENV)
		{
			envp_return[i] = exec_joinenv(env_tmp);
			if (!envp_return[i])
				return (ft_free_char2d(envp_return), NULL);
			i++;
		}
		env_tmp = env_tmp->next;
	}
	envp_return[i] = NULL;
	return (envp_return);
}
