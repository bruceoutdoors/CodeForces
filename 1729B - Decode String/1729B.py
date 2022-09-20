#python3
from string import ascii_lowercase

q = int(input())

for _ in range(q):
    n = int(input())
    t = input()
    
    seq = []
    i = n - 1 # read from reverse
    while i >= 0:
        c = t[i]
        if c == '0':
            c = t[i - 2:i]
            i -= 3
        else:
            i -= 1
        seq.append(ascii_lowercase[int(c) - 1])
    print(''.join(reversed(seq)))
