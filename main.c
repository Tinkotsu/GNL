#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main()
{
	char *str;
	int fd;

	fd = open("gnl7_3.txt", O_RDONLY);
	while (get_next_line(fd, &str))
		printf("%s", str);
	return (0);
}
