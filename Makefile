CC= cc
RM= rm -rf
CFLAGS= -Wall -Wextra -Werror
NAME= minishell
SRC= minishell.c \
	parse/utils/ft_exit.c \
	parse/utils/ft_strlen.c \
	parse/ft_check_quots.c \
	parse/ft_parse_command.c \
	parse/utils/ft_strjoin.c \
	parse/utils/ft_lst_utils.c \
	parse/utils/ft_syntax_error.c \
	parse/ft_split_command.c \
	parse/ft_token_type.c \
	parse/utils/ft_substr.c \
	parse/utils/ft_is_space.c \
	parse/ft_split_based.c \
	parse/utils/ft_split.c \
	parse/utils/ft_strchr.c \
	parse/utils/ft_strdup.c \
	parse/ft_logic_syntax.c
	
OBJ= $(SRC:.c=.o)
HEADER= minishell.h

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ -lreadline -lncurses

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean