#include <iostream>
#include <tuple>
using namespace std;

int tabs = 0; //Для создания отступов
int kol_vo = 0;
//Структура ветки 
struct Branch

{
	char bukva;
	int Data; //Поле данных 
	Branch* LeftBranch; //УКАЗАТЕЛИ на соседние ветки 
	Branch* RightBranch;
};

//Функция внесения данных 
void Add(Branch*& tree, char b, int elem) {
	Branch* tmp = new Branch();
	tmp->bukva = b;
	tmp->Data = elem;
	tmp->LeftBranch = nullptr;
	tmp->RightBranch = nullptr;

	if (tree == nullptr) {
		tree = tmp;
	}
	else {
		if (std::tie(tree->bukva, tree->Data) < std::tie(b, elem))
			Add(tree->RightBranch, b, elem);
		if (std::tie(tree->bukva, tree->Data) > std::tie(b, elem))
			Add(tree->LeftBranch, b, elem);
	}
}


//печать
void print(Branch* tree)
{
	if (!tree) return;
	tabs += 5;
	print(tree->RightBranch);
	for (int i = 0; i < tabs; i++) std::cout << " ";
	std::cout << tree->bukva << tree->Data << std::endl;
	print(tree->LeftBranch);
	tabs -= 5;
	return;
}

//поиск элемента
bool FindElem(Branch* tree, char b, int elem) {
	bool flag = false;
	if (tree != nullptr) {
		if (std::tie(tree->bukva, tree->Data) == (std::tie(b, elem)))
		{
			flag = true;
			return flag;
		}
		else if (std::tie(tree->bukva, tree->Data) > (std::tie(b, elem)))
		{
			return FindElem(tree->LeftBranch, b, elem);
		}
		else return FindElem(tree->RightBranch, b, elem);
	}
	else return flag;
}
//очистка памяти
void Del_al(Branch*& tree)
{
	if (tree == nullptr)
	{
		return;
	}

	Del_al(tree->LeftBranch);
	Del_al(tree->RightBranch);
	delete tree;
	tree = nullptr;
}
//сравнение
bool inorder(Branch* Branch1, Branch* Branch2)//сравнение деревьев
{
	while (Branch1 != nullptr && Branch2 != nullptr) {
		if (Branch1->Data != Branch2->Data)
			return false;
		if (Branch1 != nullptr and Branch2 != nullptr)
			return inorder(Branch1->LeftBranch, Branch2->LeftBranch) && inorder(Branch1->RightBranch, Branch2->RightBranch);
	}
}

// удаление
Branch* del_elem(Branch*& aBranch, char b, int aData) {

	if (aBranch == NULL)
		return aBranch;
	if ((std::tie(b, aData) == std::tie(aBranch->bukva, aBranch->Data)))
	{
		Branch* tmp;
		if (aBranch->LeftBranch == NULL)
			tmp = aBranch->RightBranch;
		
		if (aBranch->RightBranch == NULL)
			tmp = aBranch->LeftBranch;


		else {
			Branch* ptr = aBranch->LeftBranch;

			/*if (ptr->RightBranch == NULL) {
				ptr->RightBranch = aBranch->RightBranch;
				tmp = ptr;

			}*/
			//else {
				Branch* pmax = ptr->RightBranch;
				while (pmax->RightBranch != NULL) {

					ptr = pmax;
					pmax = ptr->RightBranch;

				}

				ptr->RightBranch = pmax->LeftBranch;
				pmax->RightBranch = aBranch->RightBranch;
				pmax->LeftBranch = aBranch->LeftBranch;
				tmp = pmax;
			//}
		}
		delete aBranch;
		aBranch = tmp;
		//return tmp;
	}
	else if (aData < aBranch->Data)
		aBranch->LeftBranch = del_elem(aBranch->LeftBranch, b, aData);
	else
		aBranch->RightBranch = del_elem(aBranch->RightBranch, b, aData);
	return aBranch;
}

int main()

{
	bool f = true;
	Branch* tree = nullptr;
	Branch* tree2 = nullptr;
	Add(tree, 'A', 30);
	Add(tree, 'A', 40);
	Add(tree, 'A', 35);
	Add(tree, 'A', 45);
	Add(tree, 'A', 45);
	Add(tree, 'A', 20);
	Add(tree, 'A', 25);
	Add(tree, 'A', 15);
	Add(tree, 'A', 10);
	Add(tree, 'A', 5);
	Add(tree, 'A', 39);
	Add(tree, 'A', 39);
	/*Add(tree, 'A', 39);
	Add(tree, 'A', 39);
	Add(tree, 'A', 39);*/
	print(tree);
	del_elem(tree, 'A', 45);
	del_elem(tree, 'A', 40);
	del_elem(tree, 'A', 39);
	del_elem(tree, 'A', 35);
	del_elem(tree, 'A', 30);
	//del_elem(tree, 'A', 20);
	cout << endl;
	cout << endl;
	//Del_al(tree);


	print(tree);
	Add(tree2, 'A', 8);
	Add(tree2, 'A', 9);
	Add(tree2, 'A', 5);
	Add(tree2, 'A', 1);
	Add(tree2, 'A', 11);
	Add(tree2, 'A', 10);
	Add(tree2, 'A', 6);
	Add(tree2, 'A', 7);
	Add(tree2, 'A', 12);
	Add(tree2, 'A', 4);
	Add(tree2, 'A', 39);

	cout << endl;
	cout << endl;
	//print(tree);
	cout << endl;
	cout << endl;
	//print(tree2);


	cout << endl;
	cout << endl;
	//f = FindElem(tree, 'A', 40);
	//f=inorder(tree, tree2);
	//cout << f;




	//print(tree);


}
