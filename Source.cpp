#include <iostream>
using namespace std;

static int flagpoint = 0;

class Transport
{
public:
	string name;
	virtual void show() = 0;
	virtual double get_double() = 0;
	virtual int get_int() = 0;
};

class Ground_Transport : public Transport
{
protected:
	int num_of_wheels;

public:
	Ground_Transport(int NoW = 0, string nam = "") :Transport(), num_of_wheels(NoW) { name = nam; }
	~Ground_Transport() {}

	void show() override{
		cout << endl << "GT show:" << endl;
		cout << "num of wheels - " << num_of_wheels << endl;
		cout << "name - " << name << endl;
	}
	double get_double() override { return 0; }
	int get_int() override { return num_of_wheels; }
};

class Water_Transport : public Transport
{
protected:
	int displacement;

public:
	Water_Transport(int displacemnt = 0, string nam = "") : Transport(), displacement(displacemnt) { name = nam; }
	~Water_Transport() {}

	void show() override{
		cout << endl;
		cout << "WT_show" << endl;
		cout << "displacement - " << this->displacement << endl;
		cout << "name - " << name << endl;
	}

	double get_double() override { return 0; }
	int get_int() override { return displacement; }
};

class Motor_Boat : public Water_Transport
{
protected:
	double angle_at_the_roll;					// угол наклона при крене

public:
	Motor_Boat(double aatr = 0.0, int displacemnt = 0, string nam = "") :Water_Transport(displacemnt), angle_at_the_roll(aatr) { name = nam; }
	~Motor_Boat() {}

	double get_double() override { return angle_at_the_roll; }
	int get_int() override { return displacement; }
	void show() override{
		cout << endl;
		cout << "MB_show:" << endl;
		cout << "angle_at_the_roll - " << angle_at_the_roll << endl;
		cout << "displacement - " << displacement << endl;
		cout << "name - " << name << endl;
	}
};

int int_check(string s)
{
	int i = 0, n = 0;
	while (s[i]){
		if (int(s[i]) >= 48 && s[i] <= 57){
			n = n * 10 + int(s[i] - 48);
		}
		else{
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
	while (s[i]){
		if (int(s[i]) >= 48 && int(s[i]) <= 57 && s[i] != '\0'){
			i++;
			continue;
		}
		else if (char(s[i]) == '.' && flg == 0){
			flg = 1;
			i++;
			continue;
		}
		else{
			cin.clear();
			cin.ignore(54321, '\n');
			cout << "error input. try again" << endl;
			cin >> s;
			return double_check(s);
		}
	}
	int j = i;
	i = 0; flg = 0;

	while (flg == 0){
		if (s[i] == '.'){
			flg = 1;
			break;
		}
		if (int(s[i])){
			in = in * 10 + double(double(s[i]) - 48);
			i++;
		}
		else{
			break;
		}
	}
	int x = i;
	i++;

	while (flg == 1){
		if (i < j) {
			dn = dn + double(double(s[i]) - 48) / (pow(10, i - x));
			i++;
		}
		else{
			flg = 0;
		}
	}
	in = in + dn;
	return in;
}

int main(void)
{
	int num_of_wheels, displacement;
	double angle_at_the_roll;
	string name;
	Transport* pTransport[3];

	string itmp, dtmp;

	cout << endl << "Enter name(string) - ";		//ground transport
	cin >> name;
	cout << endl;

	cout << "Enter angle at de roll(doub) - ";		//Motor Boat
	cin >> dtmp;
	angle_at_the_roll = double_check(dtmp);

	cout << endl << "Enter displacement(int) - ";		//water transport
	cin >> itmp;
	displacement = int_check(itmp);

	cout << endl << "Enter num_of_wheels(int) - ";		//ground transport
	cin >> itmp;
	num_of_wheels = int_check(itmp);

	cout << "Input end" << endl;


	cout << endl << "-------------------------" << endl;
	Motor_Boat MB(angle_at_the_roll, 123, name);
	pTransport[0] = &MB;


	cout << endl << "Enter displacement(int) - ";		//water transport
	cin >> itmp;
	displacement = int_check(itmp);

	cout << endl << "Enter name(string) - ";		//ground transport
	cin >> name;
	cout << endl;

	cout << "----------------------------" << endl;
	Water_Transport WT(displacement, name);
	pTransport[1] = &WT;


	cout << endl << "Enter name(string) - ";		//ground transport
	cin >> name;
	cout << endl;

	cout << endl << "Enter num_of_wheels(int) - ";		//ground transport
	cin >> itmp;
	num_of_wheels = int_check(itmp);

	cout << "----------------------------" << endl;
	Ground_Transport GT(num_of_wheels, name);
	pTransport[2] = &GT;


	pTransport[0]->show();
	pTransport[1]->show();
	pTransport[2]->show();
}
/*
			  transport														  |  	|
			/           \
		  GT             WT										   NoW(i)                displcmnt(i)
						   \
							motor boat                                                      angle atthrl(d)
*/