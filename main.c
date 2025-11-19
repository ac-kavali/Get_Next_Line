#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"


int main(void)
{
    int fd = open("file.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        return 1;
    }

    char *line;
    while ((line = get_next_line_bonus(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    a++;
    a++;

    close(fd);
    return 0;
}
