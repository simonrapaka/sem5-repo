// A Simplified AES Algorithm
#include <stdio.h>

int read(char str[])
{
	int i=0,c;

	while((c = getchar()) != '\n')
		str[i++] = c;
	return i;
}

int htod(char c)
{
	char h[] = "0123456789abcdef";
	int i=0;

	for(;i<16;i++)
		if(c==h[i])
			return i;
	return i;
}

void hextobin(char h[], char b[])
{
	for(int i=0;i<4;i++)
	{
		int n = htod(h[3-i]);

		for(int j=0;j<4;j++)
		{
			b[(3-i)*4 + (3-j)] = n%2 + 48;
			n /= 2;
		}
	}
}

void hextobin2(int n, char b[])
{
	for(int i=0;i<16;i++)
	{
		b[15-i] = n%2 + 48;
		n /= 2;
	}
}

void hextoint(char *in,  unsigned short int *o)
{
	for(int i=0; i<4; i++)
		*o = (*o)*16 + htod(in[i]);
}

int main()
{
	char tkey[4] = {0}, tpl[4], bkey[16] = {0}, bpl[16] = {0};
	unsigned short int key = 0,pl = 0,pl2, key2, key3;
	unsigned char w0,w1,gw1,w2,w3,gw3,w4,w5;
	unsigned char sbox[16] = {9,4,10,11,13,1,8,5,6,2,0,3,12,14,15,7};
	unsigned char mixcol[16] = {4,8,0xc,3,7,0xb,0xf,6,2,0xe,0xa,5,1,0xd,9};
	unsigned char rcon1 = 128, rcon2 = 48;

	printf("\nEnter plaintext in hex: ");
	scanf(" ");
	read(tpl);

	hextobin(tpl, bpl);
	hextoint(tpl, &pl);
	pl2 = pl;

	printf("In Binary: ");
	for(int i=0;i<16;i++)
		printf("%c %s", bpl[i], (i+1)%4 ? "\b" : " \b");
	printf("\nIn Decimal: %u", pl);


	printf("\n\nEnter key in hex: ");
	scanf(" ");
	read(tkey);

	hextobin(tkey, bkey);
	hextoint(tkey, &key);

	printf("In Binary: ");
	for(int i=0;i<16;i++)
		printf("%c %s", bkey[i], (i+1)%4 ? "\b" : " \b");
	printf("\nIn Decimal: %u", key);

	//splitting key into w0 and w1
	w0 = key >> 8;
	w1 = key;

	//Round 0
	//XORing with w0w1 i.e. the original key
	pl = pl^key;
	printf("\n\nAfter Addroundkey: %x", pl);

	//Round 1
	printf("\n\nRound 1:");
	//Nibble Substitution
	pl = sbox[pl >> 12] << 12 | sbox[(pl >> 8) % 16] << 8 | sbox[(pl >> 4) % 16] << 4 | sbox[pl % 16];
	printf("\nAfter Nibble Substitution: %x", pl);
	//ShiftRow(Swaps 2nd and 4th nibbles)
	pl = ((pl >> 8) % 16 | ((pl >> 4) % 16) << 4) | (pl % 16 << 8 | (pl >> 12) << 12);
	printf("\nAfter ShiftRow: %x", pl);
	//MixColumns
	pl = (mixcol[(pl >> 8) % 16 - 1] ^ (pl >> 12) % 16) << 12 |
		(mixcol[(pl >> 12) % 16 - 1] ^ (pl >> 8) % 16) << 8 |
		(mixcol[pl % 16 - 1] ^ (pl >> 4) % 16) << 4 |
		(mixcol[(pl >> 4) % 16 - 1] ^ pl % 16);
	printf("\nAfter MixColumns: %x", pl);


	//g function
	printf("\n\nInside the g function:");
	printf("\n\tw0: %x w1: %x", w0,w1);
	//Rotating to the left by 4 bits
	gw1 = w1 >> 4 | w1 << 4;
	printf("\n\tw1 after rotation: %x", gw1);
	//S-Box Substitution
	gw1 = sbox[gw1 >> 4] << 4 | sbox[gw1 % 16];
	printf("\n\tw1 after substitution: %x", gw1);
	//XORing with Round constant
	gw1 = gw1^rcon1;
	printf("\n\tw1 after xoring with rcon: %x", gw1);
	//g function end

	w2 = w0^gw1;
	w3 = w2^w1;

	printf("\n\n\tw2: %x w3: %x", w2,w3);
	key2 = w2 << 8 | w3;
	printf("\n\tkey2: %x", key2);

	//AddRounkey
	pl = key2 ^ pl;
	printf("\n\nAfter AddRoundKey: %x", pl);
	//Round 1 end
	

	//Round 2
	printf("\n\nRound 2:");
	pl = sbox[pl >> 12] << 12 | sbox[(pl >> 8) % 16] << 8 | sbox[(pl >> 4) % 16] << 4 | sbox[pl % 16];
	printf("\nAfter Nibble Substitution: %x", pl);
	//ShiftRow(Swaps 2nd and 4th nibbles)
	pl = ((pl >> 8) % 16 | ((pl >> 4) % 16) << 4) | (pl % 16 << 8 | (pl >> 12) << 12);
	printf("\nAfter ShiftRow: %x", pl);

	//g function
	printf("\n\nInside the g function:");
	printf("\n\tw2: %x w3: %x", w2,w3);
	//Rotating to the left by 4 bits
	gw3 = w3 >> 4 | w3 << 4;
	printf("\n\tw3 after rotation: %x", gw3);
	//S-Box Substitution
	gw3 = sbox[gw3 >> 4] << 4 | sbox[gw3 % 16];
	printf("\n\tw3 after substitution: %x", gw3);
	//XORing with Round constant
	gw3 = gw3^rcon2;
	printf("\n\tw3 after xoring with rcon: %x", gw1);
	//g function end

	w4 = w2^gw3;
	w5 = w4^w3;

	printf("\n\n\tw4: %x w5: %x", w4,w5);
	key3 = w4 << 8 | w5;
	printf("\n\tkey3: %x", key3);

	//AddRoundKey
	pl = key3 ^ pl;
	printf("\n\nAfter AddRoundKey: %x", pl);
	//Round 2 end

	printf("\n\nPlaintext(in hex): %04x", pl2);
	printf("\nIn Binary: ");
	for(int i=0;i<16;i++)
		printf("%c %s", bpl[i], (i+1)%4 ? "\b" : " \b");
	printf("\nIn Decimal: %u", pl2);

	printf("\n\nCipherText(in hex): %04x", pl);
	hextobin2(pl, bpl);
	printf("\nIn Binary: ");
	for(int i=0;i<16;i++)
		printf("%c %s", bpl[i], (i+1)%4 ? "\b" : " \b");
	printf("\nIn Decimal: %u", pl);

	return 0;
}