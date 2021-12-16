/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 23:07:21 by jekim             #+#    #+#             */
/*   Updated: 2021/12/16 10:23:22 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_token(t_data *data)
{
	int		lst_len;
	t_token	*lst;

	lst_len = 0;
	lst = data->input->next;
	while (lst)
	{
		trs(lst->content);
        tri((int)ft_strlen(lst->content));
		tri(lst->ix);
		trs(catch_lst_type(lst->type));
		lst = lst->next;
		lst_len++;
	}
	tri(lst_len);
}

void    leakcheck(void)
{
    system("leaks minishell");
}

void print_int_checker(int *checker, int len)
{
	int ix = -1;
	while (++ix < len - 1)
		printf("%d", checker[ix]);
	printf("%d\n", checker[ix]);	
}