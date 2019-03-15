#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <utime.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>


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
	char text[20];
	int counter=1;
	while(1)
	{
		struct stat filestat;
		char a[]="/home/igedeagung/Documents/makanan/makan_enak.txt";
		stat(a,&filestat);
		time_t program=time(NULL);
		time_t buka=filestat.st_atime;

		if(difftime(program, buka)<=30)
		{
			sprintf(text, "%d", counter);
		        char aa[]="/home/igedeagung/Documents/makanan/makan_sehat";
			char ext[]=".txt";
			strcat(aa,text);
			strcat(aa,ext);
			FILE *makan=fopen(aa,"w");
			fprintf(makan, "DIET");
			fclose(makan);
			counter++;
		}
		sleep(5);
	}
	exit(EXIT_SUCCESS);
	return(0);
}
