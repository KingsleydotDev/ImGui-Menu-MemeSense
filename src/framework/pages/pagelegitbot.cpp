#include "pagelegitbot.h"
#include "../custom_imgui.h"
#include "../custom_settings.h"
#include "../var.h"
#include "imgui.h"
#include "../../../ext/fonts/iconsfontawesome/IconsFontAwesome7.h"
#include <cfloat>

namespace
{
struct LegitbotState
{
    int weaponGroup = 0;
    int weaponItem = 0;
    bool isLegitEnabled = false;
    bool shouldDrawFov = true;
    bool shouldOnlyBodyAim = false;
    bool shouldPreferHeadAim = true;
    bool shouldPreferBodyAim = false;
    bool shouldBodyAimIfLethal = true;
    bool isAutoFireEnabled = false;
    bool shouldAutoStop = false;
    bool isAimKeyEnabled = false;
    bool isSelectionPopupEnabled = false;
    bool isAimKeyPopupEnabled = false;
    int targetGroup = 0;
    int autoFireSelector = 0;
    int radiusType = 0;
    int smoothType = 0;
    int hitChanceTypeRight = 0;
    int hitChanceTypeAccuracy = 0;
    int detailSelector = 0;
    int aimKeyType = 0;
    int aimTime = 0;
    int reactionTimeRight = 0;
    int reactionTimeMisc = 0;
    int shotDelayRight = 0;
    int firstShotDelayAccuracy = 0;
    float minimumHitChanceRight = 0.f;
    int minimumHitChanceAccuracy = 0;
    int targetSwitchDelay = 250;
    int minimumDamage = 0;
    int firstShotDelayType = 0;
    int lockCamera = 0;
    int ghostTimeRight = 0;
    int ghostTimeMisc = 0;
    float radius = 1.056f;
    float multiplier = 4.f;
    float smoothPitch = 2.998f;
    float smoothYaw = 2.998f;
    float rcsPitch = 1.5f;
    float rcsYaw = 1.5f;
    bool isMasterPopupEnabled = false;
    bool isMasterPopupExtraEnabled = false;
    bool isEnablePopupVisible = false;
    bool isAutoFirePopupVisible = false;
    int masterPopupMode = 0;
    bool selectionValues[4] = { true, true, true, false };
};

LegitbotState gLegitbotState;

void DrawMasterSwitchPopup()
{
    LegitbotState& aState = gLegitbotState;
    static const char* const ppMasterModes[] = { "Static", "Dynamic", "Strict" };
    ImGui::SetCursorPos(ImVec2(28.f, 20.f));
    ksd::DrawCheckbox("Enable test", &aState.isMasterPopupEnabled, 200.f);
    ImGui::SetCursorPos(ImVec2(28.f, 50.f));
    ksd::DrawCheckbox("Second test", &aState.isMasterPopupExtraEnabled, 200.f);
    ImGui::SetCursorPos(ImVec2(28.f, 80.f));
    ksd::DrawCustomCombo("masterpopupmode", &aState.masterPopupMode, ppMasterModes, sizeof(ppMasterModes) / sizeof(ppMasterModes[0]), ImVec2(200.f, 28.f));
    ImGui::SetCursorPos(ImVec2(28.f, 120.f));
    ksd::Button("Apply", ImVec2(96.f, 28.f));
    ImGui::SameLine(0.f, 8.f);
    ksd::Button("Reset", ImVec2(96.f, 28.f));
}

void DrawSelectionPopup()
{
    LegitbotState& aState = gLegitbotState;
    ImGui::SetCursorPos(ImVec2(16.f, 12.f));
    ksd::Button("Random", ImVec2(90.f, 28.f));
    ImGui::SetCursorPos(ImVec2(16.f, 46.f));
    ksd::DrawCheckbox("Random toggle", &aState.isSelectionPopupEnabled, 180.f);
}

void DrawAimKeyPopup()
{
    LegitbotState& aState = gLegitbotState;
    ImGui::SetCursorPos(ImVec2(16.f, 12.f));
    ksd::DrawCheckbox("Aim key popup", &aState.isAimKeyPopupEnabled, 180.f);
}

void DrawEnablePopup()
{
    LegitbotState& aState = gLegitbotState;
    ImGui::SetCursorPos(ImVec2(16.f, 12.f));
    ksd::Button("Random", ImVec2(90.f, 28.f));
    ImGui::SetCursorPos(ImVec2(16.f, 46.f));
    ksd::DrawCheckbox("Enable popup", &aState.isEnablePopupVisible, 180.f);
}

void DrawAutoFirePopup()
{
    LegitbotState& aState = gLegitbotState;
    ImGui::SetCursorPos(ImVec2(16.f, 12.f));
    ksd::DrawCheckbox("Auto fire popup", &aState.isAutoFirePopupVisible, 180.f);
}
}

