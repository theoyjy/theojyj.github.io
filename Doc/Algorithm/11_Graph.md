- **Graph Traversal (BFS and DFS)**
- **Tree Traversal (In-order, Pre-order, Post-order)**
- **Shortest Path Algorithms**
- **Graph Connectivity**
	- Disjoint Set Union
- **Binary Search Trees**
- **Topological Sorting**
- **Minimum Spanning Tree**

## Category

### Directional
1. weighted
2. unweighted

>Out-degree: number of edges leave from one node
>In-degree: number of edges come to one node    

### Non-directional
1. weighted
2. unweighted

>Degree: Number of edges of one node
   
### Connectivity

#### For non-directional graph
If any two nodes can be reached, the it's a connected graph
if any node can't reach other nodes, not connected

##### Connected Components
在无向图中的**极大连通***子图*称之为该图的一个连通分量。下图只有两个
![[11_Graph-20240922233438782.webp|400]]
#### For directional graph -- Strong Connectivity
If Any two nodes can **reach each other**

##### Connected Components
![[11_Graph-20240922233532314.webp|800]]

## Construct Graph
一般使用邻接表、邻接矩阵 或者用类来表示。
主要是 朴素存储、邻接表和邻接矩阵。

### 邻接矩阵
`grid[2][5] = 6`，表示 节点 2 连接 节点5，如果是有向图就是2指向5，无向图就是2和5相互连接。权值是6
邻接矩阵是从节点的角度来表示图，有多少节点就申请多大的二维数组`n * n`。

```cpp
vector<vector<int>> graph(n + 1, vector<int>(n + 1, 0));
```

#### Pros
- easy to understand
- fast to check connectivity of two points
- suitable for dense graph, especially when number of edges is close to number of nodes, which is efficient

#### Cons
- for sparse graph, waste space, when iterating edges, waste time for traveling whole `n*n`

### 邻接表
![[11_Graph-20240922234308142.webp|500]]

```cpp
vector<list<int>> graph(n + 1); // 邻接表，list为C++里的链表
```

#### Pros
1. save space for sparse graph
2. easier to iterate all edges
#### Cons
1. Inefficient to check connectivity of any two nodes, O(V), v is the degree of a node
2. Relatively difficult to understand

## Ways of Iteration
* DFS
* BFS

# DFS & BFS
>[!Tip] 深搜与广搜是图论里基本的搜索方法，大家需要掌握三点：
>
>- 搜索方式：深搜是可一个方向搜，不到黄河不回头。 广搜是围绕这起点一圈一圈的去搜。
>- 代码模板：需要熟练掌握深搜和广搜的基本写法。
>- 应用场景：图论题目基本上可以即用深搜也可用广搜，无疑是用哪个方便而已

## DFS = 回溯

### Template 和 回溯基本一个框架

```cpp
void dfs(参数) {
    if (终止条件) {
        存放结果;
        return;
    }

    for (选择：本节点所连接的其他节点) {
        处理节点;
        dfs(图，选择的节点); // 递归
        回溯，撤销处理结果
    }
}
```

### KAMA 98. 所有可达路径

```cpp
vector<vector<int>> result; // 收集符合条件的路径
vector<int> path; // 1节点到终点的路径
void dfs (const vector<vector<int>>& graph, int x, int n) {
    // 当前遍历的节点x 到达节点n 
    if (x == n) { // 找到符合条件的一条路径
        result.push_back(path);
        return;
    }
    for (int i = 1; i <= n; i++) { // 遍历节点x链接的所有节点
        if (graph[x][i] == 1) { // 找到 x链接的节点
            path.push_back(i); // 遍历到的节点加入到路径中来
            dfs(graph, i, n); // 进入下一层递归
            path.pop_back(); // 回溯，撤销本节点
        }
    }
}

path.push_back(1); // 无论什么路径已经是从0节点出发
dfs(graph, 1, n); // 开始遍历

```

or

```cpp
vector<vector<int>> result; // 收集符合条件的路径
vector<int> path; // 1节点到终点的路径

void dfs (const vector<list<int>>& graph, int x, int n) {

    if (x == n) { // 找到符合条件的一条路径
        result.push_back(path);
        return;
    }
    for (int i : graph[x]) { // 找到 x指向的节点
        path.push_back(i); // 遍历到的节点加入到路径中来
        dfs(graph, i, n); // 进入下一层递归
        path.pop_back(); // 回溯，撤销本节点
    }
}

path.push_back(1); // 无论什么路径已经是从0节点出发
dfs(graph, 1, n); // 开始遍历

```

