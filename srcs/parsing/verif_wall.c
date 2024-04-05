/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:01:46 by anmassy           #+#    #+#             */
/*   Updated: 2024/04/05 19:20:18 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

int	check_wall(char **map, int i, int j)
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

int	map_close(char **map)
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
				if (check_wall(map, i, j) == 0)  
					return (0);
			j++;
		}
		i++;
	}
	return (1);
}

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

int    check_up(char **map, int x, int y)
{
    int space;
    
    space = skip_space(map[y]);
    if (y <= 0 || y >= get_height(map))
        return (1);
    if (x + 1 < space || x + 1 > ft_strlen(map[y]))
        return (1);
    if (map[y - 1][x] == '1' || map[y - 1][x] == 'X' || map[y - 1][x] == ' ' ||
        map[y - 1][x] == '\n' || map[y - 1][x] == '\0')
        return (1);
    return (0);
}

int    check_down(char **map, int x, int y)
{
    int space;
    
    space = skip_space(map[y]);
    if (y <= 0 || y >= get_height(map))
        return (1);
    if (x + 1 < space || x + 1 > ft_strlen(map[y]))
        return (1);
    if (map[y + 1][x] == '1' || map[y + 1][x] == 'X' || map[y + 1][x] == ' ' ||
        map[y + 1][x] == '\n' || map[y + 1][x] == '\0')
        return (1);
    return (0);
}

int    check_left(char **map, int x, int y)
{
    int space;
    
    space = skip_space(map[y]);
    if (y <= 0 || y >= get_height(map))
        return (1);
    if (x + 1 < space || x + 1 > ft_strlen(map[y]))
        return (1);
    if (map[y][x - 1] == '1' || map[y][x - 1] == 'X' || map[y][x - 1] == ' ' ||
        map[y][x - 1] == '\n' || map[y][x - 1] == '\0')
        return (1);
    return (0);
}


int    check_right(char **map, int x, int y)
{
    int space;
    
    space = skip_space(map[y]);
    if (y <= 0 || y >= get_height(map))
        return (1);
    if (x + 1 < space || x + 1 > ft_strlen(map[y]))
        return (1);
    if (map[y][x + 1] == '1' || map[y][x + 1] == 'X' || map[y][x + 1] == ' ' ||
        map[y][x + 1] == '\n' || map[y][x + 1] == '\0')
        return (1);
    return (0);
}


char    **depth_first_check(char **map, int x, int y)
{
    map[y][x] = 'X';
    if (check_left(map, x, y) == 0)
        depth_first_check(map, x - 1, y);
    if (check_up(map, x, y) == 0)
        depth_first_check(map, x, y - 1);
    if (check_right(map, x, y) == 0)
        depth_first_check(map, x + 1, y);
    if (check_down(map, x, y) == 0)
        depth_first_check(map, x, y + 1);
    return (map);
}