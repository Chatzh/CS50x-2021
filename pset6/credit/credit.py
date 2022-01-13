from cs50 import get_int

card_number = 0
while True:
    card_number = get_int("Number: ")
    if card_number >= 0:
        break

check_sum = 0
m = 10
for i in range(8):
    d = int(card_number / m) % 10
    check_sum += (d * 2) % 10 + int((d * 2) / 10)
    m *= 100

m = 1
for i in range(8):
    d = int(card_number / m) % 10
    check_sum += d
    m *= 100

if check_sum % 10 == 0:
    if int(card_number / 10000000000000) == 34 or int(card_number / 10000000000000) == 37:
        print("AMEX")
    elif int(card_number / 100000000000000) >= 51 and int(card_number / 100000000000000) <= 55:
        print("MASTERCARD")
    elif int(card_number / 1000000000000) == 4 or int(card_number / 1000000000000000) == 4:
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")