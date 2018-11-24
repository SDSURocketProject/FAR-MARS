#include "logger.h"
#include "mainwindow.h"

logger::logger(){
    filename = "test.txt";
    state = CLOSED;
}

void logger::setFile(char *newFilename){
    if (state) { mainwindow::showWarningBox("File open. Close before changing file"); return; }
    filename = newFilename;
}

void logger::openFile(){
    if (state) { mainwindow::showWarningBox("File already open. Close before opening again"); return; }
    file.open(filename, std::ios::app);
    state = OPEN;
}

void logger::closeFile(){
    if (!state) { mainwindow::showWarningBox("File already closed"); return; }
    file.close();
    state = CLOSED;
}

int logger::isOpen(){
    return state;
}

void logger::appendData(const char *data){
    if (!state) { mainwindow::showWarningBox("File not open"); return; }
    file << data << '\n';
}

void logger::appendData(const char *data, int newLine){
    if (!state) { mainwindow::showWarningBox("File not open"); return; }
    file << data;
    if (newLine) { file << '\n'; }
}
