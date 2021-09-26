NAME = minishell

SRCS = main.c \
	   ft_memory_cleaner2000.c \
	   game_checker.c \
	   game_init.c \
	   game_init_utils.c \
	   game_color.c \
	   game_flood_filling.c \
	   game_manager.c \
	   game_manager_utils.c \
	   game_parser.c \
	   game_parser_utils.c \
	   game_parser_utils2.c \
	   game_parser_utils3.c \
	   game_player_ctrl.c \
	   game_player_ctrl_utils.c \
	   game_render_square_builder.c \
	   game_sprite.c \
	   game_sprite_utils.c \
	   game_render_utils.c \
	   game_render_utils2.c \
	   game_render_utils3.c \
	   game_render.c \
	   game_utils.c \
	   game_error.c \
	   game_screenshot.c \
	   gnl/get_next_line.c \
	   gnl/get_next_line_utils.c 


CFLAGS = -g

OBJS = $(SRCS:.c=.o)

all : gnl libft minilibx $(NAME)

gnl :
	make -C gnl/

libft :
	make -C libft/

minilibx :
	make -C minilibx/

$(%.o): $(%.c)
	gcc $(CFLAGS) -o $@ -c $^

$(OBJS) : minishell.h

$(NAME): $(OBJS)
	gcc $(CFLAGS) -o $@ $^ -L minilibx -lmlx -L libft -lft

clean :
	rm -f $(OBJS)
	make -C gnl/ clean
	make -C libft/ clean
	make -C minilibx/ clean

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re libft minilibx gnl