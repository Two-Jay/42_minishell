/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 14:52:08 by jekim             #+#    #+#             */
/*   Updated: 2021/09/29 19:52:38 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

int fn_strerr(char *errm, size_t errm_len)
{
	write(2, errm, errm_len);
	exit(EXIT_FAILURE);
}

// 실행하면 현재 dir을 출력하고
// 현재 dir 스트림을 연 다음에
// readdir 을 이용해서 현재 디렉토리에 있는 파일 이름을 하나씩 전개한다.
int main(void)
{
	char			*currentdir;
	DIR				*dirstr;
	struct dirent	*dir_entry;

	currentdir = getcwd(NULL, 0);
	if (!currentdir)
		fn_strerr("Error : malloc failed\n", 23);
	dirstr = opendir(currentdir);
	if (dirstr != NULL)
	{
		dir_entry = readdir(dirstr);
		while(dir_entry != NULL)
		{
			printf("%s\n", dir_entry->d_name);
			dir_entry = readdir(dirstr);
		}
		closedir(dirstr);
	}
	free(currentdir);
	return (0);
}