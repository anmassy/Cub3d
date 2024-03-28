/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:09:36 by anmassy           #+#    #+#             */
/*   Updated: 2024/03/28 13:24:27 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

void send_line_texture(t_data *game, int line, char *msg)
{
	if (ft_strncmp(msg, "NO", 2) == 0)
		game->mesh->north_line = line;
	else if (ft_strncmp(msg, "SO", 2) == 0)
		game->mesh->south_line = line;
	else if (ft_strncmp(msg, "EA", 2) == 0)
		game->mesh->east_line = line;
	else if (ft_strncmp(msg, "WE", 2) == 0)
		game->mesh->west_line = line;
	else if (ft_strncmp(msg, "F",1) == 0)
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
				count++;
				send_line_texture(game, i, word); //permet de recuperer la ligne ou se trouve les texture afin de pouvoir verifier seulement cette ligne pour le path
				if (i > game->val->last_row && count == 1)
					game->val->last_row = i;
			}
			if (!game->val->map[i + 1])
			{
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
		printf("the file must contain all the following characteristics (NO, SO, EA, WE, F, C)\n");
		return (0);
	}
	return (1);
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
				printf("one or more elements are out of place or too many in the map\n");
				return (0);
			}
			if (i == game->val->last_row)
				return (1);	
			i++;
			j = 0;
		}
	}
	return (0);
}

int verif_texture(t_data *game)
{
	if (all_texture(game) == 0) //permet de savoir si "NO, SO, EA, WE, F, C" sont bien dans le fichier map.
		return (0);
	if (texture_on_top(game) == 0) //permet de savoir si toute les texture son au top du fichier et qu'il n'y a pas de ligne en trop ou defectueuse avec des caractere random
		return (0);
	if (verif_path(game) == 0) //permet de savoir si le path des texture est correct
		return (0);
	if (verif_color(game) == 0) //check si la couleur est bonne ou non avec la bonne range [0 - 255]
		return (0);
	return (1);
}