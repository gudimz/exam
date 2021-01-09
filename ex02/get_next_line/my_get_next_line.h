
#ifndef MY_GET_NEXT_LINE_H
# define MY_GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

int get_next_line(char **line);
#endif
