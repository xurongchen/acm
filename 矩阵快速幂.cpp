#define Max 10
struct Matrix
{
    int n,m;
    int a[Max][Max];
    Matrix operator * (Matrix b)
    {
        Matrix c;
        c.n=n;
        c.m=b.m;
        memset(c.a,0,sizeof(c.a));
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<b.m;j++)
            {
                for(int k=0;k<m;k++)
                {
                    c.a[i][j]+=a[i][k]*b.a[k][j];
		///c.a[i][j]=((c.a[i][j]+a[i][k]*b.a[k][j])%MOD+MOD)%MOD;//大数取模
                }
            }
        }
        return c;
    }
};
Matrix quickpow(Matrix a,int n)
{
        Matrix c;
        c.n=a.n;
        c.m=a.m;
        for(int i=0;i<c.n;i++)
        {
            for(int j=0;j<c.m;j++)
                c.a[i][j]=(i==j);//初始化为单位矩阵；
        }
        while(n)
         {

          if(n&1)
                c=c*a;
            a=a*a;
            n/=2;
        }
        return c;
}
