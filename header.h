#ifndef TASKS_H
#define TASKS_H

#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>
#include <numeric>
#include <climits>
#include <functional>
#include <iomanip>
#include <cmath>

using std::cout;
using std::endl;
using std::cin;
using std::vector;
using std::map;
using std::pair;
using std::string;
using std::getline;
using std::accumulate;
using std::max;
using std::istringstream;
using std::setw;
using SolutionVector = vector<vector<int>>;

// Функция ввода
void Input_data(vector<int>& wires, vector<int>& task, int& minRemainder);

// Функция вывода результата
void Output_solution(vector<vector<int>>& solution);

/// <summary>
/// Функция компактной конвертации числа в строку
/// </summary>
/// <param name="s">- десятичное число умноженное на 1000</param>
/// <returns></returns>
string num_to_str(int s);

/// <summary>
/// Функция вывода вектора проводов в консоль
/// </summary>
/// <param name="vector">- множество проводов (в виде вектора)</param>
/// <param name="caption">- наименование множества</param>
void printVector(const vector<int> vector, string caption = "Провода");


#endif