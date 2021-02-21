#include "Transaction.h"
#include "DateHour.h"

using namespace std;

namespace TransactionReader
{
    string Transaction::toString()
    {
        string resultPrice = to_string(price);

        char* contentCopy = _strdup(resultPrice.c_str());
        char* context = NULL;

        string integerPortion = strtok_s(contentCopy, ".", &context);
        string decimalPortion = strtok_s(NULL, "\0", &context);

        if (decimalPortion.size() > 2)
        {
            resultPrice = integerPortion + "." + decimalPortion.substr(0, 2);
        }

        return dateHour.toString() + ";" + product + ";" + resultPrice + ";" + paymentType + ";" + personName + ";" + city + ";" + state + ";" + country;
    }
}