/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ok.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:12:53 by anmassy           #+#    #+#             */
/*   Updated: 2024/04/08 16:03:13 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

int	skip_space(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	return (i);
}

char	*pass_blank(t_data *game, char *temp)
{
	while (ft_strlen(temp) < 2 && ft_strlen(temp) > 0)
	{
		free(temp);
		temp = get_next_line(game->fd);
	}
	return (temp);
}

char	**dup_map(t_data *game, char **map, int i)
{
	char	**tmp_map;

	tmp_map = 0;
	tmp_map = ft_realloc(map, sizeof(char *) * (i + 1));
	if (!tmp_map)
		ft_exit(game, 1, ERR_MALLOC);
	tmp_map[i + 1] = 0;
	map = tmp_map;
	return (map);
}

int	lenght(char *line, int j)
{
	int	count;

	count = 0;
	while (line[j] && line[j] != '\n')
	{
		while (line[j] == ' ')
			j++;
		while (line[j] != '\n' && line[j] != ' ')
		{
			count++;
			j++;
		}
		return (count);
	}
	return (0);
}
