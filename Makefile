# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jekim <arabi1549@naver.com>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/29 16:43:27 by jekim             #+#    #+#              #
#    Updated: 2021/10/11 14:47:00 by jekim            ###   ########.fr        #
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
UTILS_DIR	= 	./src/utils/
PARSER_DIR	=	./src/parser/
CMD_DIR		=	./src/cmd/
INC_DIR		=	./includes/
LIBFT_DIR	=	./libft/

SRC_FILE		=	minishell.c \
					env.c

PARSER_FILE 	=	parser_preprocess.c

UTILS_FILE		=	utils.c

CMD_FILE		=	exit.c

MAIN_OBJ_FILE	=	$(SRC_FILE:.c=.o)
PARSER_OBJ_FILE	=	$(PARSER_FILE:.c=.o)
UTILS_OBJ_FILE	=	$(UTILS_FILE:.c=.o)
CMD_OBJ_FILE	=	$(CMD_FILE:.c=.o)

MAIN_OBJ		=	$(addprefix $(OBJ_DIR), $(MAIN_OBJ_FILE))
PARSER_OBJ		=	$(addprefix $(OBJ_DIR), $(PARSER_OBJ_FILE))
UTILS_OBJ		=	$(addprefix $(OBJ_DIR), $(UTILS_OBJ_FILE))
CMD_OBJ			=	$(addprefix $(OBJ_DIR), $(CMD_OBJ_FILE))

OBJ				= 	$(MAIN_OBJ)	\
					$(PARSER_OBJ)	\
					$(UTILS_OBJ)	\
					$(CMD_OBJ)

all			:	$(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(G) $(CCFLAG) $(INCLUDE) $< -c -o $@

$(OBJ_DIR)%.o : $(PARSER_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(G) $(CCFLAG) $(INCLUDE) $< -c -o $@

$(OBJ_DIR)%.o : $(UTILS_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(G) $(CCFLAG) $(INCLUDE) $< -c -o $@

$(OBJ_DIR)%.o : $(CMD_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(G) $(CCFLAG) $(INCLUDE) $< -c -o $@

$(NAME)		:	$(OBJ)
	@$(MAKE) -C ./libft
	$(CC) $(G) $(CCFLAG) $(OBJ) $(LIBFLAG) $(INCLUDE) -o $@
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