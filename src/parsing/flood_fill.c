/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <abolor-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:39:36 by olmarech          #+#    #+#             */
/*   Updated: 2024/10/02 17:23:54 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	print_content(char **file_content)
{
	int	i;
	int	j;

	i = -1;
	while (file_content[++i])
	{
		j = -1;
		while (file_content[i][++j])
		{
			if (file_content[i][j] == '1')
				printf("\e[96m██\033[0m");
			else if (file_content[i][j] == '0')
				printf("\e[90m██\033[0m");
			else if (file_content[i][j] == 'N' || file_content[i][j] == 'S'
					|| file_content[i][j] == 'E' | file_content[i][j] == 'W')
				printf("\033[0;32m██\033[0m");
			else if (file_content[i][j] == '2')
				printf("\033[1;31m██\033[0m");
			else
				printf("  ");
		}
		printf("\n");
	}
}

int	checker(char **map, int i, int j)
{
	if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != '2'
		&& map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'E'
		&& map[i][j] != 'W')
		return (1);
	return (0);
}

void	verify_map(char **map, int y, int x)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'E'
				|| map[i][j] == 'S' || map[i][j] == 'W')
			{
				if (j == x || j == 0 || i == y - 1 || i == 0)
					map[i][j] = '2';
				else
				{
					if (checker(map, i + 1, j) || checker(map, i - 1, j)
						|| checker(map, i, j + 1) || checker(map, i, j - 1))
						map[i][j] = '2';
				}
			}
		}
	}
}

void	pars_map(t_pars *pars)
{
	int	i;
	int	j;
	int	width;
	int	height;

	height = 0;
	width = 0;
	i = -1;
	while (pars->map[height])
		height++;
	while (pars->map[++i])
	{
		j = 0;
		while (pars->map[i][j])
			j++;
		if (j > width)
			width = j;
	}
	verify_map(pars->map, height, width);
	printf("h : %d, w : %d\n\n\n", height, width);
	pars->map_w = width;
	pars->map_h = height;
}

void	flood_fill(t_pars *pars)
{
	if (!pars->map[0])
		msg_exit("There is no map.");
	pars_map(pars);
	print_content(pars->map);
	check_map(pars->map);
}
