#ifndef TABLE_HPP
#define TABLE_HPP

#include <thread>   // used for std::jthreads
#include <mutex>    // used for std::mutex

class Table {

  public:

    /**
    * @brief Default Constructor of Table Class
    */
                    Table                   ();

    /**
    * @brief Parameterised Constructor of Table Class for default value
    */
                    Table                   (int pRow, int pCol, long long pValue = 0ll);

    /**
    * @brief Distructor of Table Class
    */
                    ~Table                  ();

    /**
    * @brief Write data at specific coordinate in table
    */
    bool            WriteAt                 (int pRow, int pCol, long long pSource);
    
    /**
    * @brief Display a specific row of Table
    */
    bool            ReadRow                 (int pRow);
    
    /**
    * @brief Display a specific range of rows of Table
    */
    bool            ReadRows                (int pRow1, int pRow2);
    
    /**
    * @brief Display entire Table
    */
    void            PrintTable              ();
    
  private:
    
    /**
    * @brief Create and Allocate memory to Table
    */
    bool            CreateTable             (int pRow, int pCol, long long pValue = 0ll);

    int             vRow;
    int             vCol;
    long long **    vTable;

    // For mutual exculsive write access to table
	std::mutex      vReadMutex;
    
    // For mutual exculsive read access to table for consistent display of table
	std::mutex      vWriteMutex;
};

#endif // !TABLE_HPP
