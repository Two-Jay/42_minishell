# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/27 12:18:02 by jiychoi           #+#    #+#              #
#    Updated: 2021/12/02 18:42:21 by jiychoi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror
SRCS_PIPE		=	test_pipe.c\
					../cmd/pipe.c ../utils/getcmd.c ../cmd/pipe_utils.c\
					../utils/builtin_error.c ../utils/free_token.c ../utils/ft_free_char2d.c\
					../executor/executor.c ../executor/executor_utils1.c ../executor/executor_utils2.c
SRCS_CD			=	test_cd.c\
					../cmd/cd.c\
					../utils/builtin_error.c ../utils/find_env.c ../utils/check_flag.c\
					../utils/save_env.c ../utils/free_token.c ../../libft/ft_strequel.c
SRCS_ECHO		=	test_echo.c\
					../cmd/echo.c
#SRCS_ENV		=
#SRCS_EXIT		=
#SRCS_EXPORT	=
#SRCS_PWD		=
#SRCS_UNSET		=
#SRCS_EXEC	=
#SRCS			=

OBJS_PIPE		=	$(SRCS_PIPE:.c=.o)
OBJS_CD			=	$(SRCS_CD:.c=.o)
OBJS_ECHO		=	$(SRCS_ECHO:.c=.o)
OBJS_ENV		=	$(SRCS_ENV:.c=.o)
OBJS_EXIT		=	$(SRCS_EXIT:.c=.o)
OBJS_EXPORT		=	$(SRCS_EXPORT:.c=.o)
OBJS_PWD		=	$(SRCS_PWD:.c=.o)
OBJS_UNSET		=	$(SRCS_UNSET:.c=.o)
OBJS_EXEC	=	$(SRCS_EXEC:.c=.o)
OBJS			=	$(SRCS:.c=.o)

TARGET			=	a.out

ifdef IF_PIPE
	OBJECTS	=	$(OBJS_PIPE)
	PRINT	=	"$(LF)Testing Pipe...\n"
else ifdef IF_CD
	OBJECTS	=	$(OBJS_CD)
	PRINT	=	"$(LF)Testing Command: CD...\n"
else ifdef IF_ECHO
	OBJECTS	=	$(OBJS_ECHO)
	PRINT	=	"$(LF)Testing Command: ECHO...\n"
else ifdef IF_ENV
	OBJECTS	=	$(OBJS_ENV)
	PRINT	=	"$(LF)Testing Command: ENV...\n"
else ifdef IF_EXIT
	OBJECTS	=	$(OBJS_EXIT)
	PRINT	=	"$(LF)Testing Command: EXIT...\n"
else ifdef IF_EXPORT
	OBJECTS	=	$(OBJS_EXPORT)
	PRINT	=	"$(LF)Testing Command: EXPORT...\n"
else ifdef IF_PWD
	OBJECTS	=	$(OBJS_PWD)
	PRINT	=	"$(LF)Testing Command: PWD...\n"
else ifdef IF_UNSET
	OBJECTS	=	$(OBJS_UNSET)
	PRINT	=	"$(LF)Testing Command: UNSET...\n"
else ifdef IF_EXEC
	OBJECTS	=	$(OBJS_EXEC)
	PRINT	=	"$(LF)Testing execution function\n"
else ifdef IF_PIPE_D
	OBJECTS	=	$(OBJS_PIPE)
	PRINT	=	"$(LF)Testing Pipe...\n"
	DFLAGS	=	-g3 -fsanitize=address
else ifdef IF_CD_D
	OBJECTS	=	$(OBJS_CD)
	PRINT	=	"$(LF)Testing Command: CD...(debug mode)\n"
	DFLAGS	=	-g3 -fsanitize=address
else ifdef IF_ECHO_D
	OBJECTS	=	$(OBJS_ECHO)
	PRINT	=	"$(LF)Testing Command: ECHO...(debug mode)\n"
	DFLAGS	=	-g3 -fsanitize=address
else ifdef IF_ENV_D
	OBJECTS	=	$(OBJS_ENV)
	PRINT	=	"$(LF)Testing Command: ENV...(debug mode)\n"
	DFLAGS	=	-g3 -fsanitize=address
else ifdef IF_EXIT_D
	OBJECTS	=	$(OBJS_EXIT)
	PRINT	=	"$(LF)Testing Command: EXIT...(debug mode)\n"
	DFLAGS	=	-g3 -fsanitize=address
else ifdef IF_EXPORT_D
	OBJECTS	=	$(OBJS_EXPORT)
	PRINT	=	"$(LF)Testing Command: EXPORT...(debug mode)\n"
	DFLAGS	=	-g3 -fsanitize=address
else ifdef IF_PWD_D
	OBJECTS	=	$(OBJS_PWD)
	PRINT	=	"$(LF)Testing Command: PWD...(debug mode)\n"
	DFLAGS	=	-g3 -fsanitize=address
else ifdef IF_UNSET_D
	OBJECTS	=	$(OBJS_UNSET)
	PRINT	=	"$(LF)Testing Command: UNSET...(debug mode)\n"
	DFLAGS	=	-g3 -fsanitize=address
else ifdef IF_EXEC_D
	OBJECTS	=	$(OBJS_EXEC)
	PRINT	=	"$(LF)Testing execution function (debug mode)\n"
	DFLAGS	=	-g3 -fsanitize=address
else ifndef	IF_DEBUG
	OBJECTS	=	$(OBJS)
	PRINT	=	"$(LF)Testing All...(debug mode)\n"
	DFLAGS	=	-g3 -fsanitize=address
else
	OBJECTS	=	$(OBJS)
	PRINT	=	"$(LF)Testing All...\n"
endif

all : $(TARGET)

$(TARGET) : $(OBJECTS)
	@printf $(PRINT)
	@$(CC) $(OBJECTS) $(CFLAGS) $(DFLAGS) libft.a -o $(TARGET)

pipe :
	@$(MAKE) IF_PIPE=1 all

debug-pipe :
	@$(MAKE) IF_PIPE_D=1 all

cd :
	@$(MAKE) IF_CD=1 all

debug-cd :
	@$(MAKE) IF_CD_D=1 all

echo :
	@$(MAKE) IF_ECHO=1 all

debug-echo :
	@$(MAKE) IF_ECHO_D=1 all

env :
	@$(MAKE) IF_ENV=1 all

debug-env :
	@$(MAKE) IF_ENV_D=1 all

exit :
	@$(MAKE) IF_EXIT=1 all

debug-exit :
	@$(MAKE) IF_EXIT_D=1 all

exprt :
	@$(MAKE) IF_EXPORT=1 all

debug-exprt :
	@$(MAKE) IF_EXPORT_D=1 all

pwd :
	@$(MAKE) IF_PWD=1 all

debug-pwd :
	@$(MAKE) IF_PWD_D=1 all

unset :
	@$(MAKE) IF_UNSET=1 all

debug-unset :
	@$(MAKE) IF_UNSET_D=1 all

exec :
	@$(MAKE) IF_EXEC=1 all

debug-exec :
	@$(MAKE) IF_EXEC_D=1 all

%.o : %.c
	@$(CC) $(CFLAGS) $(DFLAGS) -c -o $@ $< -I ./

clean :
	@printf "$(LF)Deleting files...\n"
	@rm -rf $(OBJS_PIPE) $(OBJS_CD) $(OBJS_ECHO) $(OBJS_ENV) $(OBJS_EXIT)
	@rm -rf $(OBJS_PWD) $(OBJS_UNSET) $(OBJS_EXEC) $(OBJS_EXPORT)

fclean : clean
	@rm -rf a.out

re : fclean all
