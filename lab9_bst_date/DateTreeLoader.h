#ifndef DATE_TREE_LOADER_H
#define DATE_TREE_LOADER_H

#include <string>
#include <iosfwd>
#include "Bst.h"
#include "Date.h"

/**
 * @struct DateLoadReport
 * @brief Stores summary information for loading dates into a BST.
 */
struct DateLoadReport
{
    int filesOpened;
    int filesFailed;
    int rowsRead;
    int datesInserted;
    int duplicatesRejected;
    int invalidRows;

    /**
     * @brief Default constructor.
     */
    DateLoadReport();
};

/**
 * @brief Loads Date values from all CSV files listed in a source file.
 *
 * The source file is expected to contain one CSV filename per line.
 * Each CSV file is expected to contain a date/time value in the first column
 * (for example: d/mm/yyyy h:mm).
 * Only the date component is extracted and inserted into the BST.
 *
 * @param sourceFile Path to data_source.txt.
 * @param dateTree BST to load dates into.
 * @param log Output stream for progress and duplicate logging.
 * @return Summary report of the load process.
 */
DateLoadReport LoadDatesFromDataSource(
    const std::string& sourceFile,
    Bst<Date>& dateTree,
    std::ostream& log
);

/**
 * @brief Loads dates directly from a text file containing one date per record.
 *
 * The file format should match the Date extraction operator, e.g. d/m/yyyy.
 *
 * @param dateFile Path to date.txt.
 * @param dateTree BST to load dates into.
 * @param log Output stream for progress and duplicate logging.
 * @return Summary report of the load process.
 */
DateLoadReport LoadDatesFromDateFile(
    const std::string& dateFile,
    Bst<Date>& dateTree,
    std::ostream& log
);

#endif
