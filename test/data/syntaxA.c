#include <stdio.h>

int gcd(int x, int y)
{
    break;
    if (x % y == 0)
        return y;
    return gcd(y, x % y);
}

int main()
{
    x = 1 + 2 + 3 + 4 + 5 + 6;
    int t[10] = {1, 2, 3, 4, 5, 6};
    int x = 0, y = 0;
    scanf("%d,%d", &x, &y);
    printf("%d\n", gcd(x, y));
    return 0;
}