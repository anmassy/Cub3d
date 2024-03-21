/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:03:05 by anmassy           #+#    #+#             */
/*   Updated: 2024/03/21 19:35:49 by anmassy          ###   ########.fr       */
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
				printf("%s\n", "la map n'est pas comforme au caractere demandé");
				return (0);
			}
			j++;
		}
		i++;
	}
	if (who_is_that_player(game) == 0)
	{
		printf("%s\n", "il y a trop ou pas pas assez de joueur");
		return (0);
	}
	return (1);
}

int verif_map(t_data *game)
{
	if (check_value(game) == 0) //check si la map a bieen les bonne valeur
		return (0);
	if (map_close(game) == 0) //check si la map est bien entourer de mur
		return (0);
	return (1);
}