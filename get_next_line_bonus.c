/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikalakhi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 20:30:57 by ikalakhi          #+#    #+#             */
/*   Updated: 2022/04/02 20:31:03 by ikalakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

char	*ft_copy(char *s)
{
	char	*ret;
	int		i;

	i = 0;
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	if (s[i] == '\n')
		i++;
	ret = malloc (sizeof (char) * (i + 1));
	if (!ret)
	{
		free (s);
		return (NULL);
	}
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		ret[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
		ret [i++] = '\n';
	ret[i] = '\0';
	return (ret);
}

char	*ft_save(char *p, int i)
{
	char	*save;
	int		j;

	save = malloc(sizeof(char) * ft_strlen(p + i) + 1);
	if (!save)
	{
		free (p);
		return (NULL);
	}
	j = 0;
	while (p[i] != '\0')
		save[j++] = p[i++];
	free(p);
	save[j] = '\0';
	return (save);
}

char	*ft_cut(char *p)
{
	int		i;

	i = 0;
	if (!p)
		return (NULL);
	while (p[i] != '\n' && p[i] != '\0')
		i++;
	if (p[i] != '\n')
	{
		free (p);
		return (NULL);
	}
	if (p[i] == '\n')
		i++;
	return (ft_save(p, i));
}

char	*save_read(int fd, char *save, int rd)
{
	char	*buf;

	buf = malloc (sizeof (char) * BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while (!ft_strchr(save, '\n') && rd != 0)
	{
		rd = read (fd, buf, BUFFER_SIZE);
		if (rd == -1)
		{
			free (buf);
			return (NULL);
		}
		buf[rd] = '\0';
		save = ft_strjoin(save, buf);
	}
	if (rd == 0 && save && save[0] == '\0')
	{
		free(save);
		save = NULL;
	}
	free(buf);
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save[OPEN_MAX];
	char		*line;
	int			rd;

	rd = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= OPEN_MAX)
		return (NULL);
	save[fd] = save_read(fd, save[fd], rd);
	if (!save[fd])
		return (NULL);
	line = ft_copy(save[fd]);
	if (!line || !ft_strlen(line))
	{
		free(save[fd]);
		free (line);
		return (NULL);
	}
	save[fd] = ft_cut(save[fd]);
	return (line);
}
