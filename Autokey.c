#pragma warning(disable : 4996)

#include <stdio.h>
#include<string.h>

#define MAXSIZE 100
#define MAXMAXSIZE 1000

char password[MAXSIZE];
char readText[MAXMAXSIZE];
char key[MAXMAXSIZE];

void decryptingAutokey(int i) {
	char x;
	int index = i;
	if (readText[i] >= 'A' && readText[i] <= 'Z')
	{
		while (key[index] == '-')
		{
			index++;
		}
		x = (((readText[i] - key[index]) + 26) % 26) + 'A';

		printf("%c", x);
	}
	else {
		printf("%c", readText[i]);
	}

}

void encryptingAutokey(int i) {

	char x;
	char letter = toupper(readText[i]);
	int index = i;
	if (letter >= 'A' && letter <= 'Z')
	{
		while (key[index] == '-')
		{
			index++;
		}
		x = ((letter + key[index]) % 26) + 'A';

		printf("%c", x);
	}
	else {
		printf("%c", readText[i]);
	}

}

void new_key_generatorAutokey() {

	key[0] = '\0';
	int i, j, k;
	for (i = 0, k = 0; k < strlen(password); ++i) {
		if (toupper(readText[i]) >= 'A' && toupper(readText[i]) <= 'Z') {
			key[i] = toupper(password[k++]);

		}
		else {
			key[i] = '-';
		}
	}
	for (j = 0; i < strlen(readText); ++i) {
		if (toupper(readText[i]) >= 'A' && toupper(readText[i]) <= 'Z') {

			while ((toupper(readText[j]) < 'A' || toupper(readText[j]) > 'Z') && j < strlen(readText)) {
				j++;
			}
			if (j == strlen(readText))
			{
				j = 0;
			}
			key[i] = toupper(readText[j++]);
		}
		else {
			key[i] = '-';
		}
	}

	key[i] = '\0';
}

int Autoclave(void) {
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

		new_key_generatorAutokey();

		for (int i = 0; i < strlen(readText); i++) {
			if (in == 1) {
				encryptingAutokey(i);
			}
			else {
				decryptingAutokey(i);
			}
		}
	}
	else {
		printf("!!!!!Invalid input!!!!!\n");
	}

	fclose(f_input);
	return 0;
}