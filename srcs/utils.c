/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 18:09:34 by adorigo           #+#    #+#             */
/*   Updated: 2020/11/04 17:22:46 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Joins *char 's1' and *char 's2' with a character 'del' between the two.
*/

char			*ft_strjoin_delimiter(char *s1, char *s2, char del)
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

int				ft_count_arg(char **arg)
{
	int		i;

	i = 0;
	while (arg[i])
		i++;
	return (i);
}

t_cmd			*ft_last_cmd(t_cmd *cmd)
{
	t_cmd	*last;

	last = cmd;
	while (last->next)
		last = last->next;
	return (last);
}


static int		checker(const char **str)
{
	int is_negative;

	is_negative = 0;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			is_negative = 1;
		(*str)++;
	}
	return (is_negative);
}

unsigned int	ft_atoi_pos(const char *str)
{
	unsigned long long	nb;
	int					i;
	int					is_negative;

	if ((is_negative = checker(&str)) == 1)
		return (-1);
	i = 0;
	nb = 0;
	if (ft_strlen(str) > 19)
		return(0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (nb >= (unsigned long long)INT_MAX - 1 &&
			nb <= (unsigned long long)LONG_MAX)
			return (-1);
		if (nb > (unsigned long long)LONG_MAX)
			return (0);
		nb *= 10;
		nb += str[i] - '0';
		i++;
	}
	return(nb);	
}
