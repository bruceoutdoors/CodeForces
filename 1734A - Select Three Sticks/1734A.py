# python3
t = int(input())

for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    a = sorted(a)
    min_diffs = min([a[i+2] - a[i] for i in range(n - 2)])
    print(min_diffs)
