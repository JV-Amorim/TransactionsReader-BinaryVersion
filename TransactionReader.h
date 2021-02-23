#ifndef TRANSACTION_HEADER_H
#define TRANSACTION_HEADER_H

#include <vector>
#include <string>
#include "Transaction.h"

namespace TransactionReader
{
	std::vector<Transaction> readTransactionsFromTextFile(std::string t_fileName);
	std::vector<Transaction> readTransactionsFromBinaryFile(std::string t_fileName);
	bool saveTransactionsToBinaryFile(std::vector<Transaction> t_transactions, std::string t_fileName);
	void convertTransactionsTextFileToBinaryFile(std::string t_fileName);
	std::vector<Transaction> filterTransactions(std::vector<Transaction> t_transactions, std::string t_searchDate);
	void printTransactions(std::vector<Transaction> t_transactions);
}

#endif
