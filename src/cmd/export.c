/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 13:34:23 by jiychoi           #+#    #+#             */
/*   Updated: 2021/10/16 17:53:14 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd.h"

static int	export_param_check(char *str)
{
	char	*ptr_equal;

	ptr_equal = str;
	while (*ptr_equal)
	{
		if (*ptr_equal == '=')
			break ;
		ptr_equal++;
	}
	if (ptr_equal)
	if (!ft_isalpha(*str) || *str != '_')
		return (0);
	str++;
	while (*str < *ptr_equal)
	{
		if (!ft_isalnum(*str) || *str != '_')
			return (0);
		str++;
	}
	return (1);
}

void	export_no_param(t_data *data)
{

}

void	export_with_param(t_data *data)
{
	char		**data_split;
	t_envlst	*env_node;

	data_split = ft_split(data->input->next->contents, '=');
	if (!data_split)
		return ;
	env_node = find_env(data_split[0]);
	if (env_node)
	{
		env_node->value = data_split[1];

	}

}

//void	minishell_export(t_data *data)
void	minishell_export(char *str)
{
	/*
	if (data->input->next == NULL)
		export_no_param(data);
	else
		export_with_param(data);
	*/
	if (export_param_check(str))
		printf("[%s] is valid env export parameter\n", str);
	else
		printf("[%s] is wrong parameter\n", str);
}

//테스트용 메인문 테스트용 메인문
int	main(int argc, char *argv[])
{
	if (argc != 2)
		return ;
	minishell_export(argv[1]);
}
//테스트용 메인문 테스트용 메인문
