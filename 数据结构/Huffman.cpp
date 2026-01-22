#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<math.h>
#include<vector>
#include<stack>
#include<algorithm>
#include<sstream>
#include<iostream> 
#include<cstring>
#include<fstream>
using namespace std;
int find(char c)//根据字符寻找该字符在结构体数组的位置
{
	int i=-1;
	if(c>='a'&&c<='z')i=c-'a';
	if(c>='A'&&c<='Z')i=c-'A'+26;
	if(c==',')i=52;
	if(c=='.')i=53;
	if(c==' ')i=54;
	return i;
}
struct NODE
{
	char c;
	int v;//字符出现频率
	int idx;
	string code;
	struct NODE *l,*r;
};
vector<NODE* > node(55);
vector<NODE* > nodes(55);
string s="";
string str_code="";
void initnode()//初始化结构体数组
{
	int i;
	for(i=0;i<26;i++)
	{
		node[i]=new NODE;
		node[i]->c=i+'a';
		node[i]->v=0;
		node[i]->code=s;
		node[i]->l=NULL;
		node[i]->r=NULL;
	}
	for(i=26;i<52;i++)
	{
		node[i]=new NODE;
		node[i]->c=i-26+'A';
		node[i]->v=0;
		node[i]->code=s;
		node[i]->l=NULL;
		node[i]->r=NULL;
	}
	i=52;
	node[i]=new NODE;
	node[i]->c=',';
	node[i]->v=0;
	node[i]->code=s;
	node[i]->l=NULL;
	node[i]->r=NULL;
	i=53;
	node[i]=new NODE;
	node[i]->c='.';
	node[i]->v=0;
	node[i]->code=s;
	node[i]->l=NULL;
	node[i]->r=NULL;
	i=54;
	node[i]=new NODE;
	node[i]->c=' ';
	node[i]->v=0;
	node[i]->code=s;
	node[i]->l=NULL;
	node[i]->r=NULL;
	cout<<"哈夫曼编码程序"<<endl;
	cout<<"输入转码内容，以'#'结束"<<endl;
}
int top()//寻找权值最小的元素
{
	int i,n=114514,j=-1;
	for(i=0;i<node.size();i++)
	{
		if(node[i]->v<n)
		{
			n=node[i]->v;
			j=i;
		}
	}
	return j;
}
void pop()//将最小权值弹出去
{
	int i=top();
	node.erase(node.begin()+i);
}
void coding(NODE* t)//遍历生成的哈夫曼树生成编码
{
	if(!t)return;
	else
	{
		if(t->l)
		{
			t->l->code=t->code;
			t->l->code.push_back('0');
		}
		if(t->r)
		{
		    t->r->code=t->code;
			t->r->code.push_back('1');
		}
		coding(t->l);
		coding(t->r);
	}
}
void show(NODE* t)
{
	int i;
	if(!t)return;
	else
	{
		if(!t->l&&!t->r)
		{
			cout<<t->c<<"的编码:"<<t->code<<endl;//输出字符对应01编码
			i=find(t->c);
			nodes[i]=new NODE;
			nodes[i]=t;
		}
		show(t->l);
		show(t->r);
	}
}
char transcode(string ss)//翻译编码返回对应字符
{
	int i;
	for(i=1;i<nodes.size();i++)
	{
		if(nodes[i]->code==ss)
		{
			return nodes[i]->c;
		}
	}
	return '#';
}

void trans(string str)
{
	int i,j,l=str.length(),m;
	for(i=0;i<l;i++)
	{
		m=find(str[i]);
		str_code=str_code+nodes[m]->code;
	}
}
void transcoding(string ss)//转译原码
{
	string sss="";
	int i,j,l=ss.length();
	int n=0;
	char ch;
	for(i=0;i<l;i++)
	{
		sss.push_back(ss[i]);
		ch=transcode(sss);
		if(ch!='#')
		{
			n=i;
			s.push_back(ch);
			sss.clear();
		}
	}
}
int main()
{
	int i,j,l,m,h;
	initnode();
	string str;
	char c;
	for(;;)
	{
		cin>>c;
		if(c=='#')break;
		else
		{
			m=find(c);
		    node[m]->v++;
			str.push_back(c);
		}
	}
	
	NODE *t;
	for(;node.size()>1;)
	{
		i=top();
		t=new NODE;
		t->v=node[i]->v;
		t->l=node[i];
		t->code=s;
		pop();
		i=top();
		t->v=t->v+node[i]->v;
		t->r=node[i];
		pop();
		node.push_back(t);
	}
	coding(node[0]);
	show(node[0]);
	trans(str);
	cout<<str_code<<endl;
	ofstream file;
	file.open("files.txt", ios_base::out | ios_base::trunc);
	file<<str_code<<endl;
	file<<endl;
	for(i=0;i<nodes.size();i++)
	{
		file<<nodes[i]->c<<"的编码是:"<<nodes[i]->code<<endl;
	}
	file.close();
	cout<<endl;
	string ss;
	cout<<"输入原码:"<<endl;
	cin>>ss;
	cout<<"译码结果为:"<<endl;
	transcoding(ss);
	cout<<s<<endl;
	system("pause");
	return 0;
}