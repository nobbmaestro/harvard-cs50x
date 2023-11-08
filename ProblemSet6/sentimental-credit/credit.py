# Problem Set 6: Credit


class ValidateCard:
    """Base card validator."""
    number_len = 0
    valid_digits = (0, )

    def check(self, number: int) -> bool:
        """Check card number validity."""
        return self._check(number)

    def _check(self, number: int) -> bool:
        """Internal chech card number validity."""
        valid = self._check_number_len(number)
        valid &= self._check_valid_digits(number)

        return valid

    def _check_number_len(self, number: int) -> bool:
        """Verify card number length."""
        return len(str(number)) == self.number_len

    def _check_valid_digits(self, number: int) -> bool:
        """Verify initial digits."""
        # Get number of digits that are of interest
        num_digits = len(str(self.valid_digits[0]))

        # Get the starting digits of the card number
        digits = int(str(number)[:num_digits])

        return digits in self.valid_digits


class ValidateAmex(ValidateCard):
    """Implements AMEX card validator."""
    number_len = 15
    valid_digits = (31, 37)


class ValidateMasterCard(ValidateCard):
    """Implements MasterCard card validator."""
    number_len = 16
    valid_digits = (51, 52, 53, 54, 55)


class ValidateVisa(ValidateCard):
    """Implements Card card validator."""
    number_len_lo = 13
    number_len_hi = 16
    valid_digits = (4, )

    def _check_number_len(self, number: int) -> bool:
        """Verify card number length."""
        num_len = len(str(number))
        return num_len >= self.number_len_lo and num_len <= self.number_len_hi


class ValidateLuhnsAlgorithm:
    """Implements Lugn's Algorithm."""

    def check(self, number: int) -> bool:
        """Check card number validity by performing Lugh's Algorithm."""
        number_str = str(number)
        n_digits = len(number_str)
        is_second = False
        sum = 0
        for i in range(n_digits - 1, -1, -1):
            digit = ord(number_str[i]) - ord('0')

            if is_second:
                digit = digit * 2

            sum += digit // 10
            sum += digit % 10

            is_second = not is_second

        return sum % 10 == 0


class CardNumberValidator:
    """Implements card number validator."""

    def __init__(self, validator, issuer_validator: dict) -> None:
        """Initialize CardNumberValidator.

        Args:
            validator: general validation algorithm
            issuer_validator: issuer specific validation algorithm

        """
        self.validator = validator
        self.issuer_validator = issuer_validator

    def check(self, number: int) -> str:
        """Check card number validity.

        Return card issuer if valid."""
        if self._check_valid_card_number(number):
            return self._get_card_issuer(number)
        else:
            return "INVALID"

    def _get_card_issuer(self, number: int) -> str:
        issuer = None
        for key, checker in self.issuer_validator.items():
            if checker.check(number):
                issuer = key

        if issuer is None:
            issuer = "INVALID"

        return issuer

    def _check_valid_card_number(self, number: int) -> bool:
        """Check card number validity by performing Lugh's Algorithm."""
        return self.validator.check(number)


def main():
    list_of_cards = {
        'AMEX': ValidateAmex(),
        'MASTERCARD': ValidateMasterCard(),
        'VISA': ValidateVisa(),
    }
    card_checker = CardNumberValidator(ValidateLuhnsAlgorithm(), list_of_cards)

    number = int(input("Number: "))

    print(card_checker.check(number))


if __name__ == "__main__":
    main()
