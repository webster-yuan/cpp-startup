#include <iostream>
#include <vector>
#include<string.h>
using namespace std;
//dp[i][j]琛ㄧず[0,i]鍓峣涓墿鍝佸綋涓€讳綋绉笉瓒呰繃J鎵€鏈夐€夋硶涓兘杈惧埌鐨勬渶澶т环鍊?
//dp2[i][j]琛ㄧず[0,i]鍓峣涓墿鍝佸綋涓€讳綋绉伆濂戒负J鎵€鏈夐€夋硶涓兘杈惧埌鐨勬渶澶т环鍊?
const int N=1010;
int n,V;
int v[N],w[N];
int main() 
{
    cin>>n>>V;
    for(int i=1;i<=n;i++)
        cin>>v[i]>>w[i];
    vector<vector<int>>dp(n+1,vector<int>(V+1));
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=V;j++)
        {
            dp[i][j]=dp[i-1][j];
            if(j>=v[i])
                dp[i][j]=max(dp[i][j],dp[i][j-v[i]]+w[i]);
        }
    }
    cout<<dp[n][V]<<endl;
    vector<vector<int>>dp2(n+1,vector<int>(V+1));
    for(int i=1;i<=V;i++) dp2[0][i]=-1;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=V;j++)
        {
            dp2[i][j]=dp2[i-1][j];
            if(j>=v[i] && dp2[i][j-v[i]]!=-1)
                dp2[i][j]=max(dp2[i][j],dp2[i][j-v[i]]+w[i]);
        }
    }
    cout<<(dp2[n][V]==-1?0:dp2[n][V])<<endl;
}

#include <iostream>
#include <vector>
#include<string.h>
using namespace std;
//dp[i][j]琛ㄧず[0,i]鍓峣涓墿鍝佸綋涓€讳綋绉笉瓒呰繃J鎵€鏈夐€夋硶涓兘杈惧埌鐨勬渶澶т环鍊?
//dp2[i][j]琛ㄧず[0,i]鍓峣涓墿鍝佸綋涓€讳綋绉伆濂戒负J鎵€鏈夐€夋硶涓兘杈惧埌鐨勬渶澶т环鍊?
//绌洪棿浼樺寲,鍒╃敤婊氬姩鏁扮粍,渚濊禆浜庝笂涓€琛屼綅缃?浠ュ強杩欎竴琛屽墠闈㈢殑浣嶇疆,鎵€浠ラ『搴忛渶瑕佷粠宸﹀線鍙?
const int N=1010;
int n,V;
int v[N],w[N];
int main() 
{
    cin>>n>>V;
    for(int i=1;i<=n;i++)
        cin>>v[i]>>w[i];
    vector<int>dp(V+1);
    for(int i=1;i<=n;i++)
    {
        for(int j=v[i];j<=V;j++)
        {
            dp[j]=max(dp[j],dp[j-v[i]]+w[i]);
        }
    }
    cout<<dp[V]<<endl;
    vector<int>dp2(V+1);
    for(int i=1;i<=V;i++) 
        dp2[i]=-1;
    for(int i=1;i<=n;i++)
    {
        for(int j=v[i];j<=V;j++)
        {
            if(dp2[j-v[i]]!=-1)//鍒ゆ柇鏉′欢鐨勫瓨鍦ㄥ氨鏄负浜嗗湪鏃犳晥鏃朵笉鐢ㄧ浜屼釜鏉′欢,鍥犱负姹傜殑鏄痬ax鎵€浠ュ皢鍏?1鍒濆鍖栦负鏋佸皬
            dp2[j]=max(dp2[j],dp2[j-v[i]]+w[i]);
        }
    }
    cout<<(dp2[V]==-1?0:dp2[V])<<endl;
}

#include <iostream>
#include <vector>
#include<string.h>
using namespace std;
//dp[i][j]琛ㄧず[0,i]鍓峣涓墿鍝佸綋涓€讳綋绉笉瓒呰繃J鎵€鏈夐€夋硶涓兘杈惧埌鐨勬渶澶т环鍊?
//dp2[i][j]琛ㄧず[0,i]鍓峣涓墿鍝佸綋涓€讳綋绉伆濂戒负J鎵€鏈夐€夋硶涓兘杈惧埌鐨勬渶澶т环鍊?
//绌洪棿浼樺寲,鍒╃敤婊氬姩鏁扮粍,渚濊禆浜庝笂涓€琛屼綅缃?浠ュ強杩欎竴琛屽墠闈㈢殑浣嶇疆,鎵€浠ラ『搴忛渶瑕佷粠宸﹀線鍙?
const int N=1010;
int n,V;
int v[N],w[N];
int main() 
{
    cin>>n>>V;
    for(int i=1;i<=n;i++)
        cin>>v[i]>>w[i];
    vector<int>dp(V+1);
    for(int i=1;i<=n;i++)
    {
        for(int j=v[i];j<=V;j++)
        {
            dp[j]=max(dp[j],dp[j-v[i]]+w[i]);
        }
    }
    cout<<dp[V]<<endl;
    vector<int>dp2(V+1);
    for(int i=1;i<=V;i++) 
        dp2[i]=-0x3f3f3f3f;
    for(int i=1;i<=n;i++)
    {
        for(int j=v[i];j<=V;j++)
        {
            dp2[j]=max(dp2[j],dp2[j-v[i]]+w[i]);
        }
    }
    cout<<(dp2[V]<0?0:dp2[V])<<endl;
}