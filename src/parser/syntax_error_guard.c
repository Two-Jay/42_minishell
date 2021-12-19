/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_guard.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 18:56:16 by jekim             #+#    #+#             */
/*   Updated: 2021/12/19 22:42:35 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_cnt_redirection_and_filepath(t_token *token)
{
	t_token	*tknp;
	int		cnt_redirect;
	int		cnt_filepath;

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
				PSR_ERRHEAD,
				ft_strjoin(PSR_ERRSYNTAX, "'newline'")));
	return (0);
}

int	check_consecutive_pipes(t_token *token)
{
	t_token	*tknp;
	t_token	*tmp;
	int		cnt_pipe;

	tknp = token;
	cnt_pipe = 0;
	while (tknp)
	{
		if (cnt_pipe >= 2)
			return (print_syntax_error(
					PSR_ERRHEAD,
					ft_strjoin(PSR_ERRSYNTAX, tmp->content)));
		if (tknp->type == PIPE)
		{
			cnt_pipe++;
			tmp = tknp;
		}
		else
			cnt_pipe = 0;
		tknp = tknp->next;
	}
	return (0);
}

int	check_no_cmd_between_pipes(t_token *token)
{
	t_token	*tknp;
	int		cnt_cmd;
	int		err_flag;

	cnt_cmd = 0;
	err_flag = 0;
	tknp = token;
	while (tknp->next)
	{
		printf("token: %s\n", tknp->content);
		if (cnt_cmd == 0 && tknp->type == PIPE)
		{
			err_flag = 1;
			break ;
		}
		if (tknp->type == PIPE)
			cnt_cmd = 0;
		if (tknp->type == CMD)
			cnt_cmd++;
		tknp = tknp->next;
	}
	if (tknp->type == PIPE || err_flag)
		return (print_syntax_error(PSR_ERRHEAD,
				ft_strjoin(PSR_ERRSYNTAX, tknp->content)));
	return (0);
}

int	guard_syntax_error(t_token *token)
{
	if (check_cnt_redirection_and_filepath(token)
		|| check_consecutive_pipes(token)
		|| check_no_cmd_between_pipes(token))
		return (ERROR_OCCURED);
	return (0);
}
