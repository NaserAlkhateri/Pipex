/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 11:15:49 by student          #+#    #+#             */
/*   Updated: 2024/02/11 12:51:01 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t		i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strdup(const char *s1)
{
	size_t		size;
	char		*duped;
	size_t		i;

	if (!s1 || !ft_strlen(s1))
		return (NULL);
	i = 0;
	size = ft_strlen(s1);
	duped = (char *)malloc((size + 1) * sizeof(char));
	if (!duped)
		return (NULL);
	while (s1[i] != '\0')
	{
		duped[i] = s1[i];
		i++;
	}
	duped[i] = '\0';
	return (duped);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
	{
		len++;
	}
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	joined = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!joined)
		return (NULL);
	while (*s1)
		joined[i++] = *s1++;
	while (*s2)
		joined[i++] = *s2++;
	joined[i] = '\0';
	return (joined);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
	{
		while (*s)
		{
			write(fd, s, 1);
			s++;
		}
	}
}
