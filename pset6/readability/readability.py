from cs50 import get_string


def main():
    text = get_string("Text: ")
    L = count_letters(text)
    W = count_words(text)
    S = count_sentences(text)

    index = 0.0588 * L / W * 100 - 0.296 * S / W * 100 - 15.8
    index = index + 1 if index - int(index) >= 0.5 else index

    if index >= 16:
        print("Grade 16+")
    elif index >= 1:
        print(f"Grade {int(index)}")
    else:
        print("Before Grade 1")


def count_letters(text):
    count = 0
    for char in text:
        if char.isalpha():
            count += 1

    return count


def count_words(text):
    count = 1
    for i in range(1, len(text)):
        if text[i].isalpha() and not text[i - 1].isalpha() and text[i - 1] != "-" and text[i - 1] != "'":
            count += 1

    return count


def count_sentences(text):
    count = 0
    for char in text:
        if char == "." or char == "!" or char == "?":
            count += 1

    return count


if __name__ == "__main__":
    main()