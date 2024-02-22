priceList = [
    [6, 4, 8],
    [5, 10],
    [1, 5, 3, 5]
]

dp = [[None for _ in range(4)] for _ in range(21)]


def f(m, c):
    if c <= 0:
        return 0

    if dp[m][c] is not None:
        return dp[m][c]

    maxMoney = -1
    for price in priceList[c-1]:
        if m >= price:
            money = f(m - price, c-1) + price
            maxMoney = max(maxMoney, money)

    dp[m][c] = maxMoney
    return dp[m][c]


print(f(20, 3))
