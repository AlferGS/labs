#include <iostream>
using namespace std;

class classname
{
	int **p;
	int rows, colums;
public:

	/////////////////////////////////////////////////////		//Constructors//

	classname(int rs = 2, int cs = 3)								
	{
		rows = rs;
		colums = cs;
		p = new int *[rs];
		for (int i = 0; i < rs; i++)
		{
			p[i] = new int[cs];
		}
		if (!p) exit(1);
		cout << this << "classname(int sz)" << endl;
	}

	classname(const classname& name)
		:rows(name.rows), colums(name.colums) // инициализация строк и столбцов
	{
		p = new int*[rows];
		for (int i = 0; i < rows; i++) {
			p[i] = new int[colums];
		}
		if (!p) exit(1);
		for (int i = 0; i < rows; i++)
			for(int j = 0 ; j< colums; j++)
				this->p[i][j] = name.p[i][j];
		cout << this <<"classname(const classname &)" << endl;
	}

	~classname()
	{
		for (int i = 0; i < rows; i++)
		{
			delete[] p[i];
		}
		delete []p;
		cout << this <<"~classname()" << endl;
	}
	///////////////////////////////////////////////////////////////////		 C-end

	///////////////////////////////////////////////////////////////////		//Operators
	friend classname operator+(classname &obj1, classname &obj2);
	friend classname operator+ (classname &obj1, int x);
	friend classname operator- (classname &obj1, classname &obj2);
	friend classname operator- (classname &obj1, int x);

	classname operator& (classname& obj2)
	{
		int temp_num = 0, sum = 0;
		if (this->rows == obj2.colums)
		{
			classname temp(this->rows, obj2.colums);												
			for (int ii = 0; ii < this->rows; ii++)
			{
				for (int i = 0; i < obj2.colums; i++)
				{
					for (int j = 0; j < this->colums; j++)
					{
						temp_num = this->p[ii][j] * obj2.p[j][i];
						sum += temp_num;
					}
					temp.p[ii][i] = sum;
					sum = 0;
				}
			}
			return (temp);
		}
		else
		{
			cout << "warning& " << endl;
		}
	}

	int operator() (int rows, int colums)
	{
		if (colums >= 0 && colums < this->get_colums())
		{
			if (rows >= 0 && rows < this->get_rows())
			{
				return this->p[rows][colums];
			}
		}
		else
		{
			cout << "warning operator()" << endl;
			return 0;
		}
	}

	classname operator= (classname name)
	{
		int tmp = this->rows; this->rows = name.rows; name.rows = tmp;
		tmp = this->colums; this->colums = name.colums; name.colums = tmp;
		int** ptmp = this->p; this->p = name.p; name.p = ptmp;
		return *this;
	}
	////////////////////////////////////////////////////////////	O-end

	///////////////////////////////////////////////////////////		//Function
	void matrix_input()
	{
		cout << endl << "Matrix(input)" << endl;
		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0; j < this->colums; j++)
			{
				string s;
				cin >> s;
				this->p[i][j] = check(s);
			}
		}
	}

	int check(string s)
	{
		int ii = 0, n = 0;
		while (s[ii])
		{
			if (int(s[ii]) >= 48 && s[ii] <= 57)
			{
				n = n * 10 + int(s[ii] - 48);
			}
			else
			{
				cin.clear();
				cin.ignore(54321, '\n');
				cout << "error input. try again" << endl;
				cin >> s;
				return check(s);
			}ii++;
		}
		return n;
	}

	int get_rows(){
		return rows;
	}

	int get_colums() {
		return colums;
	}

	void change_el() 
	{
		int i, j, n;
		cout << "Enter row num - ";
		while (true) {
			cin >> i;
			cin.clear();
			cin.ignore(54321, '\n');
			if (!i) { cout << "input error change_el [i]" << endl; }
			else { break; }
		}i--;

		cout << "Enter colum num - ";
		while (true) {
			cin >> j;
			cin.clear();
			cin.ignore(54321, '\n');
			if (!j) { cout << "input error change_el [j]" << endl; }
			else { break; }
		}j--;

		cout << "Enter num - ";
		while (true) {
			cin >> n;
			cin.clear();
			cin.ignore(54321, '\n');
			if (!n) { cout << "input error change_el[n]" << endl; }
			else { break; }
		}
		this->p[i][j] = n;
	}

	void show_el(classname &name)
	{
		int i, j;
		cout << "Enter row num - ";
		while (true) {
			cin >> i;
			cin.clear();
			cin.ignore(54321, '\n');
			if (!i) { cout << "input error show_el[i]" << endl; }
			else { break; }
		}i--;
		cout << "Enter colum num - ";
		while (true) {
			cin >> j;
			cin.clear();
			cin.ignore(54321, '\n');
			if (!j) { cout << "input error show_el[j]" << endl; }
			else { break; }
		}j--;
		cout << "Your num on [" << i << "][" << j << "] - " << name(i,j) << endl;
	}

	void show()
	{
		cout << endl << "Matrix(show)" << endl;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < colums; j++)
			{
				cout << "[" << p[i][j] << "]";
			}
			cout << endl;
		}
	}
	/////////////////////////////////////////////////////////////		F-end
};

