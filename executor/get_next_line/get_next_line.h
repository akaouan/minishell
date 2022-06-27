#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
#define BUFFER_SIZE 10
# include<stdlib.h>
# include<unistd.h>
int ft_strlen(char *s);
char *ft_strdup(char *s);
char *substr(char *s, int start, int len);
char *after_nline(char *s, int start);
char *join(char *s1, char *s2);
int to_check(char *s);
char *read_buffer(char *saved, int fd);
char *get_next_line(int fd);
#endif