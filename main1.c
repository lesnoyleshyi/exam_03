#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"

typedef struct s_draw_ar {
	int		w;
	int		h;
	char	bg;
	char	*str;
}				t_dr_arr;

typedef struct s_rectangle {
	char	rR;
	float	x;
	float	y;
	float	w;
	float	h;
	char	symb;
}				t_rect;

int	ft_execute(FILE *f, t_dr_arr *dr_ar, t_rect *rect);
int	ft_get_info(FILE *f, t_dr_arr *d);
int	ft_apply(t_dr_arr *d, t_rect *r);
int	ft_in_rectangle(int x, int y, t_rect *r);

int	main (int argc, char *argv[])
{
	FILE		*f;
	t_dr_arr	dr_ar;
	t_rect		rect;

	if (argc != 2)
	{
		write(1, "Error: argument\n", 17);
		return (1);
	}
	f = fopen(argv[1], "r");
	if (f == NULL || ft_execute(f, &dr_ar, &rect) == 1)
	{
		if (f)
			fclose(f);
		write(1, "Error: Operation file corrupted\n", 33);
		return (1);
	}
	return (0);
}

int	ft_execute(FILE *f, t_dr_arr *dr_ar, t_rect *rect)
{
	int	scan;
	int	x;

	if (ft_get_info(f, dr_ar) == 1)
		return (1);
	while ((scan = fscanf(f, "%c %f %f %f %f %c\n",
		  &rect->rR, &rect->x, &rect->y, &rect->w, &rect->h, &rect->symb)) == 6)
	{
		if (ft_apply(dr_ar, rect) == 1)
			return (1);
	}
	if (scan != -1)
		return (1);
	x = -1;
	while (++x < dr_ar->h)
	{
		write(1, dr_ar->str + (x * dr_ar->w), dr_ar->w);
		write(1, "\n", 1);
	}
	return (0);
}

int	ft_get_info(FILE *f, t_dr_arr *d)
{
	if (fscanf(f, "%d %d %c\n", &d->w, &d->h, &d->bg) != 3)
		return (1);
	if (d->w <= 0 || d->w > 300 || d->h <= 0 || d->h > 300)
		return (1);
	d->str = (char *) malloc(d->w * d->h);
	if ((d->str) == NULL)
		return (1);
	memset(d->str, d->bg, d->w * d->h);
	return (0);
}

int	ft_apply(t_dr_arr *d, t_rect *r)
{
	int	x;
	int y;
	int is;

	if ((r->w <= 0. || r->h <= 0.) || (r->rR != 'r' && r->rR != 'R'))
		return (1);
	x = -1;
	while (++x < d->w)
	{
		y = -1;
		while (++y < d->h)
		{
			is = ft_in_rectangle(x, y, r);
			if (is == 2 || (is == 1 && r->rR == 'R'))
			{
				(d->str)[x + y * d->w] = r->symb;
			}
		}
	}
	return (0);
}

int	ft_in_rectangle(int x, int y, t_rect *r)
{
	if (x < r->x || x > r->x + r->w || y < r->y || y > r->y + r->h)
		return (0);
	if (x - r->x < 1. || (r->x + r->w) - x < 1. || y - r->y < 1. || r->y + r->h - y < 1.)
		return (2);
	return (1);
}