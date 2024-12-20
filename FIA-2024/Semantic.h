#pragma once
#include "stdafx.h"

namespace SEM {
	void ParseForKeyWords(IT::IDTable table);
	void CheckReturns(LT::LexTable ltable);
	void CheckTypes(IT::IDTable itable, LT::LexTable ltable);
	void ProceedSemanticAnalysis(LT::LexTable ltable, IT::IDTable itable);
}