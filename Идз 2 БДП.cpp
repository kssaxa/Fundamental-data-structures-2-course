#include <iostream> 

using namespace std;

int tabs = 0; //Для создания отступов
int kol_vo = 0;
//Кол-во отступов высчитывается по кол-ву рекурсивного вхождения при выводе в фукцию print 

//Структура ветки 
struct Branch

{
	int Data; //Поле данных 
	Branch* LeftBranch; //УКАЗАТЕЛИ на соседние веточки 
	Branch* RightBranch;
};

//Функция внесения данных 

void Add(int aData, Branch*& aBranch)

{

	//Если ветки не существует 

	if (!aBranch)

	{ //создадим ее и зададим в нее данные 
		aBranch = new Branch;
		aBranch->Data = aData;
		aBranch->LeftBranch = 0;
		aBranch->RightBranch = 0;
		return;

	}

	else //Иначе сверим вносимое 
		if (aBranch->Data < aData)
		{ //Если оно меньше того, что в этой ветке - добавим влево 
			Add(aData, aBranch->LeftBranch);
		}
		else
		{ //Иначе в ветку справа 
			Add(aData, aBranch->RightBranch);
		};

}

//Функция вывода дерева 
//печать
void print(Branch* aBranch)

{

	if (!aBranch)
		return; //Если ветки не существует - выходим. Выводить нечего 
	tabs += 5; //Иначе увеличим счетчик рекурсивно вызванных процедур 
	//Который будет считать нам отступы для красивого вывода 
	print(aBranch->LeftBranch); //Выведем ветку и ее подветки слева 
	for (int i = 0; i < tabs; i++)
		cout << " "; //Потом отступы 
	cout << aBranch->Data << endl; //Данные этой ветки 
	print(aBranch->RightBranch);//И ветки, что справа 
	tabs -= 5; //После уменьшим кол-во отступов 
	return;

}

int kol_ch(Branch*& aBranch)

{
	if (NULL == aBranch) return 0; //Если дерева нет, выходим 
	if (aBranch->Data % 2 == 0)
	{

		kol_vo++;

	}
	kol_ch(aBranch->LeftBranch); //Обошли левое поддерево 
	kol_ch(aBranch->RightBranch); //Обошли правое поддерево 
	return kol_vo;

}
void add_elem(int aData, Branch*& aBranch)

{

	if (!aBranch)

	{
		aBranch = new Branch;
		aBranch->Data = aData;
		aBranch->LeftBranch = 0;
		aBranch->RightBranch = 0;
		return;
	}

	else

	{

		if (aData > aBranch->Data) {
			add_elem(aData, aBranch->LeftBranch);
		}

		else if (aData < aBranch->Data) {
			add_elem(aData, aBranch->RightBranch);
		}

	}

}

/*void is_Empty(Branch*& aBranch)

{

	if (!aBranch)

	{
		cout << "Дерево пустое...";
	}

	else

	{
		cout << "Дерево не пустое...";
	}

}*/



//Очистка памяти
void FreeTree(Branch* aBranch)

{
	if (!aBranch) return;
	FreeTree(aBranch->LeftBranch);
	FreeTree(aBranch->RightBranch);
	delete aBranch;
	return;

}
void sravn(int data, Branch* aBranch1, Branch* aBranch2) {
	//для каждого дерева переменная хранящяя дату, их и сравниванием  решить вопрос с нулптр и датой

 }





// удаление
Branch* del_elem(Branch*& aBranch, int aData) {

	if (aBranch == NULL)
		return aBranch;
	if (aData == aBranch->Data) {
		Branch* tmp;
		if (aBranch->RightBranch == NULL)
			tmp = aBranch->LeftBranch;

		else {
			Branch* ptr = aBranch->RightBranch;

			if (ptr->LeftBranch == NULL) {
				ptr->LeftBranch = aBranch->LeftBranch;
				tmp = ptr;

			}
			else {
				Branch* pmin = ptr->LeftBranch;
				while (pmin->LeftBranch != NULL) {

					ptr = pmin;
					pmin = ptr->LeftBranch;

				}

				ptr->LeftBranch = pmin->RightBranch;
				pmin->LeftBranch = aBranch->LeftBranch;
				pmin->RightBranch = aBranch->RightBranch;
				tmp = pmin;
			}
		}
		delete aBranch;
		return tmp;
	}
	else if (aData > aBranch->Data)
		aBranch->LeftBranch = del_elem(aBranch->LeftBranch, aData);
	else
		aBranch->RightBranch = del_elem(aBranch->RightBranch, aData);
	return aBranch;
}

int main()

{

	setlocale(LC_ALL, "rus");
	Branch* Root = 0;
	int vel;
	int element;
	int k;
	cout << "Введите кол-во элементов для будущего дерева: ";
	cin >> vel;
	cout << endl;
	cout << "Проверим дерево на пустоту до его заполнения: " << endl;
	//is_Empty(Root);
	//cout << endl;
	for (int i = 0; i < vel; i++)

	{

		Add(rand() % 100, Root);

	}
	cout << "Проверим дерево на пустоту после его заполнения: " << endl;
	//is_Empty(Root);
	cout << endl;
	cout << "Вывод бинарного дерева: " << endl;
	print(Root);
	cout << endl;

	
	cout << "Добавим новый элемент в бинарное дерево:" << endl;
	cout << "Введите новый элемент: ";
	cin >> element;
	add_elem(element, Root);
	cout << "Вывод бинарного дерева: " << endl;
	print(Root);
	cout << endl;
	cout << "Удалим элемент из бинарного дерева:" << endl;
	cout << "Введите нэлемент: ";
	cin >> element;
	del_elem(Root, element);
	cout << "Вывод бинарного дерева: " << endl;
	print(Root);
	cout << endl;

	FreeTree(Root);
	cout << "Вся динамическая память очищена..." << endl;
	return 0;
}