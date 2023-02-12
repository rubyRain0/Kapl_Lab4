#include "STACK.h"

STACK::STACK()
{
	top = nullptr;
}

bool STACK::Empty()
{
	return top == nullptr;
}

void STACK::Push(InfoList elem)
{
	TList p = new LIST;
	p->info = elem;
	p->next = top;
	top = p;
}

InfoList STACK::Pop()
{
	TList p = top;
	top = top->next;
	InfoList elem = p->info;
	p->next = nullptr;
	delete p;
	return elem;
}

InfoList STACK::Top()
{
	return top->info;
}

void STACK::View()
{
	TList p = top;
	while (p != nullptr) {
		std::cout << p->info;
		p = p->next;
	}
	std::cout << '\n';
}