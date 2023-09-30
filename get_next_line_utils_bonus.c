#include "get_next_line_bonus.h"

// Already in Libft

unsigned int	ft_strlen(char *str)
{
	const char *ptr;

	ptr = str;
	while (*ptr)
	{
		ptr++;
	}
	return (unsigned int)(ptr - str);
}

void	*ft_memcpy(void *target, const void *source, size_t n)
{
	size_t	i;
	char	*ptr;
	char	*ptr2;

	ptr = target;
	ptr2 = (char *)source;
	i = -1;
	while (++i < n)
		*(ptr + i) = *(ptr2 + i);
	return (target);
}

char *ft_strcat(char *dest, const char *src)
{
    size_t dest_len = ft_strlen(dest);
    size_t src_len = ft_strlen(src);
    
    ft_memcpy(dest + dest_len, src, src_len + 1); // Copy including the null terminator
    
    return (dest);
}

static char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t len1;
	size_t len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);

	char *str = (char *)malloc(len1 + len2 + 1);

	if (!str)
		return (NULL);

	ft_strcat(str, s1);
	ft_strcat(str, s2);

	return (str);
}

static char	*ft_strdup(const char *s)
{
	size_t size = ft_strlen(s) + 1;
	char *dup = (char *)malloc(size);

	if (!dup)
		return (NULL);

	ft_memcpy(dup, s, size);
	return (dup);
}
