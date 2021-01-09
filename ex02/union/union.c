
#include <unistd.h>

int ft_check(char *s, int i, char c)
{
	int j;

	j = 0;
	while(j < i)
	{
		if(s[j] == c)
			return (0);
		j++;
	}
	return (1);
}

void ft_union(char *s1, char *s2)
{
	int i;
	int j;

	i = 0;
	while (s1[i])
	{
		if(ft_check(s1, i, s1[i]))
			write(1, &s1[i], 1);
		i++;
	}
	j = 0;
	while (s2[j])
	{
		if(ft_check(s2, j, s2[j]) && ft_check(s1, i, s2[j]))
			write(1, &s2[j], 1);
		j++;
	}
}

int main(int argc, char **argv)
{
	if(argc == 3)
		ft_union(argv[1], argv[2]);
	write(1, "\n", 1);
	return (0);
}