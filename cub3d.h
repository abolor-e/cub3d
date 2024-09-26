#ifndef CUB3D_H

# include "stdio.h"
# include "stdlib.h"
# include "limits.h"
# include "stdlib.h"
# include "sys/time.h"
# include "errno.h"
# include "math.h"
# include <fcntl.h>
# include "parsing/GNL/get_next_line.h"

# include "./minilibx/mlx.h"

# define screen_h 		720
# define screen_w 		1280
# define texture_w		64
# define texture_h 		64

# define ERROR 			-1
# define SUCCESS 		0

# define KEY_D			2
# define KEY_S			1
# define KEY_A			0
# define KEY_W			13
# define KEY_ESC		53
# define ARROW_L		123
# define ARROW_R		124
# define MOUSE			46
# define LEFTCLICK		49
# define MOUSE_S		0.0027

//MLX events
# define keypress		2
# define keyrelease		3

//MLX masks
# define keypressmask	1L<<0
# define keyreleasemask	1L<<1

//Error messages
# define MSG1 "Error: t_cub3d malloc error!"

// typedef struct s_textures
// {
// 	void	*wall;
// }				t_textures;

typedef struct s_textures
{
	void	*text;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	*address;
}				t_textures;

typedef struct  s_time
{
	double	prev;
	double	pres;
	double	frame;
}				t_time;

typedef struct s_keypress
{
	int	forward;
	int	backwards;
	int	left;
	int	right;
	int	rot_l;
	int	rot_r;
	int	mouse;
	int	l_click;
}				t_keypress;

typedef struct s_cub3d
{
	void	*mlx_ptr;
	void	*mlx_window;
	void	*ptr;
	t_textures	*text;
	t_textures	*begin_image;
	t_textures	texture[4];
	t_keypress	keyp;
	t_time		time;

	char	**map;
	double	angle;
	double	ch_posx;//changed positions
	double	ch_posy;

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
	     S: planex = -0.66; planey = 0;
		 W: planex = 0; planey = 0.66; meaning the camera plane is positioned through the y-axis
		 E: planex = 0; planey = -0.66;*/

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
	double	step;
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

	int		texture_vertical;

	//t_textures	texture_data;
	int		c_rgb;
	int		f_rgb;
	char	*path_n;
	char	*path_s;
	char	*path_e;
	char	*path_w;
	void	*gun_text;
	void	*fire_text;
}				t_cub3d;

typedef struct s_pars
{
	int		f_rgb[3];
	int		c_rgb[3];
	char	**map;
	char	*path_n;
	char	*path_s;
	char	*path_e;
	char	*path_w;
	char	orientation;
	int		posx;
	int		posy;
}	t_pars;

void	ft_raycast(t_cub3d *cub3d);
void	ft_playerpos_int(t_cub3d *cub3d);
void	ft_error_str(char *str, int x);
void	flood_fill(char **map);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(char *s);
char	**ft_split(char const *str, char const c);
int		ft_atoi(const char *str);
void	msg_exit(char *error);
void	parsing(t_pars *pars, char **av);
void	free_cub(t_cub3d *cub3d);
void	free_tab(char **tab);
void	free_pars(t_pars *pars);
int		close_free(t_cub3d *cub3d);
void	ft_init_window(t_cub3d *cub3d);
void	my_mlx_pixel_put(t_textures *text, int x, int y, int color);
int		ft_keypress(int keycode, t_cub3d *cub3d);
int		ft_keyrelease(int keycode, t_cub3d *cub3d);
int		ft_render_next_frame_bymove(t_cub3d *cub3d);
void	ft_mouse(t_cub3d *cub3d);
void	ft_rot_movement(t_cub3d *cub3d, int i, double x);
void	ft_gun(t_cub3d *cub3d);
int		ft_mousepress(int mousecode, int x, int y, t_cub3d *cub3d);
void	check_map(char **map);
void	msg_exit(char *error);
void	init_file_content(char **buff, char **file_content);
void	init_pars_orientation(t_pars *pars, char **file_content, int i, int j);
void	init_pars(t_pars *pars);
void	init_rgb(t_pars *pars, char **tmp, int option, char **file_content);
int		size_tab(char **tab);
void	free_exit(t_pars *pars, char **file_content, char *error_msg, int op);
void	free_tmp_exit(t_pars *pars, char **file, char *error_msg, char **t);
int		check_duplicate(char **file_content, int i, t_pars *pars);
int		good_size(char **buff);
int		ft_handle_mouse_move(int x, int y, t_cub3d *cub3d);

#endif