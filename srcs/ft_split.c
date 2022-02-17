/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpinheir <lpinheir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 20:04:50 by lpinheir          #+#    #+#             */
/*   Updated: 2022/02/17 11:41:00 by lpinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	ft_words(char const *s, char c)
{
	size_t	count;
	size_t	flag;

	flag = 0;
	count = 0;
	while (*s != 0)
	{
		if (*s != c && flag == 0)
		{
			flag = 1;
			count++;
		}
		else if (*s == c)
			flag = 0;
		s++;
	}
	return (count);
}

static char const	*ft_isc(char const *s, char c, size_t *len_str)
{
	while (*s == c && *s != 0)
		s++;
	while (*s != c && *s != 0)
	{
		(*len_str)++;
		s++;
	}
	return (s);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	len_str;
	size_t	j;
	size_t	count;

	if (!s)
		return (NULL);
	count = ft_words(s, c);
	result = malloc(sizeof(char *) * count + 1);
	if (!result)
		return (NULL);
	j = 0;
	while (j < count)
	{
		len_str = 0;
		s = ft_isc(s, c, &len_str);
		result[j] = (char *)malloc(sizeof(char) * (len_str + 1));
		ft_strlcpy(result[j++], s - len_str, len_str + 1);
	}
	result[j] = NULL;
	return (result);
}
