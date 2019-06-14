/**
 * Data Logger Class
 */

#include "logger.h"
#include "mainwindow.h"

/**
 * @brief Logger Class Constructor
 */
logger::logger(){
	filename = "test.txt";
	state = CLOSED;	  
}

/**
 * @brief Set path to log file
 *
 * @since v0.2.0
 * @param[in] char* path to be used as filename
 */
void
logger::setFile(const char *newFilename){
	if (state) {
		return;
	}
	filename = const_cast<char *>(newFilename);
}

/**
 * @brief Open log for writing
 */
void
logger::openFile(){
	if (state) {
		return;
	}
	file.open(filename, std::ios::app);
	state = OPEN;
}

/**
 * @brief Close file after writing
 */
void
logger::closeFile(){
	if (!state) {
		return;
	}
	file.close();
	state = CLOSED;
}

/**
 * @brief Check if log is currently opened
 *
 * @return 1 if open, else 0
 */
int
logger::isOpen(){
	return state;
}

/**
 * @brief Append data to file, generic
 *
 * @param[in] float[] data to be appended to file
 * @param[in] int number of values to parse
 */
void
logger::appendData(float data[], int vals){
	if (!state) {
		return;
	}
	std::string str = csvformat(data, vals);
	file << str.c_str();
}

/**
 * @brief Append data to file, EOL-defined
 *
 * @param[in] float[] data to be appended to file
 * @param[in] int number of values to parse
 * @param[in] int append newline to end of data, 1 for yes 0 for no
 */
void
logger::appendData(float data[], int vals, int newLine){
	if (!state) {
		return;
	}
	std::string str = csvformat(data, vals, newLine);
	file << str.c_str();
}

/**
 * @brief Append data to file, EOL-defined
 *
 * @param[in] int[] data to be appended to file
 * @param[in] int number of values to parse
 * @param[in] int append newline to end of data, 1 for yes 0 for no
 */
void
logger::appendData(int data[], int vals, int newLine){
	if (!state) {
		return;
	}
	std::string str = csvformat(data, vals, newLine);
	file << str.c_str();
}

/**
 * @brief Append data to file, EOL-defined
 *
 * @param[in] long[] timestamp to be appended to file
 * @param[in] int number of values to parse
 * @param[in] int append newline to end of data, 1 for yes 0 for no
 */
void
logger::appendData(long time[], int vals, int newLine){
	if (!state) {
		return;
	}
	std::string str = csvformat(time, newLine);
	file << str.c_str();
}

/**
 * @brief Append newline to file
 */
void
logger::newLine(){
	if (!state) {
		return;
	}
	file << '\n';
}
