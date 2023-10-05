import csv
import sys
from typing import Optional


class DNAMatcher:
    """Implements DNA Matcher."""

    _data = {}

    def __init__(self, data, strategy) -> None:
        self._strategy = strategy
        self._data = data

    def check(self, seq: str) -> Optional[str]:
        match = None
        for name in self._data:
            matches = []
            for key, value in self._data[name].items():
                res = self._strategy(seq, key)
                matches.append(res == int(value))

            # check the sequnce matching results
            if False not in matches and match is None:
                match = name
                break

        return match


def main():
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # Read database file into a variable
    data = {}
    with open(sys.argv[1]) as file:
        for line in csv.DictReader(file):
            name = line.pop("name")
            data[name] = line

    # Read DNA sequence file into a variable
    seq = ""
    with open(sys.argv[2]) as file:
        for line in file:
            seq = line

    strategy = longest_match
    dna_matcher = DNAMatcher(data, strategy)

    name = dna_matcher.check(seq)
    if name is None:
        print("No match")
    else:
        print(name)

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


if __name__ == "__main__":
    main()
