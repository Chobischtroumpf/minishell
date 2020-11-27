/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 23:00:48 by nathan            #+#    #+#             */
/*   Updated: 2020/11/26 23:50:18 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long		check_lvlneg(unsigned long nbr, int is_neg)
{
	if (!is_neg)
		return (nbr);
	else
		return (LONG_MAX - nbr + 1);
}

static int		checker(const char *str)
{
	int is_negative;

	is_negative = 0;
	if (str[0] == '-' || str[0] == '+')
	{
		if (str[0] == '-')
			is_negative = 1;
	}
	return (is_negative);
}

static int		check_sign(char c)
{
	if (c == '+' || c == '-')
		return (1);
	return (0);
}

long			ft_atoi_pos(const char *str)
{
	unsigned long	nb;
	int				i;
	int				is_negative;
	int				is_sign;

	is_negative = checker(str);
	is_sign = check_sign(str[0]);
	i = is_sign;
	nb = 0;
	if (ft_strlen(str) > (size_t)(19 + is_sign))
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (nb > (unsigned long long)LONG_MAX)
			return ((long)0);
		nb *= 10;
		nb += str[i] - '0';
		i++;
	}
	if (nb > (unsigned long long)LONG_MAX)
		return ((long)0);
	if (nb >= (unsigned long long)INT_MAX - 1 &&
		nb <= (unsigned long long)LONG_MAX)
		return (check_lvlneg(nb, is_negative));
	return ((long)nb);
}
