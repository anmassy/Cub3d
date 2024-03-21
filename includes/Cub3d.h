/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:57:45 by anmassy           #+#    #+#             */
/*   Updated: 2024/03/21 19:21:55 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

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
    int     north_line;
    int     south_line;
    int     east_line;
    int     west_line;
}				t_player;

typedef struct s_texture
{
    int     north_line;
    int     south_line;
    int     east_line;
    int     west_line;
    int     floor_line;
    int     ceiling_line;
    char    *north_path;
	char    *south_path;
	char    *east_path;
	char    *west_path;
    char    *ceiling_pigmentation;
    char    *floor_pigmentation;
}				t_texture;

typedef struct  s_data
{
    struct s_player *val;
    struct s_texture *mesh;
}               t_data;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

/* get_next_line.c/ get_next_line_utils.c */
int		ft_strlen(const char *str);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *s1, char const *s2);
char	*ft_substr(char *s, unsigned int start, size_t len);
int		size_line(char *strings, int i);
char	*get_next_line(int fd);

/* init_struct.c */
void	set_null(t_data *game);
void	set_null2(t_data *game);
t_data	*init_struct(void);

/* verif_map.c */
int	who_is_that_player(t_data *game);
int	check_value(t_data *game);
int verif_map(t_data *game);

/* verif_texture.c */
int ft_strncmp(char *s1, char *s2, size_t n);
int texture_on_top(t_data *game);
void send_line_texture(t_data *game, int line, char *msg);
int search_texture(char* word, t_data *game);
int all_texture(t_data *game) ;
int set_first_row(t_data *game);
int lenght(t_data *game, int line);
char *cut_path(t_data *game, int line);
int	path_xpm(char *path);
int	valid_path(char *path);
int check_valid_path(t_data *game);
char *cut_color(t_data *game, int line);
int color_lenght(char *line, int pos);
int range_color(int nb);
int	valid_color(char *line);
int check_color(t_data *game);
int verif_texture(t_data *game);

/* verif_wall.c */
int check_up(t_data *game, int i, int j);
int check_down(t_data *game, int i, int j);
int check_left(t_data *game, int i, int j);
int check_right(t_data *game, int i, int j);
int map_close(t_data *game);

/* main.c */
void	display_map(t_data *game);
int	    len_doc(char *av);
int	count_line(char *av, t_data *game);
void	convert_map(t_data *game, char *av);
int	check_file(char *av);
int main(int ac, char **av);

#endif