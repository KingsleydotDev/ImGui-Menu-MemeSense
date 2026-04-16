#include "pageaimassist.h"
#include "../custom_imgui.h"
#include "../custom_settings.h"
#include "../var.h"
#include "imgui.h"
#include "../../../ext/fonts/iconsfontawesome/IconsFontAwesome7.h"
#include <cfloat>

namespace
{
struct AimAssistState
{
    int weaponGroup = 0;
    bool isTriggerEnabled = true;
    bool canTriggerThroughWall = true;
    bool shouldTriggerAirCheck = false;
    bool shouldTriggerAutoScope = false;
    bool shouldTriggerScopeCheck = false;
    bool shouldTriggerFlashCheck = false;
    bool shouldTriggerSmokeCheck = false;
    bool shouldTriggerIgnoreBreakables = false;
    int triggerHitChanceType = 0;
    bool isTriggerVisibleOnly = false;
    int triggerHitGroups = 0;
    int triggerMinimumDamage = 0;
    int triggerMinimumHitChance = 14;
    int triggerReactionTime = 0;
    float triggerLockCameraAfterShot = 0.f;
    float triggerDelayBetweenShots = 0.f;
    bool isRcsEnabled = false;
    bool shouldRcsReturnCrosshair = false;
    int rcsBulletStart = 2;
    int rcsBulletEnd = 30;
    float rcsX = 1.f;
    float rcsY = 1.f;
    bool isAutoPistolEnabled = true;
    int autoPistolDelay = 36;
};

AimAssistState gAimAssistState;
}

void ksd::RenderAimAssistPageHead(float fContentStartX, float fHeadCheckboxY)
{
    AimAssistState& aState = gAimAssistState;
    static const char* const ppWeaponGroups[] = { "All weapons", "Per category" };
    const int iWeaponGroupCount = (int)(sizeof(ppWeaponGroups) / sizeof(ppWeaponGroups[0]));
    const float fTopComboWidth = 124.f;
    const float fTopComboHeight = MenuSettings::fPageInlineRowHeight;
    const float fTopComboFirstX = fContentStartX + 140.f;

    ImGui::SetCursorPos(ImVec2(fContentStartX, fHeadCheckboxY));
    ksd::DrawCheckbox("Master switch", &MenuVars::isFeatureAEnabled);
    ImGui::SetCursorPos(ImVec2(fTopComboFirstX, fHeadCheckboxY));
    ksd::DrawCustomCombo("aimassistweapongroup", &aState.weaponGroup, ppWeaponGroups, iWeaponGroupCount, ImVec2(fTopComboWidth, fTopComboHeight));
    ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x - 28.f - 80.f, fHeadCheckboxY));
    ksd::DrawIconTextButton(ICON_FA_CLOUD_ARROW_UP, "Save", ImVec2(80.f, 28.f));
}

