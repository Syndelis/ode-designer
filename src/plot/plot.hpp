#ifndef PLOT_HPP
#define PLOT_HPP

#include <implot.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <imgui.h>

using std::vector;
using std::string;

extern bool open_plot;

vector<vector<double>> readCSV_MultidimensionalArray(string);
void plot(vector<vector<double>>, string, string, string);
void PrintTheCSV(vector<vector<double>>);

#endif