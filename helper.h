#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <ctime>
#include "main.h"
using namespace std;

string getDateAndTime();
vector<string> split(const string &s, char delim);
string readFile(string path);
void writeFile(string path, string data);
int getValue(string settings, string value);
void readConfig(string path, config &cfg);