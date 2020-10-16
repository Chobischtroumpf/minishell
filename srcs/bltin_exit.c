/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 14:52:51 by adorigo           #+#    #+#             */
/*   Updated: 2020/10/16 14:01:23 by alessandro       ###   ########.fr       */
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

int			ft_exec_exit(t_cmd *cmd)
{
	int		cnt;
	int		digit;
	int		ret;

	cnt = count_arg(cmd->argv);
	digit = ft_check_is_digit(cmd->argv[1]);
	if (cmd->argv[1])
	{
		if (!digit)
		{
			ft_printf("exit\n");
			exit(numeric_arg_error(cmd->argv[0], cmd->argv[1], EXIT_FAILURE));
		}
		if (cnt > 2)
		{
			ft_printf("exit\n");
			return (too_many_args(cmd->argv[0], 1));
		}
		ret = (char)ft_atoi(cmd->argv[1]);
		ft_free_cmd();
		exit(ret);
	}
	ft_free_cmd();
	exit(EXIT_SUCCESS);
}
