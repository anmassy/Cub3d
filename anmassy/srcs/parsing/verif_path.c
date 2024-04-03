/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:06:37 by anmassy           #+#    #+#             */
/*   Updated: 2024/04/03 04:00:05 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

int lenght(char* line, int j) // compter lee nombre dee ecaractere des path
{
	int count;

	count = 0;
	while (line[j] != '\n')
	{
		while (line[j] == ' ')
			j++;
		while (line[j] != '\n' && line[j] != ' ')
		{
			count++;
			j++;
		}
		return (count);
	}
	return (0);
}

typedef enum { NO = 0, SO = 1, EA = 2, WE = 3, F = 4, C = 5} elements;

int search_texture(char* word, char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (ft_strncmp(line + i, word, ft_strlen(word)) == 0)
		return (0);
	return (1);
}

int find_elements(char *line) 
{
	if (search_texture("NO", line) == 0)
		return (NO);
	else if (search_texture("SO", line) == 0)
		return (SO);
	else if (search_texture("EA", line) == 0)
		return (EA);
	else if (search_texture("WE", line) == 0)
		return (WE);
	else if (search_texture("F", line) == 0)
		return (F);
	else if (search_texture("C", line) == 0)
		return (C);
	return (0);
}

char *get_path(char *line, int j)
{
	int i;
	int len_path;
	char *path;
	
	i = 0;
	len_path = lenght(line, j);
	path = malloc(sizeof(char) * len_path + 2);
	while (line[j] != '\n')
	{
		while (line[j] == ' ')
			j++;
		while (line[j] != '\n' && line[j] != ' ')
			path[i++] = line[j++];
		path[i] = '\0';
		while (line[j] != '\n')
		{
			if (line[j] != ' ')
				return(free(path), NULL);
			j++;
		}
		return (path);
	}
	return (free(path), NULL);
}

void	set_path(t_data *game, char *line, char *element)
{

	if (ft_strncmp(element, "NO", 2) == 0)
		game->mesh->n_path = line;
	else if (ft_strncmp(element, "SO", 2) == 0)
		game->mesh->s_path = line;
	else if (ft_strncmp(element, "EA", 2) == 0)
		game->mesh->e_path = line;
	else if (ft_strncmp(element, "WE", 2) == 0)
		game->mesh->w_path = line;
	else if (ft_strncmp(element, "F", 1) == 0)
		game->mesh->f_color = line;
	else if (ft_strncmp(element, "C", 1) == 0)
		game->mesh->c_color = line;
}

void	cut_path(t_data *game, char *line) //recuperer seulement la parcelle de path donc a partir du / puis faire open deessu afin de savoir si on peut l'ouvrir ou non, si un des 4 fichier de s'ouvree pas return erreur
{
	int j;
	int element;
	char *path;
	char *elements[6];

	elements[0] = "NO";
	elements[1] = "SO";
	elements[2] = "EA";
	elements[3] = "WE";
	elements[4] = "F";
	elements[5] = "C";
	
	element = find_elements(line);
	j = ft_strstr(line, elements[element]);
	path = get_path(line, j);
	if (path != NULL)
		set_path(game, path, elements[element]);
}

int	all_textures(t_data *game)
{
	if (game->mesh->n_path == NULL)
		return (1);
	if (game->mesh->s_path == NULL)
		return (1);
	if (game->mesh->e_path == NULL)
		return (1);
	if (game->mesh->w_path == NULL)
		return (1);
	if (game->mesh->c_color == NULL)
		return (1);
	if (game->mesh->f_color == NULL)
		return (1);
	return (0);
}

void get_textures(t_data *game, int fd)
{
	char	*temp;
	int 	i;

	i = 0;
	while (all_textures(game) != 0)
	{
		temp = get_next_line(fd);
		cut_path(game, temp);
		free(temp);
		i++;
	}
}

int	path_xpm(char *path)
{
	char	s[4];
	int		i;
	int		j;

	i = ft_strlen(path) - 4;
	j = 0;
	while (path[i])
		s[j++] = path[i++];
	if (ft_strncmp(s, ".xpm", 4) == 0)
		return (1);
	printf("the file must be a .xpm\n");
	return (0);
}

int verif_path(t_data *game)
{
	if (path_xpm(game->mesh->n_path) == 0 ||
		path_xpm(game->mesh->s_path) == 0 ||
		path_xpm(game->mesh->e_path) == 0 ||
		path_xpm(game->mesh->w_path) == 0)
		return (0);
	if (file_exist(game->mesh->n_path) == 0 ||
		file_exist(game->mesh->s_path) == 0 ||
		file_exist(game->mesh->e_path) == 0 ||
		file_exist(game->mesh->w_path) == 0)
		return (0);
	return (1);
}