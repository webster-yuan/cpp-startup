#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<assert.h>
void test_strncat()
{
	//1. 从dest的\0开始追加,\0是被覆盖的
	char dest[40] = "yuanwei\0XXXXXXXX";
	char src[] = "qwert";
	strncat(dest, src, sizeof(src));
	printf("%s\n", dest);
	//2. 当src.size() < num时,并不会像strncpy一样补够num个
	strncat(dest, src, sizeof(src) + 5);
	printf("%s\n",dest);
}
char* strncat(char* dest,const char*src,size_t n)
{
	assert(dest && src);
	char* ret = dest;
	//先找到第一个\0
	while (*dest != '\0') *dest++;
	//追加
	while (n > 0 && *src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
		n--;
	}
	*dest = '\0';
	return ret;
}
//int main()
//{
//	return 0;
//}