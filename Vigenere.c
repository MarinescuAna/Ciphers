#pragma warning(disable : 4996)

#include <stdio.h>
#include<string.h>

#define MAXSIZE 100
#define MAXMAXSIZE 1000

char password[MAXSIZE];
char readText[MAXMAXSIZE];
char key[MAXMAXSIZE];

void decryptingVignere(int i) {
	char x;
	if (readText[i] >= 'A' && readText[i] <= 'Z')
	{
		x = (((readText[i] - key[i]) + 26) % 26) + 'A';

		printf("%c", x);
	}
	else {
		printf("%c", readText[i]);
	}

}

void encryptingVignere(int i) {

	char x;
	char letter = toupper(readText[i]);
	if (letter >= 'A' && letter <= 'Z')
	{
		x = ((letter + key[i]) % 26) + 'A';

		printf("%c", x);
	}
	else {
		printf("%c", readText[i]);
	}

}

void new_key_generatorVignere() {

	key[0] = '\0';
	int i, j;
	for (i = 0, j = 0; i < strlen(readText); ++i) {

		char letter = toupper(readText[i]);
		if (letter >= 'A' && letter <= 'Z') {

			if (j == strlen(password))
			{
				j = 0;
			}

			key[i] = toupper(password[j]);

			++j;
		}
		else {
			key[i] = '-';
		}

	}

	key[i] = '\0';
}

int main(void) {
	FILE* f_input;
	int in;
	char temp[MAXMAXSIZE];

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

		while (fgets(temp, MAXMAXSIZE, f_input) != NULL)
		{
			strcat(readText, temp);
		}

		new_key_generatorVignere();

		for (int i = 0; i < strlen(readText); i++) {
			if (in == 1) {
				encryptingVignere(i);
			}
			else {
				decryptingVignere(i);
			}
		}

	}
	else {
		printf("!!!!!Invalid input!!!!!\n");
	}

	fclose(f_input);
	return 0;
}