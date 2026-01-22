
//浠ユ煇涓€涓綅缃负璧风偣杩涜鎬濊€冪殑
class Solution 
{
    int ret;
    int m,n;
public:
//瀛愰棶棰? 鍒拌揪i,j浣嶇疆鏃?鑳介€夋嫨寰€涓嬭蛋,寰€鍙宠蛋,绱璺緞鍜?鍒拌揪缁堢偣鏃舵洿鏂版渶灏忚矾寰勫拰
//鍥炴函:鎭㈠鐜板満:閲囩敤鐨勬槸褰㈠弬,鍥炲埌涓婁竴灞傝嚜鍔ㄦ仮澶嶆垚鍔?
//鍓灊:鏃?
//鍒ゆ柇鏄惁鑳芥敼鎴愯蹇嗗寲鎼滅储: 鍙兘鍒拌揪鍚屼竴i,j浣嶇疆杩涜鐩稿悓鐨勬搷浣?
//鏉ュ埌杩欎釜浣嶇疆鏃跺垽鏂?杩斿洖鍊兼椂璁板綍
    int minPathSum(vector<vector<int>>& grid) 
    {
        ret=INT_MAX;
        m=grid.size(),n=grid[0].size();
        dfs(grid,0,0,grid[0][0]);
        return ret;
    }
    void dfs(vector<vector<int>>&grid,int i,int j,int path)
    {
        if(i==m-1 && j==n-1)
        {
            ret=min(ret,path);
            return;
        }
        if(i+1 <m)
            dfs(grid,i+1,j,path+grid[i+1][j]);
        if(j+1<n)
            dfs(grid,i,j+1,path+grid[i][j+1]);
    }
};
//浠ユ煇涓€涓綅缃负缁堢偣鏀圭殑璁板繂鍖栨悳绱㈢殑鏂规硶
class Solution 
{
    int m,n;
    vector<vector<int>>memo;
public:
//瀛愰棶棰? i,j浣嶇疆鍙兘鏄粠涓?宸︽潵鍒拌繖涓綅缃殑,鐩镐俊dfs鍑芥暟鑳藉鍦ㄦ垜缁欏畾杩欎袱涓€夋嫨涔嬪悗,杩斿洖鍒拌揪鎴戠殑鏈€灏忚矾寰勫拰,鐒跺悗鎴戝姞涓婅嚜宸卞氨鏄渶灏忚矾寰勫拰.
//鎵€浠ュ湪杩斿洖鐨勬椂鍊欏埆蹇樹簡鎶婅嚜宸卞姞涓婂啀杩斿洖
//鍥炴函:鏃?
//
    int minPathSum(vector<vector<int>>& grid) 
    {
        m=grid.size(),n=grid[0].size();
        memo= vector<vector<int>>(m,vector<int>(n));
        int ret=dfs(grid,m-1,n-1);
        return ret;
    }
    int dfs(vector<vector<int>>&grid,int i,int j)
    {
        if(memo[i][j]!=0) return memo[i][j];

        if(i==0 && j==0 )
        {
            memo[i][j]=grid[i][j];
            return memo[i][j];
        }
        //鏌愪竴涓妭鐐?鎴戠敤dfs鑾峰彇鍒颁袱鏉″埌杈捐嚜宸辩殑璺緞鍜?閫夋嫨灏忕殑鍚戜笂杩斿洖
        int p1=INT_MAX,p2=INT_MAX;
        if(i-1>=0)
            p1 = dfs(grid,i-1,j);
        if(j-1>=0)
            p2 = dfs(grid,i,j-1);
        
        memo[i][j]= min(p1,p2)+grid[i][j];
        return memo[i][j];
    }
};
//鏀圭殑鍔ㄦ€佽鍒?
class Solution 
{
    int m,n;
    vector<vector<int>>memo;
public:
//瀛愰棶棰? i,j浣嶇疆鍙兘鏄粠涓?宸︽潵鍒拌繖涓綅缃殑,鐩镐俊dfs鍑芥暟鑳藉鍦ㄦ垜缁欏畾杩欎袱涓€夋嫨涔嬪悗,杩斿洖鍒拌揪鎴戠殑鏈€灏忚矾寰勫拰,鐒跺悗鎴戝姞涓婅嚜宸卞氨鏄渶灏忚矾寰勫拰.
//鎵€浠ュ湪杩斿洖鐨勬椂鍊欏埆蹇樹簡鎶婅嚜宸卞姞涓婂啀杩斿洖
//鍥炴函:鏃?
//鍔ㄦ€佽鍒? 
//1. 寮€杈熺┖闂村ぇ灏?(m,n),涓轰簡灏嗙涓€琛?绗竴鍒楀垵濮嬪寲骞跺埌鏁翠綋杩愮畻涓?閲囧彇澶氬紑涓€琛?澶氬紑涓€鍒楃殑鏂瑰紡.鍒濆鍖栦笉褰卞搷鍚庣画+璁块棶grid鏃舵敞鎰忎笅鏍囧彉鎹?
//2. 濉〃椤哄簭 浠庡乏涓婂～鍒板彸涓?
//3. 鍒濆鍖? dp[0][0]=grid[0][0]
    int minPathSum(vector<vector<int>>& grid) 
    {
        m=grid.size(),n=grid[0].size();
        vector<vector<int>>dp(m+1,vector<int>(n+1,INT_MAX));
        dp[0][1]=0;
        for(int i=1;i<=m;i++)
        {
            for(int j=1;j<=n;j++)
            {
                dp[i][j]=min(dp[i-1][j],dp[i][j-1])+grid[i-1][j-1];
            }
        }
        return dp[m][n];
        // memo= vector<vector<int>>(m,vector<int>(n));
        // int ret=dfs(grid,m-1,n-1);
        // return ret;
    }
    int dfs(vector<vector<int>>&grid,int i,int j)
    {
        if(memo[i][j]!=0) return memo[i][j];

        if(i==0 && j==0 )
        {
            memo[i][j]=grid[i][j];
            return memo[i][j];
        }
        //鏌愪竴涓妭鐐?鎴戠敤dfs鑾峰彇鍒颁袱鏉″埌杈捐嚜宸辩殑璺緞鍜?閫夋嫨灏忕殑鍚戜笂杩斿洖
        int p1=INT_MAX,p2=INT_MAX;
        if(i-1>=0)
            p1 = dfs(grid,i-1,j);
        if(j-1>=0)
            p2 = dfs(grid,i,j-1);
        
        memo[i][j]= min(p1,p2)+grid[i][j];
        return memo[i][j];
    }
};