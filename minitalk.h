#ifndef MINITALK_H
# define MINITALK_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <time.h>
# include <sys/wait.h>
# include <signal.h>
# include "libft/libft.h"

# define BUFFSIZE 512

typedef struct s_minitalk
{
	char	*string;
	int		top_byte;
	int		top_bit;
	int		receive_end;
	int		buff_end;
}				t_minitalk;

int		init_struct(void);
void	exit_error(const char *error_str);

#endif
