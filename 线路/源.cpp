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
struct Dfs_Return {
	int cost = 0;
	//Order存储反向的顺序
	std::vector<int>order;
};
		//多源最短路
std::vector<std::vector<int>>dfs_map;
	//用于Dijkstra的变量
		//到起点的距离
struct Distance_To_Start {
	int point_number;
	int cost;
	int from;
	inline bool operator <(const Distance_To_Start X) {
		return this->cost < X.cost;
	}
};

//声明
	//求两个整型的最小值
inline int Min(int a, int b);
	//求多源最短路
std::vector<std::vector<int>>Floyd(std::vector<std::vector<int>>map);
	//求各点间的顺序
Dfs_Return Dfs(int start, int from, std::vector<int>to, std::vector<bool>visit, int step);
	//获取到达各目的地的最优先后顺序
std::vector<int>Get_Primary_Order(int from, std::vector<int>to, std::vector<std::vector<int>>map);
	//堆优化的Dijkstra
std::vector<int>Dijkstra(int from, int to, std::vector<std::vector<int>>map);

//返回最小值
inline int Min(int a, int b) {
	return a > b ? b : a;
}

//由已有有向图生成多源最短路,时间复杂度O(n³)
std::vector<std::vector<int>>Floyd(std::vector<std::vector<int>>map) {
	int n = sqrt(sizeof(map));
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++) {
			if (k == i)
				continue;
			if (map[i][k] == -1)
				continue;
			for (int j = 0; j < n; j++) {
				if (k == j || i == j)
					continue;
				if (map[k][j] == -1)
					continue;
				map[i][j] = Min(map[i][j], map[i][k] + map[j][k]);
			}
		}
	return map;
}

//深度优先搜索,时间复杂度O(m!)
	//Step初值为0
Dfs_Return Dfs(int start, int from, std::vector<int>to, std::vector<bool>visit, int step) {
	Dfs_Return ans;
	ans.cost = INF;
	int n = to.size();
	if (step == n-1)
		for (int i = 0; i < n; i++)
			if (!visit[i]) {
				//花费需要加上返回起点的费用
				ans.cost = dfs_map[from][to[i]] + dfs_map[to[i]][start];
				ans.order.push_back(to[i]);
				return ans;
			}
	int Min_Distance = INF;
	Dfs_Return tmp;
	for (int i = 0; i < n; i++)
		if (!visit[i]) {
			visit[i] = true;
			tmp = Dfs(start, to[i], to, visit, step + 1);
			visit[i] = false;
			int New_Distance = tmp.cost + dfs_map[from][to[i]];
			if (New_Distance < Min_Distance) {
				Min_Distance = New_Distance;
				ans = tmp;
				ans.cost += dfs_map[from][to[i]];
				ans.order.push_back(to[i]);
			}
		}
	return ans;
}

//返回到各目的地的先后
std::vector<int>Get_Primary_Order(int from, std::vector<int>to, std::vector<std::vector<int>>map) {
	std::vector<int>ans;
	int n = to.size();
	dfs_map = Floyd(map);
	std::vector<bool>visit;
	for (int i = 0; i < n; i++)
		visit.push_back(false);
	Dfs_Return Dfs_Return = Dfs(from, from, to, visit, 0);
	for (int i = n - 1; i >= 0; i--)
		ans.push_back(Dfs_Return.order[i]);
	//返回起点
	ans.push_back(from);
	return ans;
}

//堆优化的Dijkstra,但是仅用于求路径顺序,返回反向的不包含起点但包含终点的路径顺序
std::vector<int>Dijkstra(int from, int to, std::vector<std::vector<int>>map) {
	//初始化
	std::vector<int>ans;
	std::vector<int>from_point;
	std::priority_queue<Distance_To_Start>queue;
	int n = sqrt(sizeof(map));
	Distance_To_Start head{ from,0,-1 };
	std::vector<int>visit;
	for (int i = 0; i < n; i++) {
		visit.push_back(false);
		from_point.push_back(-1);
	}
	queue.push(head);

	while (queue.top().point_number != to) {
		Distance_To_Start now = queue.top();
		queue.pop();
		if (visit[now.point_number])
			continue;
		visit[now.point_number] = true;
		from_point[now.point_number] = now.from;
		for (int i = 0; i < n; i++)
			if (!visit[i] && map[now.point_number][i] != INF) {
				Distance_To_Start Tmp{ i,now.cost + map[now.point_number][i],now.point_number };
				queue.push(Tmp);
			}
	}
	for (int i = to; i != from; i = from_point[i])
		ans.push_back(i);
	return ans;
}