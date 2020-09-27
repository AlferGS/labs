#include <iostream>
#include <string>

using namespace std;

//									Классы

class Part
{
	int p_ID;												///!!!!!
	string p_NAME;
	int p_weight;
public:
	Part()
	{
		p_ID = 0;
		p_NAME = "";
		p_weight = 0;
		cout << "Part" << endl; 
	}
	Part(int m_ID, string m_NAME, int m_weight) 
	{
		this->p_ID = m_ID;
		this->p_NAME = m_NAME;
		this->p_weight = m_weight;
		cout << "Part()" << endl;
	}
	~Part() { cout << "~Part" << endl; }
	friend void part_input(Part& p_name, int m_ID, string m_NAME, int m_weight);
	friend void part_show(Part& p_name);
	friend void rewrite_func_part(Part& p_name, int c_weight);
	friend class Control;
};
class Control
{
	int c_weight;
public:
	Control()
	{
		c_weight = 0;
		cout << "Control" << endl; 
	}
	Control(int m_weight)
	{
		this->c_weight = m_weight;
		cout << "Control()" << endl; 
	}
	~Control()
	{
		cout << "~Control" << endl;
	}
	friend void control_input(Control& c_name, int m_weight);
	friend void control_show(Control& c_name);
	friend int rewrite_func_control(Control& c_name);
};
//
////							End
//
////							Функции 

void part_input(Part& p_name, int m_ID, string m_NAME, int m_weight) 
{
	static int i = 1;
	while (p_name.p_ID == 0 && p_name.p_ID == NULL)
	{
		p_name.p_ID = i;
		cout << "p_ID =  " << i++ << endl;
	}
	while (p_name.p_NAME == "" && p_name.p_NAME == "\0")
	{
		cout << "Enter p_NAME - " << endl;
		cin >> p_name.p_NAME;
		cin.clear();
	}
	while (p_name.p_weight == 0 && p_name.p_weight == NULL)
	{
		cout << "Enter p_weight - " << endl;
		cin >> p_name.p_weight;
		cin.clear();
		cin.ignore(54321, '\n');
	}
	cout << "Part object data: " << endl;
	part_show(p_name);
}

void part_show(Part& p_name)
{
	cout << " p_ID - " << p_name.p_ID;
	cout << " p_NAME - " << p_name.p_NAME;
	cout << " p_weight - " << p_name.p_weight << endl;
}

void control_input(Control& c_name, int m_weight)
{
	while (c_name.c_weight == 0 && c_name.c_weight == NULL)
	{
		cout << "Enter new c_weight - ";
		cin >> c_name.c_weight;
		cin.clear();
		cin.ignore(54321, '\n');
	}
	cout << "Control object data - " << endl;
	control_show(c_name);
}

void control_show(Control& c_name)
{
	cout << " c_weight - " << c_name.c_weight << endl;
}

int rewrite_func_control(Control& c_name)
{
	return c_name.c_weight;
}
void rewrite_func_part(Part& p_name, int c_weight)
{
	cout << "Now we rewriting p_weight = " << p_name.p_weight << " on c_weight = " << c_weight << endl;
	p_name.p_weight = c_weight;
}

//							End

//							Main

void vizov(Part& p_name, Control& c_name, int m_ID, string m_NAME, int m_weight);


int main()
{
	Part obj_1, obj_2{123, "NAME", 345}, obj_arr[4];
	Control c_obj_1{43}, c_obj_2, c_obj_arr[4];
	int m_ID = 0, m_weight = 0;
	string m_NAME = "";
	
	vizov(obj_1, c_obj_1, m_ID, m_NAME, m_weight);
	vizov(obj_2, c_obj_2, m_ID, m_NAME, m_weight);
	int i = 0;
	while (i < 4)
	{
		vizov(obj_arr[i], c_obj_arr[i], m_ID, m_NAME, m_weight);	i++;
	}
	i = 0;
	while (i < 4)
	{
		part_show(obj_arr[i++]);
	}
	return 0;
}

void vizov(Part& p_name, Control& c_name, int m_ID, string m_NAME, int m_weight)
{
	part_input(p_name, m_ID, m_NAME, m_weight);
	control_input(c_name, m_weight);
	cout << endl;
	m_weight = rewrite_func_control(c_name);
	rewrite_func_part(p_name, m_weight); m_weight = 0;
	cout << endl;
	part_show(p_name);
	cout << endl;
}