NAME=cub3D
CC=cc
S=-fsanitize=address -g
FLAGS=-Wall -Wextra -Werror $(S)
PARSING = ./part1/read_file.c
PART2   = 
SRC=  cub.c $(PARSING) $(PART2)
OBJ=$(SRC:.c=.o)
LIBFT=./libft/libft.a  ./MLX42/build/libmlx42.a
LIBFT_PATH=./libft
LIBFT_LINUX=./libft_linux
INCLUDES=./libft/libft.h cub3d.h ./MLX42/include/MLX42/MLX42.h
FRAMEWORKS= -framework OpenGL -framework AppKit -lmlx -framework Cocoa -framework OpenGL -framework IOKit
MLX_PATH = ./minilibx-linux
MLX=$(MLX_PATH)/libmlx_Linux.a 
LINUX= -lX11 -lXext -lXrandr
SYSTEM=$(uname)

all : libf $(NAME)

#  all : libf mlx  $(NAME)

# mlx :
# 	make -C $(MLX_PATH)

libf :
	make -C $(LIBFT_PATH)

# libf :
# 	make -C $(LIBFT_LINUX)

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT)  -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" $(FRAMEWORKS) -o $@

# $(NAME) : $(OBJ)
# 	$(CC) $(FLAGS) $(OBJ) $(LIBFT_LINUX)/libft.a  $(MLX) $(LINUX) -o $@

%.o : %.c $(INCLUDES)
	$(CC) $(FLAGS) -c $< -o $@

clean :
	@make -C $(LIBFT_PATH) $@
	rm -f $(OBJ)

fclean : clean
	@make -C $(LIBFT_PATH) $@
	rm -f $(NAME)

re : fclean all

.PHONY : clean
