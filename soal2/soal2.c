#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>

int main()
{
	pid_t pid, sid;

	pid = fork();

	if (pid < 0)
	{
		exit(EXIT_FAILURE);
	}

	if (pid > 0)
	{
	exit(EXIT_SUCCESS);
	}

	umask(0);

	sid = setsid();

	if (sid < 0)
	{
		exit(EXIT_FAILURE);
	}

	if ((chdir("/home/igedeagung/")) < 0)
	{
		exit(EXIT_FAILURE);
	}

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	while(1)
	{
		struct stat sb;
		char folder[100]="/home/igedeagung/hatiku/elen.ku";
		stat(folder, &sb);

		struct passwd *pw = getpwuid(sb.st_uid);
		struct group  *gr = getgrgid(sb.st_gid);
		char data[10]="www-data";
		int usr=strcmp(pw->pw_name, data);
		int grp=strcmp(gr->gr_name, data);
		if(usr==0 && grp==0)
		{
			remove(folder);
		}
		sleep(3);
	}
	exit(EXIT_SUCCESS);
	return 0;
}


