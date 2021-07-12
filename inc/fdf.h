#ifndef FDF_H
# define FDF_H

# include "../minilibx-linux/mlx.h"
# include <math.h>
# include <limits.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdarg.h>
# include <wchar.h>
# include <stdio.h>



# define BUFF_SIZE 1
# define FD_MAX 1000


typedef struct	s_arr
{
	int				fd;
	char			*rest;
	struct s_arr	*next;
}				t_arr;

typedef struct s_fdf
{
	float x;
	float y;
	float z;
	int end;
	
	int zoom;
	int zoom_z;
	int color;
	int shift_x;
	int shift_y;
	int iso_on_off;
	double degres;
	double degres_x;
	double degres_y;
	int win_x;
	int win_y;
	void *mlx_ptr;
	void *win_ptr;

}               t_fdf;


void init_value(t_fdf *fdf);

t_fdf **stock_map(char *file);

void	ft_error(char *msg);
void	parsing_argv(int argc, char *file);
void	ft_is_directory(char *file);
int		get_next_line(const int fd, char **line,int stop);

char	*ft_strjoin(char const *s1, char const *s2);
void	ft_strdel(char **as);
void	ft_memdel(void **ap);
char	*ft_strnew(size_t size);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strchr(const char *s, int c);
char	*ft_strsub(char const *s, unsigned int start, size_t len);
char	*ft_strcat(char *restrict str1, const char *restrict str2);
void	ft_strclr(char *s);
size_t	ft_strlen(const char *s1);
int		ft_atoi(const char *s);
int		ft_wdcounter(char const *str, char c);
char	**ft_strsplit(char const *str, char c);

void color_z(t_fdf *fdf, float z , float z1);
void color_z_frost(t_fdf *fdf, int z  ,int z1);
void color_z_hot(t_fdf *fdf, int z , int z1);

void draw(t_fdf **fdf);
void isometric(t_fdf *fdf, double degres_x, double degres_y);
float ft_max(float a, float b);
float mod(float i);
void set_value(t_fdf *xyz,t_fdf *xyz1, t_fdf *fdf);
void free_fdf(t_fdf **fdf);
int deal_key(int key, t_fdf **fdf);

#endif



























