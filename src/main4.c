
# include "../minilibx-linux/mlx.h"
# include <math.h>
# include <limits.h>

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <fcntl.h>
# include <stdarg.h>
# include <wchar.h>
# include <stdio.h>



# define BUFFER_SIZE 1
# define FD_MAX 1000

typedef	struct	s_get
{
	int			fd;
	int			ret;
}				t_get;




typedef struct s_fdf
{

    int width;
    int height;
    int **map2D;
	int *map_x_size;
	
	int zoom;
	int color;
	int shift_x;
	int shift_y;
	float r_x;
	float r_y;
	int zoom_base;

	void *mlx_ptr;
	void *win_ptr;


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

// DRAW ----------------------------------------
float ft_max(float a, float b);
float mod(float i);
void algo_draw(float x, float y, float x1, float y1, t_fdf *fdf);
void draw(t_fdf *fdf);


void	ft_error(char *msg);

//-------- ATTENTION TEST --------//
void print_map(t_fdf *fdf);

//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------

void    ft_free_tab(t_fdf *fdf, int height)
{
    int i;
    i = 0;

    while (i < height)
    {
        free(fdf->map2D[i]);
        i++;
    }
    free(fdf->map2D);
}


int stock_height(char *file)
{
    char *line;
    int fd;
    int height;

    if ((fd = open(file, O_RDONLY, 0)) == -1)
		ft_error("Error : Open");
    height = 0;
    while(get_next_line(fd, &line) > 0)
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

    if ((fd = open(file, O_RDONLY, 0)) == -1)
		ft_error("Error : Open");
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
    free(tab_num);
}

int stock_width_malloc(char *file, int i)
{
    char *line;
    int fd;
    int width;
	int stop = i;

	if ((fd = open(file, O_RDONLY, 0)) == -1)
		ft_error("Error : Open");
	while(get_next_line(fd, &line))
	{
		if(stop <= 0)
			break;
		stop--;
		free(line);
	}
	width = ft_wdcounter(line, ' ');
	free(line);
	close(fd);
	return (width);
}

void stock_map(t_fdf *fdf, char *file)
{
    int fd;
    char *line;
    int i;
	int j;

    fdf->height = stock_height(file);
    fdf->map2D = (int **)malloc(sizeof(int *) *(fdf->height + 2));
	if(!fdf->map2D)
		ft_error("Error1 : Malloc");
	fdf->map_x_size = malloc(sizeof(int) *(fdf->height +1));
	if(!fdf->map_x_size)
		ft_error("Error2 : Malloc");
    i = 0;
	j = 0;
    while (i < fdf->height )
	{
		fdf->width = stock_width_malloc(file, j);
        fdf->map2D[i++] = (int*)malloc(sizeof(int) * (fdf->width + 1));
		if(fdf->map2D[i - 1] == NULL)
			ft_error("Error3 : Malloc");
		fdf->map_x_size[i] = fdf->width + 1;
		j++;
		
    }
    i = 1;
	if ((fd = open(file, O_RDONLY, 0)) == -1)
		ft_error("Error : Open");
    i = 0;
	
    while (get_next_line(fd, &line))
    {
        stock_map2d(fdf->map2D[i], line);
        free(line);
        i++;
    }
    close(fd);
}


//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------

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

//---------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//---------------------------------


void	ft_memdel(void **ap)
{
    if (!ap)
            return ;
	free(*ap);
	*ap = NULL;
}


void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*b2;

	b2 = (unsigned char *)b;

	while (len > 0)
	{
		b2[len - 1] = c;
		len--;
	}
	return (b2);
}



void	ft_bzero(void *s, int n)
{
	ft_memset(s, '\0', n);
}


void	ft_strdel(char **as)
{
	if (as)
	{
		free(*as);
		*as = NULL;
	}
}


char	*ft_strnew(size_t size)
{
	char	*s;

	s = (char *)malloc(size + 1);
	if (s == NULL)
		return (NULL);
	ft_bzero(s, (int)size + 1);
	return ((void *)s);
}


char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*s2;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	s2 = ft_strnew(len);
	if (s2 == NULL)
		return (NULL);
	while (len > 0)
	{
		s2[i] = s[start + i];
		i++;
		len--;
	}
	return (s2);
}




//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//---------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------

size_t	ft_strlen(const char *s1)
{
	unsigned int	i;

	i = 0;
	while (s1[i])
		i++;
	return (i);
}

void	manage_rest(char **rest, size_t i)
{
	char *old_rest;

	old_rest = *rest;
	if ((*rest)[i + 1])
	{
		*rest = ft_strsub(*rest, i + 1, ft_strlen(*rest));
		ft_strdel(&old_rest);
	}
	else
		ft_strdel(rest);
}

