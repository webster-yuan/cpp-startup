#include<stdio.h>
#include<assert.h>
#include<string.h>
//按字节进行比较
void test_mermcpy()
{
	int arr1[10] = {1,2,3,4,5,6};
	int arr2[10] = { 1,2,3,4,5,0x11223306 };
	printf("%d\n",memcmp(arr1, arr2, sizeof(arr1[0]) * 5));//0
	printf("%d\n",memcmp(arr1, arr2, sizeof(arr1[0]) * 6));//-1
	printf("%d\n",memcmp(arr1, arr2, sizeof(arr1[0]) * 5 + 1));//0,小端存储方式,06 和6这一字节是相等的
	printf("%d\n",memcmp(arr1, arr2, sizeof(arr1[0]) * 5 + 2));//-1
}
//int main()
//{
//	test_mermcpy();
//	return 0;
//}