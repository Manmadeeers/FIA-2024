#include "stdafx.h"
#include "MFST.h"
#include "GRB.h"
//#include "Windows.h"


int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");
	//SetConsoleCP(1251);
	//SetConsoleOutputCP(1251);

	LOG::Log log = LOG::INITLOG;
	PARM::PARM parm = PARM::getparm(argc, argv);
	OUT::Out out;

#ifdef TEST1

#endif 

	try {
		In::IN in = In::getin(parm.in);
		out = OUT::getout(parm.out);
		log = LOG::getlog(parm.log);
		LOG::WriteLine(log, (char*)"Test: ", (char*)" without errors \n", "");
		LOG::WriteLine_W(log, (wchar_t*)L"Test: ", (wchar_t*)L" without errors \n", L"");
		LOG::WriteLog(log);
		LOG::WriteParm(log, parm);


		cout << endl << "<-----Исходный код FIA-2024----->" << endl << endl;;
		int src_line_counter = 0;
		cout << src_line_counter << ' ';

		for (int i = 0; i < in.words_size; i++) {


			if (in.words[i][0] == '|') {
				cout << endl;
				cout << ++src_line_counter << " ";
			}
			else {
				cout << in.words[i] << ' ';
			}
		}

		//for (int i = 0; i < in.words_size; i++) {
		//	cout << '[' << in.words[i] << ']' << endl;
		//}
		LOG::WriteIN(log, in);
		OUT::WriteOUT(in, parm.out);

		LT::LexTable LexTable = LT::Create(in.words_size);
		IT::IDTable IDTable = IT::Create(in.words_size);

		FST::formLexTable(LexTable, IDTable, in);
		//cout<<endl << ';' << in.words[0] << ';' << endl;
		if (parm.Show == true) {
			LT::PrintTable(LexTable);
		}


		/*	for (int i = 0; i < LexTable.size; i++) {
			cout<<LexTable.table[i].src_str_num << LexTable.table[i].lexem;
		}*/
		if (parm.Show == true) {
			IT::PrintTable(IDTable);
		}





		MFST_TRACE_START
			MFST::Mfst mfst(LexTable, GRB::getGreibach());
		mfst.start(parm.Show);
		mfst.savededucation();
		mfst.printrules(parm.Show);



		//ERROR::Print();
		SEM::ProceedSemanticAnalysis(LexTable, IDTable);

		/*	if (parm.Show == true) {

				cout << endl << endl << "Таблица лексем после преобразования в постфиксную польскую запись:" << endl;
				LT::PrintTable(LexTable);
			}*/
			/*POL::findN(LexTable, IDTable);
			LT::PrintTable(LexTable);*/


		GNR::GenToASM(LexTable, IDTable, out);


		OUT::Close(out);
		compileAndRunAssemblyFile(parm.out);


		IT::DeleteIdTable(IDTable);
		LT::DeleteLexTable(LexTable);
		In::deleteIN(in);


	}
	catch (ERROR::ERROR exception) {
		LOG::WriteERROR(log, exception);
		//OUT::WriteERROR(exception, out);
		LOG::Close(log);

	}

	system("pause");
	return 0;
}