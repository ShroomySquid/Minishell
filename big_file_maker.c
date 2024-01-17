#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int	main(void)
{
	int file;
	int i;

	if (!access("bigfile.txt", F_OK))
		return (0);
	file = open("bigfile.txt", O_CREAT | O_WRONLY | O_APPEND, 0000644);
	if (file < 0)
	{
		printf("Failed to open bigfile.txt");
		return (1);
	}
	i = 0;
	while (i < 1050000)
	{
		write(file, "A", 1);	
		i++;
	}
	return (0);
}
