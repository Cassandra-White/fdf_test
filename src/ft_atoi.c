#include "../inc/fdf.h"

int		ft_atoi(const char *s)
{
	int sign;
	int res;
	int i;

	res = 0;
	i = 0;
	while ((s[i] > 8 && s[i] < 20) || s[i] == ' ')
		i++;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while ((s[i] >= '0' && s[i] <= '9') && s[i] != '\0')
		res = res * 10 + (s[i++] - '0');
	return (res * sign);
}
