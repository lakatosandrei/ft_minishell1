#include <stdio.h>

char	**ft_strsplit(char const *s, char c);

int	main(int ac, char **av)
{
	char **test;

	printf("%d\n%s\n", ac, av[1]);
	test = ft_strsplit(""" -la""", ' ');
	while (*test)
	{
		printf("%s\n", *test);
		test++;
	}
	printf("%s\n", *test);
	return (0);
}
