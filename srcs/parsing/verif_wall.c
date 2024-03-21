/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:01:46 by anmassy           #+#    #+#             */
/*   Updated: 2024/03/21 19:19:08 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

int check_up(t_data *game, int i, int j)
{
	if (i == game->val->first_row)
		return (0);
	if (game->val->map[i - 1][j] != '1' && 
		game->val->map[i - 1][j] != '0' &&
		game->val->map[i - 1][j] != 'N' &&
		game->val->map[i - 1][j] != 'S' &&
		game->val->map[i - 1][j] != 'E' &&
		game->val->map[i - 1][j] != 'W')
		return (0);
	return (1);
}

int check_down(t_data *game, int i, int j)
{
	if (i == game->val->height)
		return (0);
	if (game->val->map[i + 1][j] != '1' && 
		game->val->map[i + 1][j] != '0' &&
		game->val->map[i + 1][j] != 'N' &&
		game->val->map[i + 1][j] != 'S' &&
		game->val->map[i + 1][j] != 'E' &&
		game->val->map[i + 1][j] != 'W')
		return (0);
	return (1);
}

int check_left(t_data *game, int i, int j)
{
	if (game->val->map[i][j - 1] != '1' && 
		game->val->map[i][j - 1] != '0' &&
		game->val->map[i][j - 1] != 'N' &&
		game->val->map[i][j - 1] != 'S' &&
		game->val->map[i][j - 1] != 'E' &&
		game->val->map[i][j - 1] != 'W')
		return (0);
	return (1);
}

int check_right(t_data *game, int i, int j)
{
	if (game->val->map[i][j + 1] != '1' && 
		game->val->map[i][j + 1] != '0' &&
		game->val->map[i][j + 1] != 'N' &&
		game->val->map[i][j + 1] != 'S' &&
		game->val->map[i][j + 1] != 'E' &&
		game->val->map[i][j + 1] != 'W')
		return (0);
	return (1);
}

int map_close(t_data *game)
{
	int i;
	int j;
	
	i = game->val->first_row;
	while (game->val->map[i])
	{
		j = 0;
		while (game->val->map[i][j] && game->val->map[i][j] != '\n')
		{
			if (game->val->map[i][j] == '0' || game->val->map[i][j] == 'N' ||
				game->val->map[i][j] == 'S' || game->val->map[i][j] == 'E' ||
				game->val->map[i][j] == 'W')
				if (check_up(game, i, j) == 0 ||
					check_down(game, i, j) == 0 ||
					check_left(game, i, j) == 0 ||
					check_right(game, i, j) == 0)
				{
					printf("%s\n", "la map est ouverte");
					return (0);
				}
			j++;
		}
		i++;	
	}
	printf("%s\n", "map bien fermé");
	return (1);
}