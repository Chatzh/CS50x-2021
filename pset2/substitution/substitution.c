#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int check_key(string key);
string substitution(string clear_text, string key);

int main(int argc, string argv[])
{
    if (argc == 2 && check_key(argv[1]) == 0)
    {
        string plaintext = get_string("plaintext: ");
        printf("ciphertext: %s\n", substitution(plaintext, argv[1]));
    }
    else if (argc == 2 && check_key(argv[1]) == 1)
    {
        printf("Key must contain 26 characters.\n");

        return 1;
    }
    else
    {
        printf("Usage: ./substitution key\n");

        return 1;
    }

    return 0;
}

// Check the key if it's valid.
int check_key(string key)
{
    if (strlen(key) == 26)
    {
        for (int i = 0; i < 26; i++)
        {
            if (!isalpha(key[i])) // If the key contain not alpha.
            {
                return 1;
            }
            // Check the letter if it's only show once.
            for (int j = 0; j < i; j++)
            {
                if (key[j] == key[i])
                {
                    return 1;
                }
            }
        }
    }
    else
    {
        return 2;
    }

    return 0;
}

// Make the key to all upper.
string key_to_upper(string key)
{
    string upper_key = key;

    for (int i = 0; i < 26; i++)
    {
        upper_key[i] = toupper(key[i]);
    }

    return upper_key;
}

// substitute the plaintext to ciphertext.
string substitution(string clear_text, string key)
{
    string upper_key = key_to_upper(key);
    string ciphertext = clear_text;

    for (int i = 0, n = strlen(clear_text); i < n; i++)
    {
        if (isalpha(clear_text[i]))
        {
            if (isupper(clear_text[i]))
            {
                ciphertext[i] = upper_key[clear_text[i] - 65];
            }
            else
            {
                ciphertext[i] = (char)(upper_key[clear_text[i] - 97] + 32);
            }
        }
    }

    return ciphertext;
}