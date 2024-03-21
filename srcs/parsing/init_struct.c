/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:16:08 by anmassy           #+#    #+#             */
/*   Updated: 2024/03/21 19:35:25 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

void	set_null(t_data *game)
{
	game->val->map = NULL;
    game->val->first_row = 0;
    game->val->last_row = 0;
    // game->val->orientation = NULL;
	game->val->height = 0;   
}

void	set_null2(t_data *game)
{
	game->mesh->north_line = 0;
    game->mesh->south_line = 0;
    game->mesh->east_line = 0;
    game->mesh->west_line = 0;
    game->mesh->floor_line = 0;
    game->mesh->ceiling_line = 0;
    game->mesh->north_path = NULL;
	game->mesh->south_path = NULL;
	game->mesh->east_path = NULL;
	game->mesh->west_path = NULL;
    game->mesh->ceiling_pigmentation = NULL;
    game->mesh->floor_pigmentation = NULL;
}

t_data	*init_struct(void)
{
	t_data	*game;

	game = malloc(sizeof(t_data));
	if (!game)
		return (NULL);
	game->val = malloc(sizeof(t_player)); 
	if (!game->val)
	{
		free(game);
		return (NULL);
	}
	game->mesh = malloc(sizeof(t_texture)); 
	if (!game->mesh)
	{
		free(game);
		return (NULL);
	}
	set_null(game);
	set_null2(game);
	return (game);
}