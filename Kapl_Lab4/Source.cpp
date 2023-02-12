#include <iostream>
#include <fstream>
#include <Windows.h>
#include "STACK.h"
#include "Tree.h"

void Clear(Tree& t) {
	if (t) {
		Clear(t->left);
		Clear(t->right);
		delete t;
		t = nullptr;
	}
}

void Print(Tree t, int level) {
	if (t) {
		Print(t->right, level + 1);
		for (int i = 0; i <= level; ++i)
			std::cout << ' ';
		std::cout << t->info << '\n';
		Print(t->left, level + 1);
	}
}

Tree& copyTree(const Tree& t) {
	Tree tmp = new NODE(0);
	tmp->info = t->info;
	if (t->left)
		tmp->left = copyTree(t->left);
	if (t->right)
		tmp->right = copyTree(t->right);
	return tmp;
}

bool isOperator(char t)
{
	if (t != '+' && t != '-' && t != '*')
		return false;
	else return true;
}

char derivative(char t, char var)
{
	char res;
	if (t == var)
		res = '1';
	else if (!isOperator(t))
		res = '0';
	return res;
}

Tree Build_Formula(std::ifstream& file) {
	char c = file.get();
	Tree result = new NODE(' ');
	if (c >= '0' && c <= '9' || c >= 'x' && c <= 'z')
		result->info = c;
	else {
		// c = '(';
		result->left = Build_Formula(file);
		result->info = file.get();
		result->right = Build_Formula(file);
		c = file.get(); //')'
	}
	return result;
}

std::string print_to_string(const Tree& t) {
	std::string result = "";
	if (!t->left && !t->right)
		result += t->info;
	else
		result = '(' + print_to_string(t->left) + t->info + print_to_string(t->right) + ')';
	return result;
}

bool derivativeStack(Tree& root, char var) {
	STACK myStack;
	bool res = false;
	Tree t = root;
	while (t)
	{
		res = true;
		if (t->left && t->right)
		{
			if (t->info == '+' || t->info == '-')
			{ 
				myStack.Push(t->right);
				t = t->left;
			}
			else if (t->info == '*')
			{
				Tree tmp;
				tmp = copyTree(t);

				t->info = '+';
				Clear(t->left);
				t->left = copyTree(tmp);

				Clear(t->right);
				t->right = copyTree(tmp);

				myStack.Push(t->right->right);
				t = t->left->left;

				Clear(tmp);
			}

		}
		else
		{
			t->info = derivative(t->info, var);
			if (!myStack.Empty())
			{
				t = myStack.Top();
				myStack.Pop();
			}
			else
				t = nullptr;
		}
	}
	return res;
}

bool task4(Tree& root, Tree& T1, char var)
{
	bool result;
	result = derivativeStack(T1, var);
	return result;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::ifstream file("formula.txt");
	char var;
	file >> var;
	file.ignore();
	Tree root = Build_Formula(file);
	Tree T1 = copyTree(root);

	if (task4(root, T1, 'x'))
	{
		std::cout << "Starting Tree:\n" << print_to_string(root) << '\n';
		std::cout << "Derivative Tree: \n" << print_to_string(T1) << '\n';

		Clear(T1);
		Clear(root);
	}
	else std::cout << "Something went wrong...\n";

	std::cin.get();
	return 0;
}