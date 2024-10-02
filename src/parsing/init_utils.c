/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <abolor-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:55:14 by olmarech          #+#    #+#             */
/*   Updated: 2024/10/02 17:44:05 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	little_check(char **buff, int i, int k)
{
	if ((buff[i][k] == '1' || buff[i][k] == '0'
		|| buff[i][k] == 'N' || buff[i][k] == 'S'
		|| buff[i][k] == 'E' || buff[i][k] == 'W'
		|| (buff[i][k] == ' ' && k > 0)) && k > 0)
			if (buff[i][k - 1] >= 9 && buff[i][k - 1] <= 13)
		return (1);
	return (0);
}

void	init_file_content(char **buff, char **file_content)
{
	int	i;
	int	k;
	int	j;

	j = 0;
	i = 0;
	while (buff[i])
	{
		k = -1;
		while (buff[i][++k])
		{
			if (little_check(buff, i, k))
			{
				free_tab(buff);
				msg_exit("Error in file.");
			}
		}
		if (!(buff[i][0] >= 9 && buff[i][0] <= 13))
		{
			file_content[j] = ft_strdup(buff[i]);
			j++;
		}
		i++;
	}
	file_content[j] = NULL;
}

void	init_pars(t_pars *pars)
{
	int	i;

	i = 0;
	while (i <= 3)
	{
		pars->c_rgb[i] = -1;
		pars->f_rgb[i] = -1;
		i++;
	}
	pars->map_w = 0;
	pars->map_h = 0;
	pars->map = NULL;
	pars->path_n = NULL;
	pars->path_s = NULL;
	pars->path_w = NULL;
	pars->path_e = NULL;
}

void	init_pars_orientation(t_pars *pars, int i, int j)
{
	pars->orientation = pars->map[i][j];
	pars->posx = j;
	pars->posy = i;
}

int	good_size(char **buff)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (buff[i])
	{
		if ((buff[i][0] >= 9 && buff[i][0] <= 13))
			i++;
		else
		{
			i++;
			j++;
		}
	}
	return (j);
}
