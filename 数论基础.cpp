int gcd(int a, int b)//gcd
{
    return b == 0? a: gcd(b, a%b);
}

int vis[N];
vector<int> prime;
void getPrime(int n)//素数筛 O(nlog(n))
{
    prime.clear();
    memset(vis, 0, sizeof(vis));
    for(int i = 2; i <= n; ++i)
    {
        if(vis[i])
        {
            continue;
        }
        prime.push_back(i);
        for(int j = i * 2; j <= n; j += i)
        {
            vis[j] = 1;
        }
    }
}

bool isPrime(int n)//双筛判定
{
    for(int i = 0; prime[i] * prime[i] <= n; ++i)
    {
        if(n % prime[i] == 0)
        {
            return false;
        }
    }
    return true;
}

vector<int> factors;
void getFactors(int n)///利用sqrt(n)范围内的素数表即可求出n的素因子，O(sqrt(n))
{
    factors.clear();
    int tmp = n;
    for(int i = 0; i <= prime.size() && prime[i] * prime[i] <= n; ++i)
    {
        if(tmp % prime[i] == 0)
        {
            factors.push_back(prime[i]);
        }
        while(tmp % prime[i] == 0)///由于大于sqrt(n)后还可能有唯一的较大大素因子，因此前面的素因子要除干净
        {
            tmp /= prime[i];
        }
    }
    if(tmp != 1)///最后的结果若不为1，说明还有素因子，要保存
    {
        factors.push_back(tmp);
    }
}

///用最小的素因子筛掉每个数(o(n))
int prime[N],phi[N],cnt;/// prime:记录质数，phi记录欧拉函数
int Min_factor[N];/// i的最小素因子
bool vis[N];
void Init()
{
    cnt=0;
    phi[1]=1;
    int x;
    for(int i=2;i<N;i++)
    {
        if(!vis[i])
        {
            prime[++cnt]=i;
            phi[i]=i-1;
            Min_factor[i]=i;
        }
        for(int k=1;k<=cnt&&prime[k]*i<N;k++)
        {
            x=prime[k]*i;
            vis[x]=true;
            Min_factor[x]=prime[k];
            if(i%prime[k]==0)
            {
                phi[x]=phi[i]*prime[k];
                break;
            }
            else phi[x]=phi[i]*(prime[k]-1);
        }
    }
}







