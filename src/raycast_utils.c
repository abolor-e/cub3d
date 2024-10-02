/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <abolor-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:46:20 by abolor-e          #+#    #+#             */
/*   Updated: 2024/10/02 17:23:31 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	my_mlx_pixel_put(t_textures *text, int x, int y, int color)
{
	char	*dst;

	dst = text->address + (y * text->line_length + x
			* (text->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

uint32_t	ft_color_get(t_cub3d *cub3d)
{
	int				pix_index;
	unsigned char	*pixel;
	uint32_t		color;

	pix_index = (texture_h * cub3d->texture_vertical + cub3d->texture_fix)
		* (cub3d->texture[cub3d->side].bits_per_pixel / 8);
	pixel = (unsigned char *)&cub3d->texture[cub3d->side].address[pix_index];
	color = (pixel[2] << 16) | (pixel[1] << 8) | pixel[0];
	return (color);
}