void	manage_line(int is_join, char **line, char **rest, size_t i)
{
	char *old_line;
	char *eol;

	if (is_join)
	{
		old_line = *line;
		eol = ft_strsub(*rest, 0, i);
		*line = ft_strjoin(*line, eol);
		ft_strdel(&old_line);
		ft_strdel(&eol);
	}
	else
		*line = ft_strdup("");
	manage_rest(rest, i);
}

int		check_rest(t_get *get, char **rest, char **line)
{
	size_t	i;
	char	*tmp;

	i = -1;
	get->ret = 1;
	while (*rest && ++i < ft_strlen(*rest))
	{
		if ((*rest)[i] == '\n')
		{
			if (i == 0 && *line && ft_strlen(*line) == 0)
				manage_line(0, line, rest, i);
			else
				manage_line(1, line, rest, i);
			return (1);
		}
	}
	tmp = *line;
	*line = ft_strjoin(*line, *rest);
	if (*line == NULL)
		*line = ft_strdup(*rest);
	ft_strdel(&tmp);
	ft_strdel(rest);
	return (0);
}

void	ft_read(t_get *get, char **rest, char **line)
{
	char *buf;

	buf = ft_strnew(BUFFER_SIZE);
	if (buf == NULL)
	{
		get->ret = -1;
		return ;
	}
	while ((get->ret = read(get->fd, buf, BUFFER_SIZE)))
	{
		buf[get->ret] = '\0';
		*rest = ft_strjoin(*rest, buf);
		if (*rest == NULL)
			*rest = ft_strdup(buf);
		if ((get->ret < 0) || check_rest(get, rest, line))
			break ;
	}
	ft_strdel(&buf);
}

int		get_next_line(int const fd, char **line)
{
	t_get		*get;
	static char	**rest = NULL;

	if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE <= 0 || !line)
		return (-1);
	if (!(get = (t_get *)malloc(sizeof(t_get))))
		return (-1);
	get->fd = fd;
	if (rest == NULL)
		if (!(rest = (char **)malloc(sizeof(char *) * FD_MAX)))
			return (-1);
	*line = ft_strnew(0);
	if (rest[fd] == NULL || !check_rest(get, &rest[fd], line))
		ft_read(get, &rest[fd], line);
	if (get->ret == -1)
		return (-1);
	if (get->ret == 0 && rest[fd] == NULL && *line && ft_strlen(*line) == 0)
	{
		ft_strdel(line);
		ft_memdel((void *)&get);
		return (0);
	}
	ft_memdel((void *)&get);
	return (1);
}



//---------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//---------------------------------





//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//---------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------

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
//---------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//---------------------------------





//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//---------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------

void color_z_hot(t_fdf *fdf, int z , int z1)
{
	if((z > 0 && z <= 3) || (z1 > 0 && z <= 3))
		fdf->color = 0xf48e8e;
	else if((z > 3 && z <= 5) || (z1 > 3 && z <= 5))
		fdf->color = 0xe16464;
	else if((z > 5 && z <= 8 ) || (z1 > 5 && z <= 8))
		fdf->color = 0xf05f5f;
	else if((z > 8 && z <= 10) || (z1 > 8 && z <= 10))
		fdf->color = 0xdf3838;
	else if((z > 10 && z <= 15) || (z1 > 10 && z <= 15))
		fdf->color = 0xd81c1c;
	else if(z > 15 || z1 > 15 )
		fdf->color = 0xd20000;
}

void color_z_frost(t_fdf *fdf, int z  ,int z1)
{
	if((z < 0 && z > -3)  || (z1 < 0 && z > -3))
		fdf->color = 0x8f83f7;
	else if((z < -3 && z > -5)  || (z1 < -3 && z > -5))
		fdf->color = 0x695af0;
	else if((z < -5 && z > -8 ) || (z1 < -5 && z > -8))
		fdf->color = 0x4d3ed5;
	else if((z < -8 && z > -10)  || (z1 < -8 && z > -10))
		fdf->color = 0x3324b8;
	else if((z < -10 && z > -15)  || (z1 < -10 && z > -15))
		fdf->color = 0x2010b7;
	else if(z < -15  || z1 < -15 )
		fdf->color = 0x1100b8;
}

void color_z(t_fdf *fdf, int z , int z1)
{
	if(z  || z1)
	{
		if(z > 0  || z1 > 0)
			color_z_hot(fdf, z , z1);
		if(z < 0  || z1 < 0)
			color_z_frost(fdf, z, z1);
	}
	else
		fdf->color = 0xffffff;
}


void isometric(float *x, float *y, int z, t_fdf *fdf)
{
	*x = (*x - *y) * cos(0.8 + fdf->r_x);
	*y = (*x + *y) * sin(0.8 + fdf->r_y) - z;
}

