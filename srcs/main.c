/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:16:55 by anmassy           #+#    #+#             */
/*   Updated: 2024/03/20 17:23:34 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3d.h"

void	display_map(t_data *game)
{
	int	j;
	int	i;

	i = 0;
	while (game->val->map[i])
	{
		j = 0;
		while (game->val->map[i][j])
		{
			printf("%c ", game->val->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int	len_doc(char *av)
{
	int		len;
	char	c;
	int		fd;

	len = 1;
	fd = open (av, O_RDONLY);
	while (read (fd, &c, 1) > 0)
	{
		if (c == '\n')
			len++;
	}
	close(fd);
	return (len);
}

int	count_line(char *av, t_data *game)
{
	char	c;
	int		fd;

	fd = open (av, O_RDONLY);
	while (read (fd, &c, 1) > 0)
	{
		if (c == '\n')
			game->val->height++;
	}
	close(fd);
	return (game->val->height);
}

void	convert_map(t_data *game, char *av)
{
	int		fd;
	char	*line;
	int		len;
	int		i;

	i = 0;
	len = len_doc(av);
	count_line(av, game);
	game->val->map = (char **)malloc((len + 1) * sizeof(char *));
	if (!game->val->map)
		return ;
	fd = open(av, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		game->val->map[i] = line;
		i++;
		line = get_next_line(fd);
	}
	game->val->map[i] = NULL;
	close(fd);
}

int main(int ac, char **av)
{
    t_data *game;

	if (ac > 2)
		return (0);
	game = init_struct();
    convert_map(game, av[1]); //converti la map du fichier .cub dans un buffer 
	if (verif_texture(game) == 0 || verif_map(game) == 0) //effectue les verif nessessaire avant de passer a l'exec
	    return (0);
	display_map(game); //affiche la map
    return (0);
}