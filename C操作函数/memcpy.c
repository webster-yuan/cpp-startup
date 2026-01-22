#include<stdio.h>
#include<assert.h>
#include<string.h>
//返回目标空间的起始地址
//强转为char*主要是为了一个字节一个字节的从src拷贝到dest空间中
void* my_memcpy(void* dest, const void* src, size_t count)
{
	assert(dest && src);
	void* ret = dest;
	while (count--)
	{
		*(char*)dest = *(char*)src;
		dest = (char*)dest + 1;	//dest无法++,只能采用(char*)dest+1的方式
		src = (char*)src + 1;
	}
	return ret;
}
void test_memcpy1()
{
	int arr1[10] = { 1,2,3,4,5,6,7,8,9,0 };
				//   1 2 1 2 3 4 5 8 9 0------目标效果
				//   1 2 1 2 1 2 1 8 9 0------实际效果,因为memcpy无法处理内存重叠的情况
	my_memcpy(arr1+2,arr1,sizeof(arr1[0])*5);
}
void test_memcpy2()
{
	int arr1[10] = {1,2,3,4,5,6,7,8,9,0};
	int arr2[5] = {0};
	my_memcpy(arr2,arr1,sizeof(arr1[0])* 5);//count 代表多少个字节
}
//int main()
//{
//	test_memcpy1();
//	return 0;
//}