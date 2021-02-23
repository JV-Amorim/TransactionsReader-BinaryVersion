#include "Transaction.h"
#include "DateHour.h"
#include <fstream>

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

    void Transaction::parseToTransaction(string t_content)
    {
        char* contentCopy = _strdup(t_content.c_str());
        char* context = NULL;

        string dateHourString = strtok_s(contentCopy, ";", &context);
        dateHour = DateHour::parseToDateHour(dateHourString);

        product = strtok_s(NULL, ";", &context);
        price = atof(strtok_s(NULL, ";", &context));
        paymentType = strtok_s(NULL, ";", &context);
        personName = strtok_s(NULL, ";", &context);
        city = strtok_s(NULL, ";", &context);
        state = strtok_s(NULL, ";", &context);
        country = strtok_s(NULL, "\0", &context);

        free(contentCopy);
    }

    bool Transaction::readTransactionFromBinaryFile(fstream& t_openedFile)
    {
        if (!t_openedFile || !t_openedFile.is_open() || t_openedFile.fail())
        {
            return false;
        }

        size_t stringSizes[6];
        t_openedFile.read(reinterpret_cast<char*>(&stringSizes), sizeof(stringSizes));

        product.resize(stringSizes[0]);
        paymentType.resize(stringSizes[1]);
        personName.resize(stringSizes[2]);
        city.resize(stringSizes[3]);
        state.resize(stringSizes[4]);
        country.resize(stringSizes[5]);

        t_openedFile.read(reinterpret_cast<char*>(&dateHour), sizeof(DateHour));
        t_openedFile.read(reinterpret_cast<char*>(&price), sizeof(double));
        t_openedFile.read(&product[0], stringSizes[0]);
        t_openedFile.read(&paymentType[0], stringSizes[1]);
        t_openedFile.read(&personName[0], stringSizes[2]);
        t_openedFile.read(&city[0], stringSizes[3]);
        t_openedFile.read(&state[0], stringSizes[4]);
        t_openedFile.read(&country[0], stringSizes[5]);

        return true;
    }

    bool Transaction::writeTransactionToBinaryFile(fstream& t_createdFile)
    {
        if (!t_createdFile || !t_createdFile.is_open() || t_createdFile.fail())
        {
            return false;
        }

        size_t stringSizes[6] =
        {
            product.size(),
            paymentType.size(),
            personName.size(),
            city.size(),
            state.size(),
            country.size()
        };

        t_createdFile.write(reinterpret_cast<char*>(&stringSizes), sizeof(stringSizes));
        t_createdFile.write(reinterpret_cast<char*>(&dateHour), sizeof(DateHour));
        t_createdFile.write(reinterpret_cast<char*>(&price), sizeof(double));
        t_createdFile.write(product.c_str(), stringSizes[0]);
        t_createdFile.write(paymentType.c_str(), stringSizes[1]);
        t_createdFile.write(personName.c_str(), stringSizes[2]);
        t_createdFile.write(city.c_str(), stringSizes[3]);
        t_createdFile.write(state.c_str(), stringSizes[4]);
        t_createdFile.write(country.c_str(), stringSizes[5]);

        if (t_createdFile.fail())
        {
            return false;
        }

        return true;
    }
}
