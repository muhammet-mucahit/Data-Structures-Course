//
// HASHING with SYNONYM CHANING
// Last Update : 12.12.2015
//

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#include <iostream>						
using namespace std;

struct SinglyNode 
{
	char ingilizce[12];
	char turkce[14];							
	SinglyNode* next;					
};

struct SinglyLinkedList
{
	SinglyNode* head;									// pointer to the head of list
	SinglyLinkedList();									// empty list constructor
	bool empty() const;									// is list empty?
	void print();
	void addBack(char* ing, char* tur, const int& i);
	void removeOrdered(char* ing, char* tur, const int& i);

	int n = 0;
};

SinglyLinkedList::SinglyLinkedList()					// constructor
{
	head = NULL;
}

bool SinglyLinkedList::empty() const					// is list empty?
{
	return head == NULL;
}

void SinglyLinkedList::print()
{
	if (empty())
	{
		cout << "NULL" << endl;
		return;
	}

	SinglyNode* first = head;
	while (first != NULL)
	{
		cout << first->ingilizce << " > ";
		first = first->next;
	}

	cout << "NULL";
	cout << endl;
}

void SinglyLinkedList::addBack(char* ing, char* tur, const int& i)
{
	SinglyNode* v = new SinglyNode;
	strcpy(v->ingilizce, ing);
	strcpy(v->turkce, tur);
	v->next = NULL;

	if (head == NULL) head = v;
	else
	{
		SinglyNode* first = head;
		while (first->next != NULL) first = first->next;
		first->next = v;
	}

	n++;
}

void SinglyLinkedList::removeOrdered(char* ing, char* tur, const int& i)
{
	SinglyNode* current = head;
	SinglyNode* previous = head;		// Liste tek yollu olduðundan silerken previous gerekli

	// Liste boþ mu?
	if (head == NULL)
	{
		cout << "List is empty !" << endl;
		return;
	}

	// Listenin ilk elemaný mý silinecek?
	if (strcmp(current->ingilizce, ing) == 0)
	{
		head = current->next;
		delete current;
		n--;
		return;
	}

	// Head'in iþaret ettiðinden sonraki elemanlardan biri, belki de en son eleman silinecek
	current = current->next;
	while (current != NULL)
	{
		if (strcmp(current->ingilizce, ing) == 0)
		{
			previous->next = current->next;
			delete current;
			n--;
			return;
		}

		previous = current;
		current = current->next;
	}

	if (current == NULL) cout << "\n" << ing << " is not found" << endl;
}

struct word
{
	char ingilizce[12];
	char turkce[14];
}kelime;


FILE *dic, *rel;
char c;
int Adres;
int Temp;
int nDic;
int nRel;
char sorgu[12];

SinglyLinkedList *listsofSynoyms;
int nlist = 0;

