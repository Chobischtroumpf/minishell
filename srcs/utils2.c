/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 23:00:48 by nathan            #+#    #+#             */
/*   Updated: 2021/01/06 23:15:38 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long		check_lvlneg(unsigned long nbr, int is_neg)
{
	int		new_nbr;

	new_nbr = 0;
	if (is_neg == 1)
	{
		if ((nbr >= INT_MAX && nbr <= UINT_MAX) || nbr == LONG_MAX)
			return (-1);
		else if (nbr <= INT_MAX)
			return (nbr);
		else
			return (0);
	}
	else
	{
		if (nbr > (unsigned long)INT_MAX + 2 && nbr < UINT_MAX)
			new_nbr = ((int)nbr * -1);
		if (nbr == 0)
			return (0);
		else if (new_nbr)
			return (new_nbr);
		else if (nbr <= (unsigned long)INT_MIN)
			return (-1);
		else
			return (LONG_MAX - nbr + 1);
	}
}

static int		checker(const char *str)
{
	int is_negative;

	is_negative = 1;
	if (str[0] == '-' || str[0] == '+')
	{
		if (str[0] == '-')
			is_negative = -1;
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
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (nb > (unsigned long)LONG_MAX)
			return ((long)0);
		nb *= 10;
		nb += str[i] - '0';
		i++;
	}
	if (nb > (unsigned long)LONG_MAX)
		return ((long)0);
	if (nb <= (unsigned long)LONG_MAX)
		return (check_lvlneg(nb, is_negative));
	return ((long)nb * is_negative);
}
