/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 14:52:51 by adorigo           #+#    #+#             */
/*   Updated: 2020/05/15 09:39:25 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_is_digit(char *str)
{
	while (str && *str)
	{
		if (!ft_isdigit(*str))
			return(0);
		str++;
	}
	return(1);
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
			exit(numeric_arg_error(cmd->argv[0], 1));
		}
		if (cnt > 2)
		{
			ft_printf("exit\n");
			return(too_many_arg(cmd->argv[0], 1));
		}
		ret = (char)ft_atoi(cmd->argv[1]);
		ft_free_cmd();
		exit(ret);
	}
	ft_free_cmd();
	exit(EXIT_SUCCESS);
}