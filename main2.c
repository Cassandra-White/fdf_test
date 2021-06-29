
# include <limits.h>

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <fcntl.h>
# include <stdarg.h>
# include <wchar.h>
# include <stdio.h>

# define BUFFER_SIZE 10



typedef struct s_fdf
{

    int width;
    int height;
    int **map2D;




}               t_fdf;

int	ft_wdcounter(char const *str, char c);
void stock_map(t_fdf *fdf, char *file);
void stock_map2d(int *map2d, char *line);
int stock_width(char *file);
int stock_height(char *file);


// SPLIT --------
char			**ft_strsplit(char const *str, char c);

//ATOI ----------
int		ft_atoi(const char *s);

// GNL ----------
int		get_next_line(int fd, char **line);

int		ft_end(char **line, char **save, int fd, int bytes);
int		ft_line(char **line, char **save, int fd, int i);
int		ft_next_step(char **line, char **save, int fd, int bytes);
size_t	ft_strlen(const char *s1);
char	*ft_malloc(size_t size);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int str, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *str, int c);

// FT_ERROR --------
void	ft_error(char *msg);

int stock_height(char *file)
{
    char *line;
    int fd;
    int height;

    fd = open(file, O_RDONLY, 0);
    height = 0;
    while(get_next_line(fd, &line))
    {
        height++;
        free(line);
    }
    close(fd);
    return (height);
}

int stock_width(char *file)
{
    char *line;
    int fd;
    int width;

    fd = open(file, O_RDONLY, 0);
    get_next_line(fd, &line);
    width = ft_wdcounter(line, ' ');
    free(line);
    close(fd);
    return (width);

}

void stock_map2d(int *map2d, char *line)
{
    char **tab_num;
    int i;

    tab_num = ft_strsplit(line, ' ');
    i = 0;
    while (tab_num[i])
    {
        map2d[i] = ft_atoi(tab_num[i]);
        free(tab_num[i]);
        i++;
    }
    free(tab_num[i]);

}


void stock_map(t_fdf *fdf, char *file)
{
    int fd;
    char *line;
    int i;

    fdf->height = stock_height(file);
    fdf->width = stock_width(file);
    fdf->map2D = (int **)malloc(sizeof(int *) *(fdf->height +1));
    i = 0;

    while (i <= fdf->height)
	{
        fdf->map2D[i] = (int*)malloc(sizeof(int) * (fdf->width + 1));
		i++;
	}
	fd = open(file, O_RDONLY, 0);
    i = 0;
	
    while (get_next_line(fd, &line))
    {
        stock_map2d(fdf->map2D[i], line);
        free(line);
        i++;
    }
    close(fd);
    fdf->map2D[i] = NULL;

}


//---------------------------------


int		main(int argc, char **argv)
{
	t_fdf	*fdf;

	if (argc != 2)
		ft_error("usage: ./fdf map.fdf");
	fdf = (t_fdf*)malloc(sizeof(fdf));
    stock_map(fdf, argv[1]);
    printf("\n \n");
    // TEST AFFICHAGE MAP
        int i;
        int j;
        i = 0;
        while (i < fdf->height)
        {
            j = 0;
            while (j < fdf->width)
            {
                printf("%3d", fdf->map2D[i][j]);
                j++;
            }
            printf("\n");
            i++;
        }
		 printf("\n\n");
    // FIN TEST AFFICHAGE MAP
    
    return 0;
}



//---------------------------------

int		ft_wdcounter(char const *str, char c)
{
	int i;
	int words;

	words = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == c && str[i] != '\0')
			i++;
		if (str[i])
			words++;
		while (str[i] != c && str[i] != '\0')
			i++;
	}
	return (words);
}

//---------------------------------

static int		words(char const *str, char c)
{
	int i;
	int words;

	words = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == c && str[i] != '\0')
			i++;
		if (str[i])
			words++;
		while (str[i] != c && str[i] != '\0')
			i++;
	}
	return (words);
}

static char		**memory_giver(char const *str, char c)
{
	char	**res;
	int		letters;
	int		i;
	int		j;

	if ((res = (char **)malloc(sizeof(char*) * (words(str, c) + 1))) == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		letters = 0;
		while (str[i] == c && str[i])
			i++;
		while (str[i] != c && str[i] != '\0')
		{
			letters++;
			i++;
		}
		if (letters > 0)
			if ((res[j++] = (char *)malloc(sizeof(char) * letters + 1)) == NULL)
				return (NULL);
	}
	res[j] = 0;
	return (res);
}

