# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/07 10:00:03 by anmassy           #+#    #+#              #
#    Updated: 2024/03/30 12:48:46 by anmassy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRC =	srcs/parsing/get_next_line_utils.c \
		srcs/parsing/get_next_line.c \
		srcs/parsing/init_struct.c \
		srcs/parsing/verif_map.c \
		srcs/parsing/verif_texture.c \
		srcs/parsing/verif_wall.c \
		srcs/parsing/main.c \
		srcs/parsing/verif_color.c \
		srcs/parsing/verif_path.c \
		srcs/parsing/ft_utils.c \
		srcs/parsing/convert_map.c\
		srcs/Raytracing/raycastings.c

OBJ = $(SRC:.c=.o)

NAME = Cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f

INCS = -I ./includes -I ./mlx_linux
LIBC = -L ./mlx_linux
MLX_FLAGS =	-L./mlx_linux -lX11 -lbsd -lXext -lm

all : $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(NAME): $(OBJ)
	@$(MAKE) -C mlx_linux >/dev/null 2>&1
	@$(CC) $(CFLAGS) $(INCS) $(OBJ) $(LIBC) mlx_linux/libmlx.a $(MLX_FLAGS) -o $(NAME) -g

clean :
	@$(RM) $(OBJ)
	@$(MAKE) -C mlx_linux clean >/dev/null 2>&1

fclean : clean
	@$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
