/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpinheir <lpinheir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 20:58:55 by lpinheir          #+#    #+#             */
/*   Updated: 2022/02/17 08:12:55 by lpinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* DEFINES */
# define INFILE 1
# define FIRSTCOMMANDWFLAGS 2
# define SECONDCOMMANDWFLAGS 3
# define OUTFILE 4

/* LIBRARIES */
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include "libft.h"

/* FUNCTIONS */
char	*find_command_path(char *command, char **envp);
void	write_to_file(char **command, char *file, char **envp, int *fd);
void	read_file(char **command, char *file, char **envp, int *fd);
void    ft_error_message(char *message);
void    ft_error(void);
void	ft_error_command(void);
int	    char_in_str(char *str, char c);

#endif