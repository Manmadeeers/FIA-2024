#pragma once
#define LEN 50
#include "stdafx.h"

namespace POL {

	bool PolishNotation(int lextable_pos, LT::LexTable& lextable, IT::IDTable& idtable);
	void findN(LT::LexTable& lextable, IT::IDTable& idtable);
}
