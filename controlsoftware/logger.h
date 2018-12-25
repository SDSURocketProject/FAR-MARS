#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include "csv.h"

class logger{
public:
    logger();
    void setFile(char *newfilename);
    void openFile();
    void closeFile();
    int  isOpen();
    void appendData(int data[], int vals);
    void appendData(int data[], int vals, int newLine);
    void newLine();
private:
    std::ofstream file;
    char *filename;
    int state;
    enum states { OPEN = 1, CLOSED = 0 };
};

#endif // LOGGER_H
