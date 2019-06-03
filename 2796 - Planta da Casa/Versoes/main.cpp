/**
 * @file main.cpp
 * @author Christian Reis Fagundes Gomes (christianrfg@gmail.com)
 * @brief URI Online Judge - (2796) Houseplant (https://www.urionlinejudge.com.br/judge/en/problems/view/2796)
 * @version 0.1
 * @date 2019-05-15
 * 
 * @copyright Copyright (c) 2019
 */

/**
 * @solution
 *  
 * 
 * @references
 *  [1] GeeksforGeeks. (2019). Structure Sorting (By Multiple Rules) in C++ - 
 *  GeeksforGeeks. [online] Available at: https://www.geeksforgeeks.org/structure-sorting-in-c/ 
 *  [Accessed 25 May 2019].
 * 
 *  [2] Stack Overflow. (2019). Find whether a 2d matrix is subset of another 
 *  2d matrix. [online] Stack Overflow. Available at: https://stackoverflow.com/questions/28052395/find-whether-a-2d-matrix-is-subset-of-another-2d-matrix 
 *  [Accessed 25 May 2019].
 */
#include <bits/stdc++.h>

using namespace std;

/**
 * @brief Struct for store table information
 */
struct Table
{
    int length;
    int width;
    int totalSize;
};

inline bool rabinKarpMatcher(int pRows, int pCols, int pHash, int tRows, int tCols,
                             vector<vector<char>> T)
{
    int tHash; // Matrix hash
    bool have_0;
    int k, w;

    // DEBUG
    // cout << "P_HASH=[" << pHash << "]" << endl;

    for (int i = 0; i <= (tRows - pRows); ++i)
    {
        for (int j = 0; j <= (tCols - pCols); ++j)
        {
            tHash = 0;
            have_0 = false;
            k = i;

            while ((!have_0) && (k < i + pRows))
            {
                w = j;
                while ((!have_0) && (w < j + pCols))
                {
                    if (T[k][w] == '.')
                        tHash += 1;
                    else
                        have_0 = true;

                    ++w;
                }

                ++k;
            }

            // If subT and P hash's are equal, then the table P fits in T
            if (tHash == pHash)
                return true;
        }
    }

    return false;
}

/**
 * @brief Main Program
 *  Reads the problem input, solve the problem and prints the result.
 * 
 * @return int 
 *  Indicate how the program exited (normal = 0 and abnormal = 1)
 */
int main(__attribute__((unused)) int argc, __attribute__((unused)) char const *argv[])
{
    /**
     * @brief Configuration for fast I/O with cin/cout
     */

    ios_base::sync_with_stdio(false); // Toggle off synchronization of all the C++ standard streams
    cin.tie(NULL);                    // Disable the flushing of std::cout before std::cin accepts an input

    /**
     * @brief Variables 
     */

    // Input variables
    int N, M, K, C, L;
    char character;

    // Variables for problem solution
    vector<vector<char>> P;          // Matrix to store table pattern
    vector<vector<char>> housePlant; // Matrix to store house plant
    vector<Table> tables;            // Table to store length and width of each table

    // Output variables
    bool result; // Result of Kabin-Karp Matcher

    /**
     * @brief Reading input 
     */

    // Reading the houseplant matrix
    cin >> N >> M;                              // Dimensions of the houseplant
    housePlant.resize(N, vector<char>(M, '#')); // Create houseplant matrix

    // Fill houseplant matrix with the values from input
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            cin >> character;
            housePlant[i][j] = character;
        }
    }

    // Reading the tables

    cin >> K; // Size of the list of table options

    // Read all tables lendth and width to vector
    for (int i = 0; i < K; ++i)
    {
        cin >> C >> L;
        tables.push_back({C, L, (C * L)}); // We store C * L to get the totalSize of each table
    }

    exit(1);

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);
    shuffle(tables.begin(), tables.end(), e);
    

    /**
     * @brief Solving the Problem
     */

    Table largest_table;
    largest_table.totalSize = numeric_limits<int>::min();

    for (auto const &table : tables)
    {
        if (table.totalSize > largest_table.totalSize)
        {
            result = rabinKarpMatcher(table.length, table.width,
                                      table.totalSize, N, M, housePlant);

            // Try rotate the table
            if ((!result) && (table.length != table.width))
            {
                result = rabinKarpMatcher(table.width, table.length,
                                          table.totalSize, N, M, housePlant);
            }

            // Update the largest table that fit in the houseplant
            if (result)
                largest_table = table;
        }
    }

    // cout << "MAX_TABLE=[" << max_table << "]" << endl;
    // cout << "TABLE_LENGTH=[" << largest_table.length << "], TABLE_WIDTH=[" << largest_table.width <<  "]" << endl;

    // Output
    cout << largest_table.length << " " << largest_table.width << "\n";

    return 0;
}