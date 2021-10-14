/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:07:53 by jiychoi           #+#    #+#             */
/*   Updated: 2021/10/14 20:34:33 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

static int	getenv_len(char *str)
{
	int	len;

	len = 0;
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

char	*get_envname(char *str)
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
		if (ft_strequel(envname, node_env->key))
			return (node_env);
		node_env = node_env->next;
	}
	return (0);
}

char *get_env(char *envname, t_data *data)
{
	t_envlst	*node_env;
	char		*var;
	int			varlen;

	node_env = find_env(envname, data);
	if (!node_env)
		return (NULL);
	varlen = ft_strlen(node_env->value);
	var = (char *)malloc(sizeof(char) * (varlen + 1));
	if (!var)
		return (NULL);
	var[varlen] = '\0';
	ft_memcpy(var, node_env->value, varlen);
	return (var);
}