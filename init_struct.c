#include "minitalk.h"

extern t_minitalk	g_print_str;

int	init_struct(void)
{
	g_print_str.string = (char *)malloc(sizeof(char) * (BUFFSIZE + 1));
	if (!g_print_str.string)
		return (0);
	g_print_str.top_byte = 0;
	g_print_str.top_bit = 1 << 6;
	g_print_str.receive_end = 0;
	g_print_str.buff_end = 0;
	return (1);
}
