/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:54:11 by jiychoi           #+#    #+#             */
/*   Updated: 2021/10/19 16:44:44 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

static int	echo_if_nnn(char *flag)
{
	if (*flag != '-')
		return (0);
	flag++;
	while (*flag)
	{
		if (*flag != 'n')
			return (0);
		flag++;
	}
	return (1);
}

static int	echo_noflag(t_token *tree)
{
	char	**str_to_print;
	int		i;

	str_to_print = trim_quote_and_parse(tree->content);
	if (!str_to_print)
		return (-1);
	i = -1;
	while (str_to_print[++i])
		ft_putstr_fd(str_to_print[i], 1);
	ft_free_char2d(str_to_print);
	write(1, "\n", 1);
	return (0);
}

static int	echo_nflag(t_token *tree)
{
	char	**str_to_print;
	int		i;

	str_to_print = trim_quote_and_parse(tree->content);
	if (!str_to_print)
		return (-1);
	i = -1;
	while (str_to_print[++i])
		ft_putstr_fd(str_to_print[i], 1);
	ft_free_char2d(str_to_print);
	return (0);
}

int	echo_iterate(t_data *data, t_token *tree, int (*echo_func)(t_token *))
{
	int		return_value;

	while (tree)
	{
		return_value = echo_func(tree);
		if (return_value < 0)
			return (return_value);
		tree = tree->next;
	}
	return (0);
}

int	minishell_echo(t_data *data)
{
	t_token	*tree;
	int		return_value;

	tree = data->input->next;
	if (echo_if_nnn(tree->content))
	{
		tree = tree->next;
		return (echo_iterate(data, tree, echo_nflag));
	}
	else
		return (echo_iterate(data, tree, echo_noflag));
}
