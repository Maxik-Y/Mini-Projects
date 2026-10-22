import csv

database = []
dna_sequence = []

with open("databases/large.csv", "r") as file:
    reader = csv.DictReader(file)

    str_names = reader.fieldnames[1:] 

    for row in reader:
        database.append(row)

with open("sequences/19.txt", "r") as file:
    dna_sequence = file.read()

result = dict.fromkeys(str_names, 0)

k = 0

length = len(dna_sequence)
for name in str_names:
    max = 0
    i = 0
    while i < length:
        if dna_sequence[i:i+len(name)] == name:
            i += len(name) - 1
            k += 1
            if max < k:
                max = k
        else:
            k = 0
        i += 1
    result[name] = max

k = 0

for person in database:
    for name in str_names:
        if int(person[name]) == result[name]:
            k += 1
        else:
            break
    if (k == len(str_names)):
        print(person["name"])
    else:
        print("No match") 
    k = 0

