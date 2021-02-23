#include <iostream>
#include <fstream>
#include "DateHour.h"
#include "TransactionReader.h"

using namespace std;

namespace TransactionReader
{
	vector<Transaction> readTransactionsFromTextFile(string t_fileName)
	{
		ifstream openedFile(t_fileName);

		if (openedFile.fail())
		{
			openedFile.close();
			return {};
		}

		vector<Transaction> transactions;
		string output;

		getline(openedFile, output);

		while (getline(openedFile, output))
		{
			Transaction newTransaction;
			newTransaction.parseToTransaction(output);
			transactions.push_back(newTransaction);
		}

		openedFile.close();

		return transactions;
	}

	vector<Transaction> readTransactionsFromBinaryFile(string t_fileName)
	{
		fstream openedFile("Data/" + t_fileName + ".tbin", ios::in | ios::binary);

		if (openedFile.fail())
		{
			openedFile.close();
			return {};
		}

		vector<Transaction> transactions;
		size_t vectorSize;

		openedFile.read(reinterpret_cast<char*>(&vectorSize), sizeof(vectorSize));

		for (int i = 0; i < vectorSize; i++)
		{
			Transaction newTransaction;
			bool isSuccessful = newTransaction.readTransactionFromBinaryFile(openedFile);

			if (!isSuccessful)
			{
				return {};
			}

			transactions.push_back(newTransaction);
		}

		openedFile.close();

		return transactions;
	}

	bool saveTransactionsToBinaryFile(vector<Transaction> t_transactions, string t_fileName)
	{
		fstream createdFile("Data/" + t_fileName + ".tbin", ios::out | ios::binary);

		if (createdFile.fail())
		{
			createdFile.close();
			return false;
		}

		size_t vectorSize = t_transactions.size();
		createdFile.write(reinterpret_cast<char*>(&vectorSize), sizeof(vectorSize));

		for (int i = 0; i < vectorSize; i++)
		{
			bool isSuccessful = t_transactions[i].writeTransactionToBinaryFile(createdFile);

			if (!isSuccessful)
			{
				return false;
			}
		}

		createdFile.close();

		return true;
	}

	void convertTransactionsTextFileToBinaryFile(string t_fileName)
	{
		vector<Transaction> transactions = readTransactionsFromTextFile("Data/" + t_fileName);

		if (transactions.empty())
		{
			cout << endl << "Erro: nao foi possivel abrir o arquivo especificado ou ele nao possui transacoes. A aplicacao sera encerrada." << endl;
			return;
		}

		string binaryFileNameWithoutExtension = t_fileName.substr(0, t_fileName.find_last_of("."));

		bool isSuccessful = saveTransactionsToBinaryFile(transactions, binaryFileNameWithoutExtension);

		if (!isSuccessful)
		{
			cout << "Erro: nao foi possivel salvar o arquivo binario. A aplicacao sera encerrada." << endl;
			return;
		}

		cout << endl << "Arquivo binario salvo com sucesso!" << endl;
	}

	vector<Transaction> filterTransactions(vector<Transaction> t_transactions, string t_searchDate)
	{
		vector<Transaction> filteredTransactions;

		for (int i = 0; i < t_transactions.size(); i++)
		{
			char* currentDateHourStr = _strdup(t_transactions[i].dateHour.toString().c_str());
			char* context = NULL;
			string currentDateStr = strtok_s(currentDateHourStr, " ", &context);

			if (currentDateStr == t_searchDate)
			{
				filteredTransactions.push_back(t_transactions[i]);
			}
		}

		return filteredTransactions;
	}

	void printTransactions(vector<Transaction> t_transactions)
	{
		for (int i = 0; i < t_transactions.size(); i++)
		{
			cout << i + 1 << ". " << t_transactions[i].toString() << endl;
		}
	}
}
