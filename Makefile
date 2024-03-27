# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/07 10:00:03 by anmassy           #+#    #+#              #
#    Updated: 2024/03/27 18:35:53 by lmarchai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRC =	srcs/parsing/get_next_line_utils.c \
		srcs/parsing/get_next_line.c \
		srcs/parsing/init_struct.c \
		srcs/parsing/verif_map.c \
		srcs/parsing/verif_texture.c \
		srcs/parsing/verif_wall.c \
		srcs/parsing/set_mlx.c \
		srcs/parsing/main.c \

OBJ = $(SRC:.c=.o)

NAME = Cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

INCS = -I ./includes -I ./mlx_linux
LIBC = -L ./mlx_linux
MLX_FLAGS =	-L./mlx_linux -lX11 -lbsd -lXext

all : $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(NAME): $(OBJ)
	@$(MAKE) -C mlx_linux >/dev/null 2>&1
	@$(CC) $(CFLAGS) $(INCS) $(OBJ) $(LIBC) mlx_linux/libmlx.a $(MLX_FLAGS) -o $(NAME)

clean :
	@$(RM) $(OBJ)
	@$(MAKE) -C mlx_linux clean >/dev/null 2>&1

fclean : clean
	@$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
