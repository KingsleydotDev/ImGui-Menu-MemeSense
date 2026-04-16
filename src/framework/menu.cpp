#include "menu.h"
#include "var.h"
#include "custom_settings.h"
#include "custom_imgui.h"
#include "flowstrip.h"
#include "imgui.h"
#include "../../ext/fonts/fonts.h"
#include "pages/pagelegitbot.h"
#include "pages/pageaimassist.h"
#include "pages/pageplayers.h"
#include "pages/pagechams.h"
#include "pages/pageitems.h"
#include "pages/pagevisuals.h"
#include "pages/pageworld.h"
#include "pages/pageview.h"
#include "pages/pageindicators.h"
#include "pages/pagemiscellaneous.h"
#include "pages/pageinventory.h"
#include "pages/pageconfigs.h"
#include "pages/pagedefault.h"
#include "../../ext/fonts/iconsfontawesome/fa.h"
#include "../../ext/fonts/iconsfontawesome/IconsFontAwesome7.h"

namespace
{
ImFont* defaultFont = nullptr;
ImFont* titleFont = nullptr;
ImFont* sidebarFont = nullptr;
ImFont* awesomeFont = nullptr;
float dpiScale = 1.f;
bool areFontsReady = false;

void EnsureFontsLoaded()
{
    if (areFontsReady)
    {
        return;
    }

    ImGuiIO& io = ImGui::GetIO();
    ImFontConfig fontConfig;
    fontConfig.FontDataOwnedByAtlas = false;
    defaultFont = io.Fonts->AddFontFromMemoryTTF((void*)RubikSemiBold, sizeof(RubikSemiBold), MenuSettings::fDefaultTextSize * dpiScale, &fontConfig, io.Fonts->GetGlyphRangesDefault());
    titleFont = io.Fonts->AddFontFromMemoryTTF((void*)RubikSemiBold, sizeof(RubikSemiBold), MenuSettings::fTitleTextSize * dpiScale, &fontConfig, io.Fonts->GetGlyphRangesDefault());
    sidebarFont = io.Fonts->AddFontFromMemoryTTF((void*)RubikSemiBold, sizeof(RubikSemiBold), MenuSettings::fSidebarTextSize * dpiScale, &fontConfig, io.Fonts->GetGlyphRangesDefault());
    static const ImWchar iconRanges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
    awesomeFont = io.Fonts->AddFontFromMemoryTTF((void*)freesolid900, sizeof(freesolid900), MenuSettings::fSidebarTextSize * dpiScale, &fontConfig, iconRanges);
    io.FontDefault = defaultFont;
    io.Fonts->Build();
    areFontsReady = true;
}
}

