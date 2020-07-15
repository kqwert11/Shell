void hist(char *str1,int ptr,int flag_h)
{
		char str[1024],buffer[1024],count=0,temp[100],path[1024],path2[1024];
		strcpy(str,str1);
		int l=strlen(str);
		for (int i = 0; i < strlen(actualpath); ++i)
		{
			path[i]=actualpath[i];
			path2[i]=actualpath[i];
		}
		strcpy(temp,"/history.txt");
		for (int i = 0; i <= strlen(temp); ++i)
		{
			path[i+strlen(actualpath)]=temp[i];
			path2[i+strlen(actualpath)]=temp[i];
		}
		path2[strlen(actualpath)+strlen(temp)-1]='x';
	if(flag_h==0)
	{
		FILE * fp;
		fp = fopen (path,"ab+");
		char c[1024];
		while(fgets(buffer,1020,fp)!=NULL)
		{
			count++;
		}
		if(count<20)
		{
			fprintf(fp, "%s\n",str );
			count++;
			fclose(fp);
		}
		else 
		{
			FILE * fp2;
			fp2 = fopen (path2,"ab+");
			int g=0;
			fseek(fp2,0,0);
			fseek(fp,0,0);
			while(fgets(buffer,1020,fp)!=NULL)
			{
				++g;
				if(g==1)
				continue;
				fprintf(fp2, "%s", buffer);
			}
			fprintf(fp2, "%s\n",str );
			fclose(fp);
			fclose(fp2);
			remove(path);
			rename(path2,path);
		}
	}
	else if(flag_h==1)
	{
		int val=-1,lines=0,limit=0,flag_n=0;
		if(ptr==strlen(str1))
			{
				flag_n=1;
			}
		else
			val=atoi(str+ptr);
		if(val<=0 && flag_n!=1 && str[ptr]!='0')
			{
				printf("INVALID INPUT\n");
				return;
			}
		FILE * fp;
		fp=fopen(path,"ab+");
		while(fgets(buffer,1020,fp)!=NULL)
		{
			lines++;
		}
		fseek(fp,0,0);
		if(flag_n==1)
		{
			if(lines>=10)
				val=10;
			else
				val=lines;
		}
		if(lines>=lines-val)
		{
			if(val>10)
			{
				val=10;
				printf("Printing last 10 commands\n");
			}
			limit=0;
			while(fgets(buffer,1020,fp)!=NULL)
			{
				limit++;
				if(limit>lines-val)
					printf("%s",buffer);
			}
		}
		else if(lines<val)
		{
			printf("Only %d commands are saved\n",lines );
		}
		fclose(fp);

	}
	return;
}