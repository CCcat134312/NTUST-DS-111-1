#include <stdio.h>
#define MAX 45
int main()
{
    long long dp[MAX + 1] = {[0] = 0, [1] = 1};
    for (int i = 2; i <= MAX; i++)
        dp[i] = dp[i - 1] + dp[i - 2];
    int n;
    scanf("%d", &n);
    for (int input; n; n--)
    {
        scanf("%d", &input);
        printf("%d\n", dp[input]);
    }
    return 0;
}