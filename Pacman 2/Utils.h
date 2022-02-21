#ifndef UTILS_H_
#define UTILS_H_

#include "Color.h"
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <string>
#include <ctype.h>
#include <typeinfo>
#include <queue>
#include <string>
#include <stack>
#include <fstream>
#include <sstream>
#include <filesystem>

using std::cout;
using std::endl;
using std::flush;
using std::cin;
using std::ifstream;
using std::fstream;
using std::string;
using std::stringstream;
using std::queue;
using std::stack;
using std::vector;

void gotoxy(int x, int y);
void setTextColor(Color);
void hideCursor();
void clear_screen();
int myRand(const int a, const int b);

#endif