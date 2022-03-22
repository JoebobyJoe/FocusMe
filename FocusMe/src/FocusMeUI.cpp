#include "FocusMeUI.h"

#include "imgui.h"

/*
// Helper to wire demo markers located in code to a interactive browser
typedef void (*ImGuiDemoMarkerCallback)(const char* file, int line, const char* section, void* user_data);
extern ImGuiDemoMarkerCallback  GImGuiDemoMarkerCallback;
extern void* GImGuiDemoMarkerCallbackUserData;
ImGuiDemoMarkerCallback         GImGuiDemoMarkerCallback = NULL;
void* GImGuiDemoMarkerCallbackUserData = NULL;
#define IMGUI_DEMO_MARKER(section)  do { if (GImGuiDemoMarkerCallback != NULL) GImGuiDemoMarkerCallback(__FILE__, __LINE__, section, GImGuiDemoMarkerCallbackUserData); } while (0)
*/

// Helper to display a little (?) mark which shows a tooltip when hovered.
// In your own code you may want to display an actual icon if you are using a merged icon fonts (see docs/FONTS.md)
/*
static void HelpMarker(const char* desc)
{
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}
*/

namespace FocusMeUI
{
	void RenderUI()
	{
        // Our state
        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        //style the windo
        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowMinSize = ImVec2(600, 600);//ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y);
        

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

            static int start_hm[2] = { 10, 30 };
            static int end_hm[2] = { 11, 30 };
            static int am_pm = 0;
            ImGui::InputInt2("Hour: Minute", start_hm); ImGui::SameLine();
            ImGui::RadioButton("AM", &am_pm, 0); ImGui::SameLine();
            ImGui::RadioButton("PM", &am_pm, 1);

            ImGui::InputInt2("Hour: Minute", end_hm); ImGui::SameLine();
            ImGui::RadioButton("AM", &am_pm, 0); ImGui::SameLine();
            ImGui::RadioButton("PM", &am_pm, 1);

            static int clicked = 0;
            if (ImGui::Button("Add 'off' time"))
                clicked++;
            if (clicked & 1)
            {
                ImGui::SameLine();
                ImGui::Text("Time submitted");
            }
        }
        //end time entry
        

        //time display 
        {
            //display all times entered by the user

        }
        //end time display

        
        ImGui::End();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }
	}
}