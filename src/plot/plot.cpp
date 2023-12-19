#include "imgui.h"
#include "implot.h"
#include <algorithm>
#include <cstddef>
#include <endian.h>
#include <fstream>
#include <iterator>
#include <string>
#include <math.h>

using namespace std;

#include "plot.hpp"

bool plot_all = false;
PlotLayout plot_layout;
std::vector<PlotInfo> plots;

std::vector<ImVec4> colors ={ImVec4(0.98,0.027,0.027,1), //vermelha
                            ImVec4(0.09,0.027,0.98,1), //azul
                            ImVec4(0.027,0.98,0.12,1), //verde claro
                            ImVec4(0.96,0.98,0.027,1), //amarelo
                            ImVec4(0.5,0.,1,1), //roxo
                            ImVec4(1,0.5,0.,1), //laranja
                            ImVec4(0.2,1,1,1), //ciano
                            ImVec4(1,0.2,0.6,1), //rosa
                            ImVec4(0.4,0.7,1,1), //azul claro
                            ImVec4(1,0.4,0.4,1), //vermelho claro                                                        
                            ImVec4(1,0.2,1,1), //magenta                            
                            ImVec4(1,0.7,0.4,1), //laranja claro
                            ImVec4(0.74,0.055,0.055,1),
                            ImVec4(0.6,0.298,0.,1)};
                            //ImVec4(0.1,0.4,0.1,1), //verde escuro 

void clearPlotData(){
    //plot is global
    for (PlotInfo plot: plots){
        for (std::vector<double> v: plot.data) {
            v.clear();
        }
        plot.data.clear();
        plot.time_data.clear();
        plot.labels.clear();
    }
    plots.clear();
}

//return the table's headings 
std::vector<std::string> readColumnNames(std::string fname){
    std::ifstream f(fname);
    std::string line, val;
    std::getline(f,line); 
    std::stringstream s (line);
    std::vector<std::string> labels;
    while (getline (s, val, ',')) 
        labels.push_back(val);
    labels.erase(labels.begin() + 0);
    f.close();
    return labels;
}

std::vector<std::vector<double>> readCSV_MultidimensionalArray(std::string fname){ 
    std::vector<std::vector<double>> data;   
    std::ifstream f(fname);
    std::string line, val;
    std::getline(f,line); 

    while (getline (f, line)) {        /* read each line */
        std::vector<double> v;                 /* row vector v */
        std::stringstream s (line);         /* stringstream line */
        while (getline (s, val, ','))       /* get each value (',' delimited) */
            v.push_back (stod (val));  /* add to row vector */
        data.push_back (v);                /* add row vector to array */
    }
    f.close();
    return data;
}

PlotInfo loadData(std::string fname) {
    PlotInfo plot;
    plot.labels = readColumnNames(fname);
    std::vector<std::vector<double>> data = readCSV_MultidimensionalArray(fname);
    
    plot.num_of_lines = data.size();
    plot.num_of_cols = data[0].size()-1;

    plot.time_data.reserve(plot.num_of_lines);
    plot.time_data.resize(plot.num_of_lines);
    for (std::size_t i = 0; i < plot.num_of_lines; i++)
        plot.time_data[i] = data[i][0];

    plot.data.reserve(plot.num_of_cols);
    plot.data.resize(plot.num_of_cols);
    for (std::size_t j = 0; j < plot.num_of_cols; j++)    
        for (std::size_t i = 0; i < plot.num_of_lines; i++)
            plot.data[j].push_back(data[i][j+1]);

    return plot;
}

void initializePlot(int n, float n_graphs_tab){
    //plot_layout is global
    plot_layout.next_tab_id = 0;
    plot_layout.active_tabs.clear();
    plot_layout.number_of_tabs = ceil((float)n/n_graphs_tab);
    if (plot_layout.number_of_tabs == 0)
        plot_layout.number_of_tabs = 1; 
    for (int i = 0; i < plot_layout.number_of_tabs; i++){
        plot_layout.active_tabs.push_back(plot_layout.next_tab_id++);
    }
    plot_layout.style = ImPlot::GetStyle();
    plot_layout.style.LineWeight = 2.;
}

void plot(PlotInfo plot, PlotLayout plot_layout, unsigned int id){       
    
    if (ImPlot::BeginSubplots(plot.title.c_str(), plot_layout.rows, plot_layout.cols, ImVec2(ImGui::GetWindowSize().x - 50, ImGui::GetWindowSize().y - 50), 
        ImPlotSubplotFlags_None)) {
               
        int color_index = id, colors_size = colors.size();
        for (int i = 0; i < plot_layout.rows*plot_layout.cols; ++i) {
            
            int index = id + i;
            if (index == plot.num_of_cols)
                break;

            const char* label = plot.labels[index].c_str();            
            if(ImPlot::BeginPlot(label)){
                
                ImPlot::SetupAxes(plot.xlabel.c_str(), plot.ylabel.c_str(),ImPlotAxisFlags_AutoFit,ImPlotAxisFlags_AutoFit);
                ImPlot::SetNextLineStyle(colors[color_index%colors_size]);
                color_index++;
                ImPlot::PlotLine(label,plot.time_data.data(),plot.data[index].data(),plot.num_of_lines);

                ImPlot::EndPlot();                
            }
        }

        ImPlot::EndSubplots();
    }
}

void plotDifferentScenarios(std::vector<PlotInfo> plots, PlotLayout plot_layout, unsigned int id){

    if (ImPlot::BeginSubplots(plots[0].title.c_str(), plot_layout.rows, plot_layout.cols, ImVec2(ImGui::GetWindowSize().x - 50, ImGui::GetWindowSize().y - 50), 
        ImPlotSubplotFlags_None)) {    
        
        int colors_size = colors.size();
        for (int i = 0; i < plot_layout.rows*plot_layout.cols; ++i) {    

            int index = id + i;
            if (index == plots[0].num_of_cols)
                break;

            const char *label = plots[0].labels[index].c_str();

            if(ImPlot::BeginPlot(label)){

                ImPlot::SetupAxes(plots[0].xlabel.c_str(), plots[0].ylabel.c_str(),ImPlotAxisFlags_AutoFit,ImPlotAxisFlags_AutoFit);

                for (int k = 0; k < plots.size(); k++){      
                   
                    ImPlot::SetNextLineStyle(colors[k%colors_size]);
                    ImPlot::PlotLine((plots[k].labels[index]+to_string(k)).c_str(),plots[k].time_data.data(),plots[k].data[index].data(),plots[k].num_of_lines);
                }
                                
                ImPlot::EndPlot();                
            }            
        }

        ImPlot::EndSubplots();
    }
}

void plotAll(PlotInfo plot){

    if(ImPlot::BeginPlot(plot.title.c_str(),ImVec2(ImGui::GetWindowSize().x - 50, ImGui::GetWindowSize().y - 50))){

        ImPlot::SetupAxes(plot.xlabel.c_str(), plot.ylabel.c_str(),ImPlotAxisFlags_AutoFit,ImPlotAxisFlags_AutoFit); 

        int color_index = 0, colors_size = colors.size();
        for (size_t i = 0; i < plot.data.size(); i++){

            ImPlot::SetNextLineStyle(colors[color_index%colors_size]);
            color_index++;
            ImPlot::PlotLine(plot.labels[i].c_str(),plot.time_data.data(),plot.data[i].data(),plot.num_of_lines);
        }
        ImPlot::EndPlot();
    }
}