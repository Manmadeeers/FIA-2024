#pragma once
#include "stdafx.h"
#define ID_MAXSIZE 5
#define IT_MAXSIZE 4096
#define INT_DEFAULT 0x00000000
#define STR_DEFAULT 0x00
#define NULL_INDEX 0xffffffff
#define STR_MAXSIZE 255

namespace IT {
	enum DATATYPES { INT = 1, CHR = 2, BOO = 3 };
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4 };
	struct Entry {
		int first_line_ID;
		int lex_link;
		char* id;
		DATATYPES IDDataType;
		IDTYPE IDType;
		union {
			char* vint;
			char  vchr;
			char* vbool;
		}value;
		char* scope;
	};

	struct IDTable {
		int count_literals;
		int maxsize;
		int size;
		Entry* table;
		Entry* dups;
		int count_dups;

	};
	IDTable Create(int size);
	void AddToIDTable(IDTable& idtable, Entry entry);
	Entry GetEntry(IDTable& idtable, int str_num);
	int IsId(IDTable& idtable, char id[ID_MAXSIZE]);
	bool checkLiterals(IDTable idtable, Entry literal);
	void DeleteIdTable(IDTable& idtable);
	void PrintTable(IDTable idtable);
	bool checkIDorFuncPresense(IDTable table, Entry id);
}
