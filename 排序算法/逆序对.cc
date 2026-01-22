//ret浣滀负鍏ㄥ眬鍙橀噺浣跨敤:鍙湪merage鍚堝苟鐨勮繃绋嬩腑浜х敓閫嗗簭瀵?
//鍒掑垎鐨勫尯闂存槸鍗囧簭鐨?鍦ㄥ悎骞惰繃绋嬩腑鍏虫敞(mid+1,right)涓殑y,濡傛灉鍦?left,mid)涓湁涓€涓獂>y,閭ｄ箞灏辨湁mid-index(x)+1涓€嗗簭瀵?
//杩欐椂,姣攜澶х殑鍓嶉潰鐨勯兘鎵惧畬浜?灏辨壘index(y)+1鐨勪簡.灏唝鏀惧叆tmp涓?
class Solution 
{
    int ret;
    vector<int>tmp;
public:
//褰掑苟鎺掑簭鎬濇兂,閫嗗簭瀵圭殑浜х敓鍙戠敓鍦╩erage鐨勮繃绋嬩腑
    int reversePairs(vector<int>& nums) 
    {
        tmp.resize(nums.size());
        merageSort(nums,0,nums.size()-1);
        return ret;
    }
    void merageSort(vector<int>&nums,int left,int right)
    {
        if(left>=right) return ;
        int mid=(right-left)/2+left;
        merageSort(nums,left,mid);
        merageSort(nums,mid+1,right);
        int p1=left,p2=mid+1,i=0;
        while(p1<=mid && p2<=right)
        {
            if(nums[p1]<=nums[p2])
                tmp[i++]=nums[p1++];
            else
            {
                ret+= mid-p1+1; 
                tmp[i++]=nums[p2++];
            }
        }
        while(p1<=mid)tmp[i++]=nums[p1++];
        while(p2<=right)tmp[i++]=nums[p2++];
        //[left,right]鎷疯礉鍥炲師鏁扮粍
        for(int i=left;i<=right;i++)
            nums[i]=tmp[i-left];
    }
};


//濡傛灉鍒掑垎鍖洪棿鏄檷搴忕殑,閭ｄ箞鎵鹃€嗗簭瀵?灏遍渶瑕佸叧娉?left,mid)鍖洪棿涓殑x鍊?濡傛灉(mid+1,right)涓湁涓€涓獃鍊?x,閭ｄ箞灏辨湁(right-index(y)+1)
//涓€嗗簭瀵逛骇鐢?閮芥槸瀵箈灏忕殑.
class Solution 
{
    int ret;
    vector<int>tmp;
public:
//褰掑苟鎺掑簭鎬濇兂,閫嗗簭瀵圭殑浜х敓鍙戠敓鍦╩erage鐨勮繃绋嬩腑
    int reversePairs(vector<int>& nums) 
    {
        tmp.resize(nums.size());
        merageSort(nums,0,nums.size()-1);
        return ret;
    }
    void merageSort(vector<int>&nums,int left,int right)
    {
        if(left>=right) return ;
        int mid=(right-left)/2+left;
        merageSort(nums,left,mid);
        merageSort(nums,mid+1,right);
        int p1=left,p2=mid+1,i=0;
        while(p1<=mid && p2<=right)
        {
            if(nums[p1]>nums[p2])
            {
                ret+= right-p2+1;
                tmp[i++]=nums[p1++];
            } 
            else
                tmp[i++]=nums[p2++];
        }
        while(p1<=mid)tmp[i++]=nums[p1++];
        while(p2<=right)tmp[i++]=nums[p2++];
        //[left,right]鎷疯礉鍥炲師鏁扮粍
        for(int i=left;i<=right;i++)
            nums[i]=tmp[i-left];
    }
};


//ret浣滀负merageSort鍑芥暟鐨勮繑鍥炲€?鎰忎箟鏄垜缁欏畾浣犱竴涓尯闂?浣犲綊骞舵帓搴忎箣鍚庡皢閫嗗簭瀵圭殑涓暟杩斿洖
//宸﹀尯闂撮€嗗簭瀵?鍙冲尯闂撮€嗗簭瀵?鍚堝苟杩囩▼涓骇鐢熺殑閫嗗簭瀵?
//鍖洪棿闄嶅簭
class Solution 
{
    vector<int>tmp;
public:
//褰掑苟鎺掑簭鎬濇兂,閫嗗簭瀵圭殑浜х敓鍙戠敓鍦╩erage鐨勮繃绋嬩腑
    int reversePairs(vector<int>& nums) 
    {
        tmp.resize(nums.size());
        int ret = merageSort(nums,0,nums.size()-1);
        return ret;
    }
    int merageSort(vector<int>&nums,int left,int right)
    {
        if(left>=right) return 0;
        int mid=(right-left)/2+left;
        int ret=0;
        ret+= merageSort(nums,left,mid);
        ret+= merageSort(nums,mid+1,right);
        int p1=left,p2=mid+1,i=0;
        while(p1<=mid && p2<=right)
        {
            if(nums[p1]>nums[p2])
            {
                ret+= right-p2+1;
                tmp[i++]=nums[p1++];
            } 
            else
                tmp[i++]=nums[p2++];
        }
        while(p1<=mid)tmp[i++]=nums[p1++];
        while(p2<=right)tmp[i++]=nums[p2++];
        //[left,right]鎷疯礉鍥炲師鏁扮粍
        for(int i=left;i<=right;i++)
            nums[i]=tmp[i-left];
        return ret;
    }
};
//鍖洪棿鍗囧簭
class Solution 
{
    vector<int>tmp;
public:
//褰掑苟鎺掑簭鎬濇兂,閫嗗簭瀵圭殑浜х敓鍙戠敓鍦╩erage鐨勮繃绋嬩腑
    int reversePairs(vector<int>& nums) 
    {
        tmp.resize(nums.size());
        int ret = merageSort(nums,0,nums.size()-1);
        return ret;
    }
    int merageSort(vector<int>&nums,int left,int right)
    {
        if(left>=right) return 0;
        int mid=(right-left)/2+left;
        int ret=0;
        ret+= merageSort(nums,left,mid);
        ret+= merageSort(nums,mid+1,right);
        int p1=left,p2=mid+1,i=0;
        while(p1<=mid && p2<=right)
        {
            if(nums[p1] <= nums[p2])
                tmp[i++]=nums[p1++];
            else
            {
                ret+= mid-p1+1;
                tmp[i++]=nums[p2++];
            }
        }
        while(p1<=mid)tmp[i++]=nums[p1++];
        while(p2<=right)tmp[i++]=nums[p2++];
        //[left,right]鎷疯礉鍥炲師鏁扮粍
        for(int i=left;i<=right;i++)
            nums[i]=tmp[i-left];
        return ret;
    }
};