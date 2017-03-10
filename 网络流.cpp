///最大流
///EdmondsKarp
//O(V*E^2)
//标记在这条路径上当前节点的前驱,同时标记该节点是否在队列中
int pre[N];
//记录残留网络的容量
int g[N][N],flow[N];
int BFS(int src,int des,int n)
{
    int i,j;

    queue<int> q;
    while(!q.empty())
        q.pop();
    memset(pre,-1,sizeof(pre));
    pre[src] = src;
    memset(flow,0,sizeof(flow));
    flow[src] = INF;
    q.push(src);
    while(!q.empty())
    {
        int index = q.front();
        q.pop();
        if(index == des)
            break;
        for(i=1;i<=n;i++)
            if(i!=src && pre[i]==-1 && g[index][i]>0)
            {
                pre[i] = index;
                flow[i] = min(g[index][i],flow[index]);
                q.push(i);
            }
    }
    if(pre[des] == -1)
        return -1;
    else
        return flow[des];
}
int maxFlow(int src,int des,int n)
{
    int increasement = 0;
    int sumflow = 0;
    while((increasement = BFS(src,des,n)) != -1)
    {
        int k = des;
        while(k != src)
        {
            int last = pre[k];
            g[last][k] -= increasement;
            g[k][last] += increasement;
            k = last;
        }
        sumflow += increasement;
    }
    return sumflow;
}
int main()
{
    memset(g,0,sizeof(g));
    for(i=0;i<m;i++)
    {
        scanf("%d%d%d",&x[i],&y[i],&z);
        g[x[i]][y[i]]=g[y[i]][x[i]]=z;
    }
    maxFlow(1,2,n);
    //输出割边
    for(i=0;i<m;i++)
        if(flow[x[i]]&&!flow[y[i]] || flow[y[i]]&&!flow[x[i]])
            printf("%d %d\n",x[i],y[i]);
}

///dinic
//O(V^2*E)
struct edge{int x,y,next; int c;}e[M];
int tot,head[N],ps[N],dep[N];
void init()
{
    memset(head,-1,sizeof(head));
    tot=0;
}
void addedge(int x,int y,int c)
{
    e[tot].x=x;e[tot].y=y;e[tot].c=c;
    e[tot].next=head[x];head[x]=tot++;
    e[tot].x=y;e[tot].y=x;e[tot].c=0;
    e[tot].next=head[y];head[y]=tot++;
}
int maxFlow(int src,int des,int n)
{
    int tr,res=0;
    int i,j,k,l,r,top;
    while(1)
    {
        //分层标号
        memset(dep,-1,sizeof(dep));
        for(l=dep[ps[0]=src]=0,r=1;l!=r;)
        {
            for(i=ps[l++],j=head[i];j!=-1;j=e[j].next)
                if(e[j].c&&-1==dep[k=e[j].y])
                {
                    dep[k]=dep[i]+1;ps[r++]=k;
                    if(k==des){ l=r; break; }
                }
        }
        if(dep[des]==-1)break;
        //深搜找增广路
        for(i=src,top=0;;)
        {
            if(i==des)
            {
                for(k=0,tr=INF;k<top;++k)
                    if(e[ps[k]].c<tr)tr=e[ps[l=k]].c;
				for(k=0;k<top;++k)
					e[ps[k]].c-=tr,e[ps[k]^1].c+=tr;
				res+=tr;i=e[ps[top=l]].x;
            }
            for(j=head[i];j!=-1;j=e[j].next)
                if(e[j].c&&dep[i]+1==dep[e[j].y])break;
            if(j!=-1)
                ps[top++]=j,i=e[j].y;
            else
            {
                if(!top)break;
                dep[i]=-1;i=e[ps[--top]].x;
            }
        }
    }
    return res;
}

