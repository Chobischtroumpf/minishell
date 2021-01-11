/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_static.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 12:17:00 by adorigo           #+#    #+#             */
/*   Updated: 2020/10/27 16:34:01 by nathan           ###   ########.fr       */
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
