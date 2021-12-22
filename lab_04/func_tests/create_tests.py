import random

ELEMENTS = [10, 50, 100, 250, 500]


def main():
    for num in ELEMENTS:
        file_list = open("{}_list.txt".format(num), "w")
        file_arr = open("{}_arr.txt".format(num), "w")

        file_list.write("1\n")
        file_arr.write("2\n")

        for i in range(num - 5):
            new = random.randint(-300, 300)
            file_list.write("{}\n".format(new))
            file_arr.write("{}\n".format(new))

        file_list.write("NULL\n")
        file_arr.write("NULL\n")

        for i in range(5):
            new = random.randint(-300, 300)
            file_list.write("{}\n".format(new))
            file_arr.write("{}\n".format(new))

        file_list.write("NULL\n")
        file_arr.write("NULL\n")


if __name__ == '__main__':
    main()
