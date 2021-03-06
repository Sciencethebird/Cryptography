//
//  main.cpp
//  DES
//
//  Created by Sciencethebird on 2019/3/12.
//  Copyright © 2019 Sciencethebird. All rights reserved.
//
#include "pch.h"
#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include <bitset>
#include <fstream>
#include <time.h>


using namespace std;

string GetHexFromBin(string sBinary)
{
	string rest(""), tmp, chr = "0000";
	int len = (int)sBinary.length() / 4;
	chr = chr.substr(0, len);
	for (int i = 0; i < sBinary.length(); i += 4)
	{
		tmp = sBinary.substr(i, 4);
		if (!tmp.compare("0000"))
		{
			rest = rest + "0";
		}
		else if (!tmp.compare("0001"))
		{
			rest = rest + "1";
		}
		else if (!tmp.compare("0010"))
		{
			rest = rest + "2";
		}
		else if (!tmp.compare("0011"))
		{
			rest = rest + "3";
		}
		else if (!tmp.compare("0100"))
		{
			rest = rest + "4";
		}
		else if (!tmp.compare("0101"))
		{
			rest = rest + "5";
		}
		else if (!tmp.compare("0110"))
		{
			rest = rest + "6";
		}
		else if (!tmp.compare("0111"))
		{
			rest = rest + "7";
		}
		else if (!tmp.compare("1000"))
		{
			rest = rest + "8";
		}
		else if (!tmp.compare("1001"))
		{
			rest = rest + "9";
		}
		else if (!tmp.compare("1010"))
		{
			rest = rest + "A";
		}
		else if (!tmp.compare("1011"))
		{
			rest = rest + "B";
		}
		else if (!tmp.compare("1100"))
		{
			rest = rest + "C";
		}
		else if (!tmp.compare("1101"))
		{
			rest = rest + "D";
		}
		else if (!tmp.compare("1110"))
		{
			rest = rest + "E";
		}
		else if (!tmp.compare("1111"))
		{
			rest = rest + "F";
		}
		else
		{
			continue;
		}
	}
	return rest;
}

const char* hex_char_to_bin(char c)
{
	switch (toupper(c))
	{
	case '0': return "0000";
	case '1': return "0001";
	case '2': return "0010";
	case '3': return "0011";
	case '4': return "0100";
	case '5': return "0101";
	case '6': return "0110";
	case '7': return "0111";
	case '8': return "1000";
	case '9': return "1001";
	case 'A': return "1010";
	case 'B': return "1011";
	case 'C': return "1100";
	case 'D': return "1101";
	case 'E': return "1110";
	case 'F': return "1111";
	}
	return "9999";
}

std::string hex_to_bin(const std::string& hex)
{
	std::string bin;
	for (unsigned i = 0; i != hex.length(); ++i)
		bin += hex_char_to_bin(hex[i]);
	return bin;
}



