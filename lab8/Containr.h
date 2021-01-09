#ifndef CONTAINR_H
#define CONTAINR_H

#include <iostream>
#include <string>
#include <locale>
#include <fstream>

class Object;

using namespace std;

template <typename T>

class Container
{
private:

	class Object;
	friend class Object;
	class TextFile;
	friend class TextFile;
	class BinFile;
	friend class BinFile;
												//class Object
	class Object
	{
	private:

		string FIO;
		int group_ID;
		double mid_mark;
		T valume;
		Object* next;


	public:

		friend class Container<T>;
		friend class Iterator;
		friend class BinFile;

												//Add functions
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

		void setFIO()
		{
			do {
				if (strlen(FIO.c_str()) > 0 && strlen(FIO.c_str()) < 3)
					cout << "Your FIO are short." << endl;

				cout << "Input FIO - ";
				cin.clear();
				cin >> FIO;

			} while (strlen(FIO.c_str()) < 3);
		}
		
		void setID(){
			string str;
			cout << "Enter group_ID - ";
			cin.clear();
			cin >> str;
			group_ID = CheckInt(str);
		}

		void setMark()
		{
			string str;
			cout << "Enter mid_mark - ";
			cin.clear();
			cin >> str;
			mid_mark = CheckDouble(str);
		}

		void setValume()
		{
			cout << "Enter T valume - ";
			cin.clear();
			cin >> valume;
		}



		void getFIO()
		{
			cout << "FIO - " << FIO << endl;
		}

		void getID()
		{
			cout << "group Id - " << group_ID << endl;
		}

		void getMark()
		{
			cout << "mid_mark - " << mid_mark << endl;
		}

		void getValume()
		{
			cout << "Valume - " << valume << endl;
		}

		
												//Constructors
		Object()
		{
			setFIO();
			setID();
			setMark();
			setValume();
		}
		Object(T V) : valume(V)
		{
			setFIO();
			setID();
			setMark();
		}
		Object(string F, int I, double M, T V) :FIO(F), group_ID(I), mid_mark(M), valume(V)
		{
		}
		~Object()
		{
		}
	};
	  
	class Files
	{
	private:
		/*string nametxt = "TextFile.txt";
		string namebin = "BinFile.bin";*/

	public:
		friend class Container<T>;
		friend class Iterator;
		friend class Object;

	};


	

public:

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

	class Iterator;
	friend class Iterator;

	class Iterator
	{
	private:

		Object* node;


	public:

		friend class Container<T>;
		friend class Object;

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
												//Constructors
		Iterator() :node(nullptr)
		{
		}
		Iterator(Object* temp) :node(temp)
		{
		}
		Iterator(const Iterator& iter) : node(iter.node)
		{}
						
												//???

												//operators
		Iterator operator++(int)
		{
			node = node->next;
			return *this;
		}

		bool operator ==(const Iterator& iter) const
		{
			return (node == iter.node);
		}

		bool operator !=(const Iterator& iter) const
		{
			return !(iter == *this);
		}

		Iterator& operator=(const Iterator& iter)
		{
			node = iter.node;
			return *this;
		}
	
	};

												//Constructors
private:
	Object* Obj_head;
	Object* Obj_tail;

	Iterator Iter_head;
	Iterator Iter_tail;
public:

	Container()
	{
	}
	Container(T valume)
	{
		Obj_head = Obj_tail = new Object;
		Obj_tail->next = nullptr;

		Iter_head = Iterator(Obj_head);
		Iter_tail = Iterator(Obj_tail);
		addObj(valume);
	}
	~Container()
	{
		Object* del = this->Obj_head;
		Object* end = this->Obj_tail;
		for (Object* index = Obj_head; index != Obj_tail;)
		{
			index = index->next;
			delete del;
			del = index;
		}
		delete del;
	}


	bool operator == (const Container& cont) const
	{
		return (size() == cont.size());
	}

	bool operator != (const Container& cont) const
	{
		return !(cont == *this);
	}
																			

