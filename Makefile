CC=cc
RM=rm -rf
CFLAGS=-Wall -Wextra -Werror
NAME=minishell
SRC=minishell.c \
	parse/utils/ft_exit.c \
	parse/utils/ft_strlen.c \
	parse/ft_check_quots.c \
	parse/ft_parse_command.c \
	parse/utils/ft_strjoin.c \
	parse/utils/ft_lst_utils.c \
	parse/utils/ft_syntax_error.c
OBJ=$(SRC:.c=.o)
HEADER=minishell.h

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -lreadline $(OBJ) -o $@

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all