int S_BOX[8][4][16] = {
	{
		{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
		{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
		{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
		{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
	},
	{
		{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
		{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
		{0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
		{13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
	},
	{
		{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
		{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
		{13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
		{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
	},
	{
		{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
		{13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
		{10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
		{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
	},
	{
		{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
		{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
		{4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
		{11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
	},
	{
		{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
		{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
		{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
		{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
	},
	{
		{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
		{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
		{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
		{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
	},
	{
		{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
		{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
		{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
		{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
	}
};


static int E_table[48] =
{ 32, 1, 2, 3, 4, 5,
	4, 5, 6, 7, 8, 9,
	8, 9,10,11,12,13,
	12,13,14,15,16,17,
	16,17,18,19,20,21,
	20,21,22,23,24,25,
	24,25,26,27,28,29,
	28,29,30,31,32, 1
};

static int P_table[32] =

{ 16,  7, 20, 21,
   29, 12, 28, 17,
   1, 15, 23, 26,
   5, 18, 31, 10,
   2,  8, 24, 14,
   32, 27,  3,  9,
   19, 13, 30,  6,
   22, 11,  4, 25 };


static int PC_1_L[28] =
{
	57,  49, 41, 33, 25, 17, 9 ,
	1 ,  58, 50, 42, 34, 26, 18,
	10,   2, 59, 51, 43, 35, 27,
	19,  11,  3, 60, 52, 44, 36
};
static int PC_1_R[28] =
{
	63, 55, 47, 39, 31, 23, 15,
	7 , 62, 54, 46, 38, 30, 22,
	14, 6 , 61, 53, 45, 37, 29,
	21, 13, 5 , 28, 20, 12, 4
};

static int PC_2[48] =
{
	14,  17, 11, 24, 1 , 5,
	3 ,  28, 15, 6 , 21, 10,
	23,  19, 12, 4 , 26, 8,
	16,  7 , 27, 20, 13, 2,
	41,  52, 31, 37, 47, 55,
	30,  40, 51, 45, 33, 48,
	44,  49, 39, 56, 34, 53,
	46,  42, 50, 36, 29, 32

};
int IP[64] = { 58, 50, 42, 34, 26, 18, 10, 2,
			60, 52, 44, 36, 28, 20, 12, 4,
			62, 54, 46, 38, 30, 22, 14, 6,
			64, 56, 48, 40, 32, 24, 16, 8,
			57, 49, 41, 33, 25, 17, 9,  1,
			59, 51, 43, 35, 27, 19, 11, 3,
			61, 53, 45, 37, 29, 21, 13, 5,
			63, 55, 47, 39, 31, 23, 15, 7 };


static int IP_inv[64] =
{
	40, 8, 48, 16, 56, 24, 64, 32,
	39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30,
	37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28,
	35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26,
	33, 1, 41, 9 , 49, 17, 57, 25
};

int shiftBits[] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

struct Plain_Text {

	Plain_Text() { plain_txt = ""; }
	Plain_Text(string input) {
		plain_txt = "";
		for (int i = 0; i < 64; i++) plain_txt += input[IP[i] - 1];
		L = plain_txt.substr(0, 32);
		R = plain_txt.substr(32, 32);
	}

	void E_convert() {
		tempL = R;
		string temp = "";
		for (int i = 0; i < 48; i++) temp += R[E_table[i] - 1];
		R = temp;
	}
	void S_convert() {
		string temp = "";
		for (int s = 0; s < 8; s++) {
			string row = "";
			int st = s * 6;
			string col = R.substr(st + 1, 4);
			row = row + R[st] + R[st + 5];
			int col_idx = std::stoi(col, nullptr, 2);
			int row_idx = std::stoi(row, nullptr, 2);
			bitset<4> seg(S_BOX[s][row_idx][col_idx]);
			temp += seg.to_string();
		}
		R = temp;
	}

	void P_convert() {
		string temp = "";
		for (int i = 0; i < 32; i++) temp += R[P_table[i] - 1];
		R = temp;
	}

	void XOR(string input) {
		size_t sz = R.size();
		string tempR = "";
		for (int i = 0; i < sz; i++) {
			if (input[i] == R[i]) tempR += "0";
			else tempR += "1";
		}
		R = tempR;
	}
	string IP_1() {
		plain_txt = R + L;
		string output = "";
		for (int i = 0; i < 64; i++) output += plain_txt[IP_inv[i] - 1];
		return output;
	}
	void swap() {
		L = tempL;
	}
	void show_hex() {
		cout << "L+R " << GetHexFromBin(L) << " ," << GetHexFromBin(R) << endl;
	}
	void show() { cout << "L + R  " << L + R << endl; }

	string plain_txt;  // in binary
	string L;
	string R;
	string tempL;
};


struct KEY {
	KEY() {}
	KEY(string input) {
		C = input.substr(0, 32);
		D = input.substr(32, 32);
	}
	void PC1() {
		string key = C + D;
		//cout << key << endl;
		string tempC = "";
		string tempD = "";
		for (int i = 0; i < 28; i++) tempC += key[PC_1_L[i] - 1];
		for (int i = 0; i < 28; i++) tempD += key[PC_1_R[i] - 1];
		C = tempC;
		D = tempD;
	}

	string PC2() {
		string key = C + D;
		string output = "";
		for (int i = 0; i < 48; i++) output += key[PC_2[i] - 1];
		return output;
	}

	void leftshift(int shft_amt) {
		string tempC = "";
		string tempD = "";
		tempC = tempC + C.substr(shft_amt, 28 - shft_amt) + C.substr(0, shft_amt);
		tempD = tempD + D.substr(shft_amt, 28 - shft_amt) + D.substr(0, shft_amt);
		C = tempC;
		D = tempD;
	}
	void show() { cout << "Key " << C + D << endl; }

	void show_hex() { cout << "In hex l: " << GetHexFromBin(C + D) << endl; }

	string C;
	string D;
};

string* gen_key(string input) {
	string* keys = new string[16];
	KEY key(input);
	key.PC1();
	for (int i = 0; i < 16; i++) {
		key.leftshift(shiftBits[i]);
		keys[i] = key.PC2();
	}
	return keys;
}

string encrypt(string plain, string* keys) {

	string cipher = "";
	Plain_Text txt(plain);

	for (int i = 0; i < 16; i++) {
		txt.E_convert();
		txt.XOR(keys[i]);
		txt.S_convert();
		txt.P_convert();
		txt.XOR(txt.L);
		txt.swap();
	}
	cipher = GetHexFromBin(txt.IP_1());
	return cipher;
}

string decrypt(string cipher, string* keys) {

	string plain = "";
	Plain_Text txt(cipher);

	for (int i = 15; i >= 0; i--) {
		txt.E_convert();
		txt.XOR(keys[i]);
		txt.S_convert();
		txt.P_convert();
		txt.XOR(txt.L);
		txt.swap();
	}
	plain = GetHexFromBin(txt.IP_1());
	return plain;
}

void encrypt_file(string file_name) {

	clock_t start, end;
	double cpu_time_used;

	fstream file(file_name, ios::in);
	ofstream ans_file("out.txt", ios::out);
	if (!ans_file) {
		cerr << "File Fails to Open!\n";
		exit(1);
	}
	if (!file) std::cout << "No Data to Load! " << endl;

	ans_file << "Encryption" << endl;

	string buffer;
	while (getline(file, buffer)) {
		//cout << buffer << endl;
		string key = buffer.substr(0, 16);
		string plaintext = buffer.substr(17, 16);
		cout << key << endl;


		key = hex_to_bin(key);
		plaintext = hex_to_bin(plaintext);

		start = clock();
		string* keys = gen_key(key);
		string answer = encrypt(plaintext, keys);
		end = clock();

		cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

		cout << answer << endl;
		ans_file << answer << " " << cpu_time_used << " sec" << endl;

	}
	file.close();
	ans_file.close();

}

void decrypt_file(string file_name) {

	clock_t start, end;
	double cpu_time_used;

	fstream file(file_name, ios::in);
	ofstream ans_file("out.txt", ios::app);
	if (!ans_file) {
		cerr << "File Fails to Open!\n";
		exit(1);
	}
	if (!file) std::cout << "No Data to Load! " << endl;


	string buffer;
	ans_file << "Decryption" << endl;
	while (getline(file, buffer)) {
		string key = buffer.substr(0, 16);
		cout << key << endl;
		string cipher = buffer.substr(17, 16);
		cout << key << endl;

		key = hex_to_bin(key);
		cipher = hex_to_bin(cipher);

		start = clock();
		string* keys = gen_key(key);
		string answer = decrypt(cipher, keys);
		end = clock();

		cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

		cout << answer << endl;
		ans_file << answer << " " << cpu_time_used << " sec" << endl;

	}
	file.close();
	ans_file.close();
}


int main(int argc, const char * argv[]) {

	//string test_key = "5B5A57676A56676E";
	//string key = hex_to_bin(test_key);
	//string* keys = gen_key(key);

	//string test_txt = "675A69675E5A6B5A";
	//string input = hex_to_bin(test_txt);

	// 581fbc94d3a452ea   0f1571c947d9e85
	//string answer = encrypt(input, keys);
	//cout << "Cipher " << answer << endl;

	encrypt_file("DES-Key-Plaintext.txt");
	decrypt_file("DES-Key-Ciphertext.txt");
	//decrypt_file("ci_test.txt");
	return 0;
}


