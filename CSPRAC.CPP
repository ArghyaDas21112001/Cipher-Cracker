#include<iostream.h>
#include <fstream.h>
#include<string.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


#define LEVEL 3  /* Number of Rows in RailFence Matrix */
#define MAXLEN 30

class Cryptic
{
	int msgLen;
	char temparray[90];         //Size of temparray =maxlen *level

public:
	Cryptic()
	{
		msgLen = 0;
		temparray[0]='\0';
	}
	char* CaesarEncrypt(char* message,int key);
	char* CaesarDecrypt(char* message,int key);
	char* VigenereEncrypt(char* msg,char* key);
	char* VigenereDecrypt(char* msg,char* key);
	void RailFencEncryptMsg(char msg[], int key);
	void RailFencDecryptMsg(char msg[], int key);
	int getMsgLen();
	int setMsgLen(int len);
	char* getMessage();
	int  setMessage(char *msg);
};

int Cryptic::getMsgLen()
{
	return msgLen;
}

int Cryptic::setMsgLen(int len)
{
	msgLen = len;
	return msgLen;
}

char* Cryptic::getMessage()
{
	return temparray;
}

int Cryptic::setMessage(char *msg)
{
	strcpy(temparray,msg);
	return strlen(temparray);
}
void Cryptic::RailFencEncryptMsg(char msg[], int key)
{
    int msgLen = strlen(msg), i, j, k = -1, row = 0, col = 0;
    char railMatrix[LEVEL][MAXLEN];

    for(i = 0; i < key; ++i)
	for(j = 0; j < msgLen; ++j)
	    railMatrix[i][j] = '\n';

    for(i = 0; i < msgLen; ++i){
	railMatrix[row][col++] = msg[i];

	if(row == 0 || row == key-1)
	    k= k * (-1);

	row = row + k;
    }

//    cout<<"\nEncrypted Message: ";
    int ctr1=0;
    for(ctr1 = 0 ;ctr1 < MAXLEN; ctr1++)
    {
	temparray[ctr1] ='\0';
    }
    int ctr = 0;
    for(i = 0; i < key; ++i)
	for(j = 0; j < msgLen; ++j)
	    if(railMatrix[i][j] != '\n')
	    {
		//cout<<railMatrix[i][j];
		temparray[ctr] = railMatrix[i][j];
		ctr++;
	    }
    temparray[ctr] = '\0';
//    cout << temparray;
}

void Cryptic::RailFencDecryptMsg(char enMsg[], int key)
{
    int msgLen = strlen(enMsg), i, j, k = -1, row = 0, col = 0, m = 0;
    char railMatrix[3][MAXLEN];

    for(i = 0; i < key; ++i)
	for(j = 0; j < msgLen; ++j)
	    railMatrix[i][j] = '\n';

    for(i = 0; i < msgLen; ++i){
	railMatrix[row][col++] = '*';

	if(row == 0 || row == key-1)
	    k= k * (-1);

	row = row + k;
    }

    for(i = 0; i < key; ++i)
	for(j = 0; j < msgLen; ++j)
	    if(railMatrix[i][j] == '*')
		railMatrix[i][j] = enMsg[m++];

    row = col = 0;
    k = -1;

  //  cout<<"\nDecrypted Message: ";
    int ctr = 0;
    for(i = 0; i < msgLen; ++i){
	//cout<<railMatrix[row][col++];
	//temparray[ctr] = railMatrix[row][col-1];
	temparray[ctr] = railMatrix[row][col];
	col++;
	ctr++;
	if(row == 0 || row == key-1)
	    k= k * (-1);

	row = row + k;
    }
    temparray[ctr] = '\0';
    //cout << temparray;
}


char* Cryptic::CaesarEncrypt(char* message,int key)
{

	int i;
	char ch;
	for(i = 0; message[i] != '\0'; ++i)
	{
		ch = message[i];

		if(ch >= 'a' && ch <= 'z')
		{
			ch = ch + key;

			if(ch > 'z')
			{
				ch = ch - 'z' + 'a' - 1;
			}

			message[i] = ch;
		 }
		 else if(ch >= 'A' && ch <= 'Z')
		 {
			ch = ch + key;

			if(ch > 'Z')
			{
				ch = ch - 'Z' + 'A' - 1;
			}
			message[i] = ch;
		 }
	 }

//	cout << "Encrypted message: " << message<<endl;
	return message;
}

