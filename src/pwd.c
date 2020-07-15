void f_pwd(char *str1,int ptr)
{
	char s_pwd[1024];
	getcwd(s_pwd,sizeof(s_pwd));
	printf("%s\n",s_pwd);	
}