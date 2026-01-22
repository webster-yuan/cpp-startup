#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<assert.h>
void test_strcmp()
{
	char arr1[] = "yuanwei";
	char arr2[] = "xiaowei";
	if (arr1 < arr2) { ; }//这是在比较两个字符串的地址
	if ("yuanwei" < "xiaowei") { ; } //是在比较两个字符串的地址
}
//比较的是两个字符串,对应位置上的字符的大小,ASCII码值.
//遇到不同或者\0终止
//返回值是int,ret==0,二者相同,ret<0,前小于后;
int my_strcmp(char* str1, char* str2)
{
	while (*str1 == *str2)
	{
		if (*str1 == '\0')
			return 0;
		str1++;
		str2++;
	}
	if (*str1 > *str2)
		return 1;
	else
		return -1;
	//return *str1 - *str2;
}