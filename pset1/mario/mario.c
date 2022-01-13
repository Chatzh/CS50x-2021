#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Promot user to give a height
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Print the pyramids line by line
    for (int i = 0; i < height; i++)
    {
        // Print the initial space
        for (int j = 0; j < height - i - 1; j++)
        {
            printf(" ");
        }

        // Print the left bricks
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }

        // Print the gap
        printf("  ");

        // Print the right bricks
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }

        printf("\n");
    }

}