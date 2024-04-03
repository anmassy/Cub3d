/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_fonction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:07:04 by anmassy           #+#    #+#             */
/*   Updated: 2024/04/03 18:07:40 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

int err(char *msg, int nb)
{
	printf("%s\n", msg);
	return(nb);
}

int	ft_exit(int nb, char *msg)
{
	printf("%s\n", msg);
	exit(nb);
}