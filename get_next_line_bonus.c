#include "get_next_line_bonus.h"

static t_fd_data *fd_data_list = NULL;

static t_fd_data *get_fd_data(int fd)
{
    t_fd_data *current = fd_data_list;
    while (current)
    {
        if (current->fd == fd)
            return (current);
        current = current->next;
    }
    return (NULL);
}

static t_fd_data *create_fd_data(int fd)
{
    t_fd_data *new_fd_data = (t_fd_data *)malloc(sizeof(t_fd_data));
    if (!new_fd_data)
        return (NULL);
    new_fd_data->fd = fd;
    new_fd_data->left_str = NULL;
    new_fd_data->next = NULL;
    return (new_fd_data);
}

static int ft_read(int fd, char **line_buffer, char *buffer)
{
    int bytes_read = read(fd, buffer, BUFFER_SIZE);
    if (bytes_read > 0)
    {
        buffer[bytes_read] = '\0';
        *line_buffer = ft_strjoin(*line_buffer, buffer);
    }
    return (bytes_read);
}

char *get_next_line(int fd)
{
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);

    t_fd_data *fd_data = get_fd_data(fd);
    if (!fd_data)
    {
        fd_data = create_fd_data(fd);
        if (!fd_data)
            return (NULL);
        fd_data->next = fd_data_list;
        fd_data_list = fd_data;
    }

    int bytes_read = ft_read(fd, &(fd_data->left_str), (char *)malloc((BUFFER_SIZE + 1) * sizeof(char)));
    if (bytes_read <= 0)
    {
        if (bytes_read == 0 && fd_data->left_str && fd_data->left_str[0])
        {
            char *line = fd_data->left_str;
            fd_data->left_str = NULL;
            return (line);
        }
        return (NULL);
    }

    char *line = ft_strjoin(fd_data->left_str, "");
    free(fd_data->left_str);
    fd_data->left_str = NULL;
    return (line);
}
