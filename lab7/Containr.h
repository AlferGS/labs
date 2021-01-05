#ifndef CONTAINR_H
#define CONTAINR_H

#include <iostream>
#include <locale>

using namespace std;

template <typename T>

class Container
{
private:

	class Object;
	friend class Object;
												//class Object
	class Object
	{
	private:

		string name;
		int ID, mass;
		T valume;
		Object* next;


	public:

		friend class Container<T>;
		friend class Iterator;

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

		void setName()
		{
			do {
				if (strlen(name.c_str()) > 0 && strlen(name.c_str()) < 3)
					cout << "Your name are short." << endl;

				cout << "Input name - ";
				cin.clear();
				cin >> name;

			} while (strlen(name.c_str()) < 3);
		}
		
		void setID(){
			string str;
			cout << "Enter ID - ";
			cin.clear();
			cin >> str;
			ID = CheckInt(str);
		}

		void setMass()
		{
			string str;
			cout << "Enter mass - ";
			cin.clear();
			cin >> str;
			mass = CheckInt(str);
		}

		void setValume()
		{
			cout << "Enter T valume - ";
			cin.clear();
			cin >> valume;
		}



		void getName()
		{
			cout << "Name - " << name << endl;
		}

		void getID()
		{
			cout << "Id - " << ID << endl;
		}

		void getMass()
		{
			cout << "Mass - " << mass << endl;
		}

		void getValume()
		{
			cout << "Valume - " << valume << endl;
		}

		
												//Constructors
		Object()
		{
			setName();
			setID();
			setMass();
			setValume();
		}
		Object(T V) : valume(V)
		{
			setName();
			setID();
			setMass();
		}
		Object(string N, int I, int M, T V) :name(N), ID(I), mass(M), valume(V)
		{
		}
		~Object()
		{
		}
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

			cerr << except.getErr();
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
			if (Obj_head == Obj_tail)
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
				hd.node->getName();
				hd.node->getID();
				hd.node->getMass();
				hd.node->getValume();
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
						int Itmp;

						Stmp = left->name;
						left->name = right->name;
						right->name = Stmp;

						Itmp = left->ID;
						left->ID = right->ID;
						right->ID = Itmp;

						Itmp = left->mass;
						left->mass = right->mass;
						right->mass = Itmp;

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
							int Itmp;

							Stmp = left->name;
							left->name = right->name;
							right->name = Stmp;

							Itmp = left->ID;
							left->ID = right->ID;
							right->ID = Itmp;

							Itmp = left->mass;
							left->mass = right->mass;
							right->mass = Itmp;

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

};
#endif
	//void Shell()
	//{
	//	try
	//	{
	//		if (Obj_head == Obj_tail)
	//			throw Exception("tried to sort an empty list\n");

	//		//T temp = 0;
	//		Object* templ = Obj_head;
	//		int i = 0;
	//		int mid = size();
	//		int end = mid;
	//		mid = mid / 2;
	//		while (mid > 0)
	//		{
	//			Object* cur = Obj_head;
	//			Object* last = Obj_head;

	//			Object* cur1 = cur;
	//			Object* last1 = Obj_head;
	//			for (i = 0; i < mid-1; i++)
	//			{
	//				last = last->next;
	//			}
	//			last1 = last;
	//			last = last->next;
	//			for (i = 0; i < end - mid; i++)
	//			{
	//				int j = i;
	//				while (j >= 0 && cur->valume > last->valume)
	//				{
	//					if (i != 0)
	//					{
	//						cur1->next = last;
	//						last1->next = cur;

	//						Object* curr = cur;

	//						templ->next = cur->next;
	//						curr = curr->next;
	//						cur->next = last->next;
	//						last->next = curr;
	//					}
	//					if (i == 0)
	//					{

	//						last1->next = cur;
	//						cur1 = cur1->next;

	//						templ->next = cur->next;

	//						cur->next = last->next;

	//						last->next = cur1;

	//						Obj_head = last;
	//					}
	//					if (i == end - mid - 1) { Obj_tail = cur; }

	//					for (Iterator hd = Iterator(Obj_head); hd != Iter_tail; hd++)
	//					{
	//						hd.node->getName();
	//						hd.node->getID();
	//						hd.node->getMass();
	//						hd.node->getValume();
	//					}

	//					j--;
	//					cout << endl;
	//				}
	//				cur = cur->next;
	//				last = last->next;
	//				if (i != 0) {
	//					cur1 = cur1->next;
	//					last1 = last1->next;
	//				}
	//			}
	//			mid = mid / 2;

	//			if (mid == 0)
	//			{
	//				mid = 1;
	//				cur = Obj_head;
	//				last = Obj_head;
	//				
	//				cur1 = cur;
	//				for (i = 0; i < mid-1; i++)
	//				{
	//					last = last->next;
	//				}
	//				last1 = last;
	//				last = last->next;
	//				for (i = 0; i < end - mid; i++)
	//				{
	//					int j = i;
	//					while (j >= 0 && cur->valume > last->valume)
	//					{
	//						if (i != 0)
	//						{
	//							cur1->next = last;
	//							last1->next = cur;

	//							templ->next = cur->next;
	//							cur->next = last->next;
	//							last->next = templ->next;
	//						}
	//						if (i == 0)
	//						{
	//							last1->next = cur;

	//							templ->next = cur->next;
	//							cur->next = last->next;
	//							last->next = templ->next;
	//							Obj_head = last;
	//						}
	//						if (i == end - mid - 1) { Obj_tail = cur; }
	//						
	//						for (Iterator hd = Iterator(Obj_head); hd != Iter_tail; hd++)
	//						{
	//							hd.node->getName();
	//							hd.node->getID();
	//							hd.node->getMass();
	//							hd.node->getValume();
	//						}

	//						j--;
	//						cout << endl;
	//					}
	//					cur = cur->next;
	//					last = last->next;

	//					if (i != 0) {
	//						cur1 = cur1->next;
	//						last1 = last1->next;
	//					}
	//				}
	//				mid = mid / 2;
	//			}
	//		}
	//	}
	//	catch (Exception except)
	//	{
	//		cerr << except.getErr() << endl;
	//	}

	//}