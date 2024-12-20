#include "stdafx.h"
#define out *file.stream

namespace GNR {

    // Генерация заголовка ASM
    void WriteASMHeader(OUT::Out& file) {
        out << ".586\n";
        out << "\t.model flat, stdcall\n";
        out << "\tincludelib libucrt.lib\n";
        out << "\tincludelib kernel32.lib\n";
        out << "\tincludelib ..\\Debug\\STDLIB.lib\n";
        out << "\tExitProcess PROTO : DWORD \n\n";

        // Подключение библиотечных функций
        out << "\tEXTRN get_date: proc\n";
        out << "\tEXTRN get_time: proc\n";
        out << "\tEXTRN Out_int: proc\n";
        out << "\tEXTRN Out_char: proc\n";
        out << "\t EXTRN Out_bool: proc\n";
        out << "\n.stack 4096\n";
    }

    // Генерация блока данных (переменные)
    void WriteData(LT::LexTable ltable, IT::IDTable itable, OUT::Out& file) {
        out << ".data\n";
        for (int i = 0; i < itable.size; i++) {
            if (itable.table[i].IDType == IT::V) {
                out << "\t" << itable.table[i].id;
                if (itable.table[i].IDDataType == IT::INT) {
                    out << " DD 0\n";  // Инициализация для целых чисел
                }
                else if (itable.table[i].IDDataType == IT::CHR) {
                    out << " DD 0\n";  // Инициализация для символов
                }
                else if (itable.table[i].IDDataType == IT::BOO) {
                    out << " DD 0\n";  // Инициализация для логических значений
                }
            }
        }
    }

    // Генерация констант
    void WriteConst(IT::IDTable itable, OUT::Out& file) {
        out << ".const\n";
        for (int i = 0; i < itable.size; i++) {
            if (itable.table[i].IDType == IT::L) {  // Литералы
                out << "\t" << itable.table[i].id << ' ';
                if (itable.table[i].IDDataType == IT::INT) {
                    out << "DWORD " << itable.table[i].value.vint << "\n";
                }
                else if (itable.table[i].IDDataType == IT::CHR) {
                    out << "DWORD '" << itable.table[i].value.vchr << "'\n";
                }
                else if (itable.table[i].IDDataType == IT::BOO) {
                    out << "DWORD " << (strcmp(itable.table[i].value.vbool, "true") == 0 ? "1" : "0") << "\n";
                }
            }
        }
    }

