/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:07:46 by anmassy           #+#    #+#             */
/*   Updated: 2024/03/28 13:14:48 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

int ft_strncmp(char *s1, char *s2, size_t n)
{
	while(n--)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		if (*s1 == '\0')
			break;
		s1++;
		s2++;
	}
	return (0);
}

int	ft_strstr(char *str, char *to_find)
{
	int	c;
	int	d;

	c = 0;
	d = 0;
	if (to_find[0] == '\0')
		return (0);
	while (str[c])
	{
		while (str[c + d] == to_find[d])
		{
			if (to_find[d + 1] == '\0')
				return (c + d + 1);
			d++;
		}
		d = 0;
		c++;
	}
	return (0);
}