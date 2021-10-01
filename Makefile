# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jekim <arabi1549@naver.com>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/29 16:43:27 by jekim             #+#    #+#              #
#    Updated: 2021/10/01 16:10:31 by jekim            ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

CC			=	gcc
CCFLAG		=	-Wall -Wextra -Werror
LIBFLAG		=	-L$(LIBFT_DIR) -lft -lreadline 
G			=	-g
INCLUDE		=	-I$(INC_DIR) -I$(LIBFT_DIR)

OBJ_DIR		=	./obj/
SRC_DIR		=	./src/
INC_DIR		=	./includes/
LIBFT_DIR	=	./libft/

SRC_FILE		=	minishell.c

OBJ_FILE	=	$(SRC_FILE:.c=.o)
OBJ			=	$(addprefix $(OBJ_DIR), $(OBJ_FILE))

all			:	$(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(G) $(CCFLAG)$(INCLUDE) $< -c -o $@

$(NAME)		:	$(OBJ)
	@$(MAKE) -C ./libft
	@$(CC) $(G) $(CCFLAG) $(OBJ) $(LIBFLAG) $(INCLUDE) -o $@
	@echo "\033[0;92m* $(NAME) program file was created *\033[0m"

clean		:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C ./libft clean
	@echo "\033[0;91m* $(NAME)'s object files were removed* \033[0m"


fclean		:	clean
	@rm -f $(NAME)
	@$(MAKE) -C ./libft fclean
	@echo "\033[0;91m* $(NAME) were removed* \033[0m"


re			:	fclean all

.PHONY: all, clean, fclean, re