/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:32:23 by anmassy           #+#    #+#             */
/*   Updated: 2024/04/03 20:29:49 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

char	*pass_blank(char *temp, int fd)
{
	while (ft_strlen(temp) < 2)
		temp = get_next_line(fd);
	return (temp);
}

char	**dup_map(char **map, int i)
{
	char	**tmp_map;

	tmp_map = 0;
	tmp_map = ft_realloc(map, sizeof(char *) * (i + 1));
	if (!tmp_map)
		ft_exit(1, ERR_MALLOC);
	tmp_map[i + 1] = 0;
	map = tmp_map;
	return (map);
}

void	check_char(t_player *m, char c)
{
	if (c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != '0' && c != '1'
		&& c != ' ' && c != '\n')
		ft_exit(1, ERR_MAP);
	if ((c == 'N' || c == 'S' || c == 'E' || c == 'W') && m->orientation != 0)
		ft_exit(1, ERR_PLAYER);
}

struct s_player	*check_start(struct s_player *m, char *s, int y)
{
	int	i;

	i = 0;
	while (s[i])
	{
		check_char(m, s[i]);
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

void	convert_map(t_data *game, char *av)
{
	int fd;
	char *buf;
	int i;

	i = 0;
	fd = open(av, O_RDONLY);
	game->val->m = NULL;
	//checké precedement, a verfier, apres c'est ube secu
	// if (fd == -1)
		// ft_exit(1, ERR_FILE);
	get_textures(game, fd);
	buf = get_next_line(fd);
	buf = pass_blank(buf, fd);
	while (buf != NULL)
	{
		if (ft_strlen(buf) > 1)
		{
			game->val->m = dup_map(game->val->m, i);
			game->val->m[i] = ft_strdup(buf);
			if (!game->val->m[i])
				ft_exit(1, ERR_MALLOC);
		}
		game->val = check_start(game->val, game->val->m[i], i);
		free(buf);
		buf = get_next_line(fd);
		i++;
	}
	if (game->val->orientation == 0)
		ft_exit(1, ERR_PLAYER);
	close(fd);
}