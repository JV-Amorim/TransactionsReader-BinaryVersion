#ifndef MAIN_H
#define MAIN_H

#include <vector>
#include "Transaction.h"

int main();
void showInitialView();
void showFileSelectionView();
void showSearchView(std::vector<TransactionReader::Transaction> t_transactions);
void showSaveFileView(std::vector<TransactionReader::Transaction> t_transactions);

#endif
