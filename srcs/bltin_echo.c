/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 10:23:40 by adorigo           #+#    #+#             */
/*   Updated: 2020/11/01 14:09:25 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** the print_arg function iterates through the argv 2 dimensional table and
** prints every line inside of it
*/

static void	print_arg(char **argv, int i, int cnt)
{
	while (argv[i])
	{
		ft_putstr(argv[i]);
		if (i < cnt - 1)
			ft_putstr(" ");
		i++;
	}
}

/*
** ft_exec_echo is a function that takes the t_cmd chained-list as a parameter,
** and will print all the args of echo, followed by a \n character.
** if the second argv is the "-n" flag, it will instead print all the args,
** except the first two, and put no newlines at the end.
*/

int			ft_exec_echo(t_cmd *cmd)
{
	int cnt;

	cnt = ft_count_arg(cmd->argv);

	if (cnt >= 2 && !ft_strcmp(cmd->argv[1], "-n"))
	{
		if (cnt > 2)
			print_arg(cmd->argv, 2, cnt);
	}
	else
	{
		print_arg(cmd->argv, 1, cnt);
		ft_putstr("\n");
	}
	return (EXIT_SUCCESS);
}
