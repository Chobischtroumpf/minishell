/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:02:19 by alessandro        #+#    #+#             */
/*   Updated: 2020/11/07 16:47:16 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_bracket_removal(t_cmd **cmd)
{
	char	**new_argv;
	char	*tmp;
	char	*tmp2;
	int		i;
	int		j;

	i = 0;
	while((*cmd)->argv[i])
		i++;
	if (!(new_argv = malloc(sizeof(char *) * i + 1)))
		return(-1);
	i = 0;
	while((*cmd)->argv[i])
	{
		j = 0;
		while((*cmd)->argv[i][j])
		{
			if ((*cmd)->argv[i][j] == '\"' || (*cmd)->argv[i][j] == '\'')
			{
				if (!tmp)
					tmp = ft_strndup((*cmd)->argv[i], j - 1);
				else
				{
					j = ft_brackets((*cmd)->argv[i], j);
					tmp2 = ft_substr((*cmd)->argv[i], j - (ft_strlen((*cmd)->argv[i]) - j), ft_strlen((*cmd)->argv[i]) - j);
					if (!(tmp = (char *)ft_realloc(tmp, sizeof(char) *
						(ft_strlen(tmp) + ft_strlen(tmp2)))))
						return (-1);
					tmp = ft_strcat(tmp, tmp2);
					// free(tmp2);
				}
			}
			else if (!new_argv[i] && (*cmd)->argv[i][j + 1] == '\0')
			{
				if (!(tmp = ft_strdup((*cmd)->argv[i])))
					return (-1);
			}
			j++;
		}
		new_argv[i] = tmp;
		// free(tmp);
		i++;
	}
	new_argv[i] = NULL;
	ft_free_array((*cmd)->argv);
	(*cmd)->argv = new_argv;
	return (1);
}