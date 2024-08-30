#include "cub3d.h"

void	ft_error_str(char *str)
{
	printf("%s\n", str);
	exit(ERROR);
}

int main(void)
{
	t_cub3d	*cub3d;

	cub3d = malloc(sizeof(t_cub3d));
	cub3d = NULL;
	if (!cub3d)
	{
		errno = 12;
		perror("Error t_cub3d");
		return (ERROR);
	}
	cub3d->posx = 10;
	cub3d->posy = 12;
	cub3d->dirx = -1;
	cub3d->diry = 0;
	cub3d->planex = 0;
	cub3d->planey = 0.66;
	ft_raycast(cub3d);
}