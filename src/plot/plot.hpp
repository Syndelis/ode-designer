#ifndef PLOT_HPP
#define PLOT_HPP

#include <imgui.h>
#include <implot.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::string;
using std::vector;

extern bool open_plot;

extern vector<vector<double>> plot_data;

vector<vector<double>> readCSV_MultidimensionalArray(string);

void plot(vector<vector<double>>, string, string, string);

void PrintTheCSV(vector<vector<double>>);

#endif // PLOT_HPP