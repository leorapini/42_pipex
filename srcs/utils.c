/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpinheir <lpinheir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 09:30:47 by lpinheir          #+#    #+#             */
/*   Updated: 2022/02/17 08:18:13 by lpinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error_message(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void	ft_error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

void	ft_error_command(void)
{
	perror("Error: Command not found");
	exit(127);
}

int	char_in_str(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}