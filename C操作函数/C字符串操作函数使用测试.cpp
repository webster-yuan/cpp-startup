#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
using namespace std;
//strcpy vs strncpy
void test1()
{
	const char* source = "hello world!";//后面默认携带\0
	char dest[20];						//将\0也填充了进去
	strcpy(dest,source);	//strcpy只会将source拷贝进dest中,到\0结尾.
	char dest3[5];
	//strcpy(dest3,source);	//dest3空间不够了,出现崩溃
	cout << "Copied string :" << dest << endl;

	char dest2[30];
	strncpy(dest2,dest,sizeof(source)); //source.size()< dest[20],将source.size个字符放到dest2后,不会默认添加\0,造成崩溃
	//所以最好用完strcnpy之后,手动在结尾处添加\0作为终结标志.注:大小位置size,下标从0开始的话就是size-1
	dest2[sizeof(source)-1]='\0';
	strncpy(dest2,dest,sizeof(dest)); //source.size()< dest[20],所以不够20的部分,strnpy将\0作为默认填充字符,补齐了说好的20个的空缺位置
	cout << "Copied string :" << dest2 << endl;
}
//memcpy vs memmove 
void test2()
{
	const char* source = "hello,world";
	char buffer[20];
	std::memcpy(buffer, source, std::strlen(source)+1);//strlen遇到\0中止,并且不会记录\0个数,所以要+1将\0带上,才是完整字符串
	cout << "memcpy string :" << buffer << endl;//memcpy string : hello, world
	

	char dest[20] = "hello,world";
	char* dest1 = buffer + 4;
	std::memmove(dest1,dest,strlen(dest)+1);
	cout << "memcnpy/memmove string :" << buffer << endl;//memcnpy / memmove string : hellhello, world
		
}
//split函数实现,使用strtok()函数
vector<string>mySplit(string& str,string& pattern)
{
	char* tmp = new char[str.size()+1];
	strcpy(tmp,str.c_str());
	vector<string>res;
	char* retStr = strtok(tmp,pattern.c_str());
	while (retStr != nullptr)
	{
		res.push_back(retStr);
		retStr = strtok(nullptr,pattern.c_str());
	}
	delete[] tmp;
	return res;
}
//int main()
//{
//	test2();
//}