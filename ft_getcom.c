/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getcom.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakatos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/14 21:16:00 by alakatos          #+#    #+#             */
/*   Updated: 2015/01/13 19:14:28 by alakatos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	**ft_readinput(void)
{
	char	*command;
	char	**args;
	int		i;

	args = 0;
	get_next_line(0, &command);
	ft_replace(&command);
	args = ft_strsplit(command, 5);
	i = 0;
	while (args && args[i])
	{
		if (args[i][0] == '\'' || args[i][0] == '"')
		{
			args[i] = args[i] + 1;
			if (args[i][ft_strlen(args[i]) - 1] == '\'' ||
					args[i][ft_strlen(args[i]) - 1] == '"')
				args[i][ft_strlen(args[i]) - 1] = 0;
		}
		i++;
	}
	return (args);
}

void	ft_getcommand(char **envp, char **test)
{
	char	*folder;
	pid_t	father;
	char	*error;

	error = ft_strdup("ft_minishell1: command not found: ");
	if (test[0])
	{
		father = fork();
		if (father > 0)
			wait(0);
		else
		{
			if ((folder = ft_findexec(ft_getpath(envp), test[0])))
				execve(ft_strjoin(folder, test[0]), test, envp);
			else if (access(test[0], R_OK) == 0)
				execve(test[0], test, envp);
			else
				ft_putendl_fd(ft_strjoin(error, test[0]), 2);
			exit(0);
		}
	}
}

void	ft_replace(char **line)
{
	int	i;
	int	bet;

	i = 0;
	bet = 0;
	while ((*line)[i] != 0)
	{
		if ((*line)[i] == ' ')
			(*line)[i] = 5;
		if ((*line)[i] == '\'' || (*line)[i] == '"')
			bet = (bet + 1) % 2;
		i++;
	}
}
