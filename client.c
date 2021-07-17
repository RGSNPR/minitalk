#include "minitalk.h"

void	complete(int sig)
{
	write(1, "String was sent successfully!\n", 30);
	return ;
}

void	send_symbol(int pid, char byte)
{
	unsigned int	counter;

	counter = 1 << 6;
	while (counter != 0)
	{
		if ((byte & counter) != 0)
		{
			if (kill(pid, SIGUSR1) == -1)
				exit_error("Bad pid :(\n");
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				exit_error("Bad pid :(\n");
		}
		counter >>= 1;
		usleep(50);
	}
}

void	main_handler(char *pid_str, char *message)
{
	int	pid;
	int	i;

	pid = ft_atoi(pid_str);
	while (message[i] != '\0')
	{
		send_symbol(pid, message[i]);
		i++;
	}
	send_symbol(pid, message[i]);
}

int	main(int argc, char **argv)
{
	if (argc != 3)
		exit_error("use -> ./client [server-pid] [string]\n");
	signal(SIGUSR1, complete);
	main_handler(argv[1], argv[2]);
	return (0);
}
