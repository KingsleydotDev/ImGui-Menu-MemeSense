#include "pageinventory.h"
#include "../custom_imgui.h"
#include "../custom_settings.h"
#include "../var.h"
#include "imgui.h"
#include "../../../ext/fonts/iconsfontawesome/IconsFontAwesome7.h"
#include <cfloat>

namespace
{
struct InventoryPageState
{
    int selectedWeapon = 0;
    int skinSectionTab = 0;
    int paintKitIndex = 0;
    bool isMasterEnabled = false;
    bool isStatTrakEnabled = false;
    bool isNametagEnabled = false;
    bool isSeedRandomEnabled = false;
    float wearValue = 0.12f;
    int patternSeed = 661;
    int stickerSlot = 0;
};

InventoryPageState gInventoryPageState;
}

void ksd::RenderInventoryPageHead(float fContentStartX, float fHeadCheckboxY)
{
    InventoryPageState& aState = gInventoryPageState;
    static const char* const ppWeapons[] = { "AK-47", "M4A4", "M4A1-S", "AWP", "USP-S", "Glock-18", "Desert Eagle" };
    const int iWeaponCount = (int)(sizeof(ppWeapons) / sizeof(ppWeapons[0]));
    const float fTopComboWidth = 124.f;
    const float fTopComboHeight = MenuSettings::fPageInlineRowHeight;
    const float fTopComboX = fContentStartX + 140.f;

    ImGui::SetCursorPos(ImVec2(fContentStartX, fHeadCheckboxY));
    ksd::DrawCheckbox("Master switch", &aState.isMasterEnabled);
    ImGui::SetCursorPos(ImVec2(fTopComboX, fHeadCheckboxY));
    ksd::DrawCustomCombo("inventoryweapon", &aState.selectedWeapon, ppWeapons, iWeaponCount, ImVec2(fTopComboWidth, fTopComboHeight));
    ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x - 28.f - 80.f, fHeadCheckboxY));
    ksd::DrawIconTextButton(ICON_FA_CLOUD_ARROW_UP, "Save", ImVec2(80.f, 28.f));
}

void ksd::RenderInventoryPageBody(float fContentStartX)
{
    InventoryPageState& aState = gInventoryPageState;
    (void)fContentStartX;
    static const char* const ppSkins[] = { "Vanilla", "Asiimov", "Dragon Lore", "Fade", "Doppler", "Printstream", "Neo-Noir" };
    static const char* const ppStickerSlots[] = { "Slot 1", "Slot 2", "Slot 3", "Slot 4" };
    static const char* const ppSkinTabs[] = { "Paint", "Stickers", "Charms" };
    const int iSkinCount = (int)(sizeof(ppSkins) / sizeof(ppSkins[0]));
    const int iStickerCount = (int)(sizeof(ppStickerSlots) / sizeof(ppStickerSlots[0]));
    const int iTabCount = (int)(sizeof(ppSkinTabs) / sizeof(ppSkinTabs[0]));

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
    ImGui::BeginChild("inventoryleft", ImVec2(fColumnWidth, 0.f), false, ImGuiWindowFlags_NoScrollbar);
    ksd::DrawSectionTitle("Skin", fColumnWidth, fSectionTitleY, fSectionTitleSize, iSectionTitleColor);
    ImGui::SetCursorPosX(fColumnContentX);
    ImGui::SetCursorPosY(38.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawTextSelector("inventoryskintabs", &aState.skinSectionTab, ppSkinTabs, iTabCount, 240.f);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 6.f);
    {
        const float fRowY = ImGui::GetCursorPosY();
        ksd::DrawInlineLabel("Paint kit", fColumnContentX, fRowY + fInlineLabelOffsetY);
        ImGui::SetCursorPos(ImVec2(fInlineComboX, fRowY));
        ksd::DrawCustomCombo("inventorypaint", &aState.paintKitIndex, ppSkins, iSkinCount, ImVec2(fInlineComboWidth, fInlineRowHeight));
        ImGui::SetCursorPosY(fRowY + fInlineRowHeight + 4.f);
    }
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawFloatSlider("Wear", &aState.wearValue, 0.f, 1.f, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Random seed", &aState.isSeedRandomEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawIntSlider("Pattern seed", &aState.patternSeed, 0, 1000, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("StatTrak", &aState.isStatTrakEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Nametag", &aState.isNametagEnabled, 240.f);
    ImGui::EndChild();

    ImGui::SetCursorPos(ImVec2(fRightColumnX, 0.f));
    ImGui::BeginChild("inventoryright", ImVec2(fColumnWidth, 0.f), false, ImGuiWindowFlags_NoScrollbar);
    ksd::DrawSectionTitle("Stickers", fColumnWidth, fSectionTitleY, fSectionTitleSize, iSectionTitleColor);
    ImGui::SetCursorPosX(fColumnContentX);
    ImGui::SetCursorPosY(38.f);
    {
        const float fRowY = ImGui::GetCursorPosY();
        ksd::DrawInlineLabel("Slot", fColumnContentX, fRowY + fInlineLabelOffsetY);
        ImGui::SetCursorPos(ImVec2(fInlineComboX, fRowY));
        ksd::DrawCustomCombo("inventoryslot", &aState.stickerSlot, ppStickerSlots, iStickerCount, ImVec2(fInlineComboWidth, fInlineRowHeight));
        ImGui::SetCursorPosY(fRowY + fInlineRowHeight + 4.f);
    }
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::Button("Apply sticker", ImVec2(240.f, 28.f));
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::Button("Remove all stickers", ImVec2(240.f, 28.f));
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawIconTextButton(ICON_FA_ROTATE, "Force update", ImVec2(240.f, 28.f));
    ImGui::EndChild();
}