												//functions
	void addObj(T valume)
	{

		try
		{
			Object* Node = new Object(valume);
			if (check(valume))
			{
				throw Exception("This valume already exist");
			}
			if (this->Obj_head == nullptr)
			{
				this->Obj_head = Node;
				this->Obj_tail = Node;
				return;
			}
			Iterator index = Iterator(Obj_head);
			while (index != Obj_tail)
				index++;
			index.node->next = Node;

			
			this->Obj_tail = Node;
		}
		catch (Exception except) {

			cerr << except.getErr() << endl;;
			T val;
			cout << "Enter new T valume - ";
			cin >> val;
			addObj(val);
		}

	};

	bool check(T valume) const
	{
		for (Iterator index = Iterator(Obj_head); index != Iter_tail; index++)
		{
			if (index.node->valume == valume)
				return true;
		}
		return false;

	}

	bool find(T valume)
	{
		try
		{
			for (Iterator hd = Iterator(Obj_head); hd != Iter_tail; hd++)
			{
				if (hd.node->valume == valume)
				{
					cout << "this valume exist [" << valume << "]" << endl;
					return true;
				}
			}
			throw Exception("This valume doesn't exist");
		}
		catch (Exception except)
		{
			cerr << except.getErr() << "[" << valume << "]" << endl;
		}
		return false;
	};

	bool removeObj(T valume)
	{
		try {
			if (this->Obj_head == NULL)
				throw Exception("tried to remove from an empty list\n");
			if (check(valume) == false)
				throw Exception("This valume didn't exist\n");
			Iterator hd = Iterator(Obj_head);
			Iterator nx = Iterator(hd.node->next);

			if (hd.node->valume == valume)
			{
				Obj_head = Obj_head->next;
				hd.node->next = nullptr;
				delete hd.node;
				return true;
			}
			if (nx.node->valume != valume) {
				do {
					hd++;
					nx++;

				} while (nx.node->valume != valume);
			}

			if (nx.node->valume == valume)
			{
				Iterator del = Iterator(nx);
				nx++;
				hd.node->next = nx.node;
				if (del.node->next == nullptr)
					Obj_tail = nx.node;
				delete del.node; 
				return true;
			}
		}

		catch (Exception except)
		{
			cerr << except.getErr() << endl;
		}
		return false;
	};

	void showCont()
	{
		try
		{
			if (this->Obj_head == nullptr)
				throw Exception("tried to show empty list\n");

			for (Iterator hd = Iterator(Obj_head); hd != Iter_tail; hd++)
			{
				hd.node->getFIO();
				hd.node->getID();
				hd.node->getMark();
				hd.node->getValume();
				cout << "---" << endl;
			}
		}

		catch (Exception except)
		{
			cerr << except.getErr();
		}
	}

	void Shell()
	{
		try
		{
			if (Obj_head == Obj_tail)
				throw Exception("tried to sort an empty list\n");
			T temp = 0;
			int i = 0;
			int mid = size();
			int end = mid;
			mid = mid / 2;
			while (mid > 0)
			{
				Object* left = Obj_head;
				Object* right = Obj_head;
				for (i = 0; i < mid; i++)
				{
					right = right->next;
				}
				for (i = 0; i < end - mid; i++)
				{
					int j = i;
					while (j >= 0 && left->valume > right->valume)
					{
						string Stmp;
						double Dtmp;
						int Itmp;

						Stmp = left->FIO;
						left->FIO = right->FIO;
						right->FIO = Stmp;

						Itmp = left->group_ID;
						left->group_ID = right->group_ID;
						right->group_ID = Itmp;

						Dtmp = left->mid_mark;
						left->mid_mark = right->mid_mark;
						right->mid_mark = Dtmp;

						temp = left->valume;
						left->valume = right->valume;
						right->valume = temp;
						j--;
					}
					left = left->next;
					right = right->next;
				}
				mid = mid / 2;

				if (mid == 0)
				{
					mid = 1;
					left = Obj_head;
					right = Obj_head;
					for (i = 0; i < mid; i++)
					{
						right = right->next;
					}
					for (i = 0; i < end - mid; i++)
					{
						int j = i;
						while (j >= 0 && left->valume > right->valume)
						{
							string Stmp;
							double Dtmp;
							int Itmp;

							Stmp = left->FIO;
							left->FIO = right->FIO;
							right->FIO = Stmp;

							Itmp = left->group_ID;
							left->group_ID = right->group_ID;
							right->group_ID = Itmp;

							Dtmp = left->mid_mark;
							left->mid_mark = right->mid_mark;
							right->mid_mark = Dtmp;

							temp = left->valume;
							left->valume = right->valume;
							right->valume = temp;
							j--;
						}
						left = left->next;
						right = right->next;
					}
					mid = mid / 2;
				}
			}
		}
		catch (Exception except)
		{
			cerr << except.getErr() << endl;
		}

	}

