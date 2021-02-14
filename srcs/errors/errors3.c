/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 23:51:38 by nathan            #+#    #+#             */
/*   Updated: 2021/02/14 14:11:28 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** the exit_error function frees the minishell struct, assigns errno to strerr
** and prints strerr to the stderr
*/

void	*ft_exit_error(char *err_msg)
{
	char *strerr;

	ft_free_minishell();
	ft_free_env();
	if (!err_msg)
		strerr = strerror(errno);
	else
		strerr = err_msg;
	ft_putstr_fd(strerr, 2);
	exit(-1);
	return (NULL);
}

int		ft_invalid_id(char *cmd, char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

long	ft_error_shlvl(long shlvl)
{
	char	*shlvl_str;

	if (!(shlvl_str = ft_itoa(shlvl)))
		ft_exit_error(NULL);
	ft_putstr_fd("minishell: warning: shell level (", 2);
	ft_putstr_fd(shlvl_str, 2);
	ft_putstr_fd(") too high, resetting to 1\n", 2);
	free(shlvl_str);
	return ((long)1);
}

int		ft_eof_error(int nbr_tokens, int ret)
{
	ft_putstr_fd("minishell: unexpected EOF while looking for matching `", 2);
	if (nbr_tokens == -1)
		ft_putstr_fd("\"", 2);
	else if (nbr_tokens == -2)
		ft_putstr_fd("'", 2);
	ft_putstr_fd("'\n", 2);
	ft_free_minishell();
	return (ret);
}

int		ft_err_read_error(char *arg, int ret)
{
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("\n", 2);
	return (ret);
}
