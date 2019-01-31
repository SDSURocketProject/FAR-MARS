#ifndef CSV_H
#define CSV_H

#include <string>

std::string csvformat(float data[], int vals);
std::string csvformat(float data[], int vals, bool endofline);
std::string csvformat(int data[], int vals, bool endofline);

#endif
