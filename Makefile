CC = cc
FLAGS = -Wall -Wextra -Werror -O3
LIBFT = libft/libft.a
LIBFT_DIR = libft/
GNL = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

NAME = fdf
SRC_DIR = src/
OBJ_DIR = obj/
HEADER = $(SRC_DIR)fdf.h
FILES = fdf_main.c fdf_map.c fdf_draw_1.c fdf_draw_2.c fdf_math.c fdf_color.c \
	fdf_mouse.c fdf_utils.c fdf_input_1.c fdf_input_2.c fdf_color_parse.c \
	 fdf_draw_map.c fdf_map_parse.c fdf_exit.c
SRC = $(addprefix $(SRC_DIR), $(FILES))
OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

NAME_BONUS = fdf_bonus
SRC_DIR_BONUS = bonus/src/
OBJ_DIR_BONUS = bonus/obj/
HEADER_BONUS = $(SRC_DIR_BONUS)fdf_bonus.h
FILES_BONUS = fdf_main_bonus.c fdf_map_bonus.c fdf_draw_1_bonus.c fdf_draw_2_bonus.c fdf_math_bonus.c fdf_color_bonus.c \
	fdf_mouse_bonus.c fdf_utils_bonus.c fdf_input_1_bonus.c fdf_input_2_bonus.c fdf_color_parse_bonus.c \
	 fdf_draw_map_bonus.c fdf_map_parse_bonus.c fdf_exit_bonus.c
SRC_BONUS = $(addprefix $(SRC_DIR_BONUS), $(FILES_BONUS))
OBJ_BONUS = $(addprefix $(OBJ_DIR_BONUS), $(FILES_BONUS:.c=.o))

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m
CYAN = \033[0;36m
BOLD = \033[1m

.PHONY: all $(LIBFT) clean fclean re

all: $(OBJ_DIR) $(LIBFT) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT): $(LIBFT_DIR)
	@make -C $<

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBFT) $(GNL) -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	@echo "$(GREEN)$(BOLD)FDF:$(RESET) $(CYAN)Executable created$(RESET)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@
	@echo "$(GREEN)$(BOLD)FDF:$(RESET) $(CYAN)Compiled:$(RESET) $(notdir $<)"

bonus: $(OBJ_DIR_BONUS) $(LIBFT) $(NAME_BONUS)

$(OBJ_DIR_BONUS):
	mkdir -p $(OBJ_DIR_BONUS)

$(NAME_BONUS): $(OBJ_BONUS)
	$(CC) $(OBJ_BONUS) $(LIBFT) $(GNL) -lmlx -framework OpenGL -framework AppKit -o $(NAME_BONUS)
	@echo "$(GREEN)$(BOLD)FDF:$(RESET) $(CYAN)Executable created$(RESET)"

$(OBJ_DIR_BONUS)%.o: $(SRC_DIR_BONUS)%.c $(HEADER_BONUS)
	$(CC) $(FLAGS) -c $< -o $@
	@echo "$(GREEN)$(BOLD)FDF:$(RESET) $(CYAN)Compiled:$(RESET) $(notdir $<)"

clean:
	rm -f $(OBJ) $(OBJ_BONUS)
	@echo "$(RED)$(BOLD)FDF:$(RESET) $(CYAN)Object files removed$(RESET)"

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	@echo "$(RED)$(BOLD)FDF:$(RESET) $(CYAN)Executable removed$(RESET)"

re: fclean all