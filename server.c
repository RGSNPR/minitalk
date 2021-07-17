#include "minitalk.h"

t_minitalk	g_print_str;

void	usr1_handler(int sig, siginfo_t *info, void *old)
{
	if (g_print_str.top_bit == 0)
	{
		g_print_str.top_bit = 1 << 6;
		g_print_str.top_byte++;
	}
	g_print_str.string[g_print_str.top_byte] += g_print_str.top_bit;
	g_print_str.top_bit >>= 1;
	if (g_print_str.top_byte == BUFFSIZE - 2 && g_print_str.top_bit == 0)
		g_print_str.buff_end = 1;
}

void	usr2_handler(int sig, siginfo_t *info, void *old)
{
	if (g_print_str.top_bit == 0)
	{
		g_print_str.top_bit = 1 << 6;
		g_print_str.top_byte++;
	}
	g_print_str.top_bit >>= 1;
	if (g_print_str.top_byte == BUFFSIZE - 2 && g_print_str.top_bit == 0)
		g_print_str.buff_end = 1;
	else if (g_print_str.string[g_print_str.top_byte] == 0
		&& g_print_str.top_bit == 0)
	{
		g_print_str.receive_end = 1;
		kill(info->si_pid, SIGUSR1);
	}
}

void	main_handler(void)
{
	while (1)
	{
		pause();
		if (g_print_str.buff_end || g_print_str.receive_end)
		{
			write(1, g_print_str.string, ft_strlen(g_print_str.string));
			ft_bzero(g_print_str.string, BUFFSIZE);
			g_print_str.top_bit = 1 << 6;
			g_print_str.top_byte = 0;
			if (g_print_str.receive_end)
				write(1, "\n", 1);
			g_print_str.buff_end = 0;
			g_print_str.receive_end = 0;
		}
	}
}

void	printPID(void)
{
	pid_t	pid;
	char	*pid_str;

	pid = getpid();
	pid_str = ft_itoa(pid);
	write(1, pid_str, ft_strlen(pid_str));
	write(1, "\n", 1);
	free(pid_str);
	return ;
}

int	main(void)
{
	struct sigaction	act_handler;
	struct sigaction	null_handler;

	act_handler.sa_sigaction = usr1_handler;
	null_handler.sa_sigaction = usr2_handler;
	act_handler.sa_flags = SA_SIGINFO;
	null_handler.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act_handler, NULL);
	sigaction(SIGUSR2, &null_handler, NULL);
	printPID();
	if (BUFFSIZE <= 0)
		exit_error("Buffer size is too low, nothing will be displayed\n");
	if (init_struct() == 0)
		exit (0);
	main_handler();
	return (0);
}
