#include <stdlib.h> // For malloc, free, and NULL
#include <unistd.h> // For read function
#include <string.h> // For strlen, strcpy, strchr, strdup, strndup
#include <stdio.h> // For printf

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42 // Default buffer size if not defined
#endif

// Helper function to find the newline character
static char *find_newline(const char *str)
{
    if (!str) // If the string is NULL, return NULL
        return NULL;
    return strchr(str, '\n'); // Find the first occurrence of '\n' in the string
}

// Helper function to join two strings
static char *str_join(char *s1, const char *s2)
{
    size_t len1 = s1 ? strlen(s1) : 0; // Length of the first string (or 0 if NULL)
    size_t len2 = s2 ? strlen(s2) : 0; // Length of the second string
    char *result = malloc(len1 + len2 + 1); // Allocate memory for the concatenated string
    if (!result) // Check if memory allocation failed
        return NULL;
    if (s1)
        strcpy(result, s1); // Copy the first string into result
    if (s2)
        strcpy(result + len1, s2); // Append the second string to result
    free(s1); // Free the old memory of the first string
    printf("[str_join] Joined strings, result: '%s'\n", result);
    return result; // Return the concatenated string
}

// Helper function to extract a line from the buffer
static char *extract_line(char **buffer)
{
    char *newline_pos = find_newline(*buffer); // Find the position of the newline
    char *line;
    char *remaining;

    if (newline_pos) // If a newline is found
    {
        size_t line_len = newline_pos - *buffer + 1; // Calculate the length of the line
        line = strndup(*buffer, line_len); // Duplicate the line up to the newline
        remaining = strdup(newline_pos + 1); // Duplicate the remaining part after the newline
        free(*buffer); // Free the old buffer
        *buffer = remaining; // Update the buffer with the remaining part
        printf("[extract_line] Extracted line: '%s', Remaining buffer: '%s'\n", line, *buffer ? *buffer : "(null)");
    }
    else // If no newline is found
    {
        line = strdup(*buffer); // Duplicate the entire buffer as the line
        free(*buffer); // Free the old buffer
        *buffer = NULL; // Set buffer to NULL as it's fully consumed
        printf("[extract_line] Extracted last line: '%s', Buffer is now empty.\n", line);
    }

    return line; // Return the extracted line
}

// The get_next_line function
char *get_next_line(int fd)
{
    static char *buffer = NULL; // Static buffer to hold leftover data between calls
    char *line; // Variable to store the extracted line
    char temp_buffer[BUFFER_SIZE + 1]; // Temporary buffer for reading from the file
    ssize_t bytes_read; // Number of bytes read from the file

    if (fd < 0 || BUFFER_SIZE <= 0) // Validate the file descriptor and buffer size
        return NULL;

    printf("[get_next_line] Starting with buffer: '%s'\n", buffer ? buffer : "(null)");

    while (!find_newline(buffer)) // Continue reading until a newline is found
    {
        bytes_read = read(fd, temp_buffer, BUFFER_SIZE); // Read data from the file
        if (bytes_read < 0) // If read fails, handle the error
        {
            free(buffer); // Free the buffer to avoid memory leaks
            buffer = NULL;
            perror("[get_next_line] Read error");
            return NULL; // Return NULL to indicate failure
        }
        if (bytes_read == 0) // If end of file is reached
            break;
        temp_buffer[bytes_read] = '\0'; // Null-terminate the temporary buffer
        printf("[get_next_line] Read %zd bytes: '%s'\n", bytes_read, temp_buffer);
        buffer = str_join(buffer, temp_buffer); // Append the new data to the static buffer
        if (!buffer) // If memory allocation fails during str_join
            return NULL;
    }

    if (buffer && *buffer) // If the buffer contains data
    {
        printf("[get_next_line] Extracting line from buffer: '%s'\n", buffer);
        line = extract_line(&buffer); // Extract a line from the buffer
    }
    else // If the buffer is empty or NULL
    {
        free(buffer); // Free the buffer
        buffer = NULL; // Set buffer to NULL
        printf("[get_next_line] No more lines to read.\n");
        return NULL; // Return NULL to indicate no more lines
    }

    printf("[get_next_line] Returning line: '%s'\n", line);
    return line; // Return the extracted line
}
