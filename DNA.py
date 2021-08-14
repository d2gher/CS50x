from sys import argv, exit
from csv import DictReader, reader


def main():
    # If the user didn't provide 2 command line arguments after the program's name, exit
    if len(argv) != 3:
        exit("USAGE: python dna.py [database.csv] [sequences.txt]")

    STRs = []
    data = []

    # Read the DNA dataBase with the STRs numbers for each person into memory
    with open(argv[1], "r") as dataBase:
        # Frist read the first line of the csv file
        # Which contains the word "name", then the name of each STR, sapareted by commas
        Reader = reader(dataBase)
        for seq in Reader:
            # Add that data to the list STRs as its first element
            # Then make the whole list just the first element. Then remove the frist element of it i.e. "name"
            STRs.append(seq)
            STRs = STRs[0]
            STRs.remove(STRs[0])
            break

        # Go back to the start of the file, then read the actual DNA data for each person into memory
        dataBase.seek(0)
        Reader = DictReader(dataBase)
        for person in Reader:
            data.append(person)

    # Read the DNA we're searching for into memory
    with open(argv[2], "r") as sequances:
        DNA = sequances.read()

    # Find the longest chain for each str
    STRs_chains = {}
    for i in range(len(STRs)):
        STRs_chains[STRs[i]] = sequance_chain(DNA, STRs[i])

    # Find which person in our dataBase has the same number of str chains
    find_match(data, STRs_chains, STRs, len(data))


# For finding the longest str chain we have in the dna
def sequance_chain(sequance, STR):
    STR_length = len(STR)
    seq_length = len(sequance)
    count = 0
    longest = 0

    # Search for the location of the first mention of the str
    curser = sequance.find(STR)
    # Repeat so long as there is still STRs by that name in the list
    while curser != -1:
        # If the str is followed directly by str of the same name, start/continue counting
        if sequance[curser: curser + STR_length] == sequance[curser + STR_length: curser + (STR_length * 2)]:
            count += 1
        else:
            # If the current count is longer than longest, make longest equal to countn
            # then reset count
            if longest < count:
                longest = count
                count = 0
        # move on to the next mention of the str in the list
        curser = sequance.find(STR, curser + 1)

    # Return the longest continuous str with an added 1 for the last one
    return longest + 1


# Find if a person in our dataBase has the same DNA as the one provided
def find_match(dataBase, STRs_chains, STRs, length):
    # If we have go through every person in our dataBase,
    # and haven't found a match
    if length < 1:
        print("no match")
        return

    # compare the current person's first str to the one provided
    if int(dataBase[length - 1].get(STRs[0])) == STRs_chains[STRs[0]]:
        # If they match, compare every other str.
        # And if the match, print that person's name, and exist the function
        if continue_chain(dataBase[length - 1], STRs_chains, STRs):
            print(dataBase[length - 1].get("name"))
            return

    # If we reached here, that means the current person isn't a match
    # Go to the next person on the list
    find_match(dataBase, STRs_chains, STRs, length - 1)


# Compare the provided STR chains with one person
def continue_chain(person, STRs_chains, STRs):
    # Compare every STR and return False if any of them don't match
    for i in range(len(STRs)):
        if int(person.get(STRs[i])) != STRs_chains[STRs[i]]:

            return False
    # Else, that means they match, return True
    return True


main()
