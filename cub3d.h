#ifndef CUB3D_H

# include "stdio.h"
# include "stdlib.h"
# include "limits.h"
# include "stdlib.h"
# include "errno.h"
# include "math.h"

# define screen_h 480
# define screen_w 640
# define texture_w 64
# define texture_h 64

# define ERROR -1
# define SUCCESS 0

# define MSG1 "Error: t_cub3d malloc error!"

typedef struct s_cub3d
{
	char	**map;
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
	
	double	raydirx;
	double	raydiry;
	/*These are ray vectors which represent the 
	direction of the vector*/

	int		mapy;
	int		mapx;
	/*Sets player position into int, later on will
	  help to see if vertical or horizontal wall
	  is hit and change the deltadistx or y!*/
	
	double	deltax;
	double	deltay;
	/*These are the distance the ray travels to 
	   traverse 1 unit of each axis*/

	double	sidex;
	double	sidey;
	/*These are the distance to reach the first vertical
	  or horizontal grid*/
	
	double	wall_dist;
	double	hit_location;
	double	texture_position;
	int		upper_point;
	int		lower_point;

	int		texture_fix;
	int		stepy;// These variables move coordinates towards the ray checking grids
	int		stepx;
	int		camera_height;

	int		column_height;
	int		hit;
	int		side;
	int		done;
}				t_cub3d;


int	ft_raycast(t_cub3d *cub3d);
int	ft_playerpos_int(t_cub3d *cub3d);

#endif