/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:06:11 by anmassy           #+#    #+#             */
/*   Updated: 2024/03/28 13:20:38 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

char	*cut_color(t_data *game, int line)
{
	char *path;
	int i;
	int j;
	int len;

	i = 0;
	j = 0;
	len = lenght(game, line, j);
	path = malloc(sizeof(char) * len + 1);
	while (game->val->map[line][j] != '\n')
	{
		while (!(game->val->map[line][j] >= '0' && game->val->map[line][j] <= '9'))
			j++;
		while (game->val->map[line][j] != '\n' && game->val->map[line][j] != ' ')
			path[i++] = game->val->map[line][j++];
		path[i] = '\0';
		return (path);
	}
	return (NULL);
}

int color_lenght(char *line, int pos)
{
	int i;

	i = 0;
	while (line[pos] != ',' && line[pos] != '\0' && line[pos] != ' ') // changer la condition
	{
		if ((line[pos] >= '0' && line[pos] <= '9') || line[i] == '-')
			i++;
		pos++;
	}
	// printf("len = %d\n", i);
	return (i);
}

int range_color(int nb)
{
	if (nb >= 0 && nb <= 255)
		return (1);
	return (0);
}

int	valid_color(char *line) //la fonction qui sert a egardr si on est bien entre 0 et 255
{
	int i;
	int j;
	char *temp;
	int len;

	i = 0;
	while (line[i])
	{
		len = color_lenght(line, i);
		temp = malloc (sizeof(char) * len + 1);
		if (!temp)
			return (0);
		j = 0;
		while (line[i] != ',' && line[i] != '\0' && line[i + 1] != ' ')
		{
			if ((line[i] >= '0' && line[i] <= '9') || line[i] == '-')
				temp[j++] = line[i++];
		}
		j = atoi(temp); //refaire atoi
		// printf("%d\n", j);
		if (range_color(j) == 0)
			return (0);
		free(temp);
	   	i++;
	}
	return (1);
}

int verif_color(t_data *game)
{
	game->mesh->ceiling_pigmentation = cut_color(game, game->mesh->ceiling_line);
	game->mesh->floor_pigmentation = cut_color(game, game->mesh->floor_line);
	if (valid_color(game->mesh->ceiling_pigmentation) == 0 ||
		valid_color(game->mesh->floor_pigmentation) == 0)
		return (0);
	return (1);
}
