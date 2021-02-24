NAME = minishell

CC = clang

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address -I includes/ -I libft/includes/

LIBFT = -L libft -lft

HEADER = minishell.h

SRCS = ft_cd.c ft_exec.c ft_pwd.c ft_struct_envp.c get_next_line.c ft_echo.c ft_export.c ft_set.c \
		ft_unset.c get_next_line_utils.c ft_env.c ft_get.c ft_signal.c ft_utils.c main.c ft_builtin_utils.c \
		ft_export_utils1.c ft_export_utils2.c ft_utils2.c ft_utils3.c ft_utils4.c ft_verif.c \
		ft_dollar.c ft_token.c ft_redir.c ft_builtin.c ft_exit.c ft_line.c ft_utils5.c ft_utils6.c\


SRC = $(addprefix srcs/, $(SRCS))

OBJ = $(SRC:c=o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\n"
	@make -C libft/
	@echo "\033[0;32mCompiling minishell..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)
	@echo "\n\033[0mDone !"

%.o: %.c
	@printf "\033[0;33mGenerating minishell objects... %-33.33s\r" $@
	@${CC} ${CFLAGS} -c $< -o $@

clean:
	@echo "\033[0;31mCleaning libft..."
	@make clean -C libft/
	@echo "\nRemoving binaries..."
	@rm -f $(OBJ)
	@echo "\033[0m"

fclean:
	@echo "\033[0;31mCleaning libft..."
	@make fclean -C libft/
	@echo "\nDeleting objects..."
	@rm -f $(OBJ)
	@echo "\nDeleting executable..."
	@rm -f $(NAME)
	@echo "\033[0m"

re: fclean all

.PHONY: clean fclean re test norm