void printSynonyms();

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

	printf("\n\n Dictionary.txt deki ingilizcean sayisi = %d", nDic);
	printf("\n\n Relative.txt deki ingilizcean sayisi = %d", nRel);

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

	listsofSynoyms = new SinglyLinkedList[41];
	
	while(!feof(dic))
	{
		fscanf(dic, "%s", &kelime.ingilizce);
		fscanf(dic, "%s", &kelime.turkce);	

		Adres = Hash(kelime.ingilizce);		
		fseek(rel,Adres*sizeof(kelime),0);		
		
		c=fgetc(rel);
		if( c != '*')
		{
			collisions++;

			printf("%4d DOLU\t%s\t\t INDISINE EKLENECEK \n", Adres, kelime.ingilizce);
			listsofSynoyms[Adres].addBack(kelime.ingilizce, kelime.turkce, Adres);
		}
		else
		{
			printf("%4d ADRESINE\t%s\t\t ADRES BOS OLDUGU ICIN YAZ \n", Adres, kelime.ingilizce);
			fseek(rel, Adres*sizeof(kelime), 0);
			fwrite(&kelime, sizeof(kelime), 1, rel);
		}

		strcpy(kelime.ingilizce, "            ");
		strcpy(kelime.turkce, "              ");
	}
	fclose(dic);
	fclose(rel);

	printf("\n BAGIL DOSYA ve LISTELER OLUSTURULDU \n");
	printf(" TOPLAM CAKISMA SAYISI = %d \n\n", collisions);
	printf(" Press any key... ");
	getchar();
	getchar();
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

		int compare = strcmp(sorgu, kelime.ingilizce);

		if (compare == 0)
		{
			system("cls");
			printf("\n %s kelimesinin Turkce'si %s 'dir \n", kelime.ingilizce, kelime.turkce);
		}
		else
		{
			SinglyNode* node = listsofSynoyms[Adres].head;
			while (node != NULL)
			{
				if (strcmp(sorgu, node->ingilizce) == 0)
				{
					system("cls");
					printf("\n %s kelimesinin Turkce'si %s 'dir \n", node->ingilizce, node->turkce);					
					printf("\n ILGILI LISTE : "); 
					listsofSynoyms[Adres].print();
					break;
				}
				else
					node = node->next;
			}

			if (node == NULL) printf("\n\n KELIME DOSYADA YOK ! ");
		}

		printf("\n\n Baska bir kelime sorgulamak ister misiniz? (Y or N) = ");
		scanf(" %c", &test);
		if (tolower(test) == 'n')      break;
		
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

		printf("\n\n Eklemek istediginiz kelimenin Ingilizce'sini giriniz... = ");
		scanf("%s", &kelime.ingilizce);

		printf("\n Eklemek istediginiz kelimenin Turkce'sini giriniz... = ");
		scanf("%s", &kelime.turkce);

		Adres = Hash(kelime.ingilizce);		
		fseek(rel,Adres*sizeof(kelime),0);		
		
		c = fgetc(rel);
		if (c != '*')
		{
			printf("\t\t%s\t\t LISTEYE EKLENECEK \n", kelime.ingilizce);
			listsofSynoyms[Adres].addBack(kelime.ingilizce, kelime.turkce, Adres);
		}
		else
		{
			printf("%4d ADRESINE\t%s\t\t ADRES BOS OLDUGU ICIN YAZ \n", Adres, kelime.ingilizce);
			fseek(rel, Adres*sizeof(kelime), 0);
			fwrite(&kelime, sizeof(kelime), 1, rel);
		}

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
		fseek(rel, Adres*sizeof(kelime), 0);
		fread(&kelime, sizeof(kelime), 1, rel);

		int compare = strcmp(sorgu, kelime.ingilizce);

		if (compare == 0)
		{
			system("cls");

			if (listsofSynoyms[Adres].head != NULL)
			{
				strcpy(kelime.ingilizce,	"            ");		// remove yapýlacaktan
				strcpy(kelime.turkce,		"              ");		// kalýntý olmasý diye
				strcpy(kelime.ingilizce,	listsofSynoyms[Adres].head->ingilizce);
				strcpy(kelime.turkce,		listsofSynoyms[Adres].head->turkce);

				listsofSynoyms[Adres].removeOrdered(kelime.ingilizce, kelime.turkce, Adres);

				fseek(rel, Adres*sizeof(kelime), 0);
				fwrite(&kelime, sizeof(kelime), 1, rel);
			}
			else
			{
				fseek(rel, Adres*sizeof(kelime), 0);
				fprintf(rel, "*                         "); // Liste yok
			}

			printf("\n %s DOSYADAN SILINMISTIR \n", sorgu);
		}
		else
		{
			SinglyNode* node = listsofSynoyms[Adres].head;
			while (node != NULL)
			{
				if (strcmp(sorgu, node->ingilizce) == 0)
				{
					system("cls");
					listsofSynoyms[Adres].removeOrdered(node->ingilizce, node->turkce, Adres);
					printf("\n ILGILI LISTE : ");
					listsofSynoyms[Adres].print();
					break;
				}
				else
					node = node->next;
			}

			if (node == NULL) printf("\n\n KELIME DOSYADA YOK ! ");
		}

		printf("\n\n Baska bir kelime silmek ister misiniz? (Y or N) = ");
		scanf(" %c", &test );
		if(tolower(test) == 'n')      break;		
	}
	fclose(rel);
}

void printSynonyms()
{
	cout << endl << endl;

	for (int i = 0; i < 41; i++)
	{
		cout << i << " : "; listsofSynoyms[i].print();
	}

	getchar(); getchar();
}

// Baðlý listeleri synonyms.txt'den oku. 
void readSynonyms()
{
	FILE* syn = fopen("synonyms.txt", "r");

	int indis = 0;
	int nodes = 0;

	listsofSynoyms = new SinglyLinkedList[41];

	for (int i = 0; i < 41; i++)
	{
		fscanf(syn, "%d %d", &indis, &nodes);

		if (indis != 0)
		{
			for (int i = 0; i < nodes; i++)
			{
				fscanf(dic, "%s", &kelime.ingilizce);
				fscanf(dic, "%s", &kelime.turkce);

				listsofSynoyms[indis].addBack(kelime.ingilizce, kelime.turkce, indis);
			}
		}
	}

	fclose(syn);

	printf("\n\n LISTELER OKUNDU\n\n");
	printf(" Press any key... ");
	getchar(); getchar();
}

// Programdan çýkýlýrken baðlý listeleri synonyms.txt'ye yaz.
void onExit()
{
	FILE* syn = fopen("synonyms.txt", "w");

	for (int i = 0; i < 41; i++)
	{
		if (listsofSynoyms[i].head != NULL)
		{
			fprintf(syn, "%d %d ", i, listsofSynoyms[i].n);
			SinglyNode* first = listsofSynoyms[i].head;
			while (first != NULL)
			{
				fprintf(syn, " %s %s", first->ingilizce, first->turkce);
				first = first->next;
			}
			fprintf(syn, "\n");

			nlist++;
		}
		else
			fprintf(syn, "0 0\n");
	}

	fclose(syn);

	//printf("\n LISTELER DOSYAYA YAZILDI");
	//getch();
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
		printf(" HASHING with SYNONYM CHANING \n\n");
		printf(" [0] BAGIL DOSYA OLUSTUR \n");
		printf(" [1] KELIME SORGULA \n");
		printf(" [2] KELIME EKLE\n");
		printf(" [3] KELIME SIL \n");
		printf(" [4] LISTELERI GOSTER \n");
		printf(" [5] LISTELERI OKU \n");
		printf(" [6] PROGRAMDAN CIK \n");
		printf(" \n SECIMINIZ [0..5] = ");

		s=getchar();

		switch(s)
		{
			case '0' :	RelativeOlustur();		break;
			case '1' :	kelimeSorgula();		break;
			case '2' :	kelimeEkle();			break;
			case '3' :	kelimeSil();			break;
			case '4':   printSynonyms();		break;
			case '5':   readSynonyms();			break;
			case '6':	onExit();				return;
		}
		
	}  while(1);
}