#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

typedef struct s_fd_data {
    int fd;
    char *left_str;
    struct s_fd_data *next;
} t_fd_data;


char *get_next_line(int fd);

// Utils
static t_fd_data *get_fd_data(int fd);
static t_fd_data *create_fd_data(int fd);
static int ft_read(int fd, char **line_buffer, char *buffer);

// Already in Libft

unsigned int	ft_strlen(char *str);
void	*ft_memcpy(void *target, const void *source, size_t n);
char	*ft_strcat(char *dest, const char *src);
static char	*ft_strjoin(const char *s1, const char *s2);
static char	*ft_strdup(const char *s);

#endif