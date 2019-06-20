#include <TTS.h>
#include <TimedAction.h>
#include <string>
#include <cctype>

#define PWM 10
#define DOT 6
#define DASH 5
#define SPACE 4
#define DONE 3

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

String morse;
bool spaceJustAdded;

String morseToText(String morse){
  translator tts(morse);
  return tts.gettrans();
}

bool foo=true;

void writeHello(){
  Serial.write("hello");
}

void writeHi(){
  if(foo){
    Serial.write("hi");
    foo=false;
  }
}

void startNewCharacter(){
  if(!spaceJustAdded){
    morse.concat(" ");
    Serial.write(" ");
    spaceJustAdded=true;
  }
}

TTS text2speech(PWM);  // default is digital pin 10
String text;
TimedAction action = TimedAction(1000, writeHello);
TimedAction action2 = TimedAction(500, writeHi);
TimedAction checkForStartNewCharacter = TimedAction(1000, startNewCharacter);
bool activelyReadingInput;

void setup() {
  // put your setup code here, to run once:
  pinMode(DOT, INPUT);
  pinMode(DASH, INPUT);
  pinMode(SPACE, INPUT);
  pinMode(DONE, INPUT);
  text2speech.setPitch(6);
  morse="";
  activelyReadingInput=false;
  spaceJustAdded=false;
  Serial.begin(9600);
}



void loop() {
  // put your main code here, to run repeatedly:
  while( (!activelyReadingInput) && (digitalRead(DONE==LOW)) ){delay(20);}
  while(digitalRead(DONE==HIGH)){delay(20);}
  if(!activelyReadingInput)
    checkForStartNewCharacter.reset();
  activelyReadingInput=true;

  checkForStartNewCharacter.check();
  
  if(digitalRead(DOT)==HIGH){
    morse.concat(".");
    Serial.write(".");
    spaceJustAdded=false;
    while(digitalRead(DOT)==HIGH){delay(20);}
    checkForStartNewCharacter.reset();
  }
  if(digitalRead(DASH)==HIGH){
    morse.concat("-");
    Serial.write("-");
    spaceJustAdded=false;
    while(digitalRead(DASH)==HIGH){delay(20);}
    checkForStartNewCharacter.reset();
  }
  if(digitalRead(SPACE)==HIGH){
    morse.concat("/");
    Serial.write("/");
    spaceJustAdded=true;
    while(digitalRead(SPACE)==HIGH){delay(20);}
    checkForStartNewCharacter.reset();
  }
  if(digitalRead(DONE)==HIGH){
    while(digitalRead(DONE)==HIGH){delay(20);}
    Serial.write("Morse Code: ");
    Serial.write(morse.c_str());
    text=morseToText(morse);
    Serial.write("Text: ");
    Serial.write(text.c_str());
    text2speech.sayText(text.c_str());
    morse="";
    text="";
    activelyReadingInput=false;
    spaceJustAdded=false;
  }
  
}
