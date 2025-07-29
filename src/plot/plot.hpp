#ifndef PLOT_HPP
#define PLOT_HPP

#include "implot.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <imgui.h>

using namespace std;

using PlotInfo = struct TPlotInfo {        
    int num_of_lines;
    int num_of_cols;
    std::vector<std::string> labels;
    std::string title{""};
    std::string xlabel;
    std::string ylabel;
    std::vector<std::vector<double>> data;
    std::vector<double> time_data;
};

using PlotLayout = struct TPlotLayout {
    int rows; 
    int cols;
    int next_tab_id = 0;
    int number_of_tabs;
    ImVector<int> active_tabs;     
    ImPlotStyle style;
};

extern bool plot_all; 
extern std::vector<PlotInfo> plots;
extern PlotLayout plot_layout;
extern std::vector<ImVec4> colors;

void clearPlotData();

void initializePlot(int, float);

PlotInfo loadData(std::string);

void plot(PlotInfo, PlotLayout, unsigned int);

void plotAll(PlotInfo);

void plotDifferentScenarios(std::vector<PlotInfo>, PlotLayout, unsigned int);

#endif // PLOT_HPP