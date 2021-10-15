#include "Globals.h"
#include "Application.h"
#include "ModuleMenu.h"
#include "Primitive.h"
#include <Windows.h>


ModuleMenu::ModuleMenu(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleMenu::~ModuleMenu()
{}

// Load assets
bool ModuleMenu::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui::StyleColorsDark();
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
	ImGui_ImplOpenGL2_Init();

	return ret;
}

// Load assets
bool ModuleMenu::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleMenu::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

    // Menu
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            //ShowExampleMenuFile();
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View"))
        {
            ImGui::MenuItem("Configuration", NULL, &show_app_main_menu_bar);
            
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help"))
        {
            ImGui::MenuItem("About", NULL, &about_us);
            //ImGui::MenuItem("Style Editor", NULL, &show_app_style_editor);
            ImGui::MenuItem("About ImGui", NULL, &show_app_about);
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    if (show_app_main_menu_bar)
    {
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.

               
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Configuration");                          // Create a window called "Hello, world!" and append into it.

        //ImGui::Text("ManyoEngineCP");               // Display some text (you can use a format strings too)
        //ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
        //ImGui::Checkbox("Another Window", &show_another_window);

        //ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        //ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        //ImGui::Checkbox("Debug Window", &show_debug_window);
        //if (ImGui::Button("Close Engine"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        //    return UPDATE_STOP;



        //if (ImGui::IsAnyItemHovered)
        //    ImGui::SetTooltip("Restart to apply");


        //ImGui::SameLine();
        //if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        //    counter++;
        //ImGui::SameLine();
        //ImGui::Text("counter = %d", counter);


        //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Text("options");

        if (ImGui::CollapsingHeader("Application"))
        {
            int fps = last_fps;
            int ms = last_ms;
            //Get frames
            if (fps_log.size() > 100) //Max seconds to show
            {
                for (size_t i = 1; i < fps_log.size(); i++)
                {
                    fps_log[i - 1] = fps_log[i];
                    //ms_log[i - 1] = ms_log[i];
                }
                fps_log[fps_log.size() - 1] = fps;
                //ms_log[ms_log.size() - 1] = fps;
            }
            else
            {
                fps_log.push_back(fps);
                //ms_log.push_back(fps);
            }

            char title[25];
            sprintf_s(title, 25, "Framerate %.1f", fps_log[fps_log.size() - 1]);
            ImGui::PlotHistogram("##framerate", &fps_log[0], fps_log.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
            /*sprintf_s(title, 25, "Milliseconds %.0.1f", ms_log[ms_log.size() - 1]);
            ImGui::PlotHistogram("##milliseconds", &ms_log[0], ms_log.size(), 0, title, 0.0f, 40.0f, ImVec2(310, 100));*/


        }
        if (ImGui::CollapsingHeader("Window"))
        {
			//Active
            if (ImGui::Checkbox("Active", &active)) {}


            ImGui::Text("Icon: *default!*");
						
			//Brightness
			static float f=1;
			f = App->window->GetBrightness();
			if (ImGui::SliderFloat("Brightness", &f, 0.0f, 1.0f)) {}
			App->window->SetBrightness(f);

			//Width
			static int i2 = 0;
			if (ImGui::SliderInt("Width", &i2, 0, 4000)) {}


			//Height
			static int i3 = 0;
			if (ImGui::SliderInt("Height", &i3, 0, 2000)) {}


			//FullScreen
            if (ImGui::Checkbox("FullScreen", &fullscreen)) {}
            App->window->SetFullScreen(fullscreen);


            ImGui::SameLine();
            if (ImGui::Checkbox("Resizable", &resizable)) {}
           // App->window->SetResizable(resizable);
        }
        if (ImGui::CollapsingHeader("File System"))
        {

        }
        if (ImGui::CollapsingHeader("Input"))
        {

        }
        if (ImGui::CollapsingHeader("Hardware"))
        {

        }

        ImGui::End();
               

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }
    }
    
    if (about_us) 
    {
        if (ImGui::Begin("About Us", &about_us))
        {
            ImGui::TextWrapped("This is ManyoEngineCp \nThe next Generation 3d Engine \nBy Max Llovera & Arnau Ustrell\n");
            ImGui::TextWrapped("License:\n");
            ImGui::TextWrapped("MIT License\n");
            ImGui::TextWrapped("Copyright (c) 2021 MaxLlovera\n");
            ImGui::TextWrapped("Permission is hereby granted, free of charge, to any person obtaining a copy\nof this software and associated documentation files(the Software), to deal\nin the Software without restriction, including without limitation the rights\nto use, copy, modify, merge, publish, distribute, sublicense, and /or sell\ncopies of the Software, and to permit persons to whom the Software is\nfurnished to do so, subject to the following conditions :\n");
            ImGui::TextWrapped("The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.\n");
            ImGui::TextWrapped("THE SOFTWARE IS PROVIDED AS IS, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.\n");
  
        }
        ImGui::End();
    }

    if (show_app_about)
    {
        ImGui::ShowAboutWindow();
    }

	
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::Render();
	glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
	glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	return UPDATE_CONTINUE;
}