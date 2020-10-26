#include <iostream>
using namespace std;

static int flagpoint = 0;

class Transport
{
protected:
	string body_material;
	double engine_volume;
	int tank_size;

public:
	Transport(string s = "empty", double d = 0.0, int i = 0 )
		:body_material(s), engine_volume(d), tank_size(i)
	{
//		if (this->body_material == "empty" || this-> body_material == "" ) { this->body_material = s; }
	//	if (this->engine_volume == 0.0 || this->engine_volume == NULL) { this->engine_volume = d; }
		//if (this->tank_size == 0 || this->tank_size == NULL) { this->tank_size = i; }
		//cout <<this<< " - Transport(string s, double d, int i)" << endl;
	}
	~Transport()
	{
		//cout <<this << " - ~Transport()" << endl;
	}



	virtual int int_check(string s)
	{
		int i = 0, n = 0;
		while (s[i])
		{
			if (int(s[i]) >= 48 && s[i] <= 57)
			{
				n = n * 10 + int(s[i] - 48);
			}
			else
			{
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

	virtual double double_check(string s)
	{
		int i = 0, flg = 0;
		double in = 0, dn = 0;
		while (s[i])
		{
			if (double(s[i]) >= 48 && s[i] <= 57)
			{
				i++;
				continue;
			}
			else if (char(s[i]) == '.' && flg == 0)
			{
				flg = 1;
				i++;
				continue;
			}
			else
			{
				cin.clear();
				cin.ignore(54321, '\n');
				cout << "error input. try again" << endl;
				cin >> s;
				return double_check(s);
			}
		}i = 0;
		while (s[i] != '.')
		{
			in = in * 10 + double(s[i] - 48);
			i++;
		}
		int j = i;
		i++;
		while (s[i] != '\0')
		{
			dn = dn + double(s[i] - 48)/(pow(10,i-j));
			i++;
		}
		in = in + dn;
		return in;
	}



	virtual void input_Transport()
	{
		string dtmp, itmp;
		if (this->body_material == "empty" || this->body_material == "") {
			cout << "Input Transport()" << endl;
			cout << "Enter body material - ";
			cin >> this->body_material;
		}
		if (this->engine_volume == 0.0 || this->engine_volume == NULL) {
			cout << "Enter engine volume - ";
			cin >> dtmp;
			this->engine_volume = double_check(dtmp);
		}
		if (this->tank_size == 0 || this-> tank_size == NULL) {
			cout << "Enter tank size - ";
			cin >> itmp;
			this->tank_size = int_check(itmp);
		}
	}

	virtual void T_show()
	{
		cout << endl;
		if (flagpoint == 0) {
			cout << "Show:" << endl;
			cout << "body_material - " << this->body_material << endl;;
			cout << "endgine_volume - " << this->engine_volume << endl;
			cout << "tank_size - " << this->tank_size << endl;
			flagpoint++;
		}
		else 
		{
			flagpoint--;
		}
	}

	virtual string get_body_material()	{	return this->body_material;	}
	virtual double get_engine_volume()	{	return this->engine_volume;	}
	virtual int get_tank_size()	{	return this->tank_size;	}
};

class Ground_transport: virtual public Transport
{
protected:
	int num_of_wheels;

public:
	Ground_transport(string s = "empty", double d =0.0 , int i = 0, int NoW = 0)
		:Transport(s,d,i)
	{
		this->num_of_wheels = NoW;
		//cout << this << "Ground_Transport(int NoW)" << endl;
	}
	~Ground_transport()
	{
		//cout << this << "~Ground_Transport()" << endl;
	}



	void input_GT() 
	{
		string tmpint;
		cout << "input GT" << endl;
		cout << "Enter num_of_wheels - ";
		cin >> tmpint;
		this->num_of_wheels = int_check(tmpint);
		this->input_Transport();
	}

	void GT_show()
	{
		cout << endl;
		cout << "GT_show_:" << endl;
		cout << "num of wheels - " << this->num_of_wheels << endl;
		this->T_show();
	}

	int get_num_of_wheels() { return this->num_of_wheels; }
};

class Car : public Ground_transport
{
protected:

	int trunk_capacity;
	string gearbox;

public:
	Car(string s = "empty", double d = 0.0, int i = 0, int NoW = 0, int T_capacity = 0, string numgear = "empty")
		:Ground_transport(s, d, i, NoW)
	{
		this->trunk_capacity = T_capacity;
		this->gearbox = numgear;
		//cout << "Car()" << endl;
	}
	~Car() { 
		//cout << "~Car()" << endl;
	}



	void input_Car()
	{
		string inttmp;
		cout << "input_Car:" << endl;
		cout << "Enter trunk capacity - ";
		cin >> inttmp;
		this->trunk_capacity = int_check(inttmp);
		cout << "Enter gearbox - ";
		cin >> this->gearbox;
		this->input_GT();
	}

	void Car_show()
	{
		cout << endl;
		cout << "Car_show:" << endl;
		cout << "trunk capacity - " << this->trunk_capacity << endl;
		cout << "gearbox - " << this->gearbox << endl;
		this->GT_show();
	}

	int get_trunk_capacity() { return this->trunk_capacity; }
	string get_geatbox() { return this->gearbox; }
};

class Water_Transport: virtual public Transport
{
protected:
	int displacement;

public:

	Water_Transport(string s = "empty", double d = 0.0, int i = 0, int displacemnt = 0)
		:Transport(s, d, i)
	{
		this->displacement = displacemnt;
		//cout << "Water_Transport()" << endl;
	}

	~Water_Transport() { 
		//cout << "~Water_Transport()" << endl; 
	}



	void input_Water_Transport()
	{
		string int_tmp;
		cout << "input_Water_Transport:" << endl;
		cout << "Enter displacement - ";
		cin >> int_tmp;
		this->displacement = this->int_check(int_tmp);
		this->input_Transport();
	}

	void WT_show()
	{
		cout << endl;
		cout << "WT_show" << endl;
		cout << "displacement - " << this->displacement << endl;
		this->T_show();
	}

	int get_displacement() { return this->displacement; }
};

class Motor_Boat : public Water_Transport
{
protected:
	double angle_at_the_roll;					// угол наклона при крене

public:
	Motor_Boat(string s = "emty", double d = 0.0, int i = 0, int displacemnt = 0, double aatr = 0.0)
		:Water_Transport(s,d,i,displacemnt)
	{
		this->angle_at_the_roll = aatr;
		//cout << "Motor_Boat()" << endl;
	}
	
	~Motor_Boat() { 
		//cout << "~Motor_Boat()" << endl;
	}



	void input_Motor_Boat()
	{
		string doubletmp;
		cout << "input_Motor_Boat:" << endl;
		cout << "Enter angle at the roll - ";
		cin >> doubletmp;
		this->angle_at_the_roll = double_check(doubletmp);
		this->input_Water_Transport();
	}

	void MB_show()
	{
		cout << endl;
		cout << "MB_show:" << endl;
		cout << "angle_at_the_roll - " << this->angle_at_the_roll << endl;
		this->WT_show();
	}

	double get_angle_at_the_roll() { return this->angle_at_the_roll; }
};

class Car_Amphib : public Motor_Boat,
				   public Car
{
protected:
	bool water_cannon;

public:
	Car_Amphib(string s = "empty", double d = 0.0, int i = 0, int displacemnt = 0, double aatr = 0.0, int NoW = 0, int T_capacity = 0, string numgear = "empty", bool watr_cannon = false)
		:Motor_Boat(s, d, i, displacemnt, aatr), Car(s, d, i, NoW, T_capacity, numgear)
	{
		this->water_cannon = watr_cannon;
		//cout << "Car_Amphib()" << endl;
	}
	~Car_Amphib() { 
		//cout << "~Car_Amphib()" << endl;
	}



	virtual void input_Car_Amphib()
	{
		cout << "input Car_Amphib:" << endl;
		cout << "Have you water cannon - ";
		cin >> this->water_cannon;
		this->input_Car();
		this->input_Motor_Boat();
	}

	void CA_show()
	{
		cout << "CA_show:" << endl;
		cout << "water_cannon - " << water_cannon << endl;
		this->Car_show();
		this->MB_show();
	}

	bool get_water_cannon() { return this->water_cannon; }
};

int main(void)
{
	Car_Amphib a, b("qwe", 1.2, 3, 4, 5.6, 7, 8, "asd", true), c;
	a.input_Car_Amphib();
	cout << endl << endl << endl;
	a.CA_show();
	cout << endl << endl << endl;
	b.CA_show();
	cout << endl << endl << endl;
	c.CA_show();
	a.T_show();
}