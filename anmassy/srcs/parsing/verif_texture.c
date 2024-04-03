/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:09:36 by anmassy           #+#    #+#             */
/*   Updated: 2024/04/03 13:42:41 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

int	texture_on_top(t_data *game)
{
	int i;
	int j;

	i = 0;
	while (game->val->m[i])
	{
		j = 0;
		while (game->val->m[i][j])
		{
			while (game->val->m[i][j] == ' ')
				j++;
			if (ft_strncmp(game->val->m[i] + j, "NO", 2)
				&& ft_strncmp(game->val->m[i] + j, "SO", 2)
				&& ft_strncmp(game->val->m[i] + j, "EA", 2)
				&& ft_strncmp(game->val->m[i] + j, "WE", 2)
				&& ft_strncmp(game->val->m[i] + j, "F", 1)
				&& ft_strncmp(game->val->m[i] + j, "C", 1)
				&& ft_strncmp(game->val->m[i] + j, "\n", 1))
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