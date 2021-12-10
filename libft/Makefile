# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/11 02:25:46 by jseo              #+#    #+#              #
#    Updated: 2021/12/11 00:27:37 by jekim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS			=	ft_isalnum.c ft_isprint.c ft_memcmp.c  ft_putchar_fd.c ft_split.c \
					ft_strlcat.c ft_strncmp.c ft_substr.c ft_atoi.c ft_isalpha.c \
					ft_itoa.c ft_memcpy.c  ft_putendl_fd.c ft_strchr.c  ft_strlcpy.c \
					ft_strnstr.c ft_tolower.c ft_bzero.c   ft_isascii.c ft_memccpy.c \
					ft_memmove.c ft_putnbr_fd.c  ft_strdup.c  ft_strlen.c  ft_strrchr.c \
					ft_toupper.c ft_calloc.c  ft_isdigit.c ft_memchr.c  ft_memset.c  \
					ft_putstr_fd.c  ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_strgnl.c	\
					ft_realloc.c ft_strnew.c ft_strerr.c ft_scalloc.c ft_atoi_covf.c	\
					ft_isspace.c ft_isoverflow.c ft_isable_strtonbr.c ft_strequel.c

OBJS			= $(SRCS:.c=.o)

BONUS			=	ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
					ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
					ft_lstmap.c ft_lstnew.c ft_lstsize.c
BONUS_OBJS		= $(BONUS:.c=.o)

PRINTF_DRC		= ./ft_printf/
PRINTF_SRCS		= $(PRINTF_DRC)ft_printf.c \
					$(PRINTF_DRC)ft_printf_checker.c \
					$(PRINTF_DRC)ft_printf_utils_1.c \
					$(PRINTF_DRC)ft_printf_utils_2.c \
					$(PRINTF_DRC)ft_write_addr_1.c \
					$(PRINTF_DRC)ft_write_addr_2.c \
					$(PRINTF_DRC)ft_write_nbr_1.c \
					$(PRINTF_DRC)ft_write_nbr_2.c \
					$(PRINTF_DRC)ft_write_c.c \
					$(PRINTF_DRC)ft_write_s.c

PRINTF_OBJS		= $(PRINTF_SRCS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I. -g3

NAME			= libft.a

all:			$(NAME)

$(NAME):		$(OBJS) $(BONUS_OBJS) $(PRINTF_OBJS)
				@ar rc $(NAME) $(OBJS) $(BONUS_OBJS) $(PRINTF_OBJS)
				@echo "\033[0;92m* $(NAME) was created *\033[0m"

%.o : %.c
	@$(CC) $(CFLAGS) $(INCLUDE) $< -c -o $@

clean:
				@$(RM) $(OBJS) $(BONUS_OBJS) $(PRINTF_OBJS)

fclean:			clean
				@$(RM) $(NAME)
				@echo "\033[0;91m* $(NAME) was removed *\033[0m"

re:				fclean $(NAME)

.PHONY:			all clean fclean re bonus

