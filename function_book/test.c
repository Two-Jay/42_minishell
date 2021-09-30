/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 14:52:08 by jekim             #+#    #+#             */
/*   Updated: 2021/10/01 06:17:07 by jekim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define BUFF_SIZE 4096

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

int read_data(int fd, char *buffer, int buf_size)
{
	int size;
	int len;

	size = 0;
	while (1)
	{
		len = read(fd, &buffer[size], buf_size - size);
		if (len > 0)
		{
			size += len;
			if (size == buf_size)
				return (size);
		}
		else if (len == 0)
			return (size);
		else
			return (-1);
	}
}

int cat_txtfile(int fd)
{
	char	buf[BUFF_SIZE];
	int check;

	while (1)
	{
		check = read_data(fd, buf, BUFF_SIZE);
		if (check == -1)
		{
			printf("Error : read error - %s\n", strerror(errno));
			return (1);
		}
		else if (check == 0)
			return (0);
		else
			write(1, buf, check);
	}
}

int main(int argc, char *argv[])
{
	char	*target_file;
	int		fd;

	target_file = get_targetpath(argv[1]);
	fd = open(target_file, O_RDONLY, 0);
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
	cat_txtfile(fd);
	close(fd);
	free(target_file);
	return (0);
}
