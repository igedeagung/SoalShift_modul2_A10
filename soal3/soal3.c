#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>


int main()
{
	int p[2];
	pid_t anak;
	pid_t anakanak;
	int status;
	pipe(p);
	anakanak=fork();
	if(anakanak==0)
	{
		char *unzip[]={"unzip", "/home/igedeagung/campur2.zip", "-d", "/home/igedeagung/", NULL};
		execv("/usr/bin/unzip", unzip);
	}
	else
	{
		while((wait(&status))>0);
		anak=fork();
		if(anak==0)
		{
			close (p[0]);
			int file=open("/home/igedeagung/daftar.txt", O_WRONLY);
			dup2(p[1],STDOUT_FILENO);
			char *eles[]={"ls", "/home/igedeagung/campur2/", NULL};
			execv("/bin/ls", eles);
		}
		else
		{
			while((wait(&status))>0);
			close(p[1]);
			dup2(p[0],STDIN_FILENO);
			int fileopen=open("/home/igedeagung/daftar.txt", O_WRONLY);
			close(p[0]);
			dup2(fileopen, STDOUT_FILENO);
			char *grab[]={"grep",".txt$", NULL};
			execv("/bin/grep", grab);
		}
	}
}
