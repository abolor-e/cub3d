/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <abolor-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:03:01 by abolor-e          #+#    #+#             */
/*   Updated: 2024/10/02 17:23:12 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_sidedist(t_cub3d *cub3d)
{
	while (cub3d->hit == 0)
	{
		if (cub3d->sidex < cub3d->sidey)
		{
			cub3d->side = 3;
			if (cub3d->raydirx < 0)
				cub3d->side = 2;
			cub3d->sidex = cub3d->sidex + cub3d->deltax;
			cub3d->mapx = cub3d->mapx + cub3d->stepx;
		}
		else
		{
			cub3d->side = 1;
			if (cub3d->raydiry < 0)
				cub3d->side = 0;
			cub3d->sidey = cub3d->sidey + cub3d->deltay;
			cub3d->mapy = cub3d->mapy + cub3d->stepy;
		}
		if (cub3d->map[cub3d->mapy][cub3d->mapx] == '1')
			cub3d->hit = 1;
	}
}

void	ft_column_height(t_cub3d *cub3d)
{
	if (cub3d->side == 2 || cub3d->side == 3)
		cub3d->wall_dist = cub3d->sidex - cub3d->deltax;
	else
		cub3d->wall_dist = cub3d->sidey - cub3d->deltay;
	cub3d->column_height = (int)(screen_h / cub3d->wall_dist);
	cub3d->lower_point = -cub3d->column_height / 2 + screen_h / 2 - 1;
	if (cub3d->lower_point < 0)
		cub3d->lower_point = 0;
	cub3d->upper_point = cub3d->column_height / 2 + screen_h / 2;
	if (cub3d->upper_point >= screen_h)
		cub3d->upper_point = screen_h - 1;
}

void	ft_hit_location(t_cub3d *cub3d)
{
	if (cub3d->side == 2 || cub3d->side == 3)
		cub3d->hit_location = cub3d->posy + cub3d->wall_dist * cub3d->raydiry;
	else
		cub3d->hit_location = cub3d->posx + cub3d->wall_dist * cub3d->raydirx;
	cub3d->hit_location -= floor(cub3d->hit_location);
}

void	ft_hit_loc_texturefix(t_cub3d *cub3d)
{
	cub3d->texture_fix = (int)(cub3d->hit_location * (double)texture_w);
	if ((cub3d->side == 2 && cub3d->raydirx < 0)
		|| (cub3d->side == 1 && cub3d->raydiry > 0))
		cub3d->texture_fix = texture_w - cub3d->texture_fix - 1;
	else if ((cub3d->side == 0 && cub3d->raydiry < 0)
		|| (cub3d->side == 3 && cub3d->raydirx > 0))
		cub3d->texture_fix = texture_w - cub3d->texture_fix - 1;
}

void	ft_digital_differential_analysis(t_cub3d *cub3d)
{
	ft_sidedist(cub3d);
	ft_column_height(cub3d);
	ft_hit_location(cub3d);
	ft_hit_loc_texturefix(cub3d);
	cub3d->step = 1.0 * texture_h / cub3d->column_height;
	cub3d->texture_position = (cub3d->lower_point - (screen_h / 2)
			+ (cub3d->column_height / 2)) * cub3d->step;
}
