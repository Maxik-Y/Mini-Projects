import re

text = input("Input text: ")

letters = len(re.findall(r'[a-zA-Z]', text))

words = len(text.split())

sentences = len(re.findall(r'[.!?]', text))

L = (letters / words) * 100
S = (sentences / words) * 100

index = round(0.0588 * L - 0.296 * S - 15.8)

print(f"Grade {index}")