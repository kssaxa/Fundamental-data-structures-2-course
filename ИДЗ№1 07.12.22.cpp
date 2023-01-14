#include <iostream>
using namespace std;
struct Node {
	int data;
	Node* next;
};

//Добавление в конец
void addNode(struct Node*& head, int n) {
	Node* nd = new Node;

	nd->data = n;
	nd->next = nullptr;

	if (head == nullptr)
		head = nd;
	else
	{
		Node* current = head;
		while (current->next != nullptr)
			current = current->next;
		current->next = nd;
	}
}


//Поиск заданного
int poisk(struct Node*& head, int n) {
	int count = 0;
	Node* poisk = head;
	while (poisk != nullptr) {
		if (poisk->data == n)
		{
			count++;
		}
		poisk = poisk->next;
	}
	return count;
}



// Очищение списка ?
//head->next != nullptr

void deletelist(Node*& head) {
	if (head != nullptr) {
		Node* del = head->next;
		while (del != head)
		{
			Node* del2 = del;
			del = del->next;
			delete (del2);
		}
	}
	head = nullptr;
}


//Печать списка
void print(Node* head)
{
	Node* print = head;
	if (print == nullptr) {
		cout << "\nСписок пуcтой\n";
	}
	else {
		while (print->next != nullptr) {
			cout << print->data << " <-> ";
			print = print->next;
		}
		cout << print->data;
	}
	cout << endl;
}

//удаление после каждого вхождения
void deleted(struct Node* head, int n) {
	Node* del = head;
	Node* delnext;
	if (del != nullptr) {
		while (head != nullptr && head->next != nullptr) {
			if (head->data == n) {
				Node* todelete = head->next;
				head->next = todelete->next;
				delete(todelete);
				/*if (head->next->next == nullptr) {
					delete (head->next);
				}
				else {
					delnext = head->next->next;
					delete (head->next);
					head->next = delnext;
				}*/
			}
			head = head->next;
		}
	}
}


//Функция пересечения списков

void pereseshenie(struct Node* head, struct Node* head2, struct Node*& head3)
{
	while (head != nullptr)
	{
		Node* prov1 = head2;
		while (prov1 != nullptr)
		{
			if (head->data == prov1->data)

			{

				addNode(head3, prov1->data);
				prov1 = nullptr;//выход из цикла
			}
			else
			{
				prov1 = prov1->next;
			}
		}

		if (prov1 == nullptr)
		{
			head = head->next;//шаг
			prov1 = head2;
		}

	}

}
int main() {
	setlocale(LC_ALL, "Russian");
	int n1, n, q, vibor, elem, znach;
	struct Node* newHead;
	struct Node* head = nullptr;
	struct Node* head2 = nullptr;
	struct Node* head3 = nullptr;
	//print(head);
	//deletelist(head);

	//pereseshenie(head, head2, head3);
	for (int i = 0; i < 3; i++) {
		int temp = 1;//rand() % 10 + 1;
		cout << temp << endl;
		addNode(head, temp);
	}
	for (int i = 0; i < 5; i++) {
		int temp = 1;//rand() % 10 + 1;
		cout << temp << endl;
		addNode(head2, temp);
	}
	pereseshenie(head, head2, head3);
	//deleted(head, 1);
	print(head3);
	

	/*cout << "Сколько элементов в списке " << endl;
	cin >> q;
	cout << "Введите элементы списка" << endl;
	cin >> n1;
	head = new Node();
	head->data = n1;
	head->next = nullptr;
	while (q > 1)
	{

		cin >> n;

		addNode(head, n);
		q--;

	}
	print(head);
	do {
		cout << "Выберите действие:1 - добавить элемент в конец 2 - удаление после вхождения 3 - пересечение 4 - поиск значения 0 - выход" << endl;
		cin >> vibor;

		if (vibor == 1)
		{
			cout << "Введите добавляемый элемент" << endl;
			cin >> elem;
			addNode(head, elem);
			cout << "Новый список" << endl;
			print(head);
		}
		if (vibor == 2)
		{
			cout << "Введите после какого значения удалить" << endl;
			cin >> elem;
			deleted(head, elem);
			cout << "Новый список" << endl;
			print(head);
		}
		if (vibor == 3)
		{
			cout << "Введите второй список" << endl;
			cout << "Сколько элементов в списке " << endl;
			cin >> q;
			cout << "Введите элементы списка" << endl;
			cin >> n1;
			head2 = new Node();
			head2->data = n1;
			head2->next = nullptr;
			while (q > 1)
			{
				cin >> n;
				addNode(head2, n);
				q--;

			}
			cout << "Исходный список №1:" << endl;
			print(head);
			cout << "Исходный список №2:" << endl;
			print(head2);

			cout << "Пересечение списков"<<endl;
			pereseshenie(head, head2,head3);
			print(head3);

		}
		if (vibor == 4)
		{
			cout << "Введите значение" << endl;
			cin >> znach;
			poisk(head, znach);

		}

	} while (vibor != 0);*/
}


