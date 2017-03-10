#define root 1 , n , 1
#define lson l , m , rt << 1
#define rson m + 1 , r , rt << 1 | 1
int sum[N<<2],add[N<<2];
void pushUp(int rt)
{
    sum[rt] = sum[rt<<1]+sum[rt<<1|1];
}
void pushDown(int l,int r,int rt)
{
    if(add[rt])
    {
        int m = (l+r)>>1;
        add[rt<<1] += add[rt];
        add[rt<<1|1] += add[rt];
        sum[rt<<1] += (m-l+1)*add[rt];
        sum[rt<<1|1] += (r-m)*add[rt];
        add[rt] = 0;
    }
}
void updata(int l,int r,int rt,int ql,int qr,LL val)
{
    if(l>qr||ql>r)return;
    if(l>=ql&&r<=qr)
    {
        sum[rt] += (r-l+1)*val;
        add[rt] += val;
        return;
    }
    pushDown(l,r,rt);
    int m = (l+r)>>1;
    if(ql<=m)updata(lson,ql,qr,val);
    if(qr>m)updata(rson,ql,qr,val);
    pushUp(rt);
}
void build(int l,int r,int rt)
{
    add[rt]=0;
    if(l == r)
    {
        scanf("%d",&sum[rt]);
        return;
    }
    int m = (l+r)>>1;
    build(lson);
    build(rson);
    pushUp(rt);
}
LL query(int l,int r,int rt,int ql,int qr)
{
    if(l>qr||ql>r)
        return 0;
    if(l>=ql&&r<=qr)
        return sum[rt];
    pushDown(l,r,rt);
    int m = (l+r)>>1;
    return query(lson,ql,qr)+query(rson,ql,qr);
}
