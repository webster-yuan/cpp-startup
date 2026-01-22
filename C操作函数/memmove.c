#include<stdio.h>
#include<assert.h>
#include<string.h>
//专门处理内存重叠的问题
// dest < src, 为了避免值的覆盖,src需要从前往后依次拷贝到dest上
// dest > src && (char*)dest< (char*)src + count, 为了避免值的覆盖,src需要从后往前依次拷贝到dest上
// (char*)dest >(char*)src + count,两块内存没有交集,怎么拷贝都行
void* my_memmemove(void* dest, const void* src, size_t count)
{
	assert(dest && src);
	void* ret = dest;
	//src从前往后
	if (dest < src)
	{
		while (count--)
		{
			*(char*)dest = *(char*)src;
			dest = (char*)dest + 1;
			src = (char*)src + 1;
		}
	}
	//从后往前,使用指针加偏移量的方式 ptr+ count 
	else
	{
		while (count--) // 随着count--,所指向的位置也在向前移动
		{
			*((char*)dest + count) = *((char*)src + count);
		}
	}
	return ret;
}
void test_memmove1()
{
	int arr1[10] = { 1,2,3,4,5,6,7,8,9,0 };
	//   1 2 1 2 5 6 7 8 9 0------目标效果,往后拷贝
	my_memmemove(arr1 + 2, arr1, sizeof(arr1[0]) * 2);
	int arr2[10] = { 1,2,3,4,5,6,7,8,9,0 };
	//   5 6 7 8 5 6 7 8 9 0------目标效果,往前拷贝
	my_memmemove(arr2, arr2+4, sizeof(arr2[0]) * 4);
}
//int main()
//{
//	test_memmove1();
//	system("pause");
//	return 0;
//}