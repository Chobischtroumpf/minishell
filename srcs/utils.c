/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 18:09:34 by adorigo           #+#    #+#             */
/*   Updated: 2020/11/05 18:47:13 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Joins *char 's1' and *char 's2' with a character 'del' between the two.
*/

char	*ft_strjoin_delimiter(char *s1, char *s2, char del)
{
	char	*str;
	char	*to_free;
	int		total;
	int		i;

	i = 0;
	to_free = s1;
	if (!s1 || !s2)
		return (NULL);
	total = ft_strlen(s1) + ft_strlen(s2) + 2;
	if (!(str = (char *)malloc(total * sizeof(char))))
		return (NULL);
	while (*s1)
		str[i++] = *s1++;
	str[i++] = del;
	while (*s2)
		str[i++] = *s2++;
	str[i] = '\0';
	return (str);
}

int		ft_count_arg(char **arg)
{
	int		i;

	i = 0;
	while (arg[i])
		i++;
	return (i);
}

t_cmd	*ft_last_cmd(t_cmd *cmd)
{
	t_cmd	*last;

	last = cmd;
	while (last->next)
		last = last->next;
	return (last);
}

int		ft_skip_quotes(char *str, int i)
{
	if (str[i] == '\'')
		while (str[i + 1] != '\'')
			i++;
	return (i + 1);
}
