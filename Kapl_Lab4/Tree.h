#pragma once

using TInfo = char;

struct NODE {
	TInfo info;
	NODE* left, * right;
	int count = 1;
	NODE() {}
	NODE(TInfo info, NODE* left = nullptr, NODE* right = nullptr) :info(info), left(left), right(right) {}
	~NODE() {
		left = nullptr;
		right = nullptr;
	}
};

using Tree = NODE*;