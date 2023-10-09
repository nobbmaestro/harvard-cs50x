# Problem Set 6: Readibility


class ScoringColemanLiauIndex:
    """Implements Coleman-Liau's Algorithm.'"""

    _a = 0.0588
    _b = 0.296
    _c = 15.8

    _sentence_delimiters = (".", "!", "?")
    _word_delimiters = (".", " ")

    _cache = {}

    def grade(self, text: str) -> float:
        """Getter for the grade of `text`."""
        self._cache.clear()
        self._cache["text"] = text

        return self._calculate_coleman_liau_index()

    def _calculate_coleman_liau_index(self) -> float:
        """Getter for the calculated Coleman-Liau Index."""
        L = self._calculate_avg_num_letters_per_100_words()
        S = self._calculate_avg_num_senteces_per_100_words()

        return (self._a * L) - (self._b * S) - self._c

    def _get_num_letters(self) -> int:
        """Getter for number of letters in text helper."""
        # check whether sentences are already counted
        if "sum_letters" not in self._cache:
            count = 0
            for char in self._cache["text"]:
                if char.isalpha():
                    count += 1

            # add counted sum to the cache
            self._cache["sum_letters"] = count

        return self._cache["sum_letters"]

    def _get_num_sentences(self) -> int:
        """Getter for number of sentences in text helper."""
        # check whether sentences are already counted
        if "sum_sentences" not in self._cache:
            count = 0
            for char in self._cache["text"]:
                if char in self._sentence_delimiters:
                    count += 1

            # add counted sum to the cache
            self._cache["sum_sentences"] = count

        return self._cache["sum_sentences"]

    def _get_num_words(self) -> int:
        """Getter for number of words in text helper."""
        # check whether sentences are already counted
        if "sum_words" not in self._cache:
            count = 0
            for char in self._cache["text"]:
                if char in self._word_delimiters:
                    count += 1
            # add counted sum to the cache
            self._cache["sum_words"] = count

        return self._cache["sum_words"]

    def _calculate_avg_num_letters_per_100_words(self) -> float:
        """Calcalate average number of letters per 100 words."""
        letters = self._get_num_letters()
        words = self._get_num_words()

        return (letters / words) * 100.00

    def _calculate_avg_num_senteces_per_100_words(self) -> float:
        """Calcalate average number of senteces per 100 words."""
        sentences = self._get_num_sentences()
        words = self._get_num_words()

        return (sentences / words) * 100.00


class TextGrader:
    """Implements text grader."""

    def __init__(self, strategy) -> None:
        self.strategy = strategy

    def grade(self, text: str) -> str:
        """Getter for the grade of the `text`."""
        grade = self.strategy.grade(text)
        return self._create_printout(grade)

    def _create_printout(self, grade) -> str:
        """Create pretty printout."""
        printout = ""
        if grade < 1:
            printout += "Before Grade 1"
        elif grade >= 16:
            printout += "Grade 16+"
        else:
            printout += "Grade "
            printout += str(round(grade))
        printout += "\n"

        return printout


def main():
    strategy = ScoringColemanLiauIndex()
    grader = TextGrader(strategy)

    text = input("Text: ")
    print(grader.grade(text))


if __name__ == "__main__":
    main()