## BFS
广搜的搜索方式就适合于解决两个点之间的最短路径问题。
正是因为BFS一圈一圈的遍历方式，所以一旦遇到终止点，那么一定是一条最短路径。

### Template

```cpp
int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1}; // 表示四个方向
// grid 是地图，也就是一个二维数组
// visited标记访问过的节点，不要重复访问
// x,y 表示开始搜索节点的下标
void bfs(vector<vector<char>>& grid, vector<vector<bool>>& visited, int x, int y) {
    queue<pair<int, int>> que; // 定义队列
    que.push({x, y}); // 起始节点加入队列
    visited[x][y] = true; // 只要加入队列，立刻标记为访问过的节点
    while(!que.empty()) { // 开始遍历队列里的元素
        pair<int ,int> cur = que.front(); que.pop(); // 从队列取元素
        int curx = cur.first;
        int cury = cur.second; // 当前节点坐标
        for (int i = 0; i < 4; i++) { // 开始想当前节点的四个方向左右上下去遍历
            int nextx = curx + dir[i][0];
            int nexty = cury + dir[i][1]; // 获取周边四个方向的坐标
            if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) continue;  // 坐标越界了，直接跳过
            if (!visited[nextx][nexty]) { // 如果节点没被访问过
                que.push({nextx, nexty});  // 队列添加该节点为下一轮要遍历的节点
                visited[nextx][nexty] = true; // 只要加入队列立刻标记，避免重复访问
            }
        }
    }

}
```

### 99 岛屿数量
遍历每一个位置
	如果是陆地, `++result`, 然后 `dfs` 找到相连接的所有陆地，到过就标记 `visited[i][j]`

- 把四个方向存在数组里，好遍历

#### dfs
```cpp
int findNumIslands(vector<vector<int>> grid)
{
	int result = 0;
	vector<vector<bool>> visited(n, vector<bool>(m, false));
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (!visited[i][j] && grid[i][j] == 1) {
				visited[i][j] = true;
				result++; // 遇到没访问过的陆地，+1
				dfs(grid, visited, i, j); // 将与其链接的陆地都标记上 true
			}
		}
	}
	return result;
}

int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1}; // 四个方向

void dfs(const vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y) {
    for (int i = 0; i < 4; i++) {
        int nextx = x + dir[i][0];
        int nexty = y + dir[i][1];
        if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) continue;  // 越界了，直接跳过
        if (!visited[nextx][nexty] && grid[nextx][nexty] == 1) { // 没有访问过的 同时 是陆地的

            visited[nextx][nexty] = true;
            dfs(grid, visited, nextx, nexty);
        }
    }
}
```

#### bfs
```cpp
int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1}; // 四个方向
void bfs(const vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y) {
    queue<pair<int, int>> que;
    que.push({x, y});
    visited[x][y] = true; // 只要加入队列，立刻标记
    while(!que.empty()) {
        pair<int ,int> cur = que.front(); que.pop();
        int curx = cur.first;
        int cury = cur.second;
        for (int i = 0; i < 4; i++) {
            int nextx = curx + dir[i][0];
            int nexty = cury + dir[i][1];
            if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) continue;  // 越界了，直接跳过
            if (!visited[nextx][nexty] && grid[nextx][nexty] == 1) {
                que.push({nextx, nexty});
                visited[nextx][nexty] = true; // 只要加入队列立刻标记
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    vector<vector<bool>> visited(n, vector<bool>(m, false));

    int result = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visited[i][j] && grid[i][j] == 1) {
                result++; // 遇到没访问过的陆地，+1
                bfs(grid, visited, i, j); // 将与其链接的陆地都标记上 true
            }
        }
    }


    cout << result << endl;
}
```


### 102 沉没孤岛

```cpp
#include <iostream>
#include <vector>
using namespace std;
int dir[4][2] = {-1, 0, 0, -1, 1, 0, 0, 1}; // 保存四个方向
void dfs(vector<vector<int>>& grid, int x, int y) {
    grid[x][y] = 2;
    for (int i = 0; i < 4; i++) { // 向四个方向遍历
        int nextx = x + dir[i][0];
        int nexty = y + dir[i][1];
        // 超过边界
        if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) continue;
        // 不符合条件，不继续遍历
        if (grid[nextx][nexty] == 0 || grid[nextx][nexty] == 2) continue;
        dfs (grid, nextx, nexty);
    }
    return;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    // 步骤一：
    // 从左侧边，和右侧边 向中间遍历
    for (int i = 0; i < n; i++) {
        if (grid[i][0] == 1) dfs(grid, i, 0);
        if (grid[i][m - 1] == 1) dfs(grid, i, m - 1);
    }

    // 从上边和下边 向中间遍历
    for (int j = 0; j < m; j++) {
        if (grid[0][j] == 1) dfs(grid, 0, j);
        if (grid[n - 1][j] == 1) dfs(grid, n - 1, j);
    }
    // 步骤二、步骤三
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 1) grid[i][j] = 0;
            if (grid[i][j] == 2) grid[i][j] = 1;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}
```

