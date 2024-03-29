// Miwa.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "AlV2Edl.h"
#include <string>
#include <sstream>      // std::stringstream, std::stringbuf
#include <vector>

using namespace std;

void next();
char* byte2Hex(unsigned char c);
char* convertByteArray2Hex(const unsigned char* byteArray, int length);


int main(int argc, char *argv[])
{
	if (argc == 1) {
		printf("%s \n", "===Handy Miwa DLL interface /w Alv2Edl.dll===");
		printf("\n%s\n", "Usage: Miwa <Hotel code> <Edl-Id> <Keydata> <Special door flag>");
		printf("\n%s\n\n", "Example: Miwa 89455FC8 0100-0100-BD43 GUA001001,1807091529,18071010,0000,000101,000102000103000104000105000106 0000000000");
		next();
		return 0;
	}
	if (argc != 5) {
		return 0;
	}
	
	int pEnc1_length = 48;
	int pEnc4_length = 48;
	int pEnc5_length = 48;
	unsigned char pEnc1[48];
	unsigned char pEnc4[48];
	unsigned char pEnc5[48];
	unsigned long ulHt1;
	unsigned char *pEdlId;
	unsigned char *pInf;
	unsigned char *pSpFlg;

	string str_ulHt1 = argv[1];	//89455FC8
	stringstream ss_ulHt1(str_ulHt1);
	ss_ulHt1 >> hex >> ulHt1;

	pEdlId = reinterpret_cast<unsigned char*>(argv[2]);	//0100-0100-BD43
	pInf = reinterpret_cast<unsigned char*>(argv[3]); //GUA001001,1807091529,18071010,0000,000101,000102000103000104000105000106
	pSpFlg = reinterpret_cast<unsigned char*>(argv[4]);	//0000000000

	//Calling key generation function
	EDL_Inf2EncWithEdl(pEnc1, pEnc4, pEnc5, ulHt1, pEdlId, pInf, pSpFlg);
	char* hex_pEnc1 = convertByteArray2Hex(pEnc1, pEnc1_length);
	char* hex_pEnc4 = convertByteArray2Hex(pEnc4, pEnc4_length);
	char* hex_pEnc5 = convertByteArray2Hex(pEnc5, pEnc5_length);
	printf("{\"%s\": \"%s\",","pEnc1" ,hex_pEnc1);
	printf("\"%s\": \"%s\",","pEnc4" ,hex_pEnc4);
	printf("\"%s\": \"%s\"}","pEnc5" ,hex_pEnc5);
}

void next() {
	printf("%s \n", "Press any key to continue...");
	std::getchar();
}

char* byte2Hex(unsigned char c) {
	char result[3];
	sprintf_s(result, 3, "%02x", c);
	return result;
}

char* convertByteArray2Hex(const unsigned char* byteArray, int length) {
	char* result = new char[length * 2 + 1]();
	for (int i = 0; i < length; i++) {
		char* hex = byte2Hex(byteArray[i]);
		result[i * 2] = hex[0];
		result[i * 2 + 1] = hex[1];
		//printf("%s\n", hex);
	}
	return result;
}