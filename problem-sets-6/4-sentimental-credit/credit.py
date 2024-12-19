import cs50

card_num = cs50.get_int("Your Card Number is: ")


def main():
    if luhn_Check(card_num):
        car_company_check(card_num)
    else:
        print("INVALID")


def luhn_Check(card_num):
    sum = 0
    str_card = str(card_num)
    reverse_card_num = str_card[::-1]

    for i in range(len(str_card)):
        digit = int(reverse_card_num[i])
        if i % 2 == 1:
            digit = digit * 2
            if digit >= 10:
                digit -= 9
        sum += digit

    if sum % 10 == 0:
        return True
    else:
        return False


def car_company_check(card_num):
    str_num = str(card_num)
    length = len(str_num)
    if length == 15 and str_num[:2] in ["34", "37"]:
        print("AMEX")
    elif length == 16 and 51 <= int(str_num[:2]) <= 55:
        print("MASTERCARD")
    elif length == 13 or length == 16 and str_num[0] == "4":
        print("VISA")
    else:
        print("INVALID")


main()
