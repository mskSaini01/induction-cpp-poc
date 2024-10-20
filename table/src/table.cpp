#include "table.hpp"

Table::Table ()
{
    vRow    = 0;
    vCol    = 0;
    vTable  = nullptr;
}

Table::Table (int pRow, int pCol, long long pValue)
{
    vRow    = pRow;
    vCol    = pCol;
    vTable  = nullptr;

    CreateTable (pRow, pCol, pValue);
}

Table::~Table ()
{
    // Check for size of table
    if (vRow == 0 && vCol == 0) {
        vTable = nullptr;
        return;
    }

    // delete each row and assign it to nullptr
    for (int i = 0; i < vRow; i++) {
        
        delete [] vTable[i];
        vTable[i] = nullptr;
    }
    delete [] vTable;
    vTable = nullptr;
}

bool Table::WriteAt (int pRow, int pCol, long long pSource)
{
        // Thread access - mutual exclusive
	    std::lock_guard<std::mutex> lock (vReadMutex);

    // pRow and pCol can't be greater than the tables row and column count
    if ((pRow > vRow - 1) || (pCol > vCol - 1)) {
        return false;
    }

    vTable[pRow][pCol] = pSource;
    
    return true;
}

bool Table::ReadRow (int pRow)
{
        // Thread access - mutual exclusive
	    std::lock_guard<std::mutex> lock (vWriteMutex);

    // prow can't be greater than table vRow
    if (pRow > vRow - 1) {
        return false;
    }

    printf (" { ");

    // Iterate over columns to print cell values
    for (int col = 0; col < vCol; col++) {
        printf ("%lld, ", vTable[pRow][col]);
    }
    
    printf (" }\n");

    return true;
}

bool Table::ReadRows (int pRow1, int pRow2)
{
        // Thread access - mutual exclusive
	    std::lock_guard<std::mutex> lock (vWriteMutex);

    // Handle Inputs
    if ((pRow1 > vRow - 1) || (pRow2 > vRow - 1) || (pRow1 > pRow2)) {
        return false;
    }

    printf (" { ");
    
    // Iterate over row to print cell values
    for (int row = pRow1; row <= pRow2; row++) {
        printf (" { ");
        
        // Iterate over columns to print cell values
        for (int col = 0; col < vCol; col++) {
            printf ("%lld ", vTable[row][col]);
        }
        printf (" },\n");
    }
    
    printf (" }\n");
    
    return true;
}

void Table::PrintTable ()
{
        // Thread access - mutual exclusive
	    std::lock_guard<std::mutex> lock (vWriteMutex);

    printf (" { ");
    
    // Iterate over row to print each row
    for (int row = 0; row < vRow; row++) {

        printf (" { ");
        
        // Iterate over columns to print each column value in a specific row
        for (int col = 0; col < vCol; col++) {
            printf ("%lld, ", vTable[row][col]);
        }
        
        printf (" },\n");
    }
    printf (" }\n");
}

bool Table::CreateTable (int pRow, int pCol, long long pValue)
{
    // return when size = 0
    if (pRow == 0 || pCol == 0) {
        return true;
    }
    
    vRow = pRow;
    vCol = pCol;
    
    vTable = new (std::nothrow) long long * [vRow];

    // Handle memory allocation failure
    if (vTable == nullptr) {
        vRow = 0;
        vCol = 0;
        return false;
    }
    
    // Iterate over row to allocate heap memory to each rows
    for (int row = 0; row < vRow; row++) {

        vTable[row] = new (std::nothrow) long long [vCol];
        
        // Handle memory allocation failure
        if (vTable[row] == nullptr) {
            vRow = 0;
            vCol = 0;
            return false;
        }
        
        // Initialize columns cell values with 0 as default value
        for (int col = 0; col < vCol; col++) {
            vTable[row][col] = pValue;
        }
    }

    return true;
}
