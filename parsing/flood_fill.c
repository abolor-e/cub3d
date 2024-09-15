#include "../cub3d.h"

void	print_content(char **file_content)
{
	int	i;
	int	j;

	i = 0;
	while (file_content[i])
	{
		j = 0;
		while (file_content[i][j])
		{
			if (file_content[i][j] == '1')
				printf("\e[96m██\033[0m");
			else if (file_content[i][j] == '0')
				printf("\e[90m██\033[0m");
			else if (file_content[i][j] == 'N' | file_content[i][j] == 'S'
				| file_content[i][j] == 'E' | file_content[i][j] == 'W')
				printf("\033[0;32m██\033[0m");
			else if (file_content[i][j] == '2')
				printf("\033[1;31m██\033[0m");
			else if (file_content[i][j] == '	')
				printf("	");
			else
				printf("  ");
			j++;
			usleep(2500);
		}
		printf("\n");
		i++;
	}
}

int	checker(char **map, int i, int j)
{
	if (map[i][j] != '0' && map[i][j] != '1'
		&& map[i][j] != '2' && map[i][j] != 'N'
		&& map[i][j] != 'S' && map[i][j] != 'E'
		&& map[i][j] != 'W')
		return (1);
	return (0);
}

void	verify_map(char **map, int y, int x)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '0')
			{
				if (j == x || j == 0 || i == y - 1 || i == 0)
					map[i][j] = '2';
				else
				{
					if (checker(map, i + 1, j) || checker(map, i - 1, j)
						|| checker(map, i, j + 1) || checker(map, i, j - 1))
						map[i][j] = '2';
				}
			}
		}
	}
}

void	pars_map(char **map)
{
	int	i;
	int	j;
	int	width;
	int	height;
	int	tmp;

	height = 0;
	width = 0;
	i = -1;
	while (map[height])
		height++;
	while (map[++i])
	{
		j = -1;
		tmp = 0;
		while (map[i][++j])
		{
			if (map[i][j] == '	')
				tmp += 4;
			else
				tmp++;
		}
		if (tmp > width)
			width = tmp;
	}
	printf("width : %d\nheight : %d\n", width, height);
	verify_map(map, height, width);
}

void	msg_exit(char *error)
{
	int	i;

	i = -1;
	write(1, "\033[1;31mERROR :\033[0m ", 20);
	while (error[++i])
		write(1, &error[i], 1);
	write(1, "\n", 1);
	exit(EXIT_FAILURE);
}

void	check_map(char **map)
{
	int	i;
	int	j;
	int	player;

	player = 0;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '2')
				msg_exit("The map is not playable.");
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
				player++;
		}
	}
	if (player > 1)
		msg_exit("It can be only 1 player.");
	if (player < 1)
		msg_exit("There is no player set on the map.");
	write(0, "\033[0;32mSucced :\033[0m The map is playable!\n", 42);
}

void	flood_fill(char **map)
{
	if (!map[0])
		msg_exit("There is no map.");
	pars_map(map);
	print_content(map);
	check_map(map);
}
