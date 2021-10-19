import random

COLS = 10
ROWS = 10

EMPTY_PERCENT = 90

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

file = open(f"data/{COLS}x{ROWS}.txt", "w")

file.write(str(COLS) + "\n")
file.write(str(ROWS) + "\n")
file.write(str(non_zero) + "\n")

for row in matrix:
    file.write(" ".join(str(num) for num in row))
    file.write("\n")

matrix = []
non_zero = 0

for i in range(COLS):
    row = []
    elem = None

    for j in range(ROWS):
        if random.random() > EMPTY_PERCENT / 100:
            elem = random.randint(1, 30)
            non_zero = non_zero + 1
        else:
            elem = 0

        row.append(elem)

    matrix.append(row)

file.write(str(COLS) + "\n")
file.write(str(ROWS) + "\n")
file.write(str(non_zero) + "\n")

for row in matrix:
    file.write(" ".join(str(num) for num in row))
    file.write("\n")


file.close()
