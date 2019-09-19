#include "get_next_line.h"
#include <fcntl.h>

int		main(int argc, char **argv)
{
	int		i;
	int		fd;
	char	*line;
	int		z;

	line = (char*)malloc(sizeof(char) * 1000);

	if (argc == 1)
		fd = 0;
	else
		if (!(fd = open(argv[1], O_RDONLY)))
			return (0);

	while (get_next_line(fd, &line));
		ft_putendl(line);
	close(fd);
	return (0);
}
