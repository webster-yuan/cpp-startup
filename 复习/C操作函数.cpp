#include<iostream>
#include<string.h>
#include<assert.h>
void test_memcmp()
{
	//在内存中按字节进行比较,跟大小端存储有关系
	int arr1[10] = { 1,2,3,4,5,6 };
	int arr2[10] = { 1,2,3,4,5,0x11223306 };
	printf("%d\n", memcmp(arr1, arr2, sizeof(arr1[0]) * 5));//0
	printf("%d\n", memcmp(arr1, arr2, sizeof(arr1[0]) * 6));//-1
	printf("%d\n", memcmp(arr1, arr2, sizeof(arr1[0]) * 5 + 1));//0,小端存储方式,06 和6这一字节是相等的
	printf("%d\n", memcmp(arr1, arr2, sizeof(arr1[0]) * 5 + 2));//-1
}
void test_memcpy()
{
	int arr1[10] = { 1,2,3,4 };
	int arr2[5] = { 0 };
	memcpy(arr2, arr1, sizeof(int) * 5);
}
void test_memmove()
{
	//专门处理内存重叠的情况
}
void test_memset()
{
	//以字节为单位,将所有都初始化为0
	int arr[10] = { 1,2,3,4,54 };
	memset(arr, 0, sizeof(arr));
}
/// <summary>
/// 以下是字符串系列
/// </summary>
void test_strcat()
{
	//字符串追加操作函数: 从dest的第一个\0开始替换
	char arr1[20] = "yuanwei";
	char arr2[40] = "yuanwei\0yuanwei";
	char src[] = "hello";
	strcat(arr1, src);
	strcat(arr2, src);
	printf("%s\n", arr1); //yuanweihello
	printf("%s\n", arr2);//yuanweihello
}
void test_strcmp()
{
	char arr1[] = "yuanwei";
	char arr2[] = "xiaowei";
	//字符数组名就是首元素地址
	if (arr1 < arr2) { ; }//这是在比较两个字符串的地址
	if ("yuanwei" < "xiaowei") { ; } //是在比较两个字符串的地址
	int ret = strcmp("yuanwei", "xiaoawei");
}
void test_strcpy()
{
	//1. dest必须是以\0为结尾的,尤其注意字符数组,从dest的\0开始
	char dest1[] = "yuawnei";
	char dest2[10] = {'a','b','c'};//不够的空间会自动补\0
	char dest3[] = { 'a','b','c' };//error
	char dest4[] = { 'a','b','c','\0'};
	//2. src会将自己的\0带过去
	//3. dest空间预留够大
	//4. dest必须是可变的字符串,不能是const char* 
	char dest1[20] = "zhendenoiuno";//常量字符串是不可修改的
}
void test_strerror()
{
	//根据错误码,打印出错误描述信息
	//优化之后的perror("diy")自定义打印信息
}
void test_strlen()
{
	//1. 读取到\0就终止,返回
	//2. 返回值是size_t类型,相减之后你认为是负数,起始被转化为一个很大的数字,注意使用
}
void test_strncat()
{
	//追加多少个的问题: 注意目标空间一定要充足
	//实现时,因为约定了个数,可能src的\0并没有输入到dest中,你就得手动补充一个\0
}
void test_strstr()
{
	//返回s2在s1中的起始位置,可以使用KMP算法
}
void test_strtok()
{
	//切割字符串
	//将分隔符位置改为\0,并将这个起始位置指针返回,得到切分出来的部分字符串
	//同时记录被切分的位置即被替换为\0的位置,然后下一次再从这个位置开始继续向后找下一个标记
	char arr[] = "yuanwei@yeah.net@12306.666";
	//因为切分的过程会将源数据更改,所以一般都是先生成一份拷贝进行操作
	char buffer[30] = { 0 };
	strcpy(buffer, arr);
	const char* sep = "@.";//分隔符是空格也是支持的
	//当第一次调用,传的是具体str指针
	char* str = strtok(buffer, sep);
	for (; str != NULL; str = strtok(NULL, sep))
	{
		//printf();
	}
	for (; str != NULL; str = strtok(NULL, sep))
	{
		printf("%s ", str);//yuanwei yeah net 12306 666
	}
}
int main()
{
	test_memcpy();
	system("pause");
	return 0;
}

namespace yuanwei
{
	char* my_strstr(char* str1, char* str2)
	{
		assert(str1 && str2);
		char* s1 = str1, * s2 = str2;
		char* cur = s1;
		while (*cur)
		{
			while (*s1 == *s2)
			{
				s1++;
				s2++;
			}
			if (*s2 == '\0')//如果已经相等到了结尾
				return cur;
			cur++;		//否则从下一个位置重新开始匹配
			s1 = cur;
			s2 = str2;
		}
	}
	char* my_strnpy(char* dest, char* src, int count)
	{
		assert(dest && src);
		char* ret = dest;
		while (count-- && (*dest++ = *src++))
		{
			;
		}
		//src结束了,但是还没够count个就会手动补0
		while (count-- > 0)
			*dest++ = '\0';
		return ret;
	}
	int strncmp(const char* s1, const char* s2,int count)
	{
		assert(s1 && s2);
		while (*s1 == *s2 && count--)
		{
			if (*s1 == '\0')
				return 0;
			s1++; s2++;
		}
		if (count == 0)return 0;
		else
			return *s1 - *s2;
	}
	char* my_strncat(char* dest,char* src,int count)
	{
		assert(dest && src);
		char* ret = dest;
		//寻找第一个\0
		while (*dest++) { ; }
		while (count-- && *src!='\0')
		{
			*dest = *src;
			dest++, src++;
		}
		*dest = '\0';
		return ret;
	}
	size_t my_strlen(char* s)
	{
		assert(s);
		int count = 0;
		while (*s)
		{
			count++;
			s++;
		}
	}
	char* my_strcpy(char* dest, char* src)
	{
		assert(dest && src);
		char* ret = dest;
		while (*dest++ = *src++)
		{
			;
		}
		return ret;
	}
	int my_strcmp(const char* s1, const char* s2)
	{
		while (*s1 == *s2)
		{
			if (*s1 == '\0')//一直相同到结尾的情况,就是相等,在这里返回
				return 0;
			s1++;
			s2++;
		}
		//出来意味着并不相同
		return *s1 - *s2;
	}
	char* my_strcat(char* dest, char* src)
	{
		assert(dest && src);
		char* ret = dest;
		while (*dest != '\0')
		{
			dest++;
		}
		//while (*src != '\0')
		while(*dest++ = *src++)
		{
			//*dest++ = *src++;
			;
		}
		return ret;
	}
	void* my_memcpy(void* dest,void* src,size_t n)
	{
		assert(dest && src && n > 0);
		void* ret = dest;
		while (n--)
		{
			*(char*)dest = *(char*)src;//按照字节进行拷贝;
			dest = (char*)dest + 1;
			src = (char*)src + 1;
		}
		return ret;
	}
	void* my_memmove(void* dest, void* src, size_t count)
	{
		assert(dest && src);
		if (dest < src)//从前往后操作src
		{
			int index = 0;
			while (index < count)
			{
				*((char*)dest + index) = *((char*)src + index);
				index++;
			}
		}
		else
		{
			while (count--)
			{
				*((char*)dest + count) = *((char*)src + count);
			}
		}
		return dest;
	}
}