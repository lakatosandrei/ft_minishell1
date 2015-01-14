/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakatos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/14 21:13:06 by alakatos          #+#    #+#             */
/*   Updated: 2015/01/13 19:14:30 by alakatos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_newunset(char ***envp, char ***nenvp, char **command)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while ((*envp)[i])
	{
		if (ft_strstr((*envp)[i], command[1]) == 0)
			(*nenvp)[j++] = (*envp)[i];
		i++;
	}
}

char	**ft_unsetenv(char ***envp, char **command)
{
	int		i[2];
	char	*aux;
	char	**nenvp;

	if (command[1])
	{
		aux = command[1];
		command[1] = ft_strjoin(command[1], "=");
		free(aux);
		i[0] = 0;
		while (command[i[0]])
			i[0]++;
		if (i[0] != 2)
			return (*envp);
		i[0] = 0;
		while ((*envp)[i[0]])
			i[0]++;
		nenvp = (char **)ft_memalloc(sizeof(char *) * (i[0] + 1));
		ft_newunset(envp, &nenvp, command);
		return (nenvp);
	}
	return (*envp);
}

void	ft_newenv(char ***nenvp, char ***envp, char **command)
{
	int			i;
	int			e;

	i = 0;
	e = 0;
	while ((*envp)[i])
	{
		if (ft_strstr((*envp)[i], command[1]))
		{
			(*nenvp)[i] = ft_strjoin(command[1], command[2]);
			e = 1;
		}
		else
			(*nenvp)[i] = (*envp)[i];
		i++;
	}
	if (e == 0)
		(*nenvp)[i] = ft_strjoin(command[1], command[2]);

}

char	**ft_setenv(char ***envp, char **command)
{
	int		i;
//	char	*aux;
	char	**nenvp;

	nenvp = 0;
	if (command[1])
	{
//		aux = command[1];
		command[1] = ft_strjoin(command[1], "=");
//		free(aux);
		i = 0;
		while (command[i])
			i++;
		if (i != 3)
			return (*envp);
		i = 0;
		while ((*envp)[i])
			i++;
		nenvp = (char **)ft_memalloc(sizeof(char *) * (i + 1));
		ft_newenv(&nenvp, envp, command);
		return (nenvp);
	}
	return (*envp);
}
