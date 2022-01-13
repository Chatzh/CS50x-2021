from cs50 import get_int

height = 0
while True:
    height = get_int("Height: ")
    if height > 0 and height < 9:
        break


def print_block(h):
    if h == 0:
        return

    print_block(h - 1)

    for i in range(height - h):
        print(" ", end="")
    for i in range(h):
        print("#", end="")

    print("  ", end="")

    for i in range(h):
        print("#", end="")

    print()


print_block(height)