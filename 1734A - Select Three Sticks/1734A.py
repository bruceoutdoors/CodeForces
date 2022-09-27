# python3
from statistics import median
from sys import maxsize
t = int(input())

for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    a = sorted(a)
    min_diffs = maxsize
    for i in range(n - 2):
        seg = a[i:i+3]
        mid = median(seg)
        min_diffs = min(min_diffs, sum([abs(mid - x) for x in seg]))
    print(min_diffs)
