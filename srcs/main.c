/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpinheir <lpinheir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:39:59 by lpinheir          #+#    #+#             */
/*   Updated: 2022/02/03 14:05:54 by lpinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_command_path(char *command, char **envp);
void	write_to_file(char **command, char *file, char **envp);

int	main(int argc, char **argv, char **envp)
{
	char	**first_command;

	if (argc != 5)
	{
		printf("ERROR. Usage: ./pipex infile \"cmd -f\" \"cmd -f\" outfile \n");
		return (1);
	}
	// printf("%s\n", argv[1]);
	first_command = ft_split(argv[FIRSTCOMMANDWFLAGS], ' ');
	write_to_file(first_command, argv[OUTFILE], envp);
	return (0);
}

void	write_to_file(char **command, char *file_path, char **envp)
{
	char	*path;
	int		file;

	path = find_command_path(command[0], envp);
	file = open(file_path, O_WRONLY | O_CREAT, 0777);
	if (path == NULL || file == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	dup2(file, STDOUT_FILENO);
	close(file);
	execve(path, command, envp);
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
	return (NULL);
}
