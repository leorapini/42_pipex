/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpinheir <lpinheir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:39:59 by lpinheir          #+#    #+#             */
/*   Updated: 2022/02/02 21:27:59 by lpinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"
#include "pipex.h"

int	shell(void);
char	*find_command_path(char *command, char **envp);

int	main(int argc, char **argv, char **envp)
{
	char **command;
	char *path;
	
	printf("argc = %d\n", argc);
	if (argc != 2)
	{
		printf("Too many commands. Usage: ./pipex command\n");
		return (1);
	}
	command = ft_split(argv[1], ' ');
	path = find_command_path(command[CMD], envp);
	printf("cmd: %s\n", command[CMD]);
	printf("flags: %s\n", command[FLAG]);
	printf("path: %s\n", path);
	execve(path, command, envp);
	return (0);
}


char	*find_command_path(char *original_command, char **envp) 
{
	char	**all_paths;
	char	*correct_path;
	char	*temp_path;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	all_paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (all_paths[i])
	{
		temp_path = ft_strjoin(all_paths[i], "/");
		correct_path = ft_strjoin(temp_path, original_command);
		free(temp_path);
		if (access(correct_path, F_OK) == 0)
			return (correct_path);
		i++;
	}
	return NULL;
}

int	shell(void)
{
	char *args[] = {"/bin/ls", "-la", NULL};
	char *env[] = { NULL };
	
	printf("Running shell");
	execve("/bin/ls", args, env);
	perror("execve");
	exit(1);
}