void ksd::RenderAimAssistPageBody(float fContentStartX)
{
    AimAssistState& aState = gAimAssistState;
    (void)fContentStartX;
    static const char* const ppTriggerHitChanceTypes[] = { "Spread", "Strict", "Relaxed" };
    static const char* const ppTriggerHitGroups[] = { "Head, Neck, Chest", "Head", "Chest" };
    const int iTriggerHitChanceTypeCount = (int)(sizeof(ppTriggerHitChanceTypes) / sizeof(ppTriggerHitChanceTypes[0]));
    const int iTriggerHitGroupCount = (int)(sizeof(ppTriggerHitGroups) / sizeof(ppTriggerHitGroups[0]));

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
    ImGui::BeginChild("aimassistleft", ImVec2(fColumnWidth, 0.f), false, ImGuiWindowFlags_NoScrollbar);
    ksd::DrawSectionTitle("Trigger", fColumnWidth, fSectionTitleY, fSectionTitleSize, iSectionTitleColor);
    ImGui::SetCursorPosX(fColumnContentX);
    ImGui::SetCursorPosY(38.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Enable", &aState.isTriggerEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Through wall", &aState.canTriggerThroughWall, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Air check", &aState.shouldTriggerAirCheck, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Auto scope", &aState.shouldTriggerAutoScope, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Scope check", &aState.shouldTriggerScopeCheck, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Flash check", &aState.shouldTriggerFlashCheck, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Smoke check", &aState.shouldTriggerSmokeCheck, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Ignore breakables", &aState.shouldTriggerIgnoreBreakables, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawFloatSlider("Lock camera after shot", &aState.triggerLockCameraAfterShot, 0.f, 1.f, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawFloatSlider("Delay between shots", &aState.triggerDelayBetweenShots, 0.f, 1.f, 240.f);
    {
        const float fHitChanceTypeRowY = ImGui::GetCursorPosY();
        ksd::DrawInlineLabel("Hit chance type", fColumnContentX, fHitChanceTypeRowY + fInlineLabelOffsetY);
        ImGui::SetCursorPos(ImVec2(fInlineComboX, fHitChanceTypeRowY));
        ksd::DrawCustomCombo("aimassisthitchancetype", &aState.triggerHitChanceType, ppTriggerHitChanceTypes, iTriggerHitChanceTypeCount, ImVec2(fInlineComboWidth, fInlineRowHeight));
        ImGui::SetCursorPosY(fHitChanceTypeRowY + fInlineRowHeight);
    }
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Visible", &aState.isTriggerVisibleOnly, 240.f);
    {
        const float fHitGroupsRowY = ImGui::GetCursorPosY();
        ksd::DrawInlineLabel("Hit groups", fColumnContentX, fHitGroupsRowY + fInlineLabelOffsetY);
        ImGui::SetCursorPos(ImVec2(fInlineComboX, fHitGroupsRowY));
        ksd::DrawCustomCombo("aimassisthitgroups", &aState.triggerHitGroups, ppTriggerHitGroups, iTriggerHitGroupCount, ImVec2(fInlineComboWidth, fInlineRowHeight));
        ImGui::SetCursorPosY(fHitGroupsRowY + fInlineRowHeight);
    }
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawIntSlider("Minimum damage", &aState.triggerMinimumDamage, 0, 100, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawIntSlider("Minimum hit chance", &aState.triggerMinimumHitChance, 0, 100, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawIntSlider("Reaction time", &aState.triggerReactionTime, 0, 100, 240.f);
    ImGui::EndChild();

    ImGui::SetCursorPos(ImVec2(fRightColumnX, 0.f));
    ImGui::BeginChild("aimassistright", ImVec2(fColumnWidth, 0.f), false, ImGuiWindowFlags_NoScrollbar);
    ksd::DrawSectionTitle("RCS", fColumnWidth, fSectionTitleY, fSectionTitleSize, iSectionTitleColor);
    ImGui::SetCursorPosX(fColumnContentX);
    ImGui::SetCursorPosY(38.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Enable", &aState.isRcsEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Return crosshair", &aState.shouldRcsReturnCrosshair, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawIntSlider("Bullet start", &aState.rcsBulletStart, 0, 30, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawIntSlider("Bullet end", &aState.rcsBulletEnd, 0, 30, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawFloatSlider("X", &aState.rcsX, 0.f, 2.f, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawFloatSlider("Y", &aState.rcsY, 0.f, 2.f, 240.f);

    {
        ImFont* pFont = ImGui::GetFont();
        ImDrawList* pDrawList = ImGui::GetWindowDrawList();
        const ImVec2 aWindowPos = ImGui::GetWindowPos();
        const ImVec2 aTitleSize = pFont->CalcTextSizeA(fSectionTitleSize, FLT_MAX, 0.f, "Auto Pistol");
        const float fTextY = ImGui::GetCursorPosY() + 8.f;
        pDrawList->AddText(pFont, fSectionTitleSize, ImVec2(aWindowPos.x + ((fColumnWidth - aTitleSize.x) * 0.5f), aWindowPos.y + fTextY), iSectionTitleColor, "Auto Pistol");
        ImGui::SetCursorPosY(fTextY + 22.f);
    }
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Enable", &aState.isAutoPistolEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawIntSlider("Delay between shots", &aState.autoPistolDelay, 0, 100, 240.f);
    ImGui::EndChild();
}
