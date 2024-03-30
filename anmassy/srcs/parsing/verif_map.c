/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:03:05 by anmassy           #+#    #+#             */
/*   Updated: 2024/03/30 10:40:33 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"


int	who_is_that_player(t_data *game)
{
	int	i;
	int	j;
	int	count;

	i = game->val->last_row;
	count = 0;
	while (game->val->map[i])
	{
		j = 0;
		while (game->val->map[i][j])
		{
			if (game->val->map[i][j] == 'N' ||
				game->val->map[i][j] == 'S' ||
				game->val->map[i][j] == 'E' ||
				game->val->map[i][j] == 'W')
			{
				game->val->orientation = game->val->map[i][j];
				count++;
			}
			j++;
		}
		i++;
	}
	if (count != 1)
		return (0);
	return (1);
}

int	check_value(t_data *game)
{
	int	i;
	int	j;

	i = game->val->first_row;
	while (game->val->map[i])
	{
		j = 0;
		while (game->val->map[i][j] == ' ')
			j++;
		while (game->val->map[i][j] && game->val->map[i][j] != '\n')
		{
			if (game->val->map[i][j] != '1' && game->val->map[i][j] != '0'
				&& game->val->map[i][j] != 'N' && game->val->map[i][j] != 'S'
				&& game->val->map[i][j] != 'E' && game->val->map[i][j] != 'W'
				&& game->val->map[i][j] != ' ')
			{
				printf("the map contains incorect elements\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	if (who_is_that_player(game) == 0)
	{
		printf("there are too many/ too low players in the map\n");
		return (0);
	}
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
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int verif_map(t_data *game)
{
	if (set_first_row(game) == 0)
		return (0);
	set_size_map(game);
	if (check_value(game) == 0) //check si la map a bieen les bonne valeur
		return (0);
	if (map_close(game) == 0) //check si la map est bien entourer de mur
		return (0);
	return (1);
}