//
// HASHING ile BAÐIL DOSYA ORG.
// SOZLUK UYGULAMASI
// Last Update : 24.12.2012
//

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

FILE *dic, *rel;
char c;  
int Adres;
int Temp;
int nDic;
int nRel;
char sorgu[12];

struct word
{
	char ingilizce[12];
	char turkce[14];
}kelime;

int Hash (char* key)  // R(KEY) fonksiyonu
{
	int sum = 0;
	for (int j=0; j<4; j += 2)
		sum = (sum + 10*key[j] + key[j+1]);

	sum = sum % nRel ;  
	return sum;
}

bool isPrime(int n) 
{
    if (n <= 1)	return false;
    if (n == 2) return true;

    for (int i = 2; i <= sqrt((double)n) + 1; i++) 
	{
        if (n % i == 0) return false;
    }
    return true;
}

int primeOver(int x) 
{
	while(!isPrime(x)) x++;
	return x;
}

int sizeofRel() 
{
	dic = fopen("dictionary.txt", "r");

	nDic = 0;
	while(!feof(dic))
	{
		fscanf(dic, "%s", &kelime.ingilizce);
		fscanf(dic, "%s", &kelime.turkce);	
		nDic++;
	}
	fclose(dic);

	// %75 doluluk oraný için prime nRel
	nRel = (int)((100 * nDic)/ (float)75);
	nRel = primeOver(nRel);

	printf("\n\n Dictionary.txt deki eleman sayisi = %d", nDic);
	printf("\n\n Relative.txt deki eleman sayisi = %d", nRel);

	return nRel;
}


void RelativeOlustur()
{
	int collisions = 0;

	dic = fopen("dictionary.txt", "r");
	rel = fopen("relative.txt", "w+");

	for(int i=0; i<nRel; i++)
	{
		fseek(rel,i*sizeof(kelime),0);
		fputc('*', rel );
	}

	printf("\n\n");
	
	while(!feof(dic))
	{
		fscanf(dic, "%s", &kelime.ingilizce);
		fscanf(dic, "%s", &kelime.turkce);	

		Adres = Hash(kelime.ingilizce);		
		fseek(rel,Adres*sizeof(kelime),0);		
		
		Temp=Adres;
		c=fgetc(rel);
		while( c != '*')
		{
			// LINEAR PROBING
			printf("%4d ADRESINE %s\t\t CAKISMA YUZUNDEN LINEAR PROBING YAP \n", Adres, kelime.ingilizce);
			collisions++;

			Adres = (Adres + 1) % nRel ;
			if(Adres==Temp)
			{
				printf("DOSYA DOLU ! \n");
				return;
			}

			fseek(rel,Adres*sizeof(kelime),0);
			c=fgetc(rel);
		}

		printf("%4d ADRESINE %s\t\t ADRES BOS OLDUGU ICIN YAZ \n", Adres, kelime.ingilizce);

		fseek(rel,Adres*sizeof(kelime),0); 
		fwrite(&kelime,sizeof(kelime),1,rel);

		strcpy(kelime.ingilizce, "            ");
		strcpy(kelime.turkce, "              ");
	}
	fcloseall();

	printf("\n\n BAGIL DOSYA OLUSTURULDU \n");
	printf(" TOPLAM CAKISMA SAYISI = %d \n", collisions);
	printf("\n Press any key... ");

	getch();
}


void kelimeSorgula()
{
	rel = fopen("relative.txt", "r");

	char test;

	while(true)
	{
		system("cls");
		printf("\n\n Sorgulamak istediginiz kelimeyi giriniz... = ");
		scanf("%s",sorgu);

		Adres = Hash(sorgu);		
		fseek(rel,Adres*sizeof(kelime),0);
		fread(&kelime,sizeof(kelime),1,rel);		

		Temp=Adres;
		int compare = strcmp(sorgu,kelime.ingilizce);
		while( compare != 0 )
		{
			Adres = (Adres + 1) % nRel ;
			if(Adres==Temp)
			{
				printf("\n KELIME DOSYADA YOK ! \n\n");
				printf(" Press any key... ");
				getch();
				return;
			}

			fseek(rel,Adres*sizeof(kelime),0);
			fread(&kelime,sizeof(kelime),1,rel);
			compare = strcmp(sorgu,kelime.ingilizce);
		}	
		
		system("cls");
		printf("\n %s kelimesinin Turkce'si %s 'dir \n", kelime.ingilizce, kelime.turkce);
		printf("\n\n Baska bir kelime sorgulamak ister misiniz? (Y or N) = ");
		scanf(" %c", &test );
		if(tolower(test) == 'n')      break;		
	}
	fclose(rel);
}

