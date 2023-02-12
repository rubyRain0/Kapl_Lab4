#pragma once
#include <iostream>
#include "Tree.h"

using InfoList = Tree;

struct LIST {
	InfoList info;
	LIST* next;
};

using TList = LIST*;

class STACK
{
	TList top;
public:
	STACK();
	bool Empty();
	void Push(InfoList elem);
	InfoList Pop();
	InfoList Top();
	void View();
};