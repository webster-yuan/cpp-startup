#include<stdio.h>
#include<stdlib.h>

int g_val1 = 10;
int g_val2;
//int main()
//{
//	printf("代码区:%p\n",main);
//	const char* str = "yuanweinb";
//	printf("字符常量区:%p\n",str);
//	printf("已初始化全局数据区:%p\n",&g_val1);
//	printf("未初始化全局数据区:%p\n",&g_val2);
//	int* ptr1 = (int*)malloc(sizeof(int)*10);
//	int* ptr2 = (int*)malloc(sizeof(int)*10);
//	int* ptr3 = (int*)malloc(sizeof(int)*10);
//	printf("堆区:%p\n", ptr1);
//	printf("堆区:%p\n", ptr2);
//	printf("堆区:%p\n", ptr3);
//	int a1 = 10;
//	int a2 = 10;
//	int a3 = 10;
//	printf("栈区:%p\n",&a1);
//	printf("栈区:%p\n",&a2);
//	printf("栈区:%p\n",&a3);
//	return 0;
//}