#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <iostream>

#include "csv.h"

class logger{
public:
	logger();
	void appendData(float[], int);
	void appendData(float[], int, int);
	void appendData(int[], int);
	void appendData(int[], int, int);
	void appendData(long[], int, int);
	void closeFile(void);
	int  isOpen(void);
	void newLine(void);
	void openFile(void);
	void setFile(const char*);
private:
	std::ofstream file;
	char *filename;
	int state;
	enum states {
		OPEN = 1,
		CLOSED = 0
	};
};

#endif // LOGGER_H
