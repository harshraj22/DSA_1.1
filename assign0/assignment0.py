import sys

# Taking command line argument
argument_list = sys.argv

# checking if given file exists and if it is empty
try:
    file = open(argument_list[1], "r")
except IOError:
    print("File doesn't exists.")
    exit(0)
except:
    print("No argument given to read numbers")
    exit(0)

# Reading data
number = file.read()
file.close()

# Storing number in list of integers if all data is Integer
try:
    array = list(map(int, number.split()))
except:
    print("File also contains non-integers.")
    exit(0)


# Printing in expected format if file isn't empty
try:
    print(
        len(array),
        min(array),
        max(array),
        sum(array),
        round(sum(array) / len(array), 2),
        sep="\n",
    )
except:
    print("File is empty.")
