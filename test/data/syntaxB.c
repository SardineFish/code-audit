#include <stdio.h>

int gcd(int a, int b)
{
    if (a % b == 0)
    {
        return b;
    }
    else
    {
        return gcd(b, a % b);
    }
}

int main()
{
    int m = 0;
    int n = 0;
    scanf("%d,%d", &m, &n);
    printf("%d\n", gcd(m, n));
    return 0;
}