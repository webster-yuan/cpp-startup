#include <iostream>
#include <pthread.h>
#include <thread>
#include<vector>
#include <mutex>
// 璇诲啓閿佹槸涓€鎶婇攣鍒嗕负涓ら儴鍒嗭細璇婚攣鍜屽啓閿侊紝鍏朵腑璇婚攣鍏佽澶氫釜绾跨▼鍚屾椂鑾峰緱锛岃€屽啓閿佸垯鏄簰鏂ラ攣銆?
// 瀹冪殑瀹屾暣瑙勫垯鏄細璇昏涓嶄簰鏂ャ€佽鍐欎簰鏂ャ€佸啓鍐欎簰鏂ャ€?
// 瀹冮€傜敤浜庡璇荤殑涓氬姟鍦烘櫙锛屼娇鐢ㄥ畠鍙互鏈夋晥鐨勬彁楂樼▼搴忕殑鎵ц鎬ц兘锛屼篃鑳介伩鍏嶈鍙栧埌鎿嶄綔浜嗕竴鍗婄殑涓存椂鏁版嵁

// 浣跨敤涓ゆ妸浜掓枼閿?
// 褰撹鍐欓攣涓殑璇婚攣琚煇涓嚎绋嬪姞涓婃椂锛屽厛鍔犱笂璇讳簰鏂ラ攣锛岃繖鏍蜂繚璇佷簡鍏朵粬绾跨▼涓嶈兘鍐嶈浜嗭紱
// 鎺ョ潃锛屽啀鍔犱笂鍐欎簰鏂ラ攣锛屽悓鏃惰鏁板姞涓?1锛岃繖鏍蜂繚璇佷簡鍏朵粬绾跨▼涓嶈兘鍐嶅啓浜嗐€?
// 鎺ョ潃锛屾妸璇讳簰鏂ラ攣閲婃斁鎺夛紝鍥犱负瑕佸厑璁稿叾浠栫嚎绋嬩篃鑳借杩欎釜鍏变韩鍙橀噺銆?
// 涔熷氨鏄锛屽娆¤鏃讹紝鍙渶瑕佸姞涓€鎶婂啓閿侊紝琛ㄦ槑鍏朵粬绾跨▼鏆傛椂涓嶈兘鎵ц鍐欐搷浣溿€?
// 褰撹鍐欓攣涓殑璇婚攣琚煇涓嚎绋嬮噴鏀炬椂锛屼篃鏄姞涓婁簡璇讳簰鏂ラ攣锛?
// 杩欐牱淇濊瘉澶氫釜绾跨▼鍚屾椂閲婃斁璇诲啓閿佷腑鐨勮閿佹椂娌℃湁闂銆傚綋娌℃湁绾跨▼璇绘搷浣滄椂锛岄噴鏀惧啓浜掓枼閿併€?
// 琛ㄦ槑鍏朵粬绾跨▼鍙互鎵ц鍐欐搷浣滀簡
class readwrite_lock
{
public:
    readwrite_lock()
        : read_cnt(0)
    {}

    void readLock()
    {
        read_mtx.lock();
        if (++read_cnt == 1) //瀛樺湪绾跨▼璇绘椂
            write_mtx.lock();//鍐欏姞閿?鍙姞涓€娆?

        read_mtx.unlock();
    }

    void readUnlock()
    {
        read_mtx.lock();
        if (--read_cnt == 0)    //娌℃湁绾跨▼璇绘椂
            write_mtx.unlock();//鍐欓噴鏀鹃攣

        read_mtx.unlock();
    }

    void writeLock()
    {
        write_mtx.lock();
    }

    void writeUnlock()
    {
        write_mtx.unlock();
    }

private:
    std::mutex read_mtx;
    std::mutex write_mtx;
    int read_cnt; // 宸插姞璇婚攣涓暟
};
volatile int var = 10; // 淇濇寔鍙橀噺 var 瀵瑰唴瀛樺彲瑙佹€э紝闃叉缂栬瘧鍣ㄨ繃搴︿紭鍖?
readwrite_lock rwLock; // 瀹氫箟鍏ㄥ眬鐨勮鍐欓攣鍙橀噺

void Write() {
    rwLock.writeLock();
    var += 10;
    std::cout << "write var : " << var << std::endl;
    rwLock.writeUnlock();
}

void Read() {
    rwLock.readLock();
    std::cout << "read var : " << var << std::endl;
    rwLock.readUnlock();
}

int main() {
    std::vector<std::thread> writers;
    std::vector<std::thread> readers;
    for (int i = 0; i < 10; i++) {  // 10 涓啓绾跨▼
        writers.push_back(std::thread(Write));  // std::thread t 鐨勫啓娉曟姤閿?
    }
    for (int i = 0; i < 100; i++) {   // 100 涓绾跨▼
        readers.push_back(std::thread(Read));
    }
    for (auto& t : writers) {   // 鍐欑嚎绋嬪惎鍔?
        t.join();
    }
    for (auto& t : readers) {   // 璇荤嚎绋嬪惎鍔?
        t.join();
    }
    std::cin.get();
}
// 2. 浣跨敤pthread搴撲腑鐨剅wlock鎺ュ彛瀹炵幇
class ReadWriteLock
{
public:
    ReadWriteLock()
    {
        pthread_rwlock_init(&rwlock, nullptr);
    }

    ~ReadWriteLock()
    {
        pthread_rwlock_destroy(&rwlock);
    }

    void readLock()
    {
        pthread_rwlock_rdlock(&rwlock);
    }

    void readUnlock()
    {
        pthread_rwlock_unlock(&rwlock);
    }

    void writeLock()
    {
        pthread_rwlock_wrlock(&rwlock);
    }

    void writeUnlock()
    {
        pthread_rwlock_unlock(&rwlock);
    }

private:
    pthread_rwlock_t rwlock;
};

int sharedResource = 0;
ReadWriteLock rwLock;

void readerFunction(int id)
{
    rwLock.readLock();
    std::cout << "Reader " << id << " reads: " << sharedResource << std::endl;
    rwLock.readUnlock();
}

void writerFunction(int id)
{
    rwLock.writeLock();
    sharedResource = id;
    std::cout << "Writer " << id << " writes: " << sharedResource << std::endl;
    rwLock.writeUnlock();
}

int main()
{
    std::thread readers[5];
    std::thread writers[2];

    for (int i = 0; i < 5; ++i)
    {
        readers[i] = std::thread(readerFunction, i);
    }

    for (int i = 0; i < 2; ++i)
    {
        writers[i] = std::thread(writerFunction, i + 1);
    }

    for (int i = 0; i < 5; ++i)
    {
        readers[i].join();
    }

    for (int i = 0; i < 2; ++i)
    {
        writers[i].join();
    }

    return 0;
}
