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

void terminator()
{
	cout << "abort() program" << endl;
	abort();
}

void unexpected()
{
	cout << "my unexpected" << endl;
	throw ("Exception 'my_unexpected'");
}

int CheckInt(string num)
{
	int i = 0, n = 0;
	while (num[i]) {
		if (int(num[i]) >= 48 && num[i] <= 57) {
			n = n * 10 + int(num[i] - 48);
		}
		else {
			cin.clear();
			cin.ignore(54321, '\n');
			cout << "error input. try again" << endl;
			cin >> num;
			return CheckInt(num);
		}
		i++;
	}
	return n;
}

double CheckDouble(string s)
{
	int i = 0, flg = 0;
	double in = 0, dn = 0;
	while (s[i]) {
		if (int(s[i]) >= 48 && int(s[i]) <= 57 && s[i] != '\0') {
			i++;
			continue;
		}
		else if (char(s[i]) == '.' && flg == 0) {
			flg = 1;
			i++;
			continue;
		}
		else {
			cin.clear();
			cin.ignore(54321, '\n');
			cout << "error input. try again" << endl;
			cin >> s;
			return CheckDouble(s);
		}
	}
	int j = i;
	i = 0; flg = 0;

	while (flg == 0) {
		if (s[i] == '.') {
			flg = 1;
			break;
		}
		if (int(s[i])) {
			in = in * 10 + double(double(s[i]) - 48);
			i++;
		}
		else {
			break;
		}
	}
	int x = i;
	i++;

	while (flg == 1) {
		if (i < j) {
			dn = dn + double(double(s[i]) - 48) / (pow(10, i - x));
			i++;
		}
		else {
			flg = 0;
		}
	}
	in = in + dn;
	return in;
}


int main(void)
{
	set_terminate(terminator);
	set_unexpected(unexpected);

	string nametxt = "TextFile.txt";
	string namebin = "BinFile.bin";

	cout << "Start program..." << endl;

	Container<int> cont;
	int val;
	char Switch = ' ';
	string T_val;


	while (Switch != 'q')
	{
		cout << "Choose: " << endl;

		cout << "\t\t/// Container function \\\ " << endl;
		cout << "- addObj(T valume) -- [1]" << endl;
		cout << "- find(T valume) -- [2]" << endl;
		cout << "- removeObj(T valume) -- [3]" << endl;
		cout << "- showCont() -- [4]" << endl;
		cout << "- Shell() -- [5]" << endl;

		cout << "\t\t/// File function \\\ " << endl;
		cout << "\t / TXT Files \ " << endl;
		cout << "- InpFile(string nametxt) -- [6]" << endl;
		cout << "- OutFile(string nametxt) -- [7]" << endl;
		cout << "- OutTXTFileBin(string nametxt) -- [8]"  << endl;
		
		cout << "\t / BIN Files \ " << endl;
		cout << "- InpFileBin(string namebin, Object obj) -- [9]" << endl;
		cout << "- OutBINFileBin(string namebin) -- [10]" << endl;

		cout << "\t / General files functions \ " << endl;
		cout << "- CheckFile(string name) -- [11]" << endl;
		cout << "- Del(string name) -- [12]" << endl;
		cout << "- InpObjFile(string nametxt, T val) - [t]" << endl;
		
		cin >> Switch;

		switch (Switch)
		{

		case '1':
		{
			system("cls");
			cout << "Enter valume(int) that you want to add - ";
			cin >> T_val;
			val = CheckInt(T_val);
			cont.addObj(val);
			break;
		}

		case '2':
		{
			system("cls");
			cout << "Enter valume(int) that you want to find - ";
			cin >> T_val;
			val = CheckInt(T_val);
			cont.find(val);
			cout << "Enter something to continue" << endl;
			cin >> T_val;
			break;
		}

		case '3':
		{
			system("cls");
			cout << "Enter valume(int) that you want to remove - ";
			cin >> T_val;
			val = CheckInt(T_val);
			cont.removeObj(val);
			cout << "Enter something to continue" << endl;
			cin >> T_val;
			break;
		}

		case '4':
		{
			system("cls");
			cout << "Show: " << endl;
			cont.showCont();
			cout << "Enter something to continue" << endl;
			cin >> T_val;
			break;
		}

		case '5':
		{
			system("cls");
			cout << "Shell:" << endl;
			cont.Shell();
			cout << "Enter something to continue" << endl;
			cin >> T_val;
			break;
		}

		case '6':
		{
			system("cls");
			cont.InpFile(nametxt);
			cout << "Enter something to continue" << endl;
			cin >> T_val;
			break;
		}

		case '7':
		{
			system("cls");
			cont.OutFile(nametxt);
			cout << "Enter something to continue" << endl;
			cin >> T_val;
			break;
		}

		case '8':
		{
			system("cls");
			cont.OutTXTFileBin(nametxt);
			cout << "Enter something to continue" << endl;
			cin >> T_val;
			break;
		}

		case '9':
		{
			system("cls");
			//cout << "this feature is in development" << endl;
			//Container<int>::Object* obj;
			//obj = cont.getHead();
			cout << "Enter T valume (int) - ";
			int val;
			cin >> val;

			cont.InpFileBin(namebin, val);											// ??
			cout << "Enter something to continue" << endl;
			cin >> T_val;
			break;
		}

		case '0':
		{
			system("cls");
			cont.OutBINFileBin(namebin);
			cout << "Enter something to continue" << endl;
			cin >> T_val;
			break;
		}

		case '-':
		{
			system("cls");
			cout << "Choose File (TXT/BIN) \nTXT - 1\tBIN - 2" << endl;
			cin >> val;
			if (val == 1)
				cont.CheckFile(nametxt);
			else if (val == 2)
				cont.CheckFile(namebin);
			else
				cout << "error input." << endl;
			cout << "Enter something to continue" << endl;
			cin >> T_val;
			break;
		}

		case '=':
		{
			system("cls");
			cout << "Choose File (TXT/BIN) \nTXT - 1\tBIN - 2" << endl;
			cin >> val;
			if (val == 1)
				cont.Del(nametxt);
			else if (val == 2)
				cont.Del(namebin);
			else
				cout << "error input." << endl;
			cout << "Enter something to continue" << endl;
			cin >> T_val;
			break;
		}

		case 't':
		{
			system("cls");
			cout << "Enter num of obj that you want to add - "; 
			cin >> T_val;
			val = CheckInt(T_val);
			cont.InpObjFile(nametxt, val);
			break;
		}
		case 's':
		{
			system("cls");
			cont.Sort(nametxt);
			cin >> T_val;
			val = CheckInt(T_val);
			break;
		}

		default:
		{
			break;
		}

		}

		system("cls");
	}
}


