/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:39:47 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/01/16 15:36:36 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif 

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

char	*str_join(char *s1, const char *s2);
char	*read_to_buffer(int fd, char *buffer);
char	*extract_line(char **buffer);
char	*find_newline(const char *str);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*get_next_line(int fd);

#endif