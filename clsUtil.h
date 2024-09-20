#pragma once
#include <iostream>
#include "clsDate.h"
#include "clsString.h"
#include <ctime>
using namespace std;


class clsUtil
{
public:

	enum enCharType {
		Digit = 1, CapitalLetter = 2, SmallLetter = 3,
		MixChars = 4, SpecialCharacter = 5
	};

	static void Srand()
	{
		srand(time(0));
	}

	static int RandomNumber(int from, int to)
	{
		return (rand() % (to - from + 1)) + from;
	}

	static char GetRandomCharacter(enCharType charType)
	{
		if (charType == MixChars)
		{
			charType = (enCharType)RandomNumber(1, 3);
		}

		switch (charType)
		{

		case Digit:
			return RandomNumber(48, 57);

		case CapitalLetter:
			return RandomNumber('A', 'Z');

		case SmallLetter:
			return RandomNumber('a', 'z');

		case SpecialCharacter:
			return RandomNumber(33, 47);

		}


	}

	static string GenerateWord(enCharType charType, short chars)
	{
		string word = "";

		for (short i = 0; i < chars; i++)
			word += GetRandomCharacter(charType);

		return word;
	}

	static string GenerateKey(enCharType charType)
	{

		return GenerateWord(charType, 4) + "-" + GenerateWord(charType, 4) + "-" + GenerateWord(charType, 4) + "-" + GenerateWord(charType, 4);

	}

	static void GenerateKeys(short keys, enCharType charType)
	{
		for (short i = 0; i < keys; i++)
			cout << GenerateKey(charType) << '\n';

	}

	template <typename T>
	static void Swap(T& A, T& B)
	{
		T Flag = A;
		A = B;
		B = Flag;
	}

	static void Swap(clsDate& D1, clsDate& D2)
	{
		clsDate::SwapDates(D1, D2);
	}

    template <typename T>
	static void ShuffleArray(T arr[], short length)
	{
		for (int i = 0; i < 100; i++)
			Swap<T>(arr[RandomNumber(0, length - 1)], arr[RandomNumber(0, length - 1)]);
	}

	static void FillArrayWithRandomNumbers(int arr[], short length, int from, int to)
	{
		for (int i = 0; i < length; i++)
			arr[i] = RandomNumber(from, to);
	}

	static void FillArrayWithRandomWords(string arr[], short length, enCharType charType, short wordLength)
	{
		for (int i = 0; i < length; i++)
			arr[i] = GenerateWord(charType, wordLength);
	}

	static void FillArrayWithRandomKeys(string keysArr[], short length, enCharType charType)
	{
		for (short i = 0; i < length; i++)
			keysArr[i] = GenerateKey(charType);
	}

	static string Tabs(short length)
	{
		string tabs;

		for (int i = 0; i < length; i++)
			tabs += "\t";

		return tabs;
	}

	static string EncryptText(string text, short key)
	{
		for (char& c : text)
			c += key;

		return text;
	}

	static string DecryptText(string decryptedText, short key)
	{
		for (char& c : decryptedText)
			c -= key;

		return decryptedText;
	}

	static string NumberToText(int Number)
	{

		if (Number == 0)
		{
			return "";
		}

		if (Number >= 1 && Number <= 19)
		{
			string arr[] = { "", "One","Two","Three","Four","Five","Six","Seven",
		"Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen",
		  "Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };

			return  arr[Number] + " ";

		}

		if (Number >= 20 && Number <= 99)
		{
			string arr[] = { "","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety" };
			return  arr[Number / 10] + " " + NumberToText(Number % 10);
		}

		if (Number >= 100 && Number <= 199)
		{
			return  "One Hundred " + NumberToText(Number % 100);
		}

		if (Number >= 200 && Number <= 999)
		{
			return   NumberToText(Number / 100) + "Hundreds " + NumberToText(Number % 100);
		}

		if (Number >= 1000 && Number <= 1999)
		{
			return  "One Thousand " + NumberToText(Number % 1000);
		}

		if (Number >= 2000 && Number <= 999999)
		{
			return   NumberToText(Number / 1000) + "Thousands " + NumberToText(Number % 1000);
		}

		if (Number >= 1000000 && Number <= 1999999)
		{
			return  "One Million " + NumberToText(Number % 1000000);
		}

		if (Number >= 2000000 && Number <= 999999999)
		{
			return   NumberToText(Number / 1000000) + "Millions " + NumberToText(Number % 1000000);
		}

		if (Number >= 1000000000 && Number <= 1999999999)
		{
			return  "One Billion " + NumberToText(Number % 1000000000);
		}
		else
		{
			return   NumberToText(Number / 1000000000) + "Billions " + NumberToText(Number % 1000000000);
		}


	}
};

