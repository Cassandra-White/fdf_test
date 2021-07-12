#include "../inc/fdf.h"

size_t	ft_strlen(const char *s1)
{
	unsigned int	i;

	i = 0;
	while (s1[i])
		i++;
	return (i);
}
