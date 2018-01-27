#include <iostream>
#include<fstream>
#include<interpreter.h>
using namespace std;

int main()
{
    ifstream fin;
    string line;
    Interpreter i;
    fin.open("input.txt", ios::in);
    if(fin.is_open())
    {
        while(getline(fin,line))
        {
            i.proceed(line);
        }
        fin.close();
    }
    return 0;
}
