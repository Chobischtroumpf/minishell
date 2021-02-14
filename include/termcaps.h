/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 13:14:16 by adorigo           #+#    #+#             */
/*   Updated: 2021/02/14 15:12:26 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCAPS_H
# define TERMCAPS_H

# include "minishell.h"

# ifdef __unix__
	static char term_buffer[2048];
#  elif __APPLE__
	static char term_buffer[2048];
#  else
# define term_buffer[0];
# endif

typedef struct	s_termcaps
{
	char	*buffer;
	char	*cl_string;
	char	*cm_string;
	char	PC;
	char	*BC;
	char	*UP;
	int		height;
	int		width;
	int		auto_wrap;
	
}				t_termcaps;

t_termcaps	*get_termcaps(void);
void		ft_init_terminal_data(void);
void		ft_interrogating_terminal(void);

#endif