/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_guard_syntax.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 18:56:16 by jekim             #+#    #+#             */
/*   Updated: 2021/12/06 14:13:11 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_syntax_error(char *cmd, char *error_str, t_data *data)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error_str, 2);
	write(2, "\n", 1);
    data->dq = DQ_ERRSYNTAX;
	return (ERROR_OCCURED);
}

int	check_isclosed(const char *input, t_data *data)
{
	int	ix;
	int	flag;

	flag = 0;
	ix = -1;
	if (ft_strlen(input) == 1 && is_quotation(input, ix))
		return (print_syntax_error(
			"Shell ",
			ft_strjoin(PSR_ERRSYNTAX, "'unclosed quote'"),
			data));
	while (input[++ix])
        is_inquoted(input, ix, &flag);
	if (flag == 0)
		return (TRUE);
	return (print_syntax_error(
			"Shell ",
			ft_strjoin(PSR_ERRSYNTAX, "'unclosed quote'"),
			data));
}

int check_cnt_redirection_and_filepath(t_token *token, t_data *data)
{
    t_token *tknp;
    int     cnt_redirect;
    int     cnt_filepath;

    tknp = token;
    cnt_filepath = 0;
    cnt_redirect = 0;
    while (tknp)
    {
        if (tknp->type == FILEPATH)
            cnt_filepath++;
        if (tknp->type == REDIRECT)
            cnt_redirect++;
        tknp = tknp->next;
    }
    if ((cnt_redirect || cnt_filepath) && cnt_filepath != cnt_redirect)
        return (print_syntax_error(
            "Shell ",
            ft_strjoin(PSR_ERRSYNTAX, "'newline'"),
            data));
    return (0);
}

int check_consecutive_pipes(t_token *token, t_data *data)
{
    t_token *tknp;
    t_token *tmp;
    int     cnt_pipe;

    tknp = token;
    cnt_pipe = 0;
    while (tknp)
    {
        if (ft_strequel(tknp->content, "|"))
        {
            cnt_pipe++;
            tmp = tknp;
        }
        else
            cnt_pipe = 0;
        tknp = tknp->next;
    }
    if (cnt_pipe > 3)
        return (print_syntax_error(
            "Shell ",
            ft_strjoin(PSR_ERRSYNTAX, tmp->content),
            data));
    return (0);
}

int guard_syntax_error(t_token *token, t_data *data)
{
    if (check_cnt_redirection_and_filepath(token, data)
        || check_consecutive_pipes(token, data))
        return (ERROR_OCCURED);
    return (0);
}