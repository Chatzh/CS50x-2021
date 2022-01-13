#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Promot user to enter credit card number
    long card_number;
    do
    {
        card_number = get_long("Number: ");
    }
    while (card_number < 0);


    // Calculate the checksum
    int check_sum = 0;
    for (long i = 0, m = 10; i < 8; i++, m *= 100)
    {
        int d = (card_number / m) % 10; // current other digit
        check_sum += (d * 2) % 10 + (d * 2) / 10;
    }
    printf("%i\n", check_sum);

    for (long i = 0, m = 1; i < 8; i++, m *= 100)
    {
        int d = (card_number / m) % 10;
        check_sum += d;
    }
    printf("%i\n", check_sum);


    // Check the card length and What type the card is
    if (check_sum % 10 == 0)
    {
        if (card_number / 10000000000000 == 34 || card_number / 10000000000000 == 37)
        {
            printf("AMEX\n");
        }
        else if (card_number / 100000000000000 >= 51 && card_number / 100000000000000 <= 55)
        {
            printf("MASTERCARD\n");
        }
        else if (card_number / 1000000000000 == 4 || card_number / 1000000000000000 == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

}