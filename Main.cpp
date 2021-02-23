#include <iostream>

#include "Main.h"
#include "DateHour.h"
#include "TransactionReader.h"

using namespace std;
using namespace TransactionReader;

int main()
{
    showInitialView();
    return 0;
}

void showInitialView()
{
    cout << "LEITOR DE ARQUIVOS DE TRANSACOES" << endl;
    cout << endl << "Digite uma opcao:";
    cout << endl << "[1] Converter arquivo de transacoes em formato texto (contido na pasta \"Data\") para formato binario;";
    cout << endl << "[2] Abrir um arquivo binario de transacoes (contido na pasta \"Data\");";
    cout << endl << "[0] Sair;" << endl;

    int choice = -1;
    cin >> choice;

    if (choice == 0)
    {
        return;
    }
    else if (choice == 1)
    {
        showFileConversionView();
    }
    else if (choice == 2)
    {
        showFileSelectionView();
    }
    else
    {
        cout << "Erro: nao foi digitada uma opcao valida. A aplicacao sera encerrada." << endl;
        return;
    }
}

void showFileConversionView()
{
    cout << endl << "Digite o nome completo do arquivo em formato texto (com a extensao):" << endl;

    string fileName = "";
    cin >> fileName;

    convertTransactionsTextFileToBinaryFile(fileName);
}

void showFileSelectionView()
{
    cout << endl << "Digite o nome completo do arquivo (sem a extensao):" << endl;

    string fileName = "";
    cin >> fileName;

    vector<Transaction> transactions = readTransactionsFromBinaryFile(fileName);

    if (transactions.empty())
    {
        cout << endl << "Erro: nao foi possivel abrir o arquivo especificado ou ele nao possui transacoes. A aplicacao sera encerrada." << endl;
        return;
    }

    cout << endl << "O arquivo foi lido com sucesso. O que deseja fazer com os dados?" << endl;

    int choice = -1;

    while (true)
    {
        cout << endl << "Digite uma opcao:" << endl;
        cout << "[1] Mostrar todas as transacoes;" << endl << "[2] Pesquisar transacoes de uma certa data;" << endl << "[0] Sair" << endl;

        cin >> choice;

        if (choice == 0)
        {
            return;
        }
        else if (choice == 1)
        {
            cout << endl;
            printTransactions(transactions);
        }
        else if (choice == 2)
        {
            showSearchView(transactions);
        }
        else
        {
            cout << "Erro: nao foi digitada uma opcao valida. A aplicacao sera encerrada." << endl;
            return;
        }
    }
}

void showSearchView(vector<Transaction> t_transactions)
{
    if (APP_DATE_HOUR_FORMAT == DateHourFormat::Brazil)
    {
        cout << endl << "Digite a data desejada (DD/MM/AAAA):" << endl;
    }
    else if (APP_DATE_HOUR_FORMAT == DateHourFormat::UnitedStates)
    {
        cout << endl << "Digite a data desejada (MM/DD/AAAA):" << endl;
    }
    else
    {
        cout << "Erro: o formato de data e hora nao foi definido na aplicacao." << endl;
        return;
    }

    string searchDate;
    cin >> searchDate;

    vector<Transaction> filteredTransactions = filterTransactions(t_transactions, searchDate);

    cout << endl << "RESULTADO DA PESQUISA:" << endl;

    if (filteredTransactions.empty())
    {
        cout << "Nenhuma transacao com a data informada foi encontrada." << endl;
    }
    else
    {
        printTransactions(filteredTransactions);
        showSaveFileView(filteredTransactions);
    }
}

void showSaveFileView(vector<Transaction> t_transactions)
{
    cout << endl << "Deseja salvar as transacoes em um novo arquivo?" << endl;
    cout << "Digite uma opcao:" << endl << "[1] Salvar;" << endl << "[0] Sair" << endl;

    int choice = -1;
    cin >> choice;

    if (choice != 1)
    {
        return;
    }

    cout << endl << "Nota: o arquivo sera salvo na pasta \"Data\" e sobreescrevera qualquer arquivo com o mesmo nome ja existente." << endl;
    cout << "Digite um nome para o arquivo (sem a extensao):" << endl;

    string fileName = "";
    cin >> fileName;

    bool isSuccessful = saveTransactionsToBinaryFile(t_transactions, fileName);

    if (isSuccessful)
    {
        cout << endl << "Arquivo salvo com sucesso!" << endl;
    }
    else
    {
        cout << "Erro: nao foi possivel salvar o arquivo." << endl;
    }
}
