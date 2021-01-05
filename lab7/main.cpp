#include <iostream>
#include <stdlib.h>

#include <locale>
using namespace std;

#include"Containr.h"

class Exception
{
private:
	string err_str;

public:
	Exception(string err)
	{
		err_str = err;
	}

	const char* getErr()
	{
		return err_str.c_str();
	}
};

void terminate()
{
	cout << "abort() program"<< endl;
	abort();
}



int main(void)
{
	set_terminate(terminate);

	cout << "program start" << endl;
											//Int
	Container<int> Int_Cont;
	Container<int>::Iterator Int_Iterator;

	Int_Cont.addObj(5);
	Int_Cont.addObj(1);
	Int_Cont.addObj(3);

	cout << endl;
	Int_Cont.find(2);
	Int_Cont.find(1);
	cout << endl;
	Int_Cont.showCont();

	cout << endl;
	Int_Cont.addObj(2);
	Int_Cont.addObj(4);
	Int_Cont.addObj(7);
	Int_Cont.addObj(6);
	cout << endl;

	Int_Cont.showCont();
	cout << endl;
	Int_Cont.Shell();
	cout << endl;

	Int_Cont.removeObj(9);
	Int_Cont.removeObj(7);
	cout << endl;
	Int_Cont.showCont();

											//Double
	Container<double> Double_Cont;
	Container<double>::Iterator Double_Iterator;

	Double_Cont.addObj(5.12);
	Double_Cont.addObj(2.56);

	cout << endl;
	Double_Cont.find(5.12);
	cout << endl;
	Double_Cont.showCont();

	cout << endl;
	Double_Cont.addObj(6.9214);
	Double_Cont.addObj(6.9213);
	cout << endl;

	Double_Cont.showCont();
	cout << endl;
	Double_Cont.Shell();
	cout << endl;
	Double_Cont.removeObj(6.9213);
	cout << endl;
	Double_Cont.showCont();

											//Char
	Container<char> Char_Cont;
	Container<char>::Iterator Char_Iterator;

	Char_Cont.addObj('c');
	Char_Cont.addObj('g');
	Char_Cont.addObj('k');

	cout << endl;
	Char_Cont.find('c');
	Char_Cont.find('a');
	cout << endl;
	Char_Cont.showCont();

	cout << endl;
	Char_Cont.addObj('a');
	Char_Cont.addObj('y');
	cout << endl;

	Char_Cont.showCont();
	cout << endl;
	Char_Cont.Shell();
	cout << endl;
	Char_Cont.removeObj('k');
	Char_Cont.removeObj('q');
	cout << endl;
	Char_Cont.showCont();

}
