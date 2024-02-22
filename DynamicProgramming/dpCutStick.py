length = 4
priceList = [0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30]
dp = [None for _ in range(length + 5)]


def f(n):

    if n == 1:
        return 1

    if dp[n] is not None:
        return dp[n]

    maxPrice = priceList[n]
    for i in range(1, n-1):
        subProblemResult = f(n - i)
        if maxPrice < priceList[i] + subProblemResult:
            maxPrice = priceList[i] + subProblemResult

    dp[n] = maxPrice
    return dp[n]


print(f(length))
