#include "pagechams.h"
#include "../custom_imgui.h"
#include "../custom_settings.h"
#include "../var.h"
#include "imgui.h"
#include "../../../ext/fonts/iconsfontawesome/IconsFontAwesome7.h"
#include <cfloat>

namespace
{
struct ChamsPageState
{
    int materialPreset = 0;
    bool isMasterEnabled = false;
    bool isEnemyVisibleOn = true;
    ImVec4 enemyVisibleColor = ImVec4(0.35f, 0.75f, 1.f, 1.f);
    bool isEnemyOccludedOn = true;
    ImVec4 enemyOccludedColor = ImVec4(1.f, 0.35f, 0.35f, 1.f);
    bool isTeamVisibleOn = false;
    ImVec4 teamVisibleColor = ImVec4(0.35f, 1.f, 0.45f, 1.f);
    bool isLocalArmsOn = false;
    ImVec4 localArmsColor = ImVec4(1.f, 1.f, 1.f, 1.f);
    bool isWeaponOn = false;
    ImVec4 weaponColor = ImVec4(0.9f, 0.85f, 0.2f, 1.f);
    bool isRagdollOn = false;
    ImVec4 ragdollColor = ImVec4(0.6f, 0.5f, 1.f, 1.f);
    int transparencyMode = 0;
    float overlayStrength = 0.65f;
    bool isIgnoreZForOccluded = true;
    bool isWireframeOverlay = false;
};

ChamsPageState gChamsPageState;

void DrawChamsColorRow(const char* pLabel, const char* pPickerId, bool* pEnabled, ImVec4* pColor, float fColumnWidth, float fColumnContentX, float fInlineLabelOffsetY)
{
    const float fRowY = ImGui::GetCursorPosY();
    ksd::DrawInlineLabel(pLabel, fColumnContentX, fRowY + fInlineLabelOffsetY);
    ImGui::SetCursorPos(ImVec2(fColumnWidth - 18.f, fRowY + 6.f));
    ksd::DrawColorPickerCheckbox(pPickerId, pEnabled, pColor);
    ImGui::SetCursorPosY(fRowY + 28.f);
}
}

void ksd::RenderChamsPageHead(float fContentStartX, float fHeadCheckboxY)
{
    ChamsPageState& aState = gChamsPageState;
    static const char* const ppMaterials[] = { "Default", "Flat", "Metallic", "Ghost" };
    const int iMaterialCount = (int)(sizeof(ppMaterials) / sizeof(ppMaterials[0]));
    const float fTopComboWidth = 124.f;
    const float fTopComboHeight = MenuSettings::fPageInlineRowHeight;
    const float fTopComboX = fContentStartX + 140.f;

    ImGui::SetCursorPos(ImVec2(fContentStartX, fHeadCheckboxY));
    ksd::DrawCheckbox("Master switch", &aState.isMasterEnabled);
    ImGui::SetCursorPos(ImVec2(fTopComboX, fHeadCheckboxY));
    ksd::DrawCustomCombo("chamsmaterial", &aState.materialPreset, ppMaterials, iMaterialCount, ImVec2(fTopComboWidth, fTopComboHeight));
    ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x - 28.f - 80.f, fHeadCheckboxY));
    ksd::DrawIconTextButton(ICON_FA_CLOUD_ARROW_UP, "Save", ImVec2(80.f, 28.f));
}

