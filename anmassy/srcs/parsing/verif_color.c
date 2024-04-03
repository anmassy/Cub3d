/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:06:11 by anmassy           #+#    #+#             */
/*   Updated: 2024/04/03 19:25:13 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

int	color_lenght(char *line, int pos)
{
	int	i;

	i = 0;
	while (line[pos] != ',' && line[pos] != '\0')
	{
		if ((line[pos] >= '0' && line[pos] <= '9') || line[i] == '-')
			i++;
		pos++;
	}
	return (i);
}

int	range_color(int nb)
{
	if (nb == -2147483648)
		return (0);
	else if (nb >= 0 && nb <= 255)
		return (1);
	return (0);
}

int	comma(char *line)
{
	int	i;

	i = 0;
	if (line[0] == ',' || line[ft_strlen(line) - 1] == ',')
		return (0);
	while (line[i])
	{
		if (line[i] == ',' && line[i + 1] == ',')
			return (0);
		i++;
	}
	return (1);
}

char *get_nb(char *line, char *temp, int i)
{
	int	j;
	
	j = 0;
	temp = malloc(sizeof(char) * color_lenght(line, i) + 2);
	if (!temp)
		return (0);
	while (line[i] != '\0' && line[i] != ',')
	{
		if ((line[i] >= '0' && line[i] <= '9') || line[i] == '-')
			temp[j++] = line[i++];
		else
			return (0);
	}
	temp[j] = '\0';
	
	return (temp);
}

int	valid_color(char *line)
{
	char	*number;
	int		number_of_number;
	int		i;
	
	i = 0;
	number_of_number = 0;
	if (comma(line) == 0)
		return (0);
	while (line[i] && line[i] != '\n')
	{
		number = get_nb(line, number, i);
		if (range_color(ft_atoi(number)) == 0)
			return (0);
		number_of_number++;
		i += ft_strlen(number) + 1;
		free(number);
	}
	if (number_of_number == 3)
		return (1);
	return (0);
}
