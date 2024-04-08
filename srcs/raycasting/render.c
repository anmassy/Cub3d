/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:33:02 by lmarchai          #+#    #+#             */
/*   Updated: 2024/04/08 15:51:04 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

int	pass_to_comas(char *s, int nb)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (s[i] && found < nb)
	{
		if (s[i] == ',')
			found++;
		i++;
	}
	return (i);
}

int	rgb(char *rgb)
{
	int	red;
	int	green;
	int	blue;

	red = atoi(rgb);
	green = ft_atoi(rgb + pass_to_comas(rgb, 1));
	blue = ft_atoi(rgb + pass_to_comas(rgb, 2));
	return (((red & 0x0ff) << 16) | ((green & 0x0ff) << 8) | (blue & 0x0ff));
}

t_print	init_print(t_data *game)
{
	t_print	p;

	p.y = 0;
	p.lineheight = (int)SCREENHEIGHT / game->rayc.perpwalldist;
	p.drawstart = (-1 * p.lineheight) / 2 + SCREENHEIGHT / 2;
	if (p.drawstart < 0)
		p.drawstart = 0;
	p.drawend = p.lineheight / 2 + SCREENHEIGHT / 2;
	if (p.drawend >= SCREENHEIGHT)
		p.drawend = SCREENHEIGHT - 1;
	ft_init_texture(game);
	game->rayc.texx = (int)(game->rayc.wallx \
		* (double)game->text[game->rayc.textdir].width);
	if (game->rayc.side == 0 && game->rayc.raydirx > 0)
		game->rayc.texx = game->text[game->rayc.textdir].width \
			- game->rayc.texx - 1;
	if (game->rayc.side == 1 && game->rayc.raydiry < 0)
		game->rayc.texx = game->text[game->rayc.textdir].width \
			- game->rayc.texx - 1;
	p.step = 1.0 * game->text[game->rayc.textdir].height / p.lineheight;
	p.texpos = (p.drawstart - SCREENHEIGHT / 2 + p.lineheight / 2) * p.step;
	return (p);
}

void	print_col(t_data *game, int x)
{
	t_print	p;

	p = init_print(game);
	while (p.y <= SCREENHEIGHT)
	{
		if (p.y >= p.drawstart && p.y <= p.drawend)
		{
			p.texy = (int)p.texpos & \
				(game->text[game->rayc.textdir].height - 1);
			p.texpos += p.step;
			p.color = game->text[game->rayc.textdir].addr[p.texy \
				* game->text[game->rayc.textdir].line_len / 4 \
				+ game->rayc.texx];
			game->img.addr[p.y * game->img.line_len / 4 + x] = p.color;
		}
		else if (p.y > p.drawend)
			game->img.addr[p.y * game->img.line_len / 4 + x] \
			= rgb(game->mesh->f_color);
		else
			game->img.addr[p.y * game->img.line_len / 4 + x] \
			= rgb(game->mesh->c_color);
		p.y++;
	}
}