void kelimeEkle()
{
	rel = fopen("relative.txt", "r+");

	char test;

	while(true)
	{
		system("cls");

		printf("\n Eklemek istediginiz kelimenin Ingilizce'sini giriniz... = ");
		scanf("%s", &kelime.ingilizce);

		printf("\n Eklemek istediginiz kelimenin Turkce'sini giriniz... = ");
		scanf("%s", &kelime.turkce);

		Adres = Hash(kelime.ingilizce);		
		fseek(rel,Adres*sizeof(kelime),0);		
		
		Temp=Adres;
		c=fgetc(rel);
		while( c != '*')
		{
			Adres = (Adres + 1) % nRel ;
			if(Adres==Temp)
			{
				printf("DOSYA DOLU ! \n");
				printf(" Press any key... ");
				return;
			}

			fseek(rel,Adres*sizeof(kelime),0);
			c=fgetc(rel);
		}	

		fseek(rel,Adres*sizeof(kelime),0); 
		fwrite(&kelime,sizeof(kelime),1,rel);

		system("cls");
		printf("\n %s KELIMESI BAGIL DOSYAYA EKLENMISTIR \n", kelime.ingilizce);
		printf("\n\n Baska bir kelime eklemek ister misiniz? (Y or N) = ");
		scanf(" %c", &test );
		if(tolower(test) == 'n')      break;
	}
	fclose(rel);
}

void kelimeSil()
{
	rel = fopen("relative.txt", "r+");

	char test;

	while(true)
	{
		system("cls");
		printf("\n\n Silmek istediginiz kelimeyi giriniz... = ");
		scanf("%s", &sorgu);

		Adres = Hash(sorgu);		
		fseek(rel,Adres*sizeof(kelime),0);
		fread(&kelime,sizeof(kelime),1,rel);
		
		// LINEAR PROBING
		Temp=Adres;
		int compare = strcmp(sorgu,kelime.ingilizce);
		while( compare != 0 )
		{
			Adres = (Adres + 1) % nRel ;
			if(Adres==Temp)
			{
				printf("\n KELIME DOSYADA YOK ! \n\n");
				printf(" Press any key... ");
				getch();
				return;
			}

			fseek(rel,Adres*sizeof(kelime),0);
			fread(&kelime,sizeof(kelime),1,rel);
			compare = strcmp(sorgu,kelime.ingilizce);
		}	

		fseek(rel,Adres*sizeof(kelime),0); 		
		fprintf(rel, "*                         ");

		system("cls");
		printf("\n %s KELIMESI BAGIL DOSYADAN SILINMISTIR \n", kelime.ingilizce);

		printf("\n\n Baska bir kelime silmek ister misiniz? (Y or N) = ");
		scanf(" %c", &test );
		if(tolower(test) == 'n')      break;		
	}
	fclose(rel);
}

void main(int argc, char* argv[])
{
	char s;

	nRel = sizeofRel();

	strcpy(kelime.ingilizce, "            ");
	strcpy(kelime.turkce, "              ");

	do
	{
		system("cls");

		printf(" \n");
		printf(" HASHING ile BAGIL DOSYA ORG. \n");
		printf(" SOZLUK UYGULAMASI\n\n");
		printf(" [0] BAGIL DOSYA OLUSTUR \n");
		printf(" [1] KELIME SORGULA \n");
		printf(" [2] KELIME EKLE\n");
		printf(" [3] KELIME SIL \n");
		printf(" [4] PROGRAMDAN CIK \n");
		printf(" \n SECIMINIZ [0..4] = ");

		s=getch();

		switch(s)
		{
			case '0' :	RelativeOlustur();		break;
			case '1' :	kelimeSorgula();		break;
			case '2' :	kelimeEkle();			break;
			case '3' :	kelimeSil();			break;
			case '4' :	return ;
		}
		
	}  while(1);
}

//"r"	read:			Open file for input operations. The file must exist.
//"w"	write:			Create an empty file for output operations. If a file with the same name already exists, its contents are discarded and the file is treated as a new empty file. 
//"a"	append:			Open file for output at the end of a file. Output operations always write data at the end of the file, expanding it. Repositioning operations (fseek, fsetpos, rewind) are ignored. The file is created if it does not exist.
//"r+"	read/update:	Open a file for update (both for input and output). The file must exist.
//"w+"	write/update:	Create an empty file and open it for update (both for input and output). If a file with the same name already exists its contents are discarded and the file is treated as a new empty file.
//"a+"	append/update:	Open a file for update (both for input and output) with all output operations writing data at the end of the file. Repositioning operations (fseek, fsetpos, rewind) affects the next input operations, but output operations move the position back to the end of file. The file is created if it does not exist.


//strcmp :
//return value	indicates
//	<0	the		first character that does not match has a lower value in str1 than in str2
//	0	the		contents of both strings are equal
//	>0	the		first character that does not match has a greater value in str1 than in str2