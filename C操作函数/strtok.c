#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<assert.h>
//切割字符串
//将分隔符位置改为\0,并将这个起始位置指针返回,得到切分出来的部分字符串
//同时记录被切分的位置即被替换为\0的位置,然后下一次再从这个位置开始继续向后找下一个标记
//肯定使用了静态变量进行记录指针了,
void test_strtok()
{
	char arr[] = "yuanwei@yeah.net@12306.666";
	//因为切分的过程会将源数据更改,所以一般都是先生成一份拷贝进行操作
	char buffer[30] = { 0 };
	strcpy(buffer, arr);
	const char* sep = "@.";//分隔符是空格也是支持的
	//当第一次调用,传的是具体str指针
	char* str = strtok(buffer,sep);
	for (; str != NULL; str = strtok(NULL, sep))
	{
		printf("%s ",str);//yuanwei yeah net 12306 666
	}
}
//int main()
//{
//	test_strtok();
//	return 0;
//}