/*
	Container<int> Int_Cont;
	Container<int>::Iterator Int_Iterator;

	Int_Cont.addObj(5);
	Int_Cont.addObj(5);
	Int_Cont.addObj(3);
	Int_Cont.addObj(2);
	Int_Cont.addObj(4);
	Int_Cont.addObj(7);
	Int_Cont.addObj(6);
	cout << endl;

	Int_Cont.showCont();
	cout << endl;

	Int_Cont.find(9);
	Int_Cont.find(7);
	cout << endl;

	Int_Cont.removeObj(9);
	Int_Cont.removeObj(7);
	cout << endl;

	Int_Cont.find(7);
	cout << endl;

	Int_Cont.showCont();
	cout << endl;

	Int_Cont.Shell();
	Int_Cont.showCont();
	cout << endl;


											//Double
	Container<double> Double_Cont;
	Container<double>::Iterator Double_Iterator;

	Double_Cont.addObj(5.12);
	Double_Cont.addObj(2.56);
	Double_Cont.addObj(6.9214);
	Double_Cont.addObj(6.9213);
	cout << endl;

	Double_Cont.showCont();
	cout << endl;

	Double_Cont.find(6.9213);
	cout << endl;

	Double_Cont.removeObj(6.9213);
	cout << endl;

	Double_Cont.find(6.9213);
	cout << endl;

	Double_Cont.showCont();
	cout << endl;

	Double_Cont.Shell();
	Double_Cont.showCont();
	cout << endl;


											//Char
	Container<char> Char_Cont;
	Container<char>::Iterator Char_Iterator;

	Char_Cont.addObj('c');
	Char_Cont.addObj('g');
	Char_Cont.addObj('k');
	Char_Cont.addObj('a');
	Char_Cont.addObj('y');
	cout << endl;

	Char_Cont.showCont();
	cout << endl;

	Char_Cont.find('c');
	Char_Cont.find('k');
	cout << endl;

	Char_Cont.removeObj('c');
	Char_Cont.removeObj('k');
	cout << endl;

	Char_Cont.find('c');
	Char_Cont.find('k');
	cout << endl;

	Char_Cont.showCont();
	cout << endl;
	Char_Cont.Shell();
	Char_Cont.showCont();
	cout << endl;


	
*/