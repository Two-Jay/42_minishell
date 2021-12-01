/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_getcmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:28:21 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/01 20:01:53 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*directory;

	if (argc != 2)
		return (0);
	directory = exec_getcmd(argv[1], envp);
	if (directory)
		printf("%s directory: %s\n", argv[1], directory);
	free(directory);
}
