/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_static.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 12:17:00 by adorigo           #+#    #+#             */
/*   Updated: 2021/02/14 14:45:35 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** declares the static structure minishell, and returns it's address
*/

t_minishell	*get_minishell(void)
{
	static t_minishell	minishell;

	return (&minishell);
}

t_termcaps	*get_termcaps(void)
{
	static t_termcaps	termcap;

	return(&termcap);
}
/*
** returns a static tab with all the builtin commands
*/

char		**get_built_in(void)
{
	static char *built_in[8] = {
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit",
		NULL
	};

	return (built_in);
}
