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
				line_file.insert(line_file.size(), "\r\n");
			}
		}
		file.close();

		fstream file_rep;
		file_rep.open(nametxt, fstream::out | fstream::binary);
		file_rep.write(line_file.c_str(), line_file.size());
		file_rep.clear();
		file_rep.close();

		OutFile(nametxt);

	}

	void ShellForFiles(string namefile)
	{
		fstream file;
		file.open(namefile, fstream::in | fstream::out | fstream::binary);							// Open file
		try
		{
			if (!file.is_open())
				throw Exception("File wasn't opened");
		}
		catch (Exception except)
		{
			cout << except.getErr() << endl;
		}
		cout << "File was opened" <<endl;


		int size = 0;
		string str;
		string line = "~~~\r";
		cout << line.c_str() << "\t" << line.size() << endl;
		while (!file.eof())																			// Set size
		{
			std::getline(file, str);
			cout << str.c_str() << "\t" << str.size() <<  endl;
			if (strcmp(str.c_str(), line.c_str()) == 0)
				size++;
		}
		cout << "Size - " << size << endl;
		std::get(file, str);
		cout << "Test - " << str << endl;

		int i = 0;
		int mid = size;
		int end = mid;
		mid = mid / 2;
		while (mid > 0)
		{
			int first_line_start = 0;
			int first_line_end = 0;

		}

		str = get(file);




		int num_line_now = 0;
		string first_line, second_line, new_file;

		std::getline(file, first_line);
		cout << "first_line - " << first_line << endl;
		//first_line_start = 0;
		while (second_line != "~~~")
		{
			std::getline(file, second_line);
			//first_line_end++;

			if (!(num_line_now == 4)) {
				new_file.insert(new_file.size(), first_line);
				new_file.insert(new_file.size(), "\r\n");
			}
		}
		file.close();

	/*	fstream file_rep;
		file_rep.open(nametxt, fstream::out | fstream::binary);
		file_rep.write(line_file.c_str(), line_file.size());
		file_rep.clear();
		file_rep.close();*/
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
			fstream fileBin;
			fileBin.open(nametxt, fstream::in | fstream::binary);
			try
			{
				if (!fileBin.is_open())
					throw Exception("File wasn't opened");
			}
			catch (Exception except)
			{
				cout << except.getErr() << endl;
			}
			
			char ch_str[15];
			//ch_str = new char[15];
			fileBin.read(ch_str, 15);

			int count = 0;
			for (int index = 0; index < 15; index++)
			{
				if (ch_str[index] >= 97 && ch_str[index] <= 122 || ch_str[index] >= 65 && ch_str[index] <= 90)
					count++;
			}
			for (int index = 0; index < count; index++)
				cout << ch_str[index];
			cout << endl;
			fileBin.close();
		}


	void OutBINFileBin(string namebin)
		{
			fstream file_bin;
			file_bin.open(namebin, fstream::binary | fstream::out);
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
			Iterator obj = Iterator(Obj_head);
			char str[15];
			while (!file_bin.eof())
			{
				file_bin.read((char*)&obj.node->FIO, 15);
				cout << obj.node->group_ID << endl;
				cout << obj.node->mid_mark << endl;
				cout << obj.node->valume << endl;
				cout << "~~~" << endl;
				obj.node = obj.node->next;
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

			if (check(val) == true)
			{
				int size = 15;
				Iterator obj = Iterator(Obj_head);
				while (obj.node->valume != val)
					obj++;
				//file_bin << obj.node->FIO << "\n";
				//file_bin << obj.node->group_ID << "\n";
				//file_bin << obj.node->mid_mark << "\n";
				//file_bin << obj.node->valume << "\n";
				//file_bin << "~~~" << "\n";
				file_bin.write((char*) obj.node->FIO.c_str(), size * sizeof(Object));
				file_bin.write("\n", 3);

				file_bin.write((char*) obj.node->group_ID, size * sizeof(Object));
				file_bin.write("\n", 3);

			//	file_bin.write((char*) obj.node->mid_mark, size * sizeof(Object));
				file_bin.write("\n", 3);

				file_bin.write((char*) obj.node->valume, size * sizeof(Object));
				file_bin.write("\n", 3);
				file_bin.write("~~~", 3);
				file_bin.write("\n", 3);
			}
			else 
			{
				cout << "This valume aren't exist in your container" << endl;
			}

			file_bin.close();
		}

};
#endif
	



