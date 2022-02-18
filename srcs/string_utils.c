/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpinheir <lpinheir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 11:23:35 by lpinheir          #+#    #+#             */
/*   Updated: 2022/02/18 14:41:03 by lpinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s++ != 0)
		len++;
	return (len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	counter;

	if (!src)
		return (0);
	srclen = ft_strlen(src);
	if (dstsize == 0)
		return (srclen);
	counter = 0;
	while (*src != 0 && counter < (dstsize - 1))
	{
		*dst = *src;
		src++;
		dst++;
		counter++;
	}
	*dst = 0;
	return (srclen);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*buffer;
	int		length;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	length = ft_strlen(s1) + ft_strlen(s2);
	buffer = malloc(sizeof(*s1) * (length + 1));
	if (buffer == NULL)
		return (NULL);
	while (s1[i] != 0)
		buffer[j++] = s1[i++];
	i = 0;
	while (s2[i] != 0)
		buffer[j++] = s2[i++];
	buffer[j] = 0;
	return (buffer);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	n_len;

	n_len = ft_strlen(needle);
	if (*needle == 0)
		return ((char *)haystack);
	while (*haystack != 0 && len >= n_len)
	{
		if (ft_strncmp(haystack, needle, n_len) == 0)
			return ((char *)haystack);
		len--;
		haystack++;
	}
	return (NULL);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (n > 0)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		if (*s1 == '\0')
			return (0);
		s1++;
		s2++;
		n--;
	}
	return (0);
}
