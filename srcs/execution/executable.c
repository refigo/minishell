#include <sys/stat.h>
#include "execution.h"

/*
	lstat
		buf.st_mode
			S_ISREG
			S_ISDIR
			S_IXUSR
*/

int	is_executable(char *checking)
{
	struct stat	stat_buf;
	int			status;
	int			ret;

	ret = FALSE;
	status = lstat(checking, &stat_buf);
	if (status == 0 \
		&& ((stat_buf.st_mode & S_IFMT) == S_IFREG) \
		&& (stat_buf.st_mode & S_IXUSR))
		ret = TRUE;
	return (ret);
}
