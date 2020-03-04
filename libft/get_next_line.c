/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 14:54:16 by adorigo           #+#    #+#             */
/*   Updated: 2020/01/21 07:48:39 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_strnewone(void)
{
	char *ret;

	if (!(ret = (char *)malloc(sizeof(char))))
		return (0);
	ret[0] = '\0';
	return (ret);
}

static int		extract(char **line, char **cache, int idx)
{
	char	*tmp;
	int		ret;

	if (idx >= 0)
	{
		if (!(*line = ft_substr(*cache, 0, idx)))
			return (ft_strfree(cache, -1));
		if (!(tmp = ft_substr(*cache, idx + 1, ft_strlen(*cache) - idx - 1)))
			return (ft_strfree(cache, -1));
		ret = 1;
	}
	else
	{
		if (!(*line = ft_substr(*cache, 0, ft_strlen(*cache))))
			return (ft_strfree(cache, -1));
		tmp = 0;
		ret = 0;
	}
	ft_strfree(cache, 0);
	*cache = tmp;
	return (ret);
}

int				get_next_line(int fd, char **line)
{
	ssize_t		r_size;
	char		buff[BUFFER_SIZE + 1];
	static char	*cache;
	char		*tmp;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (ft_strfree(&cache, -1));
	while ((r_size = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[r_size] = '\0';
		if (!(tmp = ft_strnjoin(cache, buff, r_size)))
			return (ft_strfree(&cache, -1));
		ft_strfree(&cache, 0);
		cache = tmp;
		if (ft_strnbr(cache) != -1)
			break ;
	}
	if (r_size < 0)
		return (ft_strfree(&cache, -1));
	if (r_size == 0 && (!cache || *cache == '\0')
		&& (*line = ft_strnewone()))
		return (ft_strfree(&cache, 0));
	return (extract(line, &cache, ft_strnbr(cache)));
}
