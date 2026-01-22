//瀛樺湪鐤戦棶: 涓轰粈涔堜竴瀹氳灏哾[i][j]褰撲綔鏄鍖?dfs()杩斿洖浣滀负鎵€闇€瑕佺殑琛€閲?鐒跺悗dfs-d[i][j],涓轰粈涔堜笉鏄??
//鎷撳睍鍒版璐熸暟閮藉瓨鍦ㄧ殑棰樻椂鎬庝箞鍔?
//鐤戦棶瑙ｇ瓟: x+d[i][j]浠ｈ〃缁忚繃杩欎釜鐐逛箣鍚庣殑琛€閲?浣犱篃璇村埌浜嗘璐熸暟閮藉瓨鍦?+璐熸暟涓嶅氨鏄閲?鍚?+姝ｆ暟涓嶅氨鏄閲?鍚?
//dfs()杩斿洖鍊间笉灏辨槸涓や釜閫夋嫨涔嬪悗鐨刴in-杩欎釜鐐瑰甫鏉ョ殑褰卞搷鍚?
//鍙兘浠ユ煇涓偣涓鸿捣鐐?
class Solution 
{
    int m;
    int n;
public:
//瀛愰棶棰?缁欏畾dfs涓€涓柟鍚?鎴戠浉淇fs鑳界粰鎴戣繑鍥炰粠杩欎釜鍒拌揪缁堢偣鎵€闇€瑕佺殑鏈€灏忕殑琛€閲忔秷鑰?閫夋嫨涓ょ涓殑杈冨皬鍊?+浠巌,j浣嶇疆閫氳繃鐨勬秷鑰?灏辨槸浠巌,j浣嶇疆鍒拌揪缁堢偣鐨勬秷鑰?
//d鍊煎彲姝ｅ彲璐?瀵艰嚧浠巌,j鐐归€氳繃鏃跺凡缁忔浜?琛€閲忎笉鑳藉皬浜?锛屽洜姝よ鍜?鍙栦釜max(鍑暐杩欎箞澶勭悊)
    int calculateMinimumHP(vector<vector<int>>& dungeon) 
    {
        m=dungeon.size(),n=dungeon[0].size();
        int ret= dfs(dungeon,0,0);
        return ret;
    }
    int dfs(vector<vector<int>>& d,int i,int j)
    {
        if(i==m-1 && j==n-1)
            return max(1-d[i][j],1);//淇濊瘉娲荤殑鏈€灏忓€煎氨鏄?
        int p1=INT_MAX,p2=INT_MAX;
        if(i+1<m)
            p1=dfs(d,i+1,j);
        if(j+1<n)
            p2=dfs(d,i,j+1);
        int tmp=min(p1,p2)-d[i][j];
        return max(tmp,1);
    }
};

class Solution 
{
    int m;
    int n;
    vector<vector<int>>memo;
public:
//瀛愰棶棰?缁欏畾dfs涓€涓柟鍚?鎴戠浉淇fs鑳界粰鎴戣繑鍥炰粠杩欎釜鍒拌揪缁堢偣鎵€闇€瑕佺殑鏈€灏忕殑琛€閲忔秷鑰?閫夋嫨涓ょ涓殑杈冨皬鍊?+浠巌,j浣嶇疆閫氳繃鐨勬秷鑰?灏辨槸浠巌,j浣嶇疆鍒拌揪缁堢偣鐨勬秷鑰?
//d鍊煎彲姝ｅ彲璐?瀵艰嚧浠巌,j鐐归€氳繃鏃跺凡缁忔浜?琛€閲忎笉鑳藉皬浜?锛屽洜姝よ鍜?鍙栦釜max(鍑暐杩欎箞澶勭悊)
    int calculateMinimumHP(vector<vector<int>>& dungeon) 
    {
        m=dungeon.size(),n=dungeon[0].size();
        memo=vector<vector<int>>(m,vector<int>(n));
        int ret= dfs(dungeon,0,0);
        return ret;
    }
    int dfs(vector<vector<int>>& d,int i,int j)
    {
        if(memo[i][j]!=0) return memo[i][j];

        if(i==m-1 && j==n-1)
        {
            memo[i][j]=max(1-d[i][j],1);
            return memo[i][j];
        }
        int p1=INT_MAX,p2=INT_MAX;
        if(i+1<m)
            p1=dfs(d,i+1,j);
        if(j+1<n)
            p2=dfs(d,i,j+1);
        int tmp=min(p1,p2)-d[i][j];
        memo[i][j]=max(tmp,1);
        return memo[i][j];
    }
};


class Solution 
{
    int m;
    int n;
    vector<vector<int>>memo;
public:
//瀛愰棶棰?缁欏畾dfs涓€涓柟鍚?鎴戠浉淇fs鑳界粰鎴戣繑鍥炰粠杩欎釜鍒拌揪缁堢偣鎵€闇€瑕佺殑鏈€灏忕殑琛€閲忔秷鑰?閫夋嫨涓ょ涓殑杈冨皬鍊?+浠巌,j浣嶇疆閫氳繃鐨勬秷鑰?灏辨槸浠巌,j浣嶇疆鍒拌揪缁堢偣鐨勬秷鑰?
//d鍊煎彲姝ｅ彲璐?瀵艰嚧浠巌,j鐐归€氳繃鏃跺凡缁忔浜?琛€閲忎笉鑳藉皬浜?锛屽洜姝よ鍜?鍙栦釜max(鍑暐杩欎箞澶勭悊)
    int calculateMinimumHP(vector<vector<int>>& dungeon) 
    {
        m=dungeon.size(),n=dungeon[0].size();
        vector<vector<int>> dp(m+1,vector<int>(n+1,INT_MAX));
        dp[m][n-1]=1;
        for(int i=m-1;i>=0;i--)
        {
            for(int j=n-1;j>=0 ;j--)
            {
                dp[i][j]=min(dp[i+1][j],dp[i][j+1])-dungeon[i][j];
                dp[i][j]=max(dp[i][j],1);
            }
        }
        return dp[0][0];
        // memo=vector<vector<int>>(m,vector<int>(n));
        // int ret= dfs(dungeon,0,0);
        // return ret;
    }
    int dfs(vector<vector<int>>& d,int i,int j)
    {
        if(memo[i][j]!=0) return memo[i][j];

        if(i==m-1 && j==n-1)
        {
            memo[i][j]=max(1-d[i][j],1);
            return memo[i][j];
        }
        int p1=INT_MAX,p2=INT_MAX;
        if(i+1<m)
            p1=dfs(d,i+1,j);
        if(j+1<n)
            p2=dfs(d,i,j+1);
        int tmp=min(p1,p2)-d[i][j];
        memo[i][j]=max(tmp,1);
        return memo[i][j];
    }
};