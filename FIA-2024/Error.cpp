#include "stdafx.h"
namespace ERROR
{
	// 0 - 99 - system erors
	// 100 - 109 - parameter erors
	// 110 - 119 - file open and read erors

	ERROR errors[ERROR_MAX_ENTRY] = //list of errors
	{

		ERROR_ENTRY(0, "Неверный код ошибки"),
		ERROR_ENTRY(1, "Системная ошибка"),
		ERROR_ENTRY(2,"Задано недостаточно параметров"),
		ERROR_ENTRY(3,"Деление на 0 запрещено"),
		ERROR_ENTRY_NODEF(4),
		ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6),
		ERROR_ENTRY_NODEF(7),
		ERROR_ENTRY_NODEF(8),
		ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10),
		ERROR_ENTRY_NODEF10(20),
		ERROR_ENTRY_NODEF10(30),
		ERROR_ENTRY_NODEF10(40),
		ERROR_ENTRY_NODEF10(50),

		//lexem and identifier table errors
		ERROR_ENTRY(60, "Таблица лексем: Невозможно добавить новый элемент. Превышен максимальный размер таблицы"),
		ERROR_ENTRY(61, "Таблица лексем: Невозможно получить элемент из таблицы. Индекс меньше или больше возможного"),
		ERROR_ENTRY_NODEF(62),
		ERROR_ENTRY(63, "Таблица лексем: Невозможно открыть поток для вывода таблицы лексем"),
		ERROR_ENTRY_NODEF(64),
		ERROR_ENTRY(65, "Таблица идентификаторов: Имя идентификатора длиннее разрешённого значения"),
		ERROR_ENTRY(66, "Таблица идентификаторов: Невозможно добавить новый элемент. Превышен максимальный размер таблицы"),
		ERROR_ENTRY(67, "Таблица идентификаторов: Невозможно получить элемент из таблицы. Индекс меньше или больше возможого"),
		ERROR_ENTRY(68,"Таблица идентификаторов: Невозможно создать таблицу. Размер таблицы больше возможного "),
		ERROR_ENTRY_NODEF(69),
		ERROR_ENTRY_NODEF10(70),
		ERROR_ENTRY_NODEF10(80),

		//lecsical analyzer erors
		ERROR_ENTRY(90, "Лексический анализатор: Слово не распознано"),
		ERROR_ENTRY(91, "Лексический анализатор: Длина литерала больше разрешённого значения"),
		ERROR_ENTRY(92, "Лексический анализатор: Литерал не был распознан"),
		ERROR_ENTRY(93, "Лексический анализатор: Идентификатор не был распознан"),
		ERROR_ENTRY(94, "Лексический анализатор: Найдено больше одной или ни одной функции main"),
		ERROR_ENTRY(95, "Лексический анализатор: Функция была определена больше чем один раз"),
		ERROR_ENTRY(96, "Лексический анализатор: Переменная была объявлена больше одного раза"),
		ERROR_ENTRY(97, "Лексический анализатор: Нераспознанная пременная"),
		ERROR_ENTRY(98,"Лексический анализатор: Ошибки пунктуатии"),
		ERROR_ENTRY_NODEF(99),

		//
		ERROR_ENTRY(100, " -in должен иметь параметр"),
		ERROR_ENTRY_NODEF(101),
		ERROR_ENTRY_NODEF(102),
		ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104, "Длина входного параметра больше возможного"),
		ERROR_ENTRY(105, "Длина входного файла больше возможного"),
		ERROR_ENTRY_NODEF(106),
		ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108),
		ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110, "Ошибка открытия файла с исходным кодом (-in)"),
		ERROR_ENTRY(111, "Неразрешённый символ во входном файле (-in)"),
		ERROR_ENTRY(112, "Невозможно создать файл протокола (-log)"),
		ERROR_ENTRY(113, "Невозможно создать файл объектного кода (-out)"),
		ERROR_ENTRY(114,"Невозможно создать файл протокола с именем входного файла"),
		ERROR_ENTRY_NODEF(115),
		ERROR_ENTRY_NODEF(116),
		ERROR_ENTRY_NODEF(117),
		ERROR_ENTRY_NODEF(118),
		ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY_NODEF10(120),

		ERROR_ENTRY_NODEF10(130),
		ERROR_ENTRY_NODEF10(140),
		ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160),
		ERROR_ENTRY_NODEF10(170),
		ERROR_ENTRY_NODEF10(180),
		ERROR_ENTRY_NODEF10(190),

		ERROR_ENTRY_NODEF100(200),

		ERROR_ENTRY_NODEF100(300),

		ERROR_ENTRY_NODEF100(400),

		ERROR_ENTRY_NODEF100(500),

		//syntax analyser errors
		ERROR_ENTRY(600,"Синтаксический анализатор: Неверная структура программы"),
		ERROR_ENTRY(601,"Синтаксический анализатор: Неверный идентификатор, использования ключевого слова или ошибка пунктуации"),
		ERROR_ENTRY(602,"Синтаксический анализатор: Неверное выражение"),
		ERROR_ENTRY(603,"Синтаксический анализатор: Неверное выражение в параметрах функции"),
		ERROR_ENTRY(604,"Синтаксический анализатор: Неверные параметры функции"),
		ERROR_ENTRY(605,"Синтаксический анализатор: Неверный математический оператор или его использование"),
		ERROR_ENTRY(606,"Синтаксический анализатор: Неверное условие выхода из цикла"),
		ERROR_ENTRY(607,"Синтаксический анализатор: Неверно заданы параметры функции, не принимающей параметров"),
		ERROR_ENTRY_NODEF(608),
		ERROR_ENTRY_NODEF(609),
		ERROR_ENTRY_NODEF10(610),
		ERROR_ENTRY_NODEF10(620),
		ERROR_ENTRY_NODEF10(630),
		ERROR_ENTRY_NODEF10(640),
		ERROR_ENTRY_NODEF10(650),
		ERROR_ENTRY_NODEF10(660),
		ERROR_ENTRY_NODEF10(670),
		ERROR_ENTRY_NODEF10(680),
		ERROR_ENTRY_NODEF10(690),


		ERROR_ENTRY(700,"Семантический анализатор: Ключевое слово используется в качестве идентификатора"),
		ERROR_ENTRY(701, "Семантический анализатор: Две функции названы одинаково"),
		ERROR_ENTRY(702, "Семантический анализатор: Две переменные названы одинаково"),
		ERROR_ENTRY(703,"Семантический анализатор: Фукнция используется до инициализации"),
		ERROR_ENTRY(704,"Семантический анализатор: Переменная используется до инициализации"),
		ERROR_ENTRY(705,"Семантический анализатор: Некорректный тип данных для математической операции"),
		ERROR_ENTRY(706,"Семантический анализатор: Некорректные параметры функции"),
		ERROR_ENTRY(707,"Семантический анализатор: Функция принимает больше параметров, чем возможно"),
		ERROR_ENTRY(708,"Семантический анализатор: Некорректный тип операции"),
		ERROR_ENTRY(709,"Семантический анализатор: Некорректный тип возвращаемого значения функции Main"),
		ERROR_ENTRY(710,"Семантический анализатор: Тип данных возвращаемого значения не соответствует типу данных функции"),
		ERROR_ENTRY(711,"Семантический анализатор: В функцию передано больше параметров, чем функция может принять"),
		ERROR_ENTRY(712,"Семантический анализатор: Неверный тип данных операции больше/меньше"),
		ERROR_ENTRY(713,"Семантический анализатор: Неверный тип данных при операции сравнения"),
		ERROR_ENTRY(714,"Семантический анализатор: Неверный тип данных в условии выхода из цикла"),
		ERROR_ENTRY(715,"Семантический анализатор: Повторяющийся возврат значения функции"),
		ERROR_ENTRY_NODEF(716),
		ERROR_ENTRY_NODEF(717),
		ERROR_ENTRY_NODEF(718),
		ERROR_ENTRY_NODEF(719),
		ERROR_ENTRY_NODEF10(720),
		ERROR_ENTRY_NODEF10(730),
		ERROR_ENTRY_NODEF10(740),
		ERROR_ENTRY_NODEF10(750),
		ERROR_ENTRY_NODEF10(760),
		ERROR_ENTRY_NODEF10(770),
		ERROR_ENTRY_NODEF10(780),
		ERROR_ENTRY_NODEF10(790),
		ERROR_ENTRY_NODEF100(800)

	};

	ERROR geterror(int id) //function for common general errors
	{
		if (id < 1 || id >= ERROR_MAX_ENTRY) {//if there is an unexpected error
			return errors[0];//throw an error for an unexpected error
		}
		cout << "Ошибка: " << errors[id].id << ": " << errors[id].message << endl;
		return errors[id];//if an eror in expected throw an eror suitable for a situation
	}
	ERROR geterrorin(int id, int line = -1, int col = -1, unsigned char* FailedText = (unsigned char*)"")//function to throw a specified error
	{
		if (id < 1 || id >= ERROR_MAX_ENTRY) {
			return errors[0];
		}
		//specify an error and column where an error is ocured
		errors[id].err_spec.col = col;
		errors[id].err_spec.line = line;
		errors[id].err_spec.FailedText = FailedText;
		cout << "Ошибка: " << errors[id].id << ": " << errors[id].message << " в строке " << errors[id].err_spec.line << " : " << errors[id].err_spec.FailedText << endl;
		return errors[id];
	}

	void Print() {
		for (int i = 0; i < ERROR_MAX_ENTRY; i++) {
			cout << errors[i].id << errors[i].message << endl;
		}
	}
}