///SAP
int pre[N];
int g[N][N];
int gap[N],dis[N],cur[N];
//0~sum-1
int maxFlow(int src,int des,int sum)
{
    memset(cur,0,sizeof(cur));
    memset(dis,0,sizeof(dis));
    memset(gap,0,sizeof(gap));
    int u=pre[src]=src,maxflow=0,aug=-1;
    gap[0]=sum;
    while(dis[src]<sum)
    {
        int flag=1;
        while(flag)
        {
            flag=0;
            for(int v=cur[u]; v<sum; v++)
            {
                if(g[u][v] && dis[u]==dis[v]+1)
                {
                    if(aug==-1 || aug>g[u][v])aug=g[u][v];
                    pre[v]=u;
                    u=cur[u]=v;
                    if(v==des)
                    {
                        maxflow+=aug;
                        for(u=pre[u]; v!=src; v=u,u=pre[u])
                        {
                            g[u][v]-=aug;
                            g[v][u]+=aug;
                        }
                        aug=-1;
                    }
                    flag=1;
                }
                if(flag)break;
            }
        }
        int mindis=sum-1;
        for(int v=0; v<sum; v++)
            if(g[u][v]&&mindis>dis[v])
            {
                cur[u]=v;
                mindis=dis[v];
            }
        if((--gap[dis[u]])==0)break;
        gap[dis[u]=mindis+1]++;
        u=pre[u];
    }
    return maxflow;
}

///ISAP
struct Edge
{
    int to,next,cap,flow;
} edge[M];
int tol;
int head[N];
int gap[N],dep[N],cur[N];
void init()
{
    tol = 0;
    memset(head,-1,sizeof(head));
}
void addedge(int u,int v,int w,int rw = 0)
{
    edge[tol].to = v;
    edge[tol].cap = w;
    edge[tol].flow = 0;
    edge[tol].next = head[u];
    head[u] = tol++;
    edge[tol].to = u;
    edge[tol].cap = rw;
    edge[tol].flow = 0;
    edge[tol].next = head[v];
    head[v] = tol++;
}
int Q[N];
void BFS(int start,int ends)
{
    memset(dep,-1,sizeof(dep));
    memset(gap,0,sizeof(gap));
    gap[0] = 1;
    int fronts = 0, rear = 0;
    dep[ends] = 0;
    Q[rear++] = ends;
    while(fronts != rear)
    {
        int u = Q[fronts++];
        for(int i = head[u]; i != -1; i = edge[i].next)
        {
            int v = edge[i].to;
            if(dep[v] != -1)continue;
            Q[rear++] = v;
            dep[v] = dep[u] + 1;
            gap[dep[v]]++;
        }
    }
}
int S[N];
int maxFlow(int start,int ends,int sum)
{
    BFS(start,ends);
    memcpy(cur,head,sizeof(head));
    int top = 0;
    int u = start;
    int ans = 0;
    while(dep[start] < sum)
    {
        if(u == ends)
        {
            int Min = INF;
            int inser;
            for(int i = 0; i < top; i++)
                if(Min > edge[S[i]].cap - edge[S[i]].flow)
                {
                    Min = edge[S[i]].cap - edge[S[i]].flow;
                    inser = i;
                }
            for(int i = 0; i < top; i++)
            {
                edge[S[i]].flow += Min;
                edge[S[i]^1].flow -= Min;
            }
            ans += Min;
            top = inser;
            u = edge[S[top]^1].to;
            continue;
        }
        bool flag = false;
        int v;
        for(int i = cur[u]; i != -1; i = edge[i].next)
        {
            v = edge[i].to;
            if(edge[i].cap - edge[i].flow && dep[v]+1 == dep[u])
            {
                flag = true;
                cur[u] = i;
                break;
            }
        }
        if(flag)
        {
            S[top++] = cur[u];
            u = v;
            continue;
        }
        int Min = N;
        for(int i = head[u]; i != -1; i = edge[i].next)
            if(edge[i].cap - edge[i].flow && dep[edge[i].to] < Min)
            {
                Min = dep[edge[i].to];
                cur[u] = i;
            }
        gap[dep[u]]--;
        if(!gap[dep[u]])return ans;
        dep[u] = Min + 1;
        gap[dep[u]]++;
        if(u != start)u = edge[S[--top]^1].to;
    }
    return ans;
}