# Disjoint Set Union
并查集常用来**解决连通性**问题。
* 并查集主要有两个功能：
	
	- 将两个元素添加到一个集合中。
	- 判断两个元素在不在同一个集合

### Template

初始化 + join

```cpp
// 并查集初始化
void init() {
    for (int i = 0; i < n; ++i) {
        father[i] = i;
    }
}

// 将v->u 这条边加入并查集
void join(int u, int v) {
    u = find(u); // 寻找u的根
    v = find(v); // 寻找v的根
    if (u == v) return; // 如果发现根相同，则说明在一个集合，不用两个节点相连直接返回
    father[v] = u;
}
```

find + is same
- find 内部路径压缩
  ==除了根节点其他所有节点都挂载根节点下，这样我们在寻根的时候就很快，只需要一步==

```cpp
// 并查集里寻根的过程
int find(int u) {
    return u == father[u] ? u : father[u] = find(father[u]); 
}

// 判断 u 和 v是否找到同一个根
bool isSame(int u, int v) {
    u = find(u);
    v = find(v);
    return u == v;
}
```

### 108  冗余连接
有一个图，它是一棵树，他是拥有 n 个节点（节点编号1到n）和 n - 1 条边的连通无环无向图（其实就是一个线形图）。现在在这棵树上的基础上，添加一条边（依然是n个节点，但有n条边），使这个图变成了有环图。先请你找出冗余边，删除后，使该图可以重新变成一棵树。


```cpp
#include <iostream>
#include <vector>
using namespace std;
int n; // 节点数量
vector<int> father(1001, 0); // 按照节点大小范围定义数组

void init()
{
    for(int i = 0; i <= 1000; ++i)
        father[i] = i;
}

int find(int u)
{
    return father[u] == u ? u : 
            father[u] = find(father[u]);
}

void join(int u, int v)
{
    u = find(u);
    v = find(v);
    if(u == v)  return;
    father[v] = u;
}

bool isSame(int u, int v)
{
    u = find(u);
    v = find(v);
    return u == v;
}


int main()
{
    int s, t;
    cin >> n;
    init();
    for (int i = 0; i < n; i++) {
        cin >> s >> t;
        if(isSame(s, t)) //找到冗余边
        {
            cout << s << " " << t << endl;
            return 0;
        }
        join(s, t);
    }
    return 0;
}
```

# Minimum Spanning Tree 最小生成树

**针对无向图** 
最小生成树是所有节点的最小连通子图， 即：以最小的成本（边的权值）将图中所有节点链接到一起。

## Prime
每次寻找距离 最小生成树最近的节点 并加入到最小生成树中

1. 初始化
	`minDist`  **用来记录 每一个节点距离最小生成树的最近距离**
		初始化所有节点的最小距离为n+1
	
2. prim算法核心就是三步，我称为**prim三部曲**，大家一定要熟悉这三步，代码相对会好些很多：
	1. 第一步，选距离生成树最近节点
	   选择距离最小生成树最近的节点，加入到最小生成树，*刚开始还没有最小生成树，所以随便选一个节点加入就好（因为每一个节点一定会在最小生成树里*，所以随便选一个就好），那我们选择节点1 （符合遍历数组的习惯，第一个遍历的也是节点1）
	2. 第二步，最近节点加入生成树
	3. 第三步，更新非生成树节点到生成树的距离（即更新minDist数组）

