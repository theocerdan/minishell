# Project file
NAME = minishell

RED = \033[0;31m
GREEN = \033[0;32m
NONE = \033[0m

#Source directories:

MAIN_DIR = srcs/
ERR_DIR = error/
PRMPT_DIR = prompt/
PARSE_DIR = parser/
EXEC_DIR = execute/
BLTIN_DIR = builtins/
LIBFT_DIR = libft/

#Source files:

SRCS_FILES = main.c \
				built_process.c \
				env_manager.c \
				equals_ignore_case.c \
				exec.c \
				ft_memory_cleaner2000.c \
				get_absolute_path.c \
				get_next_word.c \

SRC_BLTIN = ft_pwd.c \
				ft_echo.c \
				ft_env.c \
				ft_exit.c \
				ft_cd.c \
				ft_export.c \
				ft_unset.c

SRC_ERR = ft_error.c

SRC_PRMPT = ft_prompt.c

SRCS = $(addprefix $(MAIN_DIR),$(SRCS_FILES)) \
		$(addprefix $(MAIN_DIR),$(addprefix $(BLTIN_DIR),$(SRC_BLTIN))) \
		$(addprefix $(MAIN_DIR),$(addprefix $(ERR_DIR),$(SRC_ERR))) \
		$(addprefix $(MAIN_DIR),$(addprefix $(PRMPT_DIR),$(SRC_PRMPT))) \

INC	= -I ./includes/ -I ./libft/includes

OBJS = $(patsubst %.c,%.o,$(SRCS))

# Libft builds and dirs
LIBDIR = ./libft/
LIBFT = ./libft/libft.a

# Optimization and Compiler flags and commands
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address

# Main rule
all: $(LIBFT) $(NAME)

# Objects rule
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

# Project file rule
$(NAME): $(OBJS)
	@$(CC) $(INC) $(OBJS) $(LIBFT) -lreadline -lncurses -o $@ #-fsanitize=address
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
