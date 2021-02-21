#ifndef TRANSACTION_HEADER_H
#define TRANSACTION_HEADER_H

#include <vector>
#include <string>
#include "Transaction.h"

namespace TransactionReader
{
	std::vector<Transaction> readTransactionsFromFile(std::string t_fileName);
	std::vector<Transaction> filterTransactions(std::vector<Transaction> t_transactions, std::string t_searchDate);
	void printTransactions(std::vector<Transaction> t_transactions);
	bool saveTransactionsToFile(std::vector<Transaction> t_transactions, std::string t_fileName);
}

#endif
