/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmarech <olmarech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:39:36 by olmarech          #+#    #+#             */
/*   Updated: 2024/09/26 13:16:33 by olmarech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void	pars_map(char **map)
{
	int	i;
	int	j;
	int	width;
	int	height;
	int	tmp;

	height = 0;
	width = 0;
	i = -1;
	while (map[height])
		height++;
	while (map[++i])
	{
		j = 0;
		tmp = 0;
		while (map[i][j])
			j++;
		if (j > width)
			width = tmp;
	}
	verify_map(map, height, width);
}

void	flood_fill(char **map)
{
	if (!map[0])
		msg_exit("There is no map.");
	pars_map(map);
	print_content(map);
	check_map(map);
}
