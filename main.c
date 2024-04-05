/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:16:55 by anmassy           #+#    #+#             */
/*   Updated: 2024/04/05 20:04:46 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Cub3d.h"

int	check_file(char *av)
{
	char	s[4];
	int		i;
	int		j;

	i = ft_strlen(av) - 4;
	j = 0;
	while (av[i])
		s[j++] = av[i++];
	if (ft_strncmp(s, ".cub", 4) == 0)
		return (1);
	return (0);
}

int	file_exist(char *path)
{
	int		fd;
	char	buffer;
	ssize_t	bytes_read;

	fd = open(path, O_RDONLY);
	if (fd != -1)
	{
		bytes_read = read(fd, &buffer, 1);
		if (bytes_read > 0)
			return (close(fd), 1);
		else
			return (close(fd), 0);
	}
	else
		return (0);
}

void	display_map(char **map)
{
	int	j;
	int	i;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			printf("%c", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data	*game;

	if (ac != 2)
		err(1, NB_ARG);
	if (check_file(av[1]) == 0 || file_exist(av[1]) == 0)
		err(1, EMPTY_FILE);
	game = init_struct();
	convert_map(game, av[1]);
	/*penser a faire une copie de game->val->m*/
	depth_first_check(game->val->m, game->val->startX, game->val->startY);
	if (map_is_close(game->val->m) == 0)
		ft_exit(1, ERR_WALL);
	display_map(game->val->m);
	start_game(game);
	ft_free(game); //pas oublié de clean
	return (0);
}
