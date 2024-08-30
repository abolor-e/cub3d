#ifndef CUB3D_H

# include "stdio.h"
# include "stdlib.h"
# include "limits.h"
# include "stdlib.h"
# include "errno.h"

# define screen_h "480"
# define screen_w "640"

# define ERROR -1
# define SUCCESS 0

# define MSG1 "Error: t_cub3d malloc error!"

typedef struct s_cub3d
{
	double	posx;//x coordinate of player's start position
	double	posy;//y coordinate of player's start position

	double	dirx;//x direction vector
	double	diry;//y direction vector 
	/*if N: dirx = 0; diry = -1;
	  if S: dirx = 0; diry = +1;
	  if W: dirx = -1; diry = 0;
	  if E: dirx = +1; diry = 0*/
	double	planex;//camera plane 
	double	planey;
	/*if N: planex = 0.66; planey = 0; meaning the camera plane is positioned through the x-axis
	     S: planex = 0.66; planey = 0;
		 W: planex = 0; planey = 0.66; meaning the camera plane is positioned through the y-axis
		 E: planex = 0; planey = 0.66;*/
}				t_cub3d;


void	ft_raycast(t_cub3d *cub3d);

#endif