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
	};
}

#endif
