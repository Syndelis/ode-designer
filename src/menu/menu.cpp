#include "menu.hpp"

void resetContextMenuState() {
    currentFactory = nullptr;
    nodeName[0]    = '\0';
}

void openContextMenu() {
    isContextMenuOpen = true;
    resetContextMenuState();
}

void renderContextMenu() {

    if (ImGui::BeginPopupContextItem("Create Node")) {

        if (currentFactory) {
            ImGui::Text("New %s", currentNodeName.c_str());
            if (ImGui::InputText(
                    "##nodename", nodeName, MAX_NODE_NAME_LENGTH,
                    ImGuiInputTextFlags_EnterReturnsTrue
                )
                || ImGui::Button("Create"))
            {
                (*currentFactory)(nodeName);
                isContextMenuOpen = false;
                resetContextMenuState();
                ImGui::CloseCurrentPopup();
            }
        }
        else
            for (auto &[nodeName, nodeFactory] : nodeFactories)
                if (ImGui::Selectable(nodeName.c_str())) {
                    currentFactory    = &nodeFactory;
                    currentNodeName   = nodeName;
                    isContextMenuOpen = true;
                }
        ImGui::EndPopup();
    }

    /*else if (simulate){
    }*/
    if (isContextMenuOpen) {

        ImGui::OpenPopup("Create Node");
    }
}

void menuOpenfile() {
    // File open
    auto f = pfd::open_file(
        "Choose file", ".", { "Files (.json)", "*.json" },
        pfd::opt::none
    );
}

void menuSavefile() {
    // File save
    auto f = pfd::save_file(
        "Choose file to save",
        //pfd::path:: + pfd::path::separator() + ".json",
        ".",
        { "Files (.json)", "*.json" }, pfd::opt::force_overwrite
    );
}

void menuBarFile() {

    if (ImGui::MenuItem("New")) {
    }
    if (ImGui::MenuItem("Open", "Ctrl+O")) {

        menuOpenfile();
    }    
    if (ImGui::MenuItem("Save", "Ctrl+S")) {
        menuSavefile();
    }
    if (ImGui::MenuItem("Save As..")) {
        menuSavefile();
    }
    if (ImGui::MenuItem("Plot CSV file")) {

        auto selection = pfd::open_file(
            "Choose file", "~", { "Files (.csv)", "*.csv"},
            pfd::opt::multiselect
        ).result();

        //to do: create submenu with some options?

        if (selection.empty() == false) {
            //plots is global
            clearPlotData();
            for (std::string fname: selection){
                plots.push_back(loadData(fname));
            }
            for (int i = 0; i < plots.size(); i++){
                plots[i].xlabel = "time (days)";
                plots[i].ylabel = "conc/ml";
            }          
            plot_layout.rows = 2;
            plot_layout.cols = 2;
            initializePlot(plots[0].num_of_cols, (float)plot_layout.rows*plot_layout.cols);   
            plot_all = false;
            flag_simulation = false;
        }
    }

    if (ImGui::MenuItem("Plot CSV file (All populations)")) {

        auto selection = pfd::open_file(
            "Choose file", "~", { "Files (.csv)", "*.csv"},
            pfd::opt::none
        ).result();

        if (selection.empty() == false) {            
            //plots is global
            clearPlotData();
            plots.push_back(loadData(selection[0]));
            plots[0].xlabel = "time (days)";
            plots[0].ylabel = "conc/ml";

            plot_layout.rows = 2;
            plot_layout.cols = 2;
            initializePlot(1, plot_layout.rows*plot_layout.cols); 
            plot_all = true;  
            flag_simulation = false;
        }
    }
}

void odesystem(const std::vector<double> &u, std::vector<double> &dudt, const double t){
    double r = params[0];
    double a = params[1];
    double m = params[2];
    double H = u[0], P = u[1];
    dudt[0] = r*H - a*H*P;
    dudt[1] = a*H*P - m*P;
    dudt[2] = 1;
    dudt[3] = 1;
}

void menuBarEdit() {
       
    if (ImGui::BeginMenu("Generate Code")) {

        //Save the values in Json 
        static float ti, tf, dt; 
        ImGui::InputFloat("t initial", &ti);
        ImGui::InputFloat("t final", &tf);
        ImGui::InputFloat("dt", &dt);

        if (ImGui::BeginMenu("Export_Codes")) {
            if (ImGui::Button("Python")) {
            }
            if (ImGui::Button("C++")) {
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Simulate Model")) {        
        static float ti, tf, dt; 
        ImGui::InputFloat("t initial", &ti);
        ImGui::InputFloat("t final", &tf);
        ImGui::InputFloat("dt", &dt);
        
        if (ImGui::Button("Simulate")){
            //to do: In Rust, read model information from expression tree 
            //teste if information was read
            params = {0.05,0.005,0.1};
            std::vector<std::string> names = {"H", "P", "T1", "T2"};
            ode = new ODE(ti,tf,dt,"results.csv",names,odesystem);
            ode->initializeSolver({50,5,1,1});
            ode->t = ode->ti + ode->dt;

            clearPlotData();

            PlotInfo plot;
            for (double time = ode->ti; time < ode->tf; time += ode->dt) {
                plot.time_data.push_back(time);
            }
            plot.num_of_cols = ode->u.size();
            plot.num_of_lines = 1;
            plot.data.reserve(plot.num_of_cols);
            plot.data.resize(plot.num_of_cols);
            for (int i = 0; i < plot.num_of_cols; i++)
                plot.data[i].push_back(ode->u[i]);
            plot.xlabel = "time (days)";
            plot.ylabel = "conc/ml";
            plot.labels = names;
            plots.push_back(plot);

            plot_layout.rows = 2;
            plot_layout.cols = 2;
            initializePlot(plots[0].num_of_cols, (float)plot_layout.rows*plot_layout.cols);
            plot_all = false;
            flag_simulation = true;
        }

        ImGui::EndMenu();
    }
}