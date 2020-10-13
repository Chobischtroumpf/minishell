/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_print_and_count.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 17:49:20 by alessandro        #+#    #+#             */
/*   Updated: 2019/12/05 17:49:34 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	free_all(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = 0;
}

char	*sp_malloc(int size)
{
	char	*ret;
	int		i;

	if (!(ret = (char *)malloc(sizeof(char) * (size + 1))))
		return (0);
	i = 0;
	while (size--)
		ret[i++] = ' ';
	ret[i] = '\0';
	return (ret);
}

int		print_and_count(t_pl pl, va_list *ap)
{
	if (pl.convert == 'c')
		return (print_c(pl, ap));
	if (pl.convert == 's')
		return (print_s(pl, ap));
	if (pl.convert == 'p')
		return (print_p(pl, ap));
	if (pl.convert == 'd' || pl.convert == 'i')
		return (print_d(pl, ap));
	if (pl.convert == 'u')
		return (print_u(pl, ap));
	if (pl.convert == 'x' || pl.convert == 'X')
		return (print_x(pl, ap));
	if (pl.convert == '%')
		return (print_percent(pl, ap));
	return (0);
}

int get_p_len(int len, t_pl pl)
{
	if (len > pl.precise)
		return (len);
	else
		return (pl.precise);
}