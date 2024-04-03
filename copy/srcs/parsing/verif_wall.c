/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:01:46 by anmassy           #+#    #+#             */
/*   Updated: 2024/04/03 04:40:21 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

int check_up(t_data *game, int i, int j)
{
	if (i == game->val->first_row)
		return (0);
	if (game->val->m[i - 1][j] != '1' && 
		game->val->m[i - 1][j] != '0' &&
		game->val->m[i - 1][j] != 'N' &&
		game->val->m[i - 1][j] != 'S' &&
		game->val->m[i - 1][j] != 'E' &&
		game->val->m[i - 1][j] != 'W')
		return (0);
	return (1);
}

int check_down(t_data *game, int i, int j)
{
	if (i == game->val->y)
		return (0);
	if (game->val->m[i + 1][j] != '1' && 
		game->val->m[i + 1][j] != '0' &&
		game->val->m[i + 1][j] != 'N' &&
		game->val->m[i + 1][j] != 'S' &&
		game->val->m[i + 1][j] != 'E' &&
		game->val->m[i + 1][j] != 'W')
		return (0);
	return (1);
}

int check_left(t_data *game, int i, int j)
{
	if (game->val->m[i][j - 1] != '1' && 
		game->val->m[i][j - 1] != '0' &&
		game->val->m[i][j - 1] != 'N' &&
		game->val->m[i][j - 1] != 'S' &&
		game->val->m[i][j - 1] != 'E' &&
		game->val->m[i][j - 1] != 'W')
		return (0);
	return (1);
}

int check_right(t_data *game, int i, int j)
{
	if (game->val->m[i][j + 1] != '1' && 
		game->val->m[i][j + 1] != '0' &&
		game->val->m[i][j + 1] != 'N' &&
		game->val->m[i][j + 1] != 'S' &&
		game->val->m[i][j + 1] != 'E' &&
		game->val->m[i][j + 1] != 'W')
		return (0);
	return (1);
}

int map_close(t_data *game)
{
	int i;
	int j;
	
	i = game->val->first_row;
	while (game->val->m[i])
	{
		j = 0;
		while (game->val->m[i][j] && game->val->m[i][j] != '\n')
		{
			if (game->val->m[i][j] == '0' || game->val->m[i][j] == 'N' ||
				game->val->m[i][j] == 'S' || game->val->m[i][j] == 'E' ||
				game->val->m[i][j] == 'W')
				if (check_up(game, i, j) == 0 ||
					check_down(game, i, j) == 0 ||
					check_left(game, i, j) == 0 ||
					check_right(game, i, j) == 0)
				{
					printf("the map is not closed\n");
					return (0);
				}
			j++;
		}
		i++;	
	}
	return (1);
}