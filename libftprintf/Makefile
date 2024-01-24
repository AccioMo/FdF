CC = cc
NAME = libftprintf.a
HEADER = ft_printf.h
FLAGS = -Werror -Wextra -Wall
SRC = ft_printf.c ft_printf_multiverse.c ft_puthex.c ft_putstr.c ft_putchar.c ft_putnbr.c ft_putunbr.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re