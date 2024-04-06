/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycastings.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:32:22 by lmarchai          #+#    #+#             */
/*   Updated: 2024/04/06 16:49:02 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

void	destroy_textures(t_data *game)
{
	if (game->text[0].mlx_img)
		mlx_destroy_image(game->mlx_ptr, game->text[0].mlx_img);
	if (game->text[1].mlx_img)
		mlx_destroy_image(game->mlx_ptr, game->text[1].mlx_img);
	if (game->text[2].mlx_img)
		mlx_destroy_image(game->mlx_ptr, game->text[2].mlx_img);
	if (game->text[3].mlx_img)
		mlx_destroy_image(game->mlx_ptr, game->text[3].mlx_img);
	free(game->text);
}

void	free_game(t_data *game)
{
	if (game->mlx_ptr != NULL)
	{
		destroy_textures(game);
		if (game->img.mlx_img != NULL)
			mlx_destroy_image(game->mlx_ptr, game->img.mlx_img);
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	ft_free(game);
	exit(1);
}

int	hook(void *dt)
{
	t_data	*game;

	game = dt;
	if (game->img.mlx_img)
		mlx_destroy_image(game->mlx_ptr, game->img.mlx_img);
	game->img.mlx_img = mlx_new_image(game->mlx_ptr, SCREENWIDTH, SCREENHEIGHT);
	if (!game->img.mlx_img)
		free_game(game);
	game->img.addr = (int *)mlx_get_data_addr(game->img.mlx_img, \
		&game->img.bpp, &game->img.line_len, &game->img.endian);
	if (!game->img.addr)
		free_game(game);
	raycast(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, \
		game->img.mlx_img, 0, 0);
	move(game);
	return (0);
}

void	start_game(t_data *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		free_game(game);
	init_game(game);
	game->win_ptr = mlx_new_window(game->mlx_ptr, \
		SCREENWIDTH, SCREENHEIGHT, "Cub3d");
	if (!game->win_ptr)
		free_game(game);
	mlx_hook(game->win_ptr, 2, 1L << 0, key_hook, game);
	mlx_hook(game->win_ptr, 3, 1L << 1, key_release, game);
	mlx_loop_hook(game->mlx_ptr, &hook, game);
	mlx_hook(game->win_ptr, 17, 1L << 17, &handle_click_end, game);
	mlx_loop(game->mlx_ptr);
}
