/**
 * CSV Formatting functions
 */

#include "csv.h"

/**
 * @brief Format floats as csv with no newline
 *
 * @since v0.2.0
 * @param[in] float[] floats to format
 * @param[in] int number of values to process
 * @return csv formatted string
 */
std::string
csvformat(float data[], int vals){
	std::string csv;
	int items = vals;
	for (int i = 0; i < items; i++){
		char buf[100];
		sprintf(buf, "%f", data[i]);
		std::string str(buf);
		csv.append(str);
		if (i < items-1){
			csv.append(",");
		}
	}
	return csv;
}

/**
 * @brief Format longs as csv with no newline
 *
 * @since v0.5.0
 * @param[in] long[] longs to format
 * @param[in] int number of values to process
 * @return csv formatted string
 */
std::string
csvformat(long data[], int vals){
	std::string csv;
	int items = vals;
	for (int i = 0; i < items; i++){
		char buf[100];
		sprintf(buf, "%ld", data[i]);
		std::string str(buf);
		csv.append(str);
		if (i < items-1){
			csv.append(",");
		}
	}
	return csv;
}

/**
 * @brief Format integers as csv with no newline
 *
 * @since v0.3.2
 * @param[in] int[] integers to format
 * @param[in] int number of values to process
 * @return csv formatted string
 */
std::string
csvformat(int data[], int vals){
	std::string csv;
	int items = vals;
	for (int i = 0; i < items; i++){
		char buf[100];
		sprintf(buf, "%d", data[i]);
		std::string str(buf);
		csv.append(str);
		if (i < items-1){
			csv.append(",");
		}
	}
	return csv;
}


/**
 * @brief Format floats as csv with optional newline
 *
 * @since v0.3.2
 * @param[in] float[] floats to format
 * @param[in] int number of values to process
 * @param[in] int whether to append newline
 * @return csv formatted string
 */
std::string
csvformat(float data[], int vals, int newline){
	std::string csv = csvformat(data, vals);
	if (newline){
		csv.append("\n");
	}
	else {
		csv.append(",");
	}
	return csv;
}

/**
 * @brief Format long as csv with optional newline
 *
 * @since v0.5.0
 * @param[in] long long to format
 * @param[in] int number of values to process
 * @param[in] int whether to append newline
 * @return csv formatted string
 */
std::string
csvformat(long data[], int vals, int newline){
	std::string csv = csvformat(data, vals);
	if (newline){
		csv.append("\n");
	}
	else {
		csv.append(",");
	}
	return csv;
}

/**
 * @brief Format integers as csv with no newline
 *
 * @since v0.2.0
 * @param[in] int[] integers to format
 * @param[in] int number of values to process
 * @param[in] int whether to append newline
 * @return csv formatted string
 */
std::string
csvformat(int data[], int vals, int newline){
	std::string csv = csvformat(data, vals);
	if (newline){
		csv.append("\n");
	}
	else {
		csv.append(",");
	}
	return csv;
}
