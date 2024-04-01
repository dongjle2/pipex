#include <unistd.h>

int	main(void)
{
	int		fildes[2];
	int		pipe_res;
	pid_t	pid;

	pipe_res = pipe(fildes);
	if (pipe_res == -1)
		return (0);
	
	pid = fork();
	if (pid == 0)
	{
		
	}
	else
	return (0);
}