float ft_max(float a, float b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

float mod(float i)
{
	if (i < 0)
		return (-i);
	else
		return (i);
}

void algo_draw(float x, float y, float x1, float y1, t_fdf *fdf)

{
	float x_step;
	float y_step;
	int max;
	int z;
	int z1;

	//-------zoom--------
	z = fdf->map2D[(int)y][(int)x];
	z1 = fdf->map2D[(int)y1][(int)x1];

	x = x * fdf->zoom;
	y = y * fdf->zoom;
	x1 = x1 * fdf->zoom;
	y1 = y1 * fdf->zoom;
	//-------color-------
	color_z(fdf, z , z1);
	isometric(&x, &y, z, fdf);
	isometric(&x1, &y1, z1, fdf);
	x = x + fdf->shift_x ;
	y = y + fdf->shift_y ;
	x1 = x1 + fdf->shift_x ;
	y1 = y1 + fdf->shift_y ;
	x_step = x1 - x;
	y_step = y1 - y;
	max = ft_max(mod(x_step), mod(y_step));
	x_step = x_step / max;
	y_step = y_step / max;
	while ((int)(x - x1) || (int)(y - y1))
	{	
		mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, x, y , fdf->color);
		x = x + x_step;
		y = y + y_step;
	}
}


void draw(t_fdf *fdf)
{
	int x;
	int y;
	int k;

	y = 0;
	k = 1;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->map_x_size[k] -1)
		{
			if(x < fdf->map_x_size[k] -2)
				algo_draw(x, y, x + 1, y , fdf);
			if(y < fdf->height - 1)
				algo_draw(x, y, x , y + 1, fdf);
			x++;
		}
		y++;
		k++;
	}
}



//---------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
void parsing_argv(int argc, char *file)
{
	int i;
	int stop;
    
    i = 0;
	if (argc != 2)
		ft_error("Error: ARGS ./fdf map.fdf");
    while (file[i] != '\0')
        i++;
    while (file[i] != '.')
        i--;
	stop = i;
	while(file[i] != '\0')
	{
    	if (file[i] != '.' && file[i] != 'f' && file[i] != 'd')
				ft_error("Error: FILE map.fdf");
		i++;
	}
	if (i != stop + 4)
		ft_error("Error: FILE map.fdf");
}



void init_value(t_fdf *fdf)
{
	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, 1000, 1000, "FDF");
	fdf->zoom = 20;
	fdf->shift_x = 0;
	fdf->shift_y = 0;
	fdf->r_x = 0.00;
	fdf->r_y = 0.00;
	fdf->zoom_base = 0;
	
}



//---------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------

void ctrl_arrow(t_fdf *fdf, int key)
{
	if(key == 65362)
		fdf->shift_y = fdf->shift_y - 10;
	if(key == 65364)
		fdf->shift_y = fdf->shift_y + 10;
	if(key == 65361)
		fdf->shift_x = fdf->shift_x - 10;
	if(key == 65363)
		fdf->shift_x = fdf->shift_x + 10;
}

void ctrl_zqsd(t_fdf *fdf, int key)
{
	if(key == 115)
		fdf->r_y = fdf->r_y - 0.05;
	if(key == 122)
		fdf->r_y = fdf->r_y + 0.05;
	if(key == 100)
		fdf->r_x = fdf->r_x - 0.05;
	if(key == 113)
		fdf->r_x = fdf->r_x + 0.05;
}

void ctrl_zoom(t_fdf *fdf, int key)
{
	if(key == 65453)
		if(fdf->zoom >= 22)
			fdf->zoom = fdf->zoom - 2;
	if(key == 65451)
		if(fdf->zoom <= 800)
			fdf->zoom = fdf->zoom + 2;

}

int deal_key(int key, t_fdf *fdf)
{
	if(key == 65307)
	{
		mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
		exit(1);
		return 0;
	}
	if(key == 65362 || key == 65364 || key == 65361 || key == 65363)
		ctrl_arrow(fdf, key);
	
	if(key == 115 || key == 122 || key == 100 || key == 113)
		ctrl_zqsd(fdf, key);
	if(key == 65453 || key == 65451)
		ctrl_zoom(fdf, key);
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	draw(fdf);
	return (0);
}



//---------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------

int		main(int argc, char **argv)
{
	t_fdf	*fdf;
	
	parsing_argv(argc, argv[1]);
	fdf = (t_fdf*)malloc(sizeof(fdf));
	if(fdf == NULL)
		ft_error("Error : Malloc");
	//-------free-test OK -------
	//free(fdf);

	stock_map(fdf, argv[1]);
	//-------free-test KO -------
	//ft_free_tab(fdf, fdf->height);

	init_value(fdf);
	draw(fdf);
	mlx_key_hook(fdf->win_ptr, deal_key, fdf);	
	mlx_loop(fdf->mlx_ptr);
    return (0);
}


