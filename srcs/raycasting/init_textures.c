/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:31:34 by lmarchai          #+#    #+#             */
/*   Updated: 2024/04/05 19:36:49 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

void	init_text_addr(t_data *game)
{
	game->text[0].addr = (int *)mlx_get_data_addr(game->text[0].mlx_img, \
	&game->text[0].bpp, &game->text[0].line_len, &game->text[0].endian);
	if (!game->text[0].addr)
		exit(1);
	game->text[1].addr = (int *)mlx_get_data_addr(game->text[1].mlx_img, \
	&game->text[1].bpp, &game->text[1].line_len, &game->text[1].endian);
	if (!game->text[1].addr)
		exit(1);
	game->text[2].addr = (int *)mlx_get_data_addr(game->text[2].mlx_img, \
	&game->text[2].bpp, &game->text[2].line_len, &game->text[2].endian);
	if (!game->text[2].addr)
		exit(1);
	game->text[3].addr = (int *)mlx_get_data_addr(game->text[3].mlx_img, \
	&game->text[3].bpp, &game->text[3].line_len, &game->text[3].endian);
	if (!game->text[3].addr)
		exit(1);
}

void	init_text_img(t_data *game)
{
	game->text = calloc(4, sizeof(t_img));
	if (!game->text)
		exit(1);
	game->text[0].mlx_img = mlx_xpm_file_to_image(game->mlx_ptr, \
	game->mesh->w_path, &game->text[0].width, &game->text[0].height);
	if (!game->text[0].mlx_img)
		exit(1);
	game->text[1].mlx_img = mlx_xpm_file_to_image(game->mlx_ptr, \
	game->mesh->e_path, &game->text[1].width, &game->text[1].height);
	if (!game->text[1].mlx_img)
		exit(1);
	game->text[2].mlx_img = mlx_xpm_file_to_image(game->mlx_ptr, \
	game->mesh->n_path, &game->text[2].width, &game->text[2].height);
	if (!game->text[2].mlx_img)
		exit(1);
	game->text[3].mlx_img = mlx_xpm_file_to_image(game->mlx_ptr, \
	game->mesh->s_path, &game->text[3].width, &game->text[3].height);
	if (!game->text[3].mlx_img)
		exit(1);
	init_text_addr(game);
}
