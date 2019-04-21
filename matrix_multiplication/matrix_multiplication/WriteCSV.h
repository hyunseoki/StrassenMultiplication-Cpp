#pragma once
#include <fstream>

std::ofstream MyFile;

void makeFile(const char * filename);

void writeCSV(const char * s);

void closeFile();