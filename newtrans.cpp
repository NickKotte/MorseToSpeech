#include "stdafx.h"
#include <string>
#include <cctype>
using namespace std;

class translator
{
private:
	string m;
	string t;
	string dictionary[36] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J",
		"K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W",
		"X", "Y", "Z", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0" };

	string morse_code[36] = { ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.",
	"---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", ".----", "..---", "...--", "....-",
	".....", "-....", "--...", "---..", "----.", "-----" };
public:
	translator()
	{
		// don't use this
	}
	translator(string morse) //auto translates when declared
	{
		m = morse;
		get();
	}

	void get()
	{
		string n = "";
		for (int i = 0; i < m.size(); i++)
		{
			if (iswspace(m[i]) || m[i] == '/')
			{
				translate(n, m[i]);
				n.clear();
			}
			else if (i == (m.size() - 1))
			{
				n = n + m[i];
				translate(n, m[i]);
				n.clear();
			}
			else
				n = n + m[i];
		}

	}

	void translate(string n, char type)
	{
		for (int i = 0; i < 36; i++)
		{
			if (morse_code[i] == n) 
			{
				if (type == '/')
					t = t + dictionary[i] + " ";
				else
					t = t + dictionary[i];
				break;
			}
		}
	}

	string gettrans() //gives you the translated string
	{
		return t;
	}
};
