/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 17:56:14 by alessandro        #+#    #+#             */
/*   Updated: 2019/12/05 17:56:16 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	set_size(t_pl pl, int *p_len, int len, char *ret)
{
	if (pl.precise == 0 && *ret == '0')
		*p_len = 0;
	else
		*p_len = get_p_len(len, pl);;
	if (*p_len > pl.min_w)
		return (*p_len);
	else
		return (pl.min_w);
}

static int	print_without_fminus(char *ret, t_pl pl)
{
	int len;
	int p_len;
	int size;
	int i;

	len = ft_strlen(ret);
	size = set_size(pl, &p_len, len, ret);
	i = size - p_len;
	while (i-- > 0)
	{
		if (pl.precise != -1)
			write(1, " ", 1);
		else if (pl.f_zpad == 1)
			write(1, "0", 1);
		else
			write(1, " ", 1);
	}
	i = p_len - len;
	while (i-- > 0)
		write(1, "0", 1);
	if (p_len != 0 || *ret != '0')
		write(1, ret, len);
	free_all(ret);
	return (size);
}

static int	print_with_fminus(char *ret, t_pl pl)
{
	int len;
	int p_len;
	int size;
	int i;

	len = ft_strlen(ret);
	size = set_size(pl, &p_len, len, ret);
	i = p_len - len;
	while (i-- > 0)
		write(1, "0", 1);
	if (p_len != 0 || *ret != '0')
		write(1, ret, len);
	i = size - p_len;
	while (i-- > 0)
		write(1, " ", 1);
	free_all(ret);
	return (size);
}

static int	print_res(char *ret, t_pl pl)
{
	if (pl.f_minus)
		return (print_with_fminus(ret, pl));
	else
		return (print_without_fminus(ret, pl));
}

int			print_u(t_pl pl, va_list *ap)
{
	char			*ret;
	unsigned int	u;

	u = va_arg(*ap, unsigned int);
	if (!(ret = ft_utoa_base(u, "0123456789", 10)))
		return (0);
	return (print_res(ret, pl));
}
