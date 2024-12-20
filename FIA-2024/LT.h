#include "stdafx.h"
#define LEX_RIGHT_BRACE '}'
#define LEX_LEFTHESIS '('
#define LEX_RIGHTESIS ')'
#define LEX_MATH 'v'
#define LEX_FUNCTION 'f'
#define LEX_LIB_FUNC1 'S'
#define LEX_LIB_FUNC2 'C'
#define LEX_CREATE 'c'
#define LEX_DATATYPE 't'
#define LEX_MOVE_RIGHT 'R'
#define LEX_MOV_LEFT 'L'
#define LEX_MAIN 'm'
#define LEX_LOOP 'w'
#define LEX_TERN 'T'
#define LEX_IDENTIFIER 'i'
#define LEX_IS '='
#define LEX_RETURN 'r'
#define LEX_UNDEFINED 'U'
#define LEX_LOOP_EXIT_CONDITION '!'
#define LEX_GREATER '>'
#define LEX_SMALLER '<'
#define LEX_EQUALS 'e'
#define LEX_LITERAL 'l'
#define LEX_WIRTE 'p'
#define LEX_WRITELINE 'P'
#define LT_MAXSIZE 4096


namespace LT {
    struct Entry
    {
        char lexem;
        int src_str_num;
        int index;
    };

    struct LexTable {
        int maxsize;
        int size;
        Entry* table;
    };
    LexTable Create(int size);
    void AddToLexTable(LexTable& LexTable, Entry entry);
    Entry GetEntry(LexTable& LexTable, int str_num);
    void DeleteLexTable(LexTable& LexTable);
    void PrintTable(LexTable table);
};