char			**ft_strsplit(char const *str, char c)
{
	char	**res;
	int		i;
	int		j;
	int		str_number;
	int		size;

	if (str == NULL)
		return (NULL);
	size = words(str, c);
	res = memory_giver(str, c);
	if (res == NULL)
		return (NULL);
	i = 0;
	str_number = 0;
	while (str_number < size)
	{
		while (str[i] == c && str[i])
			i++;
		j = 0;
		while (str[i] != c && str[i])
			res[str_number][j++] = str[i++];
		res[str_number][j] = '\0';
		str_number++;
	}
	return (res);
}

//---------------------------------

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

//_____________________________________________


size_t	ft_strlen(const char *s1)
{
	unsigned int	i;

	i = 0;
	while (s1[i])
		i++;
	return (i);
}

int		ft_end(char **line, char **save, int fd, int bytes)
{
	if (bytes == BUFFER_SIZE)
		return (get_next_line(fd, line));
	*line = ft_strdup(save[fd]);
	free(save[fd]);
	save[fd] = NULL;
	return (0);
}

int		ft_line(char **line, char **save, int fd, int i)
{
	char	*temp;

	*line = ft_substr(save[fd], 0, i);
	temp = ft_strdup(save[fd] + i + 1);
	free(save[fd]);
	save[fd] = temp;
	if (save[fd][0] == '\0')
	{
		free(save[fd]);
		save[fd] = NULL;
	}
	return (1);
}

int		ft_next_step(char **line, char **save, int fd, int bytes)
{
	int		i;

	i = 0;
	if (bytes == 0 && (save[fd] == NULL || save[fd][0] == '\0'))
	{
		*line = malloc(1);
		**line = '\0';
		return (0);
	}
	while (save[fd][i] != '\0' && save[fd][i] != '\n')
		i++;
	return ((save[fd][i] == '\0') ? (ft_end(line, save, fd, bytes))
			: (ft_line(line, save, fd, i)));
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char	*save[255];
	char		buff[BUFFER_SIZE + 1];
	char		*temp;
	int			bytes;

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	while ((bytes = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[bytes] = '\0';
		if (!save[fd])
			save[fd] = ft_malloc(1);
		temp = ft_strjoin(save[fd], buff);
		free(save[fd]);
		save[fd] = temp;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (bytes < 0)
		return (-1);
	return (ft_next_step(line, save, fd, bytes));
}

char	*ft_malloc(size_t size)
{
	char	*s;
	size_t	i;

	i = 0;
	if (!(s = malloc(sizeof(size + 1))))
		return (NULL);
	while (i < size)
		s[i++] = 0;
	s[i] = '\0';
	return (s);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*string;
	size_t	size;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	size = ft_strlen(s1) + ft_strlen(s2);
	if (!(string = (char *)malloc((size + 1) * sizeof(char))))
		return (NULL);
	while (*s1)
		string[i++] = *(s1++);
	while (*s2)
		string[i++] = *(s2++);
	string[i] = '\0';
	return (string);
}

char	*ft_substr(char const *s, unsigned int str, size_t len)
{
	size_t		i;
	char		*copy;

	i = 0;
	if (!s || !(copy = malloc(((len + 1) * sizeof(char)))))
		return (0);
	if (str > ft_strlen(s))
	{
		copy[0] = '\0';
		return (copy);
	}
	while (i < len && s[str])
	{
		copy[i] = s[str];
		i++;
		str++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*ft_strdup(const char *s1)
{
	char	*copy;
	int		i;

	i = 0;
	while (s1[i])
		i++;
	if (!(copy = (char *)malloc((i * sizeof(char)) + 1)))
		return (0);
	i = -1;
	while (s1[++i])
		copy[i] = s1[i];
	copy[i] = '\0';
	return (copy);
}

char	*ft_strchr(const char *str, int c)
{
	if (c == 0)
	{
		while (*str)
			str++;
		return ((char*)str);
	}
	while (*str)
	{
		if (*str == (unsigned char)c)
			return ((char*)str);
		str++;
	}
	return (0);
}

void	ft_error(char *msg)
{
	printf("%s\n", msg);
	exit(1);
}