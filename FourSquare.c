#pragma warning(disable : 4996)

#include<string.h>
#include<stdio.h>

char keyTable[10][10];
char readText[1000];

struct index
{
    int x, y;
};

void toLowerArray(char* text) {
    int index;
    for (index = 0; index < strlen(text); index++) {
        text[index] = tolower(text[index]);
    }
}

void GenerateKeyTFourSquare(char* password1, char* password2)
{
    int i, j;
    int table1 = 97;
    int lpassword1 = 0, frequencyArrayPass1[26] = { 0 }, indexFrequnecyArrayPass1= 0;
    int table2 = 97;
    int lpassword2=0, frequencyArrayPass2[26] = { 0 }, indexFrequnecyArrayPass2=0;

    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            if (i < 5)
            {
                if (j < 5)
                {
                    if (table1 == 'j') {
                        table1++;
                    }
                    keyTable[i][j] = table1;
                    table1++;
                }
                else
                {
                    while ((password1[lpassword1] == 'j' || frequencyArrayPass1[password1[lpassword1] - 97] == 1) && lpassword1 < strlen(password1)) {
                        lpassword1++;
                    }
                    if (lpassword1 < strlen(password1))
                    {
                        keyTable[i][j] = password1[lpassword1];
                        frequencyArrayPass1[password1[lpassword1] - 97] = 1;
                        lpassword1++;
                    }
                    else
                    {
                        while (frequencyArrayPass1[indexFrequnecyArrayPass1] == 1 || indexFrequnecyArrayPass1+97=='j')
                        {
                            indexFrequnecyArrayPass1++;
                        }
                        keyTable[i][j] = indexFrequnecyArrayPass1 + 97;
                        indexFrequnecyArrayPass1++;
                    }

                }
            }
            else
            {
                if (j < 5)
                {
                    while ((password2[lpassword2] == 'j' || frequencyArrayPass2[password2[lpassword2]-97]==1) && lpassword2<strlen(password2)) {
                        lpassword2++;
                    }
                    if (lpassword2 < strlen(password2))
                    {
                        keyTable[i][j] = password2[lpassword2];
                        frequencyArrayPass2[password2[lpassword2]- 97] = 1;
                        lpassword2++;
                    }
                    else
                    {
                        while (frequencyArrayPass2[indexFrequnecyArrayPass2] == 1 || indexFrequnecyArrayPass2 + 97=='j')
                        {
                            indexFrequnecyArrayPass2++;
                        }
                        keyTable[i][j] = indexFrequnecyArrayPass2 + 97;
                        indexFrequnecyArrayPass2++;
                    }
                }
                else
                {

                    if (table2 == 'j') {
                        table2++;
                    }
                    keyTable[i][j] = table2;
                    table2++;
                }
            }
          printf("%c ", keyTable[i][j] );
        }
        printf("\n");
    }

}

//tb1 -> 0, 5 for all
//tb2 -> 0,5 and 5,10
//tb3 -> 5, 10; 0,5
//tb4 -> 5, 10 for all

struct index SearchInTable(char ch, int lines, int columns, int startline, int startcolumn)
{
    int i, j;
    struct index f;
    f.x = f.y = -1;
    for (i = startline; i < lines; i++)
    {
        for (j = startcolumn; j < columns; j++)
        {
            if (keyTable[i][j] == ch)
            {
                f.x = i;
                f.y = j;
                return f;
            }
        }
    }
    return f;
}

void encryptFourSquare()
{
    int i, ax, ay, bx, by;
    struct index letter1;
    struct index letter2;
    for (i = 0; i < strlen(readText)-1; i += 2)
    {
        //search into the first square
        letter1 = SearchInTable(readText[i],5,5,0,0);
        //search into the square four
        letter2 = SearchInTable(readText[i + 1], 10, 10, 5, 5);

        ax = letter1.x;
        ay = letter2.y;
        bx = letter2.x;
        by = letter1.y;
        
        printf("%c%c", keyTable[ax][ay], keyTable[bx][by]);
    }
}

void decryptFourSquare()
{
    int i, ax, ay, bx, by;
    struct index letter1;
    struct index letter2;
    for (i = 0; i < strlen(readText)-1; i += 2)
    {
        //search into the second square
        letter1 = SearchInTable(readText[i],5,10,0,5);
        //search into the square tree
        letter2 = SearchInTable(readText[i + 1],10,5,5,0);

        ax = letter1.x;
        ay = letter2.y;
        bx = letter2.x;
        by = letter1.y;
        
        printf("%c%c", keyTable[ax][ay], keyTable[bx][by]);
    }
}

void ReadTextFourSquare(FILE* f_input) {

	int length = 0, i;
	char temp_text[1000];

	while (fgets(temp_text, 1000, f_input) != NULL) {

		for (i = 0; i < strlen(temp_text); i++) {

			if (tolower(temp_text[i]) >= 'a' && tolower(temp_text[i]) <= 'z')
			{
				readText[length] = tolower(temp_text[i]);

				if (length % 2 == 1 && readText[length - 1] == readText[length])
				{
					readText[length] = 'x';
				}

				length++;
			}
		}
	}

	if (length % 2 == 1) {
		readText[length++] = 'x';
	}

	readText[length] = '\0';
}

int FourSquare(void) {
	FILE* f_input;
	int in;
    char password1[1000], password2[1000];

	fopen_s(&f_input, "Text.txt", "rt");

	if (f_input == NULL) {
		printf("Error when we try to open the Input.txt!!!\n");
		return 0;
	}

	printf("\n\n1 -> Encryption\n2 -> Decryption\n\n");
	scanf_s("%d", &in);

	if (in == 1 || in == 2) {

		printf("\nEnter your first password:");
		scanf("%s", password1);
		printf("\nEnter your second password:");
		scanf("%s", password2);

        toLowerArray(password1);
        toLowerArray(password2);

        printf("key: \n");
		GenerateKeyTFourSquare(password1,password2);

		ReadTextFourSquare(f_input);
        toLowerArray(readText);

		if (in == 1) {
            printf("Encrypted text: ");
			encryptFourSquare();
            printf("\n\n");
		}
		else {
            printf("Decrypted text: ");
			decryptFourSquare();
            printf("\n\n");
		}

	}
	else {
		printf("!!!!!Invalid input!!!!!\n");
	}

	fclose(f_input);
	return 0;
}