#include "FocusMeUI.h"

#include "imgui.h"
#include "timeSet.h"
#include "Log.h"
#include <list>


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
            ImGui::InputInt2("From (Hour:Minute)", start.getTime()); ImGui::SameLine(); ImGui::SameLine();
            if (ImGui::RadioButton("AM##Start", AM == s_meridiem)) { s_meridiem = AM; }; ImGui::SameLine();
            if (ImGui::RadioButton("PM##Start", PM == s_meridiem)) { s_meridiem = PM; };

            //ending time
            ImGui::InputInt2("To (Hour:Minute)", end.getTime()); ImGui::SameLine(); ImGui::SameLine();
            if (ImGui::RadioButton("AM##End", AM == e_meridiem)) { e_meridiem = AM; }; ImGui::SameLine();
            if (ImGui::RadioButton("PM##End", PM == e_meridiem)) { e_meridiem = PM; };

            //button for submitting the time
            if (ImGui::Button("Add 'off' time"))
            {
                //add the time to the list
                times.push_back(TimeSet(start, end));
            }
            
        }
        //end time entry
        

        //time display 
        {
            ImGui::Text("Times program x won't run:");
            //display all times entered by the user
            static TimeSet selected_time = TimeSet(-1, -1); // Here we store our selection data as an pointer.
            
            std::string sel_time_str = "temp";//value doesn't matter
            std::string logString = "log";//value doesn't matter

            static bool clicked = false;//did the user request a time to be removed
            static bool deleted = false;//has an item been deleted, used to avoid a iteration incrment if so

            if (ImGui::BeginListBox("##Timelist"))
            {
                std::list <TimeSet> ::iterator it;
                for (it = times.begin(); it != times.end();)
                {
                    //check if this is currently a selected value
                    const bool is_selected = (selected_time == *it);

                    //get the string of the current iterator value
                    (*it).to_string(sel_time_str);

                    //set the string ID with if it is selected.
                    if (ImGui::Selectable(sel_time_str.c_str(), is_selected))
                    {
                        //set the selected item
                        selected_time = *it;

                        (*it).to_string(logString);
                        g_log << "Selected item " << logString << " bool value: " << is_selected << std::endl;
                    }
                    
                    //don't do anything if the button wasn't clicked
                    if (clicked)
                    {
                        //make sure we are on the selected item
                        if (is_selected)
                        {
                            (*it).to_string(logString);
                            g_log << "Removed item " << logString << " bool value: " << is_selected << std::endl;

                            //remove the item from the list
                            it = times.erase(it);

                            //reset the button
                            clicked = false;
                            deleted = false;

                            //break;
                        }
                        else
                        {
                            //this isn't the correct time in the loop so move onto the next one
                            it++;
                        }
                    }
                    else
                    {
                        //the button wasn't clicked so move onto the next iteration of the loop
                        //when an item is deleted we can't increment the iterater, thus the messy code
                        it++;
                    }

                    // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }

                ImGui::EndListBox();
            }

            //the remove time button
            if (ImGui::Button("Remove Time"))
            {
                clicked = true;
                deleted = true;
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