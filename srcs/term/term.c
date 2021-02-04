/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 13:22:43 by adorigo           #+#    #+#             */
/*   Updated: 2021/02/04 17:30:32 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_terminal_data()
{
	char *termtype;
	int success;

	termtype = ft_find_by_key2("TERM");
	if (termtype == 0)
		ft_exit_error();
	success = tgetent (term_buffer, termtype);
	if (success < 0)
		fatal ("Could not access the termcap data base.\n");
	if (success == 0)
		fatal ("Terminal type `%s' is not defined.\n", termtype);
}