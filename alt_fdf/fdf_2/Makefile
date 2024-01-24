# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/01 16:22:42 by sgoffaux          #+#    #+#              #
#    Updated: 2024/01/23 21:54:51 by mzeggaf          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fdf
LIBFT		=	libft/
GNL			=	get_next_line/
MLX			=	minilibx/
LIBFT_A		=	$(addprefix $(LIBFT), libft.a)
GNL_A		=	$(addprefix $(GNL), libgnl.a)
MLX_A		=	$(addprefix $(MLX), libmlx.a)

CC			=	gcc
INCLUDE 	=	includes
CFLAGS		=	-I$(INCLUDE)
RM			=	rm -f
SRCS		=	fdf.c \
				srcs/alg_utils.c \
				srcs/controls.c \
				srcs/mouse.c \
				srcs/keyboard.c \
				srcs/draw.c \
				srcs/line_alg.c \
				srcs/project.c \
				srcs/parse_map.c \
				srcs/utils.c \

OBJS		=	$(SRCS:%.c=%.o)

all:			$(NAME)

$(NAME):		$(OBJS) $(LIBFT_A) $(GNL_A)
				@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT) -lft -L$(GNL) -lgnl -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME) -framework OpenGL -framework AppKit
				@echo "Linked into executable \033[0;32mfdf\033[0m."

$(LIBFT_A):
				@$(MAKE) -s -C $(LIBFT)
				@echo "Compiled $(LIBFT_A)."

$(GNL_A):
				@$(MAKE) -s -C $(GNL)
				@echo "Compiled $(GNL_A)."

$(MLX_A):
				@$(MAKE) -s -C $(MLX)
				@echo "Compiled $(MLX_A)."

bonus:			all

.c.o:
				@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
				@echo "Compiling $<."

localclean:
				@$(RM) $(OBJS)
				@echo "Removed object files."

clean:			localclean
				@$(MAKE) clean -s -C $(LIBFT)
				@echo "Clean libft."
				@$(MAKE) clean -s -C $(GNL)
				@echo "Clean gnl."

fclean:			localclean
				@$(MAKE) fclean -s -C $(LIBFT)
				@echo "Full clean libft."
				@$(MAKE) fclean -s -C $(GNL)
				@echo "Full clean gnl."
				@$(RM) $(NAME)
				@echo "Removed executable."

re:				fclean all

.PHONY:			all clean fclean re localclean bonus