
#include "short_get_next_line.h"

int			get_next_line(char **line)
{
	char	buff;
	int		count_byte;
	int		count;
	long	counter;
	char	*result;
	if (!line)
		return (-1);
	*line = malloc(1);
	(*line)[0] = '\0';
	count = 0;
	while ((count_byte = read(0, &buff, 1)) > 0)
	{
		if (buff == '\n')
			return (1);
		counter = 0;
		result = (char *)malloc(count + 2);
		while ((*line)[counter])
		{
			result[counter] = (*line)[counter];
			counter++;
		}
		free(*line);
		*line = result;
		(*line)[count++] = buff;
		(*line)[count] = '\0';
	}
	if (count_byte < 0)
		free(*line);
	return (count_byte);
}
