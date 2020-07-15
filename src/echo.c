void f_echo(char *str1,int ptr,int l)
{
	int q=ptr,x,flag=0,flag_x=-1;
	for (int i = ptr-1; i < strlen(str1); ++i)
	{
		if(str1[i]=='\'')
		{
			flag_x=0;
			i++;
			while(i<strlen(str1) && str1[i]!='\'')
			{
				i++;
			}
			if(i<strlen(str1) && str1[i]=='\'')
			{
				flag_x=1;
			}
		}
		else if(str1[i]=='\"')
		{
			flag_x=0;
			i++;
			while(i<strlen(str1) && str1[i]!='\"')
			{
				i++;
			}
			if(i<strlen(str1) && str1[i]=='\"')
			{
				flag_x=1;
			}
		}
	}
	if(flag_x==0)
	{
		printf("Invalid Input\n");
		return;
	}
	for (int i = q; i < l; ++i)
	{
		flag=0;
		while(i<strlen(str1) && str1[i]==' ')
			{
				flag=1;
				i++;
			}
		if(flag==1)
			printf(" ");
		if(str1[i]=='\'')
		{
			x=i+1;
			i++;
			while(i<strlen(str1) && str1[i]!='\'')
			{
				i++;
			}
			if(i<strlen(str1) && str1[i]=='\'')
			{
				str1[i]='\0';
				printf("%s",str1+x);
				str1[i]='\'';
			}
			else
				return;
		}
		else if(str1[i]=='\"')
		{
			x=i+1;
			i++;
			while(i<strlen(str1) && str1[i]!='\"')
			{
				i++;
			}
			str1[i]='\0';
			printf("%s",str1+x);
			str1[i]='\"';
		}
		else
		{
			x=i;
			while(i<strlen(str1) && str1[i]!='\"' && str1[i]!='\'' && str1[i]!=' ')
			{
				i++;
			}
			if(str1[i]==' ')
			{
				str1[i]='\0';
				printf("%s",str1+x);
				str1[i]=' ';
				i--;
			}
			else if(str1[i]=='\'')
			{
				str1[i]='\0';
				printf("%s",str1+x);
				str1[i]='\'';
				i++;
				x=i;
				while(i<strlen(str1) && str1[i]!='\'')
				{
					i++;
				}
				str1[i]='\0';
				printf("%s",str1+x);
				str1[i]='\'';
			}
			else if(str1[i]=='\"')
			{
				str1[i]='\0';
				printf("%s",str1+x);
				str1[i]='\"';
				i++;
				x=i;
				while(i<strlen(str1) && str1[i]!='\"')
				{
					i++;
				}
				str1[i]='\0';
				printf("%s",str1+x);
				str1[i]='\"';
			}
			else if(str1[i]=='\0')
			{
				str1[i]='\0';
				printf("%s",str1+x);
				str1[i]=' ';
				i--;
			}
		}
	}
	printf("\n");	
}