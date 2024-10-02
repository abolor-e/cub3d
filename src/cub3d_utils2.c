/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <abolor-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:23:26 by olmarech          #+#    #+#             */
/*   Updated: 2024/10/02 17:22:46 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_dot_cub(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	i -= 4;
	if (i <= 0)
		return (1);
	if (!ft_strncmp(str + i, ".cub", 4))
		return (0);
	else
		return (1);
}

void	convert_rgb_hex_floor(t_cub3d *cub3d, t_pars *pars, int option)
{
	if (option == 1)
		cub3d->f_rgb = (1 << 24 | pars->f_rgb[0] << 16
				| pars->f_rgb[1] << 8 | pars->f_rgb[2]);
	else
		cub3d->c_rgb = (1 << 24 | pars->c_rgb[0] << 16
				| pars->c_rgb[1] << 8 | pars->c_rgb[2]);
}

void	init_map_cub(t_cub3d *cub3d, t_pars *pars)
{
	int	i;

	i = -1;
	cub3d->map = malloc(sizeof(char *) * (size_tab(pars->map) + 1));
	while (pars->map[++i])
		cub3d->map[i] = ft_strdup(pars->map[i]);
	cub3d->map[i] = NULL;
}

void	init_plane_dir(t_cub3d *cub3d, int dirx, double planex)
{
	cub3d->dirx = dirx;
	cub3d->planex = planex;
	if (dirx == 1)
	{
		cub3d->diry = 0;
		cub3d->planey = 0.66;
	}
	else if (dirx == -1)
	{
		cub3d->diry = 0;
		cub3d->planey = -0.66;
	}
	else if (planex == 0.66)
	{
		cub3d->diry = -1;
		cub3d->planey = 0;
	}
	else if (planex == -0.66)
	{
		cub3d->diry = 1;
		cub3d->planey = 0;
	}
}

void	init_cub(t_cub3d *cub3d, t_pars *pars)
{
	init_map_cub(cub3d, pars);
	cub3d->posx = pars->posx + 0.5;
	cub3d->posy = pars->posy + 0.5;
	convert_rgb_hex_floor(cub3d, pars, 0);
	convert_rgb_hex_floor(cub3d, pars, 1);
	cub3d->path_n = ft_strdup(pars->path_n);
	cub3d->path_s = ft_strdup(pars->path_s);
	cub3d->path_e = ft_strdup(pars->path_e);
	cub3d->path_w = ft_strdup(pars->path_w);
	cub3d->width = pars->map_w;
	cub3d->height = pars->map_h;
	if (pars->orientation == 'N')
		init_plane_dir(cub3d, 0, 0.66);
	if (pars->orientation == 'S')
		init_plane_dir(cub3d, 0, -0.66);
	if (pars->orientation == 'E')
		init_plane_dir(cub3d, 1, 0);
	if (pars->orientation == 'W')
		init_plane_dir(cub3d, -1, 0);
	free_pars(pars);
}
