/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_chdir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 22:02:20 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/02 16:08:06 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	main(void)
{
	char	*def;
	char	*cwd;

	def = getcwd(0, 100);
	printf("default directory: %s\n", def);
	chdir("test");
	cwd = getcwd(0, 100);
	printf("now: %s\n", cwd);
	free(cwd);
}
