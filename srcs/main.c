/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpinheir <lpinheir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:39:59 by lpinheir          #+#    #+#             */
/*   Updated: 2022/02/09 08:46:25 by lpinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *find_command_path(char *command, char **envp);
void write_to_file(char **command, char *file, char **envp, int *fd);
void read_file(char **command, char *file, char **envp, int *fd);

int main(int argc, char **argv, char **envp)
{
	int fd[2];
	char **first_command;
	char **second_command;
	int pipe_success;
	pid_t child_pid;

	if (argc != 5)
	{
		printf("ERROR. Usage: ./pipex infile \"cmd -f\" \"cmd -f\" outfile\n");
		return (1);
	}
	pipe_success = pipe(fd);
	if (pipe_success == -1)
	{
		printf("ERROR. Pipe failure\n");
		return (1);
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		printf("ERROR. Pid failure\n");
		return (1);
	}
	first_command = ft_split(argv[FIRSTCOMMANDWFLAGS], ' ');
	second_command = ft_split(argv[SECONDCOMMANDWFLAGS], ' ');
	if (child_pid == 0)
		read_file(first_command, argv[INFILE], envp, fd);
	waitpid(child_pid, NULL, 0);
	write_to_file(second_command, argv[OUTFILE], envp, fd);
	return (0);
}

void read_file(char **command, char *file_path, char **envp, int *fd)
{
	char *path;
	int file;

	path = find_command_path(command[0], envp);
	file = open(file_path, O_RDONLY, 0777);
	if (path == NULL || file == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	dup2(fd[1], STDOUT_FILENO);
	dup2(file, STDIN_FILENO);
	close(fd[0]);
	execve(path, command, envp);
}

void write_to_file(char **command, char *file_path, char **envp, int *fd)
{
	char *path;
	int file;

	path = find_command_path(command[0], envp);
	file = open(file_path, O_WRONLY | O_CREAT, 0777);
	if (path == NULL || file == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(file, STDOUT_FILENO);
	close(fd[1]);
	execve(path, command, envp);
}

char *find_command_path(char *original_command, char **envp)
{
	char **all_paths;
	char *correct_path;
	char *temp_path;
	int i;

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
