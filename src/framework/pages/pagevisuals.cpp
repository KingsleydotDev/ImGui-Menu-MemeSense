#include "pagevisuals.h"
#include "../custom_imgui.h"
#include "../custom_settings.h"
#include "../var.h"
#include "imgui.h"
#include "../../../ext/fonts/iconsfontawesome/IconsFontAwesome7.h"
#include <cfloat>

namespace
{
struct VisualsPageState
{
    int hudLayout = 0;
    bool isMasterEnabled = false;
    bool isRadarEnabled = true;
    bool isBombTimerEnabled = true;
    bool isSpectatorListEnabled = true;
    bool isGrenadePredictionEnabled = false;
    bool isPenetrationReticleEnabled = false;
    bool isSpreadCircleEnabled = false;
    bool isHitsoundEnabled = true;
    bool isHitmarkerEnabled = true;
    bool isDamageNumbersEnabled = false;
    bool isKillFeedOverrideEnabled = false;
    int hitsoundStyle = 0;
    int hitmarkerStyle = 0;
    int damageNumberStyle = 0;
    float hitsoundVolume = 0.7f;
    int grenadeTrailLength = 120;
};

VisualsPageState gVisualsPageState;
}

void ksd::RenderVisualsPageHead(float fContentStartX, float fHeadCheckboxY)
{
    VisualsPageState& aState = gVisualsPageState;
    static const char* const ppLayouts[] = { "Compact", "Standard", "Minimal" };
    const int iLayoutCount = (int)(sizeof(ppLayouts) / sizeof(ppLayouts[0]));
    const float fTopComboWidth = 124.f;
    const float fTopComboHeight = MenuSettings::fPageInlineRowHeight;
    const float fTopComboX = fContentStartX + 140.f;

    ImGui::SetCursorPos(ImVec2(fContentStartX, fHeadCheckboxY));
    ksd::DrawCheckbox("Master switch", &aState.isMasterEnabled);
    ImGui::SetCursorPos(ImVec2(fTopComboX, fHeadCheckboxY));
    ksd::DrawCustomCombo("visualshudlayout", &aState.hudLayout, ppLayouts, iLayoutCount, ImVec2(fTopComboWidth, fTopComboHeight));
    ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x - 28.f - 80.f, fHeadCheckboxY));
    ksd::DrawIconTextButton(ICON_FA_CLOUD_ARROW_UP, "Save", ImVec2(80.f, 28.f));
}

void ksd::RenderVisualsPageBody(float fContentStartX)
{
    VisualsPageState& aState = gVisualsPageState;
    (void)fContentStartX;
    static const char* const ppHitsounds[] = { "Click", "Bell", "Metal", "Off" };
    static const char* const ppHitmarkers[] = { "Classic", "Dot", "Cross", "Off" };
    static const char* const ppDamageNums[] = { "Floating", "Stack", "World", "Off" };
    const int iHitsoundCount = (int)(sizeof(ppHitsounds) / sizeof(ppHitsounds[0]));
    const int iHitmarkerCount = (int)(sizeof(ppHitmarkers) / sizeof(ppHitmarkers[0]));
    const int iDamageCount = (int)(sizeof(ppDamageNums) / sizeof(ppDamageNums[0]));

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
    ImGui::BeginChild("visualsleft", ImVec2(fColumnWidth, 0.f), false, ImGuiWindowFlags_NoScrollbar);
    ksd::DrawSectionTitle("HUD", fColumnWidth, fSectionTitleY, fSectionTitleSize, iSectionTitleColor);
    ImGui::SetCursorPosX(fColumnContentX);
    ImGui::SetCursorPosY(38.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Radar", &aState.isRadarEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Bomb timer", &aState.isBombTimerEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Spectator list", &aState.isSpectatorListEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Grenade prediction", &aState.isGrenadePredictionEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawIntSlider("Trail length", &aState.grenadeTrailLength, 0, 300, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Penetration reticle", &aState.isPenetrationReticleEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Spread circle", &aState.isSpreadCircleEnabled, 240.f);
    ImGui::EndChild();

    ImGui::SetCursorPos(ImVec2(fRightColumnX, 0.f));
    ImGui::BeginChild("visualsright", ImVec2(fColumnWidth, 0.f), false, ImGuiWindowFlags_NoScrollbar);
    ksd::DrawSectionTitle("Feedback", fColumnWidth, fSectionTitleY, fSectionTitleSize, iSectionTitleColor);
    ImGui::SetCursorPosX(fColumnContentX);
    ImGui::SetCursorPosY(38.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Hitsound", &aState.isHitsoundEnabled, 240.f);
    {
        const float fRowY = ImGui::GetCursorPosY();
        ksd::DrawInlineLabel("Hitsound style", fColumnContentX, fRowY + fInlineLabelOffsetY);
        ImGui::SetCursorPos(ImVec2(fInlineComboX, fRowY));
        ksd::DrawCustomCombo("visualshitsound", &aState.hitsoundStyle, ppHitsounds, iHitsoundCount, ImVec2(fInlineComboWidth, fInlineRowHeight));
        ImGui::SetCursorPosY(fRowY + fInlineRowHeight);
    }
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawFloatSlider("Hitsound volume", &aState.hitsoundVolume, 0.f, 1.f, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Hitmarker", &aState.isHitmarkerEnabled, 240.f);
    {
        const float fRowY = ImGui::GetCursorPosY();
        ksd::DrawInlineLabel("Hitmarker style", fColumnContentX, fRowY + fInlineLabelOffsetY);
        ImGui::SetCursorPos(ImVec2(fInlineComboX, fRowY));
        ksd::DrawCustomCombo("visualshitmarker", &aState.hitmarkerStyle, ppHitmarkers, iHitmarkerCount, ImVec2(fInlineComboWidth, fInlineRowHeight));
        ImGui::SetCursorPosY(fRowY + fInlineRowHeight);
    }
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Damage numbers", &aState.isDamageNumbersEnabled, 240.f);
    {
        const float fRowY = ImGui::GetCursorPosY();
        ksd::DrawInlineLabel("Damage style", fColumnContentX, fRowY + fInlineLabelOffsetY);
        ImGui::SetCursorPos(ImVec2(fInlineComboX, fRowY));
        ksd::DrawCustomCombo("visualsdamage", &aState.damageNumberStyle, ppDamageNums, iDamageCount, ImVec2(fInlineComboWidth, fInlineRowHeight));
        ImGui::SetCursorPosY(fRowY + fInlineRowHeight);
    }
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Kill feed override", &aState.isKillFeedOverrideEnabled, 240.f);
    ImGui::EndChild();
}
