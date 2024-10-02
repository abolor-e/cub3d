/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <abolor-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:29:19 by abolor-e          #+#    #+#             */
/*   Updated: 2024/10/02 17:23:35 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_ray_vector(t_cub3d *cub3d, int index)
{
	double	camerax;

	cub3d->hit = 0;
	camerax = 2 * index / (double)screen_w - 1;
	cub3d->raydirx = cub3d->dirx + cub3d->planex * camerax;
	cub3d->raydiry = cub3d->diry + cub3d->planey * camerax;
	cub3d->mapx = (int)cub3d->posx;
	cub3d->mapy = (int)cub3d->posy;
}

void	ft_delta_dist(t_cub3d *cub3d)
{
	if (cub3d->raydirx == 0)
		cub3d->deltax = 1e30;
	else
		cub3d->deltax = fabs(1 / cub3d->raydirx);
	if (cub3d->raydiry == 0)
		cub3d->deltay = 1e30;
	else
		cub3d->deltay = fabs(1 / cub3d->raydiry);
}

void	ft_distance(t_cub3d *cub3d)
{
	if (cub3d->raydirx < 0)
	{
		cub3d->stepx = -1;
		cub3d->sidex = (cub3d->posx - cub3d->mapx) * cub3d->deltax;
	}
	else if (cub3d->raydirx >= 0)
	{
		cub3d->stepx = 1;
		cub3d->sidex = (cub3d->mapx + 1.0 - cub3d->posx) * cub3d->deltax;
	}
	if (cub3d->raydiry < 0)
	{
		cub3d->stepy = -1;
		cub3d->sidey = (cub3d->posy - cub3d->mapy) * cub3d->deltay;
	}
	else if (cub3d->raydiry >= 0)
	{
		cub3d->stepy = 1;
		cub3d->sidey = (cub3d->mapy + 1.0 - cub3d->posy) * cub3d->deltay;
	}
}

void	ft_draw_text(t_cub3d *cub3d, int x)
{
	uint32_t	color;
	int			i;

	i = 0;
	while (i < cub3d->lower_point)
	{
		my_mlx_pixel_put(cub3d->text, x, i, cub3d->c_rgb);
		i++;
	}
	while (cub3d->lower_point <= cub3d->upper_point)
	{
		cub3d->texture_vertical = (int)cub3d->texture_position
			& (texture_h - 1);
		cub3d->texture_position += cub3d->step;
		color = ft_color_get(cub3d);
		my_mlx_pixel_put(cub3d->text, x, cub3d->lower_point, color);
		cub3d->lower_point++;
	}
	i = cub3d->upper_point;
	while (++i < screen_h)
		my_mlx_pixel_put(cub3d->text, x, i, cub3d->f_rgb);
}

void	ft_raycast(t_cub3d *cub3d)
{
	int		x;

	cub3d->text->text = mlx_new_image(cub3d->mptr, screen_w, screen_h);
	if (!cub3d->text->text)
		ft_error_str("Raycast text->text mlx_new_image error", 12);
	cub3d->text->address = mlx_get_data_addr(cub3d->text->text,
			&cub3d->text->bits_per_pixel, &cub3d->text->line_length,
			&cub3d->text->endian);
	x = -1;
	while (++x < screen_w)
	{
		ft_ray_vector(cub3d, x);
		ft_delta_dist(cub3d);
		ft_distance(cub3d);
		ft_digital_differential_analysis(cub3d);
		ft_draw_text(cub3d, x);
	}
	ft_gun_point(cub3d);
	ft_minimap(cub3d);
	mlx_put_image_to_window(cub3d->mptr, cub3d->mlx_window,
		cub3d->text->text, 0, 0);
	ft_gun(cub3d);
}
