#include "../inc/fdf.h"

void	ft_error(char *msg)
{
	write(1, msg, ft_strlen(msg));
	write(1, "\n", 1);
	exit(1);
}