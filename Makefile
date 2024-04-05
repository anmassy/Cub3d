# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/07 10:00:03 by anmassy           #+#    #+#              #
#    Updated: 2024/04/05 20:03:39 by anmassy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRC =	srcs/parsing/get_next_line_utils.c \
		srcs/parsing/get_next_line.c \
		srcs/parsing/init_struct.c \
		srcs/parsing/verif_texture.c \
		srcs/parsing/verif_wall.c \
		srcs/parsing/verif_color.c \
		srcs/parsing/get_path.c \
		srcs/parsing/ft_utils.c \
		srcs/parsing/convert_map.c \
		srcs/parsing/exit_fonction.c \
		srcs/parsing/player_road.c \
		srcs/raycasting/raycastings.c\
		srcs/raycasting/dda.c\
		srcs/raycasting/init.c\
		srcs/raycasting/move.c\
		srcs/raycasting/move_cam.c\
		srcs/raycasting/event_hooks.c\
		srcs/raycasting/render.c\
		srcs/raycasting/init_textures.c\
		main.c

OBJ = $(SRC:.c=.o)

NAME = Cub3d
CC = clang
CFLAGS = -Wall -Wextra -Werror -gdwarf-4
RM = rm -f

INCS = -I ./includes -I ./mlx_linux
LIBC = -L ./mlx_linux 
MLX_FLAGS =	-L./mlx_linux -lX11 -lXext -lm 

all : $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(NAME): $(OBJ)
	@$(MAKE) -C mlx_linux 
	@$(CC) $(CFLAGS) $(INCS) $(OBJ) $(LIBC) mlx_linux/libmlx.a $(MLX_FLAGS) -o $(NAME) 

clean :
	@$(RM) $(OBJ)
	@$(MAKE) -C mlx_linux clean 

fclean : clean
	@$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
