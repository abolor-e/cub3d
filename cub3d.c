#include "cub3d.h"


void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
}

void	free_cub(t_cub3d *cub3d)
{
	if (cub3d->map)
		free_tab(cub3d->map);
	if (cub3d->path_n)
		free(cub3d->path_n);
	if (cub3d->path_s)
		free(cub3d->path_s);
	if (cub3d->path_e)
		free(cub3d->path_e);
	if (cub3d->path_w)
		free(cub3d->path_w);
	free(cub3d);
}

void	free_pars(t_pars *pars)
{
	if (pars->map)
	{
		free_tab(pars->map);
		free(pars->map);
	}
	if (pars->path_n)
		free(pars->path_n);
	if (pars->path_s)
		free(pars->path_s);
	if (pars->path_e)
		free(pars->path_e);
	if (pars->path_w)
		free(pars->path_w);
}

int	close_free(t_cub3d *cub3d)
{
	mlx_destroy_image(cub3d->mlx_ptr, cub3d->text->text);
	mlx_destroy_window(cub3d->mlx_ptr, cub3d->mlx_window);
	free(cub3d->mlx_ptr);
	free(cub3d->text);
	free_cub(cub3d);
	exit(EXIT_SUCCESS);
	return (0);
}

void	ft_error_str(char *str, int x)//don't forget to change it so it can receive and int (ERRNO)
{
	errno = x;
	perror(str);
	exit(ERROR);
}

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

void	init_cub(t_cub3d *cub3d, t_pars *pars)
{
	int	i;

	i = 0;
	cub3d->map = pars->map;
	cub3d->posx = pars->posx;
	cub3d->posy = pars->posy;
	convert_rgb_hex_floor(cub3d, pars, 0);
	convert_rgb_hex_floor(cub3d, pars, 1);
	cub3d->path_n = pars->path_n;
	cub3d->path_s = pars->path_s;
	cub3d->path_e = pars->path_e;
	cub3d->path_w = pars->path_w;
	if (pars->orientation == 'N')
	{
		cub3d->dirx = 0;
		cub3d->diry = -1;
		cub3d->planex = 0.66;
		cub3d->planey = 0;
	}
	if (pars->orientation == 'S')
	{
		cub3d->dirx = 0;
		cub3d->diry = 1;
		cub3d->planex = -0.66;
		cub3d->planey = 0;
	}
	if (pars->orientation == 'E')
	{
		cub3d->dirx = 1;
		cub3d->diry = 0;
		cub3d->planex = 0;
		cub3d->planey = 0.66;
	}
	if (pars->orientation == 'W')
	{
		cub3d->dirx = -1;
		cub3d->diry = 0;
		cub3d->planex = 0;
		cub3d->planey = -0.66;
	}
}

int main(int ac, char **av)
{
	t_cub3d	*cub3d;
	t_pars	pars;
	int i;

	if (ac != 2)
		msg_exit("Wrong input!");
	if (check_dot_cub(av[1]))
		msg_exit("Wrong file format.");
	cub3d = malloc(sizeof(t_cub3d));
	if (!cub3d)
	{
		ft_error_str("Error t_cub3d", 12);
		return (ERROR);
	}
	i = -1;
	while (++i < 4)
		cub3d->texture[i].text = NULL;
	// init everything!
	parsing(&pars, av);
	init_cub(cub3d, &pars);
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
	//ft_begin_image(cub3d);//Image to see first
	ft_init_window(cub3d);
	ft_raycast(cub3d);
	mlx_mouse_move(cub3d->mlx_window, screen_w/2, screen_h/2);
	mlx_hook(cub3d->mlx_window, keypress, keypressmask, &ft_keypress, cub3d);
	mlx_hook(cub3d->mlx_window, keyrelease, keyreleasemask, &ft_keyrelease, cub3d);
	mlx_hook(cub3d->mlx_window, 17, 0, close_free, cub3d);
	mlx_loop_hook(cub3d->mlx_ptr, &ft_render_next_frame_bymove, cub3d);
	mlx_loop(cub3d->mlx_ptr);

	// cub3d->posx = 10; //player position
	// cub3d->posy = 12;

	// cub3d->dirx = -1; // orientation
	// cub3d->diry = 0; // exemple : W

	// cub3d->planex = 0; // N, S : x0.66 y0
	// cub3d->planey = 0.66; // W, E : x0 y0.66

}
