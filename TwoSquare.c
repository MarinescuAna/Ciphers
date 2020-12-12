#pragma warning(disable : 4996)

#include<string.h>
#include<stdio.h>

char keyTable[10][10];
char readText[1000];

struct index
{
	int x, y;
};

void toLowerArrayTwoSquare(char* text) {
	int index;
	for (index = 0; index < strlen(text); index++) {
		text[index] = tolower(text[index]);
	}
}

void GenerateKeyTwoSquare(char* password1, char* password2)
{
	int i, j;
	int lpassword1 = 0, frequencyArrayPass1[26] = { 0 }, indexFrequnecyArrayPass1 = 0;
	int lpassword2 = 0, frequencyArrayPass2[26] = { 0 }, indexFrequnecyArrayPass2 = 0;

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 5; j++)
		{
			if (i < 5)
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
					while (frequencyArrayPass1[indexFrequnecyArrayPass1] == 1 || indexFrequnecyArrayPass1 + 97 == 'j')
					{
						indexFrequnecyArrayPass1++;
					}
					keyTable[i][j] = indexFrequnecyArrayPass1 + 97;
					indexFrequnecyArrayPass1++;
				}


			}
			else
			{

				while ((password2[lpassword2] == 'j' || frequencyArrayPass2[password2[lpassword2] - 97] == 1) && lpassword2 < strlen(password2)) {
					lpassword2++;
				}
				if (lpassword2 < strlen(password2))
				{
					keyTable[i][j] = password2[lpassword2];
					frequencyArrayPass2[password2[lpassword2] - 97] = 1;
					lpassword2++;
				}
				else
				{
					while (frequencyArrayPass2[indexFrequnecyArrayPass2] == 1 || indexFrequnecyArrayPass2 + 97 == 'j')
					{
						indexFrequnecyArrayPass2++;
					}
					keyTable[i][j] = indexFrequnecyArrayPass2 + 97;
					indexFrequnecyArrayPass2++;
				}

			}
			printf("%c ", keyTable[i][j]);
		}
		printf("\n");
	}

}

struct index SearchInTableTwoSquare(char ch, int lines, int columns, int startline, int startcolumn)
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

void encryptTwoSquare()
{
	int i, ax, ay, bx, by;
	struct index letter1;
	struct index letter2;
	for (i = 0; i < strlen(readText) - 1; i += 2)
	{
		//search into the first square
		letter1 = SearchInTableTwoSquare(readText[i], 5, 5, 0, 0);
		//search into the second square
		letter2 = SearchInTableTwoSquare(readText[i + 1], 10, 5, 5, 0);
		
		if (letter1.y == letter2.y) {
			if (letter1.x == 4) {
				letter1.x = 0;
			}
			else {
				letter1.x++;
			}

			ax = letter1.x;
			ay = letter1.y;

			if (letter2.x == 9) {
				letter2.x = 5;
			}
			else {
				letter2.x++;
			}

			bx = letter2.x;
			by = letter2.y;
		}
		else {
			ax = letter1.x;
			ay = letter2.y;
			bx = letter2.x;
			by = letter1.y;
		}
		printf("%c%c", keyTable[ax][ay], keyTable[bx][by]);
	}
}

void decryptTwoSquare()
{
	int i, ax, ay, bx, by;
	struct index letter1;
	struct index letter2;
	for (i = 0; i < strlen(readText) - 1; i += 2)
	{
		//search into the first square
		letter1 = SearchInTableTwoSquare(readText[i], 5, 5, 0, 0);
		//search into the second square
		letter2 = SearchInTableTwoSquare(readText[i + 1], 10, 5, 5, 0);

		if (letter1.y == letter2.y) {
			if (letter1.x == 0) {
				letter1.x = 4;
			}
			else {
				letter1.x--;
			}

			ax = letter1.x;
			ay = letter1.y;

			if (letter2.x == 5) {
				letter2.x = 9;
			}
			else {
				letter2.x--;
			}

			bx = letter2.x;
			by = letter2.y;
		}
		else {
			ax = letter1.x;
			ay = letter2.y;
			bx = letter2.x;
			by = letter1.y;
		}
		printf("%c%c", keyTable[ax][ay], keyTable[bx][by]);
	}
}

void ReadTextTwoSquare(FILE* f_input, int decrypt) {

	int length = 0, i;
	char temp_text[1000];

	while (fgets(temp_text, 1000, f_input) != NULL) {

		for (i = 0; i < strlen(temp_text); i++) {

			if (tolower(temp_text[i]) >= 'a' && tolower(temp_text[i]) <= 'z')
			{
				readText[length] = tolower(temp_text[i]);

				if (length % 2 == 1 && readText[length - 1] == readText[length] && decrypt!=1)
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

int TwoSquare(void) {
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

		toLowerArrayTwoSquare(password1);
		toLowerArrayTwoSquare(password2);

		printf("key: \n");
		GenerateKeyTwoSquare(password1, password2);

		ReadTextTwoSquare(f_input,in-1);

		if (in == 1) {
			printf("Encrypted text: ");
			encryptTwoSquare();
			printf("\n\n");
		}
		else {
			printf("Decrypted text: ");
			decryptTwoSquare();
			printf("\n\n");
		}

	}
	else {
		printf("!!!!!Invalid input!!!!!\n");
	}

	fclose(f_input);
	return 0;
}