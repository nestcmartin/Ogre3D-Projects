#include "Widget.h"
#include "OgreImGuiOverlay.h"
#include "GraphicsEngine/Graphics.h"
#include "OgreRoot.h"

Widget::Widget(const char* name, bool opened,
    float x, float y, float w, float h, 
    bool title, bool scroll, bool menu, 
    bool move, bool resize, bool collapse, 
    bool nav, bool background, bool front) :
    name_(name), opened_(&opened),
    x_(x), y_(y), w_(w), h_(h),
    has_titlebar(title),
    has_scrollbar(scroll),
    has_menu(menu),
    has_move(move),
    has_resize(resize),
    has_collapse(collapse),
    has_nav(nav),
    has_background(background),
    has_bring_to_front(front),
    flags_(0)

{
    if (!has_titlebar)        flags_ |= ImGuiWindowFlags_NoTitleBar;
    if (!has_scrollbar)       flags_ |= ImGuiWindowFlags_NoScrollbar;
    if (has_menu)             flags_ |= ImGuiWindowFlags_MenuBar;
    if (!has_move)            flags_ |= ImGuiWindowFlags_NoMove;
    if (!has_resize)          flags_ |= ImGuiWindowFlags_NoResize;
    if (!has_collapse)        flags_ |= ImGuiWindowFlags_NoCollapse;
    if (!has_nav)             flags_ |= ImGuiWindowFlags_NoNav;
    if (!has_background)      flags_ |= ImGuiWindowFlags_NoBackground;
    if (!has_bring_to_front)  flags_ |= ImGuiWindowFlags_NoBringToFrontOnFocus;
    if (!&opened_)            opened_ = NULL;
}

void Widget::show()
{
    ImGui::SetNextWindowPos(ImVec2(x_, y_));
    ImGui::SetNextWindowSize(ImVec2(w_, h_));
    if (!ImGui::Begin(name_.c_str(), opened_, flags_))
    {
        ImGui::End();
        return;
    }
    ImGui::End();
}

void FPSCounterWidget::show()
{
    ImGuiIO& io = ImGui::GetIO();

    if (corner != -1)
    {
        ImVec2 window_pos = ImVec2((corner & 1) ? io.DisplaySize.x - DISTANCE : DISTANCE, (corner & 2) ? io.DisplaySize.y - DISTANCE : DISTANCE);
        ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
        ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
    }

    ImGui::SetNextWindowBgAlpha(0.35f);

    if (ImGui::Begin(name_.c_str(), opened_, (corner != -1 ?
        ImGuiWindowFlags_NoMove : 0) |
        ImGuiWindowFlags_NoDecoration |
        ImGuiWindowFlags_AlwaysAutoResize |
        ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoFocusOnAppearing |
        ImGuiWindowFlags_NoNav))
    {
        ImGui::Text("Frames per second based in\n" "the rendering engine loop");
        ImGui::Separator();
        std::string msg = "FPS: " + std::to_string(Graphics::FPS).substr(0, (std::to_string(Graphics::FPS).find(".") + 1) + 1);;
        ImGui::Text(msg.c_str());
        if (ImGui::BeginPopupContextWindow())
        {
            if (ImGui::MenuItem("Custom", NULL, corner == -1)) corner = -1;
            if (ImGui::MenuItem("Top-left", NULL, corner == 0)) corner = 0;
            if (ImGui::MenuItem("Top-right", NULL, corner == 1)) corner = 1;
            if (ImGui::MenuItem("Bottom-left", NULL, corner == 2)) corner = 2;
            if (ImGui::MenuItem("Bottom-right", NULL, corner == 3)) corner = 3;
            ImGui::EndPopup();
        }
    }
    ImGui::End();
}
