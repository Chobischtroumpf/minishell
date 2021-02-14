/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 13:22:43 by adorigo           #+#    #+#             */
/*   Updated: 2021/02/14 15:13:34 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_terminal_data(void)
{
	char *termtype;
	int success;

	termtype = ft_find_by_key2("TERM");
	if (termtype == 0)
		ft_exit_error("could not get terminal type, set it with the TERM variable");
	success = tgetent (term_buffer, termtype);
	if (success < 0)
		ft_exit_error("Could not access the termcap data base.\n");
	if (success == 0)
	{
		ft_printf("Terminal type `%s' is not defined.\n", termtype);
		ft_exit_error(NULL);
	}
}

void	ft_interrogating_terminal(void)
{
	t_termcaps	*struct_term;
	char		*tmp;

	struct_term = get_termcaps();
#ifdef __unix__
	struct_term->buffer = (char *)malloc(ft_strlen(term_buffer));
#elif __APPLE__
	struct_term->buffer = (char *)malloc(ft_strlen(term_buffer));
#else
	struct_term->buffer = NULL;
#endif
	struct_term->cl_string = tgetstr("cl", &struct_term->buffer);
	if (!(struct_term->cm_string = tgetstr("cm", &struct_term->buffer)))
		ft_exit_error("cm string not defined, terminal will not operate\n");
	struct_term->auto_wrap = tgetflag("am");
	struct_term->height = tgetnum("li");
	struct_term->width = tgetnum("co");
	tmp = tgetstr("pc", &struct_term->buffer);
	struct_term->PC = tmp ? *tmp : 0;
	struct_term->BC = tgetstr("le", &struct_term->buffer);
	struct_term->UP = tgetstr("up", &struct_term->buffer);
}