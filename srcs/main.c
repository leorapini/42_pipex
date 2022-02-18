/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpinheir <lpinheir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:39:59 by lpinheir          #+#    #+#             */
/*   Updated: 2022/02/18 19:06:04 by lpinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	int		pipe_success;
	pid_t	child_pid;

	if (argc != 5)
		ft_error(1, "Error. Usage: ./pipex infile \"cmd\" \"cmd\" outfile");
	pipe_success = pipe(fd);
	if (pipe_success == -1)
		ft_error(1, "Error");
	child_pid = fork();
	if (child_pid == -1)
		ft_error(1, "Error");
	if (child_pid == 0)
		child_and_read_file(argv[FIRSTCOMMANDWFLAGS], argv[INFILE], envp, fd);
	waitpid(child_pid, NULL, 0);
	parent_and_write_to_file(argv[SECONDCOMMANDWFLAGS],
		argv[OUTFILE], envp, fd);
	return (0);
}

void	child_and_read_file(char *original_command, char *file_path,
	char **envp, int *fd)
{
	char	*cmd_path;
	int		file;
	char	**command;

	file = open(file_path, O_RDONLY, 0777);
	if (file == -1)
		ft_error(1, "Error");
	dup2(fd[1], STDOUT_FILENO);
	dup2(file, STDIN_FILENO);
	close(fd[0]);
	command = ft_split(original_command, ' ');
	cmd_path = find_command_path(command[0], envp);
	if (cmd_path == NULL)
	{
		free_split(command);
		ft_error(127, "Error: command not found");
	}
	if (execve(cmd_path, command, envp) == -1)
	{
		free(cmd_path);
		free_split(command);
		ft_error(1, "Error");
	}
	free_split(command);
	free(cmd_path);
}

void	parent_and_write_to_file(char *original_command, char *file_path,
	char **envp, int *fd)
{
	char	*cmd_path;
	int		file;
	char	**command;

	file = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file == -1)
		ft_error(1, "Error");
	dup2(fd[0], STDIN_FILENO);
	dup2(file, STDOUT_FILENO);
	close(fd[1]);
	command = ft_split(original_command, ' ');
	cmd_path = find_command_path(command[0], envp);
	if (cmd_path == NULL)
	{
		free_split(command);
		ft_error(127, "Error: command not found");
	}
	if (execve(cmd_path, command, envp) == -1)
	{
		free(cmd_path);
		free_split(command);
		ft_error(1, "Error");
	}
	free_split(command);
	free(cmd_path);
}

static char	*path_finder(char **all_paths, char *original_command)
{
	char	*correct_path;
	char	*temp_path;
	int		i;

	i = 0;
	while (all_paths[i])
	{
		temp_path = ft_strjoin(all_paths[i], "/");
		correct_path = ft_strjoin(temp_path, original_command);
		free(temp_path);
		if (access(correct_path, F_OK) == 0)
			return (correct_path);
		else
			free(correct_path);
		i++;
	}
	return (NULL);
}

char	*find_command_path(char *original_command, char **envp)
{
	char	**all_paths;
	char	*correct_path;
	int		i;

	if (char_in_str(original_command, '/') == 1)
		if (access(original_command, F_OK), F_OK == 0)
			return (original_command);
	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	all_paths = ft_split(envp[i] + 5, ':');
	correct_path = path_finder(all_paths, original_command);
	if (correct_path != NULL)
	{
		free_split(all_paths);
		return (correct_path);
	}
	free_split(all_paths);
	return (NULL);
}