char* Cryptic::CaesarDecrypt(char* message,int key)
{

	int i;
	char ch;

    for(i = 0; message[i] != '\0'; ++i){
	ch = message[i];

	if(ch >= 'a' && ch <= 'z'){
	    ch = ch - key;

	    if(ch < 'a'){
		ch = ch + 'z' - 'a' + 1;
	    }

	    message[i] = ch;
		}
	else if(ch >= 'A' && ch <= 'Z'){
	    ch = ch - key;

	    if(ch > 'a'){
		ch = ch + 'Z' - 'A' + 1;
	    }

	    message[i] = ch;
	}
    }

  //  cout << "Decrypted message: " << message<<endl;

    return message;
}

char* Cryptic::VigenereEncrypt(char msg[],char key[])
{
   int msgLen = strlen(msg), keyLen = strlen(key), i, j;
   char newKey[MAXLEN], encryptedMsg[MAXLEN];
   //generating new key
   for(i = 0, j = 0; i < msgLen; ++i, ++j){
	if(j == keyLen)
	    j = 0;

	newKey[i] = key[j];
   }

   newKey[i] = '\0';

   //encryption
   for(i = 0; i < msgLen; ++i)
   {

	 if(msg[i] == ' ')
	 {
		encryptedMsg[i] = ' ';
	 }
	 else if ( msg[i] == '.')
	 {
		encryptedMsg[i] = '.';
	 }
	 else
	 {      msg[i] = toupper(msg[i]);
		encryptedMsg[i] = ((msg[i] + newKey[i]) % 26) + 'A';
	 }
   }
   encryptedMsg[i] = '\0';
   return encryptedMsg;
}
char* Cryptic::VigenereDecrypt(char msg[],char key[])
{
   int msgLen = strlen(msg), keyLen = strlen(key), i, j;
   char newKey[MAXLEN], decryptedMsg[MAXLEN];
   //generating new key
   for(i = 0, j = 0; i < msgLen; ++i, ++j){
	if(j == keyLen)
	    j = 0;

	newKey[i] = key[j];
   }

   newKey[i] = '\0';
 //decryption
    for(i = 0; i < msgLen; ++i)
    {
	if( msg[i] == ' ')
	{
		decryptedMsg[i] = ' ';
	}
	else if ( msg[i] == '.')
	{
		decryptedMsg[i] = '.';
	}
	else
	{
		decryptedMsg[i] = (((msg[i] - newKey[i]) + 26) % 26) + 'A';
	}
    }
    decryptedMsg[i] = '\0';
   return decryptedMsg;
}

