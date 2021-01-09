
#include <unistd.h>

int ft_check(char *s, int pos, char c)
{
	int i;

	i = 0;
	while(i < pos)
	{
		if(s[i] == c)
			return (0);
		i++;
	}
	return (1);
}
void ft_inter(char *s1, char *s2)
{
	int i;
	int j;

	i = 0;
	while(s1[i])
	{
		if(ft_check(s1, i, s1[i]))
		{
			j = 0;
			while(s2[j])
			{
				if (s1[i] == s2[j])
				{
					write(1, &s1[i], 1);
					break;
				}
				j++;
			}
		}
		i++;
	}
}

int main(int argc, char **argv)
{
	if(argc == 3)
		ft_inter(argv[1], argv[2]);
	write(1, &"\n", 1);
	return (0);
}