/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signalref.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 11:00:36 by jekim             #+#    #+#             */
/*   Updated: 2021/12/14 21:24:26 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALREF_H
# define SIGNALREF_H

# include "structure.h"
# include "headers.h"

void set_signal_handler_default(void);
void set_signal_handler_blocked_cmd(void);
void set_signal_handler_heredoc(void);
void    set_signal_handler_ignore(int signo);

#endif
