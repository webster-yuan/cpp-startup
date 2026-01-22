#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<assert.h>

void test_strncmp()
{
	char str[20] = "yuanwei";
	char str2[] = "yuanxin";
	printf("%d\n",strncmp(str, str2, 4));
}
int my_strncmp(const char* str1, const char* str2, size_t n)
{
	assert(str1 && str2);
	while (*str1 == *str2 && n > 0)
	{
		if (*str1 == '\0')
			return 0;
		str1++;
		str2++;
		n--;
	}
	//前n个相同,但是*str!=nulltr
	if (n == 0) return 0;
	else if (*str1 > *str2) return 1;
	else if (*str1 < *str2) return -1;
}