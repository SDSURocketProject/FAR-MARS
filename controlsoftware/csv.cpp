/**
 * CSV Formatting functions
 */

#include "csv.h"

/**
 * Format floats as csv with no newline
 *
 * @since v0.2.0
 * @param float[] floats to format
 * @param int number of values to process
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
 * Format integers as csv with no newline
 *
 * @since v0.3.2
 * @param int[] integers to format
 * @param int number of values to process
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
 * Format floats as csv with no newline
 *
 * @since v0.3.2
 * @param float[] integers to format
 * @param int number of values to process
 * @param bool whether to append newline
 * @return csv formatted string
 */
std::string
csvformat(float data[], int vals, bool newline){
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
 * Format integers as csv with no newline
 *
 * @since v0.2.0
 * @param int[] integers to format
 * @param int number of values to process
 * @param bool whether to append newline
 * @return csv formatted string
 */
std::string
csvformat(int data[], int vals, bool newline){
	std::string csv = csvformat(data, vals);
	if (newline){
		csv.append("\n");
	}
	else {
		csv.append(",");
	}
	return csv;
}
