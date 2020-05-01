#python3

t = int(input())

# n is bounded to 10^9; where i=30, 2^i - 1 > 10^9
qs = [(1 << i) - 1 for i in range(30)]
for _ in range(t):
    n = int(input())
    for q in reversed(qs): # pick max x if available
        if n % q == 0:
            print(int(n / q))
            break
