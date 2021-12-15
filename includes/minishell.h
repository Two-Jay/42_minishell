/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@42seoul.student.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 14:09:01 by jekim             #+#    #+#             */
/*   Updated: 2021/12/05 06:36:39 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "cmd.h"
# include "parser.h"
# include "signalref.h"

# define INTRO "||Nyamnyam_shell||"
# define PROMPT ">> :"
# define TRUE 0
# define FALSE 1
# define ERROR_OCCURED 1

int			g_dq;
extern int	g_dq;

# define DQ_ERRSYNTAX 258
# define DQ_SIGINT 130
# define DQ_SIGQUIT 131

#endif
