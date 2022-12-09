#pragma once
//这里引用库函数
constexpr auto INF = 0x7fffffff;

//定义全局变量
	//用于DFS的变量
		//DFS的返回值
struct Dfs_Return {
	double cost = 0;
	//Order存储反向的顺序
	std::vector<int>order;
};

		//多源最短路
extern std::vector<std::vector<double>>dfs_map;

	//用于Dijkstra的变量
		//到起点的距离
struct Distance_To_Start {
	int point_number;
	double cost;
	int from;
	inline bool operator <(const Distance_To_Start X) const {
		return this->cost > X.cost;
	}
};

//声明
	//求两个整型的最小值
inline double Min(double a, double b);
	//求多源最短路
std::vector<std::vector<double>>Floyd(std::vector<std::vector<double>>map);
	//求各点间的顺序
Dfs_Return Dfs(int start, int from, std::vector<int>to, std::vector<bool>visit, int step);
	//获取到达各目的地的最优先后顺序
std::vector<int>Get_Primary_Order(int from, std::vector<int>to, std::vector<std::vector<double>>map);
	//堆优化的Dijkstra
std::vector<int>Dijkstra(int from, int to, std::vector<std::vector<double>>map);
	//输出
std::vector<int>Get_Order(int from, std::vector<int>to, std::vector<std::vector<double>>map);
