import cs50

while True:
    cents = cs50.get_float("Change owed: ")
    if cents >= 0:
        break


def main():
    n = int(cents * 100)
    print(calculate_coins(n))


def calculate_coins(cents):
    i = 0
    while cents >= 25:
        i += 1
        cents -= 25

    while cents >= 10:
        i += 1
        cents -= 10

    while cents >= 5:
        i += 1
        cents -= 5

    while cents >= 1:
        i += 1
        cents -= 1

    return i


main()
