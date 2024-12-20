#include "stdafx.h"
namespace ERROR
{
	// 0 - 99 - system erors
	// 100 - 109 - parameter erors
	// 110 - 119 - file open and read erors

	ERROR errors[ERROR_MAX_ENTRY] = //list of errors
	{

		ERROR_ENTRY(0, "�������� ��� ������"),
		ERROR_ENTRY(1, "��������� ������"),
		ERROR_ENTRY(2,"������ ������������ ����������"),
		ERROR_ENTRY(3,"������� �� 0 ���������"),
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
		ERROR_ENTRY(60, "������� ������: ���������� �������� ����� �������. �������� ������������ ������ �������"),
		ERROR_ENTRY(61, "������� ������: ���������� �������� ������� �� �������. ������ ������ ��� ������ ����������"),
		ERROR_ENTRY_NODEF(62),
		ERROR_ENTRY(63, "������� ������: ���������� ������� ����� ��� ������ ������� ������"),
		ERROR_ENTRY_NODEF(64),
		ERROR_ENTRY(65, "������� ���������������: ��� �������������� ������� ������������ ��������"),
		ERROR_ENTRY(66, "������� ���������������: ���������� �������� ����� �������. �������� ������������ ������ �������"),
		ERROR_ENTRY(67, "������� ���������������: ���������� �������� ������� �� �������. ������ ������ ��� ������ ���������"),
		ERROR_ENTRY(68,"������� ���������������: ���������� ������� �������. ������ ������� ������ ���������� "),
		ERROR_ENTRY_NODEF(69),
		ERROR_ENTRY_NODEF10(70),
		ERROR_ENTRY_NODEF10(80),

		//lecsical analyzer erors
		ERROR_ENTRY(90, "����������� ����������: ����� �� ����������"),
		ERROR_ENTRY(91, "����������� ����������: ����� �������� ������ ������������ ��������"),
		ERROR_ENTRY(92, "����������� ����������: ������� �� ��� ���������"),
		ERROR_ENTRY(93, "����������� ����������: ������������� �� ��� ���������"),
		ERROR_ENTRY(94, "����������� ����������: ������� ������ ����� ��� �� ����� ������� main"),
		ERROR_ENTRY(95, "����������� ����������: ������� ���� ���������� ������ ��� ���� ���"),
		ERROR_ENTRY(96, "����������� ����������: ���������� ���� ��������� ������ ������ ����"),
		ERROR_ENTRY(97, "����������� ����������: �������������� ���������"),
		ERROR_ENTRY(98,"����������� ����������: ������ ����������"),
		ERROR_ENTRY_NODEF(99),

		//
		ERROR_ENTRY(100, " -in ������ ����� ��������"),
		ERROR_ENTRY_NODEF(101),
		ERROR_ENTRY_NODEF(102),
		ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104, "����� �������� ��������� ������ ����������"),
		ERROR_ENTRY(105, "����� �������� ����� ������ ����������"),
		ERROR_ENTRY_NODEF(106),
		ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108),
		ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110, "������ �������� ����� � �������� ����� (-in)"),
		ERROR_ENTRY(111, "������������� ������ �� ������� ����� (-in)"),
		ERROR_ENTRY(112, "���������� ������� ���� ��������� (-log)"),
		ERROR_ENTRY(113, "���������� ������� ���� ���������� ���� (-out)"),
		ERROR_ENTRY(114,"���������� ������� ���� ��������� � ������ �������� �����"),
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
		ERROR_ENTRY(600,"�������������� ����������: �������� ��������� ���������"),
		ERROR_ENTRY(601,"�������������� ����������: �������� �������������, ������������� ��������� ����� ��� ������ ����������"),
		ERROR_ENTRY(602,"�������������� ����������: �������� ���������"),
		ERROR_ENTRY(603,"�������������� ����������: �������� ��������� � ���������� �������"),
		ERROR_ENTRY(604,"�������������� ����������: �������� ��������� �������"),
		ERROR_ENTRY(605,"�������������� ����������: �������� �������������� �������� ��� ��� �������������"),
		ERROR_ENTRY(606,"�������������� ����������: �������� ������� ������ �� �����"),
		ERROR_ENTRY(607,"�������������� ����������: ������� ������ ��������� �������, �� ����������� ����������"),
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


		ERROR_ENTRY(700,"������������� ����������: �������� ����� ������������ � �������� ��������������"),
		ERROR_ENTRY(701, "������������� ����������: ��� ������� ������� ���������"),
		ERROR_ENTRY(702, "������������� ����������: ��� ���������� ������� ���������"),
		ERROR_ENTRY(703,"������������� ����������: ������� ������������ �� �������������"),
		ERROR_ENTRY(704,"������������� ����������: ���������� ������������ �� �������������"),
		ERROR_ENTRY(705,"������������� ����������: ������������ ��� ������ ��� �������������� ��������"),
		ERROR_ENTRY(706,"������������� ����������: ������������ ��������� �������"),
		ERROR_ENTRY(707,"������������� ����������: ������� ��������� ������ ����������, ��� ��������"),
		ERROR_ENTRY(708,"������������� ����������: ������������ ��� ��������"),
		ERROR_ENTRY(709,"������������� ����������: ������������ ��� ������������� �������� ������� Main"),
		ERROR_ENTRY(710,"������������� ����������: ��� ������ ������������� �������� �� ������������� ���� ������ �������"),
		ERROR_ENTRY(711,"������������� ����������: � ������� �������� ������ ����������, ��� ������� ����� �������"),
		ERROR_ENTRY(712,"������������� ����������: �������� ��� ������ �������� ������/������"),
		ERROR_ENTRY(713,"������������� ����������: �������� ��� ������ ��� �������� ���������"),
		ERROR_ENTRY(714,"������������� ����������: �������� ��� ������ � ������� ������ �� �����"),
		ERROR_ENTRY(715,"������������� ����������: ������������� ������� �������� �������"),
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
		cout << "������: " << errors[id].id << ": " << errors[id].message << endl;
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
		cout << "������: " << errors[id].id << ": " << errors[id].message << " � ������ " << errors[id].err_spec.line << " : " << errors[id].err_spec.FailedText << endl;
		return errors[id];
	}

	void Print() {
		for (int i = 0; i < ERROR_MAX_ENTRY; i++) {
			cout << errors[i].id << errors[i].message << endl;
		}
	}
}