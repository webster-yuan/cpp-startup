//https://leetcode.cn/problems/count-of-smaller-numbers-after-self/description/
class Solution 
{
    vector<int>counts;
    vector<int>tmp;
    vector<int>index;//璁板綍鏁版嵁鍘熷涓嬫爣
    vector<int>tmpIndex;//涓轰簡瀵逛笅鏍囩殑鍚堝苟浣跨敤涓存椂鏁扮粍
public:
//閲囩敤鍖洪棿闄嶅簭,鍏虫敞涓?left,mid)涓瓁鍊?鏌ョ湅(mid+1,right)涓槸鍚︽湁y<x,閭ｄ箞right-p2+1涓兘鏄瘮x灏忕殑
//鍦ㄤ袱涓尯闂撮檷搴忓悎骞朵箣鍚?鍏冪礌鐨勪笅鏍囬噸鏂板彉鍖?涓嬫爣鍙樹簡,涓嬩竴娆℃棤娉曞皢鍊兼斁鍒版纭殑浣嶇疆
//濡傛灉鐢ㄥ搱甯岃〃,閭ｄ箞濡傛灉鏈夐噸澶嶅厓绱犲嚭鐜?灏变細瀛樺湪鍊肩殑瑕嗙洊,鍑虹幇闂
//鎵€浠ュ啓涓猧ndex鏁扮粍璁板綍鏁版嵁鍘熷鐨勪笅鏍?鍦ㄦ暟鎹Щ鍔ㄧ殑杩囩▼涓?涓嬫爣涔熻窡鐫€绉诲姩,鏁版嵁闇€瑕乼mp鏁扮粍,閭ｄ箞涓嬫爣涔熼渶瑕佷竴涓猼mpIndex绉诲姩
//涓€涓暟鎹殑涓嬫爣鍜屾暟鎹Щ鍔ㄥソ浜嗕箣鍚?鎵嶅彲浠++,p1++,p2++
    vector<int> countSmaller(vector<int>& nums) 
    {
        int n=nums.size();
        counts.resize(n);
        tmp.resize(n);
        tmpIndex.resize(n);
        index.resize(n);
        for(int i=0;i<n;i++)
            index[i]=i;

        merageSort(nums,0,n-1);
        return counts;
    }
    void merageSort(vector<int>&nums,int left,int right)
    {
        if(left>=right)return ;
        int mid=(right-left)/2+left;
        merageSort(nums,left,mid);
        merageSort(nums,mid+1,right);
        //鍚庡簭閬嶅巻
        int p1=left,p2=mid+1,i=0;
        while(p1<=mid && p2<=right)//鍖洪棿闄嶅簭鏁扮粍
        {
            if(nums[p1]>nums[p2])
            {
                
                counts[index[p1]] += right-p2+1;//闅忕潃鍚堝苟涔嬪悗涓嬫爣鐨勯噸鏂板垎閰?count璁℃暟涓嬫爣鍑虹幇鍙樻崲
                tmpIndex[i]=index[p1];
                tmp[i++]=nums[p1++];
            }
            else
            {
                tmp[i]=nums[p2];
                tmpIndex[i++]=index[p2++];
            }
        }
        while(p1<=mid) tmpIndex[i]=index[p1],tmp[i++]=nums[p1++];
        while(p2<=right) tmpIndex[i]=index[p2],tmp[i++]=nums[p2++];
        for(int i=left;i<=right;i++)
            nums[i]=tmp[i-left],index[i]=tmpIndex[i-left];
    }
};