#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main()
{
	char *str;
	int fd;

	fd = open("get_next_line.h", O_RDONLY);
	while (get_next_line(fd, &str))
		printf("%s", str);
	return (0);
}