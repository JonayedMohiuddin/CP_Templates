#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;

vector<int> numToVec(long long num)
{
    vector<int> arr;
    while(num > 0)
    {
        arr.push_back(num % 10);
        num /= 10;
    }    
    reverse(arr.begin(), arr.end());
    return arr;
}

long long binexp(long long a, long long n)
{
    long long ans = 1;
    while(n > 0)
    {
        if(n & 1)
            ans = (ans * a);
        a = (a * a);
        n >>= 1;
    }
    return ans;
}

long long a, b, k;
long long dp[90][2][2][90][90]; // n (digits covered till now), f (is less than b), s (maximum sum), r (current remainder)
vector<int> digitsOfUpperLimit, digitsOfLowerLimit;

long long solve(long long n, int isSmall, int isBig, long long sum, long long remainder)
{
    if(n >= digitsOfUpperLimit.size()) return sum % k == 0 && remainder % k == 0; 
    if(dp[n][isSmall][isBig][sum][remainder] != -1) return dp[n][isSmall][isBig][sum][remainder];

    long long cur = 0;
    long long nthDigitOfUpperLimit = (isSmall? 9 : digitsOfUpperLimit[n]);
    long long nthDigitOfLowerLimit = (isBig?   0 : digitsOfLowerLimit[n]);

    for (int d = nthDigitOfLowerLimit; d <= nthDigitOfUpperLimit; d++)
    {
        int newIsBig = isBig, newIsSmall = isSmall;
        if(d < nthDigitOfUpperLimit && isSmall == 0) newIsSmall = 1;
        if(d > nthDigitOfLowerLimit && isBig   == 0) newIsBig = 1; 
        cur += solve(n + 1, newIsSmall, newIsBig, (sum + d) % k, (remainder * 10 + d) % k);
    }

    return dp[n][isSmall][isBig][sum][remainder] = cur;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int TC; 
    cin >> TC;
    for (int tc = 1; tc <= TC; tc++)
    {
        cin >> a >> b >> k;

        memset(dp, -1, sizeof(dp));
        digitsOfUpperLimit = numToVec(b);
        vector<int> temp = numToVec(a);
        long long diff = digitsOfUpperLimit.size() - temp.size();
        digitsOfLowerLimit.clear();
        for (int i = 0; i < diff; i++)
        {
            digitsOfLowerLimit.push_back(0);
        }
        for(auto x : temp)
        {
            digitsOfLowerLimit.push_back(x);
        }

        long long ans = solve(0, 0, 0, 0, 0);

        cout << "Case " << tc << ": " << ans << endl;
    }
    

    return 0;
}