```cpp
int main() {
    int v, e;
    int x, y, k;
    cin >> v >> e;
    // 填一个默认最大值，题目描述val最大为10000
    vector<vector<int>> grid(v + 1, vector<int>(v + 1, 10001));
    while (e--) {
        cin >> x >> y >> k;
        // 因为是双向图，所以两个方向都要填上
        grid[x][y] = k;
        grid[y][x] = k;

    }
    // 所有节点到最小生成树的最小距离
    vector<int> minDist(v + 1, 10001);

    // 这个节点是否在树里
    vector<bool> isInTree(v + 1, false);

    //加上初始化
    vector<int> parent(v + 1, -1);


    // 我们只需要循环 n-1次，建立 n - 1条边，就可以把n个节点的图连在一起
    for (int i = 1; i < v; i++) {

        // 1、prim三部曲，第一步：选距离生成树最近节点
        int cur = -1; // 选中哪个节点 加入最小生成树
        int minVal = INT_MAX;
        for (int j = 1; j <= v; j++) { // 1 - v，顶点编号，这里下标从1开始
            //  选取最小生成树节点的条件：
            //  （1）不在最小生成树里
            //  （2）距离最小生成树最近的节点
            if (!isInTree[j] &&  minDist[j] < minVal) {
                minVal = minDist[j];
                cur = j;
            }
        }
        // 2、prim三部曲，第二步：最近节点（cur）加入生成树
        isInTree[cur] = true;

        // 3、prim三部曲，第三步：更新非生成树节点到生成树的距离（即更新minDist数组）
        // cur节点加入之后， 最小生成树加入了新的节点，那么所有节点到 最小生成树的距离（即minDist数组）需要更新一下
        // 由于cur节点是新加入到最小生成树，那么只需要关心与 cur 相连的 非生成树节点 的距离 是否比 原来 非生成树节点到生成树节点的距离更小了呢
        for (int j = 1; j <= v; j++) {
            // 更新的条件：
            // （1）节点是 非生成树里的节点
            // （2）与cur相连的某节点的权值 比 该某节点距离最小生成树的距离小
            // 很多录友看到自己 就想不明白什么意思，其实就是 cur 是新加入 最小生成树的节点，那么 所有非生成树的节点距离生成树节点的最近距离 由于 cur的新加入，需要更新一下数据了
            if (!isInTree[j] && grid[cur][j] < minDist[j]) {
                minDist[j] = grid[cur][j];
                
                parent[j] = cur; // 记录边
            }
        }
    }
    // 统计结果
    int result = 0;
    for (int i = 2; i <= v; i++) { // 不计第一个顶点，因为统计的是边的权值，v个节点有 v-1条边
        result += minDist[i];
    }
    cout << result << endl;

    // 输出 最小生成树边的链接情况
    for (int i = 1; i <= v; i++) {
        cout << i << "->" << parent[i] << endl;
    }
    
	return 0;
}
```

## Kruskal
**prim 算法是维护节点的集合，而 Kruskal 是维护边的集合**。

kruscal的思路：
- 边的权值排序，因为要优先选最小的边加入到生成树里
- 遍历排序后的边
  **并查集思想**
    - 如果边首尾的两个节点在同一个集合，说明如果连上这条边图中会出现环
    - 如果边首尾的两个节点不在同一个集合，加入到最小生成树，并把两个节点加入同一个集合

```cpp

// l,r为 边两边的节点，val为边的数值
struct Edge {
    int l, r, val;
};


int main() {

    int v, e;
    int v1, v2, val;
    vector<Edge> edges;
    int result_val = 0;
    cin >> v >> e;
    while (e--) {
        cin >> v1 >> v2 >> val;
        edges.push_back({v1, v2, val});
    }

    // 执行Kruskal算法
    // 按边的权值对边进行从小到大排序
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
            return a.val < b.val;
    });

    // 并查集初始化
    init();

    // 从头开始遍历边
    for (Edge edge : edges) {
        // 并查集，搜出两个节点的祖先
        int x = find(edge.l);
        int y = find(edge.r);

        // 如果祖先不同，则不在同一个集合
        if (x != y) {
            result_val += edge.val; // 这条边可以作为生成树的边
            join(x, y); // 两个节点加入到同一个集合
        }
    }
    cout << result_val << endl;
	// 打印最小生成树的边
    for (Edge edge : result) {
        cout << edge.l << " - " << edge.r << " : " << edge.val << endl;
    }

    return 0;
}
```


## Compare Two Algo
Kruskal 与 prim 的关键区别在于，prim维护的是节点的集合，而 Kruskal 维护的是边的集合。 如果 一个图中，节点多，但边相对较少，那么使用Kruskal 更优。


# Topology Sorting

N 个文件，文件编号从 0 到 N - 1，在这些文件中，某些文件依赖于其他文件的内容，这意味着如果文件 A 依赖于文件 B，则必须在处理文件 A 之前处理文件 B （0 <= A, B <= N - 1）。请编写一个算法，用于确定文件处理的顺序。

概括来说，**给出一个 有向图，把这个有向图转成线性的排序 就叫拓扑排序**。

所以**拓扑排序也是图论中判断有向无环图的常用方法**。

*一般来说我们只需要掌握 BFS （广度优先搜索）就可以了，清晰易懂*

## 拓扑排序的过程

