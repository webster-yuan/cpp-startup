//https://leetcode.cn/problems/satisfiability-of-equality-equations/description/
class Solution 
{
    private:
    vector<int>ufs;
public:
//鍥犱负涓嶅悓鍙橀噺涔嬮棿鐩哥瓑鍏锋湁鍙紶閫掓€?鎵€浠ュ皢鐩哥瓑鐨勬暟瀛楁斁鍒板悓涓€闆嗗悎褰撲腑,鍒ゆ柇鏍硅妭鐐规槸鍚︾浉鍚屾潵浠ｆ浛瀹炵幇鍒ゆ柇
    int FindRoot(int x)
    {
        while(ufs[x]>=0)
            x=ufs[x];
        return x;
    }
    bool equationsPossible(vector<string>& nums) 
    {
        //澶氬皯涓彉閲?  nums[i][0] nums[i][3]
        //鍥犱负閮芥槸灏忓啓鐨勫瓧姣?鎵€浠ユ渶澶т笉瓒呰繃26
        ufs=vector<int>(26,-1);
        int n=nums.size();
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<4;j++)
            {
                if(nums[i][1] == '=')//鐩哥瓑,杩涜鍚堝苟鎿嶄綔
                {
                    int ai =nums[i][0] - 'a',bi=nums[i][3]-'a';
                    int root1 =FindRoot(ai);
                    int root2 =FindRoot(bi);
                    if(root1!=root2)
                    {
                        ufs[root1]+=ufs[root2];
                        ufs[root2]=root1;
                    }
                }
            }
        }
        //鎵句笉鐩稿悓鐨?鐪嬫槸鍚︽槸涓嶅悓鑺傜偣
        for(auto& str: nums)
        {
            if(str[1] == '!')
            {
                    int ai =str[0] - 'a',bi=str[3]-'a';
                    int root1 =FindRoot(ai);
                    int root2 =FindRoot(bi);
                    if(root1==root2)
                        return false;
            }
        }
        return true;
    }
};