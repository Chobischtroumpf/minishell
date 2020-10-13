/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 17:54:51 by alessandro        #+#    #+#             */
/*   Updated: 2019/12/05 17:54:53 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*copy_to_ret(unsigned int size, unsigned int len, char *s, t_pl pl)
{
	char			*ret;
	unsigned int	space;
	unsigned int	i;

	if (!(ret = sp_malloc(size)))
		return (0);
	i = 0;
	if (pl.f_minus)
		while (len--)
			ret[i++] = *s++;
	else
	{
		space = size - len;
		while (space--)
		{
			if (pl.f_zpad)
				ret[i] = '0';
			i++;
		}
		while (len--)
			ret[i++] = *s++;
	}
	return (ret);
}

int			print_s(t_pl pl, va_list *ap)
{
	char	*ret;
	char	*s;
	int		len;
	int		size;

	s = va_arg(*ap, char*);
	if (!s)
		s = "(null)";
	len = ft_strlen(s);
	if (pl.precise != -1 && len > pl.precise) 
		len = pl.precise;
	if (len > pl.min_w)
		size = len;
	else
		size = pl.min_w;
	if (!(ret = copy_to_ret(size, len, s, pl)))
		return (0);
	write(1, ret, size);
	free_all(ret);
	return (size);
}
