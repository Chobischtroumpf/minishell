/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 18:09:34 by adorigo           #+#    #+#             */
/*   Updated: 2021/02/14 14:13:56 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_count_arg(char **arg)
{
	int i;

	i = 0;
	while (arg[i])
		i++;
	return (i);
}

int		ft_isascii_except(int c)
{
	if (c >= ' ' && c <= '~' && c != '$' && c != '"' && c != '\\')
		return (0);
	return (1);
}

char	*remove_char(char *str, char c)
{
	char	*new;
	int		i;
	int		j;
	int		l;

	if (!(new = ft_strnew(ft_strlen(str))))
		ft_exit_error(NULL);
	i = 0;
	j = 0;
	l = ft_strlen(str);
	while (i < l)
	{
		if (str[i] != c)
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	return (new);
}

int		free_str_ret(char *str, int ret)
{
	free(str);
	return (ret);
}

/*
**	Ft_append_env receives a keyvalue pair,retrieves the corresponding node
**	from the env_list and appends the 'value' string.
*/

void	ft_append_env(char **keyvalue)
{
	t_env	*tmp;
	char	*new;

	tmp = ft_find_by_key(keyvalue[0]);
	if (!(new = (char *)malloc(ft_strlen(tmp->value) + \
								ft_strlen(keyvalue[1] + 1))))
		ft_exit_error(NULL);
	if (!(tmp->value = ft_strjoin_free(tmp->value, keyvalue[1])))
		ft_exit_error(NULL);
}
