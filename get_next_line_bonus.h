/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:39:47 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/01/15 17:27:24 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif 

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

char	*str_join(char *s1, const char *s2);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*extract_line(char **buffer);
char	*read_to_buffer(int fd, char *buffer);
char	*find_newline(const char *str);
char	*get_next_line(int fd);

#endif