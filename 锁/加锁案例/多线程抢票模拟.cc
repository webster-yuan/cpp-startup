#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <vector>
using namespace std;

vector<int> coupons;

const int numOfTheads = 100;//100涓嚎绋嬪幓鎶㈢エ
const int N = 10000;//涓€鍏辨湁澶氬皯寮犵エ

pthread_mutex_t mtx;
sem_t sem;

void* Rountine(void* args)
{
    int threadIndex=*(int*)args;
    // pthread_t threadIndex=pthread_self();
    sem_wait(&sem);//2.

    pthread_mutex_lock(&mtx);
    //涓寸晫鍖?
    //鎶㈠埌閿佷箣鍚庡氨鍙互鎶㈢エ浜?鍦ㄦ暟缁勪腑闅忔満浜х敓涓€涓笅鏍囦綅缃垹闄?浠ｈ〃鎶㈠埌绁ㄤ簡
    if(!coupons.empty())
    {
        //鎶㈢エ
        int index=rand() % coupons.size();
        int coupon=coupons[index];
        coupons.erase(coupons.begin()+index);
        pthread_mutex_unlock(&mtx);
        cout<<"Thread "<<threadIndex<<" get a coupon ,which is "<<coupon<<endl;
    }
    else
    {
        //娌＄エ浜?鍒繕浜嗘妸閿侀噴鏀炬帀
        pthread_mutex_unlock(&mtx);
        std::cout << "Thread " << threadIndex << " - No more coupons available." << std::endl;
    }
    sem_post(&sem);
    return nullptr;
}
int main()
{
    for (int i = 1; i <= N; i++)
        coupons.push_back(i);
    sem_init(&sem, 0, 10); // 1
    pthread_mutex_init(&mtx, nullptr);

    pthread_t arr[numOfTheads];
    for (int i = 0; i < numOfTheads; i++)
    {
        pthread_create(&arr[i], nullptr, Rountine, (void*)&i);//3.
    }
    for (int i = 0; i < numOfTheads; i++)
    {
        pthread_join(arr[i],nullptr);
    }
    pthread_mutex_destroy(&mtx);
    sem_destroy(&sem);
    return 0;
}
// 1.
// 琛ㄧず鏈€鍒濇湁10涓?璁稿彲璇?鍙互琚嚎绋嬭幏鍙栥€傚綋绾跨▼璋冪敤 sem_wait() 鏃讹紝淇″彿閲忕殑鍊煎皢閫掑噺锛屽綋鍊间负0鏃讹紝绾跨▼灏嗚闃诲鐩村埌鏈夊叾浠栫嚎绋嬭皟鐢?sem_post() 澧炲姞淇″彿閲忕殑鍊笺€?
// 杩欐牱锛屽湪涓€涓苟鍙戝満鏅腑锛屾渶澶氭湁10涓嚎绋嬪彲浠ュ悓鏃惰幏鍙栦俊鍙烽噺锛屼箣鍚庡叾浠栫嚎绋嬮渶瑕佺瓑寰呫€?
// 杩欐槸涓€绉嶆湁鏁堢殑闄愬埗骞跺彂璧勬簮璁块棶鐨勬柟寮忥紝鐗瑰埆鏄綋浣犲笇鏈涙帶鍒朵竴瀹氭暟閲忕殑绾跨▼璁块棶鍏变韩璧勬簮鏃躲€?
//2. 
//褰撹皟鐢?sem_wait() 鏃讹紝瀹冧細妫€鏌ヤ俊鍙烽噺鐨勫€硷紝濡傛灉鍊煎ぇ浜庨浂锛屽氨浼氬皢淇″彿閲忕殑鍊煎噺涓€锛屽苟绔嬪嵆杩斿洖銆?
// 濡傛灉鍊肩瓑浜庨浂锛屽畠浼氶樆濉炲綋鍓嶇嚎绋嬶紝鐩村埌淇″彿閲忕殑鍊煎ぇ浜庨浂涓烘銆?
// 杩欐槸涓€绉嶉樆濉炴搷浣滐紝鐢ㄤ簬鎺у埗绾跨▼鐨勬墽琛屾祦绋嬶紝浠ラ伩鍏嶈繃澶氱殑绾跨▼鍚屾椂璁块棶鍏变韩璧勬簮銆?
// 涓€鑸潵璇达紝sem_wait() 閰嶅悎鐫€ sem_post() 浣跨敤锛宻em_post() 鐢ㄤ簬澧炲姞淇″彿閲忕殑鍊硷紝
// 浠庤€屽厑璁哥瓑寰呯殑绾跨▼缁х画鎵ц銆?
//3. 
//3.1 鍦ㄥ嚱鏁皏oid* Rountine(void* args)涓紝浣犱娇鐢ㄤ簡int threadIndex=pthread_self();鏉ヨ幏鍙栫嚎绋嬬殑ID銆?
//鐒惰€岋紝pthread_self()杩斿洖鐨勬槸pthread_t绫诲瀷鐨勭嚎绋婭D锛岃€屼綘灏嗗叾璧嬪€肩粰浜唅nt绫诲瀷鐨則hreadIndex銆?
//杩欐牱鍙兘浼氬鑷寸被鍨嬭浆鎹㈤棶棰樸€傛纭殑鍋氭硶鏄皢绾跨▼ID浼犻€掍綔涓哄弬鏁般€?
//3.2 鍦ㄥ垱寤虹嚎绋嬫椂锛屼綘灏?thread"浼犻€掔粰浜嗙嚎绋嬪嚱鏁帮紝杩欏彲鑳藉鑷寸嚎绋嬪嚱鏁板唴寮曠敤宸茬粡澶辨晥鐨勫瓧绗︿覆銆?
// 淇敼鏂瑰紡锛?
// 鍦ㄤ紶閫掔嚎绋婭D鏃讹紝浣跨敤姝ｇ‘鐨勫彉閲忕被鍨嬶紙鏁存暟锛?
