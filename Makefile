# Project file
NAME = minishell

RED = \033[0;31m
GREEN = \033[0;32m
NONE = \033[0m

#Source directories:

MAIN_DIR = srcs/
ERR_DIR = error/
ENV_DIR = env/
PRMPT_DIR = prompt/
PARSE_DIR = parser/
EXEC_DIR = execute/
BLTIN_DIR = builtins/
TKN_DIR = tokenizer/
SIG_DIR = signal/
UTLS_DIR = utils/
PRS_DIR = parser/
LIBFT_DIR = libft/

#Source files:

SRCS_FILES = main.c \

SRC_BLTIN = ft_pwd.c \
				ft_echo.c \
				ft_env.c \
				ft_exit.c \
				ft_cd.c \
				ft_export.c \
				ft_unset.c \
				utils_builtins.c

SRC_ERR = ft_error.c

SRC_PRMPT = ft_prompt.c

SRC_ENV = env_manager.c \
			env_utils.c

SRC_EXEC = execute.c \
			execute_utils1.c \
			execute_utils2.c

SRC_TKN = tokenizer.c \
			tokenizer_utils1.c \
			tokenizer_utils2.c \
			tokenizer_utils3.c \
			tokenizer_utils4.c \

SRC_SIG = signal.c \

SRC_UTLS = init.c \
			ft_memory_cleaner2000.c \
			utils.c \

SRC_PRS = parser.c \
			quotes.c \
			vaguellette.c \
			parser_utils1.c \
			parse_env_key.c \
			parse_env_key_utils1.c \

SRCS = $(addprefix $(MAIN_DIR),$(SRCS_FILES)) \
		$(addprefix $(MAIN_DIR),$(addprefix $(BLTIN_DIR),$(SRC_BLTIN))) \
		$(addprefix $(MAIN_DIR),$(addprefix $(ERR_DIR),$(SRC_ERR))) \
		$(addprefix $(MAIN_DIR),$(addprefix $(PRMPT_DIR),$(SRC_PRMPT))) \
		$(addprefix $(MAIN_DIR),$(addprefix $(ENV_DIR),$(SRC_ENV))) \
		$(addprefix $(MAIN_DIR),$(addprefix $(EXEC_DIR),$(SRC_EXEC))) \
		$(addprefix $(MAIN_DIR),$(addprefix $(TKN_DIR),$(SRC_TKN))) \
		$(addprefix $(MAIN_DIR),$(addprefix $(SIG_DIR),$(SRC_SIG))) \
		$(addprefix $(MAIN_DIR),$(addprefix $(UTLS_DIR),$(SRC_UTLS))) \
		$(addprefix $(MAIN_DIR),$(addprefix $(PRS_DIR),$(SRC_PRS))) \

INC	= -I ./includes/ -I ./libft/includes

OBJS = $(patsubst %.c,%.o,$(SRCS))

# Libft builds and dirs
LIBDIR = ./libft/
LIBFT = ./libft/libft.a

# Optimization and Compiler flags and commands
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

# Main rule
all: $(LIBFT) $(NAME)

# Objects rule
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

# Project file rule
$(NAME): $(OBJS)
	@$(CC) $(INC) $(OBJS) $(LIBFT) -lreadline -lncurses -o $@ -fsanitize=address
	@printf "\e[92mminishell compiled\e[0m\e[?25h\n"

# Libft rule
$(LIBFT):
	@make -C $(LIBDIR)
	@printf "\e[92mlibft compiled\e[0m\e[?25h\n"
	
# Cleaning up the build files
clean:
	@make -C $(LIBDIR) clean
	@rm -rf $(OBJS)
	@printf "\033[0;31mfolder cleaned\e[0m\n"

# Getting rid of the project file
fclean:	clean
	@make -C $(LIBDIR) fclean
	@rm -rf $(NAME)
	@printf "\033[0;31mfolder fcleaned\e[0m\n"

# Do both of the above
re:	fclean all

# Just in case those files exist in the root dir
.PHONY:	all clean fclean re
