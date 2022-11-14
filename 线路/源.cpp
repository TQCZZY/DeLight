//�������������˵�ͷ�ļ�

//�������ÿ⺯��
#include<vector>
#define INF 0x7fffffff

//����ȫ�ֱ���
	//����DFS�ı���
		//DFS�ķ���ֵ
struct dfs_return {
	int Cost = 0;
	//Order�洢�����˳��
	std::vector<int>Order;
};
		//��Դ���·
std::vector<std::vector<int>>Dfs_Map;

//����
	//���������͵���Сֵ
inline int min(int a, int b);
	//���Դ���·
std::vector<std::vector<int>>Floyd(std::vector<std::vector<int>>Map);
	//�������˳��
dfs_return dfs(int From, std::vector<int>To, std::vector<bool>Visit, int Step);

//������Сֵ
inline int min(int a, int b) {
	return a > b ? b : a;
}

//����������ͼ���ɶ�Դ���·
std::vector<std::vector<int>>Floyd(std::vector<std::vector<int>>Map) {
	int n = sqrt(sizeof(Map));
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++) {
			if (k == i)
				continue;
			if (Map[i][k] == -1)
				continue;
			for (int j = 0; j < n; j++) {
				if (k == j || i == j)
					continue;
				if (Map[k][j] == -1)
					continue;
				Map[i][j] = min(Map[i][j], Map[i][k] + Map[j][k]);
			}
		}
	return Map;
}

//�����������
	//Step��ֵΪ0
dfs_return dfs(int From, std::vector<int>To, std::vector<bool>Visit, int Step) {
	dfs_return Ans;
	Ans.Cost = INF;
	int N = To.size();
	if (Step == N-1)
		for (int i = 0; i < N; i++)
			if (!Visit[i]) {
				Ans.Cost = Dfs_Map[From][To[i]];
				Ans.Order.push_back(To[i]);
				return Ans;
			}
	int Min_Distance = INF;
	dfs_return Tmp;
	for (int i = 0; i < N; i++)
		if (!Visit[i]) {
			Visit[i] = true;
			Tmp = dfs(To[i], To, Visit, Step + 1);
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

//���յĳ�Ʒ֮һ,���ص���Ŀ�ĵص��Ⱥ�
std::vector<int>Get_Primary_Order(int From, std::vector<int>To, std::vector<std::vector<int>>Map) {
	std::vector<int>Ans;
	int N = To.size();
	Dfs_Map = Floyd(Map);
	std::vector<bool>Visit;
	for (int i = 0; i < N; i++)
		Visit.push_back(false);
	dfs_return Dfs_Return = dfs(From, To, Visit, 0);
	for (int i = N - 1; i >= 0; i--)
		Ans.push_back(Dfs_Return.Order[i]);
	return Ans;
}