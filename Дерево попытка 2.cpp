

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<tuple>

int tabs = 0;
int kol_vo = 0;

struct node
{
	std::string data;
	int index;
	node* next;
};

struct crown
{
	node* head;
};

struct tree
{
	crown* crown;
	tree* left;
	tree* right;
};

void PrintList(crown* list)
{
	node* carrent;
	if (list->head != nullptr)
	{
		carrent = list->head;
		while (carrent != nullptr)
		{
			std::cout << "(" << carrent->index << ")" << carrent->data << " "<<"-> ";
			carrent = carrent->next;
		}
		std::cout << std::endl;
	}
}

void Add_in_list(std::string val, int num, crown*& list)
{
	node* temp;
	node* carrent = new node;
	carrent->data = val;
	carrent->index = num;
	carrent->next = nullptr;
	if (list == nullptr)
	{
		list = new crown;
		list->head = new node;
		list->head->next = nullptr;
		list->head = carrent;
	}
	else
	{ 
		temp = list->head;
		while (temp->next != nullptr) {
			temp = temp->next;
		}
		temp->next = carrent;
		/*temp = list->head;
		if ((list->head->index > num) && (list->head->index != num))
		{
			carrent->next = list->head;
			list->head = carrent;
		}
		else
		{
			while ((temp->next != nullptr) && (temp->index < num))
			{
				temp = temp->next;
			}
			if ((temp->index > num) && (temp->index != num))
			{
				
				carrent->next = temp;
				
			}
			else if ((temp->index < num) && (temp->index != num))
			{
				temp->next = carrent;
				carrent->next = nullptr;
				
			}
		}*/
	}
}
void Add_in_tree(std::string val, int num, tree*& branch)
{
	if (!branch)
	{
		branch = new tree;
		branch->crown = new crown;
		branch->crown = nullptr;
		Add_in_list(val, num, branch->crown);
		branch->left = 0;
		branch->right = 0;
	}
	else
		if (branch->crown->head->data != val)
		{
			if (branch->crown->head->data > val)
			{
				Add_in_tree(val, num, branch->left);
			}
			else
			{
				Add_in_tree(val, num, branch->right);
			}
		}
		else
			Add_in_list(val, num, branch->crown);
}
void Delcrown(int num, crown*& list)
{
	node* carrent;
	node* elem;
	node* prev = nullptr;
	carrent = list->head;
	if (list->head != nullptr)
	{
		if (list->head->index == num)
		{
			elem = carrent;
		
			list->head = list->head->next;
			delete(elem);
		}
		else
		{
			while ((carrent->index != num) && (carrent != nullptr))
			{
				prev = carrent;
				carrent = carrent->next;
			}
			if (carrent)
			{
			
				prev->next = carrent->next;
				elem = carrent;
				delete(elem);
			}
		}
	}
	else
	{
		list->head = nullptr;
	}
}
tree* deleteNode(std::string val, int num, tree*& branch)
{
	if (branch == nullptr)
		return branch;
	if (branch->crown->head->data == val)
	{
		if (branch->crown->head->next == nullptr)
		{
			tree* tmp;
			if (branch->right == nullptr)
				tmp = branch->left;
			else
			{
				tree* ptr = branch->right;
				if (ptr->left == nullptr)
				{
					ptr->left = branch->left;
					tmp = ptr;
				}
				else
				{
					tree* pmin = ptr->left;
					while (pmin->left != nullptr)
					{
						ptr = pmin;
						pmin = ptr->left;
					}
					ptr->left = pmin->right;
					pmin->left = branch->left;
					pmin->right = branch->right;
					tmp = pmin;
				}
			}
			delete branch;
			return tmp;
		}
		else
			Delcrown(num, branch->crown);
	}
	else
		if (branch->crown->head->data > val)
			branch->left = deleteNode(val, num, branch->left);
		else
			branch->right = deleteNode(val, num, branch->right);
	return branch;
}
bool searchList(std::string val, crown* list)
{
	node* carrent = list->head;
	while (carrent != nullptr)
	{
		if (carrent->data == val)
			return true;
		else
			return false;
	}
}
bool search(std::string val, tree* branch)
{
	if (branch != nullptr)
	{
		if (searchList(val, branch->crown)) {
			return true;
			//std::cout << "Найден" << branch->crown << std::endl;
		}
		if (branch->crown->head->data > val)
			return search(val, branch->left);
		else
			return search(val, branch->right);
	}
	else {
		return false;
		//std::cout << "Не найден";
	}
}
void print(tree* branch)
{
	if (!branch)
		return;
	tabs += 5;
	print(branch->right);
	for (int i = 0; i < tabs; i++)
		std::cout << " ";
	PrintList(branch->crown);
	print(branch->left);
	tabs -= 5;
	return;
}
int main() {
	bool f = true;
	tree* tree1 = nullptr;
	tree* tree2 = nullptr;
	Add_in_tree("F", 3, tree1);
	Add_in_tree("O", 4, tree1);
	Add_in_tree("B", 4, tree1);
	Add_in_tree("C", 5, tree1);
	Add_in_tree("G", 6, tree1);
	Add_in_tree("Y", 7, tree1);
	Add_in_tree("R", 8, tree1);
	Add_in_tree("L", 9, tree1);
	Add_in_tree("P", 10, tree1);
	Add_in_tree("Q", 11, tree1);
	Add_in_tree("A", 12, tree1);
	Add_in_tree("B", 1, tree1);
	Add_in_tree("B", 2, tree1);
	print(tree1);
	std::cout << std::endl;
	std::cout << std::endl;
	search("E", tree1);
	std::cout << search("E", tree1) << std::endl;
	deleteNode("G", 6, tree1);
	deleteNode("B", 4, tree1);

	print(tree1);
	return 0;
}