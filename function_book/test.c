/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 14:52:08 by jekim             #+#    #+#             */
/*   Updated: 2021/09/29 21:32:36 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int fn_strerr(char *errm, size_t errm_len)
{
	write(2, errm, errm_len);
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    struct stat file_info;
    char *str;
    int i;

	i = 1;
	while (i < argc)
	{
        if (lstat(argv[i], &file_info) < 0) {
            fn_strerr("lstat error\n", 14);
            continue;
        }
        if (S_ISREG(file_info.st_mode))
            str = "regular file";
        else if (S_ISDIR(file_info.st_mode))
            str = "directory";
        else
            str = "unknown";
        printf("name = %s, type = %s\n", argv[i], str);
		i++;
    }
	return (0);
}