#include "FocusMeUI.h"

#include "imgui.h"
#include "timeSet.h"
//#include "time.h"
#include <list>

enum time
{
    AM,
    PM
};

namespace FocusMeUI
{
    //list of times that the user doesn't want to use program x
    std::list<TimeSet>times;

	void RenderUI()
	{
        // Our state
        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        //style the window
        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowMinSize = ImVec2(700, 700);//ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y);
        

        ImGui::Begin("Settings", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

        ImGui::Text("Select the program you want to create restrictions for:");

        //drop down menu for programs
        ImGui::Separator();
        //ImGui::LabelText("label", "Value");
        {
            //list of all the programs on the computers
            const char* programs[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIIIIII", "JJJJ", "KKKKKKK" };

            //the selected program by the user
            static int selected_program = 0;
            ImGui::Combo("Program List", &selected_program, programs, IM_ARRAYSIZE(programs));
            //ImGui::SameLine(); 
            //HelpMarker("Using the simplified one-liner Combo API here.\nRefer to the \"Combo\" section below for an explanation of how to use the more flexible and general BeginCombo/EndCombo API.");
        }
        //end drop down menu

        //time entry
        {
            ImGui::Text("What time should this program not be used?");

            //variables
            static Time start = Time(), end = Time();

            //starting time
            static int s_meridiem = 0, e_meridiem = 0;
            ImGui::InputInt2("From (Hour:Minute)", start.getTime()); ImGui::SameLine();
            if (ImGui::RadioButton("AM##Start", AM == s_meridiem)) { s_meridiem = AM; }; ImGui::SameLine();
            if (ImGui::RadioButton("PM##Start", PM == s_meridiem)) { s_meridiem = PM; };

            //ending time
            ImGui::InputInt2("To (Hour:Minute)", end.getTime()); ImGui::SameLine();
            if (ImGui::RadioButton("AM##End", AM == e_meridiem)) { e_meridiem = AM; }; ImGui::SameLine();
            if (ImGui::RadioButton("PM##End", PM == e_meridiem)) { e_meridiem = PM; };

    

            static int clicked = 0;
            if (ImGui::Button("Add 'off' time"))
                clicked = 1;
            if (clicked == 1)
            {
                ImGui::SameLine();
                ImGui::Text("Time submitted");

                times.push_back(TimeSet(start, end));
                clicked = 0;
            }
            
        }
        //end time entry
        

        //time display 
        {
            //display all times entered by the user
            static TimeSet selected_time = TimeSet(-1, -1); // Here we store our selection data as an index.
            if (ImGui::BeginListBox("Times for program x"))
            {
                std::list <TimeSet> ::iterator it;
                for (it = times.begin(); it != times.end(); it++)
                {
                    const bool is_selected = (selected_time == *it);
                    if (ImGui::Selectable((*it).toString().c_str(), is_selected))
                    {
                        static int clicked = 0;
                        if (ImGui::Button("Remove Time"))
                            clicked = 1;
                        if (clicked == 1)
                        {
                            ImGui::SameLine();
                            ImGui::Text("Time removed");

                            //times.remove(*it);
                            clicked = 0;
                        }
                    }
                        //selected_time = *it;

                    // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }

                

                ImGui::EndListBox();
            }
        }
        //end time display

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);
	}
}