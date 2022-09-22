# python3
from string import ascii_lowercase

t = int(input())
score = {x: i+1 for i, x in enumerate(ascii_lowercase)}

for _ in range(t):
    s = input()
    
    if s[0] > s[-1]:
        # if first is more than last, we iterate in reverse order, but retain the secondary sort in ascending order
        ss = sorted([(x, i) for i, x in enumerate(s)], key=lambda k: (k[0], -k[1]), reverse=True)
    else:
        ss = sorted([(x, i) for i, x in enumerate(s)])

    start = None
    end = None
    for i, x in enumerate(ss):
        if x[1] == 0 and start is None:
            start = i
        if x[0] == s[-1]:
            end = i

    max_score = abs(score[ss[end][0]] - score[ss[start][0]])
    max_jumps = end - start + 1
    path = [ss[x][1] + 1 for x in range(start, end + 1)]
    print(max_score, max_jumps)
    print(' '.join(map(str, path)))