classname operator+ (classname &obj1, classname &obj2)
{
	classname temp(obj1.rows, obj2.colums);
	if (obj1.rows == obj2.rows || obj1.colums == obj2.colums)
	{
		for (int i = 0; i < obj1.rows; i++)
		{
			for (int j = 0; j < obj2.colums; j++)
			{
				temp.p[i][j] = obj1.p[i][j] + obj2.p[i][j];
			}
		}
		return (temp);
	}
	else
	{
		cout << "warning +" << endl;
	}
}

classname operator+ (classname &obj1, int x)
{
	classname temp(obj1.rows, obj1.colums);
	for (int i = 0; i < obj1.rows; i++)
	{
		for (int j = 0; j < obj1.colums; j++)
		{
			temp.p[i][j] = obj1.p[i][j] + x;
		}
	}
	return (temp);
}

classname operator- (classname &obj1, classname &obj2)
{
	if (obj1.rows == obj2.rows || obj1.colums == obj2.colums)
	{
		classname temp(obj1.rows, obj1.colums);
		for (int i = 0; i < obj2.rows; i++)
		{
			for (int j = 0; j < obj2.colums; j++)
			{
				temp.p[i][j] = obj1.p[i][j] - obj2.p[i][j];
			}

		}
		return (temp);
	}
	else
	{
		cout << "warning -" << endl;
	}
}

classname operator- (classname &obj1, int x)
{
	classname temp(obj1.rows, obj1.colums);
	for (int i = 0; i < obj1.rows; i++)
	{
		for (int j = 0; j < obj1.colums; j++)
		{
			temp.p[i][j] = obj1.p[i][j] - x;
		}
	}
	return (temp);
}


													//Main
