/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 13:43:46 by adorigo           #+#    #+#             */
/*   Updated: 2020/05/15 09:39:16 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		numeric_arg_error(char *cmd, char *arg, int ret)
{
	ft_printf("minishell: %s: %s: numeric argument required\n", cmd, arg);
	return (ret);
}

int		too_many_args(char *cmd, int ret)
{
	ft_printf("minishell: too many arguments: %s\n", cmd);
	return (ret);
}

int		parse_error(char *error, int ret)
{
	ft_printf("minishell : parse error near '%s'\n", error);
	return(ret);
}

void	*exit_error(void)
{
	char *strerr;

	ft_free_cmd();
	strerr = strerror(errno);
	ft_putstr_fd(strerr, 2);
	exit(-1);
	return (NULL);
}
