#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h> // tool for controlling files and file descriptors, essential for working with files

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);

// Utils
static void	ft_free(char **str);
static int	ft_read(int fd, char **line_buffer, char *buffer);

// Already in Libft
unsigned int	ft_strlen(char *str);
void	*ft_memcpy(void *target, const void *source, size_t n);
char*	ft_strcat(char *dest, const char *src);
static char	*ft_strjoin(const char *s1, const char *s2);
static char	*ft_strdup(const char *s);

#endif