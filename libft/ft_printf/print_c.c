/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 17:50:27 by alessandro        #+#    #+#             */
/*   Updated: 2019/12/05 17:50:30 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_c(t_pl pl, va_list *ap)
{
	char	*ret;
	char	c;

	c = va_arg(*ap, int);
	if (!pl.min_w)
		pl.min_w = 1;
	if (!(ret = sp_malloc(pl.min_w)))
		return (0);
	if (pl.f_minus)
		ret[0] = c;
	else
		ret[pl.min_w - 1] = c;
	write(1, ret, pl.min_w);
	free_all(ret);
	return (pl.min_w);
}
