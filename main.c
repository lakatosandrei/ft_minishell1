/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakatos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/14 20:38:50 by alakatos          #+#    #+#             */
/*   Updated: 2015/01/13 19:06:09 by alakatos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	**ft_getpath(char **envp)
{
	char	**folders;
	int		i;

	while (*envp)
	{
		if (ft_strstr(*envp, "PATH="))
			break ;
		envp++;
	}
	folders = ft_strsplit(ft_strstr(*envp, "PATH=") + 5, ':');
	i = 0;
	while (folders[i])
	{
		folders[i] = ft_strjoin(folders[i], "/");
		i++;
	}
	return (folders);
}

char	*ft_findexec(char **paths, char *command)
{
	if (command[0] != '.' && command[0] != '/' && command[0] != '~')
	{
		while (*paths)
		{
			if (access(ft_strjoin(*paths, command), R_OK) == 0)
				return (*paths);
			paths++;
		}
	}
	return (0);
}

char	*ft_gethome(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strstr("HOME=", envp[i]) == 0)
			return (envp[i + 3] + 5);
		i++;
	}
	return (0);
}

void	ft_cd(char **command, char **envp)
{
	struct stat	fst;

	if (command[1] && stat(command[1], &fst))
		ft_putendl_fd(ft_strjoin("cd: No such file or directory: ",
			command[1]), 2);
	else if (!(S_ISDIR(fst.st_mode)) && command[1])
		ft_putendl_fd(ft_strjoin("cd: Not a directory: ",
			command[1]), 2);
	else if (access(command[1], X_OK) == -1 && command[1])
		ft_putendl_fd(ft_strjoin("cd: Permission Denied: ", command[1]), 2);
	else if (command[1] == 0)
		chdir(ft_gethome(envp));
	else
		chdir(command[1]);
}

int		main(int ac, char **av, char **envp)
{
	char	**test;

	(void)ac;
	(void)av;
	while (42)
	{
		ft_putstr_fd("$> ", 1);
		test = ft_readinput();
		if (test[0] && ft_strcmp(test[0], "exit") == 0)
			exit(0);
		else if (test[0] && ft_strcmp(test[0], "setenv") == 0)
			envp = ft_setenv(&envp, test);
		else if (test[0] && ft_strcmp(test[0], "unsetenv") == 0)
			envp = ft_unsetenv(&envp, test);
		else if (test[0] && ft_strcmp(test[0], "cd") == 0)
			ft_cd(test, envp);
		else
			ft_getcommand(envp, test);
	}
	return (0);
}
