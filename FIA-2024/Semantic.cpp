#include "stdafx.h"

namespace SEM {

	void ParseForKeyWords(IT::IDTable table) {
		char* words[] = { (char*)"return", (char*)"main", (char*)"declare", (char*)"create", (char*)"func", (char*)"int", (char*)"char", (char*)"bool", (char*)"write", (char*)"writeline", (char*)"if", (char*)"while" };
		int words_size = 12;
		for (int i = 0; i < table.size; i++) {
			for (int j = 0; j < words_size; j++) {
				if (_stricmp(words[j], table.table[i].id) == 0) {
					throw ERROR_THROW_IN(700, table.table[i].first_line_ID, 0, (unsigned char*)table.table[i].id);
				}
				if (_stricmp(words[j], table.dups[i].id) == 0) {
					throw ERROR_THROW_IN(700, table.dups[i].first_line_ID, 0, (unsigned char*)table.table[i].id);
				}
			}
		}
	}
	void CheckTypes(IT::IDTable itable, LT::LexTable ltable) {


		for (int i = 0; i < ltable.size; i++) {
			LT::Entry current = ltable.table[i];
			//проверка на совпадение всех типов данных после равно
			if (current.lexem == LEX_IS) {
				int eq_position = current.index;
				IT::DATATYPES src_type = IT::BOO;
				IT::IDTYPE next_type = IT::F;
				IT::DATATYPES next_dtype = IT::BOO;
				char* name = (char*)"";
				//получаем тип данных идентификатора слева от равно
				for (int j = 0; j < itable.size; j++) {
					if (itable.table[j].lex_link == eq_position - 1) {
						src_type = itable.table[j].IDDataType;

					}
					if (itable.dups[j].lex_link == eq_position - 1) {
						src_type = itable.dups[j].IDDataType;

					}
					if (itable.table[j].lex_link == eq_position + 1) {
						next_type = itable.table[j].IDType;
						next_dtype = itable.table[j].IDDataType;

					}
					if (itable.dups[j].lex_link == eq_position + 1) {
						next_type = itable.dups[j].IDType;
						next_dtype = itable.dups[j].IDDataType;
						name = itable.dups[j].id;
					}
				}
				if (ltable.table[eq_position + 1].lexem == LEX_LIB_FUNC1 || ltable.table[eq_position + 1].lexem == LEX_LIB_FUNC2) {
					continue;
				}
				if (next_dtype != src_type) {
					throw ERROR_THROW_IN(708, current.src_str_num, 0, (unsigned char*)"AAA");
				}
				//смотрим, одиночное ли присваивание(нет ли мат. операций)
				if (next_type != IT::F) {
					i += 2;
					IT::DATATYPES ltype = IT::INT;
					IT::DATATYPES rtype = IT::INT;
					while (ltable.table[i].lexem != ';') {
						if (ltable.table[i].lexem == '+' || ltable.table[i].lexem == '-' || ltable.table[i].lexem == '/' || ltable.table[i].lexem == '*' || ltable.table[i].lexem == '%') {
							if (src_type != IT::INT) {
								throw ERROR_THROW_IN(708, current.src_str_num, 0, (unsigned char*)"A");
							}
							int counter = 0;
							for (int j = 0; j < itable.size; j++) {
								if (itable.table[j].lex_link == ltable.table[i].index + 1) {
									rtype = itable.table[j].IDDataType;
									counter++;
								}
								if (itable.dups[j].lex_link == ltable.table[i].index + 1) {
									rtype = itable.dups[j].IDDataType;
									counter++;
								}
								if (itable.table[j].lex_link == ltable.table[i].index - 1) {
									ltype = itable.table[j].IDDataType;
									counter++;
								}
								if (itable.dups[j].lex_link == ltable.table[i].index - 1) {
									ltype = itable.dups[j].IDDataType;
									counter++;
								}
								if (counter == 4) {
									break;
								}
							}
							if (ltype != rtype) {
								throw ERROR_THROW_IN(708, current.src_str_num, 0, (unsigned char*)"AA");
							}
						}
						i++;
					}
					continue;
				}
				//проверка на передачу в функцию именно того кол-ва параметров, которое может принять эта функция
				//else {
					/*if (ltable.table[i + 1].lexem != LEX_LIB_FUNC1 && ltable.table[i + 1].lexem != LEX_LIB_FUNC2) {
						int params_counter = 0;
						int real_params_counter = 0;
						for (int j = 0; j < itable.size; j++) {
							if (itable.table[j].scope == name && itable.table[j].IDType == IT::P) {
								params_counter++;
							}
						}

						while (ltable.table[i].lexem != ';') {
							if (ltable.table[i].lexem == ',') {
								real_params_counter++;
							}
							i++;
						}
						if (params_counter != real_params_counter) {
							throw ERROR_THROW_IN(711, current.src_str_num, 0, (unsigned char*)"");
						}
					}
					*/
					//}
			}

			//проверка на корректность возвращаемого функцией значения
			else if (current.lexem == LEX_RETURN) {
				for (int j = 0; j < itable.size; j++) {
					if (itable.table[j].first_line_ID == current.src_str_num && itable.table[j].lex_link == current.index + 1) {
						if (strcmp(itable.table[j].scope, "Main") == 0) {
							if (itable.table[j].IDType != IT::L || itable.table[j].IDDataType != IT::INT) {
								throw ERROR_THROW_IN(709, current.src_str_num, 0, (unsigned char*)"");
							}
						}
						else if (strcmp(itable.table[j].scope, "Main") != 0) {
							char* current_scope = itable.table[j].scope;
							IT::DATATYPES f_type = IT::BOO;
							for (int k = 0; k < itable.size; k++) {
								if (strcmp(current_scope, itable.table[k].scope)) {
									f_type = itable.table[k].IDDataType;
									break;
								}
							}
							if (itable.table[j].IDDataType != f_type) {
								throw ERROR_THROW_IN(710, current.src_str_num, 0, (unsigned char*)"");
							}
						}

					}
				}
				for (int j = 0; j < itable.size; j++) {
					if (itable.dups[j].first_line_ID == current.src_str_num && itable.dups[j].lex_link == current.index + 1) {
						char* current_scope = itable.dups[j].scope;
						IT::DATATYPES f_type = IT::BOO;
						for (int f = 0; f < itable.size; f++) {
							if (strcmp(current_scope, itable.table[f].id)) {
								f_type = itable.table[f].IDDataType;
								break;
							}
						}
						if (itable.dups[j].IDDataType != f_type) {
							throw ERROR_THROW_IN(710, current.src_str_num, 0, (unsigned char*)"");
						}
					}
				}

			}
			//проверка типов данных операций больше и меньше
			else if (current.lexem == LEX_GREATER || current.lexem == LEX_SMALLER) {
				IT::DATATYPES l_type;
				IT::DATATYPES r_type;
				for (int j = 0; j < itable.size; j++) {
					if (itable.dups[j].lex_link == current.index - 1) {
						l_type = itable.dups[j].IDDataType;
					}
					if (itable.table[j].lex_link == current.index - 1) {
						l_type = itable.table[j].IDDataType;
					}
					if (itable.table[j].lex_link == current.index + 1) {
						r_type = itable.table[j].IDDataType;
					}
					if (itable.dups[j].lex_link == current.index + 1) {
						r_type = itable.dups[j].IDDataType;
					}
				}
				if (l_type != r_type) {
					throw ERROR_THROW_IN(712, current.src_str_num, 0, (unsigned char*)"");
				}

			}
			//проверка типов для операции сравнения
			else if (current.lexem == LEX_EQUALS) {
				IT::DATATYPES l_type;
				IT::DATATYPES r_type;
				for (int j = 0; j < itable.size; j++) {
					if (itable.dups[j].lex_link == current.index - 1) {
						l_type = itable.dups[j].IDDataType;
					}
					if (itable.table[j].lex_link == current.index - 1) {
						l_type = itable.table[j].IDDataType;
					}
					if (itable.table[j].lex_link == current.index + 1) {
						r_type = itable.table[j].IDDataType;
					}
					if (itable.dups[j].lex_link == current.index + 1) {
						r_type = itable.dups[j].IDDataType;
					}
				}
				if (l_type != r_type) {
					throw ERROR_THROW_IN(713, current.src_str_num, 0, (unsigned char*)"");
				}
			}
			//проверка на соответствие типов данных итератора и условия выхода из цикла
			else if (current.lexem == LEX_LOOP_EXIT_CONDITION) {
				IT::DATATYPES l_type;
				IT::DATATYPES r_type;
				for (int j = 0; j < itable.size; j++) {
					if (itable.table[j].lex_link == current.index - 1) {
						l_type = itable.table[j].IDDataType;
					}
					if (itable.table[j].lex_link == current.index + 1) {
						r_type = itable.table[j].IDDataType;
					}
					if (itable.dups[j].lex_link == current.index - 1) {
						l_type = itable.dups[j].IDDataType;
					}
					if (itable.dups[j].lex_link == current.index + 1) {
						r_type = itable.dups[j].IDDataType;
					}
				}
				if (l_type != r_type) {
					throw ERROR_THROW_IN(714, current.src_str_num, 0, (unsigned char*)"");
				}
			}

		}
		//проверяем ошибки возврата значения. Нельзя вернуть значение дажды
	}
	void CheckReturns(LT::LexTable ltable) {
		int store_prev_return_str = -1;
		for (int j = 0; j < ltable.size; j++) {
			if (ltable.table[j].lexem == LEX_RETURN) {
				if (ltable.table[j + 3].lexem != '}' && ltable.table[j + 3].lexem != ']') {
					throw ERROR_THROW_IN(715, ltable.table[j].src_str_num, 0, (unsigned char*)"");
				}

			}
		}
	}

	void ProceedSemanticAnalysis(LT::LexTable ltable, IT::IDTable itable) {

		CheckTypes(itable, ltable);
		//ParseForKeyWords(itable);
		CheckReturns(ltable);
		cout << endl << "<-------------------------------------------------->" << endl;
		cout << endl << "Семантика: Семантический анализ выполнен без ошибок" << endl << endl;
	}
}