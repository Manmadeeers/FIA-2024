#pragma once
#include "stdafx.h"

namespace GNR {

	void WriteASMHeader(LT::LexTable ltable, IT::IDTable itable, OUT::Out& file);
	void WriteConst(LT::LexTable ltable, IT::IDTable itable, OUT::Out& file);
	void WriteData(LT::LexTable ltable, IT::IDTable itable, OUT::Out& file);
	void WriteCode(LT::LexTable ltable, IT::IDTable itable, OUT::Out& file);
	void GenToASM(LT::LexTable ltable, IT::IDTable itable, OUT::Out& file);
}