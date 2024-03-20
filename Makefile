# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/07 10:00:03 by anmassy           #+#    #+#              #
#    Updated: 2024/03/07 13:26:35 by anmassy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	srcs/main.c \
		srcs/get_next_line_utils.c \
		srcs/get_next_line.c \
		srcs/verif_value.c \
		srcs/verif_wall.c \


OBJ = $(SRC:.c=.o)

NAME = Cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

INCS = -I ./includes -I

all : $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(INCS) $(OBJ) -o $(NAME)

clean :
	@$(RM) $(OBJ)

fclean : clean
	@$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
