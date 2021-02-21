#include <iostream>
#include <fstream>
#include "DateHour.h"
#include "TransactionReader.h"

using namespace std;

namespace TransactionReader
{
	string fileHeader;

	vector<Transaction> readTransactionsFromFile(string t_fileName)
	{
		ifstream openedFile(t_fileName);
		string output;
		vector<Transaction> transactions;

		if (openedFile.fail())
		{
			openedFile.close();
			return {};
		}

		getline(openedFile, fileHeader);

		while (getline(openedFile, output))
		{
			char* contentCopy = _strdup(output.c_str());
			char* context = NULL;
			Transaction newTransaction;

			string dateHourString = strtok_s(contentCopy, ";", &context);
			newTransaction.dateHour = DateHour::parseToDateHour(dateHourString);

			newTransaction.product = strtok_s(NULL, ";", &context);
			newTransaction.price = atof(strtok_s(NULL, ";", &context));
			newTransaction.paymentType = strtok_s(NULL, ";", &context);
			newTransaction.personName = strtok_s(NULL, ";", &context);
			newTransaction.city = strtok_s(NULL, ";", &context);
			newTransaction.state = strtok_s(NULL, ";", &context);
			newTransaction.country = strtok_s(NULL, "\0", &context);

			transactions.push_back(newTransaction);

			free(contentCopy);
		}

		openedFile.close();
		return transactions;
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

	bool saveTransactionsToFile(vector<Transaction> t_transactions, string t_fileName)
	{
		ofstream createdFile(t_fileName);

		if (createdFile.fail())
		{
			createdFile.close();
			return false;
		}

		createdFile << fileHeader << endl;

		for (int i = 0; i < t_transactions.size(); i++)
		{
			createdFile << t_transactions[i].toString() << endl;
		}

		createdFile.close();
		return true;
	}
}