void ksd::RenderLegitbotPageHead(float fContentStartX, float fHeadCheckboxY)
{
    LegitbotState& aState = gLegitbotState;
    static const char* const ppWeaponGroups[] = { "Per weapons", "Per category" };
    static const char* const ppWeaponItems[] = { "Tec-9", "AK-47", "AWP", "M4A1-S" };
    const int iWeaponGroupCount = (int)(sizeof(ppWeaponGroups) / sizeof(ppWeaponGroups[0]));
    const int iWeaponItemCount = (int)(sizeof(ppWeaponItems) / sizeof(ppWeaponItems[0]));
    const float fTopComboWidth = 124.f;
    const float fTopComboHeight = 28.f;
    const float fTopComboFirstX = fContentStartX + 140.f;
    const float fTopComboSecondX = fTopComboFirstX + fTopComboWidth + 10.f;

    ImGui::SetCursorPos(ImVec2(fContentStartX, fHeadCheckboxY));
    ksd::DrawCheckboxIconPopup("Master switch", &MenuVars::isFeatureBEnabled, 34.f, -2.f, ICON_FA_GEAR, "masterswitchpopup", 0.f, DrawMasterSwitchPopup);
    ImGui::SetCursorPos(ImVec2(fTopComboFirstX, fHeadCheckboxY));
    ksd::DrawCustomCombo("weapongroup", &aState.weaponGroup, ppWeaponGroups, iWeaponGroupCount, ImVec2(fTopComboWidth, fTopComboHeight));
    ImGui::SetCursorPos(ImVec2(fTopComboSecondX, fHeadCheckboxY));
    ksd::DrawCustomCombo("weaponitem", &aState.weaponItem, ppWeaponItems, iWeaponItemCount, ImVec2(fTopComboWidth, fTopComboHeight));
    ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x - 28.f - 80.f, fHeadCheckboxY));
    ksd::DrawIconTextButton(ICON_FA_CLOUD_ARROW_UP, "Save", ImVec2(80.f, 28.f));
}

