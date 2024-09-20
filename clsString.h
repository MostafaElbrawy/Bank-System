#pragma once
#include <iostream>
#include<vector>
using namespace std;

class clsString
{

private:
	string _Value;

public:
	clsString()
	{
		_Value = "";
	}

	clsString(string value)
	{
		_Value = value;
	}

	void setValue(string value)
	{
		_Value = value;
	}

	string getValue()
	{
		return _Value;
	}

	__declspec(property (put = setValue, get = getValue))string Value;

	static char InvertLetterCase(char c)
	{

		return isupper(c) ? tolower(c) : toupper(c);

	}

	static bool IsVowel(char c)
	{
		c = tolower(c);
		return(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');

	}

	static short CountWords(string s ,string delim= " ")
	{
		short counter = 0; 
		short pos = 0;

		while ((pos = s.find(delim)) != string::npos)
		{
			if(s.substr(0,pos) != "")
			    counter++;

			s.erase(0, pos+delim.length());

			
		}
			if (s != "")
				counter++;

			return counter;
	}

	short CountWords()
	{
		return CountWords(_Value);
	}

	static void UpperFirstLetterOfEachWord(string &s)
	{

		if (s[0] != ' ')
			s[0] = toupper(s[0]);

		for (int i = 0; i < s.length(); i++)
			if (s[i] == ' ' && s[i + 1] != ' ')
			{
				s[i + 1] = toupper(s[i + 1]);
				i++;
			}

	}

	void UpperFirstLetterOfEachWord()
	{
		UpperFirstLetterOfEachWord(_Value);
	}

	static void LowerFirstLetterOfEachWord(string &s)
	{


		if (s[0] != ' ')
			s[0] = tolower(s[0]);

		for (int i = 0; i < s.length(); i++)
			if (s[i] == ' ' && s[i + 1] != ' ')
			{
				s[i + 1] = tolower(s[i + 1]);
				i++;
			}

		

	}

	void LowerFirstLetterOfEachWord()
	{
		 LowerFirstLetterOfEachWord(_Value);
	}

	static string UpperAll(string s)
	{

		for (char& c : s)
			c = toupper(c);
		
		return s;
	}

	void UpperAll()
	{
	   _Value =  UpperAll(_Value);
	}

	static string LowerAll(string s)
	{
		for (char& c : s)
			c = tolower(c);
		return s;
	}

	void LowerAll()
	{
		_Value = LowerAll(_Value);
	}

	static void InvertAllLettersCase(string &s)
	{
		for (char& c : s)
			c = InvertLetterCase(c);

		
	}

	void InvertAllLettersCase()
	{
		InvertAllLettersCase(_Value);
	}

	static short CountLetters(string s, char c, bool matchCase = true)
	{
		short counter = 0;

		if (matchCase)
		{
			for (const char& a : s)
				if (a == c)
					counter++;

		}
		else
			for (const char& a : s)
				if (tolower(a) == tolower(c))
					counter++;
		return counter;

	}

	short CountLetters(char c ,bool matchCase = true)
	{
		return CountLetters(_Value, c,matchCase);
	}

	static short CountVowels(string s)
	{
		short counter = 0;

		for (const char& a : s)
			if (IsVowel(a))
				counter++;

		return counter;

	}

	short CountVowels()
	{
		return CountVowels(_Value);
	}

	static void PrintEachWord(string s)
	{

		string delim = " ", sWord = "";
		short pos = 0;
		while ((pos = s.find(delim)) != string::npos)
		{
			sWord = s.substr(0, pos);
			if (sWord != "")
				cout << sWord << '\n';

			s.erase(0, pos + delim.length());
		}

		if (s != "")
			cout << s;

	}

	void PrintEachWord()
	{
		PrintEachWord(_Value);
	}

	static vector <string> Split(string s, string delim)
	{
		vector <string> vString;

		string sWord = "";
		short pos = 0;
		while ((pos = s.find(delim)) != string::npos)
		{
			sWord = s.substr(0, pos);
			if (sWord != "")
				vString.push_back(sWord);

			s.erase(0, pos + delim.length());
		}

		if (s != "")
			vString.push_back(s);

		return vString;

	}

	vector <string> Split(string delim)
	{
		return Split(_Value, delim);
	}

	static string TrimLeft(string s)
	{

		for (int i = 0; i < s.length(); i++)
		{
			if (isalpha(s[i]))
			{
				return s.substr(i, s.length() - i);
			}
		}
		return "";

	}

	void TrimLeft()
	{
		_Value = TrimLeft(_Value);
	}

	static string TrimRight(string s)
	{

		for (int i = s.length() - 1; i >= 0; i--)
		{
			if (isalpha(s[i]))
			{
				return s.substr(0, i + 1);
			}
		}
		return "";

	}

	void TrimRight()
	{
		_Value = TrimRight(_Value);
	}

	static string Trim(string s)
	{
		return (TrimLeft(TrimRight(s)));
	}

	void Trim()
	{
		_Value = Trim(_Value);
	}

	static string Join(vector <string> vString, string delim)
	{
		string s = "";
		for (const string& a : vString)
		{
			s = s + a + delim;
		}
		return s.substr(0, s.length() - delim.length());

	}

	static string ReverseWords(string s1, string delim)
	{
		string s2 = "";
		vector <string> vString = Split(s1, delim);

		vector <string>::iterator itr = vString.end();
		while (itr != vString.begin())
		{
			itr--;
			s2 += *itr + delim;
		}

		return s2.substr(0, s2.length() - delim.length());
	}

	void ReverseWords(string delim)
	{
		_Value = ReverseWords(_Value, delim);
	}

	static void ReplaceWord(string &s, string word1, string word2)
	{
		short pos = 0;

		if (s.find(word1) == s.npos)
		{
			cout << word1 << " Not Found\n";
			s = "";
		}
		while ((pos = s.find(word1)) != s.npos)
		{
			s.replace(pos, word1.length(), word2);

		}

	
	}

	void ReplaceWord(string word1, string word2)
	{
		ReplaceWord(_Value, word1, word2);
	}

	static void RemovePunctuations(string &s)
	{
		for (int i = 0; i < s.length(); i++)
		{
			if (ispunct(s[i]))
			{
				s.erase(i, 1);
				i--;
			}

		}


	}

	void RemovePunctuations()
	{
		RemovePunctuations(_Value);
	}

};

