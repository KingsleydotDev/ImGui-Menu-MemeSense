#include "pagemiscellaneous.h"
#include "../custom_imgui.h"
#include "../custom_settings.h"
#include "../var.h"
#include "imgui.h"
#include "../../../ext/fonts/iconsfontawesome/IconsFontAwesome7.h"
#include <cfloat>

namespace
{
struct MiscellaneousPageState
{
    int safeMode = 0;
    bool isMasterEnabled = false;
    bool isBunnyHopEnabled = false;
    bool isJumpBugEnabled = false;
    bool isEdgeJumpEnabled = false;
    bool isAutoStrafeEnabled = false;
    bool isFastStopEnabled = false;
    bool isClanTagEnabled = false;
    bool isAutoAcceptEnabled = false;
    bool isRevealRanksEnabled = false;
    bool isLogWeaponPurchasesEnabled = false;
    bool isAntiAfkEnabled = false;
    int strafeStrength = 50;
    int clanTagSpeed = 3;
};

MiscellaneousPageState gMiscellaneousPageState;
}

void ksd::RenderMiscellaneousPageHead(float fContentStartX, float fHeadCheckboxY)
{
    MiscellaneousPageState& aState = gMiscellaneousPageState;
    static const char* const ppSafe[] = { "Off", "Legit", "Strict" };
    const int iSafeCount = (int)(sizeof(ppSafe) / sizeof(ppSafe[0]));
    const float fTopComboWidth = 124.f;
    const float fTopComboHeight = MenuSettings::fPageInlineRowHeight;
    const float fTopComboX = fContentStartX + 140.f;

    ImGui::SetCursorPos(ImVec2(fContentStartX, fHeadCheckboxY));
    ksd::DrawCheckbox("Master switch", &aState.isMasterEnabled);
    ImGui::SetCursorPos(ImVec2(fTopComboX, fHeadCheckboxY));
    ksd::DrawCustomCombo("miscsafemode", &aState.safeMode, ppSafe, iSafeCount, ImVec2(fTopComboWidth, fTopComboHeight));
    ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x - 28.f - 80.f, fHeadCheckboxY));
    ksd::DrawIconTextButton(ICON_FA_CLOUD_ARROW_UP, "Save", ImVec2(80.f, 28.f));
}

void ksd::RenderMiscellaneousPageBody(float fContentStartX)
{
    MiscellaneousPageState& aState = gMiscellaneousPageState;
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
    ImGui::BeginChild("miscleft", ImVec2(fColumnWidth, 0.f), false, ImGuiWindowFlags_NoScrollbar);
    ksd::DrawSectionTitle("Movement", fColumnWidth, fSectionTitleY, fSectionTitleSize, iSectionTitleColor);
    ImGui::SetCursorPosX(fColumnContentX);
    ImGui::SetCursorPosY(38.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Bunny hop", &aState.isBunnyHopEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Jump bug", &aState.isJumpBugEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Edge jump", &aState.isEdgeJumpEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Auto strafe", &aState.isAutoStrafeEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawIntSlider("Strafe assist", &aState.strafeStrength, 0, 100, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Fast stop", &aState.isFastStopEnabled, 240.f);
    ImGui::EndChild();

    ImGui::SetCursorPos(ImVec2(fRightColumnX, 0.f));
    ImGui::BeginChild("miscright", ImVec2(fColumnWidth, 0.f), false, ImGuiWindowFlags_NoScrollbar);
    ksd::DrawSectionTitle("Other", fColumnWidth, fSectionTitleY, fSectionTitleSize, iSectionTitleColor);
    ImGui::SetCursorPosX(fColumnContentX);
    ImGui::SetCursorPosY(38.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Clan tag", &aState.isClanTagEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawIntSlider("Clan tag speed", &aState.clanTagSpeed, 1, 10, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Auto accept match", &aState.isAutoAcceptEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Reveal competitive ranks", &aState.isRevealRanksEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Log weapon purchases", &aState.isLogWeaponPurchasesEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Anti AFK", &aState.isAntiAfkEnabled, 240.f);
    ImGui::EndChild();
}
