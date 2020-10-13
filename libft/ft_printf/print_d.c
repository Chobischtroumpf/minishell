/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 17:50:51 by alessandro        #+#    #+#             */
/*   Updated: 2019/12/05 17:50:53 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_pad(t_pl pl, int sign, char **ret, int i)
{
	if (pl.f_zpad == 1 && pl.precise == -1)
	{
		if (sign && (*ret)++)
			write(1, "-", 1);
		while (i--)
			write(1, "0", 1);
	}
	else
	{
		while (i--)
			write(1, " ", 1);
		if (sign && (*ret)++)
			write(1, "-", 1);
	}
}

static int	print_without_fminus(char *ret, t_pl pl, int sign)
{
	int		p_len;
	int		size;
	int		i;
	char	*begin;

	begin = ret;
	if (pl.precise == 0 && *ret == '0')
		p_len = 0;
	else
		p_len = get_p_len(ft_strlen(ret) - sign, pl);
	if (p_len + sign > pl.min_w)
		size = p_len + sign;
	else
		size = pl.min_w;
	i = size - p_len - sign;
	print_pad(pl, sign, &ret, i);
	i = p_len - ft_strlen(ret) - sign;
	while (i-- > 0)
		write(1, "0", 1);
	if (p_len != 0 || *ret != '0')
		write(1, ret, ft_strlen(ret) - sign);
	free_all(begin);
	return (size);
}

static int	print_with_fminus(char *ret, t_pl pl, int sign)
{
	int		p_len;
	int		size;
	int		i;
	char	*begin;

	begin = ret;
	if (pl.precise == 0 && *ret == '0')
		p_len = 0;
	else
		p_len = get_p_len(ft_strlen(ret) - sign, pl);
	if (p_len + sign > pl.min_w)
		size = p_len + sign;
	else
		return (pl.min_w);
	if (sign)
		write(1, &*ret++, 1);
	i = p_len - ft_strlen(ret) - sign;
	while (i-- > 0)
		write(1, "0", 1);
	if (p_len != 0 || *ret != '0')
		write(1, ret, ft_strlen(ret) - sign);
	i = size - p_len - sign;
	while (i-- > 0)
		write(1, " ", 1);
	free_all(begin);
	return (size);
}

static int	print_res(char *ret, t_pl pl, int sign)
{
	if (pl.f_minus)
		return (print_with_fminus(ret, pl, sign));
	else
		return (print_without_fminus(ret, pl, sign));
}

int			print_d(t_pl pl, va_list *ap)
{
	char	*ret;
	int		d;
	int		sign;

	sign = 0;
	d = va_arg(*ap, int);
	if (d < 0) 
		sign = 1;
	if (!(ret = ft_itoa_base(d, "0123456789", 10)))
		return (0);
	return (print_res(ret, pl, sign));
}
