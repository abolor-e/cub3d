#include "../cub3d.h"

int	cmpchar(char chr1, char chr2)
{
	if ((unsigned char)chr1 != (unsigned char)chr2)
		return ((unsigned char)chr1 - (unsigned char)chr2);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] && s2[i])
	{
		if (cmpchar(s1[i], s2[i]))
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i < n)
		return (cmpchar(s1[i], s2[i]));
	return (0);
}

char	*ft_strdup(char *s)
{
	int		i;
	int		size;
	char	*cpy;

	i = 0;
	size = ft_strlen(s);
	cpy = malloc(sizeof(char) * (size + 1));
	if (!cpy)
		return (NULL);
	while (s[i] != '\0' && s[i] != '\n')
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

int	ft_atoi(const char *str)
{
	size_t		i;
	int			sign;
	long int	result;
	long int	tmp;

	result = 0;
	i = 0;
	tmp = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i++] - '0');
		if (tmp > result && sign > 0)
			return (-1);
		else if (tmp > result && sign < 0)
			return (0);
		tmp = result;
	}
	return ((int)(result * sign));
}
