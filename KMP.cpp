///KMP 返回匹配数
inline void BuildNext(const char* pattern, size_t length, unsigned int* next)
{
	unsigned int i, t;

	i = 1;
	t = 0;
	next[1] = 0;

	while(i < length + 1)
	{
		while(t > 0 && pattern[i - 1] != pattern[t - 1])
		{
			t = next[t];
		}

		++t;
		++i;

		if(pattern[i - 1] == pattern[t - 1])
		{
			next[i] = next[t];
		}
		else
		{
			next[i] = t;
		}
	}

	//pattern末尾的结束符控制，用于寻找目标字符串中的所有匹配结果用
	while(t > 0 && pattern[i - 1] != pattern[t - 1])
	{
		t = next[t];
	}

	++t;
	++i;

	next[i] = t;
}

unsigned int KMP(const char* text, size_t text_length, const char* pattern, size_t pattern_length, unsigned int* matches)
{
	unsigned int i, j, n;
	unsigned int next[pattern_length + 2];

	BuildNext(pattern, pattern_length, next);

	i = 0;
	j = 1;
	n = 0;

	while(pattern_length + 1 - j <= text_length - i)
	{
		if(text[i] == pattern[j - 1])
		{
			++i;
			++j;

			//发现匹配结果，将匹配子串的位置，加入结果
			if(j == pattern_length + 1)
			{
				matches[n++] = i - pattern_length;
				j = next[j];
			}
		}
		else
		{
			j = next[j];

			if(j == 0)
			{
				++i;
				++j;
			}
		}
	}

	//返回发现的匹配数
	return n;
}


/// 返回发现位置
void get_nextval(const char *T, int next[])
{
       // 求模式串T的next函数值并存入数组 next。
       int j = 0, k = -1;
       next[0] = -1;
       while ( T[j/*+1*/] != '\0' )
       {
              if (k == -1 || T[j] == T[k])
              {
                     ++j; ++k;
                     if (T[j]!=T[k])
                            next[j] = k;
                     else
                            next[j] = next[k];
              }// if
              else
                     k = next[k];
       }// while
    ////这里是我加的显示部分
   // for(int  i=0;i<j;i++)
       //{
       //     cout<<next[i];
       //}
       //cout<<endl;
}// get_nextval　
另一种写法，也差不多。
void getNext(const char* pattern,int next[])
{
       next[0]=-1;
       int k=-1,j=0;
       while(pattern[j]  !=  '\0')
       {
              if(k!=  -1  &&  pattern[k]!=  pattern[j] )
                     k=next[k];
              ++j;++k;
              if(pattern[k]==  pattern[j])
                     next[j]=next[k];
              else
                     next[j]=k;
       }
       ////这里是我加的显示部分
   // for(int  i=0;i<j;i++)
       //{
       //     cout<<next[i];
       //}
       //cout<<endl;
}
#include <iostream.h>
#include <string.h>
int KMP(const char *Text,const char* Pattern) //const 表示函数内部不会改变这个参数的值。
{
       if( !Text||!Pattern||  Pattern[0]=='\0'  ||  Text[0]=='\0' )//
              return -1;//空指针或空串，返回-1。
       int len=0;
       const char * c=Pattern;
       while(*c++!='\0')//移动指针比移动下标快。
       {
              ++len;//字符串长度。
       }
       int *next=new int[len+1];
       get_nextval(Pattern,next);//求Pattern的next函数值

       int index=0,i=0,j=0;
       while(Text[i]!='\0'  && Pattern[j]!='\0' )
       {
              if(Text[i]== Pattern[j])
              {
                     ++i;// 继续比较后继字符
                     ++j;
              }
              else
              {
                     index += j-next[j];
                     if(next[j]!=-1)
                            j=next[j];// 模式串向右移动
                     else
                     {
                            j=0;
                            ++i;
                     }
              }
       }//while
       delete []next;
       if(Pattern[j]=='\0')
              return index;// 匹配成功
       else
              return -1;
}




///以0开始的next数组




void getFail(char *p,int *f)
{
    int m=strlen(p);
    f[0]=f[1]=0;
    for(int i=1;i<m;++i)
    {
        int j=f[i];
        while(j&&p[i]!=p[j])j=f[j];
        f[i+1]=p[i]==p[j]?j+1:0;
    }
}
void Find(char *str,char *p,int *f)
{
    int n=strlen(str),m=strlen(p);
    int j=0;
    for(int i=0;i<n;++i)
    {
        while(j&&p[j]!=str[i])j=f[j];
        if(p[j]==str[i])j++;
        if(j==m)printf("%d\n",i-m+1);
    }
}


///以-1开始的next数组

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100

void cal_next( char * str, int * next, int len )
{
  int i, j;

  next[0] = -1;
  for( i = 1; i < len; i++ )
  {
    j = next[ i - 1 ];
    while( str[ j + 1 ] != str[ i ] && ( j >= 0 ) )
    {
      j = next[ j ];
    }
    if( str[ i ] == str[ j + 1 ] )
    {
      next[ i ] = j + 1;
    }
    else
    {
      next[ i ] = -1;
    }
  }
  /*   for(int  i=0;i<len;i++)
       {
            cout<<next[i]<<" ";
       }
       cout<<endl;*/
}

int KMP( char * str, int slen, char * ptr, int plen, int * next )
{
  int s_i = 0, p_i = 0;

  while( s_i < slen && p_i < plen )
  {
    if( str[ s_i ] == ptr[ p_i ] )
    {
      s_i++;
      p_i++;
    }
    else
    {
      if( p_i == 0 )
      {
        s_i++;
      }
      else
      {
        p_i = next[ p_i - 1 ] + 1;
      }
    }
  }
  return ( p_i == plen ) ? ( s_i - plen ) : -1;
}

int main()
{
  char str[ N ] = {0};
  char ptr[ N ] = {0};
  int slen, plen;
  int next[ N ];

  while( scanf( "%s%s", str, ptr ) )
  {
    slen = strlen( str );
    plen = strlen( ptr );
    cal_next( ptr, next, plen );
    printf( "%d\n", KMP( str, slen, ptr, plen, next ) );
  }
  return 0;
}















#include<stdio.h>
#include<string.h>
void makeNext(const char P[],int next[])
{
    int q,k;
    int m = strlen(P);
    next[0] = 0;
    for (q = 1,k = 0; q < m; ++q)
    {
        while(k > 0 && P[q] != P[k])
            k = next[k-1];
        if (P[q] == P[k])
        {
            k++;
        }
        next[q] = k;
    }
}

int kmp(const char T[],const char P[],int next[])
{
    int n,m;
    int i,q;
    n = strlen(T);
    m = strlen(P);
    makeNext(P,next);
    for (i = 0,q = 0; i < n; ++i)
    {
        while(q > 0 && P[q] != T[i])
            q = next[q-1];
        if (P[q] == T[i])
        {
            q++;
        }
        if (q == m)
        {
            printf("Pattern occurs with shift:%d\n",(i-m+1));
        }
    }
}

int main()
{
    int i;
    int next[20]={0};
    char T[] = "ababxbababcadfdsss";
    char P[] = "abcdabd";
    printf("%s\n",T);
    printf("%s\n",P );
    // makeNext(P,next);
    kmp(T,P,next);
    for (i = 0; i < strlen(P); ++i)
    {
        printf("%d ",next[i]);
    }
    printf("\n");

    return 0;
}
