#include "cub3d.h"

void	ft_error_str(char *str)
{
	perror(str);
	exit(ERROR);
}

int main(void)
{
	t_cub3d	*cub3d;

	cub3d = malloc(sizeof(t_cub3d));
	if (!cub3d)
	{
		errno = 12;
		ft_error_str("Error t_cub3d");
		return (ERROR);
	}
	// init everything!
	cub3d->posx = 10;
	cub3d->posy = 12;
	cub3d->dirx = -1;
	cub3d->diry = 0;
	cub3d->planex = 0;
	cub3d->planey = 0.66;
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
	ft_raycast(cub3d);
	free(cub3d);
}
