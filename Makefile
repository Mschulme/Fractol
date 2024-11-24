# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/03 21:52:32 by mschulme          #+#    #+#              #
#    Updated: 2023/06/07 15:26:47 by mschulme         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

CC = gcc
CFLAGS = -Wall -Werror -Wextra -Ofast

LIBFT_DIR = ./libft/
LIBFT = $(LIBFT_DIR)libft.a

MLX_DIR = ./mlx/
MLX = $(MLX_DIR)libmlx.a

OBJS = $(SRCS:%.c=%.o)

SRCS = ft_fractol.c ft_handlekeypress.c \
		mandelbrot.c julia.c burningship.c \
		ft_utils.c ft_atof.c ft_helper.c

HDRS = -I$(LIBFT_DIR) -I$(MLX_DIR)

LIBS = -L$(LIBFT_DIR) -L$(MLX_DIR) -lft -lmlx -lm -lX11 -lXext

%.o: %.c
	$(CC) $(CFLAGS) $(HDRS) -c $< -o $@

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
