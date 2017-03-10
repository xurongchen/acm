int sum[10001];

void pushUp(int rt)
{
    sum[rt] = sum[rt*2]+sum[rt*2+1];
}

void updata(int l, int r, int rt, int q, int val)
{
    if(l==q && r==q)
    {
        sum[rt] = val;
        return;
    }
    int m = (l+r)/2;
    if(q<=m)updata(l,m,rt*2,q,val);
    if(q>m) updata(m+1,r,rt*2+1,q,val);
    pushUp(rt);
}

int query(int l, int r, int rt, int ql, int qr)
{
    if(l>qr || r<ql)return 0;
    if(l>=ql && r<=qr)return sum[rt];
    int m = (l+r)/2;
    return query(l,m,rt*2,ql,qr) + query(m+1,r,rt*2+1,ql,qr);
}

void build(int l, int r, int rt)
{
    if(l==r)
    {
        scanf("%d",&sum[rt]);
        return;
    }
    int m = (l+r)/2;
    build(l,m,rt*2);
    build(m+1,r,rt*2+1);
    pushUp(rt);
}
