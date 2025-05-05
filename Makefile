NAME = minishell

CC = cc
RM = rm -rf

# Enable sanitizer/debug by uncommenting these
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
# CFLAGS = -Wall -Wextra -Werror

SRC = minishell.c \
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
	parse/ft_logic_syntax.c \
	parse/utils/ft_strlcpy.c \
	garbage.c \
	parse/ft_quotes_type.c \
	parse/utils/ft_strstr.c \
	parse/ft_expend.c \
	parse/utils/ft_strlcat.c \
	parse/ft_total_len.c \
	exec/exec_main.c \
	exec/exec_child.c \
	exec/builtins.c \
	exec/exec_list.c \
	exec/exec_more_list.c \
	exec/parse_to_exec.c \
	exec/exec_utils.c \
	exec/export.c \
	exec/unset.c \
	exec/echo.c \
	exec/env.c \
	exec/cd.c \
	exec/exit.c \
	exec/ft_split_exec.c

OBJ = $(SRC:.c=.o)

HEADER = minishell.h

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
