#include "minitalk.h"

void	exit_error(const char *error_str)
{
	write(1, error_str, ft_strlen(error_str));
	exit(0);
}
