int glob = 0;

int gcd(int x, int y)
{
    // break;
    if (x % y == 0)
        return y;
    return gcd(y, x % y);
}

int main()
{
    int arr[10] = {1, 6, 7, 2, 6, 9, 3, 5, 4, 7};
    int n = 10;
    int a = input();
    int b = input();
    int t = gcd(a, b);
    output(t);

    for (int i = 0; i < n; i++)
    {
        for (int index = 0; index < n - i - 1; index++)
        {
            if (arr[index] < arr[index + 1])
            {
                int swap;
                swap = arr[index];
                arr[index] = arr[index + 1];
                arr[index + 1] = swap;
            }
        }
    }
}