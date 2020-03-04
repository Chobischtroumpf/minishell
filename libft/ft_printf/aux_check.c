/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 17:47:12 by alessandro        #+#    #+#             */
/*   Updated: 2019/12/05 17:48:14 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			check_minus(char c)
{
	if (c == '-')
		return (1);
	return (0);
}

int			check_conversion(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd'
			|| c == 'i' || c == 'u' || c == 'x' || c == 'X' || c == '%')
		return (c);
	return (0);
}

int			check_form(char *f)
{
	int	cnt;
	int ck;

	cnt = 0;
	ck = 0;
	if (!f)
		return (0);
	while (*f != '\0')
	{
		if (*f == '%' && ck == 0)
			ck = 1;
		else if (check_conversion(*f) && ck == 1)
		{
			ck = 0;
			cnt++;
		}
		f++;
	}
	if (ck == 1)
		return (0);
	return (1);
}
