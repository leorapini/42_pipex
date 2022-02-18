/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpinheir <lpinheir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 20:04:50 by lpinheir          #+#    #+#             */
/*   Updated: 2022/02/18 19:06:38 by lpinheir         ###   ########.fr       */
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

static size_t	ft_quotes(char const *s)
{
	size_t	count;

	count = 0;
	while (*s != 0)
	{
		if (*s == '\'')
			count++;
		s++;
	}
	return (count / 2);
}

static char const	*ft_isc(char const *s, char c, size_t *len_str)
{
	while (*s == c && *s != 0)
		s++;
	while (*s != c && *s != 0 && *s != '\'')
	{
		(*len_str)++;
		s++;
	}
	if (*s == '\'')
	{
		s++;
		while (*s != 0 && *s != '\'')
		{
			(*len_str)++;
			s++;
		}
	}
	return (s);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	len_str;
	size_t	j;
	size_t	count;
	size_t	quotes;

	if (!s)
		return (NULL);
	count = ft_words(s, c);
	quotes = ft_quotes(s);
	count = count - quotes;
	result = malloc(sizeof(*result) * (count + 1));
	if (!result)
		return (NULL);
	j = 0;
	while (j < count)
	{
		len_str = 0;
		s = ft_isc(s, c, &len_str);
		result[j] = (char *)malloc(sizeof(char *) * (len_str + 1));
		ft_strlcpy(result[j++], s - len_str, len_str + 1);
	}
	result[j] = NULL;
	return (result);
}
