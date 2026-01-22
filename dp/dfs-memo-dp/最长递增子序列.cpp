#include<iostream>
#include<vector>
using namespace std;
class Solution1
{
    int n;
public:
    //鎬濊矾: 鍙兘鏄互浠绘剰浣嶇疆涓鸿捣鐐?寰楀埌鏈€闀跨殑搴忓垪闀垮害,鎵€浠?
    //1. dfs瑕佹湁int 杩斿洖鍊?浠ｈ〃浠涓鸿捣鐐圭殑鏈€闀垮簭鍒楅暱搴?
    //瀛愰棶棰? 寰楀埌涓€涓笅鏍噄,閬嶅巻浠巌+1寮€濮嬫瘮浠栧ぇ鑳藉鏀惧湪i鍚庨潰鐨勫€?缁勬垚寰堝瀛愬簭鍒?璁板綍鏈€闀跨殑閭ｄ釜
    //鍥炴函: 娌℃湁鍥炴函
    //鍓灊: 娌℃湁鍓灊,濡傛灉鑳藉鏀逛负璁板繂鍖栨悳绱?鍓灊灏辨槸灏嗗凡缁忔煡鎵剧殑浠涓哄ご鐨勬渶闀块暱搴︽坊鍔犺繘澶囧繕褰?
    //鍑哄彛: 
    int lengthOfLIS(vector<int>& nums)
    {
        n = nums.size();
        int ret = 0;
        for (int i = 0; i < n; i++)
        {
            ret = max(ret, dfs(nums, i));
        }
        return ret;
    }
    //浠涓哄紑澶寸殑鏈€闀垮簭鍒?鏈夊緢澶氬簭鍒?浣犲緱璁板綍鏈€澶х殑閭ｄ釜
    int dfs(vector<int>& nums, int index)
    {
        int ret = 1;
        for (int i = index + 1; i < n; i++)
        {
            if (nums[i] > nums[index])
                ret = max(ret, dfs(nums, i) + 1);
        }
        return ret;
    }
};
class Solution2
{
    int n;
public:
//浠ユ墍鏈夊€间负璧风偣,鍙兘杈炬垚鐨勬渶闀块€掑瀛愬簭鍒?ret 璁板綍杩斿洖鏈€澶у€?
//瀛愰棶棰?鍐崇瓥鏍? 浠ndex涓鸿捣鐐?鐩镐俊dfs()鑳藉澶勭悊濂戒粠index+1涔嬪悗鐨勬墍鏈夊瓙搴忓垪闀垮害,鐒跺悗鍦ㄨ繑鍥炵粨鏋滀箣涓婂姞涓婃垜1涓?浣嗘槸瑕佽褰曟墍鏈夊瓙搴忓垪涓暱搴︽渶澶у€?鎵€浠ヨ鏈?int 杩斿洖鍊?dfs(int index)
//闇€瑕侀亶鍘唅ndex+1 涔嬪悗鐨?姣擺index]澶х殑鍊?鎷兼帴鍦ㄥ悗闈㈡墍鑳藉舰鎴愮殑鏈€闀垮瓙搴忓垪,
//鍒ゆ柇鏄惁鑳芥敼涓鸿蹇嗗寲鎼滅储: 鎴戜滑鍙戠幇,浠ユ煇涓€涓暟涓鸿捣鐐圭殑dfs()杩囩▼澶ч噺閲嶅
    int lengthOfLIS(vector<int>& nums) 
    {
        n=nums.size();
        vector<int> memo(n);
        int ret=0;
        for(int i=0;i<n;i++)
        {
            ret= max(ret,dfs(nums,i,memo));
        }
        return ret;
    }
    int dfs(vector<int>&nums,int index,vector<int>&memo)
    {
        if(memo[index]) return memo[index];

        int ret=1;
        for(int i=index+1;i<n;i++)
        {
            if(nums[i]>nums[index])
            {
                ret = max(ret,dfs(nums,i,memo)+1);
            }
        }
        memo[index]=ret;
        return memo[index];
    }
};

class Solution3
{
    int n;
public:
    //鎬濊矾: 鍙兘鏄互浠绘剰浣嶇疆涓鸿捣鐐?寰楀埌鏈€闀跨殑搴忓垪闀垮害,鎵€浠?
    //1. dfs瑕佹湁int 杩斿洖鍊?浠ｈ〃浠涓鸿捣鐐圭殑鏈€闀垮簭鍒楅暱搴?
    //瀛愰棶棰? 寰楀埌涓€涓笅鏍噄,閬嶅巻浠巌+1寮€濮嬫瘮浠栧ぇ鑳藉鏀惧湪i鍚庨潰鐨勫€?缁勬垚寰堝瀛愬簭鍒?璁板綍鏈€闀跨殑閭ｄ釜
    //鍥炴函: 娌℃湁鍥炴函
    //鍓灊: 娌℃湁鍓灊,濡傛灉鑳藉鏀逛负璁板繂鍖栨悳绱?鍓灊灏辨槸灏嗗凡缁忔煡鎵剧殑浠涓哄ご鐨勬渶闀块暱搴︽坊鍔犺繘澶囧繕褰?
    //鍑哄彛: 
    //鏀瑰姩褰? 
    //dp鏁扮粍涓褰曠殑鏄褰曚互i涓哄紑澶寸殑瀛愬簭鍒楃殑鏈€闀跨殑闀垮害,瑕佹渶澶у€?灏遍渶瑕乺et=max(ret,dp[i])鎵惧埌鏈€澶у€艰繑鍥?
    //1. 寮€绌洪棿澶у皬 n,
    //2. 濉〃椤哄簭,濉玦=1鐨勬渶闀垮瓙搴忓垪闀垮害dp[1],鍦ㄩ€掑綊鍒颁笅涓€灞傛椂,闇€瑕乮=3鐨刣p鍊?鎵€浠ュ～琛ㄩ『搴忔槸鍏堟妸鍚庨潰鐨勫～濂?浠庡彸寰€宸﹀～
    int lengthOfLIS(vector<int>& nums)
    {
        n = nums.size();
        vector<int>dp(n, 1);//鑷冲皯鏄嚜宸辨湁涓€涓?鎵€浠ラ兘鍒濆鍖栦负1
        int ret = 0;
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (nums[j] > nums[i])
                {
                    dp[i] = max(dp[i], dp[j] + 1);//鑷韩澶?杩樻槸鍚庨潰鐨勭粍鎴愬瓙搴忓垪闀垮害+鎴戣嚜宸?澶?
                }
            }
            ret = max(ret, dp[i]);
        }
        return ret;
    }
};