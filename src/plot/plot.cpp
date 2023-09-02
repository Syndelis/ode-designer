#include "imgui.h"
#include "implot.h"
#include "plot.hpp"
#include <cstddef>
#include <endian.h>
#include <fstream>

bool open_plot = false;

// vector<vector<double>> readCSV_MultidimensionalArray(string fname) {
//     vector<vector<double>> data;
//     ifstream file(fname);
//     string line = "";
//     while (getline(file, line)) {
//         vector<double> vec;
//         stringstream ss(line);
//         string cell = "";
//         while (getline(ss, cell, ',')) {
//             vec.push_back(stod(cell));
//         }
//         data.push_back(vec);
//     }
//     return data;
// }

// void plot(vector<vector<double>> data, string title, string x_label, string y_label) {
// //     ImPlot::SetNextPlotLimits(0, 1, 0, 1, ImGuiCond_Always);
// //     if (ImPlot::BeginPlot(title.c_str(), x_label.c_str(), y_label.c_str())) {
// //         for (int i = 0; i < data.size(); i++) {
// //             ImPlot::PlotLine(data[i].data(), data[i].size());
// //         }
// //         ImPlot::EndPlot();
// //     }
// // }

vector<vector<double>> readCSV_MultidimensionalArray(string fname){

    std::ifstream f(fname);
    string line, val;                  /* string for line & value */
    vector<vector<double>> array;    /* vector of vector<int>  */

    while (getline (f, line)) {        /* read each line */
        vector<double> v;                 /* row vector v */
        std::stringstream s (line);         /* stringstream line */
        while (getline (s, val, ','))       /* get each value (',' delimited) */
            v.push_back (stod (val));  /* add to row vector */
        array.push_back (v);                /* add row vector to array */
    }
    return array;
}

void plot(vector<vector<double>> data, string title, string x_label, string y_label){

    // if (ImGui::Begin("Style Editor (ImGui)", NULL)){
       
    //     if(ImPlot::BeginPlot(title.c_str())){
    //         cout << "Plotting" << endl;
    //         ImPlot::SetupAxes(x_label.c_str(), y_label.c_str());
    //         std::size_t S = data.size();
    //         double p[S], times[S];
    //         for (std::size_t i = 0; i < S; i++){
    //             p[i] = data[i][1];
    //             times[i] = data[i][0];
    //         }
            
    //         ImPlot::PlotLine("V",times,p,(int)S);
    //         ImPlot::EndPlot();
    //     }
    //     ImGui::End();
    // }
    std::cout << open_plot << std::endl;
    ImGui::OpenPopup("Plot");
    ImGui::SetNextWindowSize(ImVec2(800, 600));
     if (ImGui::BeginPopupModal("Plot")){
           if(ImPlot::BeginPlot(title.c_str())){
            ImPlot::SetupAxes(x_label.c_str(), y_label.c_str());
            std::size_t S = data.size();
            double p[S], times[S];
            for (std::size_t i = 0; i < S; i++){
                p[i] = data[i][1];
                times[i] = data[i][0];
            }
            
            ImPlot::PlotLine("V",times,p,(int)S);
            ImPlot::EndPlot();
        }
        ImGui::EndPopup();
    }
    //if (open_plot) {
        
    //}
}

void PrintTheCSV(vector<vector<double>> data){
   
    // for (int i = 0; i < (int)data.size(); i++){
    //         cout << data.at(i)<<data.at(j) << " ";
    //     cout << endl;
    // }
}

// for (int i = 0; i < (int)array.size(); i++){
//         for (int j = 0; j < (int)array.at(i).size(); j++)


// void plot(std::vector<double> times, int id, std::string vname, std::string fname){
//     std::vector<std::string> colors = {"Green","Purple", "IndianRed", "Aqua", "Aquamarine", "Azure", "Beige", "Bisque", "Black", "BlanchedAlmond", "Blue"};    
//     std::vector<std::vector<double>> data = readCSV_to_MultidimensionalArray(fname, false);
//     std::vector<double> col;
//     for (auto& row: data){    
//         col.push_back(row.at(id));    
//     }
//     assert(times.size() == col.size());
       
//     plt::figure_size(1200, 780);
//     plt::xlabel("days");
//     plt::plot(times, col, { {"label", vname}, {"color",colors[(id-1)%colors.size()]}, {"linewidth", "2"}});
//     plt::legend();
   
//     stringstream ss;
//     ss << "figs/" << vname << "_plot.png";
//     plt::save(ss.str());
//     ss.str("");
// }