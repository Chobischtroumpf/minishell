/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 14:52:51 by adorigo           #+#    #+#             */
/*   Updated: 2020/11/27 13:36:42 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		checker(const char **str)
{
	int is_negative;

	is_negative = 0;
	while (**str == ' ' || **str == '\t' || **str == '\n'
			|| **str == '\v' || **str == '\f' || **str == '\r')
		(*str)++;
	if (*str[0] == '-' || *str[0] == '+')
	{
		if (*str[0] == '-')
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

static int		ft_atol_check(const char *str)
{
	unsigned long	nb;
	int				i;
	int				is_negative;
	int				is_sign;
	const char		*str_cpy;

	str_cpy = ft_strtrim(str, " \t");
	is_negative = checker(&str_cpy);
	is_sign = check_sign(str_cpy[0]);
	i = is_sign;
	while (str_cpy[is_sign])
		if (!ft_isdigit(str_cpy[is_sign++]))
			return (0);
	nb = 0;
	while (str_cpy[i] >= '0' && str_cpy[i] <= '9')
	{
		if (!is_negative && nb > (unsigned long)LONG_MAX )
			return (0);
		else if (nb > (unsigned long)LONG_MIN)
			return (0);
		nb *= 10;
		nb += str_cpy[i] - '0';
		i++;
	}
	// free((char *)str_cpy);
	if ((!is_negative && nb > (unsigned long)LONG_MAX) || nb > (unsigned long)LONG_MIN)
		return ((long)0);
	return (1);
}

/*
** ft_exec_exit takes a pointer to a t_cmd struct, checks if the argument
** to the exit cmd is numeric or not, and if it has more than two args
** if the argument is not numeric or there are too many arguments, the exit
** command will still do it's job, ie exiting, but with an error return code
*/

int			ft_exec_exit(t_cmd *cmd)
{
	int		cnt;
	int		digit;
	int		ret;

	cnt = ft_count_arg(cmd->argv);
	if (cmd->argv[1])
	{
		digit = ft_atol_check(cmd->argv[1]);
		if (!digit)
			exit(ft_numeric_arg_error(cmd->argv[0], cmd->argv[1], 255));
		if (cnt > 2)
			exit(ft_too_many_args(cmd->argv[0], 1));
		ret = (char)ft_atol(cmd->argv[1]);
		ft_free_minishell();
		exit(ret);
	}
	ft_free_minishell();
	exit(EXIT_SUCCESS);
}
