#include "so_long.h"

static void	check_file_descriptor(int fd);
static void	check_line_len(char *line, size_t *md_format);
static void	check_map_description_format(size_t *md_format);
static void	get_map_description_format(int fd, size_t *md_format);

t_matrix	*create_map_description(char *md_file)
{
	int	fd;
	size_t	md_format[2];

	fd = open(md_file, O_RDWR);
	check_file_descriptor(fd);
	get_map_description_format(fd, md_format);
	close(fd);
	return (create_matrix(md_format[0], md_format[1]));
}

static void	get_map_description_format(int fd, size_t *md_format)
{
	char	*line;

	line = get_next_line(fd);
	md_format[0] = 0;
	md_format[1] = ft_strlen(line) - 1;
	while (line)
	{
		md_format[0]++;
		check_line_len(line, md_format);
		free(line);
		line = get_next_line(fd);
	}
	check_map_description_format(md_format);
}

static void	check_map_description_format(size_t *md_format)
{
	t_error error;

	if (md_format[0] && md_format[1])
		return ;
	errno = EINVAL;
	error.message = ft_strdup("Map description file is empty");
	error.matrix = NULL;
	exit_with_error(&error);
}

static void	check_line_len(char *line, size_t *md_format)
{
	t_error	error;
	size_t	line_len;
	char	*rows_str;

	line_len = ft_strlen(line) - 1;
	if (line_len == md_format[1])
		return ;
	rows_str = ft_itoa(md_format[0]);
	errno = EINVAL;
	error.message = ft_strjoin("Map description file has line ", rows_str);
	error.matrix = NULL;
	free(line);
	free(rows_str);
	exit_with_error(&error);
}

static void	check_file_descriptor(int fd)
{
	t_error error;

	if (fd != -1)
		return ;
	error.message = ft_strdup("Map description file");
	error.matrix = NULL;
	exit_with_error(&error);
}
