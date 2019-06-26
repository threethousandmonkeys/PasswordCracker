# Use two wordlist text file to count the frequency of common passwords
# Then apply then to smart brute force in crack.c

from collections import Counter
ASCII_32 = 32
ASCII_126 = 126

def count_freq(filename):
    fl = open(filename, mode='r')
    words = fl.read()
    dic = Counter(words)
    # print("Count of all characters in text file is :\n " +  str(dic))
    word_list = words.split('\n')
    for word in word_list.copy():
        if len(word) != 4 and len(word) != 6:
            word_list.remove(word)
    print('\n'.join(word_list))
    fl.close()
    return dic
    
dic1 = count_freq("common_passwords.txt")
# Counter({'\n': 9742, 'e': 5849, 'a': 5399, 'r': 4131, 'o': 4052, 'n': 3821, 
# 'i': 3754, 's': 3571, 't': 3082, 'l': 3032, 'c': 2080, 'd': 2017, 'm': 1952, 
# 'h': 1771, 'g': 1612, 'b': 1593, 'u': 1564, 'p': 1478, '1': 1351, 'y': 1334, 
# 'k': 1085, 'f': 873, 'w': 844, '2': 588, 'v': 578, 'j': 449, '3': 397, 
# 'z': 374, '0': 367, '4': 335, '5': 328, '9': 321, '6': 309, 'x': 308, 
# '7': 275, '8': 220, 'q': 189, '*': 15, '?': 11, '.': 5, '+': 2, '-': 2, 
# '&': 2, ';': 1, "'": 1, '!': 1, '\\': 1})

dic2 = count_freq("pwd_list_1.txt")
#  Counter({'\n': 998, 'e': 252, 'a': 176, 'o': 155, 'l': 151, 't': 132, 
# 'r': 116, 's': 115, 'i': 108, 'n': 107, 'd': 88, 'h': 70, 'k': 59, 'm': 58, 
# 'w': 56, 'c': 55, 'p': 54, 'u': 51, 'f': 48, 'b': 38, 'g': 37, 'y': 34, 
# 'v': 20, 'j': 8, 'x': 3, 'z': 3, 'E': 1, 'R': 1, 'M': 1, 'C': 1, 'O': 1, 
# 'G': 1})

dic3 = dic1 + dic2
# print(dic3)
# Counter({'\n': 10740, 'e': 6101, 'a': 5575, 'r': 4247, 'o': 4207, 'n': 3928, 
# 'i': 3862, 's': 3686, 't': 3214, 'l': 3183, 'c': 2135, 'd': 2105, 'm': 2010, 
# 'h': 1841, 'g': 1649, 'b': 1631, 'u': 1615, 'p': 1532, 'y': 1368, '1': 1351, 
# 'k': 1144, 'f': 921, 'w': 900, 'v': 598, '2': 588, 'j': 457, '3': 397, 
# 'z': 377, '0': 367, '4': 335, '5': 328, '9': 321, 'x': 311, '6': 309,
#  '7': 275, '8': 220, 'q': 189, '*': 15, '?': 11, '.': 5, '+': 2, '&': 2, 
# '-': 2, 'C': 1, '!': 1, 'G': 1, 'E': 1, '\\': 1, ';': 1, 'M': 1, 'R': 1, 
# 'O': 1, "'": 1})

# The alphabetical result: (Descending)
# earonistlcdmhgbupykfwvjzxqGEMRO

# The numerical result: (Descending)
# 1230459678

# The whole case result: (Descending)
# earonistlcdmhgbupy1kfwv2j3z0459x678q*?.+&-C!GE\;MRO'

# Other ASCII but haven't occur in those two commom wordlist file:
# earonistlcdmhgbupy1kfwv2j3z0459x678q*?.+&-C!GE\;MRO' "#$%(),/:<=>@ABDFHIJKLNPQSTUVWXYZ[]^_`{|}
whole_char = "earonistlcdmhgbupy1kfwv2j3z0459x678q*?.+&-C!GE\;MRO'"
for i in range(ASCII_32,ASCII_126):
    if chr(i) not in whole_char:
        whole_char = whole_char + chr(i)

print(whole_char)

