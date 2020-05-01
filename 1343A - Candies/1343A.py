#python3
from math import log2

t = int(input())

# n is bounded to 10^9
# where i=34, 2^i > 17*10^9
# we always look for the largest x
qs = [2**i for i in range(34)]
for _ in range(t):
    n = int(input())
    x = None
    for q in reversed(qs):
        x = n / (q - 1)
        if x.is_integer():
            break
    assert x.is_integer()
    # k = log2(n/x + 1)
    # print(f'k = {k}, x = {x}')
    print(int(x))
