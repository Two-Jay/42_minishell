/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 11:00:36 by jekim             #+#    #+#             */
/*   Updated: 2021/12/18 18:46:31 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "structure.h"
# include "headers.h"

void	set_signal_handler_default(void);
void	set_signal_handler_blocked_cmd(void);
void	set_signal_handler_heredoc(void);
void	set_signal_handler_ignore();

void	signal_handler_default_SIGINT(int signo);
void	signal_handler_blocked_cmd(int signo);
void	signal_handler_interrupt_heredoc(int signo);
void	init_signal(int signo);

void backup_termattr(struct termios *termattr);
void reset_termattr(struct termios *termattr);
void turnoff_echoctl_termattr(void);

#endif
