/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpinheir <lpinheir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:39:59 by lpinheir          #+#    #+#             */
/*   Updated: 2022/02/17 19:49:41 by lpinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	char	**first_command;
	char	**second_command;
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
	first_command = ft_split(argv[FIRSTCOMMANDWFLAGS], ' ');
	second_command = ft_split(argv[SECONDCOMMANDWFLAGS], ' ');
	if (child_pid == 0)
		child_and_read_file(first_command, argv[INFILE], envp, fd);
	waitpid(child_pid, NULL, 0);
	parent_and_write_to_file(second_command, argv[OUTFILE], envp, fd);
	return (0);
}

void	child_and_read_file(char **command, char *file_path,
	char **envp, int *fd)
{
	char	*cmd_path;
	int		file;

	file = open(file_path, O_RDONLY, 0777);
	if (file == -1)
		ft_error(1, "Error");
	dup2(fd[1], STDOUT_FILENO);
	dup2(file, STDIN_FILENO);
	close(fd[0]);
	cmd_path = find_command_path(command[0], envp);
	if (cmd_path == NULL)
		ft_error(127, "Error: command not found");
	if (execve(cmd_path, command, envp) == -1)
		ft_error(1, "Error");
}

void	parent_and_write_to_file(char **command, char *file_path,
	char **envp, int *fd)
{
	char	*cmd_path;
	int		file;

	file = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file == -1)
		ft_error(1, "Error");
	dup2(fd[0], STDIN_FILENO);
	dup2(file, STDOUT_FILENO);
	close(fd[1]);
	cmd_path = find_command_path(command[0], envp);
	if (cmd_path == NULL)
		ft_error(127, "Error: command not found");
	if (execve(cmd_path, command, envp) == -1)
		ft_error(1, "Error");
}

char	*find_command_path(char *original_command, char **envp)
{
	char	**all_paths;
	char	*correct_path;
	char	*temp_path;
	int		i;

	if (char_in_str(original_command, '/') == 1)
		if (access(original_command, F_OK), F_OK == 0)
			return (original_command);
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
