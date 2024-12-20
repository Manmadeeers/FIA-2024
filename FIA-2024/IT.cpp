#include "stdafx.h"


namespace IT {
	IDTable Create(int size) {
		if (size > IT_MAXSIZE || size < 0) {
			throw ERROR_THROW(68);
		}
		IDTable newIDTable;
		newIDTable.size = 0;
		newIDTable.table = new Entry[size];
		newIDTable.maxsize = ID_MAXSIZE;
		newIDTable.count_literals = 0;
		newIDTable.dups = new Entry[size];
		newIDTable.count_dups = 0;
		return newIDTable;
	}

	void AddToIDTable(IDTable& idtable, Entry entry) {
		idtable.table[idtable.size] = entry;
		idtable.size++;
	}

	Entry GetEntry(IDTable& idtable, int str_num) {
		if (str_num >= ID_MAXSIZE || str_num < 0) {
			throw ERROR_THROW(67);
		}
		Entry IDTableElem = idtable.table[str_num];
		return IDTableElem;
	}

	int IsId(IDTable& idtable, char id[ID_MAXSIZE]) {
		for (int i = 0; i < idtable.size; i++) {
			if (idtable.table[i].id == id) {
				return i;
			}
		}
		return NULL_INDEX;
	}

	bool checkLiterals(IDTable idtable, Entry literal) {

		for (int i = 0; i < idtable.size; i++) {
			Entry current = idtable.table[i];
			if (literal.IDDataType == INT && current.IDDataType == INT && current.IDType == IT::L) {
				if (literal.value.vint == current.value.vint) {
					return true;
				}
			}
			else if (literal.IDDataType == CHR && current.IDDataType == CHR && current.IDType == IT::L) {
				if (literal.value.vchr == current.value.vchr) {
					return true;
				}
			}

			else if (literal.IDDataType == BOO && current.IDDataType == BOO && current.IDType == IT::L) {
				int iterator = 0;
				bool equal = true;
				while (literal.value.vbool[iterator] != '\0') {
					if (literal.value.vbool[iterator] != current.value.vbool[iterator]) {
						equal = false;
						break;
					}
					iterator++;
				}
				if (equal) {
					return true;
				}
				else {
					continue;
				}
			}
		}
		return false;
	}

	void PrintTable(IDTable idtable) {
		cout << endl << endl;
		cout << "<-----Identifier table----->" << endl;
		cout << "Identifier data types: " << "1 - INT   2 - CHR   3 - BOO   4 - STR" << endl;
		cout << "Identifier types: " << "1-Variable   2-Function   3-Parametres   4-Literal(int, char, bool or str)" << endl << endl;


		cout << " ¹" << "\t\t" << "Identifier" << "\t\t" << "Data type" << "\t\t" << "Identifier type" << "\t\t" << "Scope" << endl;
		for (int i = 0; i < idtable.size; i++) {
			IT::Entry current = idtable.table[i];
			if (current.first_line_ID <= 9) {

				if (current.IDType == IT::L) {
					if (current.IDDataType == IT::INT) {
						cout << "0" << current.first_line_ID << '/' << current.lex_link << "\t\t" << current.id << "\t\t  " << current.IDDataType << "\t\t\t" << current.IDType << " ( " << current.value.vint << " )" << "\t\t\t" << current.scope << endl;
					}
					else if (current.IDDataType == IT::BOO) {
						cout << "0" << current.first_line_ID << '/' << current.lex_link << "\t\t" << current.id << "\t\t\t" << current.IDDataType << "\t\t\t" << current.IDType << " ( " << current.value.vbool << " )" << "\t\t" << current.scope << endl;
					}

					else {
						cout << "0" << current.first_line_ID << '/' << current.lex_link << "\t\t" << current.id << "\t\t\t" << current.IDDataType << "\t\t\t" << current.IDType << " ( " << current.value.vchr << " )" << "\t\t\t" << current.scope << endl;
					}

				}
				else {
					cout << "0" << current.first_line_ID << '/' << current.lex_link << "\t\t" << current.id << "\t\t\t" << current.IDDataType << "\t\t\t" << current.IDType << "\t\t\t" << current.scope << endl;
				}
			}
			else {
				if (current.IDType == IT::L) {
					if (current.IDDataType == IT::INT) {
						cout << current.first_line_ID << '/' << current.lex_link << "\t\t" << current.id << "\t\t\t" << current.IDDataType << "\t\t\t" << current.IDType << " ( " << current.value.vint << " )" << "\t\t\t" << current.scope << endl;
					}
					else if (current.IDDataType == IT::BOO) {
						cout << current.first_line_ID << '/' << current.lex_link << "\t\t" << current.id << "\t\t\t" << current.IDDataType << "\t\t\t" << current.IDType << "( " << current.value.vbool << " )" << "\t\t" << current.scope << endl;
					}

					else {
						cout << current.first_line_ID << '/' << current.lex_link << "\t\t" << current.id << "\t\t\t" << current.IDDataType << "\t\t\t" << current.IDType << " ( " << current.value.vchr << " )" << "\t\t\t" << current.scope << endl;
					}
				}
				else {
					cout << current.first_line_ID << '/' << current.lex_link << "\t\t" << current.id << "\t\t\t" << current.IDDataType << "\t\t\t" << current.IDType << "\t\t\t" << current.scope << endl;
				}
			}

		}

		cout << endl << "DUPS: " << endl;
		for (int i = 0; i < idtable.count_dups; i++) {
			cout << idtable.dups[i].id << "-->" << idtable.dups[i].first_line_ID << "-->" << idtable.dups[i].scope << "-->" << idtable.dups[i].IDDataType << ' ' << idtable.dups[i].IDType << ' ' << idtable.dups[i].lex_link << endl;
		}
		cout << endl << endl;
	}

	bool checkIDorFuncPresense(IDTable table, Entry id) {
		for (int i = 0; i < table.size; i++) {
			Entry current = table.table[i];
			if (id.IDType == IT::F) {
				if (current.IDType == IT::F) {
					if (strcmp(id.id, current.id) == 0) {
						return true;
					}
				}

			}
			else if (id.IDType == IT::V) {
				if (current.IDType == IT::V || current.IDType == IT::P) {
					if (current.scope == id.scope) {
						if (strcmp(id.id, current.id) == 0) {
							return true;
						}
					}
				}
			}
		}
		return false;
	}

	void DeleteIdTable(IDTable& idtable) {

		delete[] idtable.table;
		delete[]idtable.dups;
	}

};