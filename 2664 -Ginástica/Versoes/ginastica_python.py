import math

aux = input().split(' ')
t, m, n = int(aux[0]), int(aux[1]), int(aux[2])
first_line = n-m + 1
second_line = (2*(n-m))
lines = []
lines.extend([first_line, second_line])
for i in range(2, t):
	lines.append((lines[i-2]+lines[i-1]) % ((math.pow(10, 9)+7)))

lines = sorted(lines)
print(int(lines[-1]%(math.pow(10, 9)+7)))