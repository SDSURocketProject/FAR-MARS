/**
 * Data Logger Class
 *
 * @author Zack Mudd <zmudd@sdsu.edu>
 */

#include "logger.h"
#include "mainwindow.h"

/**
 * Logger Class Constructor
 */
logger::logger(){
    filename = "test.txt";
    state = CLOSED;      
}

/**
 * Set path to log file
 *
 * @since v0.2.0
 * @param char* path to be used as filename
 */
void logger::setFile(const char *newFilename){
    if (state) { mainwindow::showWarningBox("File open. Close before changing file"); return; }
	filename = const_cast<char *>(newFilename);
}

/**
 * Open log for writing
 */
void logger::openFile(){
    if (state) { mainwindow::showWarningBox("File already open. Close before opening again"); return; }
    file.open(filename, std::ios::app);
    state = OPEN;
}

/**
 * Close file after writing
 */
void logger::closeFile(){
    if (!state) { mainwindow::showWarningBox("File already closed"); return; }
    file.close();
    state = CLOSED;
}

/**
 * Check if log is currently opened
 *
 * @return int 1 if open, else 0
 */
int logger::isOpen(){
    return state;
}

/**
 * Append data to file, generic
 *
 * @param int[] data to be appended to file
 * @return spawns warning popup if file not opened for writing
 */
void logger::appendData(int data[], int vals){
    if (!state) { mainwindow::showWarningBox("File not open"); return; }
	std::string str = csvformat(data, vals);
    file << str.c_str();
}

/**
 * Append data to file, EOL-defined
 *
 * @param int[] data to be appended to file
 * @param int append newline to end of data, 1 for yes 0 for no
 * @return spawns warning popup if file not opened for writing
 */
void logger::appendData(int data[], int vals, int newLine){
    if (!state) { mainwindow::showWarningBox("File not open"); return; }
	std::string str = csvformat(data, vals, newLine);
    file << str.c_str();
}

/**
 * Append newline to file
 *
 * @return spawns warning window if file not opened for writing
 */
void logger::newLine(){
    if (!state) { mainwindow::showWarningBox("File not open"); return; }
    file << '\n';
}
