/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:01:46 by anmassy           #+#    #+#             */
/*   Updated: 2024/04/06 14:12:01 by anmassy          ###   ########.fr       */
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
	if (i == 0 || i == get_height(map))
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

char **duplicate_map(char **original_map)
{
	int height;
	int i;

    i = 0;
	height = get_height(original_map);
    char **copy_map = malloc((height + 1) * sizeof(char *));
    if (copy_map == NULL)
        ft_exit(1, ERR_MALLOC);
    while (i < height)
	{
        copy_map[i] = ft_strdup(original_map[i]);
        if (copy_map[i] == NULL)
            ft_exit(1, ERR_MALLOC);
		i++;
    }
    copy_map[height] = NULL;
    return (copy_map);
}

void verif_wall(t_data *game)
{
	char **temp_map;
	
	temp_map = duplicate_map(game->val->m);
	depth_first_check(temp_map, game->val->startX, game->val->startY);
	// printf("ORIGINAL MAP :\n");
	// display_map(game->val->m);
	// printf("\nCOPY MAP :\n");
	// display_map(temp_map);
	if (map_is_close(temp_map) == 0)
		ft_exit(1, ERR_WALL);
	free_map(temp_map);
}