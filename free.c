/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 14:30:13 by adorigo           #+#    #+#             */
/*   Updated: 2020/03/16 01:02:59 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_free_all()
{
	int i;
	char **tokens;

	tokens = get_minishell()->tokens;
	i = -1;
	while (tokens[++i])
	{
		free(tokens[i]);
		tokens[i] = 0;
	}
	if (tokens)
	{
		free (tokens);
		tokens = 0;
	}
	if (get_minishell()->line != NULL)
	{
		free(get_minishell()->line);
		get_minishell()->line = 0;
	}	
}