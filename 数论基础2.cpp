LL multi(LL a, LL b, LL mod)//快速乘法取模，防止两个过大的数相乘爆LL, 速度比原生乘法要慢
{
    LL ans = 0;
    a %= mod;
    while(b)//原理与快速幂类似，将一个数装换为二进制，按位相乘再求和
    {
        if(b&1)
        {
            ans = (ans + a) % mod;
        }
        b >>= 1;
        a = (a + a) % mod;
    }
    return ans;
}

LL quickMod(LL a, LL b, LL mod)//基于快速乘法取模的快速幂取模
///重点！！！！！如果能够改成int且满足题目要求一定要改，速度比LL快两倍
{
    if(b == 0)
        return 1%mod;
    LL c = a%mod;
    LL ans = 1;
    while(b)
    {
        if(b&1)
        {
            //            ans = multi(ans,c,mod);//根据题目要求选择乘法方式
            ans = ans * c % mod;
        }
        //        c = multi(c,c,mod);
        c = c * c % mod;
        b >>= 1;
    }
    return ans;
}



void euler() //欧拉筛
{
    memset(Euler,0,sizeof(Euler));
    Euler[1] = 1;
    for(int i = 2; i <= 100010; ++i)
    {
        if(!Euler[i])
        {
            for(int j = i; j <= 100010; j += i)
            {
                if(!Euler[j])
                    Euler[j] = j;
                Euler[j] = Euler[j] / i *(i-1);
            }
        }
    }
}