	int size() const
	{
		int count = 0;
		for (Iterator size = Iterator(Obj_head); size != Iter_tail; size++)
		{
			++count;
		}

		return count;
	}

	//Files function

	bool CheckFile(string nametxt)
		{
			try
			{
				if (!fstream(nametxt)) {
					throw Exception("File wasn't founded");
					return false;
				}
				else {
					cout << "File was founded" << endl;
					return true;
				}
			}
			catch (Exception except)
			{
				cout << except.getErr() << endl;
			}
		}

	void Del(string nametxt)
	{
		fstream file;
		file.open(nametxt, fstream::in | fstream::out | fstream::binary);
		try
		{
			if (!file.is_open())
				throw Exception("File wasn't opened");
		}
		catch (Exception except)
		{
			cout << except.getErr() << endl;
		}

		OutFile(nametxt);

		cout << "Enter num of string, that you want delete - ";
		int num_line_del;
		cin >> num_line_del;
		int num_line_now = 0;
		string del_line, line_file;

		while (std::getline(file, del_line))
		{
			num_line_now++;

			if (!(num_line_now == num_line_del)) {
				line_file.insert(line_file.size(), del_line);
				line_file.insert(line_file.size(), "\n");
			}
		}
		file.close();

		fstream file_rep;
		file_rep.open(nametxt, fstream::out | fstream::binary);
		file_rep.write(line_file.c_str(), line_file.size());
		file_rep.clear();
		file_rep.close();

		OutFile(nametxt);

	}	// моя сортировка

	void get_bin_el(Object& temp, string nametxt) {
		int len;
		fstream file;
		file.open(nametxt, fstream::in | fstream::out | fstream::binary);
		file.read((char*)&temp.group_ID, sizeof(int));
		file.read((char*)&temp.mid_mark, sizeof(double));
		file.read((char*)&len, sizeof(int));
		char* nam = new char[len + 1];
		file.read(nam, len);
		nam[len] = '\0';
		temp.FIO = nam;

		delete[] nam;
	}

	void Sort(string nametxt)
	{
		fstream file;
		file.open(nametxt, fstream::in | fstream::out | fstream::binary);
		try
		{
			if (!file.is_open())
				throw Exception("File wasn't opened");
		}
		catch (Exception except)
		{
			cout << except.getErr() << endl;
		}

	}

	void InpFile(string nametxt)
		{
			fstream file;
			file.open(nametxt, fstream::out | fstream::app);
			try
			{
				if (!file.is_open())
					throw Exception("File wasn't opened");
			}
			catch (Exception except)
			{
				cout << except.getErr() << endl;
			}

			string str;
			cout << "Enter some text: ";
			cin >> str;
			file << str << "\n";
			file.close();
		}

	void InpObjFile(string nametxt, T val)
	{
		fstream file;
		file.open(nametxt, fstream::out | fstream::app);
		try
		{
			if (!file.is_open())
				throw Exception("File wasn't opened");
		}
		catch (Exception except)
		{
			cout << except.getErr() << endl;
		}

		Iterator obj = Iterator(Obj_head);
		while (obj.node->valume != val)
			obj++;

		file << "*" << obj.node->valume << "\n";
		file << obj.node->FIO << "\n";
		file << obj.node->group_ID << "\n";
		file << obj.node->mid_mark << "\n";
		file << "~~~" << "\n";
		file.close();
	}

