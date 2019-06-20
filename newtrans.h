
#ifndef NEWTRANS_H
#define NEWTRANS_H

class newtrans
{
  private:
    string m;
    string t;
    static string dictionary[36];
    static string morse_code[36];
  
  public:
    translator();
    translator(string morse);
    void get();
    void translate(string n, char type);
    string gettrans(); //gives you the translated string
  
  
};



#endif //NEWTRANS_H
