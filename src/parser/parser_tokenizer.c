/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokenizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 14:48:48 by jekim             #+#    #+#             */
/*   Updated: 2021/10/12 21:47:07 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int get_split_buflen(char *buf)
{
	
}

int tokenize_input(char *buf, t_data *data)
{
	char **splited;

	if (split_inputbuf(splited, buf) || )
		return (ERROR_OCCURED);
	return (0);
}