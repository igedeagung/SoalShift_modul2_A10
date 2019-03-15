#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>

static int parse_ext(const struct dirent *dir)
{
	if(!dir)
	return 0;

	if(dir->d_type == DT_REG)
	{
		const char *ext = strrchr(dir->d_name,'.');
		if((!ext) || (ext == dir->d_name))
		{return 0;}
		else
		{
			if(strcmp(ext, ".png") == 0)
			{return 1;}
		}
	}
	return 0;
}

int main()
{
	pid_t pid, sid;

	pid = fork();

	if (pid < 0) {
		exit(EXIT_FAILURE);
	}

	if (pid > 0) {
		exit(EXIT_SUCCESS);
	}

	umask(0);

	sid = setsid();

	if (sid < 0) {
		exit(EXIT_FAILURE);
	}

	if ((chdir("/home/igedeagung/")) < 0) {
		exit(EXIT_FAILURE);
	}

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	while(1)
	{
		struct dirent **namelist;
		int n;
		int i;
		i=0;
		n = scandir(".", &namelist, parse_ext, alphasort);
		if (n < 0)
		{
			perror("scandir");
			return 1;
		}
		else
		{
			while(n--)
			{
		        	char *old_name = namelist[n]->d_name;
				char sementara[100];
				memset(sementara, '\0', sizeof(sementara));
				strncpy(sementara, old_name, (strlen(old_name)-4));
				if(i==0)
				{
					strcat(sementara, "_grey.png");
				}
				char new_name[100];
				strcpy(new_name, "/home/igedeagung/modul2/gambar/");
				strcat(new_name, sementara);
				rename(old_name, new_name);
        	   		free(namelist[n]);
			}
		}
		sleep(5);
	}
	exit(EXIT_SUCCESS);
}
