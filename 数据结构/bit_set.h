#pragma once
namespace yuanwei
{
	//用来表示某一位数字是否出现过01表示
	template<size_t N>
	class bitset
	{
	public:
		bitset()
		{
			bits.resize(N/8+1);
			//以8bit为一个单位进行区分,也就是一个int
			//当你需要N>32位的标记时,就多申请几个int 即可
		}
		void set(size_t x)
		{
			size_t i = x / 8;
			size_t j = x % 8;
			bits[i] |= (1<<j);
		}
		void reset(size_t x)
		{
			size_t i = x / 8;
			size_t j = x % 8;
			bits[i] &=~(1<<j)
		}
		bool test(size_t x)
		{
			size_t i = x / 8;
			size_t j = x % 8;
			return bits[i] & (1 << j)
		}
	private:
		std::vector<char> bits;
	};
	
}
//当想标记一个数字是否出现过两次,就用两张表来表示
template<size_t N>
class TwoBitSet
{
public:
	void Set(size_t N)
	{
		if (!bs1.test(N) && !bs2.test(N))//00
			bs2.set(N);
		else if (!bs1.test(N) && bs2.test(N))
		{
			bs1.set(N);
			bs2.reset(N);
		}
	}

private:
	yuanwei::bitset<N> bst1;
	yuanwei::bitset<N> bst2;
};