/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 14:52:08 by jekim             #+#    #+#             */
/*   Updated: 2021/10/01 03:30:10 by jekim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define BUFF_SIZE 1024

char	*get_targetpath(const char *file_name)
{
	char	*current_dir;
	char	*ret;
	size_t	cdir_l;
	size_t	fn_l;
	int		ix;

	if (!file_name)
		return (NULL);
	current_dir = getcwd(NULL, 0);
	cdir_l = strlen(current_dir);
	fn_l = strlen(file_name);
	ret = (char *)malloc(sizeof(char) * ((int)cdir_l + (int)fn_l + 2));
	ix = 0;
	while (ix < cdir_l)
		ret[ix++] = *current_dir++;
	ret[ix] = '/';
	ix = 0;
	while (ix < fn_l)
		ret[cdir_l + ix++ + 1] = *file_name++;
	ret[cdir_l + ix + 1] = '\0';
	free(current_dir - cdir_l);
	return (ret);
}

int ft_strequel(char *s1, char *s2)
{
	int ix;

	ix = 0;
	while (s1[ix] && s2[ix])
	{
		if (s1[ix] != s2[ix])
			return (0);
		ix++;
	}
	return (1);
}

int is_txtfile(char *file_name)
{
	int		ix;
	size_t	fn_l;

	fn_l = strlen(file_name);
	ix = fn_l - 4;
	if (!ft_strequel(file_name + ix, ".txt"))
		return (0);
	return (1);
}

int cat_text(int fd)
{
	char	buf[BUFF_SIZE + 1];
	int		checker;

	while (1)
	{
		checker = read(fd, buf, BUFF_SIZE);
		if (checker <= 0)
			return (0);
		write(1, buf, checker);
	}
	return (1);
}

int main(int argc, char *argv[])
{
	char	*target_file;
	int		fd;

	target_file = get_targetpath(argv[1]);
	fd = open(target_file, O_WRONLY, 0);
	if (fd == -1)
	{
		printf("Error : %s\n", strerror(errno));
		exit(errno);
	}
	if (!is_txtfile(argv[1]))
	{
		printf("Error : this is not txt file.\n");
		exit(errno);
	}
	cat_text(fd);
	close(fd);
	free(target_file);
	return (0);
}
