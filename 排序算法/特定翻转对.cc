//https://leetcode.cn/problems/reverse-pairs/submissions/
class Solution 
{
    vector<int>tmp;
    int ret;
public:
//褰掑苟鎺掑簭绛栫暐涓庣炕杞缁熻绛栫暐鐩稿乏,鍗硆et鏇存柊绛栫暐鍜屽尯闂存帓搴忕瓥鐣ヤ笉鍚?閲囩敤ret閫夋嫨绛栫暐鍙兘瀵艰嚧鍖洪棿鏁扮粍鍙樺緱鏃犲簭,浣嗘槸鎴戜滑鎯宠楂樻晥鐜囪绠楀鏁拌繕寰楅渶瑕佸尯闂村崟璋冩€?杩欐槸闂鎵€鍦?
//闇€瑕佸尯闂村崟璋冩€?鏉ヤ竴娆¤幏鍙栧涓炕杞,鍚屽悜鍙屾寚閽?涓€娆″悎骞跺崌绾т负O(n).涓€鍏監(logn)娆?=>O(nlogn)
//绛栫暐1:涓撴敞浜?left,mid)鍖洪棿涓殑x,鍦?mid+1,right)涓殑y,婊¤冻x>2*y,ret+=right-p2+1,閲囩敤鍖洪棿闄嶅簭
//绛栫暐2:涓撴敞浜?mid+1,right)鍖洪棿涓殑y,鍦?left,mid)鍖洪棿涓殑x,濡傛灉x/2 >y,ret+=mid-p1+1,閲囩敤鍖洪棿鍗囧簭
    int reversePairs(vector<int>& nums) 
    {
        int n=nums.size();
        tmp.resize(n);
        mergeSort(nums,0,n-1);
        return ret;
    }
    void mergeSort(vector<int>&nums,int left,int right)
    {
        if(left>=right)return ;

        int mid=(right-left)/2+left;
        mergeSort(nums,left,mid);
        mergeSort(nums,mid+1,right);
        int p1=left,p2=mid+1,i=0;
        //鍚庡簭鍒拌繖閲屽緱鍒颁袱涓湁搴忔暟缁?鍦ㄨ繖閲岃繘琛岀炕杞鐨勮绠?
        while(p1<=mid)
        {
            while(p2<=right && nums[p2]>=nums[p1]/2.0) p2++;//nums[p2]*2浼氬嚭鐜伴棶棰?
            if(p2>right) break;//娌℃壘鍒板氨涓嶇敤鎵句簡
            ret += right-p2+1;
            p1++;
        }
        //鍒繕浜嗗皢涓や釜鍖洪棿澶存寚閽堟洿鏀瑰洖鏉?杩涜鍖洪棿鏁板€煎悎骞?
        p1=left,p2=mid+1;
        while(p1<=mid && p2<=right)//瀹屾垚鍖洪棿闄嶅簭鎺掑垪
        {
            // if(nums[p1] > 2* nums[p2])
            //     ret+=right-p2+1;
            if(nums[p1] > nums[p2])
                tmp[i++]=nums[p1++];
            else
                tmp[i++]=nums[p2++];
        }
        while(p1<=mid) tmp[i++]=nums[p1++];
        while(p2<=right) tmp[i++]=nums[p2++];
        for(int i=left;i<=right;i++)
            nums[i]=tmp[i-left];
    }
};