import csv
import sys


def main():

    # TODO: Check for command-line usage
    while True:
        if len(sys.argv) != 3:
            print("Usage: python dna.py data.csv sequence.txt")
            sys.exit(1)
        if len(sys.argv) == 3:
            break

    # TODO: Read database file into a variable
    # This will look like
    # [
    # {'name': 'Alice', 'AGAT': '28', 'AATG': '42', 'TATC': '14'},
    # {'name': 'Bob', 'AGAT': '17', 'AATG': '22', 'TATC': '19'},
    # {'name': 'Charlie', 'AGAT': '36', 'AATG': '18', 'TATC': '25'}
    # ]
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        rows = []
        for row in reader:
            rows.append(row)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2]) as file_dna:
        dna_sequence = file_dna.read()

    # TODO: Find longest match of each STR in DNA sequence
    # strs_dna will look like
    # ['AGAT', 'AATG', 'TATC']
    strs_dna = list(rows[0].keys())[1:]
    str_count = {}
    # will pass ['AGAT', 'AATG', 'TATC'] as str to longest_match()
    # and become
    # {
    #   AGAT : 28
    #   AATG : 21
    # }
    for str in strs_dna:
        str_count[str] = longest_match(dna_sequence, str)

    # TODO: Check database for matching profiles
    for person in rows:
        match = True
        for str in str_count:
            if int(person[str]) != str_count[str]:
                match = False
                break
        if match:
            print(person["name"])
            return

    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
