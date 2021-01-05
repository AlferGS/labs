#include <iostream>
#include <locale>

using namespace std;

template <typename type> type searchB(type* mass, int size)
{
	int  i = 0;

	type biggest = NULL;
	while (i < size)
	{
		if (mass[i] > biggest)
		{
			biggest = mass[i];
		}
		i++;
	}
	return type(biggest);
}
					//явна€ —пециализаци€
char searchB(char* mass, int size)
{
	int i = 0;
	cout << endl << endl << "Ёто массив символов (char *)" << endl << endl;

	char biggest = NULL;
	while (i < size)
	{
		if (mass[i] > biggest)
		{
			biggest = mass[i];
		}
		i++;
	}
	return biggest;
}

int int_check(string s)
{
	int i = 0, n = 0;
	while (s[i]) {
		if (int(s[i]) >= 48 && s[i] <= 57) {
			n = n * 10 + int(s[i] - 48);
		}
		else {
			cin.clear();
			cin.ignore(54321, '\n');
			cout << "error input. try again" << endl;
			cin >> s;
			return int_check(s);
		}
		i++;
	}
	return n;
}

double double_check(string s)
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
			return double_check(s);
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
{					//Inicialization//
	setlocale(LC_ALL, "Russian");
	const int Intsize = 5, Charsize = 7, Doubsize = 3;
	int bigInt, i = 0, massInt[Intsize];
	char bigChar, massChar[Charsize];
	double bigDoub, massDoub[Doubsize];
	string intM, doubM;

	//Input\\

	while (i < Intsize)
	{
		cin.clear();
		cout << "Enter el[int] - ";
		cin >> intM;
		massInt[i] = int_check(intM);
		cout << massInt[i] << endl;
		i++;
	}
	i = 0; cout << endl;
	while (i < Charsize)
	{
		cin.clear();
		cout << "Enter el[char] - ";
		cin >> massChar[i];
		cout << massChar[i] << endl;
		i++;
	}
	i = 0; cout << endl;
	while (i < Doubsize)
	{
		cin.clear();
		cout << "Enter el[double] - ";
		cin >> doubM;
		massDoub[i] = double_check(doubM);
		cout << massDoub[i] << endl;
		i++;
	}

	//Output mass\\

	cout << endl << endl << "Massives: " << endl; i = 0;
	while (i < Intsize)
		cout << massInt[i++] << " ";
	i = 0; cout << endl;
	while (i < Charsize)
		cout << massChar[i++] << " ";
	i = 0; cout << endl;
	while (i < Doubsize)
		cout << massDoub[i++] << " ";
	

	//Searching biggest elements\\
	 
	bigInt = searchB(massInt, Intsize);
	bigChar = searchB(massChar, Charsize);
	bigDoub = searchB(massDoub, Doubsize);

	//Output results\\
	
	cout << "Ёто массив int: " << endl;
	cout << "|massInt end|" << endl << "\t BigInt - " << bigInt << endl; i = 0;

	cout << "Ёто массив doub: " << endl;
	cout << "|massDouble end|" << endl << "\t BigDoub - " << bigDoub << endl; i = 0;

	cout << "Ёто массив char: " << endl;
	cout << "|massChar end|" << endl << "\t BigChar - " << bigChar << endl; i = 0;

}