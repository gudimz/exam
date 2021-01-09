
#include "my_get_next_line.h"

size_t ft_strlen(char *str)
{
	size_t len;

	len = 0;
	while(str[len])
	{
		len++;
	}
	return (len);
}

char *ft_strcpy(char *s1, char *s2)
{
	size_t i;

	i = 0;
	while(s2)
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

char *ft_strdup(char *str)
{
	char *s;
	size_t i;

	i = ft_strlen(str);
	if(!(s = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while(str[i])
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char *ft_strchr(char *str, char c)
{
	size_t i;

	i = 0;
	while(str[i] != c)
	{
		if(str[i] == '\0')
			return (NULL);
		i++;
	}
	return (&str[i]);
}

char *ft_strjoin(char *s1, char *s2)
{
	char *str;
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if(!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1) + ft_strlen(s2);
	if(!(str = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while(s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while(s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	free(s1);
	return (str);
}

int ft_check_buf(char *s_buf, char **line)
{
	char *n;

	if (!s_buf)
		*line = ft_strdup("");
	else
	{
		if((n = ft_strchr(s_buf, '\n')))
		{
			*n++ = '\0';
			*line = ft_strdup(s_buf);
			ft_strcpy(s_buf, n);
			return (0);
		}
		else
		{
			*line = ft_strdup(s_buf);
			free(s_buf);
		}
	}
	return(1);
}

int get_next_line(char ** line)
{
	static char *s_buf;
	char buffer[BUFFER_SIZE + 1];
	int flag;
	int ret;

	if (!line || BUFFER_SIZE < 0)
		return (-1);
	flag = ft_check_buf(s_buf, line);
	if (flag)
		s_buf = NULL;
	while(flag && (ret = read(0, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		if ((s_buf = ft_strchr(buffer, '\n')))
		{
			*s_buf++ = '\0';
			if(!(s_buf = ft_strdup(s_buf)))
				return (-1);
			flag = 0;
		}
		if (!(*line = ft_strjoin(*line, buffer)))
			return (-1);
	}
	if (ret < BUFFER_SIZE && !s_buf && ret != -1)
		return (0);
	if (ret == -1)
	{
		free(*line);
		return (-1);
	}
	return (1);
}

int main(void)
{
	int		r;
	char	*line;

	line = NULL;
	while ((r = get_next_line(&line)) > 0)
	{
		printf("%s\n", line);
		free(line);
		line = NULL;
	}
	printf("%s", line);
	free(line);
	line = NULL;
	return (0);
}
