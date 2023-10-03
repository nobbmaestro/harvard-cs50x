# Problem Set 6: Mario


def build_pyramid_printout(height: int) -> str:
    printout = ""

    for i in range(1, height + 1):
        num_whitespc = height - i
        printout += " " * (num_whitespc)
        printout += "#" * (height - num_whitespc)
        printout += "  "
        printout += "#" * (height - num_whitespc)
        printout += "\n" if i < height else ""

    return printout


def main() -> None:
    height = 0
    while height < 1 or height > 8:
        try:
            height = int(input("Height: "))

        except ValueError:
            print("usage: python mario.py [int]")

    printout = build_pyramid_printout(height)
    print(printout)


if __name__ == "__main__":
    main()
