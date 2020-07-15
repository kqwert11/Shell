#include<stdlib.h>
#include<stdio.h> 
#include<fcntl.h> 
#include<sys/types.h>
#include <sys/wait.h> 
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#include<libgen.h>
#include<pwd.h>
#include<dirent.h> 
#include<grp.h>
#include <time.h>
char actualpath[1024];
#include "cd.c"
#include "pwd.c"
#include "echo.c"
#include "ls.c"
#include "pinfo.c"
#include "hist.c"
long long int T=0;
void commandprompt(char *arr)
{
	if(T==0)
		{
			char *ptr1;
			char *symlinkpath = arr;
			ptr1 = realpath(symlinkpath, actualpath);
			int point;
			for (int i = strlen(actualpath)-1; i >=0; --i)
			{
				if(actualpath[i]=='/')
				{
					actualpath[i]='\0';
					point=i;
					break;
				}
			}
		}
	T++;
	char hostname[1024], *username,cwd[1024],net_cwd[1024];
	username=getlogin();
	gethostname(hostname, 1023);
	long long int n1,n2,flag=1,i;
	getcwd(cwd,sizeof(cwd));
	n1=strlen(cwd);
	n2=strlen(actualpath);
	for (i = 0; i < n2 && i < n1; ++i)
	{
		if(cwd[i]!=actualpath[i])
			{
				flag=0;
				break;
			}
	}
	if(i==n2 && flag==1)
	{
		net_cwd[0]='~';
		for (int j = n2; j < n1+1; ++j)
		{
			net_cwd[j-n2+1]=cwd[j];
		}
	}
	else
	{
		for (int j = 0; j < n1+1; ++j)
		{
			net_cwd[j]=cwd[j];
		}
	}
	// fflush(stdout);
	printf("<%s@%s:%s> ",username, hostname,net_cwd);
	fflush(stdout);
}
void handler(int sig)
{
	pid_t pid;
	int status;
	char *exit=(char *)malloc(1024*(sizeof(char)));
	char *exit_status=(char *)malloc(1024*(sizeof(char)));
	pid=waitpid(0,&status,WNOHANG);
	sprintf(exit,"\npid %d exited.\n",pid);
	if(WIFEXITED(status))
	{
		int ab=WEXITSTATUS(status);
		if(ab==0)
			sprintf(exit_status, "normally\n");
		else
			sprintf(exit_status, "abnormally\n");
	}
	if(pid>0)
	{
		write(2,exit,strlen(exit));
		write(2,exit_status,strlen(exit_status));
		commandprompt(actualpath);
	}
	free(exit);
	return;
}
#include "oth.c"
int main(int argc, char** argv)
{
	signal(SIGCHLD,handler);
	char str101[1024],str1[1024];
	while(1)
	{
		commandprompt(argv[0]);
		scanf(" %[^\n]%*c",str101);
		hist(str101,-1,0);
		char* token = strtok(str101,";");
		while (token != NULL)
		{
			for (int i = 0; i <strlen(token); ++i)
			{
				str1[i]=token[i];
				if(i==strlen(token)-1)
					str1[i+1]='\0';
			}
			long long int l=strlen(str1),ptr=0,flag_bg=0;
			while(str1[ptr]==' ')
			{
				ptr++;
			}
			if(str1[ptr]=='c' && str1[ptr+1]=='d')
			{
				ptr+=2;
				if(str1[ptr]==' ' || str1[ptr]=='\0')
				{
					while(str1[ptr]==' ')
					{
						ptr++;
					}
					cd(str1,ptr);
				}
				else
				{
					printf("%s: command not found\n",str1);
				}
			}
			else if(str1[ptr]=='p' && str1[ptr+1]=='w' && str1[ptr+2]=='d')
			{
				ptr+=3;
				if(str1[ptr]==' ' || str1[ptr]=='\0')
				{
					f_pwd(str1,ptr);
				}
				else
				{
					printf("%s: command not found\n",str1);
				}
			}
			else if(str1[ptr]=='e' && str1[ptr+1]=='c' && str1[ptr+2]=='h' && str1[ptr+3]=='o')
			{
				ptr+=4;
				if(str1[ptr]==' ' || str1[ptr]=='\0')
				{
					while(str1[ptr]==' ')
					{
						ptr++;
					}
					f_echo(str1,ptr,l);
				}
				else
				{
					printf("%s: command not found\n",str1);	
				}
			}
			else if(str1[ptr]=='l' && str1[ptr+1]=='s')
			{
				ptr+=2;
				if(str1[ptr]==' ' || str1[ptr]=='\0')
				{
					while(str1[ptr]==' ')
					{
						ptr++;
					}
					list(str1,ptr);
				}
				else
				{
					printf("%s: command not found\n",str1);	
				}

			}
			else if(str1[ptr]=='p' && str1[ptr+1]=='i' && str1[ptr+2]=='n' && str1[ptr+3]=='f' && str1[ptr+4]=='o')
			{
				ptr+=5;
				if(str1[ptr]==' ' || str1[ptr]=='\0')
				{
					while(str1[ptr]==' ')
					{
						ptr++;
					}
					pinfo(str1,ptr);
				}
				else
				{
					printf("%s: command not found\n",str1);
				}
			}
			else if(str1[ptr]=='h' && str1[ptr+1]=='i' && str1[ptr+2]=='s' && str1[ptr+3]=='t' && str1[ptr+4]=='o' && str1[ptr+5]=='r' && str1[ptr+6]=='y')
			{
				ptr+=7;
				if(str1[ptr]==' ' || str1[ptr]=='\0')
				{
					while(str1[ptr]==' ')
					{
						ptr++;
					}
					hist(str1,ptr,1);
				}
				else
				{
					printf("%s: command not found\n",str1);
				}
			}
			else if(str1[ptr]=='e' && str1[ptr+1]=='x' && str1[ptr+2]=='i' && str1[ptr+3]=='t' && (str1[ptr+4]==' ' || str1[ptr+4]=='\0'))
			{
				ptr+4;
				exit(0);
			}
			else
			{	
				othfunc(str1,ptr);
			}
			token = strtok(NULL,";");
		}
	}
}
