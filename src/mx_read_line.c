#include "libmx.h"

static void reline(char **lineptr, char **buffer, size_t buf_size);

int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd) {
    char buf = '\0';
    int i = 0;
    char *buffer = mx_strnew(buf_size);
    mx_strdel(lineptr);

    if (fd == -1)
        return -2;

    while (read(fd, &buf, 1) > 0) {
        if (!(i % buf_size) || buf == delim) {
            reline(lineptr, &buffer, buf_size);
            
            if (buf == delim) {
                mx_strdel(&buffer);
                return i;
            }
        }
        
        buffer[i % buf_size] = buf;
        i++;
    }
    
    reline(lineptr, &buffer, buf_size);
    mx_strdel(&buffer);
    return -1;
}

static void reline(char **lineptr, char **buffer, size_t buf_size) {
    char *str = mx_strjoin(*lineptr, *buffer);

    mx_strdel(lineptr);
    mx_strdel(buffer);
    *buffer = mx_strnew(buf_size);
    *lineptr = str;
}