void ksd::RenderLegitbotPageBody(float fContentStartX)
{
    LegitbotState& aState = gLegitbotState;
    (void)fContentStartX;
    static const char* const ppTargetGroups[] = { "Players", "Enemies", "All" };
    static const char* const ppSelectionModes[] = { "Head", "Neck", "Chest", "Legs" };
    static const char* const ppAimKeyTypes[] = { "Always", "Hold" };
    static const char* const ppRadiusTypes[] = { "Static", "Dynamic", "Linear", "Custom" };
    static const char* const ppSmoothTypes[] = { "Dynamic", "Linear", "Custom" };
    static const char* const ppHitChanceTypes[] = { "Strict", "Relaxed", "Custom" };
    static const char* const ppDetailTabs[] = { "Aim", "Accuracy", "RCS", "Misc" };
    static const char* const ppFirstShotDelayTypes[] = { "Combined", "Separate" };
    static const char* const ppAutoFireText[] = { "Auto fire", "Auto wall" };
    const int iAimKeyTypeCount = (int)(sizeof(ppAimKeyTypes) / sizeof(ppAimKeyTypes[0]));
    const int iRadiusTypeCount = (int)(sizeof(ppRadiusTypes) / sizeof(ppRadiusTypes[0]));
    const int iSmoothTypeCount = (int)(sizeof(ppSmoothTypes) / sizeof(ppSmoothTypes[0]));
    const int iHitChanceTypeCount = (int)(sizeof(ppHitChanceTypes) / sizeof(ppHitChanceTypes[0]));
    const int iDetailTabCount = (int)(sizeof(ppDetailTabs) / sizeof(ppDetailTabs[0]));
    const int iFirstShotDelayTypeCount = (int)(sizeof(ppFirstShotDelayTypes) / sizeof(ppFirstShotDelayTypes[0]));
    const int iSelectionModeCount = (int)(sizeof(ppSelectionModes) / sizeof(ppSelectionModes[0]));
    const int iTargetGroupCount = (int)(sizeof(ppTargetGroups) / sizeof(ppTargetGroups[0]));
    const int iAutoFireTextCount = (int)(sizeof(ppAutoFireText) / sizeof(ppAutoFireText[0]));

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
    ImGui::BeginChild("legitbotleft", ImVec2(fColumnWidth, 0.f), false, ImGuiWindowFlags_NoScrollbar);
    ksd::DrawSectionTitle("General", fColumnWidth, fSectionTitleY, fSectionTitleSize, iSectionTitleColor);
    ImGui::SetCursorPosX(fColumnContentX);
    ImGui::SetCursorPosY(38.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckboxIconPopup("Enable", &aState.isLegitEnabled, 344.f, -8.f, ICON_FA_LIST_CHECK, "enablepopup", 0.f, DrawEnablePopup);
    {
        const float fRowY = ImGui::GetCursorPosY();
        ImGui::SetCursorPos(ImVec2(fColumnContentX, fRowY));
        ksd::DrawCheckboxIconPopup("Aim Key", &aState.isAimKeyEnabled, 104.f, -2.f, ICON_FA_KEYBOARD, "aimkeypopup", 0.f, DrawAimKeyPopup);
        ImGui::SetCursorPos(ImVec2(fInlineComboX, fRowY));
        ksd::DrawCustomCombo("##aimkeytypeinline", &aState.aimKeyType, ppAimKeyTypes, iAimKeyTypeCount, ImVec2(fInlineComboWidth, fInlineRowHeight));
        ImGui::SetCursorPosY(fRowY + fInlineRowHeight);
    }
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Draw FOV", &aState.shouldDrawFov, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawIntSlider("Aim time", &aState.aimTime, 0, 100, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawTextSelector("detailtabs", &aState.detailSelector, ppDetailTabs, iDetailTabCount, 240.f);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 6.f);
    if (aState.detailSelector == 0)
    {
        const float fRadiusTypeRowY = ImGui::GetCursorPosY();
        ksd::DrawInlineLabel("Radius type", fColumnContentX, fRadiusTypeRowY + fInlineLabelOffsetY);
        ImGui::SetCursorPos(ImVec2(fInlineComboX, fRadiusTypeRowY));
        ksd::DrawCustomCombo("radiustype", &aState.radiusType, ppRadiusTypes, iRadiusTypeCount, ImVec2(fInlineComboWidth, fInlineRowHeight));
        ImGui::SetCursorPosX(fColumnContentX);
        ksd::DrawFloatSlider("Radius", &aState.radius, 0.f, 5.f, 240.f);
        ImGui::SetCursorPosX(fColumnContentX);
        ksd::DrawFloatSlider("Multiplier", &aState.multiplier, 0.f, 10.f, 240.f);
        {
            const float fSmoothTypeRowY = ImGui::GetCursorPosY();
            ksd::DrawInlineLabel("Smooth type", fColumnContentX, fSmoothTypeRowY + fInlineLabelOffsetY);
            ImGui::SetCursorPos(ImVec2(fInlineComboX, fSmoothTypeRowY));
            ksd::DrawCustomCombo("smoothTypeFinal", &aState.smoothType, ppSmoothTypes, iSmoothTypeCount, ImVec2(fInlineComboWidth, fInlineRowHeight));
            ImGui::SetCursorPosY(fSmoothTypeRowY + fInlineRowHeight + 6.f);
        }
        ImGui::SetCursorPosX(fColumnContentX);
        ksd::DrawFloatSlider("Smooth pitch", &aState.smoothPitch, 0.f, 5.f, 240.f);
        ImGui::SetCursorPosX(fColumnContentX);
        ksd::DrawFloatSlider("Smooth yaw", &aState.smoothYaw, 0.f, 5.f, 240.f);
    }
    else if (aState.detailSelector == 1)
    {
        const float fFirstShotTypeRowY = ImGui::GetCursorPosY();
        ksd::DrawInlineLabel("First shot delay type", fColumnContentX, fFirstShotTypeRowY + fInlineLabelOffsetY);
        ImGui::SetCursorPos(ImVec2(fInlineComboX, fFirstShotTypeRowY));
        ksd::DrawCustomCombo("firstshotdelaytype", &aState.firstShotDelayType, ppFirstShotDelayTypes, iFirstShotDelayTypeCount, ImVec2(fInlineComboWidth, fInlineRowHeight));
        ImGui::SetCursorPosX(fColumnContentX);
        ksd::DrawIntSlider("First shot delay", &aState.firstShotDelayAccuracy, 0, 500, 240.f);
        ImGui::SetCursorPosX(fColumnContentX);
        ksd::DrawIntSlider("Target switch delay", &aState.targetSwitchDelay, 0, 500, 240.f);
        {
            const float fHitChanceRowY = ImGui::GetCursorPosY();
            ksd::DrawInlineLabel("Hit chance type", fColumnContentX, fHitChanceRowY + fInlineLabelOffsetY);
            ImGui::SetCursorPos(ImVec2(fInlineComboX, fHitChanceRowY));
            ksd::DrawCustomCombo("hitchancetypeleft", &aState.hitChanceTypeAccuracy, ppHitChanceTypes, iHitChanceTypeCount, ImVec2(fInlineComboWidth, fInlineRowHeight));
            ImGui::SetCursorPosY(fHitChanceRowY + fInlineRowHeight + 4.f);
        }
        ImGui::SetCursorPosX(fColumnContentX);
        ksd::DrawIntSlider("Minimum hit chance", &aState.minimumHitChanceAccuracy, 0, 100, 240.f);
        ImGui::SetCursorPosX(fColumnContentX);
        ksd::DrawIntSlider("Minimum damage", &aState.minimumDamage, 0, 100, 240.f);
    }
    else if (aState.detailSelector == 2)
    {
        ImGui::SetCursorPosX(fColumnContentX);
        ksd::DrawFloatSlider("Pitch", &aState.rcsPitch, 0.f, 5.f, 240.f);
        ImGui::SetCursorPosX(fColumnContentX);
        ksd::DrawFloatSlider("Yaw", &aState.rcsYaw, 0.f, 5.f, 240.f);
    }
    else
    {
        ImGui::SetCursorPosX(fColumnContentX);
        ksd::DrawIntSlider("Reaction time", &aState.reactionTimeMisc, 0, 500, 240.f);
        ImGui::SetCursorPosX(fColumnContentX);
        ksd::DrawIntSlider("Ghost time", &aState.ghostTimeMisc, 0, 500, 240.f);
    }
    ImGui::EndChild();

    ImGui::SetCursorPos(ImVec2(fRightColumnX, 0.f));
    ImGui::BeginChild("legitbotright", ImVec2(fColumnWidth, 0.f), false, ImGuiWindowFlags_NoScrollbar);
    ksd::DrawSectionTitle("Hit groups", fColumnWidth, fSectionTitleY, fSectionTitleSize, iSectionTitleColor);
    ImGui::SetCursorPosX(fColumnContentX);
    ImGui::SetCursorPosY(38.f);
    {
        const float fSelectionRowY = ImGui::GetCursorPosY();
        ksd::DrawInlineLabel("Selection", fColumnContentX, fSelectionRowY + fInlineLabelOffsetY);
        ImGui::SetCursorPos(ImVec2(fInlineComboX - 22.f, fSelectionRowY));
        ksd::DrawMultiComboIcon("selectionmode", aState.selectionValues, ppSelectionModes, iSelectionModeCount, ImVec2(fInlineComboWidth, fInlineRowHeight), ICON_FA_LIST_CHECK, "selectionpopup", 0.f, DrawSelectionPopup);
        ImGui::SetCursorPosY(fSelectionRowY + fInlineRowHeight);
    }
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckboxIcon("Only body aim", &aState.shouldOnlyBodyAim, 240.f, ICON_FA_KEYBOARD);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Prefer head aim", &aState.shouldPreferHeadAim, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Prefer body aim", &aState.shouldPreferBodyAim, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Body aim if lethal", &aState.shouldBodyAimIfLethal, 240.f);
    {
        const float fTargetsRowY = ImGui::GetCursorPosY();
        ksd::DrawInlineLabel("Targets", fColumnContentX, fTargetsRowY + fInlineLabelOffsetY);
        ImGui::SetCursorPos(ImVec2(fInlineComboX, fTargetsRowY));
        ksd::DrawCustomCombo("targetgroup", &aState.targetGroup, ppTargetGroups, iTargetGroupCount, ImVec2(fInlineComboWidth, fInlineRowHeight));
        const float fAutoFireTextY = fTargetsRowY + fInlineRowHeight;
        ImGui::SetCursorPos(ImVec2(fColumnContentX, fAutoFireTextY + 2.f));
        ksd::DrawTextSelector("autofiretextselector", &aState.autoFireSelector, ppAutoFireText, iAutoFireTextCount, 240.f);
        ImGui::SetCursorPos(ImVec2(fColumnContentX, fAutoFireTextY + fInlineRowHeight + 2.f));
        ksd::DrawCheckboxIconPopup("Enable", &aState.isAutoFireEnabled, 336.f, -8.f, ICON_FA_KEYBOARD, "autofireenablepopup", 0.f, DrawAutoFirePopup);
        ImGui::SetCursorPosX(fColumnContentX);
        ksd::DrawCheckbox("Auto stop", &aState.shouldAutoStop, 240.f);

        const float fHitChanceRowY = ImGui::GetCursorPosY();
        ksd::DrawInlineLabel("Hit chance type", fColumnContentX, fHitChanceRowY + fInlineLabelOffsetY);
        ImGui::SetCursorPos(ImVec2(fInlineComboX, fHitChanceRowY));
        ksd::DrawCustomCombo("hitchancetype", &aState.hitChanceTypeRight, ppHitChanceTypes, iHitChanceTypeCount, ImVec2(fInlineComboWidth, fInlineRowHeight));

        ImGui::SetCursorPos(ImVec2(fColumnContentX, fHitChanceRowY + fInlineRowHeight + 4.f));
        ksd::DrawIntSlider("Reaction time", &aState.reactionTimeRight, 0, 100, 240.f);
        ImGui::SetCursorPosX(fColumnContentX);
        ksd::DrawIntSlider("Delay between shots", &aState.shotDelayRight, 0, 100, 240.f);
        ImGui::SetCursorPosX(fColumnContentX);
        ksd::DrawFloatSlider("Minimum hit chance", &aState.minimumHitChanceRight, 0.f, 100.f, 240.f);
        ImGui::SetCursorPosX(fColumnContentX);
        ksd::DrawIntSlider("Lock camera after shot", &aState.lockCamera, 0, 100, 240.f);
        ImGui::SetCursorPosX(fColumnContentX);
        ksd::DrawIntSlider("Ghost time", &aState.ghostTimeRight, 0, 100, 240.f);
    }
    ImGui::EndChild();
}
