#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int main(void)
{
    int fd;
    char *line;
    fd = 0;
    while (line = get_next_line(fd))
    {
        printf("%s",line);
        free(line);
    }
    return 0;
}