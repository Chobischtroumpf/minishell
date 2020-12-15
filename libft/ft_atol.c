/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 10:46:26 by adorigo           #+#    #+#             */
/*   Updated: 2020/12/13 14:06:39 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	checker(const char **str)
{
	int is_negative;

	while (**str == ' ' || **str == '\t' || **str == '\n'
			|| **str == '\v' || **str == '\f' || **str == '\r')
		(*str)++;
	is_negative = 0;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			is_negative = 1;
		(*str)++;
	}
	return (is_negative);
}

long		ft_atol(const char *str)
{
	unsigned long	nb;
	int				i;
	int				is_negative;

	is_negative = checker(&str);
	i = 0;
	nb = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (!is_negative && nb > (unsigned long)LONG_MAX)
			return (1);
		else if (nb > (unsigned long)LONG_MIN)
			return (0);
		nb *= 10;
		nb += str[i] - '0';
		i++;
	}
	if (is_negative)
		return (-nb);
	else
		return (nb);
}
