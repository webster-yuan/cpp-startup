//https://leetcode.cn/problems/zui-xiao-de-kge-shu-lcof/submissions/

class Solution 
{
public:
//1. 鎺掑簭涔嬪悗杩斿洖澶磌涓€?
//2. 浣跨敤鍫嗙殑鎬濇兂,O(nlogk)鍙兘澶勭悊鏃犻噸澶嶅€肩殑鎯呭喌,鏈夐噸澶嶅€艰繕闇€瑕佸啀鍫嗙殑鍩虹涓婂姞涓婅瘝棰戠粺璁?
//3. 蹇€熼€夋嫨绠楁硶,灏嗗墠k灏忕殑鏁拌繑鍥?浣嗘槸骞舵病鏈夎繘琛屾帓搴?
    vector<int> getLeastNumbers(vector<int>& arr, int k) 
    {
        sort(arr.begin(),arr.end());
        return {arr.begin(),arr.begin()+k};
    }
};

class Solution 
{
public:
//蹇€熼€夋嫨鎬濇兂: 鍖洪棿鍒掑垎涔嬪悗,鏈€灏忕殑K涓偗瀹氬凡缁忔斁鍦ㄤ簡鍖洪棿鏈€宸︿晶,杩涜鍖洪棿涓暟姣斿杩斿洖缁撴灉
    vector<int> getLeastNumbers(vector<int>& arr, int k) 
    {
        srand(time(NULL));
        qsort(arr,0,arr.size()-1,k);
        return {arr.begin(),arr.begin()+k};
    }
    void qsort(vector<int>& arr,int l,int r,int k)
    {
        if(l>=r)return;
        //鑾峰彇闅忔満鍊?鍒掑垎涓夊潡鍖哄煙
        int key=getRandom(arr,l,r);
        int i=l,less=l-1,more=r+1;
        while(i<more)
        {
            if(arr[i] >key) swap(arr[--more],arr[i]);
            else if(arr[i]<key) swap(arr[++less],arr[i++]);
            else i++;
        }
        //l,less less+1,more-1 more,r
        //姹傚嚭鍖哄煙鍏冪礌涓暟,鍦ㄩ€変腑鐨勫尯闂翠腑缁х画鍘昏皟鐢╭sort鍑芥暟鎵惧墠k涓厓绱?
        int a=less-l+1,b=more-less-1;
        if(k<=a) qsort(arr,l,less,k);  //灏嗗乏鍖洪棿涓墠k涓皬鐨?鏀惧埌鍖洪棿鍓嶉潰
        else if(k-a<=b) return ;    //姝ゆ椂鍓峩涓凡缁忔憜濂戒簡
        else qsort(arr,more,r,k-a-b);//鍒板彸鍖洪棿涓皢鍓╀笅鐨勫厓绱犱腑鍓峩-a-b涓斁鍒板彸鍖洪棿杈冨墠闈?
    }
    int getRandom(vector<int>&arr,int left,int right)
    {
        return arr[rand() % (right-left+1)+left];
    }
};