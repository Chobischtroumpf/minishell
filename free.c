/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 14:30:13 by adorigo           #+#    #+#             */
/*   Updated: 2020/03/14 12:03:29 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_free_all()
{
	int i;
	t_minishell *minishell;
	
	minishell = get_minishell();
	i = 0;
	while (minishell->tokens[i] && (ft_strfree(&(minishell->tokens[i]), 1)))
		i++;
}