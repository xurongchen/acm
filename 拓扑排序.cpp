const int MAXN = 110;
const int MAXM = 10010;

int head[MAXN],indegree[MAXN],ans[MAXN],N,M,T;
//indegree[]存放入度，ans[]逆序存放拓扑序列
struct EdgeNode
{
    int to;
    int w;
    int next;
};
EdgeNode Edges[MAXM];

int toposort()
{
    queue<int> Q;//拓扑排序
    int u;
    for(int i = 1; i <= N; i++)
    {
        if(indegree[i] == 0)
            Q.push(i);
    }//将没有前驱(入度为0)的点加入队列
    int id = 0;
    //使用队列中的点，更新indegree数组，并生成拓扑序列
    while(!Q.empty())
    {
        u = Q.front();
        ans[id++] = u;  //记录拓扑序列
        Q.pop();
        //删除从该顶点出发的全部有向边，更新indegree[]
        for(int i = head[u]; i != -1; i = Edges[i].next)
        {
            indegree[Edges[i].to]--;
            if(indegree[Edges[i].to]==0)
            {
                Q.push(Edges[i].to);
            }//如果indegree数组为0，则新的没有前驱的店被找到，加入队列
        }
    }
    if(id == N)//如果有N个点进队，出队，则能生成拓扑序列
    {
        for(int i = N; i >= 1; i--)//逆序输出
            if(i != 1)
                cout << ans[i] << " ";
            else
                cout << ans[i] << endl;
        return true;
    }
    else//否则构不成拓扑序列
        return false;
}
