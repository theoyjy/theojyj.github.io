- **Graph Traversal (BFS and DFS)**
- **Tree Traversal (In-order, Pre-order, Post-order)**
- **Shortest Path Algorithms**
- **Graph Connectivity**
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
