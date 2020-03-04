#include "ft_printf.h"

int	print_percent(t_pl pl, va_list *ap)
{
	char	*ret;
	size_t		i;

	i = 0;
	(void)ap;
	if (!pl.min_w)
		pl.min_w = 1;
	if (!(ret = sp_malloc(pl.min_w)))
		return (0);
	if (pl.f_minus)
		ret[0] = '%';
	else
	{
		if (pl.f_zpad == 1)
			while (i < ft_strlen(ret))
				ret[i++] = '0';
		ret[pl.min_w - 1] = '%';
	}
	write(1, ret, pl.min_w);
	free_all(ret);
	return (pl.min_w);
}
