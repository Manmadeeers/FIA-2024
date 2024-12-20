#include "stdafx.h"


namespace LT {
	LexTable Create(int size) {
		if (size<0 || size>LT_MAXSIZE) {
			throw ERROR_THROW(60);
		}
		LexTable newLexTable;
		newLexTable.maxsize = LT_MAXSIZE;
		newLexTable.size = 0;
		newLexTable.table = new Entry[size];
		return newLexTable;
	}

	void AddToLexTable(LexTable& LexTable, Entry entry) {
		if (LexTable.size >= LT_MAXSIZE) {
			throw ERROR_THROW(60);
		}
		LexTable.table[LexTable.size] = entry;
		LexTable.size++;
	}

	Entry GetEntry(LexTable& LexTable, int str_num) {
		if (str_num >= LT_MAXSIZE || str_num < 0) {
			throw ERROR_THROW(61);
		}
		Entry LexTableElem = LexTable.table[str_num];
		return LexTableElem;
	}

	void PrintTable(LexTable table) {
		cout << endl << endl << "<-----Lexem table----->" << endl;
		int store_prev = 0;
		cout << "0" << store_prev << " ";
		for (int i = 0; i < table.size; i++) {
			LT::Entry current = LT::GetEntry(table, i);
			if (current.src_str_num != store_prev) {
				cout << endl;
				if (current.src_str_num <= 9) {
					cout << '0' << current.src_str_num << ' ';
				}
				else {
					cout << current.src_str_num << ' ';
				}
			}
			cout << current.lexem << " [" << current.index << "] ";
			store_prev = current.src_str_num;

		}
		cout << endl << endl;
	}

	void DeleteLexTable(LexTable& LexTable) {

		delete[] LexTable.table;

	}


};