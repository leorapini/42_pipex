/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpinheir <lpinheir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 20:58:55 by lpinheir          #+#    #+#             */
/*   Updated: 2022/02/17 12:02:52 by lpinheir         ###   ########.fr       */
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
# include <fcntl.h>
# include <sys/wait.h>

/* FUNCTIONS */
char	*find_command_path(char *command, char **envp);
void	parent_and_write_to_file(char **command, char *file,
			char **envp, int *fd);
void	child_and_read_file(char **command, char *file_path,
			char **envp, int *fd);
int		char_in_str(char *str, char c);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
void	ft_error(int exit_code, char *message);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif