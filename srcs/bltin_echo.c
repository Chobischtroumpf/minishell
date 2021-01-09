/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 10:23:40 by adorigo           #+#    #+#             */
/*   Updated: 2021/01/09 17:13:55 by adorigo          ###   ########.fr       */
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

static int	check_flag(int *i, int cnt, char **arg)
{
	int		ret;
	int		n_flag;
	int		j;

	n_flag = 0;
	while (*i < cnt)
	{
		if ((ret = ft_strncmp(arg[*i], "-n", 2)) == 0)
		{
			j = 2;
			while (arg[*i][j] && arg[*i][j] == 'n')
				j++;
		}
		if (!arg[*i] || ret != 0)
			break ;
		else
			n_flag = 1;
		(*i)++;
	}
	return (n_flag);
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
	int	i;
	int	n_flag;

	i = 1;
	cnt = ft_count_arg(cmd->argv);
	n_flag = check_flag(&i, cnt, cmd->argv);
	if (n_flag)
		print_arg(cmd->argv, i, cnt);
	else
	{
		print_arg(cmd->argv, 1, cnt);
		ft_putstr("\n");
	}
	return (EXIT_SUCCESS);
}
