/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 17:45:57 by alessandro        #+#    #+#             */
/*   Updated: 2019/12/05 17:47:21 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

typedef struct	s_pl
{
	int			f_minus;
	int			f_zpad;
	int			f_dot;
	int			min_w;
	int			precise;
	char		convert;
}				t_pl;

int				ft_printf(const char *form, ...);
int				check_form(char *f);
int				check_minus(char c);
int				check_conversion(char c);
int				make_pl(t_pl *pl, char *form, va_list *ap);
int				print_and_count(t_pl pl, va_list *ap);
int				print_c(t_pl pl, va_list *ap);
int				print_s(t_pl pl, va_list *ap);
int				print_p(t_pl pl, va_list *ap);
int				print_d(t_pl pl, va_list *ap);
int				print_u(t_pl pl, va_list *ap);
int				print_x(t_pl pl, va_list *ap);
int				print_percent(t_pl pl, va_list *ap);
int				get_p_len(int len, t_pl pl);
char			*sp_malloc(int size);
void			free_all(void *ptr);

#endif
