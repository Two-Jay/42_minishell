/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 14:52:08 by jekim             #+#    #+#             */
/*   Updated: 2021/09/27 17:37:33 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int get_pwd()
{
	char *cwd;
	cwd = getcwd(NULL, 0);
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

int ft_strequel(char *s1, char *s2)
{
	int ix;

	ix = 0;
	while (s1[ix] && s2[ix])
	{
		if (s1[ix] != s2[ix])
			return (1);
		ix++;
	}
	return (0);
}

int main(void)
{
	char *str;

	while (1)
	{
		str = readline(NULL);
		if (!ft_strequel(str, "pwd"))
			get_pwd();
		else
			printf("%s\n", str);
        add_history(str);
		free(str);
	}
	return (system("leaks a"));
}