#include "libft.h"

int	main()
{
	char	*line = "$a";
	char	*value = "";
	int		start = 0;
	int		end = 1;

	char	*new_line = ft_strunion(line, value, start, end);
	ft_printf(1, "ft_strunion(\"%s\", \"%s\", %d, %d) = \"%s\"\n", line, value, start, end, new_line);
	free(new_line);
}