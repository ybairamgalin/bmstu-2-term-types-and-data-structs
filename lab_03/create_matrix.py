import random

COLS = 6
ROWS = 10

matrix = []

for i in range(COLS):
    row = [(random.randint(-20, 20) if random.random() > 0.8 else 0) for j in range(ROWS)]
    matrix.append(row)

for row in matrix:
    for num in row:
        print(num, end="\t")
