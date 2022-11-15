/*
中国邮递员问题是邮递员在某一地区的信件投递路程问题。
邮递员每天从邮局出发，走遍该地区所有街道再返回邮局，问题是他应如何安排送信的路线可以使所走的总路程最短。
这个问题由中国学者管梅谷在1960年首先提出，并给出了解法——“奇偶点图上作业法”，被国际上统称为“中国邮递员问题”。
用图论的语言描述，给定一个连通图G，每边e有非负权)，要求一条回路经过每条边至少一次，且满足总权最小。

此图论中和中国邮递员问题类似的是旅行商问题，区别于中国邮递员问题，旅行商问题是说在边赋权的完全图中找一个权和最小的哈密尔顿圈。
埃德蒙兹（J.Edmonds）和约翰逊（E.L.Johnson)在1973年给出了求解（1）的多项式时间算法。
如果邮递员所通过的街道都是单向道，则对应的图应为有向图。1973年，埃德蒙兹和约翰逊证明此时CPP也有多项式时间算法。
帕帕季米特里屋（C.H.Papadimitrious）在1976年证明，如果既有双向道，又有单向道，则CPP是NP困难的。

这里给出的解法思路为:先通过Floyd算法求出各目的地两两间的多源最短路,再通过记忆化搜索求解最优访问顺序,最后通过Dijkstra算法求出两点间具体路径
记点数为n,目的地数为m,边数为e,则时间复杂度为O(n³+m!+(e+n)logn)
相比直接搜索的O(n!m!)略优
*/
//这里引用其他人的头文件

//这里引用库函数
#include<vector>
#include<queue>
#define INF 0x7fffffff

//定义全局变量
	//用于DFS的变量
		//DFS的返回值
struct dfs_return {
	int Cost = 0;
	//Order存储反向的顺序
	std::vector<int>Order;
};
		//多源最短路
std::vector<std::vector<int>>Dfs_Map;
	//用于Dijkstra的变量
		//到起点的距离
struct distance_to_start {
	int Point_Number;
	int Cost;
	int From;
	inline bool operator <(const distance_to_start X) {
		return this->Cost < X.Cost;
	}
};

//声明
	//求两个整型的最小值
inline int min(int a, int b);
	//求多源最短路
std::vector<std::vector<int>>floyd(std::vector<std::vector<int>>Map);
	//求各点间的顺序
dfs_return dfs(int Start, int From, std::vector<int>To, std::vector<bool>Visit, int Step);
	//获取到达各目的地的最优先后顺序
std::vector<int>get_primary_order(int From, std::vector<int>To, std::vector<std::vector<int>>Map);
	//堆优化的Dijkstra
std::vector<int>dijkstra(int From, int To, std::vector<std::vector<int>>Map);

//返回最小值
inline int min(int a, int b) {
	return a > b ? b : a;
}

//由已有有向图生成多源最短路,时间复杂度O(n³)
std::vector<std::vector<int>>floyd(std::vector<std::vector<int>>Map) {
	int N = sqrt(sizeof(Map));
	for (int k = 0; k < N; k++)
		for (int i = 0; i < N; i++) {
			if (k == i)
				continue;
			if (Map[i][k] == -1)
				continue;
			for (int j = 0; j < N; j++) {
				if (k == j || i == j)
					continue;
				if (Map[k][j] == -1)
					continue;
				Map[i][j] = min(Map[i][j], Map[i][k] + Map[j][k]);
			}
		}
	return Map;
}

//深度优先搜索,时间复杂度O(m!)
	//Step初值为0
dfs_return dfs(int Start, int From, std::vector<int>To, std::vector<bool>Visit, int Step) {
	dfs_return Ans;
	Ans.Cost = INF;
	int N = To.size();
	if (Step == N-1)
		for (int i = 0; i < N; i++)
			if (!Visit[i]) {
				//花费需要加上返回起点的费用
				Ans.Cost = Dfs_Map[From][To[i]] + Dfs_Map[To[i]][Start];
				Ans.Order.push_back(To[i]);
				return Ans;
			}
	int Min_Distance = INF;
	dfs_return Tmp;
	for (int i = 0; i < N; i++)
		if (!Visit[i]) {
			Visit[i] = true;
			Tmp = dfs(Start, To[i], To, Visit, Step + 1);
			Visit[i] = false;
			int New_Distance = Tmp.Cost + Dfs_Map[From][To[i]];
			if (New_Distance < Min_Distance) {
				Min_Distance = New_Distance;
				Ans = Tmp;
				Ans.Cost += Dfs_Map[From][To[i]];
				Ans.Order.push_back(To[i]);
			}
		}
	return Ans;
}

//返回到各目的地的先后
std::vector<int>get_primary_order(int From, std::vector<int>To, std::vector<std::vector<int>>Map) {
	std::vector<int>Ans;
	int N = To.size();
	Dfs_Map = floyd(Map);
	std::vector<bool>Visit;
	for (int i = 0; i < N; i++)
		Visit.push_back(false);
	dfs_return Dfs_Return = dfs(From, From, To, Visit, 0);
	for (int i = N - 1; i >= 0; i--)
		Ans.push_back(Dfs_Return.Order[i]);
	//返回起点
	Ans.push_back(From);
	return Ans;
}

//堆优化的Dijkstra,但是仅用于求路径顺序,返回反向的不包含起点但包含终点的路径顺序
std::vector<int>dijkstra(int From, int To, std::vector<std::vector<int>>Map) {
	//初始化
	std::vector<int>Ans;
	std::vector<int>From_Point;
	std::priority_queue<distance_to_start>Queue;
	int N = sqrt(sizeof(Map));
	distance_to_start Head{ From,0,-1 };
	std::vector<int>Visit;
	for (int i = 0; i < N; i++) {
		Visit.push_back(false);
		From_Point.push_back(-1);
	}
	Queue.push(Head);

	while (Queue.top().Point_Number != To) {
		distance_to_start Now = Queue.top();
		Queue.pop();
		if (Visit[Now.Point_Number])
			continue;
		Visit[Now.Point_Number] = true;
		From_Point[Now.Point_Number] = Now.From;
		for (int i = 0; i < N; i++)
			if (!Visit[i] && Map[Now.Point_Number][i] != INF) {
				distance_to_start Tmp{ i,Now.Cost + Map[Now.Point_Number][i],Now.Point_Number };
				Queue.push(Tmp);
			}
	}
	for (int i = To; i != From; i = From_Point[i])
		Ans.push_back(i);
	return Ans;
}