/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 14:52:51 by adorigo           #+#    #+#             */
/*   Updated: 2020/11/15 10:52:06 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_is_digit(char *str)
{
	while (str && *str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
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
	digit = ft_check_is_digit(cmd->argv[1]);
	if (cmd->argv[1])
	{
		if (!digit)
		{
			exit(ft_numeric_arg_error(cmd->argv[0], cmd->argv[1], 255));
		}
		if (cnt > 2)
		{
			exit(ft_too_many_args(cmd->argv[0], 1));
		}
		ret = (char)ft_atoi(cmd->argv[1]);
		ft_free_minishell();
		exit(ret);
	}
	ft_free_minishell();
	exit(EXIT_SUCCESS);
}
