/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:32:23 by anmassy           #+#    #+#             */
/*   Updated: 2024/04/08 15:30:42 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

int	check_char(t_data *game, t_player *m, char c)
{
	if (c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != '0' && c != '1'
		&& c != ' ' && c != '\n')
	{
		close(game->fd);
		ft_exit(game, 1, ERR_MAP);
	}
	if ((c == 'N' || c == 'S' || c == 'E' || c == 'W') && m->orientation != 0)
	{
		close(game->fd);
		ft_exit(game, 1, ERR_MAP);
	}
	return (1);
}

struct s_player	*check_start(t_data *game, struct s_player *m, char *s, int y)
{
	int	i;

	i = 0;
	if (!s)
		return (m);
	while (s[i])
	{
		check_char(game, m, s[i]);
		if (s[i] == 'N' || s[i] == 'S' || s[i] == 'E' || s[i] == 'W')
		{
			m->startY = (double)y;
			m->startX = (double)i;
		}
		if (s[i] == 'N')
			m->orientation = 'N';
		else if (s[i] == 'S')
			m->orientation = 'S';
		else if (s[i] == 'E')
			m->orientation = 'E';
		else if (s[i] == 'W')
			m->orientation = 'W';
		i++;
	}
	return (m);
}

void	convert_map2(t_data *game)
{
	int		i;
	char	*buf;

	i = 0;
	buf = get_next_line(game->fd);
	buf = pass_blank(game, buf);
	if (buf == NULL)
		return ;
	while (buf != NULL)
	{
		if (ft_strlen(buf) > 1)
		{
			game->val->m = dup_map(game, game->val->m, i);
			game->val->m[i] = ft_strdup(buf);
			if (!game->val->m[i])
				ft_exit(game, 1, ERR_MALLOC);
			free(buf);
			game->val = check_start(game, game->val, game->val->m[i], i);
		}
		else
			break ;
		buf = get_next_line(game->fd);
		i++;
	}
	free(buf);
}

void	convert_map(t_data *game, char *av)
{
	char	*buf;

	game->fd = open(av, O_RDONLY);
	get_textures(game);
	convert_map2(game);
	buf = get_next_line(game->fd);
	while (buf != NULL)
	{
		if (ft_strlen(buf) > 1)
		{
			close(game->fd);
			free(buf);
			ft_exit(game, 1, MAP_ERROR);
		}
		free(buf);
		buf = get_next_line(game->fd);
	}
	free(buf);
	close(game->fd);
}
