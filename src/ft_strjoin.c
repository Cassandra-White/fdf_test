#include "../inc/fdf.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*res;
	size_t	len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	if ((str = (char *)malloc(len + 1)) == NULL)
		return (NULL);
	res = str;
	while (*s1)
	{
		*str = *s1;
		str++;
		s1++;
	}
	while (*s2)
	{
		*str = *s2;
		str++;
		s2++;
	}
	*str = '\0';
	return (res);
}
