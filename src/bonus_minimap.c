/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <abolor-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:22:33 by abolor-e          #+#    #+#             */
/*   Updated: 2024/10/02 17:22:34 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_draw_orientation_triangle(t_cub3d *cub3d)
{
	int		line_length;
	double	angle_offset;
	int		i;

	angle_offset = 0.6;
	line_length = 90;
	i = 0;
	cub3d->left_dir_x = cos(cub3d->angle - angle_offset);
	cub3d->left_dir_y = sin(cub3d->angle - angle_offset);
	cub3d->right_dir_x = cos(cub3d->angle + angle_offset);
	cub3d->right_dir_y = sin(cub3d->angle + angle_offset);
	while (i++ < line_length)
	{
		cub3d->left_x = 120 + (int)(cub3d->left_dir_x * i);
		cub3d->left_y = 120 + (int)(cub3d->left_dir_y * i);
		my_mlx_pixel_put(cub3d->text, cub3d->left_x, cub3d->left_y, 0xFFFFFF);
	}
	i = 0;
	while (i++ < line_length)
	{
		cub3d->right_x = 120 + (int)(cub3d->right_dir_x * i);
		cub3d->right_y = 120 + (int)(cub3d->right_dir_y * i);
		my_mlx_pixel_put(cub3d->text, cub3d->right_x, cub3d->right_y, 0xFFFFFF);
	}
}

void	ft_draw_minimap_pixel(t_cub3d *cub3d, int x, int y, int color)
{
	int	center_x;
	int	center_y;
	int	dist;

	center_x = 120;
	center_y = 120;
	dist = sqrt((x - center_x) * (x - center_x)
			+ (y - center_y) * (y - center_y));
	if (dist <= cub3d->radius)
	{
		my_mlx_pixel_put(cub3d->text, x, y, color);
		my_mlx_pixel_put(cub3d->text, x + 1, y + 1, color);
	}
}

void	ft_draw_minimap_tile(t_cub3d *cub3d, int scale)
{
	int		pixel_x;
	int		pixel_y;
	double	dist_to_player;

	dist_to_player = sqrt((cub3d->map_x - cub3d->posx)
			* (cub3d->map_x - cub3d->posx) + (cub3d->map_y - cub3d->posy)
			* (cub3d->map_y - cub3d->posy));
	if (dist_to_player <= 6.5)
	{
		pixel_x = 120 + (cub3d->map_x - cub3d->posx) * scale;
		pixel_y = 120 + (cub3d->map_y - cub3d->posy) * scale;
		if (cub3d->map[cub3d->map_y][cub3d->map_x] == '1')
			ft_draw_minimap_pixel(cub3d, pixel_x, pixel_y, 0x000000);
		else
			ft_draw_minimap_pixel(cub3d, pixel_x, pixel_y, 0x39FF14);
	}
}

void	ft_draw_circle(t_cub3d *cub3d, int x0, int y0, int color)
{
	int	x;
	int	y;
	int	d;

	x = 0;
	y = cub3d->radius;
	d = 3 - 2 * cub3d->radius;
	while (x++ <= y)
	{
		my_mlx_pixel_put(cub3d->text, x0 + x, y0 + y, color);
		my_mlx_pixel_put(cub3d->text, x0 + y, y0 + x, color);
		my_mlx_pixel_put(cub3d->text, x0 - x, y0 + y, color);
		my_mlx_pixel_put(cub3d->text, x0 - y, y0 + x, color);
		my_mlx_pixel_put(cub3d->text, x0 + x, y0 - y, color);
		my_mlx_pixel_put(cub3d->text, x0 + y, y0 - x, color);
		my_mlx_pixel_put(cub3d->text, x0 - x, y0 - y, color);
		my_mlx_pixel_put(cub3d->text, x0 - y, y0 - x, color);
		if (d < 0)
			d += 4 * x + 6;
		else
		{
			d += 4 * (x - y) + 10;
			y--;
		}
	}
}

void	ft_minimap(t_cub3d *cub3d)
{
	int	scale;

	scale = 13;
	cub3d->radius = 90;
	ft_draw_circle(cub3d, 120, 120, 0x000000);
	cub3d->map_y = (int)(cub3d->posy - 6.5);
	cub3d->end_y = (int)(cub3d->posy + 6.5);
	cub3d->end_x = (int)(cub3d->posx + 6.5);
	while (cub3d->map_y++ <= cub3d->end_y)
	{
		cub3d->map_x = (int)(cub3d->posx - 6.5);
		while (cub3d->map_x++ <= cub3d->end_x)
		{
			if (cub3d->map_x >= 0 && cub3d->map_x < cub3d->width
				&& cub3d->map_y >= 0 && cub3d->map_y < cub3d->height)
				ft_draw_minimap_tile(cub3d, scale);
		}
	}
	mlx_hook(cub3d->mlx_window, 6, 0, &ft_handle_mouse_move, cub3d);
	ft_draw_orientation_triangle(cub3d);
	my_mlx_pixel_put(cub3d->text, 120 + 1, 120, 0xFF0000);
	my_mlx_pixel_put(cub3d->text, 120 - 1, 120, 0xFF0000);
	my_mlx_pixel_put(cub3d->text, 120, 120, 0xFF0000);
	my_mlx_pixel_put(cub3d->text, 120, 120 + 1, 0xFF0000);
	my_mlx_pixel_put(cub3d->text, 120, 120 - 1, 0xFF0000);
}