///最小费用最大流
struct Edge
{
    int to,next,cap,flow,cost;
} edge[M];
int head[N],tol,tot;//tot总节点数，0~tot-1
int pre[N],dis[N];
bool vis[N];
void init()
{
    tol = 0;
    memset(head,-1,sizeof(head));
}
void addedge(int u,int v,int cap,int cost)
{
    edge[tol].to = v;
    edge[tol].cap = cap;
    edge[tol].cost = cost;
    edge[tol].flow = 0;
    edge[tol].next = head[u];
    head[u] = tol++;
    edge[tol].to = u;
    edge[tol].cap = 0;
    edge[tol].cost = -cost;
    edge[tol].flow = 0;
    edge[tol].next = head[v];
    head[v] = tol++;
}
bool spfa(int s,int t)
{
    queue<int>q;
    for(int i = 0; i < tot; i++)
    {
        dis[i] = INF;
        vis[i] = false;
        pre[i] = -1;
    }
    dis[s] = 0;
    vis[s] = true;
    q.push(s);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = false;
        for(int i = head[u]; i != -1; i = edge[i].next)
        {
            int v = edge[i].to;
            if(edge[i].cap > edge[i].flow &&
                    dis[v] > dis[u] + edge[i].cost )
            {
                dis[v] = dis[u] + edge[i].cost;
                pre[v] = i;
                if(!vis[v])
                {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
    }
    if(pre[t] == -1)return false;
    else return true;
}
//返回的是最大流，cost存的是最小费用
int minCostMaxflow(int s,int t,int &cost)
{
    int flow = 0;
    cost = 0;
    while(spfa(s,t))
    {
        int Min = INF;
        for(int i = pre[t]; i != -1; i = pre[edge[i^1].to])
        {
            if(Min > edge[i].cap - edge[i].flow)
                Min = edge[i].cap - edge[i].flow;
        }
        for(int i = pre[t]; i != -1; i = pre[edge[i^1].to])
        {
            edge[i].flow += Min;
            edge[i^1].flow -= Min;
            cost += edge[i].cost * Min;
        }
        flow += Min;
    }
    return flow;
}













#define M 50000
#define N 500
struct Edge
{
    int u;
    int v;
    int cap;
    int cost;
    int next;
}edge[M];
int NE;
int head[N], dist[N], pp[N];
bool vis[N];
void init()
{
    NE=0;
    memset(head,-1,sizeof(head));
}
void addedge(int u,int v,int cap,int cost)
{
    edge[NE].u=u;edge[NE].v=v;edge[NE].cap=cap;edge[NE].cost=cost;
    edge[NE].next=head[u];head[u]=NE++;
    edge[NE].u=v;edge[NE].v=u;edge[NE].cap=0;edge[NE].cost=-cost;
    edge[NE].next=head[v];head[v]=NE++;
}
bool SPFA(int s,int t,int n)
{
    int i,u,v;
    queue<int>qu;
    memset(vis,false,sizeof(vis));
    memset(pp,-1,sizeof(pp));
    for(i=0;i<=n;i++)
        dist[i]=INF;
    vis[s]=true;
    dist[s]=0;
    qu.push(s);
    while(!qu.empty())
    {
        u=qu.front();
        qu.pop();
        vis[u]=false;
        for(i=head[u];i!=-1;i=edge[i].next)
        {
            v=edge[i].v;
            if(edge[i].cap&&dist[v]>dist[u]+edge[i].cost)
            {
                dist[v]=dist[u]+edge[i].cost;
                pp[v]=i;
                if(!vis[v])
                {
                    qu.push(v);
                    vis[v]=true;
                }
            }
        }
    }
    if(dist[t]==INF)
        return false;
    return true;
}
int MCMF(int s,int t,int n)
{
    int flow=0; // 总流量
    int i,minflow,mincost;
    mincost=0;
    while(SPFA(s,t,n))
    {
        minflow=INF+1;
        for(i=pp[t];i!=-1;i=pp[edge[i].u])
            if(edge[i].cap<minflow)
                minflow=edge[i].cap;
        flow+=minflow;
        for(i=pp[t];i!=-1;i=pp[edge[i].u])
        {
            edge[i].cap-=minflow;
            edge[i^1].cap+=minflow;
        }
        mincost+=dist[t]*minflow;
    }
    //sumFlow=flow; // 最大流
    return mincost;
}
