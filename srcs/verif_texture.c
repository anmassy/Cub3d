/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 12:53:33 by anmassy           #+#    #+#             */
/*   Updated: 2024/03/20 22:26:41 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3d.h"

int ft_strncmp(char *s1, char *s2, size_t n)
{
	while(n--)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		if (*s1 == '\0')
			break;
		s1++;
		s2++;
	}
	return (0);
}

int texture_on_top(t_data *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->val->map[i])
	{
		j = 0;
		while (game->val->map[i][j])
		{
			while (game->val->map[i][j] == ' ')
				j++;
			if (ft_strncmp(game->val->map[i] + j, "NO", 2) &&
				ft_strncmp(game->val->map[i] + j, "SO", 2) &&
				ft_strncmp(game->val->map[i] + j, "EA", 2) &&
				ft_strncmp(game->val->map[i] + j, "WE", 2) &&
				ft_strncmp(game->val->map[i] + j, "F", 1) &&
				ft_strncmp(game->val->map[i] + j, "C", 1) &&
				ft_strncmp(game->val->map[i] + j, "\n", 1))
			{
				printf("%s\n", "les texture ne sont pas au top du fichier ou il y a des caractere genant");
				return (0);
			}
			if (i == game->val->last_row)
			{
				printf("%s\n", "les texture sont bien entreposé au top");
				return (1);	
			}
			i++;
			j = 0;
		}
	}
}

void send_line_texture(t_data *game, int line, char *msg)
{
	if (msg == "NO")
		game->mesh->north_line = line;
	else if (msg == "SO")
		game->mesh->south_line = line;
	else if (msg == "EA")
		game->mesh->east_line = line;
	else if (msg == "WE")
		game->mesh->west_line = line;
	else if (msg == "F")
		game->mesh->floor_line = line;
	else
		game->mesh->ceiling_line = line;
}

int search_texture(char* word, t_data *game)
{
	int	i;
	int	j;
	int count;

	i = 0;
	count = 0;
	while (game->val->map[i])
	{
		j = 0;
		while (game->val->map[i][j])
		{
			while (game->val->map[i][j] == ' ')
				j++;
			if (ft_strncmp(game->val->map[i] + j, word, ft_strlen(word)) == 0)
			{
				// printf("texture = %s\ni = %d\nj = %d\n", word, i, j);
				count++;
				send_line_texture(game, i, word); //permet de recuperer la ligne ou se trouve les texture afin de pouvoir verifier seulement cette ligne pour le path
				if (i > game->val->last_row && count == 1)
					game->val->last_row = i;
			}
			if (!game->val->map[i + 1])
			{
				// printf("last_row =%d\n", game->val->last_row);
				if (count != 1)
					return (0);
				return (1);	
			}
			i++;
			j = 0;
		}
	}
	return (1);
}

int all_texture(t_data *game) 
{
	if (search_texture("NO", game) == 0 ||
		search_texture("SO", game) == 0 ||
		search_texture("EA", game) == 0 ||
		search_texture("WE", game) == 0 ||
		search_texture("F", game) == 0 ||
		search_texture("C", game) == 0)
	{
		printf("%s\n", "il manque des textures");
		return (0);
	}
	printf("%s\n", "toute les textures sont presente");
	return (1);
}

int set_first_row(t_data *game)
{
	int	i;
	int	j;

	i = game->val->last_row + 1;
	while (game->val->map[i])
	{
		j = 0;
		while (game->val->map[i][j] || game->val->map[i][j] == '\n')
		{
			if (game->val->map[i][j] != ' ' && game->val->map[i][j] != '\n')
			{
				game->val->first_row = i;
				// printf("%d\n", game->val->first_row);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int lenght(t_data *game, int line) // compter lee nombre dee ecaractere des path
{
	int j;
	int count;

	j = 0;
	count = 0;
	while (game->val->map[line][j] != '\n')
	{
		while (game->val->map[line][j] != '/')
			j++;
		while (game->val->map[line][j] != '\n' && game->val->map[line][j] != ' ')
		{
			count++;
			j++;
		}
		return (count);
	}
	return (0);
}

char *cut_path(t_data *game, int line) //recuperer seulement la parcelle de path donc a partir du / puis faire open deessu afin de savoir si on peut l'ouvrir ou non, si un des 4 fichier de s'ouvree pas return erreur
{
	char *path;
	int i;
	int j;
	int len_path;

	i = 0;
	j = 0;
	len_path = lenght(game, line);
	path = malloc(sizeof(char) * len_path + 1);
	while (game->val->map[line][j] != '\n')
	{
		while (game->val->map[line][j] != '/')
			j++;
		while (game->val->map[line][j] != '\n' && game->val->map[line][j] != ' ')
			path[i++] = game->val->map[line][j++];
		path[i] = '\0';
		return (path);
	}
	return (NULL);
}

int	path_xpm(char *path)
{
	char	s[4];
	int		i;
	int		j;

	printf("path = %s\n", path);
	i = ft_strlen(path) - 4;
	j = 0;
	while (path[i])
		s[j++] = path[i++];
	if (ft_strncmp(s, ".xpm", 4) == 0)
		return (1);
	printf("%s\n", "le fichier doit etre un .xpm");
	return (0);
}

int	valid_path(char *path)
{
    int fd;
	
	fd = open(path, O_RDONLY);
	printf("fd = %d\n", fd);
    if (fd != -1)
	{
        close(fd);
        return (1);
    }
	else 
        return (0);
}

int check_valid_path(t_data *game)
{
	game->mesh->north_path = cut_path(game, game->mesh->north_line);
	game->mesh->south_path = cut_path(game, game->mesh->south_line);
	game->mesh->east_path = cut_path(game, game->mesh->east_line);
	game->mesh->west_path = cut_path(game, game->mesh->west_line);
	if (path_xpm(game->mesh->north_path) == 0 ||
		path_xpm(game->mesh->south_path) == 0 ||
		path_xpm(game->mesh->east_path) == 0 ||
		path_xpm(game->mesh->west_path) == 0)
		return (0);
	if (valid_path(game->mesh->north_path) == 0 ||
		valid_path(game->mesh->south_path) == 0 ||
		valid_path(game->mesh->east_path) == 0 ||
		valid_path(game->mesh->west_path) == 0)
		return (0);
	return (1);
}

char	*cut_color(t_data *game, int line)
{
	char *path;
	int i;
	int j;
	int len;

	i = 0;
	j = 0;
	len = lenght(game, line);
	path = malloc(sizeof(char) * len + 1);
	while (game->val->map[line][j] != '\n')
	{
		while (game->val->map[line][j] != ' ')
			j++;
		while (game->val->map[line][j] != '\n' && game->val->map[line][j] != ' ')
			path[i++] = game->val->map[line][j++];
		path[i] = '\0';
		return (path);
	}
	return (NULL);
}

int	valid_color(char *line) //je me suis arreter la fonction qui sert a egardr si on est bien entre 0 et 255
{

}

int check_color(t_data *game)
{
	game->mesh->ceiling_pigmentation = cut_color(game, game->mesh->ceiling_line);
	game->mesh->floor_pigmentation = cut_color(game, game->mesh->floor_line);
	if (valid_color(game->mesh->ceiling_pigmentation) == 0 ||
		valid_color(game->mesh->floor_pigmentation) == 0)
		return (0);
}

int verif_texture(t_data *game)
{
	if (all_texture(game) == 0) //permet de savoir si "NO, SO, EA, WE, F, C" sont bien dans le fichier map.
		return (0);
	if (texture_on_top(game) == 0) //permet de savoir si toute les texture son au top du fichier et qu'il n'y a pas de ligne en trop ou defectueuse avec des caractere random
		return (0);
	//penser a check si la ligne du path est correct et que il n'y a pas ecrit un truc chelou avant ou apres le path, idem pour la pigmentation
	// if (check_valid_path(game) == 0) //permet de savoir si le path des texture est correct
	// 	return (0);
	if (check_color(game) == 0)
		return (0);
	set_first_row(game); //permet de set la premiere ligne ou commence la map
	return (1);
}