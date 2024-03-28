/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:06:37 by anmassy           #+#    #+#             */
/*   Updated: 2024/03/28 13:17:59 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

int lenght(t_data *game, int line, int j) // compter lee nombre dee ecaractere des path
{
	int count;

	count = 0;
	while (game->val->map[line][j + 1] != '\n')
	{
		while (game->val->map[line][j] == ' ')
			j++;
		while (game->val->map[line][j + 1] != '\n' && game->val->map[line][j] != ' ')
		{
			count++;
			j++;
		}
		return (count);
	}
	return (0);
}

char *cut_path(t_data *game, int line, char *element) //recuperer seulement la parcelle de path donc a partir du / puis faire open deessu afin de savoir si on peut l'ouvrir ou non, si un des 4 fichier de s'ouvree pas return erreur
{
	char *path;
	int i;
	int j;
	int len_path;

	i = 0;
	j = ft_strstr(game->val->map[line], element);
	len_path = lenght(game, line, j);
	path = malloc(sizeof(char) * len_path + 1);
	while (game->val->map[line][j] != '\n')
	{
		while (game->val->map[line][j] == ' ')
			j++;
		while (game->val->map[line][j] != '\n' && game->val->map[line][j] != ' ')
			path[i++] = game->val->map[line][j++];
		path[i] = '\0';
		while (game->val->map[line][j] != '\n')
		{
			if (game->val->map[line][j] != ' ')
				return("INVALID PATH");
			j++;
		}
		return (path);
	}
	return (NULL);
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
	game->mesh->north_path = cut_path(game, game->mesh->north_line, "NO");
	game->mesh->south_path = cut_path(game, game->mesh->south_line, "SO");
	game->mesh->east_path = cut_path(game, game->mesh->east_line, "EA");
	game->mesh->west_path = cut_path(game, game->mesh->west_line, "WE");
	if (path_xpm(game->mesh->north_path) == 0 ||
		path_xpm(game->mesh->south_path) == 0 ||
		path_xpm(game->mesh->east_path) == 0 ||
		path_xpm(game->mesh->west_path) == 0)
		return (0);
	if (file_exist(game->mesh->north_path) == 0 ||
		file_exist(game->mesh->south_path) == 0 ||
		file_exist(game->mesh->east_path) == 0 ||
		file_exist(game->mesh->west_path) == 0)
		return (0);
	return (1);
}