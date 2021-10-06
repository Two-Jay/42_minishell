/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 14:09:01 by jekim             #+#    #+#             */
/*   Updated: 2021/10/07 04:48:31 by jekim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <signal.h>
# include <termios.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "./parser.h"

# define INTRO "Nyamnyam_shell.dev '-'//"

typedef struct s_envlst
{
	char				*key;
	char				*value;
	struct	t_envlst	*next;
}	t_envlst;

typedef struct	s_data
{
	t_envlst	*envlst;
	t_token		*input;
}	t_data;

#endif