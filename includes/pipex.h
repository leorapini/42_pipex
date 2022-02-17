/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpinheir <lpinheir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 20:58:55 by lpinheir          #+#    #+#             */
/*   Updated: 2022/02/17 10:14:43 by lpinheir         ###   ########.fr       */
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
void	parent_and_write_to_file(char **command, char *file,
			char **envp, int *fd);
void	child_and_read_file(char **command, char *file_path,
			char **envp, int *fd);
void	ft_error_message(char *message);
void	ft_error_command(void);
int		char_in_str(char *str, char c);
void	ft_error(int exit_code, char *message);

#endif