	void OutFile(string nametxt)
		{
			fstream file;
			file.open(nametxt, fstream::in);
			try
			{
				if (!file.is_open())
					throw Exception("File wasn't opened");
			}
			catch (Exception except)
			{
				cout << except.getErr() << endl;
			}

			cout << "File " << nametxt << " was opened." << endl;
			string str;
			while (!file.eof())
			{
				while (std::getline(file, str))
				{
					cout << str << endl;
				}
			}
			file.close();

		}
																	
	void OutTXTFileBin(string nametxt)
	{
		char* msg;
		
		int num = 90;
		msg = new char[num];
		fstream file;
		file.open(nametxt, fstream::in | fstream::binary);
		try
		{
			if (!file.is_open())
				throw Exception("File wasn't opened");
		}
		catch (Exception except)
		{
			cout << except.getErr() << endl;
		}
		string str, line_file;

		while (std::getline(file, str))
		{
				line_file.insert(line_file.size(), str);
				line_file.insert(line_file.size(), "\n");
			
		}
		int count = line_file.size();


		for (int i = 0; i < count; i++)
		{
			cout << line_file[i];
		}
		cout << endl;
		file.close();
	}


	void OutBINFileBin(string namebin)
	{
		fstream file_bin;
		file_bin.open(namebin, fstream::in | fstream::binary);
		try
		{
			if (!file_bin.is_open())
				throw Exception("File wasn't opened");
		}
		catch (Exception except)
		{
			cout << except.getErr() << endl;
		}

		cout << "FileBin.bin: " << endl;
		char str[300];
		int len;
		
		while (!(file_bin.eof()))
		{
			file_bin.read(str, 300);
		}

		file_bin.close();

		file_bin.open(namebin, fstream::in | fstream::binary);
		try
		{
			if (!file_bin.is_open())
				throw Exception("File wasn't opened");
		}
		catch (Exception except)
		{
			cout << except.getErr() << endl;
		}

		len = strlen(str) / 6;
		file_bin.seekp(0, ios::beg);
		
		char *s = new char[len];
		while (!(file_bin.eof()))
		{
			file_bin.read(s, len);
			cout << s << endl;
		}

		file_bin.close();

	}

	void InpFileBin(string namebin, int val)
	{

		fstream file_bin;
		file_bin.open(namebin, fstream::out | fstream::binary | fstream::app);
		try
		{
			if (!file_bin.is_open())
				throw Exception("File wasn't opened");
		}
		catch (Exception except)
		{
			cout << except.getErr() << endl;
		}
		Iterator obj = Iterator(Obj_head);

		while (obj.node->valume != val)
		{
			if (obj.node->next == nullptr)
			{
				cout << "Element aren't exist" << endl;
				break;
			}
			obj.node = obj.node->next;
		}
		char str[20];
		string sprop = "\n";
		char prop[2];
		strcpy_s(prop, sprop.c_str());
		int prop_len = strlen(prop);

		string s = std::to_string(obj.node->valume);
		strcpy_s(str, s.c_str());
		int len = strlen(str);
		file_bin.write(str, len);

		file_bin.write(prop, prop_len);

		strcpy_s(str, obj.node->FIO.c_str());
		len = strlen(str);
		file_bin.write(str, len);


		file_bin.write(prop, prop_len);


		s = std::to_string(obj.node->group_ID);
		strcpy_s(str, s.c_str());
		len = strlen(str);
		file_bin.write(str, len);

		file_bin.write(prop, prop_len);
		
		s = std::to_string(obj.node->mid_mark);
		strcpy_s(str, s.c_str());
		len = strlen(str);
		file_bin.write(str, len);

		file_bin.write(prop, prop_len);

		s = "~~~\n";
		strcpy_s(str, s.c_str());
		len = strlen(str);
		file_bin.write(str, len);

		file_bin.close();
	}


};
#endif
	



