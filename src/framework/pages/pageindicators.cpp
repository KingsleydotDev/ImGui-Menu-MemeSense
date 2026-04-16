#include "pageindicators.h"
#include "../custom_imgui.h"
#include "../custom_settings.h"
#include "../var.h"
#include "imgui.h"
#include "../../../ext/fonts/iconsfontawesome/IconsFontAwesome7.h"
#include <cfloat>

namespace
{
struct IndicatorsPageState
{
    int cornerStyle = 0;
    bool isMasterEnabled = false;
    bool isCrosshairEnabled = false;
    bool isCenterDotEnabled = false;
    bool isRecoilLineEnabled = false;
    bool isSpreadDisplayEnabled = false;
    bool isVelocityEnabled = true;
    bool isStaminaEnabled = false;
    bool isBombTimerBarEnabled = true;
    bool isKeybindListEnabled = true;
    bool isWatermarkEnabled = true;
    bool isSpectatorWarningEnabled = true;
    int velocityPosition = 0;
    int keybindLayout = 0;
    float crosshairSize = 4.f;
    int watermarkStyle = 0;
};

IndicatorsPageState gIndicatorsPageState;
}

void ksd::RenderIndicatorsPageHead(float fContentStartX, float fHeadCheckboxY)
{
    IndicatorsPageState& aState = gIndicatorsPageState;
    static const char* const ppCorners[] = { "Sharp", "Rounded", "Minimal" };
    const int iCornerCount = (int)(sizeof(ppCorners) / sizeof(ppCorners[0]));
    const float fTopComboWidth = 124.f;
    const float fTopComboHeight = MenuSettings::fPageInlineRowHeight;
    const float fTopComboX = fContentStartX + 140.f;

    ImGui::SetCursorPos(ImVec2(fContentStartX, fHeadCheckboxY));
    ksd::DrawCheckbox("Master switch", &aState.isMasterEnabled);
    ImGui::SetCursorPos(ImVec2(fTopComboX, fHeadCheckboxY));
    ksd::DrawCustomCombo("indicatorscorner", &aState.cornerStyle, ppCorners, iCornerCount, ImVec2(fTopComboWidth, fTopComboHeight));
    ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x - 28.f - 80.f, fHeadCheckboxY));
    ksd::DrawIconTextButton(ICON_FA_CLOUD_ARROW_UP, "Save", ImVec2(80.f, 28.f));
}

void ksd::RenderIndicatorsPageBody(float fContentStartX)
{
    IndicatorsPageState& aState = gIndicatorsPageState;
    (void)fContentStartX;
    static const char* const ppVelocityPos[] = { "Bottom left", "Top left", "Right stack" };
    static const char* const ppKeybindLayout[] = { "List", "Compact", "Icons only" };
    static const char* const ppWatermark[] = { "Full", "Name only", "FPS only" };
    const int iVelPosCount = (int)(sizeof(ppVelocityPos) / sizeof(ppVelocityPos[0]));
    const int iKeybindCount = (int)(sizeof(ppKeybindLayout) / sizeof(ppKeybindLayout[0]));
    const int iWatermarkCount = (int)(sizeof(ppWatermark) / sizeof(ppWatermark[0]));

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
    ImGui::BeginChild("indicatorsleft", ImVec2(fColumnWidth, 0.f), false, ImGuiWindowFlags_NoScrollbar);
    ksd::DrawSectionTitle("Crosshair", fColumnWidth, fSectionTitleY, fSectionTitleSize, iSectionTitleColor);
    ImGui::SetCursorPosX(fColumnContentX);
    ImGui::SetCursorPosY(38.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Custom crosshair", &aState.isCrosshairEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawFloatSlider("Crosshair size", &aState.crosshairSize, 1.f, 12.f, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Center dot", &aState.isCenterDotEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Recoil line", &aState.isRecoilLineEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Spread display", &aState.isSpreadDisplayEnabled, 240.f);
    ImGui::EndChild();

    ImGui::SetCursorPos(ImVec2(fRightColumnX, 0.f));
    ImGui::BeginChild("indicatorsright", ImVec2(fColumnWidth, 0.f), false, ImGuiWindowFlags_NoScrollbar);
    ksd::DrawSectionTitle("Info panels", fColumnWidth, fSectionTitleY, fSectionTitleSize, iSectionTitleColor);
    ImGui::SetCursorPosX(fColumnContentX);
    ImGui::SetCursorPosY(38.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Velocity", &aState.isVelocityEnabled, 240.f);
    {
        const float fRowY = ImGui::GetCursorPosY();
        ksd::DrawInlineLabel("Velocity position", fColumnContentX, fRowY + fInlineLabelOffsetY);
        ImGui::SetCursorPos(ImVec2(fInlineComboX, fRowY));
        ksd::DrawCustomCombo("indicatorsvelpos", &aState.velocityPosition, ppVelocityPos, iVelPosCount, ImVec2(fInlineComboWidth, fInlineRowHeight));
        ImGui::SetCursorPosY(fRowY + fInlineRowHeight);
    }
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Stamina", &aState.isStaminaEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Bomb timer bar", &aState.isBombTimerBarEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Keybind list", &aState.isKeybindListEnabled, 240.f);
    {
        const float fRowY = ImGui::GetCursorPosY();
        ksd::DrawInlineLabel("Keybind layout", fColumnContentX, fRowY + fInlineLabelOffsetY);
        ImGui::SetCursorPos(ImVec2(fInlineComboX, fRowY));
        ksd::DrawCustomCombo("indicatorskeybind", &aState.keybindLayout, ppKeybindLayout, iKeybindCount, ImVec2(fInlineComboWidth, fInlineRowHeight));
        ImGui::SetCursorPosY(fRowY + fInlineRowHeight);
    }
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Watermark", &aState.isWatermarkEnabled, 240.f);
    {
        const float fRowY = ImGui::GetCursorPosY();
        ksd::DrawInlineLabel("Watermark style", fColumnContentX, fRowY + fInlineLabelOffsetY);
        ImGui::SetCursorPos(ImVec2(fInlineComboX, fRowY));
        ksd::DrawCustomCombo("indicatorswatermark", &aState.watermarkStyle, ppWatermark, iWatermarkCount, ImVec2(fInlineComboWidth, fInlineRowHeight));
        ImGui::SetCursorPosY(fRowY + fInlineRowHeight);
    }
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Spectator warning", &aState.isSpectatorWarningEnabled, 240.f);
    ImGui::EndChild();
}
