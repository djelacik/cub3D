NAME = cub3D
CC = cc
LIBMLX = ./MLX42
MLX_42 = $(LIBMLX)/build/libmlx42.a

INCLUDES = -Iincludes -Ilibft -Iget_next_line -I$(LIBMLX)/include
CFLAGS =  -Wall -Werror -Wextra -g -O2 #-fPIE

LDFLAGS = -L./MLX42/build -lmlx42 -lglfw -pthread -lm -L./libft -lft -L"/opt/homebrew/Cellar/glfw/3.4/lib/" #-ldl #-pie

SRC = \
src/color_utils.c \
src/main.c \
src/shading.c \
src/texture.c \
src/ray.c \
src/rays.c \
src/hooks.c \
src/utils.c \
src/minimap.c \
src/movement.c

OBJ = $(SRC:.c=.o)

# Rule for building the final executable
all: $(NAME)

# Compile the project and link it with libft and MLX42
$(NAME): $(OBJ) libft/libft.a $(MLX_42)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

# Compile libft library with -fPIE
libft/libft.a:
	@make CFLAGS="-Wall -Wextra -Werror -fPIE" -C libft

# Clone MLX42 if it does not exist
mlx_clone: 
	@if [ ! -d "$(LIBMLX)" ]; then \
		echo "Cloning MLX42..."; \
		git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX); \
	fi

# Build the MLX42 library only if it hasn't been built yet
$(MLX_42): mlx_clone
	@if [ ! -f "$(MLX_42)" ]; then \
		echo "Building MLX42..."; \
		cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4; \
	fi

# Compile object files from source
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

# Clean object files
clean:
	rm -f $(OBJ)
	@make clean -C libft
	rm -rf $(LIBMLX)/build

# Full clean (removes executable and object files)
fclean: clean
	rm -f $(NAME)
	@make fclean -C libft

# Rebuild everything
re: fclean all

# Bonus target to compile the bonus version without relinking
bonus: $(NAME)

.PHONY: all clean fclean re bonus mlx_clone
