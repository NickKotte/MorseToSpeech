// translator.cpp : Defines the entry point for the console application.
//

#include <string>
#include <cctype>
#include <fstream>
using namespace std;

class translator
{
private:
	string m;
	string t;
	string dictionary[36] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J",
		"K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W",
		"X", "Y", "Z", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0" };
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
		ifstream in;
		in.open("letters.txt");
		for (int i = 0; i < 36; i++)
		{
			string find;
			getline(in, find);
			if (find.compare(n) == 0)
			{
				if (type == '/')
					t = t + dictionary[i] + " ";
				else
					t = t + dictionary[i];
				break;
			}
		}
		in.close();
	}

	string gettrans() //gives you the translated string
	{
		return t;
	}
};
