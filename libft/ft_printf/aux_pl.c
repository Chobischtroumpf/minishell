/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_pl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 17:47:50 by alessandro        #+#    #+#             */
/*   Updated: 2019/12/05 17:48:10 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	init_pl(t_pl *pl)
{
	pl->f_minus = 0;
	pl->f_zpad = 0;
	pl->f_dot = 0;
	pl->min_w = 0;
	pl->precise = -1;
	pl->convert = 0;
}

static void	get_zpad_minus(t_pl *pl, char **form, int *digit)
{
	*digit = 0;
	while (**form == '-' || **form == '0' || **form == ' ')
	{
		if (**form == '-')
			pl->f_minus = 1;
		else if (**form == '0')
			pl->f_zpad = 1;
		(*form)++;
	}
}

static void	get_min_w(t_pl *pl, char **form, va_list *ap)
{
	int	digit;

	get_zpad_minus(pl, form, &digit);
	while (**form != '.' && !check_conversion(**form))
	{
		if (ft_isdigit(**form))
			digit = (digit * 10) + (**form - '0');
		else if (**form == '*')
		{
			if ((pl->min_w = va_arg(*ap, int)) < 0)
			{
				pl->min_w = -1 * pl->min_w;
				pl->f_minus = 1;
			}
			digit = 0;
		}
		else
		{
			if (digit)
				pl->min_w = digit;
			digit = 0;
		}
		(*form)++;
	}
	if (digit)
		pl->min_w = digit;
}

static void	get_precision(t_pl *pl, char **form, va_list *ap)
{
	int digit;

	digit = 0;
	while (!check_conversion(**form))
	{
		if (ft_isdigit(**form))
			digit = (digit * 10) + (**form - '0');
		else if (**form == '*')
		{
			if ((pl->precise = va_arg(*ap, int)) < 0)
				pl->precise = -1;
			digit = pl->precise;
		}
		(*form)++;
	}
	pl->precise = digit;
}

int			make_pl(t_pl *pl, char *form, va_list *ap)
{
	char	*begin;

	begin = form;
	init_pl(pl);
	get_min_w(pl, &form, ap);
	if (*form == '.')
		get_precision(pl, &form, ap);
	pl->convert = *form++;
	return (form - begin);
}