    // Генерация кода программы
    void WriteCode(LT::LexTable ltable, IT::IDTable itable, OUT::Out& file) {
        out << ".code\n";
        stack<char*>parm_stk;
        int count_loops = 0;
        bool in_loop = false;
        int count_additions = 0;
        // Обработка функций
        for (int i = 0; i < ltable.size; i++) {
            LT::Entry current = ltable.table[i];

            if (current.lexem == LEX_FUNCTION) {

                char* func_name = nullptr;
                for (int j = 0; j < itable.size; j++) {
                    if (itable.table[j].lex_link == current.index + 1) {
                        func_name = itable.table[j].id;
                        out << func_name << "_F PROC ";
                        break;
                    }
                }
                i++;
                while (ltable.table[i].lexem != '{') {
                    if (ltable.table[i].lexem == ',') {
                        out << ", ";
                    }
                    for (int j = 0; j < itable.size; j++) {
                        if (itable.table[j].lex_link == ltable.table[i].index && itable.table[j].IDType == IT::P) {
                            if (itable.table[j].IDDataType == IT::INT) {
                                out << itable.table[j].id << " : DWORD ";
                                parm_stk.push(itable.table[j].id);
                            }
                            else {
                                out << itable.table[j].id << " : DWORD ";
                                parm_stk.push(itable.table[j].id);
                            }
                        }
                    }


                    i++;
                }
                out << "\n";
                /* out << "\tpush ebp\n";
                 out << "\tmov ebp, esp\n";*/
                while (!parm_stk.empty()) {
                    out << "\tpush " << parm_stk.top() << "\n";
                    parm_stk.pop();
                }
                i++;
                // Тело функции
                char* store_acc_name = (char*)"";
                while (ltable.table[i].lexem != '}') {
                    if (ltable.table[i].lexem == LEX_IDENTIFIER && ltable.table[i + 1].lexem == LEX_IS) {
                        for (int j = 0; j < itable.size; j++) {
                            if (itable.table[j].lex_link == ltable.table[i].index) {
                                out << "\tpush " << itable.table[j].id << "\n";
                                store_acc_name = itable.table[j].id;
                                break;
                            }
                            if (itable.dups[j].lex_link == ltable.table[i].index) {
                                out << "\tpush " << itable.dups[j].id << "\n";
                                store_acc_name = itable.dups[j].id;
                                break;
                            }
                        }
                        i++;

                    }

                    else if ((ltable.table[i].lexem == LEX_IDENTIFIER || ltable.table[i].lexem == LEX_LITERAL) && ltable.table[i - 1].lexem == LEX_IS) {
                        out << "\tmov eax, ";
                        for (int j = 0; j < itable.size; j++) {
                            if (itable.table[j].lex_link == ltable.table[i].index) {
                                out << itable.table[j].id << "\n";
                                break;
                            }
                            if (itable.dups[j].lex_link == ltable.table[i].index) {
                                out << itable.dups[j].id << "\n";
                                break;
                            }
                        }
                        i++;
                        while (ltable.table[i].lexem != ';') {
                            if ((ltable.table[i].lexem == LEX_IDENTIFIER || ltable.table[i].lexem == LEX_LITERAL) && ltable.table[i - 1].lexem == '+') {
                                out << "\tadd eax, ";
                                for (int j = 0; j < itable.size; j++) {
                                    if (itable.table[j].lex_link == ltable.table[i].index) {
                                        out << itable.table[j].id;
                                        break;
                                    }
                                    if (itable.dups[j].lex_link == ltable.table[i].index) {
                                        out << itable.dups[j].id;
                                        break;
                                    }
                                }
                                out << "\n";
                            }
                            else if ((ltable.table[i].lexem == LEX_IDENTIFIER || ltable.table[i].lexem == LEX_LITERAL) && ltable.table[i - 1].lexem == '-') {
                                out << "\tsub eax, ";
                                for (int j = 0; j < itable.size; j++) {
                                    if (itable.table[j].lex_link == ltable.table[i].index) {
                                        out << itable.table[j].id;
                                        break;
                                    }
                                    if (itable.dups[j].lex_link == ltable.table[i].index) {
                                        out << itable.dups[j].id;
                                        break;
                                    }
                                }
                                out << "\n";
                            }
                            else if ((ltable.table[i].lexem == LEX_IDENTIFIER || ltable.table[i].lexem == LEX_LITERAL) && ltable.table[i - 1].lexem == '*') {
                                out << "\tmov edx ";
                                for (int j = 0; j < itable.size; j++) {
                                    if (itable.table[j].lex_link == ltable.table[i].index) {
                                        out << itable.table[j].id;
                                        break;
                                    }
                                    if (itable.dups[j].lex_link == ltable.table[i].index) {
                                        out << itable.dups[j].id;
                                        break;
                                    }
                                }
                                out << "\n";
                                out << "\tmul edx\n";
                            }
                            else if ((ltable.table[i].lexem == LEX_IDENTIFIER || ltable.table[i].lexem == LEX_LITERAL) && ltable.table[i - 1].lexem == '/') {
                                out << "\tmov edx, ";
                                for (int j = 0; j < itable.size; j++) {
                                    if (itable.table[j].lex_link == ltable.table[i].index) {
                                        out << itable.table[j].id;
                                        break;
                                    }
                                    if (itable.dups[j].lex_link == ltable.table[i].index) {
                                        out << itable.dups[j].id;
                                        break;
                                    }
                                }
                                out << "\n";
                                out << "\tdiv edx\n";
                            }
                            i++;
                        }
                        out << "\tmov [" << store_acc_name << "], eax\n";
                        out << "\tpop eax\n";
                    }
                    else if (ltable.table[i].lexem == LEX_RETURN) {
                        for (int j = 0; j < itable.size; j++) {
                            if (itable.table[j].lex_link == ltable.table[i + 1].index) {
                                out << "\tmov eax, [" << itable.table[j].id << "]\n";
                                break;
                            }
                            if (itable.dups[j].lex_link == ltable.table[i + 1].index) {
                                out << "\tmov eax, [" << itable.dups[j].id << "]\n";
                                break;
                            }
                        }
                        // out << "\tpop eax\n";
                        out << "\tret\n";
                        i++;
                        break;
                    }
                    //
                    else if (ltable.table[i].lexem == LEX_WRITELINE) {
                        out << "\tmov ecx, ";
                        for (int j = 0; j < itable.size; j++) {
                            if (itable.table[j].lex_link == ltable.table[i + 1].index) {
                                out << itable.table[j].id << "\n";
                                //out << "\tcall \n";
                                if (itable.table[j].IDDataType == IT::INT) {
                                    out << "\tcall Out_int\n";
                                }
                                else if (itable.table[j].IDDataType == IT::BOO) {
                                    out << "\tcall Out_bool\n";
                                }
                                else {
                                    out << "\tcall Out_char\n";
                                }
                                break;
                            }
                            if (itable.dups[j].lex_link == ltable.table[i + 1].index) {
                                out << itable.dups[j].id << "\n";
                                // out << "\tcall \n";
                                if (itable.dups[j].IDDataType == IT::INT) {
                                    out << "\tcall Out_int\n";
                                }
                                else if (itable.dups[j].IDDataType == IT::BOO) {
                                    out << "\tcall Out_bool\n";
                                }
                                else {
                                    out << "\tcall Out_char\n";
                                }
                                break;
                            }
                        }

                    }
                    else if (ltable.table[i].lexem == LEX_LOOP) {
                        while (ltable.table[i].lexem != LEX_LOOP_EXIT_CONDITION) {
                            i++;
                        }
                        char* loop_end = (char*)"";
                        char* loop_iter = (char*)"";
                        for (int j = 0; j < itable.size; j++) {
                            if (itable.table[j].lex_link == ltable.table[i + 1].index) {
                                loop_end = itable.table[j].id;
                                break;
                            }
                            if (itable.dups[j].lex_link == ltable.table[i + 1].index) {
                                loop_end = itable.dups[j].id;
                                break;
                            }
                        }
                        for (int j = 0; j < itable.size; j++) {
                            if (itable.table[j].lex_link == ltable.table[i - 1].index) {
                                loop_iter = itable.table[j].id;
                                break;
                            }
                            if (itable.dups[j].lex_link == ltable.table[i - 1].index) {
                                loop_iter = itable.table[j].id;
                                break;
                            }
                        }
                        out << "\tmov ecx, [" << loop_iter << "]\n";
                        out << "\tmov edx, [" << loop_end << "]\n";
                        out << "loop_" << count_loops << ":\n";
                        i += 3;
                        out << "\tcmp ecx, edx\n";
                        out << "\tjmp loop_" << count_loops << "_End\n";
                        ;                        while (ltable.table[i].lexem != ']') {
                            if ((ltable.table[i].lexem == LEX_IDENTIFIER || ltable.table[i].lexem == LEX_LITERAL) && ltable.table[i - 1].lexem == LEX_IS) {
                                out << "\tmov eax, ";
                                for (int j = 0; j < itable.size; j++) {
                                    if (itable.table[j].lex_link == ltable.table[i].index) {
                                        out << itable.table[j].id << "\n";
                                        break;
                                    }
                                    if (itable.dups[j].lex_link == ltable.table[i].index) {
                                        out << itable.dups[j].id << "\n";
                                        break;
                                    }
                                }
                                i++;
                                while (ltable.table[i].lexem != ';') {
                                    if ((ltable.table[i].lexem == LEX_IDENTIFIER || ltable.table[i].lexem == LEX_LITERAL) && ltable.table[i - 1].lexem == '+') {
                                        out << "\tadd eax, ";
                                        for (int j = 0; j < itable.size; j++) {
                                            if (itable.table[j].lex_link == ltable.table[i].index) {
                                                out << itable.table[j].id;
                                                break;
                                            }
                                            if (itable.dups[j].lex_link == ltable.table[i].index) {
                                                out << itable.dups[j].id;
                                                break;
                                            }
                                        }
                                        out << "\n";
                                    }
                                    else if ((ltable.table[i].lexem == LEX_IDENTIFIER || ltable.table[i].lexem == LEX_LITERAL) && ltable.table[i - 1].lexem == '-') {
                                        out << "\tsub eax, ";
                                        for (int j = 0; j < itable.size; j++) {
                                            if (itable.table[j].lex_link == ltable.table[i].index) {
                                                out << itable.table[j].id;
                                                break;
                                            }
                                            if (itable.dups[j].lex_link == ltable.table[i].index) {
                                                out << itable.dups[j].id;
                                                break;
                                            }
                                        }
                                        out << "\n";
                                    }
                                    else if ((ltable.table[i].lexem == LEX_IDENTIFIER || ltable.table[i].lexem == LEX_LITERAL) && ltable.table[i - 1].lexem == '*') {
                                        out << "\tmov edx ";
                                        for (int j = 0; j < itable.size; j++) {
                                            if (itable.table[j].lex_link == ltable.table[i].index) {
                                                out << itable.table[j].id;
                                                break;
                                            }
                                            if (itable.dups[j].lex_link == ltable.table[i].index) {
                                                out << itable.dups[j].id;
                                                break;
                                            }
                                        }
                                        out << "\n";
                                        out << "\tmul edx\n";
                                    }
                                    else if ((ltable.table[i].lexem == LEX_IDENTIFIER || ltable.table[i].lexem == LEX_LITERAL) && ltable.table[i - 1].lexem == '/') {
                                        out << "\tmov edx, ";
                                        for (int j = 0; j < itable.size; j++) {
                                            if (itable.table[j].lex_link == ltable.table[i].index) {
                                                out << itable.table[j].id;
                                                break;
                                            }
                                            if (itable.dups[j].lex_link == ltable.table[i].index) {
                                                out << itable.dups[j].id;
                                                break;
                                            }
                                        }
                                        out << "\n";
                                        out << "\tdiv edx\n";
                                    }
                                    i++;
                                }
                                /*   out << "\tmov [" << store_acc_name << "], eax\n";
                                   out << "\tpop eax\n";*/
                            }

                            i++;

                        }
                        out << "loop " << "loop_" << count_loops << "\n";
                        out << "loop_" << count_loops << "_End:\n";

                    }
                    //else if(ltable.table[i].lexem==)
                    i++;
                }
                out << func_name << "_F ENDP\n";
            }
            else if (current.lexem == LEX_MAIN) {
                out << "main PROC\n";
                char* store_acc_name = (char*)"";
                char* loop_end = (char*)"";
                char* loop_iter = (char*)"";
                while (ltable.table[i].lexem != '}') {
                    if (ltable.table[i].lexem == LEX_IDENTIFIER && ltable.table[i + 1].lexem == LEX_IS) {

                        for (int j = 0; j < itable.size; j++) {
                            if (itable.table[j].lex_link == ltable.table[i].index) {
                                // out << "\tpop " << itable.table[j].id << "\n";
                                store_acc_name = itable.table[j].id;
                                break;
                            }
                            if (itable.dups[j].lex_link == ltable.table[i].index) {
                                // out << "\tpop " << itable.dups[j].id << "\n";
                                store_acc_name = itable.dups[j].id;
                                break;
                            }
                        }
                        i++;

                    }
                    else if (ltable.table[i].lexem == LEX_IDENTIFIER && ltable.table[i - 1].lexem == LEX_IS && ltable.table[i + 1].lexem == '(') {
                        char* called_func = (char*)"";
                        for (int j = 0; j < itable.size; j++) {
                            if (itable.dups[j].lex_link == ltable.table[i].index) {
                                called_func = itable.dups[j].id;
                                break;
                            }
                        }
                        i++;
                        while (ltable.table[i].lexem != ')') {
                            for (int j = 0; j < itable.size; j++) {
                                if (itable.table[j].lex_link == ltable.table[i].index) {
                                    out << "\tpush " << itable.table[j].id << "\n";
                                    break;
                                }
                                if (itable.dups[j].lex_link == ltable.table[i].index) {
                                    out << "\tpush " << itable.dups[j].id << "\n";
                                    break;
                                }
                            }

                            i++;
                        }
                        out << "\tcall " << called_func << "_F\n";
                        continue;
                    }
                    //
                    else if ((ltable.table[i].lexem == LEX_IDENTIFIER || ltable.table[i].lexem == LEX_LITERAL) && ltable.table[i - 1].lexem == LEX_IS) {
                        char* id = (char*)"";
                        for (int j = 0; j < itable.size; j++) {
                            if (itable.table[j].lex_link == ltable.table[i].index) {
                                id = itable.table[j].id;
                                break;
                            }
                            if (itable.dups[j].lex_link == ltable.table[i].index) {
                                id = itable.dups[j].id;
                                break;
                            }
                        }
                        if (strcmp(loop_iter, id) == 0) {
                            while (ltable.table[i].lexem != ';') {
                                i++;
                            }
                            char* num_to_iter = (char*)"";
                            for (int j = 0; j < itable.size; j++) {
                                if (itable.table[j].lex_link == ltable.table[i - 1].index) {
                                    num_to_iter = itable.table[j].id;
                                    break;
                                }
                                if (itable.dups[j].lex_link == ltable.table[i - 1].index) {
                                    num_to_iter = itable.dups[j].id;
                                    break;

                                }
                            }
                            out << "\tadd ebx, " << num_to_iter << "\n";
                            continue;
                        }
                        out << "\tmov eax, ";
                        for (int j = 0; j < itable.size; j++) {
                            if (itable.table[j].lex_link == ltable.table[i].index) {
                                out << itable.table[j].id << "\n";
                                break;
                            }
                            if (itable.dups[j].lex_link == ltable.table[i].index) {
                                out << itable.dups[j].id << "\n";
                                break;
                            }
                        }
                        i++;
                        while (ltable.table[i].lexem != ';') {
                            if ((ltable.table[i].lexem == LEX_IDENTIFIER || ltable.table[i].lexem == LEX_LITERAL) && ltable.table[i - 1].lexem == '+') {
                                out << "\tadd eax, ";
                                for (int j = 0; j < itable.size; j++) {
                                    if (itable.table[j].lex_link == ltable.table[i].index) {
                                        out << itable.table[j].id;
                                        break;
                                    }
                                    if (itable.dups[j].lex_link == ltable.table[i].index) {
                                        out << itable.dups[j].id;
                                        break;
                                    }
                                }
                                out << "\n\tmov ebx, eax\n";
                            }
                            else if ((ltable.table[i].lexem == LEX_IDENTIFIER || ltable.table[i].lexem == LEX_LITERAL) && ltable.table[i - 1].lexem == '-') {
                                out << "\tsub eax, ";
                                for (int j = 0; j < itable.size; j++) {
                                    if (itable.table[j].lex_link == ltable.table[i].index) {
                                        out << itable.table[j].id;
                                        break;
                                    }
                                    if (itable.dups[j].lex_link == ltable.table[i].index) {
                                        out << itable.dups[j].id;
                                        break;
                                    }
                                }
                                out << "\n\tmov eax, ebx\n";
                            }
                            else if ((ltable.table[i].lexem == LEX_IDENTIFIER || ltable.table[i].lexem == LEX_LITERAL) && ltable.table[i - 1].lexem == '*') {
                                out << "\tmov edx ";
                                for (int j = 0; j < itable.size; j++) {
                                    if (itable.table[j].lex_link == ltable.table[i].index) {
                                        out << itable.table[j].id;
                                        break;
                                    }
                                    if (itable.dups[j].lex_link == ltable.table[i].index) {
                                        out << itable.dups[j].id;
                                        break;
                                    }
                                }
                                out << "\n";
                                out << "\tmul edx\n";
                            }
                            else if ((ltable.table[i].lexem == LEX_IDENTIFIER || ltable.table[i].lexem == LEX_LITERAL) && ltable.table[i - 1].lexem == '/') {
                                out << "\tmov edx, ";
                                for (int j = 0; j < itable.size; j++) {
                                    if (itable.table[j].lex_link == ltable.table[i].index) {
                                        if (strcmp(itable.table[j].value.vint, 0) == 0) {
                                            throw ERROR_THROW_IN(3, ltable.table[i].src_str_num, 0, (unsigned char*)"");
                                        }
                                        out << itable.table[j].id;
                                        break;
                                    }
                                    if (itable.dups[j].lex_link == ltable.table[i].index) {
                                        out << itable.dups[j].id;
                                        break;
                                    }
                                }
                                out << "\n";
                                out << "\tdiv edx\n";
                            }
                            
                            else if (ltable.table[i].lexem == LEX_MOV_LEFT) {
                                for (int j = 0; j < itable.size; j++) {
                                    if (itable.table[j].lex_link == ltable.table[i].index-1) {
                                        out << "\tmov eax, " << itable.table[j].id << "\n";
                                        break;
                                    }
                                    if (itable.dups[j].lex_link == ltable.table[i].index-1) {
                                        out << "\tmov eax, " << itable.dups[j].id << "\n";
                                        break;
                                    }
                                }
                                for (int j = 0; j < itable.size; j++) {
                                    if (itable.table[j].lex_link == ltable.table[i].index+1) {
                                        out << "\tshl eax, " << itable.table[j].id << "\n";
                                        break;
                                    }
                                }
                            }
                            i++;
                        }
                        out << "\tmov [" << store_acc_name << "], eax\n";
                       // out << "\tpop eax\n";
                    }
                    else if (ltable.table[i].lexem == LEX_IDENTIFIER&&ltable.table[i+1].lexem==LEX_MOVE_RIGHT) {
                        for (int j = 0; j < itable.size; j++) {
                            if (itable.table[j].lex_link == ltable.table[i].index) {
                                out << "\tmov eax, " << itable.table[j].id << "\n";
                                break;
                            }
                            if (itable.dups[j].lex_link == ltable.table[i].index) {
                                out << "\tmov eax, " << itable.dups[j].id << "\n";
                                break;
                            }
                        }
                        for (int j = 0; j < itable.size; j++) {
                            if (itable.table[j].lex_link == ltable.table[i + 2].index) {
                                out << "\tsar eax, " << itable.table[j].value.vint<< "\n";
                                break;
                            }   
                        }
                    }
                    else if (ltable.table[i].lexem == LEX_IDENTIFIER && ltable.table[i + 1].lexem == LEX_MOV_LEFT) {
                        for (int j = 0; j < itable.size; j++) {
                            if (itable.table[j].lex_link == ltable.table[i].index) {
                                out << "\tmov eax, " << itable.table[j].id << "\n";
                                break;
                            }
                            if (itable.dups[j].lex_link == ltable.table[i].index) { 
                                out << "\tmov eax, " << itable.dups[j].id << "\n";
                                break;
                            }
                        }
                        for (int j = 0; j < itable.size; j++) {
                            if (itable.table[j].lex_link == ltable.table[i + 2].index) {
                                out << "\tshl eax, " << itable.table[j].value.vint << "\n";
                                break;
                            }
                        }
                    }
                    else if (ltable.table[i].lexem == LEX_RETURN) {
                        for (int j = 0; j < itable.size; j++) {
                            if (itable.table[j].lex_link == ltable.table[i + 1].index) {
                                out << "\tmov eax, [" << itable.table[j].id << "]\n";
                                break;
                            }
                            if (itable.dups[j].lex_link == ltable.table[i + 1].index) {
                                out << "\tmov eax, [" << itable.dups[j].id << "]\n";
                                break;
                            }
                        }
                        // out << "\tpop eax\n";
                        out << "\tret\n";
                        i++;
                        break;
                    }
                    //
                    else if (ltable.table[i].lexem == LEX_WRITELINE) {
                        //out << "\tmov ecx, ";
                        bool write_iter = false;
                        for (int j = 0; j < itable.size; j++) {
                            if (itable.dups[j].lex_link == ltable.table[i + 1].index) {
                                if (strcmp(loop_iter, itable.dups[j].id) == 0) {
                                    write_iter = true;  
                                }
                            }

                        }
                        if (write_iter == true) {
                            out << "\tpush ebx\n";
                            out << "\tcall Out_int\n";
                        }

                        if (write_iter == false) {
                            for (int j = 0; j < itable.size; j++) {
                                if (itable.table[j].lex_link == ltable.table[i + 1].index) {
                                    //out << itable.table[j].id << "\n";
                                    //out << "\tcall printf\n";
                                    out << "\tpush eax\n";
                                    if (itable.table[j].IDDataType == IT::INT) {
                                        out << "\tcall Out_int\n";
                                    }
                                    else if (itable.table[j].IDDataType == IT::BOO) {
                                        out << "\tcall Out_bool\n";
                                    }
                                    else {
                                        out << "\tcall Out_char\n";
                                    }
                                    break;
                                }
                                if (itable.dups[j].lex_link == ltable.table[i + 1].index) {
                                    //out << itable.dups[j].id << "\n";
                                    //out << "\tcall printf\n";
                                    out << "\tpush eax\n";
                                    if (itable.dups[j].IDDataType == IT::INT) {
                                        out << "\tcall Out_int\n";
                                    }
                                    else if (itable.dups[j].IDDataType == IT::BOO) {
                                        out << "\tcall Out_bool\n";
                                    }
                                    else {
                                        out << "\tcall Out_char\n";
                                    }
                                    break;
                                }
                            }
                        }


                    }
                    else if (ltable.table[i].lexem == LEX_LOOP) {
                        in_loop = true;
                        while (ltable.table[i].lexem != LEX_LOOP_EXIT_CONDITION) {
                            i++;
                        }

                        for (int j = 0; j < itable.size; j++) {
                            if (itable.table[j].lex_link == ltable.table[i - 1].index) {
                                loop_iter = itable.table[j].id;
                            }
                            if (itable.dups[j].lex_link == ltable.table[i - 1].index) {
                                loop_iter = itable.dups[j].id;
                            }
                            if (itable.table[j].lex_link == ltable.table[i + 1].index) {
                                loop_end = itable.table[j].id;

                            }
                            if (itable.dups[j].lex_link == ltable.table[i + 1].index) {
                                loop_end = itable.dups[j].id;
                            }
                        }
                        // out << "\tmov ebx, " << loop_end << "\n";
                        out << "\tmov ebx, " << loop_iter << "\n";
                        out << "loop_" << count_loops << ":\n";
                        out << "\tcmp ebx, " << loop_end << "\n";
                        out << "\tje loop_" << count_loops << "_End\n";



                    }
                    else if (ltable.table[i].lexem == ']') {
                        out << "loop " << "loop_" << count_loops << "\n";
                        out << "loop_" << count_loops << "_End:\n";
                        in_loop = false;
                    }
                    else if (ltable.table[i].lexem == LEX_LIB_FUNC1) {
                        i++;
                        while (ltable.table[i].lexem != ';') {
                            for (int j = 0; j < itable.size; j++) {
                                if (itable.table[j].lex_link == ltable.table[i].index && ltable.table[i].lexem != LEX_LIB_FUNC1) {
                                    out << "\tpush " << itable.table[j].id << "\n";
                                }
                                if (itable.dups[j].lex_link == ltable.table[i].index && ltable.table[i].lexem != LEX_LIB_FUNC1) {
                                    out << "\tpush " << itable.dups[j].id << "\n";
                                }
                            }
                            i++;
                        }
                        out << "\tcall get_date\n";
                    }
                    else if (ltable.table[i].lexem == LEX_LIB_FUNC2) {
                        i++;
                        while (ltable.table[i].lexem != ';') {
                            for (int j = 0; j < itable.size; j++) {
                                if (itable.table[j].lex_link == ltable.table[i].index && ltable.table[i].lexem != LEX_LIB_FUNC1) {
                                    out << "\tpush " << itable.table[j].id << "\n";
                                }
                                if (itable.dups[j].lex_link == ltable.table[i].index && ltable.table[i].lexem != LEX_LIB_FUNC1) {
                                    out << "\tpush " << itable.dups[j].id << "\n";
                                }
                            }
                            i++;
                        }
                        out << "\tcall get_time\n";
                    }
                    /*   else if(ltable.table[i])*/

                    i++;
                }
            }

        }

        out << "\tmov eax, 0\n";
        out << "\tcall ExitProcess\n";
        out << "main ENDP\n";

    }


    // Главная функция генерации ASM
    void GenToASM(LT::LexTable ltable, IT::IDTable itable, OUT::Out& file) {
        WriteASMHeader(file);
        out << ";<---------- Константы ---------->\n";
        WriteConst(itable, file);
        out << ";<---------- Данные ---------->\n";
        WriteData(ltable, itable, file);
        out << ";<---------- Код ---------->\n";
        WriteCode(ltable, itable, file);
        out << "END main\n";
    }
}
