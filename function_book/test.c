/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 14:52:08 by jekim             #+#    #+#             */
/*   Updated: 2021/09/27 21:31:54 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int main(void)
{
	char *str;

	while (1)
	{
		// readline은 입력받은 문자열을 \n을 포함하여 반환한다. 빈 문자열 입력시 \n을 반환함.
		str = readline(NULL);
		if (str)
			printf("%s\n", str);
		else
			break ;
		// readline 을 실행하여 리턴되는 라인은 malloc을 이용하여 메모리가 할당된 상태로 리턴된다.
		// 누수를 방지하기 위해, free를 해주어야 한다.
		rl_on_new_line();
		add_history(str);
		free(str);
	}
	return (system("leaks a"));
}