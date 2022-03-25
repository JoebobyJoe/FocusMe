#include "FocusMeUI.h"

#include "imgui.h"
#include "timeSet.h"

#include <vector>


namespace FocusMeUI
{
    //list of times that the user doesn't want to use program x
    std::vector<TimeSet>times;

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
            static int clicked = 0;
            if (ImGui::Button("Add 'off' time"))
                clicked = 1;
            if (clicked == 1)
            {
                //add the time to the list
                times.push_back(TimeSet(start, end));

                //reset the button, otherwise every frame adds the time
                clicked = 0;
            }
            
        }
        //end time entry
        

        //time display 
        {
            static int clicked = 0;
            

            ImGui::Text("Times program x won't run:");
            
            //display all times entered by the user
            static TimeSet selected_time = TimeSet(-1, -1); // Here we store our selection data as an index.
            static bool deleted = false;
            if (ImGui::BeginListBox("##Timelist"))
            {
                std::vector <TimeSet> ::iterator it;
                for (it = times.begin(); it != times.end();)
                //for (i = 0; i <= times.size(); i++)
                {
                    //check to see if the selected item is highlighted
                    const bool is_selected = (selected_time == *it);

                    //highlight the selected item in the listbox
                    if (ImGui::Selectable((*it).toString().c_str(), is_selected))
                    {
                        //set the selected_time to the the item we clicked
                        selected_time = *it;
                        
                        //don't do anything if the button wasn't clicked
                        if (clicked == 1)
                        {
                            //remove the item from the list
                            it = times.erase(it);
                            deleted = true;

                            //this might be the solution to multiple blocks being highlighted when times are the same
                            //break;

                            
                        }
                    }

                    //remove the correct element from the list
                    if (deleted)
                    {
                        //reset deleted
                        deleted = false;
                        clicked = 0;

                    }
                    else
                    {
                        //we didn't delete anything so we can increment the itterator
                        //if we delete we cannot increment
                        it++;
                    }

                    // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }

                ImGui::EndListBox();
            }

            if (ImGui::Button("Remove Time"))
                clicked = 1;

             
            
            //working list
            std::vector<const char*>tempList;
            tempList.push_back("AAAA");
            tempList.push_back("BBBB");
            tempList.push_back("CCCC");
            tempList.push_back("DDDD");
            tempList.push_back("EEEE");
            tempList.push_back("FFFF");

            
            static const char* item_current_idx = nullptr; // Here we store our selection data as an POINTER.
            if (ImGui::BeginListBox("listbox 1"))
            {
                std::vector <const char*> ::iterator it;
                for (it = tempList.begin(); it != tempList.end(); it++)
                {
                    const bool is_selected = (item_current_idx == *it);
                    if (ImGui::Selectable((*it), is_selected))
                        item_current_idx = *it;

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