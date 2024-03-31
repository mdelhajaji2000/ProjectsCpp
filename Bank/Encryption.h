#pragma once

#include <string>

using namespace std;

class clsEncryption {
private :
	int _EnKey1 = 656574847;
	int _Enkey2 = 90094;
	int _Enkey3 = 44567;

	string Encryption(string text)
	{
		for (int i = 0; i < text.length(); i++)
		{
			text[i] += _EnKey1;
			text[i] -= _Enkey2;
			text[i] -= _Enkey3;
		}

		return text;
	}

	string Dencryption(string text)
	{
		for (int i = 0; i < text.length(); i++)
		{
			text[i] += _Enkey3;
			text[i] += _Enkey2;
			text[i] -= _EnKey1;
		}

		return text;
	}

public :
	string Enc(string str)
	{
		return Encryption(str);
	}
	string Denc(string str)
	{
		return Dencryption(str);
	}
};