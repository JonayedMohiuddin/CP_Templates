#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

int n, q;
int a[200010];
int p[100], check[2000];
int d[500010];
int mark[200010];
vector<int> primes;
vector<vector<int> > factors;

int main(){
    check[2] = 0;
    for(int i=2;i*i<=500000;++i){
        if(check[i])continue;
        primes.push_back(i);
        for(int j=2;i*j<=1000;++j){
            check[i*j]=1;
        }
    }
    scanf("%d%d",&n,&q);
    for(int i=0;i<n;++i){
        scanf("%d",&a[i]);
        factors.push_back(vector<int>());
        for(int j=0;j<primes.size();++j){
            if(a[i]%primes[j]==0){
                while(a[i]%primes[j]==0) a[i]/=primes[j];
                factors[i].push_back(primes[j]);
            }
        }
        if(a[i]!=1) factors[i].push_back(a[i]);
    }
    int x;
    int cnt = 0;
    long long prev = 0;
    for(int qq=0;qq<q;++qq){
        scanf("%d",&x);
        --x;
        int sz = factors[x].size();

        if(mark[x]) {
            for(int mask = 1; mask < (1<<sz);++mask){
                int fact = 1;
                for(int j=0;j<sz;++j){
                    if(mask&(1<<j)){
                        fact *= factors[x][j];
                    }
                }
                d[fact]--;
            }           
            --cnt;
        }

        int cur = cnt;
        for(int mask = 1; mask < (1<<sz);++mask){
            int fact = 1;
            int mult = 1;
            for(int j=0;j<sz;++j){
                if(mask&(1<<j)){
                    mult *= -1;
                    fact *= factors[x][j];
                }
            }
            cur += mult*d[fact];
        }
        prev = prev + (mark[x] ? -cur : cur);
        cout << prev << endl;

        if(!mark[x]){
            for(int mask = 1; mask < (1<<sz);++mask){
                int fact = 1;
                for(int j=0;j<sz;++j){
                    if(mask&(1<<j)){
                        fact *= factors[x][j];
                    }
                }
                d[fact]++;
            }           
            ++cnt;
        }

        mark[x] ^=1;
    }
    return 0;
}