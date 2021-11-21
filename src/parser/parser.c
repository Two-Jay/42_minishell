/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:22:59 by jekim             #+#    #+#             */
/*   Updated: 2021/11/21 17:01:20 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int parse_input_string(const char *str, t_data *data)
{
    if (split_by_junk(str, data))
        return (ERROR_OCCURED);
    return (0);
}