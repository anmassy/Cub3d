/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:16:08 by anmassy           #+#    #+#             */
/*   Updated: 2024/03/22 18:06:42 by anmassy          ###   ########.fr       */
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

void	set_null3(t_data *game)
{
	game->img->mlx = NULL;
	game->img->window = NULL;
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
	game->img = malloc(sizeof(t_image)); 
	if (!game->img)
	{
		free(game);
		return (NULL);
	}
	set_null(game);
	set_null2(game);
	set_null3(game);
	return (game);
}