void ksd::RenderChamsPageBody(float fContentStartX)
{
    ChamsPageState& aState = gChamsPageState;
    (void)fContentStartX;
    static const char* const ppTransparency[] = { "Off", "Low", "High" };
    const int iTransparencyCount = (int)(sizeof(ppTransparency) / sizeof(ppTransparency[0]));

    const float fBodyWidth = ImGui::GetWindowSize().x;
    const float fColumnWidth = MenuSettings::fPageColumnWidth;
    const float fLeftMargin = MenuSettings::fPageLeftMargin;
    const float fRightMargin = MenuSettings::fPageRightMargin;
    const float fRightColumnX = fBodyWidth - fRightMargin - fColumnWidth;
    const float fColumnContentX = 0.f;
    const float fSectionTitleY = MenuSettings::fPageSectionTitleY;
    const float fSectionTitleSize = MenuSettings::fPageSectionTitleSize;
    const float fInlineRowHeight = MenuSettings::fPageInlineRowHeight;
    const float fInlineComboWidth = MenuSettings::fPageInlineComboWidth;
    const float fInlineComboX = fColumnWidth - fInlineComboWidth;
    const float fInlineLabelOffsetY = 6.f;
    const ImU32 iSectionTitleColor = ImGui::GetColorU32(ImVec4(128.f / 255.f, 128.f / 255.f, 128.f / 255.f, 1.f));

    ImGui::SetCursorPos(ImVec2(fLeftMargin, 0.f));
    ImGui::BeginChild("chamsleft", ImVec2(fColumnWidth, 0.f), false, ImGuiWindowFlags_NoScrollbar);
    ksd::DrawSectionTitle("Players", fColumnWidth, fSectionTitleY, fSectionTitleSize, iSectionTitleColor);
    ImGui::SetCursorPosX(fColumnContentX);
    ImGui::SetCursorPosY(38.f);
    DrawChamsColorRow("Enemy visible", "chamsev", &aState.isEnemyVisibleOn, &aState.enemyVisibleColor, fColumnWidth, fColumnContentX, fInlineLabelOffsetY);
    DrawChamsColorRow("Enemy occluded", "chamseo", &aState.isEnemyOccludedOn, &aState.enemyOccludedColor, fColumnWidth, fColumnContentX, fInlineLabelOffsetY);
    DrawChamsColorRow("Team visible", "chamstv", &aState.isTeamVisibleOn, &aState.teamVisibleColor, fColumnWidth, fColumnContentX, fInlineLabelOffsetY);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Ignore Z occluded", &aState.isIgnoreZForOccluded, 240.f);
    {
        const float fRowY = ImGui::GetCursorPosY();
        ksd::DrawInlineLabel("Transparency", fColumnContentX, fRowY + fInlineLabelOffsetY);
        ImGui::SetCursorPos(ImVec2(fInlineComboX, fRowY));
        ksd::DrawCustomCombo("chamstransparency", &aState.transparencyMode, ppTransparency, iTransparencyCount, ImVec2(fInlineComboWidth, fInlineRowHeight));
        ImGui::SetCursorPosY(fRowY + fInlineRowHeight);
    }
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawFloatSlider("Overlay strength", &aState.overlayStrength, 0.f, 1.f, 240.f);
    ImGui::EndChild();

    ImGui::SetCursorPos(ImVec2(fRightColumnX, 0.f));
    ImGui::BeginChild("chamsright", ImVec2(fColumnWidth, 0.f), false, ImGuiWindowFlags_NoScrollbar);
    ksd::DrawSectionTitle("Viewmodel", fColumnWidth, fSectionTitleY, fSectionTitleSize, iSectionTitleColor);
    ImGui::SetCursorPosX(fColumnContentX);
    ImGui::SetCursorPosY(38.f);
    DrawChamsColorRow("Local arms", "chamsla", &aState.isLocalArmsOn, &aState.localArmsColor, fColumnWidth, fColumnContentX, fInlineLabelOffsetY);
    DrawChamsColorRow("Weapon", "chamswp", &aState.isWeaponOn, &aState.weaponColor, fColumnWidth, fColumnContentX, fInlineLabelOffsetY);
    DrawChamsColorRow("Ragdolls", "chamsrg", &aState.isRagdollOn, &aState.ragdollColor, fColumnWidth, fColumnContentX, fInlineLabelOffsetY);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Wireframe overlay", &aState.isWireframeOverlay, 240.f);
    ImGui::EndChild();
}
