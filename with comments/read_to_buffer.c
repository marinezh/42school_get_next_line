#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>



void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (i < n)
	{
		d[i] = s[i];
		// Debug: Show each byte being copiedprintf("ft_memcpy: 
		//copying byte %zu: %c\n", i, s[i]); // Debug: Show each byte being copied
		//printf("ft_memcpy: copying byte %zu: %c\n", i, s[i]); 
		i++;
	}
	return (dest);
}
char	*find_newline(const char *str)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == '\n')
		{
			// Debug: Show where the newline is found
			// printf("find_newline: found newline at position %ld\n", str - str);
			return ((char *)str); // return pointer to the newline
		}
			
		str++;
	}
	return (NULL);
}
char	*str_join(char *s1, const char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*result;

	s1_len = 0;
	s2_len = 0;
	while (s1 && s1[s1_len])
		s1_len++;
	while (s2[s2_len])
		s2_len++;
		// Debug: Print the lengths of s1 and s2
	//printf("str_join: s1_len=%zu, s2_len=%zu\n", s1_len, s2_len);
	result = malloc(s1_len + s2_len + 1);
	if (!result)
		return (NULL);
	if (s1)
	{
		ft_memcpy(result, s1, s1_len); // Copy s1 into result
		//printf("str_join: copied s1='%s'\n", s1);
	}
		
	ft_memcpy(result + s1_len, s2, s2_len + 1); // Copy s2 (including null terminator)
	//printf("str_join: copied s2='%s', result='%s'\n", s2, result);

	free(s1);
	return (result);
}

char	*read_to_buffer(int fd, char *buffer)
{
	char	*temp_buffer;
	int	bytes_read;

	temp_buffer = malloc(BUFFER_SIZE + 1);
	if (!temp_buffer)
		return (free(buffer), NULL);
	bytes_read = 1;
	printf("start reading data from the file\n"); 
	while (!find_newline(buffer) && bytes_read > 0) // read untill new line is found
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes_read <= 0) // if reading ends or error accure leave the cycle
			break ;
		temp_buffer[bytes_read] = '\0';
		printf("read %d bite: '%s'\n", bytes_read, temp_buffer);
		buffer = str_join(buffer, temp_buffer);
		if (!buffer)
			break ;
		printf("new buffer: '%s'\n", buffer);
	}
	free(temp_buffer);
	if (bytes_read < 0 || !buffer)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}


int main(void)
{
  
    int fd = open("text.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("error");
        return (1);
    }


    char *buffer = NULL;

    buffer = read_to_buffer(fd, buffer);

   
    if (!buffer)
    {
        printf("error while reading file\n");
    }
    else
    {
        printf("result of file reading:\n%s\n", buffer);
        free(buffer); 
    }


    close(fd);
    return (0);
}