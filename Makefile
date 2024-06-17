NAME		= minishell
CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror -g -Iinclude -Ilibft
LDFLAGS		= -Llibft
LINKS		= -lft -lm -lpthread -lreadline
RM			= rm -f
MAKEFLAGS   := --no-print-directory

LIBFT		= libft/libft.a

SRC_DIR		= src
SRCS		:= /main.c \
				/tokenize/ft_tokenize.c \
				/tokenize/ft_tokenize_word.c \
				/tokenize/ft_tokenize_special_char.c \
				/tokenize/ft_quote_clean.c \
				/tokenize/ft_word_end.c \
				/envp/ft_swap_envp.c \
				/envp/ft_swap_envp_hc.c \
				/envp/ft_change_value.c \
				/envp/ft_env_init.c \
				/envp/ft_env_to_mtx.c \
				/envp/ft_swap_value.c \
				/ft_free_n_err.c \
				/ft_update_status.c \
				/command/ft_command.c \
				/command/ft_command_init.c \
				/command/ft_command_fill.c \
				/command/ft_addheredoc.c \
				/command/ft_addpath.c \
				/command/ft_addredir.c \
				/command/ft_addarg.c \
				/exec/ft_exec.c \
				/exec/ft_exec_builtin.c \
				/exec/ft_exec_child.c \
				/exec/ft_redir.c \
				/exec/ft_pipe.c \
				/builtin/ft_echo.c \
				/builtin/ft_exit.c \
				/builtin/ft_export.c \
				/builtin/ft_unset.c \
				/builtin/ft_cd.c \
				/builtin/ft_pwd.c \
				/builtin/ft_env.c \
				/token_list/ft_lstnew_t.c \
				/token_list/ft_lstadd_back_t.c \
				/token_list/ft_lstclear_t.c \
				/token_list/ft_lstlast_t.c \
				/lexer/ft_lexer.c \
				/cmd_list/ft_lstadd_back_c.c \
				/cmd_list/ft_lstclear_c.c \
				/cmd_list/ft_lstcut_c.c \
				/cmd_list/ft_lstnew_c.c \
				/env_list/ft_lstaddback_e.c \
				/env_list/ft_lstclear_e.c \
				/env_list/ft_lstnew_e.c \

SRCS_FINAL = $(addprefix $(SRC_DIR), $(SRCS))

all: $(NAME)

$(NAME): $(SRCS_FINAL)
	@[ -f $(LIBFT) ] || make -C libft/
	echo "${BOLD}Creating  -> ${YELLOW}libft.a${NO_COLOR}"
	$(CC) $(SRCS_FINAL) $(LDFLAGS) $(CFLAGS) $(LINKS) -o $(NAME)
	echo "${BOLD}Creating  -> ${RED}$(NAME)${NO_COLOR}"
	$(MAKE) goku

valgrind: $(NAME)
	valgrind --leak-check=full --show-reachable=yes --show-leak-kinds=all --track-origins=yes --track-fds=yes --trace-children=yes --suppressions=readline.supp  ./$(NAME)

clean:
	make clean -C libft/

fclean: clean
	make fclean -C libft/
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re all goku
.SILENT:

RED			:= ${shell tput setaf 1}
BLUE		:= ${shell tput setaf 4}
YELLOW		:= ${shell tput setaf 3}
NO_COLOR	:= ${shell tput sgr0}
BOLD		:= ${shell tput bold}

goku:
	@echo '⣿⣿⠿⠿⠿⠿⣿⣷⣂⠄⠄⠄⠄⠄⠄⠈⢷⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿'
	@echo '⣷⡾⠯⠉⠉⠉⠉⠚⠑⠄⡀⠄⠄⠄⠄⠄⠈⠻⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿'
	@echo '⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⡀⠄⠄⠄⠄⠄⠄⠄⠄⠉⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿'
	@echo '⠄⠄⠄⠄⠄⠄⠄⠄⠄⢀⠎⠄⠄⣀⡀⠄⠄⠄⠄⠄⠄⠄⠘⠋⠉⠉⠉⠉⠭⠿⣿'
	@echo '⡀⠄⠄⠄⠄⠄⠄⠄⠄⡇⠄⣠⣾⣳⠁⠄⠄⢺⡆⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄'
	@echo '⣿⣷⡦⠄⠄⠄⠄⠄⢠⠃⢰⣿⣯⣿⡁⢔⡒⣶⣯⡄⢀⢄⡄⠄⠄⠄⠄⠄⣀⣤⣶'
	@echo '⠓⠄⠄⠄⠄⠄⠸⠄⢀⣤⢘⣿⣿⣷⣷⣿⠛⣾⣿⣿⣆⠾⣷⠄⠄⠄⠄⢀⣀⣼⣿'
	@echo '⠄⠄⠄⠄⠄⠄⠄⠑⢘⣿⢰⡟⣿⣿⣷⣫⣭⣿⣾⣿⣿⣴⠏⠄⠄⢀⣺⣿⣿⣿⣿'
	@echo '⣿⣿⣿⣿⣷⠶⠄⠄⠄⠹⣮⣹⡘⠛⠿⣫⣾⣿⣿⣿⡇⠑⢤⣶⣿⣿⣿⣿⣿⣿⣿'
	@echo '⣿⣿⣿⣯⣤⣤⣤⣤⣀⣀⡹⣿⣿⣷⣯⣽⣿⣿⡿⣋⣴⡀⠈⣿⣿⣿⣿⣿⣿⣿⣿'
	@echo '⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣾⣝⡻⢿⣿⡿⠋⡒⣾⣿⣧⢰⢿⣿⣿⣿⣿⣿⣿⣿'
	@echo '⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠃⣏⣟⣼⢋⡾⣿⣿⣿⣘⣔⠙⠿⠿⠿⣿⣿⣿'
	@echo '⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠿⣛⡵⣻⠿⠟⠁⠛⠰⠿⢿⠿⡛⠉⠄⠄⢀⠄⠉⠉⢉'
	@echo '⣿⣿⣿⣿⡿⢟⠩⠉⣠⣴⣶⢆⣴⡶⠿⠟⠛⠋⠉⠩⠄⠉⢀⠠⠂⠈⠄⠐⠄⠄⠄'

