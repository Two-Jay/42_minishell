/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 23:41:52 by jekim             #+#    #+#             */
/*   Updated: 2021/07/28 02:52:49 by jekim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_word(const char *src, char c)
{
	unsigned int	count;

	count = 0;
	while (*src)
	{
		if (*src != c && *(src + 1) == c)
			count++;
		if (*src != c && !*(src + 1))
			count++;
		src++;
	}
	return (count);
}

static int	ft_wordlen(const char *src, char c)
{
	unsigned int	len;

	len = 0;
	while (*src != c && *src)
	{
		len++;
		src++;
	}
	return (len);
}

static void	ft_free_error(char **bucket, unsigned int count)
{
	unsigned int	ix;

	ix = 0;
	while (ix < count)
	{
		free(bucket[ix]);
		ix++;
	}
	free(bucket);
}

static char	**ft_fillbucket(const char *src, unsigned int count,
		char c, char **bucket)
{
	unsigned int	ix;
	unsigned int	jx;
	unsigned int	len;

	ix = 0;
	while (ix < count)
	{
		while (*src == c)
			src++;
		len = ft_wordlen(src, c);
		bucket[ix] = (char *)malloc(sizeof(char) * (len + 1));
		if (!bucket)
		{
			ft_free_error(bucket, ix);
			return (NULL);
		}
		jx = 0;
		while (jx < len)
			bucket[ix][jx++] = *(src++);
		bucket[ix][jx] = '\0';
		ix++;
	}
	bucket[ix] = NULL;
	return (bucket);
}

char	**ft_split(const char *src, char c)
{
	char			**bucket;
	unsigned int	count;
	int				ix;

	if (!src)
		return (NULL);
	count = ft_count_word(src, c);
	bucket = (char **)malloc(sizeof(char *) * (count + 1));
	if (!bucket)
		return (NULL);
	bucket = ft_fillbucket(src, count, c, bucket);
	return (bucket);
}
