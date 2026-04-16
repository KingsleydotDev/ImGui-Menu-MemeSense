#include "pageplayers.h"
#include "../custom_imgui.h"
#include "../custom_settings.h"
#include "../var.h"
#include "imgui.h"
#include "../../../ext/fonts/iconsfontawesome/IconsFontAwesome7.h"
#include <cfloat>

namespace
{
struct PlayersPageState
{
    int espMode = 0;
    bool isMasterEnabled = false;
    bool isBoxEnabled = true;
    bool isNameEnabled = true;
    bool isHealthBarEnabled = true;
    bool isArmorBarEnabled = false;
    bool isDistanceEnabled = true;
    bool isWeaponTextEnabled = true;
    bool isAmmoEnabled = false;
    bool isSkeletonEnabled = false;
    bool isHitboxEnabled = false;
    bool isSnaplinesEnabled = false;
    bool isGlowEnabled = false;
    bool isDormantEnabled = true;
    bool isTeamCheckEnabled = true;
    bool isVisibleOnlyEnabled = false;
    int snaplineOrigin = 0;
    int boxType = 0;
    int healthBarStyle = 0;
    int namePosition = 0;
    int maxDistance = 2000;
    int fontSize = 12;
    float boxThickness = 1.2f;
};

PlayersPageState gPlayersPageState;
}

void ksd::RenderPlayersPageHead(float fContentStartX, float fHeadCheckboxY)
{
    PlayersPageState& aState = gPlayersPageState;
    static const char* const ppEspModes[] = { "Enemies", "All", "Team only" };
    const int iEspModeCount = (int)(sizeof(ppEspModes) / sizeof(ppEspModes[0]));
    const float fTopComboWidth = 124.f;
    const float fTopComboHeight = MenuSettings::fPageInlineRowHeight;
    const float fTopComboX = fContentStartX + 140.f;

    ImGui::SetCursorPos(ImVec2(fContentStartX, fHeadCheckboxY));
    ksd::DrawCheckbox("Master switch", &aState.isMasterEnabled);
    ImGui::SetCursorPos(ImVec2(fTopComboX, fHeadCheckboxY));
    ksd::DrawCustomCombo("playersespmode", &aState.espMode, ppEspModes, iEspModeCount, ImVec2(fTopComboWidth, fTopComboHeight));
    ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x - 28.f - 80.f, fHeadCheckboxY));
    ksd::DrawIconTextButton(ICON_FA_CLOUD_ARROW_UP, "Save", ImVec2(80.f, 28.f));
}

void ksd::RenderPlayersPageBody(float fContentStartX)
{
    PlayersPageState& aState = gPlayersPageState;
    (void)fContentStartX;
    static const char* const ppSnaplineOrigins[] = { "Bottom", "Center", "Top" };
    static const char* const ppBoxTypes[] = { "2D", "3D corners", "3D full" };
    static const char* const ppHealthStyles[] = { "Bar", "Text", "Both" };
    static const char* const ppNamePositions[] = { "Top", "Bottom", "Side" };
    const int iSnaplineCount = (int)(sizeof(ppSnaplineOrigins) / sizeof(ppSnaplineOrigins[0]));
    const int iBoxTypeCount = (int)(sizeof(ppBoxTypes) / sizeof(ppBoxTypes[0]));
    const int iHealthStyleCount = (int)(sizeof(ppHealthStyles) / sizeof(ppHealthStyles[0]));
    const int iNamePosCount = (int)(sizeof(ppNamePositions) / sizeof(ppNamePositions[0]));

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
    ImGui::BeginChild("playersleft", ImVec2(fColumnWidth, 0.f), false, ImGuiWindowFlags_NoScrollbar);
    ksd::DrawSectionTitle("Player ESP", fColumnWidth, fSectionTitleY, fSectionTitleSize, iSectionTitleColor);
    ImGui::SetCursorPosX(fColumnContentX);
    ImGui::SetCursorPosY(38.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Bounding box", &aState.isBoxEnabled, 240.f);
    {
        const float fRowY = ImGui::GetCursorPosY();
        ksd::DrawInlineLabel("Box type", fColumnContentX, fRowY + fInlineLabelOffsetY);
        ImGui::SetCursorPos(ImVec2(fInlineComboX, fRowY));
        ksd::DrawCustomCombo("playersboxtype", &aState.boxType, ppBoxTypes, iBoxTypeCount, ImVec2(fInlineComboWidth, fInlineRowHeight));
        ImGui::SetCursorPosY(fRowY + fInlineRowHeight);
    }
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawFloatSlider("Box thickness", &aState.boxThickness, 0.5f, 3.f, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Name", &aState.isNameEnabled, 240.f);
    {
        const float fRowY = ImGui::GetCursorPosY();
        ksd::DrawInlineLabel("Name position", fColumnContentX, fRowY + fInlineLabelOffsetY);
        ImGui::SetCursorPos(ImVec2(fInlineComboX, fRowY));
        ksd::DrawCustomCombo("playersnamepos", &aState.namePosition, ppNamePositions, iNamePosCount, ImVec2(fInlineComboWidth, fInlineRowHeight));
        ImGui::SetCursorPosY(fRowY + fInlineRowHeight);
    }
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Health bar", &aState.isHealthBarEnabled, 240.f);
    {
        const float fRowY = ImGui::GetCursorPosY();
        ksd::DrawInlineLabel("Health style", fColumnContentX, fRowY + fInlineLabelOffsetY);
        ImGui::SetCursorPos(ImVec2(fInlineComboX, fRowY));
        ksd::DrawCustomCombo("playershealthstyle", &aState.healthBarStyle, ppHealthStyles, iHealthStyleCount, ImVec2(fInlineComboWidth, fInlineRowHeight));
        ImGui::SetCursorPosY(fRowY + fInlineRowHeight);
    }
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Armor bar", &aState.isArmorBarEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Distance", &aState.isDistanceEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Weapon text", &aState.isWeaponTextEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Ammo text", &aState.isAmmoEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawIntSlider("Max distance", &aState.maxDistance, 0, 5000, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawIntSlider("Font size", &aState.fontSize, 8, 24, 240.f);
    ImGui::EndChild();

    ImGui::SetCursorPos(ImVec2(fRightColumnX, 0.f));
    ImGui::BeginChild("playersright", ImVec2(fColumnWidth, 0.f), false, ImGuiWindowFlags_NoScrollbar);
    ksd::DrawSectionTitle("Extra", fColumnWidth, fSectionTitleY, fSectionTitleSize, iSectionTitleColor);
    ImGui::SetCursorPosX(fColumnContentX);
    ImGui::SetCursorPosY(38.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Skeleton", &aState.isSkeletonEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Hitboxes", &aState.isHitboxEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Snaplines", &aState.isSnaplinesEnabled, 240.f);
    {
        const float fRowY = ImGui::GetCursorPosY();
        ksd::DrawInlineLabel("Snapline origin", fColumnContentX, fRowY + fInlineLabelOffsetY);
        ImGui::SetCursorPos(ImVec2(fInlineComboX, fRowY));
        ksd::DrawCustomCombo("playerssnaporigin", &aState.snaplineOrigin, ppSnaplineOrigins, iSnaplineCount, ImVec2(fInlineComboWidth, fInlineRowHeight));
        ImGui::SetCursorPosY(fRowY + fInlineRowHeight);
    }
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Glow outline", &aState.isGlowEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Dormant ESP", &aState.isDormantEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Team check", &aState.isTeamCheckEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Visible only", &aState.isVisibleOnlyEnabled, 240.f);
    ImGui::EndChild();
}
