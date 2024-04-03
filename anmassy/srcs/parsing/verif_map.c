/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:03:05 by anmassy           #+#    #+#             */
/*   Updated: 2024/04/03 15:02:58 by anmassy          ###   ########.fr       */
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
	while (game->val->m[i])
	{
		j = 0;
		while (game->val->m[i][j])
		{
			if (game->val->m[i][j] == 'N' || game->val->m[i][j] == 'S'
				|| game->val->m[i][j] == 'E' || game->val->m[i][j] == 'W')
			{
				game->val->orientation = game->val->m[i][j];
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
	while (game->val->m[i])
	{
		j = 0;
		while (game->val->m[i][j] == ' ')
			j++;
		while (game->val->m[i][j] && game->val->m[i][j] != '\n')
		{
			if (game->val->m[i][j] != '1' && game->val->m[i][j] != '0'
				&& game->val->m[i][j] != 'N' && game->val->m[i][j] != 'S'
				&& game->val->m[i][j] != 'E' && game->val->m[i][j] != 'W'
				&& game->val->m[i][j] != ' ')
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

int	set_first_row(t_data *game)
{
	int	i;
	int	j;

	i = game->val->last_row;
	while (game->val->m[i])
	{
		j = 0;
		while (game->val->m[i][j] || game->val->m[i][j] == '\n')
		{
			if (game->val->m[i][j] != ' ' && game->val->m[i][j] != '\n')
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

int	verif_map(t_data *game)
{
	if (check_value(game) == 0)
		return (0);
	if (map_close(game) == 0)
		return (0);
	return (1);
}
