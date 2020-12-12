#pragma warning(disable : 4996)
#include<stdio.h>
#include<string.h>

#define MAX_LENGTH 100
#define KEY 16
#define a 'a'
#define z 'z'
#define A 'A'
#define Z 'Z'


char crypt_password[MAX_LENGTH];
char decrypt_password[MAX_LENGTH];
char password[MAX_LENGTH];

void cryptFnc() {
	int i;
	char ch;
	for (i = 0; i < strlen(password); i++) {
		ch = password[i];

		if (ch >= a && ch <= z) {
			ch += KEY;

			if (ch > z) {
				ch = ch - z + a - 1;
			}
		}
		else if (ch >= A && ch <= Z) {
			ch += KEY;

			if (ch > Z) {
				ch = ch - Z + A - 1;
			}
		}

		crypt_password[i] = ch;

	}
}

void decryptFnc() {
	int i, possibleKey;
	char ch;

	for (possibleKey = 1; possibleKey <= 26; possibleKey++)
	{
		for (i = 0; i < strlen(crypt_password); i++) {
			ch = crypt_password[i];

			if (ch >= a && ch <= z) {
				ch = ch - possibleKey;

				if (ch < a) {
					ch = ch + z - a + 1;
				}
			}
			else if (ch >= A && ch <= Z) {
				ch = ch - possibleKey;

				if (ch < A) {
					ch = ch + Z - A + 1;
				}
			}
			decrypt_password[i] = ch;
		}
		printf("For key = %d the password is %s\n", possibleKey, decrypt_password);
	}
}

int Caesar() {

	char input_key;

	while (1)
	{
		printf("1 -> Encryption\n2 -> Decryption\n\n");
		scanf("%d", &input_key);

		switch (input_key)
		{
		case 1:
		{
			printf("Enter your password:");
			scanf("%s", password);
			cryptFnc();
			printf("Your password is: %s\n\n", crypt_password);
			break;
		}
		case 2:
		{
			if (crypt_password[0] == '\0')
			{
				printf("Enter the password first!!!\n");
			}
			else {
				decryptFnc();
			}
			crypt_password[0] = '\0';
			break;
		}
		default:
			printf("!!!!!Invalid input!!!!!\n");
			break;
		}

	}
	return 0;
}