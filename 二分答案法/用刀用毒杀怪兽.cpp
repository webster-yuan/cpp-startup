//刀砍毒杀怪兽问题怪兽的初始血量是一个整数hp，
//给出每一回合刀砍和毒杀的数值cuts和poisons
//第i回合如果用刀砍，怪兽在这回合会直接损失cuts[i]的血，不再有后续效果
//第i回合如果用毒杀，怪兽在这回合不会损失血量，但是之后每回合都损失poisons[i]的血量
//并且你选择的所有毒杀效果，
//在之后的回合都会叠加两个数组cuts、poisons，长度都是n，代表你一共可以进行n回合
//每一回合你只能选择刀砍或者毒杀中的一个动作
//如果你在n个回合内没有直接杀死怪兽，意味着你已经无法有新的行动了
//但是怪兽如果有中毒效果的话，那么怪兽依然会不停扣血，直到血量耗尽的那回合死掉
//返回 至少 多少回合怪兽会死掉
//数据范围 : 1 <= n <= 10^5; 1 <= hp <= 10^9; 1 <= cuts[i]、poisons[i] <= 10^9
//真实大厂算法笔试题

//二分答案法
//多少个回合怪兽会死是有范围的,[1,hp+1],可能第一刀就砍死了就一回合,最大就是在血量耗尽的那一回合死了,可能每回的伤害都是1
//那么就在hp/1+1回合死的.
//要求怪兽在越少的回合数中死,要求就越高.x回合就让怪死了,必然x+1回合也死了.
//func()一定不要超过mid回合数,保证让怪兽死亡能不能达成.一定让他在mid回合内死掉,更多回合无意义
//当回合数mid-index确定之后,在这个回合区间中选择收益最高的方式,是刀杀还是毒杀.

#include<iostream>
#include<vector>
using namespace std;
class Solution
{
public:
	int getTurns(vector<int>&cuts,vector<int>&poision,int hp)
	{
		int l = 1, r = hp + 1;
		int ans = 0;
		while (l <= r)
		{
			int mid = l + ((r - l) >> 1);
			if (func(cuts, poision,hp, mid))
			{
				ans = mid;
				r = mid - 1;
			}
			else
				l = mid + 1;
		}
		return ans;
	}
	bool func(vector<int>& cuts, vector<int>& posions, int hp, int limit)
	{
		int m = cuts.size();
		int n = min(m, limit);
		for (int i = 0, j = 1; i < n; i++, j++)
		{
			hp -= max((long long)cuts[i], (long long)(limit - j) * posions[i]);
			if (hp <= 0)
				return true;
		}
		return false;
	}
};