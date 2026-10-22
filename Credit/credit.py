card_number = input("Credit card number: ")

if len(card_number) == 15 and card_number.startswith(("34", "37")):
    result = 'AMEX'
elif len(card_number) == 16 and card_number.startswith(("51", "52", "53", "54", "55")):
    result = 'MasterCard'
elif len(card_number) in (13, 16) and card_number[:1] == "4":
    result = 'Visa'
else:
    result = 'INVALID'

if result != 'INVALID':
    card_number = card_number[::-1]

    k = 1
    sum = 0

    for c in card_number:
        if k % 2 == 0:
            number = str(int(c) * 2)
            for n in number:
                sum += int(n)
        else:
            sum += int(c)
        k += 1

    if sum % 10 != 0:
        result = "INVALID"

print(result)