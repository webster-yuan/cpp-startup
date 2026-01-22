#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<assert.h>

void test_strncpy()
{
	char dest[20] = "yuanwei";
	char src[] = "qwerty";
	strncpy(dest,src,sizeof(src));
	printf("%s\n",dest);//qwerty

	//src<num时,不够的部分会默认用\0填充,监控角度小看更清晰
	strncpy(dest, src, sizeof(src)+10);
	printf("%s\n", dest);//qwerty
}
//返回目标空间的起始地址
char* my_strncpy(char* dest, const char* src, size_t n)
{
	assert(dest && src);
	char* ret = dest;
	while (n > 0 && *src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
		n--;
	}
	while (n > 0)
	{
		*dest = '\0';
		dest++;
		n--;
	}
	return ret;
}
//int main()
//{
//	test_strncpy();
//	return 0;
//}