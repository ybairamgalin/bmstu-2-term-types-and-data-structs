import random

COLS = 250
ROWS = 250

EMPTY_PERCENT = 98

matrix = []
non_zero = 0

for i in range(COLS):
    row = []
    elem = None

    for j in range(ROWS):
        if random.random() > EMPTY_PERCENT / 100:
            elem = random.randint(-20, 20)
            non_zero = non_zero + 1
        else:
            elem = 0

        row.append(elem)

    matrix.append(row)

file = open(f"data/{COLS}x{ROWS}_{100-EMPTY_PERCENT}_1.txt", "w")

file.write(str(COLS) + "\n")
file.write(str(ROWS) + "\n")
file.write(str(non_zero) + "\n")

for row in matrix:
    file.write(" ".join(str(num) for num in row))
    file.write("\n")

file.close()
