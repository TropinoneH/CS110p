test_input: list = [-6, -3, 5, 11]

for number in test_input:
    sum = 0
    if number > 0:
        for i in range(number + 1):
            sum += i * i
    elif number < 0:
        for i in range(number, 0):
            sum += i * i

    print(sum)
