void list(char *str,int ptr)
{
	int flag_l=0,flag_a=0;
	int temp=ptr;
	for (int i = ptr; i < strlen(str); ++i)
	{
		if(str[i]=='-')
		{
			if(str[i+1]=='a' && str[i+2]=='l')
			{
				flag_a=1;
				flag_l=1;
			}
			else if(str[i+1]=='l' && str[i+2]=='a')
			{
				flag_a=1;
				flag_l=1;
			}
			else if(str[i+1]=='a')
			{
				flag_a=1;
			}
			else if(str[i+1]=='l')
			{
				flag_l=1;
			}
		}
	}
	if(flag_a==0 && flag_l==0)
	{
		int count=0,x;
		for (int i = ptr; i < strlen(str); ++i)
		{
			if(str[i]!=' ')
			{
				while(str[i]!=' ')
				{
					i++;
				}
				count++;
			}
		}
		int g=0;
		x=count;
		struct dirent *de;
		char path[1024],real_path[1024];
		char* token;
		char* qwerty=str;
		if(count==0)
			{
				DIR *dr = opendir(".");
				while ((de = readdir(dr)) != NULL)
			  	{
			  		if(de->d_name[0]!='.')
						printf("%s  ", de->d_name); 
			  	}
				printf("\n");
			}
		else
		{
			while((token=strtok_r(qwerty," ",&qwerty)))
			{
				g++;
				if(g==1)
					continue;
				if(token[0]=='~')
				{
					for (int i = 0; i < strlen(actualpath); ++i)
					{
						real_path[i]=actualpath[i];
					}
					real_path[strlen(actualpath)]='\0';
					if(strlen(token)!=1)
					for (int i = 1; i < strlen(token); ++i)
					{
						real_path[strlen(actualpath)-1+i]=token[i];
						if(i==strlen(token)-1)
							real_path[strlen(actualpath)+i]='\0';
					}
				}
				else
				{
					char *ptr1;
					char *symlinkpath = token;
					ptr1 = realpath(symlinkpath, real_path);
			    }
			    DIR *dr = opendir(real_path);
			    if (dr == NULL)  
			    {
			    	if(access( real_path, F_OK ) != -1 )
			        	{
			        		printf("%s\n",token);
			        	}
			        else
			        	{
			        		printf("No such file or directory existss\n");
			        	}
			    	continue;
			    }
			    if(count!=1)
			    	printf("%s:\n",token);
			  	while ((de = readdir(dr)) != NULL) 
			  	{
			  		if(de->d_name[0]!='.')
						printf("%s  ", de->d_name); 
			  	}
			  	printf("\n");
				closedir(dr);
			    if(count!=1)
			    {
			    	if(x>1)
			    	{
			    		x--;
			    		printf("\n");
			    	}
			    }
			}
		}
	}
	else if(flag_l==0 && flag_a==1)
	{
		struct dirent *de;
		DIR *dr = opendir(".");
		while ((de = readdir(dr)) != NULL) 
	  	{
			printf("%s  ", de->d_name); 
	  	}
		printf("\n");
	}
	else if(flag_l==1)
	{
		char date_str[1024];
		struct dirent *de;
		struct stat sfile;
		DIR *dr = opendir(".");
		while ((de = readdir(dr)) != NULL) 
	  	{
	  		if(de->d_name[0]=='.' && flag_a==0)
	  			continue;
			char temp_filename[1024];
			strcpy(temp_filename,de->d_name);
			if(stat(temp_filename,&sfile)==-1)
			{
				printf("ERROR: file is not accessible\n");
			}
			printf((sfile.st_mode & S_IFDIR)? "d":"-");
		  	printf((sfile.st_mode & S_IRUSR)? "r":"-");
		  	printf((sfile.st_mode & S_IWUSR)? "w":"-");
		  	printf((sfile.st_mode & S_IXUSR)? "x":"-");
		  	printf((sfile.st_mode & S_IRGRP)? "r":"-");
		  	printf((sfile.st_mode & S_IWGRP)? "w":"-");
		  	printf((sfile.st_mode & S_IXGRP)? "x":"-");
		  	printf((sfile.st_mode & S_IROTH)? "r":"-");
		  	printf((sfile.st_mode & S_IWOTH)? "w":"-");
		  	printf((sfile.st_mode & S_IXOTH)? "x":"-");
		  	printf(" ");
		  	printf("%u",(unsigned int)sfile.st_nlink);
		  	printf(" ");
		  	struct passwd *pw = getpwuid(sfile.st_uid);
			struct group *gr = getgrgid(sfile.st_gid);
			printf("%s %s ",pw->pw_name,gr->gr_name);
			printf("%5ld ",sfile.st_size );
			strcpy(date_str,ctime(&sfile.st_ctime));
			date_str[7]='\0';
			date_str[10]='\0';
			date_str[16]='\0';
			printf("%s ",date_str +4);
			printf("%s ",date_str +8 );
			printf("%s ",date_str +11 );
			printf("%s\n",temp_filename);
	  	}
	}
	return;
}