#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_drawing {
	char	*m;
	int		w;
	int		h;
	char	c;
}				t_drawing;

typedef struct s_rectangle {
	char	rR;
	float	x;
	float	y;
	float	w;
	float	h;
	char	c;
}				t_rectangle;

int	ft_execute(FILE *f_ptr, t_drawing *d, t_rectangle *r);
int	ft_get_info(FILE *f, t_drawing *d);
int	ft_apply(t_drawing *d, t_rectangle *r);
int	ft_in_rectangle(int x, int y, t_rectangle *r);

int main(int argc, char *argv[])
{
	FILE		*f;
	t_drawing	drawing;
	t_rectangle	rectangle;

	if (argc != 2)
	{
		write(1, "Error: argument\n", 17);
		return (1);
	}
	f = fopen(argv[1], "r");
	if (f == NULL || ft_execute(f, &drawing, &rectangle) == 1)
	{
		fclose(f);
		write(1, "Error: Operation file corrupted\n", 33);
		return (1);
	}
	return 0;
}

int	ft_execute(FILE *f_ptr, t_drawing *d, t_rectangle *r)
{
	int	x;
	int	scan;

	if (ft_get_info(f_ptr, d) == 1)
		return (1);
	while ((scan = fscanf(f_ptr, "%c %f %f %f %f %c\n", &r->rR, &r->x, &r->y, &r->w, &r->h, &r->c)) == 6)
	{
		if (ft_apply(d, r) == 1)
			return (1);
	}
	if (scan != -1)
		return (1);
	x = -1;
	while (++x < d->h)
	{
		write(1, d->m + (x * d->w), d->w);
		write(1,"\n", 1);
	}
	return (0);
}

int	ft_get_info(FILE *f, t_drawing *d)
{
	if (fscanf(f, "%d %d %c\n", &d->w, &d->h, &d->c) != 3)
		return (1);
	if (d->w < 1 || d->w > 300 || d->h < 1 || d->h > 300)
		return (1);
	d->m = (char *)malloc(d->w * d->h);
	if (d->m == NULL)
		return (1);
	memset(d->m, d->c, d->w * d->h);
	return (0);
}

int	ft_apply(t_drawing *d, t_rectangle *r)
{
	int	x;
	int	y;
	int	is;

	if ((r->w <= 0. || r->h <= 0.) || (r->rR != 'R' && r->rR != 'r'))
		return (1);
	x = -1;
	while (++x < d->w)
	{
		y = -1;
		while (++y < d->h)
		{
			is = ft_in_rectangle(x, y, r);
			if (is == 2 || (is == 1 && r->rR == 'R'))
				(d->m)[x + y * d->w] = r->c;
		}
	}
	return (0);
}

int	ft_in_rectangle(int x, int y, t_rectangle *r)
{
	if (x < r->x || r->x + r->w < x || y < r->y || r->y + r->h < y)
		return (0);
	if (x - r->x < 1. || (r->x + r->w) - x < 1. || y - r->y < 1. || (r->y + r->h) - y < 1.)
		return (2);
	return (1);
}

