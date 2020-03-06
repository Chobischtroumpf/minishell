/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 14:54:16 by adorigo           #+#    #+#             */
/*   Updated: 2020/03/06 00:39:41 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		get_next_line(int fd, char **line)
{
	static char		buf[FOPEN_MAX][BUFFER_SIZE + 1];
	int				ret;
	int				i;

	if (BUFFER_SIZE < 1 || fd < 0 || fd >= FOPEN_MAX || !line
					|| !(*line = ft_strjoin_to_eol(NULL, buf[fd])))
		return (-1);
	ret = 1;
	while (ft_strchr_pos(buf[fd], '\n') == -1 && ret)
	{
		ret = read(fd, buf[fd], BUFFER_SIZE);
		if (ret == -1)
			return (-1);
		buf[fd][ret] = '\0';
		if (!(*line = ft_strjoin_to_eol(*line, buf[fd])))
			return (-1);
	}
	i = 0;
	ret = ft_strchr_pos(buf[fd], '\n') + 1;
	if (buf[fd][0] == 0)
		return (0);
	while (buf[fd][ret] != '\0' && ret)
		buf[fd][i++] = buf[fd][ret++];
	buf[fd][i] = '\0';
	return (1);
}