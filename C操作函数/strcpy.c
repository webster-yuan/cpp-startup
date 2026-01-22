#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<assert.h>
//1. 原字符串必须以\0结尾
void test1()
{
	char src1[] = "yuanwei";
	char dest1[20] = {0};
	strcpy(dest1,src1);
	printf("%s\n", dest1); //yuanwei


	char src2[] = { 'a','b','c' };
	char dest2[20] = { 0 };
	strcpy(dest2, src1);
	printf("%s\n", dest2); //fatal

	char src3[10] = { 'a','b','c' };
	char dest3[20] = { 0 };
	strcpy(dest3, src1);
	printf("%s\n", dest2); //abc
}

//2. 会将原字符串中的\0也拷贝过去(监视窗口查看)
void test2()
{
	char dest[20] = "XXXXXXXX";
	char src1[] = "abcd";
	strcpy(dest, src1);

}
//3. 目标字符换缓冲区必须足够大,否则崩溃.将目标缓冲区空间破坏
void test3()
{
	char src1[] = "yuanwei";
	char dest1[4] = { 0 };
	strcpy(dest1, src1);
	printf("%s\n", dest1); //fatal
}
//4. 目标空间必须可变
void test4()
{
	char src1[] = "yuanwei";
	char dest1[20] = "zhendenoiuno";//常量字符串是不可修改的
	strcpy(dest1, src1);
	printf("%s\n", dest1); //fatal
}
//strcpy返回值是目标空间的起始地址
//有返回值是为了实现链式访问 printf("%s",strcpy(dest,src));
char* my_strcpy(char* dest, const char* src)
{
	assert(dest && src);
	char*  ret = dest;
	while(*dest ++ =*src++)//while判断的是每一次*dest,当最后一次被赋值为0时,退出循环
	{
		;
	}
	//while (*src != '\0')
	//{
	//	*dest++ = *src++;
	//}	
	//*dest = *src;//将最后的\0补上
	return ret;
}
//int main()
//{
//	test1();
//	return 0;
//}