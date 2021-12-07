/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 11:00:36 by jekim             #+#    #+#             */
/*   Updated: 2021/12/07 19:01:01 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include "structure.h"
# include "headers.h"

# define MSG_SIGQUIT "Quit: 3"

int set_signal_handler(void);
int set_signal_attr(void);

#endif
