#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <iostream>
#include "csv.h"

class logger{
public:
    logger();
    void appendData(float data[], int vals);
    void appendData(float data[], int vals, int newLine);
    void appendData(int data[], int vals, int newLine);
    void appendData(long time[], int vals, int newLine);
    void closeFile();
    int  isOpen();
    void newLine();
    void openFile();
    void setFile(const char *newfilename);
private:
    std::ofstream file;
    char *filename;
    int state;
    enum states { OPEN = 1, CLOSED = 0 };
};

#endif // LOGGER_H