void main()
{
      char line[MAXLEN],line2[MAXLEN];	
	Cryptic CryptObj;
      clrscr();
      int key = 0;
      char choice=' ';
      ifstream fil, fil2;
      ofstream fenc,fdec;
      char strkey[]="DEFAULT";
      //textcolor(CYAN);

      while(choice!='4')
      {
	       clrscr();
	       gotoxy(16,3);

	       cout<<"**** Implementation of Some Algorithms For  ****";
	       gotoxy(16,4);
	       cout<<"****         Encryption - Decryption        ****";
       gotoxy(16,5);

       cout<<"1. Encryption & Decryption - RailFence Cipher";
       gotoxy(16,7);
       cout<<"2. Encryption & Decryption - Caesar Cipher";
       gotoxy(16,9);
       cout<<"3. Encryption & Decryption - Vigenere Cipher";
       gotoxy(16,11);
       cout<<"4. Exit"<<endl;
       gotoxy(16,15);
       cout<<"Enter your choice [1/2/3/4] - ";
       cin>>choice;


       switch(choice)
       {
	case '1':
		fil.open("Source.txt");
		fenc.open("EncRail.txt");
		cout << "Reading File Source.txt for Encryption Using RailFence Cipher\n";
		cout << "|\t\tSource.txt\t\t|\t\tEncRail.txt\t\t"<<endl;

		while(!fil.eof())
		{
			fil.getline(line,MAXLEN);
			CryptObj.RailFencEncryptMsg(line,LEVEL);
			cout << "|\t"<< line <<"\t|\t"<< CryptObj.getMessage()<<endl;
			fenc << CryptObj.getMessage();
		}
		fenc.close();
		fil.close();
		cout << "\n------File Encryption Using RailFence Cipher Algorithm Completed-----" << endl;
		cout << "------Check Encrypted File EncRail.txt------" << endl;
		cout << endl << endl << "Press a Key to Continue...." << endl;
		getch();
		fil2.open("EncRail.txt");
		fdec.open("DecRail.txt");

		cout << "Reading File EncRail.txt for Decryption Using RailFence Cipher\n";
		cout << "|\t\tEncRail.txt\t\t|\t\tDecRail.txt\t\t"<<endl;

		while(!fil2.eof())
		{
			fil2.getline(line2,MAXLEN);
			CryptObj.RailFencDecryptMsg(line2,LEVEL);
			cout << "|\t"<< line2 <<"\t|\t"<< CryptObj.getMessage()<<endl;
			fdec << CryptObj.getMessage();
		}
		fdec.close();
		fil2.close();
		cout << "\nFile Decryption Using RailFence Cipher Algorithm Completed" << endl;
		cout << "Check Decrypted File DecRail.txt" << endl;
		getch();
		break;
	case '2':
		fil.open("Source.txt");
		fenc.open("EncCsr.txt");
		cout << "Enter a number between 2 to 5for the Key....\t";
		cin >> key;
		if (key < 2 || key > 5 )
		{
			cout << "Invalid Key .. (2- 5 are Valid keys)\n";
			break;
		}
		cout << "Reading File Source.txt for Encryption Using Caeser Cipher\n";
		cout << "|\t\tSource.txt\t\t|\t\tEncCsr.txt\t\t"<<endl;

		while(!fil.eof())
		{
			fil.getline(line,MAXLEN);
			cout << "|\t" << line << "\t|";
			CryptObj.setMessage(CryptObj.CaesarEncrypt(line,key))	;
			cout << "\t"<< CryptObj.getMessage()<<endl;
			fenc << CryptObj.getMessage();
		}
		fenc.close();
		fil.close();
		cout << "File Encryption Using Caesar Cipher Algorithm Completed" << endl;
		cout << "Check Encrypted File EncCsr.txt" << endl;
		cout << endl << endl << "Press a Key to Continue...." << endl;

		getch();
		fil2.open("EncCsr.txt");
		fdec.open("DecCsr.txt");
		cout << "Reading File EncCsr.txt for Decryption Using Caeser Cipher\n";
		cout << "|\t\tEncCsr.txt\t\t|\t\tDecCsr.txt\t\t"<<endl;

		while(!fil2.eof())
		{
			fil2.getline(line2,MAXLEN);
			cout << "|\t"<< line2 <<"\t";
			CryptObj.setMessage(CryptObj.CaesarDecrypt(line2,key))	;
			cout << "|\t"<< CryptObj.getMessage()<<endl;

			fdec << CryptObj.getMessage();
		}
		fdec.close();
		fil2.close();
		cout << "File Decryption Using Caesar Cipher Algorithm Completed" << endl;
		cout << "Check Decrypted File DecCsr.txt" << endl;
		getch();
		break;
	case '3':
		clrscr();
		fil.open("SoVig.txt");
		fenc.open("EncVig.txt");
		cout << "Enter a 6 letter string of alphabets (in CAPITALS) for the Key....\t";
		cin >> strkey;
		if (strlen(strkey) >=7 )
		{
			cout << "Invalid Key .. (6 letter alphabets)\n";
			break;
		}
		cout << "Reading File SoVig.txt for Encryption Using Vigenere Cipher\n";
		cout << "|\t\tSoVig.txt\t\t|\t\tEncVig.txt\t\t"<<endl;

		while(!fil.eof())
		{
			fil.getline(line,MAXLEN);
			//cout << "PlainText Line:" << line << endl;
			CryptObj.setMessage(CryptObj.VigenereEncrypt(line,strkey));
			//cout << "Encrypted Line:" <<	CryptObj.getMessage() << endl;
			cout << "|\t"<< line <<"\t|\t"<< CryptObj.getMessage()<<endl;
			fenc << CryptObj.getMessage();
		}
		fenc.close();
		fil.close();
		cout << "File Encryption Completed Using Vigenere Cipher Algorithm" << endl;
		cout << "Check Encrypted File EncVig.txt" << endl;
		cout << endl << endl << "Press a Key to Continue...." << endl;

		getch();
		fil2.open("EncVig.txt");
		fdec.open("DecVig.txt");

		cout << "\n\nReading File Encrypt.txt for Encryption Using Vigenere Cipher\n";
		cout << "|\t\tEncVig.txt\t\t|\tDecVig.txt\t\t"<<endl;

		while(!fil2.eof())
		{
			fil2.getline(line2,MAXLEN);
			CryptObj.setMessage(CryptObj.VigenereDecrypt(line2,strkey));
			cout << "|\t"<< line2 <<"\t|\t"<< CryptObj.getMessage()<<endl;
			fdec << CryptObj.getMessage();
		}
		fdec.close();
		fil2.close();
		cout << "File Decryption Using Vigenere Cipher Algorithm Completed" << endl;
		cout << "Check Decrypted File DecVig.txt" << endl;
		getch();
		break;
	case '4':
		cout << "Quitting the Program\n";
		break;
		}
	}
}