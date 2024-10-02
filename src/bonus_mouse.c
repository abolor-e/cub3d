/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <abolor-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:16:35 by abolor-e          #+#    #+#             */
/*   Updated: 2024/10/02 17:37:53 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_mouse(t_cub3d *cub3d)
{
	int	x;
	int	y;

	mlx_mouse_show();
	if (cub3d->keyp.mouse == 0)
	{
		mlx_mouse_hide();
		mlx_mouse_get_pos(cub3d->mlx_window, &x, &y);
		if (x != (screen_w / 2))
			ft_rot_movement(cub3d, 0, cub3d->time.frame
				* (x - screen_w / 2) / 4);
		mlx_mouse_move(cub3d->mlx_window, screen_w / 2, screen_h / 2);
	}
}

int	ft_handle_mouse_move(int x, int y, t_cub3d *cub3d)
{
	int	cx;
	int	mov;

	(void)y;
	cx = screen_w / 2;
	mov = x - cx;
	cub3d->angle += mov * MOUSE_S;
	if (cub3d->angle < 0)
		cub3d->angle += 2 * M_PI;
	if (cub3d->angle >= 2 * M_PI)
		cub3d->angle -= 2 * M_PI;
	return (0);
}

int	ft_mousepress(int mousecode, int x, int y, t_cub3d *cub3d)
{
	(void)x;
	(void)y;
	if (mousecode == 1)
		cub3d->keyp.l_click = 1;
	return (0);
}