1. 找起点：找到入度为0 的节点，加入结果集
2. 将该节点从图中移除
### 判断环
==如果有环，移除0后，就不存在入度为0的节点了！！==
![[11_Graph-20240923212638700.webp|500]]

```cpp
int main() {
    int m, n, s, t;
    cin >> n >> m;
    vector<int> inDegree(n, 0); // 记录每个文件的入度

    unordered_map<int, vector<int>> umap;// 记录文件依赖关系
    vector<int> result; // 记录结果

    while (m--) {
        // s->t，先有s才能有t
        cin >> s >> t;
        inDegree[t]++; // t的入度加一
        umap[s].push_back(t); // 记录s指向哪些文件
    }
    queue<int> que;
    for (int i = 0; i < n; i++) {
        // 入度为0的文件，可以作为开头，先加入队列
        if (inDegree[i] == 0) que.push(i);
        //cout << inDegree[i] << endl;
    }
    // int count = 0;
    while (que.size()) {
        int  cur = que.front(); // 当前选中的文件
        que.pop();
        //count++;
        result.push_back(cur);
        vector<int> files = umap[cur]; //获取该文件指向的文件
        if (files.size()) { // cur有后续文件
            for (int i = 0; i < files.size(); i++) {
                inDegree[files[i]] --; // cur的指向的文件入度-1
                if(inDegree[files[i]] == 0) que.push(files[i]);
            }
        }
    }
    if (result.size() == n) {
        for (int i = 0; i < n - 1; i++) cout << result[i] << " ";
        cout << result[n - 1];
    } else cout << -1 << endl;
}
```

# 最短路算法中的 dijkstra 算法
需要注意两点：
- dijkstra 算法可以同时求 起点到所有节点的最短路径
- 权值不能为负数

## dijkstra三部曲

1. 第一步，选源点到哪个节点近且该节点未被访问过
2. 第二步，该最近节点被标记访问过
3. 第三步，更新非访问节点到源点的距离（即更新minDist数组）

![[11_Graph-20240923213827532.webp]]
	原本到节点3的值是4，现在是到2 再到3 也就是 1+2 = 3，更小，所以更新
	

```cpp
int main() {
    int n, m, p1, p2, val;
    cin >> n >> m;

    vector<vector<int>> grid(n + 1, vector<int>(n + 1, INT_MAX));
    for(int i = 0; i < m; i++){
        cin >> p1 >> p2 >> val;
        grid[p1][p2] = val;
    }

    int start = 1;
    int end = n;

    // 存储从源点到每个节点的最短距离
    std::vector<int> minDist(n + 1, INT_MAX);

    // 记录顶点是否被访问过
    std::vector<bool> visited(n + 1, false);

    vector<int> parent(n + 1, -1);

    minDist[start] = 0;  // 起始点到自身的距离为0

    for (int i = 1; i <= n; i++) { // 遍历所有节点

        int minVal = INT_MAX;
        int cur = 1;

        // 1、选距离源点最近且未访问过的节点
        for (int v = 1; v <= n; ++v) {
            if (!visited[v] && minDist[v] < minVal) {
                minVal = minDist[v];
                cur = v;
            }
        }

        visited[cur] = true;  // 2、标记该节点已被访问

        // 3、第三步，更新非访问节点到源点的距离（即更新minDist数组）
        for (int v = 1; v <= n; v++) {
            if (!visited[v] && grid[cur][v] != INT_MAX && minDist[cur] + grid[cur][v] < minDist[v]) {
                minDist[v] = minDist[cur] + grid[cur][v];
                parent[v] = cur; // 记录边
            }
        }

    }

    if (minDist[end] == INT_MAX) cout << -1 << endl; // 不能到达终点
    else cout << minDist[end] << endl; // 到达终点最短路径

    // 输出最短情况
    for (int i = 1; i <= n; i++) {
        cout << parent[i] << "->" << i << endl;
    }

```

## Prime 最小生成数 VS Dijkstra最短路径
**prim是求 非访问节点到最小生成树的最小距离，而 dijkstra是求 非访问节点到源点的最小距离**。

prime 更新 `minDist`
```cpp
for (int j = 1; j <= v; j++) {
    if (!isInTree[j] && grid[cur][j] < minDist[j]) {
        minDist[j] = grid[cur][j];
    }
}
```

dijkstra 更新 `minDist`
```cpp
for(int v = 1; v <= n; ++v)
{
	if(!visited[v] && grid[cur][v] != INT_MAX 
		&& minDist[cur] + grid[cur][v] < minDist[v])
		minDist[v] = minDist[cur] + grid[cur][v];
}
```