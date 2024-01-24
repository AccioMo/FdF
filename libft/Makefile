CC = cc
FLAGS = -Wall -Wextra -Werror

NAME = libft.a
SRC_DIR = src/
OBJ_DIR = obj/
HEADER = libft.h
FILES = ft_calloc.c ft_isdigit.c ft_memset.c ft_split.c ft_strlcat.c ft_strnstr.c ft_toupper.c ft_isprint.c \
		ft_memchr.c ft_putchar_fd.c ft_strchr.c ft_strlcpy.c ft_strrchr.c ft_isalnum.c ft_itoa.c ft_memcmp.c \
		ft_putendl_fd.c ft_strdup.c ft_strlen.c ft_strtrim.c ft_atoi.c ft_isalpha.c ft_memcpy.c ft_putnbr_fd.c \
		ft_striteri.c ft_strmapi.c ft_substr.c ft_bzero.c ft_isascii.c ft_memmove.c ft_putstr_fd.c ft_strjoin.c \
		ft_strncmp.c ft_tolower.c
SRC = $(addprefix $(SRC_DIR), $(FILES))
OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

BONUS = libft_bonus.a
BONUS_SRC_DIR = bonus/src/
BONUS_OBJ_DIR = bonus/obj/
BONUS_FILES = ft_lstdelone_bonus.c ft_lstlast_bonus.c ft_lstiter_bonus.c ft_lstclear_bonus.c ft_lstsize_bonus.c \
			ft_lstadd_front_bonus.c ft_lstnew_bonus.c ft_lstadd_back_bonus.c ft_lstmap_bonus.c
BONUS_SRC = $(addprefix $(BONUS_SRC_DIR), $(BONUS_FILES))
BONUS_OBJ = $(addprefix $(BONUS_OBJ_DIR), $(BONUS_FILES:.c=.o))

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(FLAGS) -I. -c $< -o $@

bonus: $(BONUS_OBJ_DIR) $(BONUS)

$(BONUS_OBJ_DIR):
	mkdir -p $(BONUS_OBJ_DIR)

$(BONUS): $(OBJ) $(BONUS_OBJ) $(HEADER)
	ar rcs $(BONUS) $(OBJ) $(BONUS_OBJ)

$(BONUS_OBJ_DIR)%.o: $(BONUS_SRC_DIR)%.c $(HEADER)
	$(CC) $(FLAGS) -I. -c $< -o $@

clean:
	rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME) $(BONUS)

re: fclean all

.PHONY: all clean fclean re bonus
