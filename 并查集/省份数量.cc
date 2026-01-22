//https://leetcode.cn/problems/bLyHh0/submissions/
class Solution 
{
    private:
    vector<int> ufs;
public:
    int FindRoot(int x)
    {
        while(ufs[x]>=0)
            x=ufs[x];
        return x;//杩斿洖澶寸殑涓嬫爣
    }
    int findCircleNum(vector<vector<int>>& arr) 
    {
        int n=arr.size();
        ufs= vector<int>(n,-1);//-1鐨勫惈涔? 姣忎竴涓妭鐐逛互鑷繁涓哄ご鐨勯泦鍚堜腑鍏冪礌涓暟灏辨槸鑷繁涓€涓?
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(arr[i][j] == 1)//i j涓ょ偣涔嬮棿瀛樺湪鐩歌繛鍏崇郴
                {
                    int root1 =FindRoot(i);
                    int root2 =FindRoot(j);
                    if(root1 !=root2)
                    {
                        ufs[root1] += ufs[root2];
                        ufs[root2]=root1;
                    }
                }
            }
        }
        int count=0;
        for(auto e:ufs)
            if(e<0)
                count++;
        return count;
    }
};