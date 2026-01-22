#include<stdio.h>
#include<string.h>
#include<assert.h>
//用法:遇到\0终止,计算字符串长度
void test_strlen1()
{
	//str1 结尾默认是\0
	char str1[] = "yuanwei";
	printf("%d\n",strlen(str1));//7
	//str2结尾并没有\0,strlen会一直往后读,直到读到\0,但是那是什么非法位置就不知道了
	char str2[] = {'a','b','c','d'};
	printf("%d\n", strlen(str2));//122,随机值,每回都可能不一样

	//str3,元素中包含一个'\0',读到就终止
	char str3[] = { 'a','b','c','d','\0'};
	printf("%d\n", strlen(str3));//4

	//str5,'\0'后面元素是读不到的
	char str5[] = { 'a','b','c','d','\0','a','c'};
	printf("%d\n", strlen(str5));//4

	//str4 开10个字节大小空间,但是初始化时只有4个,那么默认剩下的6个地方都是填充的\0
	char str4[10] = {'a','b','c','d'};
	printf("%d\n", strlen(str4));//4
}
//返回值是size_t 类型
void test_strlen2()
{
	//error use case1: 返回值是size_t 类型,无符号整数,相减之后不是负数而是一个很大的正数 
	if (strlen("abcd") - strlen("bcdefg") > 0)
		printf(">\n");//打印的是>
	else 
		printf("<=\n");
	//correct use case2:
	if (strlen("abcd") > strlen("bcdefg"))
		printf(">\n");
	else
		printf("<=\n");//打印的是<=

	//correct use case3:
	if ((int)strlen("abcd") - (int)strlen("bcdefg") >0)
		printf(">\n");
	else
		printf("<=\n");//打印的是<=
}
size_t my_strlen(const char* str)
{
	int count = 0;
	assert(str != NULL);
	while (*str != '\0')
	{
		count++;
		str++;
	}
	return count;
}
//int main()
//{
//	test_strlen2();
//	return 0;
//}