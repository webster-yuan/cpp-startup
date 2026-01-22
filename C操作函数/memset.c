#include<stdio.h>
#include<assert.h>
#include<string.h>
//将所有字节都设置为0,以字节为单位进行初始化的
//void *memset( void *dest, int c, size_t count );
void test_memset()
{
	int arr1[10] = { 1,2,3,4,5,6 };
	memset(arr1, 0, sizeof(int) * 6);
}

int main()
{
	test_memset();
	return 0;
}