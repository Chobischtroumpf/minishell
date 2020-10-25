/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 14:52:51 by adorigo           #+#    #+#             */
/*   Updated: 2020/10/25 10:31:13 by adorigo          ###   ########.fr       */
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
			ft_printf("exit\n");
			exit(ft_numeric_arg_error(cmd->argv[0], cmd->argv[1], 1));
		}
		if (cnt > 2)
		{
			ft_printf("exit\n");
			return (ft_too_many_args(cmd->argv[0], 1));
		}
		ret = (char)ft_atoi(cmd->argv[1]);
		ft_free_cmd();
		exit(ret);
	}
	ft_free_cmd();
	ft_free_env();
	exit(EXIT_SUCCESS);
}
