#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include "DateHour.h"

namespace TransactionReader
{
	class Transaction
	{
	public:
		DateHour dateHour;
		double price{ 0 };
		std::string product{ "" }, paymentType{ "" }, personName{ "" }, city{ "" }, state{ "" }, country{ "" };

		std::string toString();
		void parseToTransaction(std::string t_content);
		bool readTransactionFromBinaryFile(std::fstream& t_openedFile);
		bool writeTransactionToBinaryFile(std::fstream& t_createdFile);
	};
}

#endif
