#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define	BUFF_SIZE 2048

char	buff[BUFF_SIZE];

char	*strjoinlen(char *a, char *b, int len)
{
	int alen = 0;

	while (a[alen])
		alen++;

	char	*ptr = malloc(alen + len + 1);
	ptr[alen + len] = 0;

	int i = 0;
	while (i < alen)
	{
		ptr[i] = a[i];
		i++;
	}
	int j = 0;
	while (j < len)
	{
		ptr[i + j] = b[j];
		j++;
	}
	free(a);
	return ptr;
}

int		get_next_line(char **line)
{
	char	*tmp;
	static char	*last = 0;
	int		len;
	int		code = 1;
	int		ll = 0;

	if (last == 0)
		last = strdup("");
	while (strchr(last, '\n') == 0)
	{
		len = read(0, buff, BUFF_SIZE);
		if (len == 0)
		{
			code = 0;
			break ;
		}
		else if (len == -1)
		{
			free (last);
			return (-1);
		}
		last = strjoinlen(last, buff, len);
	}
	while (last[ll] != '\n' && last[ll])
		ll++;
	*line = strjoinlen(strdup(""), last, ll); //strndup(last, ll);
	tmp = last;
	if (code)
		last = strdup(last + ll + 1);
	free(tmp);
	return code;
}

#include "stdio.h"

int		main(int argc, char **argv)
{
	char	*line;

	while (get_next_line(&line) > 0)
	{
		printf("%s\n", line);
		free(line);
	}
	printf("%s", line);
	free(line);
}