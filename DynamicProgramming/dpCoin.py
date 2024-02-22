coinList = [1, 7, 10]

money = 18
dp = [None for _ in range(money + 1)]


def f(n):

    if dp[n] is not None:
        return dp[n]

    minCoin = 2 * n
    coins = []
    for coin in coinList:
        if n == coin:
            dp[n] = (1, [coin])
            return dp[n]
        if n > coin:
            c, coinUsed = f(n - coin)
            coinUsed = coinUsed[::]
            coinUsed.append(coin)
            if minCoin > c + 1:
                minCoin = c + 1
                coins = coinUsed

    dp[n] = (minCoin, coins)
    return dp[n]


print(f(money))