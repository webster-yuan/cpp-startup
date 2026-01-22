#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<unordered_map>
using namespace std;
class Solution
{
private:
    unordered_map<string, vector<string>>hashMap;
public:
    void createTree(vector<string>& content)
    {
        string root = content[0];
        for (int i = 1; i < content.size(); i++)
        {
            string str = content[i];
            char ch = str[1];
            if (ch != '-')
            {
                hashMap[root].push_back(str);
            }
            else//插入二级目录时找他对应的一级目录
            {
                string index = hashMap[root].back();
                hashMap[index].push_back(str);
            }
        }
    }
    //每个节点都有相同的子问题,
    //先查看自己是否包含key关键字,包含,path+=str,不包含; 都走孩子节点遍历
    //然后再遍历自己的vector中每个节点是否包含
    //剪枝: 
    //void dfs(string str,string path)
    //{
    //    //if (isCon(str)) 造成只有包含key的非叶子节点才能打印
    //    //    path += str;
    //    path += str;//所有路径全部打印了
    //    if (hashMap[str].size() == 0)//到叶子节点
    //    {
    //        ans.push_back(path);
    //        return;
    //    }
    //    for (auto s : hashMap[str])
    //    {
    //        //if(isCon(s)) 分支不包含的直接不走了就错了
    //        //    dfs(s, path+s);
    //        dfs(s, path);
    //    }
    //    //恢复现场
    //    for (int i = 0; i < str.size(); i++)
    //        path.pop_back();
    //}
    bool dfs(string str, string path)
    {
        path += str;
        if (hashMap[str].size() == 0 && isCon(str))//到叶子节点并且包含key
        {
            ans.push_back(path);
            return true;
        }
        bool ret= false;
        for (auto s : hashMap[str])
        {
            ret=dfs(s, path);
        }
        //从该路径回来,发现并没有结果,将该路径添加的str目录分级删除
        if (!ret)
        {
            for (int i = 0; i < str.size(); i++)
                path.pop_back();
        }
    }
    bool isCon(string& s)
    {
        char* tmp = new char[s.size() + 1];
        strcpy(tmp, s.c_str());
        char* pos =strstr(tmp, key.c_str());
        if (pos == nullptr)
            return false;
        return true;
    }
    vector<string> find(string& keyword)
    {
        key = keyword;
        string root = "/root";
        string path;
        bool tmp = dfs(root, path);
        if (tmp)
        {
            vector<string>ret;
            for (int i = 0; i < ans.size(); i++)
            {
                if (!ans[i].empty())
                    ret.push_back(ans[i]);
            }
            return ret;
        }
        else
        {
            return {};
        }
    }
private:
    vector<string>ans;
    string key;
};
int main()
{
    std::string keyword;
    std::cin >> keyword; // 读取关键字
    int count = 0;
    std::cin >> count;
    std::vector<std::string> contents; // 每行的数据
    for (int i = 0; i < count; ++i) {
        std::string tmp;
        std::cin >> tmp;
        contents.push_back(tmp);
    }
    Solution s;
    s.createTree(contents);
    vector<string>ans = s.find(keyword);
    if (ans.size() == 0)
        cout << "No Files Found" << endl;
    else
    {
        for (auto e : ans)
        {
            cout << e << endl;
        }
    }
    return 0;
}
