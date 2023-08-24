#include <stdio.h>

int read(char s[])
{
	int i=0,ch;

	while ((ch = getchar()) != '\n') 
		s[i++] = ch;
	s[i] = '\0';

	return i;
}

int main()
{
	int ch,ch2, key, rail, l;
	char mes[100] = {0}, ci;

	while(1)
	{
		printf("\n\n1) Caesar Cipher\n2) Rail Fence Cipher\n3) EXIT\n\nWhat cipher do you want to you use? ");
		scanf("%d", &ch);
		if(ch==3) return 0;

		printf("1) Encryption\n2) Decryption\n\nEnter choice: ");
		scanf("%d", &ch2);

		printf("\nEnter message: ");
		scanf(" ");
		l = read(mes);

		switch (ch) 
		{
			case 1:
				printf("Enter key(1-25): ");
				scanf("%d", &key);

				if(ch2>1) printf("Plaintext: ");
				else printf("Cipher Text: ");

				if(ch2>1) key = 26 - key;

				for(int i=0;mes[i] != '\0'; i++)
				{
					ci = mes[i];
					if(ci >= 'A' && ci <= 'Z')
						ci = ((ci - 'A') + key) % 26 + 'a';
					else if(ci >= 'a' && ci <= 'z')
						ci = ((ci - 'a') + key) % 26 + 'A';
					putchar(ci);
				}
				break;

			case 2:
				printf("Enter no of rails: ");
				scanf("%d", &rail);

				if(ch2<2) printf("Cipher Text: ");

				int b=1,in,inc,pos=0;
				char pl[100] = {0};

				for(int i=0;i<rail;i++)
				{
					in = i;
					ci = mes[i];
					if(ch2>1) ci = mes[pos++];
					if(ci >= 'A' && ci <= 'Z')
						ci = ci - 'A' + 'a';
					else if(ci >= 'a' && ci <= 'z')
						ci = ci - 'a' + 'A';
					if(ch2<2) putchar(ci);
					else pl[in] = ci;
					while(1)
					{
						if(b)
							inc = 2*(rail-1-i);
						else
							inc = 2*i;
						if(inc==0) inc = 2*(rail-1);
						in += inc;

						if(in>=l) {b=1; break;}

						ci = mes[in];
						if(ch2>1) ci = mes[pos++];
						if(ci >= 'A' && ci <= 'Z')
							ci = ci - 'A' + 'a';
						else if(ci >= 'a' && ci <= 'z')
							ci = ci - 'a' + 'A';
						if(ch2<2) putchar(ci);
						else pl[in] = ci;
						b = !b;
					}
				}
				if(ch2>1) printf("Plain Text: %s", pl);
				break;

			default:
				printf("Invalid choice");
				break;
		}
	}
	return 0;
}
