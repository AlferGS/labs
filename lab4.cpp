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
	Transport(int tanksize = 0, double engine_vol = 0.0, string body_mat = "")
	{
		body_material = body_mat;
		engine_volume = engine_vol;
		tank_size = tanksize;
	}
	~Transport()
	{
		//cout <<this << " - ~Transport()" << endl;
	}

	virtual void T_show()
	{
		cout << endl;
		if (flagpoint == 0) {
			cout << "Transport Show:" << endl;
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

	virtual void set_body_material(string s) { this->body_material = s; }
	virtual void set_engine_volume(double d) {  this->engine_volume = d; }
	virtual void set_tank_size(int i) {  this->tank_size = i; }

	virtual string get_body_material()	{	return this->body_material;	}
	virtual double get_engine_volume()	{	return this->engine_volume;	}
	virtual int get_tank_size()	{	return this->tank_size;	}
};

class Ground_transport: public Transport
{
protected:
	int num_of_wheels;

public:
	Ground_transport(int NoW = 0, int tanksize = 0, double engine_vol = 0.0, string body_mat = "")
		:Transport(tanksize, engine_vol, body_mat)
	{
		num_of_wheels = NoW;
		//cout << this << "Ground_Transport(int NoW)" << endl;
	}
	~Ground_transport()
	{
		//cout << this << "~Ground_Transport()" << endl;
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
	Car(int T_capacity = 0, string numgear = "empty", int NoW = 0, int tanksize = 0, double engine_vol = 0.0, string body_mat = "")
		:Ground_transport(NoW, tanksize, engine_vol, body_mat)
	{
		trunk_capacity = T_capacity;
		gearbox = numgear;
	}
	~Car() { 
		//cout << "~Car()" << endl;
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

class Water_Transport: public Transport
{
protected:
	int displacement;

public:
	Water_Transport(int displacemnt, int tanksize, double engine_vol, string body_mat )	:Transport(tanksize, engine_vol, body_mat)
	{
		displacement = displacemnt;
	}

	~Water_Transport() { 
		//cout << "~Water_Transport()" << endl; 
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
	//Motor_Boat() {}
	Motor_Boat(double aatr, int displacemnt, int tanksize, double engine_vol, string body_mat)	:Water_Transport(displacemnt, tanksize, engine_vol, body_mat)
	{
		angle_at_the_roll = aatr;
	}
	
	~Motor_Boat() { 
		//cout << "~Motor_Boat()" << endl;
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
	Car_Amphib(bool watr_cannon = false, string numgear = "empty", int T_capacity = 0, int NoW = 0, double aatr = 0.0, int displacemnt = 0, int tanksize = 0, double engine_vol = 0.0, string body_mat = "")
		:Motor_Boat(aatr, displacemnt, tanksize, engine_vol, body_mat), Car(T_capacity, numgear, NoW, tanksize, engine_vol, body_mat)
	{
		this->water_cannon = watr_cannon;
	}
	~Car_Amphib() { 
		//cout << "~Car_Amphib()" << endl;
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


int int_check(string s)
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


double double_check(string s)
{
	int i = 0, flg = 0;
	double in = 0, dn = 0;
	while (s[i])
	{
		if (int(s[i]) >= 48 && int(s[i]) <= 57 && s[i] != '\0')
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
	}
	int j = i;
	i = 0; flg = 0;
	while (flg == 0)
	{
		if (s[i] == '.')
		{
			flg = 1;
			break;
		}
		if (int(s[i]))
		{
			in = in * 10 + double(double(s[i]) - 48);
			i++;
		}
		else
		{
			break;
		}
	}
	int x = i;
	i++;
	while (flg == 1)
	{
		if (i < j) {
			dn = dn + double(double(s[i]) - 48) / (pow(10, i - x));
			i++;
		}
		else
		{
			flg = 0;
		}
	}
	in = in + dn;
	return in;
}


int main(void)
{
	bool water_gun;
	int tank_size, num_of_wheels, displacement, trunk_capacity;
	double engine_volume, angle_at_the_roll;
	string body_material, gearbox;

	string itmp, dtmp;

	cout << "Enter angle at de roll(doub) - ";
	cin >> dtmp;
	angle_at_the_roll = double_check(dtmp);

	cout << endl << "Enter displacement(int) - ";
	cin >> itmp;
	displacement = int_check(itmp);

	cout << endl << "Enter body_material(str) - ";
	cin >> body_material;

	cout << endl << "Enter engine_volume(doub) - ";
	cin >> dtmp;
	engine_volume = double_check(dtmp);

	cout << endl << "Enter tank_size(int) - ";
	cin >> itmp;
	tank_size = int_check(itmp);

	cout << "Enter gearbox(str) - ";
	cin >> gearbox;

	cout << endl << "Enter trunk_capacity(int) - ";
	cin >> itmp;
	trunk_capacity = int_check(itmp);

	cout << endl << "Enter num_of_wheels(int) - ";
	cin >> itmp;
	num_of_wheels = int_check(itmp);

	cout << endl << "Enter water_gun(bool) - ";
	cin >> water_gun;

	cout << "Input end" << endl;

	// Задание 3)
	Car_Amphib CA(water_gun, gearbox, trunk_capacity, num_of_wheels, angle_at_the_roll, displacement, tank_size, engine_volume, body_material);


	CA.CA_show();


}






