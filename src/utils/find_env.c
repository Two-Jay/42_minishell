/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:07:53 by jiychoi           #+#    #+#             */
/*   Updated: 2021/10/12 13:35:01 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

static int	is_str_valid(char *src, char *dst)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(src);
	while (++i < len && src[i])
	{
		if (src[i] != dst[i])
			return (0);
	}
	if (!src[i] && dst[i])
		return (0);
	return (1);
}

static int	getenv_len(char *str)
{
	int	len;

	while (*str)
	{
		if (*str == '$')
		{
			while (*str != ' ' && *str != 0)
			{
				len++;
				str++;
			}
			break ;
		}
		str++;
	}
	return (len);
}

char	*get_env(char *str)
{
	int		len;
	int		i;
	char	*env_name;

	if (!str)
		return (0);
	len = getenv_len(str);
	env_name = malloc(sizeof(char) * len + 1);
	if (!env_name)
		return (0);
	i = 0;
	while (*str != ' ' && *str != 0)
	{
		env_name[i++] = *str;
		str++;
	}
	env_name[i] = 0;
	return (env_name);
}

//pseudo-code
t_envlst	*find_env(char *envname, t_data *data)
{
	t_envlst	*node_env;

	node_env = data->envlst;
	while (node_env)
	{
		if (is_str_valid(envname, node_env->key))
			return (node_env);
		node_env = node_env->next;
	}
	return (0);
}
