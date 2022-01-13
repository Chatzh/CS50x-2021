#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    int L = count_letters(text);
    int W = count_words(text);
    int S = count_sentences(text);

    float index = 0.0588 * L / W * 100 - 0.296 * S / W * 100 - 15.8;
    index = (index - (int) index >= 0.5) ? (int) index + 1 : index;

    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index >= 1)
    {
        printf("Grade %i\n", (int) index);
    }
    else
    {
        printf("Before Grade 1\n");
    }

}

int count_letters(string text)
{
    int count = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            count++;
        }
    }
    //printf("%i letter(s)\n", count);
    return count;
}

int count_words(string text)
{
    int count = 1;

    for (int i = 1, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]) && !isalpha(text[i - 1]) && text[i - 1] != '-' && text[i - 1] != '\'')
        {
            count++;
        }
    }
    //printf("%i word(s)\n", count);
    return count;
}

int count_sentences(string text)
{
    int count = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }
    //printf("%i sentence(s)\n", count);
    return count;
}