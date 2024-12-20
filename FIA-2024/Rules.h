#pragma once
#include "GRB.h"

#define GRB_ERROR_SERIES 600
#define NS(n) GRB::Rule::Chain::N(n)
#define TS(n) GRB::Rule::Chain::T(n)
#define ISNS(n)  GRB::Rule::Chain::isN(n)

namespace GRB
{
    Greibach greiibach(NS('S'), TS('$'),        // начальный символ, или строка (дно стека)
        8,                      // количество правил
        Rule(NS('S'), GRB_ERROR_SERIES + 0,      //Нотация программы
            5,    // S ->  m{NrE;}; | tfi(F){NrE;};S |  m{NrE;};S |  tfi(F){NrE;}; | i{NrE;}
            Rule::Chain(7, TS('m'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}')),
            Rule::Chain(13, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S')),
            Rule::Chain(13, TS('t'), TS('f'), TS('i'), TS('('), NS('I'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S')),
            Rule::Chain(8, TS('m'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S')),
            Rule::Chain(12, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'))
            //Rule::Chain(12, TS('t'), TS('f'), TS('i'), TS('('), NS('I'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'))
        ),
        Rule(NS('N'), GRB_ERROR_SERIES + 1,      //Идентификаторы и использование ключевых слов, а также пунктуация
            34,
            // N ->  cti; | rE; | i = E; | ctfi(F); | cti;N | rE;N | i=E;N | ctfi(F);N | pE; | pE;N| PE; | PE;N
            Rule::Chain(4, TS('c'), TS('t'), TS('i'), TS(';')),
            Rule::Chain(5, TS('c'), TS('t'), TS('i'), TS(';'), NS('N')),
            Rule::Chain(6, TS('c'), TS('t'), TS('i'), TS('='), NS('E'), TS(';')),
            Rule::Chain(7, TS('c'), TS('t'), TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
            Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
            Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),

            Rule::Chain(9, TS('c'), TS('t'), TS('i'), TS('='), TS('S'), TS('('), NS('W'), TS(')'), TS(';')),
            Rule::Chain(10, TS('c'), TS('t'), TS('i'), TS('='), TS('S'), TS('('), NS('W'), TS(')'), TS(';'), NS('N')),
            Rule::Chain(9, TS('c'), TS('t'), TS('i'), TS('='), TS('C'), TS('('), NS('W'), TS(')'), TS(';')),
            Rule::Chain(10, TS('c'), TS('t'), TS('i'), TS('='), TS('C'), TS('('), NS('W'), TS(')'), TS(';'), NS('N')),
            Rule::Chain(7, TS('i'), TS('='), TS('S'), TS('('), NS('W'), TS(')'), TS(';')),
            Rule::Chain(8, TS('i'), TS('='), TS('S'), TS('('), NS('W'), TS(')'), TS(';'), NS('N')),
            Rule::Chain(7, TS('i'), TS('='), TS('C'), TS('('), NS('W'), TS(')'), TS(';')),
            Rule::Chain(8, TS('i'), TS('='), TS('C'), TS('('), NS('W'), TS(')'), TS(';'), NS('N')),
           /* Rule::Chain(3, TS('i'), NS('M'), TS(';')),
            Rule::Chain(4, TS('i'), NS('M'), TS(';'), NS('N')),*/
            Rule::Chain(4, TS('i'), TS('R'), TS('l'), TS(';')),
            Rule::Chain(5, TS('i'), TS('R'), TS('l'), TS(';'),NS('N')),
            Rule::Chain(4, TS('i'), TS('L'), TS('l'), TS(';')),
            Rule::Chain(5, TS('i'), TS('L'), TS('l'), TS(';'),NS('N')),
            Rule::Chain(3, TS('S'), NS('I'), TS(';')),
            Rule::Chain(4,TS('S'),NS('I'),TS(';'),NS('N')),
            Rule::Chain(3,TS('C'),NS('I'),TS(';')),
            Rule::Chain(4,TS('C'),NS('I'),TS(';'),NS('N')),

            Rule::Chain(8, TS('c'), TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';')),
            Rule::Chain(9, TS('c'), TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';'), NS('N')),
            Rule::Chain(3, TS('r'), NS('E'), TS(';')),
            Rule::Chain(4, TS('r'), NS('E'), TS(';'), NS('N')),
            Rule::Chain(3, TS('p'), NS('E'), TS(';')),
            Rule::Chain(4, TS('p'), NS('E'), TS(';'), NS('N')),
            Rule::Chain(3, TS('P'), NS('E'), TS(';')),
            Rule::Chain(4, TS('P'), NS('E'), TS(';'), NS('N')),
            Rule::Chain(10, TS('T'), TS('('), NS('E'), NS('C'), TS(')'), TS('{'), NS('N'), TS('}'), TS(';'), NS('N')),
            Rule::Chain(9, TS('T'), TS('('), NS('E'), NS('C'), TS(')'), TS('{'), NS('N'), TS('}'), TS(';')),
            Rule::Chain(9, TS('w'), TS('('), NS('E'), NS('C'), TS(')'), TS('['), NS('N'), TS(']'), TS(';')),
            Rule::Chain(10, TS('w'), TS('('), NS('E'), NS('C'), TS(')'), TS('['), NS('N'), TS(']'), TS(';'), NS('N'))),
        Rule(NS('E'), GRB_ERROR_SERIES + 2,      //Выражения 
            9,    // E ->  i | l |  (E)  | i(W) | iM  | lM | (E)M  | i(W)M| i()
            Rule::Chain(1, TS('i')),
            Rule::Chain(1, TS('l')),
            Rule::Chain(3, TS('('), NS('E'), TS(')')),
            Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
            Rule::Chain(3, TS('i'), TS('('), TS(')')),
            Rule::Chain(2, TS('i'), NS('M')),
            Rule::Chain(2, TS('l'), NS('M')),
            Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
            Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), NS('M'))
        ),
        Rule(NS('W'), GRB_ERROR_SERIES + 3,      // Выражение в параметрах функции
            4,    // W  -> i | l | i,W | l,W  
            Rule::Chain(1, TS('i')),
            Rule::Chain(1, TS('l')),
            Rule::Chain(3, TS('i'), TS(','), NS('W')),
            Rule::Chain(3, TS('l'), TS(','), NS('W'))
        ),
        Rule(NS('F'), GRB_ERROR_SERIES + 4,      // Параметры вызываемой функции
            2,    // F  -> ti | ti,F
            Rule::Chain(2, TS('t'), TS('i')), Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F'))
        ),
        Rule(NS('M'), GRB_ERROR_SERIES + 5,      // Математические операторы
            10,    // M -> vE | vEM
            Rule::Chain(2, TS('+'), NS('E')),
            Rule::Chain(3, TS('+'), NS('E'), NS('M')),
            Rule::Chain(2, TS('-'), NS('E')),

            Rule::Chain(3, TS('-'), NS('E'), NS('M')),
            Rule::Chain(2, TS('*'), NS('E')),
            Rule::Chain(3, TS('*'), NS('E'), NS('M')),
            Rule::Chain(2, TS('/'), NS('E')),

            Rule::Chain(3, TS('/'), NS('E'), NS('M')),
            Rule::Chain(2, TS('%'), NS('E')),
            Rule::Chain(3, TS('%'), NS('E'), NS('M'))
        ),
        Rule(NS('C'), GRB_ERROR_SERIES + 6,//тернарные операторы и их условия
            4,
            Rule::Chain(2, TS('>'), NS('E')),

            Rule::Chain(2, TS('<'), NS('E')),

            Rule::Chain(2, TS('e'), NS('E')),

            Rule::Chain(2, TS('!'), NS('E'))
        ),
        Rule(NS('I'), GRB_ERROR_SERIES + 8,//правило для функций без параметров
            1,
            Rule::Chain(2, TS('('), TS(')'))
        )
    );
}