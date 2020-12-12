#pragma warning(disable : 4996)

#include <stdio.h>
#include<string.h>

#define MAXSIZE 100
#define MAXMAXSIZE 1000
#define MATRIX_SIZE 5

char password[MAXSIZE];
char readText[MAXMAXSIZE];
char keyT[MATRIX_SIZE][MATRIX_SIZE];
char text[MAXMAXSIZE];

void search(char a, char b, int arr[])
{
	int i, j;

	if (a == 'j')
		a = 'i';
	else if (b == 'j')
		b = 'i';

	for (i = 0; i < 5; i++) {

		for (j = 0; j < 5; j++) {

			if (keyT[i][j] == a) {
				arr[0] = i;
				arr[1] = j;
			}
			else if (keyT[i][j] == b) {
				arr[2] = i;
				arr[3] = j;
			}
		}
	}
}

void encryptingFairplay()
{
	int i, a[4];

	for (i = 0; i < strlen(readText); i += 2) {

		search(readText[i], readText[i + 1], a);

		if (a[0] == a[2]) {
			readText[i] = keyT[a[0]][(a[1] + 1) % 5];
			readText[i + 1] = keyT[a[0]][(a[3] + 1) % 5];
		}
		else if (a[1] == a[3]) {
			readText[i] = keyT[(a[0] + 1) % 5][a[1]];
			readText[i + 1] = keyT[(a[2] + 1) % 5][a[1]];
		}
		else {
			readText[i] = keyT[a[0]][a[3]];
			readText[i + 1] = keyT[a[2]][a[1]];
		}
	}
}

void decryptingFairplay()
{
	int i, a[4];
	for (i = 0; i < strlen(readText); i += 2) {
		search(readText[i], readText[i + 1], a);
		if (a[0] == a[2]) {
			readText[i] = keyT[a[0]][(a[1] - 1) % 5];
			readText[i + 1] = keyT[a[0]][(a[3] - 1) % 5];
		}
		else if (a[1] == a[3]) {
			readText[i] = keyT[(a[0] - 1) % 5][a[1]];
			readText[i + 1] = keyT[(a[2] - 1) % 5][a[1]];
		}
		else {
			readText[i] = keyT[a[0]][a[3]];
			readText[i + 1] = keyT[a[2]][a[1]];
		}
	}
}
void GenerateKeyTFairplay() {

	int i, j, k, flag = 0, dicty[26] = { 0 };

	for (i = 0; i < strlen(password); i++) {
		password[i] = tolower(password[i]);
	}

	printf("\nKey Table:");

	for (i = 0; i < strlen(password); i++) {
		if (password[i] != 'j')
			dicty[password[i] - 97] = 2;
	}

	dicty['j' - 97] = 1;

	i = 0;
	j = 0;

	for (k = 0; k < strlen(password); k++) {
		if (dicty[password[k] - 97] == 2) {
			dicty[password[k] - 97] -= 1;
			keyT[i][j] = password[k];
			j++;
			if (j == 5) {
				i++;
				j = 0;
			}
		}
	}

	for (k = 0; k < 26; k++) {
		if (dicty[k] == 0) {
			keyT[i][j] = (char)(k + 97);
			j++;
			if (j == 5) {
				i++;
				j = 0;
			}
		}
	}

	printf("\n");
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			printf("%c ", keyT[i][j]);
		}
		printf("\n");
	}
}

void ReadText(FILE* f_input) {

	int length = 0, i;
	char temp_text[MAXMAXSIZE];

	while (fgets(temp_text, MAXMAXSIZE, f_input) != NULL) {

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

int Fairplay(void) {
	FILE* f_input;
	int in;

	fopen_s(&f_input, "Text.txt", "rt");

	if (f_input == NULL) {
		printf("Error when we try to open the Input.txt!!!\n");
		return 0;
	}

	printf("\n\n1 -> Encryption\n2 -> Decryption\n\n");
	scanf_s("%d", &in);

	if (in == 1 || in == 2) {

		printf("\nEnter your password:");
		scanf("%s", password);

		GenerateKeyTFairplay();

		ReadText(f_input);

		if (in == 1) {
			encryptingFairplay();
			printf("Encrypted text: %s\n", readText);
		}
		else {
			decryptingFairplay();
			printf("Decrypted text: %s\n", readText);
		}

	}
	else {
		printf("!!!!!Invalid input!!!!!\n");
	}

	fclose(f_input);
	return 0;
}