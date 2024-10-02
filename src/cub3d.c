/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <abolor-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:07:02 by olmarech          #+#    #+#             */
/*   Updated: 2024/10/02 17:45:36 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_variable(t_cub3d *cub3d, int i)
{
	cub3d->done = 0;
	cub3d->wall_dist = 0;
	cub3d->lower_point = 0;
	cub3d->upper_point = 0;
	cub3d->raydirx = 0;
	cub3d->raydiry = 0;
	cub3d->mapx = 0;
	cub3d->mapy = 0;
	cub3d->deltax = 0;
	cub3d->deltay = 0;
	cub3d->sidex = 0;
	cub3d->sidey = 0;
	cub3d->hit_location = 0;
	cub3d->texture_fix = 0;
	cub3d->column_height = 0;
	cub3d->stepx = 0;
	cub3d->camera_height = 100;
	cub3d->texture_position = 0;
	cub3d->stepy = 0;
	cub3d->hit = 0;
	cub3d->side = 0;
	cub3d->ch_posx = cub3d->posx;
	cub3d->ch_posy = cub3d->posy;
	while (++i < 4)
		cub3d->texture[i].text = NULL;
}

void	malloc_base(t_cub3d *cub3d, t_pars *pars)
{
	cub3d = malloc(sizeof(t_cub3d));
	if (!cub3d)
	{
		ft_error_str("Error t_cub3d", 12);
		exit(ERROR);
	}
	pars = malloc(sizeof(t_pars));
	if (!pars)
	{
		ft_error_str("Error pars", 12);
		exit(ERROR);
	}
}

void	global_initialisation(t_cub3d *cub3d, t_pars *pars, char **av)
{
	cub3d->angle = 6.28319;//initialize!
	init_variable(cub3d, -1);
	parsing(pars, av);
	init_cub(cub3d, pars);
	ft_init_window(cub3d);
	ft_raycast(cub3d);
}

void	begin_check(int ac, char *str)
{
	if (ac != 2)
		msg_exit("Wrong input!");
	if (check_dot_cub(str))
		msg_exit("Wrong file format.");
}

int	main(int ac, char **av)
{
	t_cub3d	*cub3d;
	t_pars	*pars;

	begin_check(ac, av[1]);
	cub3d = malloc(sizeof(t_cub3d));
	if (!cub3d)
	{
		ft_error_str("Error t_cub3d", 12);
		exit(ERROR);
	}
	pars = malloc(sizeof(t_pars));
	if (!pars)
	{
		ft_error_str("Error pars", 12);
		exit(ERROR);
	}
	global_initialisation(cub3d, pars, av);
	mlx_mouse_move(cub3d->mlx_window, screen_w / 2, screen_h / 2);
	mlx_hook(cub3d->mlx_window, 4, keypressmask, &ft_mousepress, cub3d);
	mlx_hook(cub3d->mlx_window, keypress, 0, &ft_keypress, cub3d);
	mlx_hook(cub3d->mlx_window, keyrelease, 0, &ft_keyrelease, cub3d);
	mlx_hook(cub3d->mlx_window, 17, 0, close_free, cub3d);
	mlx_loop_hook(cub3d->mptr, &ft_render_next_frame_bymove, cub3d);
	mlx_loop(cub3d->mptr);
}
