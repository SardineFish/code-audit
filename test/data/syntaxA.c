#include <stdio.h>

int gcd(int x, int y)
{
    //break;
    if (x % y == 0)
        return y;
    return gcd(y, x % y);
}

int main()
{
    int a = 1 + 2 + 3 + 4 + 5 + 6;
    int t[10] = {1, 2, 3, 4, 5, 6};
    int x = 48, y = 64;
    a = gcd(x, y);
    return 0;
}