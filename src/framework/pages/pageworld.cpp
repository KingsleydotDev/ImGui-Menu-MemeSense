#include "pageworld.h"
#include "../custom_imgui.h"
#include "../custom_settings.h"
#include "../var.h"
#include "imgui.h"
#include "../../../ext/fonts/iconsfontawesome/IconsFontAwesome7.h"
#include <cfloat>

namespace
{
struct WorldPageState
{
    int skyPreset = 0;
    bool isMasterEnabled = false;
    bool isNightModeEnabled = false;
    bool isCustomFogEnabled = false;
    bool isBrightnessBoostEnabled = false;
    bool isRemoveSmokeEnabled = false;
    bool isRemoveFlashEnabled = false;
    bool isRemoveFogEnabled = false;
    bool isPropModEnabled = false;
    int nightStrength = 40;
    float fogDensity = 0.25f;
    float worldBrightness = 1.f;
    float propAlpha = 1.f;
    int exposure = 0;
};

WorldPageState gWorldPageState;
}

void ksd::RenderWorldPageHead(float fContentStartX, float fHeadCheckboxY)
{
    WorldPageState& aState = gWorldPageState;
    static const char* const ppSkies[] = { "Default", "Night", "Purple", "Cloudy", "Custom" };
    const int iSkyCount = (int)(sizeof(ppSkies) / sizeof(ppSkies[0]));
    const float fTopComboWidth = 124.f;
    const float fTopComboHeight = MenuSettings::fPageInlineRowHeight;
    const float fTopComboX = fContentStartX + 140.f;

    ImGui::SetCursorPos(ImVec2(fContentStartX, fHeadCheckboxY));
    ksd::DrawCheckbox("Master switch", &aState.isMasterEnabled);
    ImGui::SetCursorPos(ImVec2(fTopComboX, fHeadCheckboxY));
    ksd::DrawCustomCombo("worldskypreset", &aState.skyPreset, ppSkies, iSkyCount, ImVec2(fTopComboWidth, fTopComboHeight));
    ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x - 28.f - 80.f, fHeadCheckboxY));
    ksd::DrawIconTextButton(ICON_FA_CLOUD_ARROW_UP, "Save", ImVec2(80.f, 28.f));
}

void ksd::RenderWorldPageBody(float fContentStartX)
{
    WorldPageState& aState = gWorldPageState;
    (void)fContentStartX;

    const float fBodyWidth = ImGui::GetWindowSize().x;
    const float fColumnWidth = MenuSettings::fPageColumnWidth;
    const float fLeftMargin = MenuSettings::fPageLeftMargin;
    const float fRightMargin = MenuSettings::fPageRightMargin;
    const float fRightColumnX = fBodyWidth - fRightMargin - fColumnWidth;
    const float fColumnContentX = 0.f;
    const float fSectionTitleY = MenuSettings::fPageSectionTitleY;
    const float fSectionTitleSize = MenuSettings::fPageSectionTitleSize;
    const ImU32 iSectionTitleColor = ImGui::GetColorU32(ImVec4(128.f / 255.f, 128.f / 255.f, 128.f / 255.f, 1.f));

    ImGui::SetCursorPos(ImVec2(fLeftMargin, 0.f));
    ImGui::BeginChild("worldleft", ImVec2(fColumnWidth, 0.f), false, ImGuiWindowFlags_NoScrollbar);
    ksd::DrawSectionTitle("Lighting", fColumnWidth, fSectionTitleY, fSectionTitleSize, iSectionTitleColor);
    ImGui::SetCursorPosX(fColumnContentX);
    ImGui::SetCursorPosY(38.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Night mode", &aState.isNightModeEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawIntSlider("Night strength", &aState.nightStrength, 0, 100, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Custom fog", &aState.isCustomFogEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawFloatSlider("Fog density", &aState.fogDensity, 0.f, 1.f, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Brightness boost", &aState.isBrightnessBoostEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawFloatSlider("Brightness", &aState.worldBrightness, 0.5f, 2.f, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawIntSlider("Exposure shift", &aState.exposure, -50, 50, 240.f);
    ImGui::EndChild();

    ImGui::SetCursorPos(ImVec2(fRightColumnX, 0.f));
    ImGui::BeginChild("worldright", ImVec2(fColumnWidth, 0.f), false, ImGuiWindowFlags_NoScrollbar);
    ksd::DrawSectionTitle("Removals", fColumnWidth, fSectionTitleY, fSectionTitleSize, iSectionTitleColor);
    ImGui::SetCursorPosX(fColumnContentX);
    ImGui::SetCursorPosY(38.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Remove smoke", &aState.isRemoveSmokeEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Remove flash", &aState.isRemoveFlashEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Remove fog", &aState.isRemoveFogEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Prop transparency", &aState.isPropModEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawFloatSlider("Prop alpha", &aState.propAlpha, 0.2f, 1.f, 240.f);
    ImGui::EndChild();
}
