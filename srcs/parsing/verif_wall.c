/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:01:46 by anmassy           #+#    #+#             */
/*   Updated: 2024/04/05 20:02:32 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

int skip_space(char *line)
{
    int i;

    i = 0;
    while(line[i] && line[i] == ' ')
        i++;
    return (i);
}


int get_height(char **map)
{
    int i;

    i = 0;
    while(map[i])
        i++;
    return (i);
}

int	side(char **map, int i, int j)
{
	if (i == 0 || i == 15)
		return (0);
	if (map[i - 1][j] != '1' && map[i - 1][j] != 'X')
		return (0);
	else if (map[i + 1][j] != '1' && map[i + 1][j] != 'X')
		return (0);
    else if (map[i][j - 1] != '1' && map[i][j - 1] != 'X')
		return (0);
    else if (map[i][j + 1] != '1' && map[i][j + 1] != 'X')
		return (0);
    else
	    return (1);
}

int	map_is_close(char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] && map[i][j] != '\n')
		{
			if (map[i][j] == 'X')
				if (side(map, i, j) == 0)  
					return (0);
			j++;
		}
		i++;
	}
	return (1);
}
