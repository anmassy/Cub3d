/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_road.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:02:12 by anmassy           #+#    #+#             */
/*   Updated: 2024/04/05 22:00:11 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

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