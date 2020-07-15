void pinfo(char *str,int ptr)
{
	int l=strlen(str);
	char str1[1024];
	if(ptr==l)
	{
		int pid=getpid();
		printf("pid -- %d\n",getpid());
		sprintf(str1,"/proc/%d",getpid());
	}
	else
	{
		strcpy(str1,"/proc/");
		printf("pid -- ");
		for (int i = ptr; i < strlen(str); ++i)
		{
			printf("%c",str[i]);
			str1[6+i-ptr]=str[i];
			if(i==l-1)
				str1[7+i-ptr]='\0';
		}
		printf("\n");
	}
	int count=0,ct=0,flag=0;
	char str3[1024];
	strcpy(str3,str1);
	l=strlen(str3);
	str3[l]='/';
	str3[l+1]='s';
	str3[l+2]='t';
	str3[l+3]='a';
	str3[l+4]='t';
	str3[l+5]='u';
	str3[l+6]='s';
	str3[l+7]='\0';
	FILE *fp = fopen(str3,"r");
    char word[10000];
    char str2[1024];
        while( fscanf(fp, "%s", word) != EOF )
        {
        	count++;
        	if(!strcmp("State:",word))
        	{
        		ct++;
        		flag=1;
        		continue;
        	}
        	else if(!strcmp("VmSize:",word))
        	{
        		ct++;
        		flag=2;
        		continue;
        	}
        	if(flag!=0)
        	{
        		if(flag==1)
        		{
        			printf("Process Status -- %s\n",word );	
        			flag=0;
        		}
        		else if(flag==2)
        		{
        			printf("memory -- %s  {virtual memory}\n", word);
        			flag=0;
        		}
        	}
        }
        if(ct!=2)
        {
        	printf("memory -- ?\n");
        }
        l=strlen(str1);
        str1[l]='/';
        str1[l+1]='e';
        str1[l+2]='x';
        str1[l+3]='e';
        str1[l+4]='\0';
        memset(str2, 0, sizeof(str2));
		int x= readlink(str1,str2,1023);
		flag=1;
		long long int n1,n2,i;
		char net_cwd[1024];
		n1=strlen(str2);
		n2=strlen(actualpath);
		for (i = 0; i < n2 && i < n1; ++i)
		{
			if(str2[i]!=actualpath[i])
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
				net_cwd[j-n2+1]=str2[j];
			}
		}
		else
		{
			for (int j = 0; j < n1+1; ++j)
			{
				net_cwd[j]=str2[j];
			}
		}
		if(x<0)
			perror("Error");
		else
		printf("Executable Path -- %s\n",net_cwd );
}