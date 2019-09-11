#include <stdio.h>

int gcd(int x, int y)
{
    if (x % y == 0)
        return y;
    return gcd(y, x % y);
}

int main()
{
    int x = 0, y = 0;
    scanf("%d,%d", &x, &y);
    printf("%d\n", gcd(x, y));
    return 0;
}