#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<assert.h>

//判断str2是不是在str1中,判断在不在,不在返回nullptr,在,返回第一次出现的地址
char* my_strstr(const char* str1, const char* str2);
void test_strstr()
{
	char str1[] = "yuanwei";
	char str2[] = "wei";
	char* ret1 = my_strstr(str1,str2);
	char* ret2 = strstr(str1,str2);
	if (ret1)
		printf("%s\n",ret1);
}
char* my_strstr( const char* str1, const  char* str2)
{
	assert(str1 &&str2);

	const char* s1 = str1, * s2 = str2;   //加上const 避免不加时和参数列表constchar* 权限放大的问题
	char* cur = str1;
	while (*cur)//以每一个字符都作为起始字符试试能不能匹配str2
	{
		while (*s1 && *s2 && *s1 == *s2)//*s!='\0'
		{
			s1++;
			s2++;
		}
		if (*s2 == '\0') return cur;
		//else说明以此时的cur开头没有匹配成功
		cur++;//从下一个字符开始再匹配
		//两个指针再回指到两个字符串的起始位置
		s1 = cur;
		s2 = str2;
	}
	return NULL;
}
//int main()
//{
//	test_strstr();
//	return 0;
//}