# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/07 10:00:03 by anmassy           #+#    #+#              #
#    Updated: 2024/03/21 19:40:36 by anmassy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	srcs/parsing/get_next_line_utils.c \
		srcs/parsing/get_next_line.c \
		srcs/parsing/init_struct.c \
		srcs/parsing/verif_map.c \
		srcs/parsing/verif_texture.c \
		srcs/parsing/verif_wall.c \
		srcs/parsing/main.c \


OBJ = $(SRC:.c=.o)

NAME = Cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

INCS = -I ./includes

all : $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(INCS) $(OBJ) $(LIBC) -o $(NAME)

clean :
	@$(RM) $(OBJ)

fclean : clean
	@$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
