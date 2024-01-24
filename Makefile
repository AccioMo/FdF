CC = cc
# FLAGS = -Wall -Wextra -Werror
NAME = fdf
LIBFT = libft/libft.a
LIBFT_DIR = libft/
GNL = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

SRC_DIR = src/
OBJ_DIR = obj/
HEADER = $(SRC_DIR)fdf.h
FILES = fdf_main.c fdf_map.c fdf_draw.c fdf_draw2.c fdf_math.c fdf_color.c
SRC = $(addprefix $(SRC_DIR), $(FILES))
OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

.PHONY: all $(LIBFT) clean fclean re

all: $(OBJ_DIR) $(LIBFT) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT): $(LIBFT_DIR)
	@make -C $<

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBFT) $(GNL) libftprintf/libftprintf.a -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean

re: fclean all