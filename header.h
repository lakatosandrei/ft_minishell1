#ifndef HEADER_H
# define HEADER_H

# include "libft/libft.h"
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdlib.h>

int		get_next_line(int const fd, char **line);
void	ft_newenv(char ***nenvp, char ***envp, char **command);
char	**ft_unsetenv(char ***envp, char **command);
char	**ft_setenv(char ***envp, char **command);
char	**ft_readinput(void);
void	ft_getcommand(char **envp, char **test);
void	ft_replace(char **line);
char	*ft_findexec(char **paths, char *command);
char	**ft_getpath(char **envp);
typedef struct		s_env
{
	char		*name;
	char		*val;
	struct s_env	*next;
}			t_env;
#endif
