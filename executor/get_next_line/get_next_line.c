#include "get_next_line.h"

int to_check(char *s)
{
    int i;

    i = 0;
    if (!s)
        return (-1);
    while (s[i])
    {
        if (s[i] == '\n')
            return (i);
        i++;
    }
    return (-1);
}

char *read_buffer(char *saved, int fd)
{
    char *buffer;
    int max;

    max = 1;
    buffer = malloc(BUFFER_SIZE + 1);
    while (to_check(saved) == -1 && max != 0)
    {
        max = read(fd, buffer, BUFFER_SIZE);
        if (max == -1)
        {
            free(saved);
            free(buffer);
            saved = NULL;
            return (saved);
        }
        buffer[max] = '\0';
        saved = join(saved,buffer);
    }
    if (ft_strlen(saved) == 0 && max == 0)
    {
        free(saved);
        saved = NULL;
    }
    free(buffer);
    return (saved);
}

char *get_next_line(int fd)
{
    static char *saved = NULL;
    char *line;
    int index_line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    if (to_check(saved) == -1)
        saved = read_buffer(saved, fd);
    if (!saved)
        return (NULL);
    index_line = to_check(saved);
    if (index_line != -1)
    {
        line = substr(saved, 0, index_line + 1);
        saved = after_nline(saved, index_line + 1);
        return (line);
    }
    line = saved;
    saved = NULL;
    return(line);
}