/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:57:45 by anmassy           #+#    #+#             */
/*   Updated: 2024/03/20 17:23:20 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct s_player
{
	char	**map;
    int     first_row;
    int     last_row;
    char    orientation;
    int		height;
}				t_player;

typedef struct s_data
{
    struct s_player *val;
}t_data;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

int		ft_strlen(const char *str);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *s1, char const *s2);
char	*ft_substr(char *s, unsigned int start, size_t len);
int		size_line(char *strings, int i);
char	*get_next_line(int fd);

int check_up(t_data *game, int i, int j);
int check_down(t_data *game, int i, int j);
int check_left(t_data *game, int i, int j);
int check_right(t_data *game, int i, int j);
int map_close(t_data *game);

void	display_map(t_data *game);
int	    len_doc(char *av);
void	convert_map(t_data *game, char *av);
int     valid_map(t_data *game);

int verif_texture(t_data *game);
int verif_map(t_data *game);

t_data	*init_struct(void);

int main(int ac, char **av);

#endif