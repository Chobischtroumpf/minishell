/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 17:53:18 by alessandro        #+#    #+#             */
/*   Updated: 2019/12/05 17:53:32 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_ptr(char *ptr, t_pl pl)
{
	write(1, "0x", 2);
	if (pl.precise != 0 || *ptr != '0')
		write(1, ptr, ft_strlen(ptr));
}

static void	print_res(char *ptr, t_pl pl, int sp)
{
	if (pl.f_minus)
	{
		print_ptr(ptr, pl);
		while (sp-- > 0)
			write(1, " ", 1);
	}
	else
	{
		while (sp-- > 0)
			write(1, " ", 1);
		print_ptr(ptr, pl);
	}
}

int			print_p(t_pl pl, va_list *ap)
{
	long	n;
	char	*ret;
	int		size;
	int		len;

	n = (unsigned long)va_arg(*ap, void*);
	if (!(ret = ft_itoa_base(n, "0123456789abcdef", 16)))
		return (0);
	if (pl.precise == 0 && *ret == '0')
		len = 0 + 2;
	else
		len = ft_strlen(ret) + 2;
	if (len > pl.min_w)
		size =  len ;
	else
		size = pl.min_w;
	print_res(ret, pl, size - len);
	free_all(ret);
	return (size);
}
