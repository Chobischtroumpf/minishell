/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 14:52:51 by adorigo           #+#    #+#             */
/*   Updated: 2021/01/13 15:08:43 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	checker(char **str)
{
	int	is_negative;

	is_negative = 0;
	while (**str == '\f' || **str == '\r' || **str == ' ' || **str == '\t')
		(*str)++;
	if (*str[0] == '-' || *str[0] == '+')
	{
		if (*str[0] == '-')
			is_negative = 1;
	}
	return (is_negative);
}

static int
	check_sign(char c)
{
	if (c == '+' || c == '-')
		return (1);
	return (0);
}

static int
	ft_atol_check(const char *str, unsigned long nb, int is_sign, int is_neg)
{
	char			*str_cpy;
	char			*str_cpy_cpy;
	int				i;

	if (!(str_cpy = ft_strtrim(str, " \t")))
		ft_exit_error();
	str_cpy_cpy = str_cpy;
	is_neg = checker(&str_cpy);
	is_sign = check_sign(str_cpy[0]);
	i = is_sign;
	while (str_cpy[is_sign])
		if (!ft_isdigit(str_cpy[is_sign++]))
			return (free_str_ret(str_cpy_cpy, 0));
	while (str_cpy[i] >= '0' && str_cpy[i] <= '9')
	{
		if ((!is_neg && nb > LONG_MAX) || nb > (unsigned long)LONG_MIN)
			return (free_str_ret(str_cpy_cpy, 0));
		nb *= 10;
		if (nb > (unsigned long)LONG_MAX && (nb + str_cpy[i] - '0') < INT_MAX)
			return (free_str_ret(str_cpy_cpy, 0));
		nb += str_cpy[i++] - '0';
	}
	if ((!is_neg && nb > LONG_MAX) || nb > (unsigned long)LONG_MIN)
		return (free_str_ret(str_cpy_cpy, 0));
	return (free_str_ret(str_cpy_cpy, 1));
}

/*
** ft_exec_exit takes a pointer to a t_cmd struct, checks if the argument
** to the exit cmd is numeric or not, and if it has more than two args
** if the argument is not numeric or there are too many arguments, the exit
** command will still do it's job, ie exiting, but with an error return code
*/

int
	ft_exec_exit(t_cmd *cmd)
{
	int		digit;
	int		ret;

	if (cmd->argv[1])
	{
		digit = ft_atol_check(cmd->argv[1], 0, 0, 0);
		if (!digit)
		{
			ft_numeric_arg_error(cmd->argv[0], cmd->argv[1]);
			ft_free_all();
			exit(255);
		}
		if (ft_count_arg(cmd->argv) > 2)
		{
			ft_too_many_args(cmd->argv[0], 0);
			ft_free_all();
			exit(1);
		}
		ret = (char)ft_atol(cmd->argv[1]);
		ft_free_all();
		exit(ret);
	}
	ft_free_all();
	exit(EXIT_SUCCESS);
}