namespace ksd
{
void Initialize(float dpiValue)
{
    dpiScale = dpiValue;
}

void Render()
{
    EnsureFontsLoaded();
    ksd::SetIconButtonFont(awesomeFont);

    ImGui::PushStyleColor(ImGuiCol_WindowBg, MenuSettings::inactiveColor);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.f, 0.f));
    ImGui::SetNextWindowSize(ImVec2(MenuSettings::fMenuWidth, MenuSettings::fMenuHeight), ImGuiCond_Always);

    const ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse;
    if (ImGui::Begin("menu", &MenuVars::isMenuVisible, windowFlags))
    {
        static const char* const pageNames[] =
        {
            "Legitbot",
            "Aim Assist",
            "Players",
            "Chams",
            "Items",
            "Visuals",
            "World",
            "View",
            "Indicators",
            "Miscellaneous",
            "Inventory",
            "Configs"
        };
        static const char* const pageIcons[] =
        {
            ICON_FA_CROSSHAIRS,
            ICON_FA_COMPUTER_MOUSE,
            ICON_FA_USER,
            ICON_FA_GLASSES,
            ICON_FA_GUN,
            ICON_FA_FIRE,
            ICON_FA_GLOBE,
            ICON_FA_EYE,
            ICON_FA_BARS_STAGGERED,
            ICON_FA_LIST_CHECK,
            ICON_FA_PAINTBRUSH,
            ICON_FA_FOLDER_OPEN
        };
        const int pageCount = (int)(sizeof(pageNames) / sizeof(pageNames[0]));
        if (MenuVars::currentTab < 0)
        {
            MenuVars::currentTab = 0;
        }
        if (MenuVars::currentTab >= pageCount)
        {
            MenuVars::currentTab = pageCount - 1;
        }

        ksd::DrawFlowStrip();

        ImGui::PushStyleColor(ImGuiCol_ChildBg, MenuSettings::inactiveColor);
        ImGui::BeginChild("sidebar", ImVec2(MenuSettings::fSidebarWidth, 0.f), false, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
        ksd::DrawBrandingText(titleFont);
        ImGui::SetCursorPos(ImVec2(0.f, MenuSettings::fFirstButtonY));
        for (int pageIndex = 0; pageIndex < pageCount; ++pageIndex)
        {
            if (ksd::DrawSidebarButton(pageNames[pageIndex], pageIcons[pageIndex], MenuVars::currentTab == pageIndex, sidebarFont, awesomeFont))
            {
                MenuVars::currentTab = pageIndex;
            }
            if (pageIndex + 1 < pageCount)
            {
                if (pageIndex == 1 || pageIndex == 8)
                {
                    ksd::Spacing();
                }
                else
                {
                    ksd::ButtonSpacing();
                }
            }

        }
        ImGui::EndChild();
        ImGui::PopStyleColor();

        ImGui::SameLine(0.f, 0.f);
        ImGui::PushStyleColor(ImGuiCol_ChildBg, MenuSettings::pageColor);
        ImGui::BeginChild("pagecontent", ImVec2(0.f, 0.f), false, ImGuiWindowFlags_NoScrollbar);
        const float fHeadHeight = MenuSettings::fSidebarLineY;
        const float fContentStartX = MenuSettings::fPageContentStartX;
        const float fHeadTextY = MenuSettings::fPageHeadControlY;
        const float fHeadCheckboxY = MenuSettings::fPageHeadControlY;

        ImGui::BeginChild("pagehead", ImVec2(0.f, fHeadHeight), false, ImGuiWindowFlags_NoScrollbar);
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 1.f));
        switch (MenuVars::currentTab)
        {
        case 0:
            ksd::RenderLegitbotPageHead(fContentStartX, fHeadCheckboxY);
            break;
        case 1:
            ksd::RenderAimAssistPageHead(fContentStartX, fHeadCheckboxY);
            break;
        case 2:
            ksd::RenderPlayersPageHead(fContentStartX, fHeadCheckboxY);
            break;
        case 3:
            ksd::RenderChamsPageHead(fContentStartX, fHeadCheckboxY);
            break;
        case 4:
            ksd::RenderItemsPageHead(fContentStartX, fHeadCheckboxY);
            break;
        case 5:
            ksd::RenderVisualsPageHead(fContentStartX, fHeadCheckboxY);
            break;
        case 6:
            ksd::RenderWorldPageHead(fContentStartX, fHeadCheckboxY);
            break;
        case 7:
            ksd::RenderViewPageHead(fContentStartX, fHeadCheckboxY);
            break;
        case 8:
            ksd::RenderIndicatorsPageHead(fContentStartX, fHeadCheckboxY);
            break;
        case 9:
            ksd::RenderMiscellaneousPageHead(fContentStartX, fHeadCheckboxY);
            break;
        case 10:
            ksd::RenderInventoryPageHead(fContentStartX, fHeadCheckboxY);
            break;
        case 11:
            ksd::RenderConfigsPageHead(fContentStartX, fHeadCheckboxY);
            break;
        default:
            ksd::RenderDefaultPageHead(pageNames[MenuVars::currentTab], fContentStartX, fHeadTextY);
            break;
        }
        ImGui::PopStyleColor();
        ImGui::EndChild();

        {
            ImDrawList* pageDrawList = ImGui::GetWindowDrawList();
            const ImVec2 aPageLinePos = ImGui::GetCursorScreenPos();
            const float fPageWidth = ImGui::GetWindowSize().x;
            pageDrawList->AddRectFilled(aPageLinePos, ImVec2(aPageLinePos.x + fPageWidth, aPageLinePos.y + MenuSettings::fSidebarLineHeight), ImGui::GetColorU32(MenuSettings::sidebarLineColor));
        }
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + MenuSettings::fSidebarLineHeight);

        ImGui::BeginChild("pagebody", ImVec2(0.f, 0.f), false, ImGuiWindowFlags_NoScrollbar);
        switch (MenuVars::currentTab)
        {
        case 0:
            ksd::RenderLegitbotPageBody(fContentStartX);
            break;
        case 1:
            ksd::RenderAimAssistPageBody(fContentStartX);
            break;
        case 2:
            ksd::RenderPlayersPageBody(fContentStartX);
            break;
        case 3:
            ksd::RenderChamsPageBody(fContentStartX);
            break;
        case 4:
            ksd::RenderItemsPageBody(fContentStartX);
            break;
        case 5:
            ksd::RenderVisualsPageBody(fContentStartX);
            break;
        case 6:
            ksd::RenderWorldPageBody(fContentStartX);
            break;
        case 7:
            ksd::RenderViewPageBody(fContentStartX);
            break;
        case 8:
            ksd::RenderIndicatorsPageBody(fContentStartX);
            break;
        case 9:
            ksd::RenderMiscellaneousPageBody(fContentStartX);
            break;
        case 10:
            ksd::RenderInventoryPageBody(fContentStartX);
            break;
        case 11:
            ksd::RenderConfigsPageBody(fContentStartX);
            break;
        default:
            ksd::RenderDefaultPageBody(fContentStartX);
            break;
        }
        ImGui::EndChild();
        ImGui::EndChild();
        ImGui::PopStyleColor();
    }
    ImGui::End();
    ImGui::PopStyleVar(3);
    ImGui::PopStyleColor();
}
}

namespace KSD
{
void Render()
{
    ksd::Render();
}
}
