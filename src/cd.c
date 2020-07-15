void cd(char *str1, int ptr)
{
	int q=ptr;
	char str2[1024];
	if(q==strlen(str1))
	{
		chdir(actualpath);
	}
	else
	{
		while(str1[ptr]!=' ')
		{
			ptr++;
		}
		if(str1[q]=='~')
		{
			for (int i = 0; i < strlen(actualpath); ++i)
			{
				str2[i]=actualpath[i];
			}
			for (int i = q+1; i < ptr; ++i)
			{
				str2[strlen(actualpath)+i-q-1]=str1[i];
				if(i==ptr-1)
					str2[strlen(actualpath)+i-q]='\0';
			}
		}
		else
		{
			for (int i = q; i < ptr; ++i)
			{
				str2[i-q]=str1[i];
				if(i==ptr-1)
					str2[i-q+1]='\0';
			}
		}
		if(chdir(str2)<0)
			perror("error");	
	}
}