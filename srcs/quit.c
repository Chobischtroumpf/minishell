/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 15:07:26 by adorigo           #+#    #+#             */
/*   Updated: 2021/01/12 02:52:30 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_get_exit_code(int status, int excode)
{
	if (excode == -1)
	{
		if (WIFEXITED(status))
			get_minishell()->excode = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			get_minishell()->excode = 128 + WTERMSIG(status);
	}
	else
		get_minishell()->excode = excode;
	return (NULL);
}