int main(void)
{
	classname a(2, 3), b;
	int x;

	a.matrix_input();
	cout << "operator obj+int " << endl;
	cout << "Enter x - ";
	cin >> x;
	cin.clear();
	b = a + x;
	cout << "Show(+):";
	a.show();
	b.show();


	cout << "operator obj-int " << endl;
	cout << "Enter x - ";
	cin >> x;
	b = b - x;
	cout << "Show(-):";
	a.show();
	b.show();


	cout << "operator obj+obj " << endl;
	classname c(a.get_rows(), a.get_colums());
	c = a + b;
	cout << "Show(+):";
	c.show();


	cout << endl<< "operator obj-obj " << endl;
	c = a - b;
	cout << "Show(-):";
	c.show();


	cout << "operator obj&obj " << endl;
	classname d(a.get_rows(), b.get_colums());
	classname f(a.get_colums(), a.get_rows());
	f.matrix_input();
	d = a & f;
	cout <<"Show(&) = " << endl;
	d.show();

	cout << endl << "exaple operator()";
	cout << a(0, 0) << endl << b(1, 1) << endl << d(1, 2) << endl;;
	

	//classname a(2, 3), b(2, 3), e(3, 2);
	//a.matrix_input();
	//a.show();
	//cin.clear();
	//b.matrix_input();
	//b.show();
	//e.matrix_input();
	//e.show();
	//cout << endl << "input is end" << endl;
	//

	//cout << endl << "Sum a+b = " << endl;
	//classname r;
	//r = a + b;
	//r.show();
	//r.~classname();

	//cout << endl << "Diff a-b = " << endl;
	//classname l = a - b;
	//l.show();
	//l.~classname();

	//cout << endl << "Prod a&e = " << endl;
	//classname d(a.get_rows(), e.get_colums());
	//d = a & e;
	//d.show();
	//d.~classname();

	//cout << "Math action complited" << endl;

	//a.change_el();	b.change_el();
	//a.show_el(a);	b.show_el(b);

	//cout << "It was result of function" << endl;

	//cout << "Operator()" << endl;
	//cout << a(0, 1) << endl << b(1, 2) << endl;
	//a.show();
	//b.show();

	//int row, col;
	//cout << "Enter num rows - " << endl;
	//while (true)
	//{
	//	cin >> row;
	//	cin.clear();
	//	cin.ignore(54321, '\n');
	//	if (!row) { cout << "input error row" << endl; }
	//	else { break; }
	//}

	//cout << "Enter num colums - " << endl;
	//while (true)
	//{
	//	cin >> col;
	//	cin.clear();
	//	cin.ignore(54321, '\n');
	//	if (!col) {
	//		cout << "input error col" << endl;
	//	}
	//	else { break; }
	//}
	//cout << "Create new obj" << endl;
	//classname obj(row,col);
	//obj.matrix_input();
	//classname t(row, col);
	//t.matrix_input();
	//cout << " obj + t" << endl;
	//classname copy = obj + t;
	//obj.show();
	//copy.show();

	/////////////////////////////		//Matrix (10)
	//int size;
	//cout << "Enter size - " << endl;
	//while (true)
	//{
	//	cin >> size;
	//	cin.clear();
	//	cin.ignore(54321, '\n');
	//	if (!size) { cout << "input error size" << endl; }
	//	else { break; }
	//}

	//classname matrix[3];
	//for (int i = 0; i < 3; i++)
	//{
	//	matrix[i].matrix_input();
	//}
	//for (int i = 0; i < 3; i++)
	//{
	//	matrix[i].show();
	//}
}




	//classname operator+ (classname& obj1, classname& obj2)							// перегрузить для разных типов операторов
	//{
	//	classname temp(obj1.rows, obj1.colums);
	//	if (obj1.rows == obj2.rows || obj1.colums == obj2.colums)
	//	{
	//		for (int i = 0; i < obj1.rows; i++)
	//		{
	//			for (int j = 0; j < obj2.colums; j++)
	//			{
	//				temp.p[i][j] = obj1.p[i][j] + obj2.p[i][j];
	//			}
	//		}
	//		return (temp);
	//	}
	//	else
	//	{
	//		cout << "warning +" << endl;
	//	}
	//}

	//friend classname operator+ (classname &obj1, int x)							// перегрузить для разных типов операторов
	//{
	//	classname temp(obj1.rows, obj1.colums);
	////	if (obj1.rows == obj2.rows || obj1.colums == obj2.colums)
	//	//{
	//		for (int i = 0; i < obj1.rows; i++)
	//		{
	//			for (int j = 0; j < obj1.colums; j++)
	//			{
	//				temp.p[i][j] = obj1.p[i][j] + x;
	//			}
	//		}
	//		return (temp);
	//	//}
	////	else
	//	//{
	//		//cout << "warning +" << endl;
	//	//}
	//}

	//friend classname operator- (classname& obj1, classname& obj2)
	//{
	//	if (obj1.rows == obj2.rows || obj1.colums == obj2.colums)
	//	{
	//		classname temp(obj1.rows, obj1.colums);
	//		for (int i = 0; i < obj2.rows; i++)
	//		{
	//			for (int j = 0; j < obj2.colums; j++)
	//			{
	//				temp.p[i][j] = obj1.p[i][j] - obj2.p[i][j];
	//			}

	//		}
	//		return (temp);
	//	}
	//	else
	//	{
	//		cout << "warning -" << endl;
	//	}
	//}

	//classname operator& (classname &obj2)
	//{
	//	int temp_num = 0, sum = 0;
	//	if (this->rows == obj2.colums)
	//	{
	//		classname temp(this->rows, obj2.colums);												//!!!!!			//error
	//		for (int ii = 0; ii < this->rows; ii++)
	//		{
	//			for (int i = 0; i < obj2.colums; i++)
	//			{
	//				for (int j = 0; j < this->colums; j++)
	//				{
	//					temp_num = this->p[ii][j] * obj2.p[j][i];
	//					sum += temp_num;
	//				}
	//				temp.p[ii][i] = sum;
	//				sum = 0;
	//			}
	//		}
	//		return (temp);
	//	}
	//	else
	//	{
	//		cout << "warning& " << endl;
	//	}
	//}

	//int operator() (int rows, int colums)
	//{
	//	if (colums >= 0 && colums < get_colums())
	//	{
	//		if (rows >= 0 && rows < get_rows())
	//		{
	//			return p[rows][colums];
	//		}
	//	}
	//	else 
	//	{
	//		cout << "warning operator()" << endl;
	//		return 0;
	//	}
	//}

	//classname operator= (classname name)
	//{
	//	int tmp = rows; rows = name.rows; name.rows = tmp;
	//	tmp = colums; colums = name.colums; name.colums = tmp;
	//	int** ptmp = p; p = name.p; name.p = ptmp;
	//	return *this;
	//}