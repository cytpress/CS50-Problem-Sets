import cs50

while True:
    n = cs50.get_int("Height: ")
    if n <= 8 and n >= 1:
        break


def main():
    for i in range(n):
        print_row(n - i - 1, i + 1)


def print_row(spaces, bricks):
    for i in range(spaces):
        print(" ", end="")

    for i in range(bricks):
        print("#", end="")

    print("  ", end="")

    for i in range(bricks):
        print("#", end="")

    print()


main()
