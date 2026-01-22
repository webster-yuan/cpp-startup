#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<assert.h>

//字符串追加函数,在dest的\0位置开始替换,会将src的\0也拷贝过去
//dest目标空间足够大,否则形成内存越界访问
void test_strcat()
{
	char arr1[20] = "yuanwei";
	char arr2[40] = "yuanwei\0yuanwei";
	char src[] = "hello";
	strcat(arr1, src);
	strcat(arr2, src);
	printf("%s\n",arr1); //yuanweihello
	printf("%s\n",arr2);//yuanweihello
}
//返回dest目标空间的起始地址
char* my_strat(char* dest, const char* src)
{
	assert(dest && src);
	char* ret = dest;
	//找到第一个\0
	while (*dest != '\0')
	{
		dest++;
	}
	//拷贝
	while (*dest++ = *src++)
	{
		;
	}
	return ret;
}
//自己给自己赋值会出现死循环问题,因为src找的那个\0已经被dest修改为其他值了
//int main()
//{
//	test_strcat();
//	return 0;
//}