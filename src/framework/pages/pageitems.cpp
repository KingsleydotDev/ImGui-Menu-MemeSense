#include "pageitems.h"
#include "../custom_imgui.h"
#include "../custom_settings.h"
#include "../var.h"
#include "imgui.h"
#include "../../../ext/fonts/iconsfontawesome/IconsFontAwesome7.h"
#include <cfloat>
#include <cstdio>

namespace
{
struct ItemsPageState
{
    int itemsMode = 0;
    bool isItemsMasterEnabled = false;
    bool isItemsPopupEnabled = false;
};

ItemsPageState gItemsPageState;

struct ItemEntryState
{
    bool isBaseEnabled;
    bool isTintEnabled;
    ImVec4 tintColor;
    bool isInnerEnabled;
    ImVec4 innerColor;
    bool isDetailEnabled;
    ImVec4 detailColor;
};

ImVec4 CreatePlaceholderColor(int seedValue)
{
    unsigned int seed = (unsigned int)(seedValue * 1103515245 + 12345);
    const float red = (float)((seed >> 16) & 0xFF) / 255.f;
    seed = seed * 1103515245 + 12345;
    const float green = (float)((seed >> 16) & 0xFF) / 255.f;
    seed = seed * 1103515245 + 12345;
    const float blue = (float)((seed >> 16) & 0xFF) / 255.f;
    return ImVec4(red, green, blue, 1.f);
}

void InitializeItemState(ItemEntryState* pState, int rowIndex, int listSeedOffset)
{
    if (!pState)
    {
        return;
    }
    pState->isBaseEnabled = false;
    pState->isTintEnabled = false;
    pState->tintColor = CreatePlaceholderColor(listSeedOffset + rowIndex * 3 + 0);
    pState->isInnerEnabled = false;
    pState->innerColor = CreatePlaceholderColor(listSeedOffset + rowIndex * 3 + 1);
    pState->isDetailEnabled = false;
    pState->detailColor = CreatePlaceholderColor(listSeedOffset + rowIndex * 3 + 2);
}

bool DrawSmallCheckbox(const char* pId, bool* pValue)
{
    constexpr float fSize = 16.f;
    constexpr float fRounding = 3.f;
    constexpr ImVec4 uncheckedColor = ImVec4(29.f / 255.f, 30.f / 255.f, 34.f / 255.f, 1.f);
    if (!pId || !pValue)
    {
        return false;
    }

    char szId[128] = {};
    snprintf(szId, sizeof(szId), "##%s", pId);
    const bool bPressed = ImGui::InvisibleButton(szId, ImVec2(fSize, fSize));
    if (bPressed)
    {
        *pValue = !(*pValue);
    }

    const ImVec2 aMin = ImGui::GetItemRectMin();
    const ImVec2 aMax = ImGui::GetItemRectMax();
    ImDrawList* pDrawList = ImGui::GetWindowDrawList();
    const ImU32 iUnchecked = ImGui::GetColorU32(uncheckedColor);
    const ImU32 iAccent = ImGui::GetColorU32(MenuVars::accentColor);
    const ImU32 iWhite = ImGui::GetColorU32(ImVec4(1.f, 1.f, 1.f, 1.f));
    pDrawList->AddRectFilled(aMin, aMax, *pValue ? iAccent : iUnchecked, fRounding);
    if (*pValue)
    {
        const ImVec2 aStart = ImVec2(aMin.x + (fSize * 0.22f), aMin.y + (fSize * 0.54f));
        const ImVec2 aMid = ImVec2(aMin.x + (fSize * 0.42f), aMin.y + (fSize * 0.74f));
        const ImVec2 aEnd = ImVec2(aMin.x + (fSize * 0.78f), aMin.y + (fSize * 0.30f));
        pDrawList->PathLineTo(aStart);
        pDrawList->PathLineTo(aMid);
        pDrawList->PathLineTo(aEnd);
        pDrawList->PathStroke(iWhite, 0, 2.4f);
    }
    return bPressed;
}

void DrawLineLabel(const char* pLabel, float fX, float fY, const ImU32 iColor)
{
    ImFont* pFont = ImGui::GetFont();
    ImDrawList* pDrawList = ImGui::GetWindowDrawList();
    const ImVec2 aWindowPos = ImGui::GetWindowPos();
    pDrawList->AddText(pFont, 15.f, ImVec2(aWindowPos.x + fX, aWindowPos.y + fY), iColor, pLabel);
}

void DrawItemsRow(const char* pRowId, const char* pLabel, ItemEntryState* pState, float fColumnWidth, float fLabelX)
{
    if (!pState)
    {
        return;
    }

    constexpr float fControlSize = 16.f;
    constexpr float fControlGap = 6.f;
    constexpr float fRowHeight = 24.f;
    const float fRowY = ImGui::GetCursorPosY();
    const ImU32 iDimText = ImGui::GetColorU32(ImVec4(115.f / 255.f, 116.f / 255.f, 121.f / 255.f, 1.f));
    DrawLineLabel(pLabel, fLabelX, fRowY + 3.f, iDimText);

    const float fControlsWidth = (fControlSize * 4.f) + (fControlGap * 3.f);
    float fControlX = fColumnWidth - fControlsWidth;

    char szIdTint[128] = {};
    snprintf(szIdTint, sizeof(szIdTint), "%stint", pRowId);
    ImGui::SetCursorPos(ImVec2(fControlX, fRowY));
    ksd::DrawColorPickerCheckbox(szIdTint, &pState->isTintEnabled, &pState->tintColor);

    char szIdInner[128] = {};
    snprintf(szIdInner, sizeof(szIdInner), "%sinner", pRowId);
    fControlX += fControlSize + fControlGap;
    ImGui::SetCursorPos(ImVec2(fControlX, fRowY));
    ksd::DrawColorPickerCheckbox(szIdInner, &pState->isInnerEnabled, &pState->innerColor);

    char szIdDetail[128] = {};
    snprintf(szIdDetail, sizeof(szIdDetail), "%sdetail", pRowId);
    fControlX += fControlSize + fControlGap;
    ImGui::SetCursorPos(ImVec2(fControlX, fRowY));
    ksd::DrawColorPickerCheckbox(szIdDetail, &pState->isDetailEnabled, &pState->detailColor);

    char szIdBase[128] = {};
    snprintf(szIdBase, sizeof(szIdBase), "%sbase", pRowId);
    fControlX += fControlSize + fControlGap;
    ImGui::SetCursorPos(ImVec2(fControlX, fRowY));
    DrawSmallCheckbox(szIdBase, &pState->isBaseEnabled);

    ImGui::SetCursorPosY(fRowY + fRowHeight);
}

void DrawItemsHeader(float fColumnWidth, float fHeaderY)
{
    constexpr float fControlSize = 16.f;
    constexpr float fControlGap = 6.f;
    const float fControlsWidth = (fControlSize * 4.f) + (fControlGap * 3.f);
    const float fControlsStartX = fColumnWidth - fControlsWidth;
    const ImU32 iDimText = ImGui::GetColorU32(ImVec4(115.f / 255.f, 116.f / 255.f, 121.f / 255.f, 1.f));
    DrawLineLabel("Item name", 0.f, fHeaderY, iDimText);

    const char* ppLetters[4] = { "B", "T", "I", "D" };
    const int iLetterCount = (int)(sizeof(ppLetters) / sizeof(ppLetters[0]));
    ImFont* pFont = ImGui::GetFont();
    ImDrawList* pDrawList = ImGui::GetWindowDrawList();
    const ImVec2 aWindowPos = ImGui::GetWindowPos();
    for (int iLetter = 0; iLetter < iLetterCount; ++iLetter)
    {
        const ImVec2 aTextSize = pFont->CalcTextSizeA(MenuSettings::fDefaultTextSize, FLT_MAX, 0.f, ppLetters[iLetter]);
        const float fCenterX = fControlsStartX + (iLetter * (fControlSize + fControlGap)) + (fControlSize * 0.5f);
        const float fTextX = fCenterX - (aTextSize.x * 0.5f);
        pDrawList->AddText(pFont, MenuSettings::fDefaultTextSize, ImVec2(aWindowPos.x + fTextX, aWindowPos.y + fHeaderY), iDimText, ppLetters[iLetter]);
    }
}

void DrawItemsMasterPopup()
{
    ItemsPageState& aState = gItemsPageState;
    ImGui::SetCursorPos(ImVec2(28.f, 20.f));
    ksd::DrawCheckbox("Enable items", &aState.isItemsPopupEnabled, 200.f);
}
}

void ksd::RenderItemsPageHead(float fContentStartX, float fHeadCheckboxY)
{
    ItemsPageState& aState = gItemsPageState;
    static const char* const ppItemsMode[] = { "Through wall", "Visible only", "Off" };
    const int iItemsModeCount = (int)(sizeof(ppItemsMode) / sizeof(ppItemsMode[0]));
    const float fTopComboWidth = 124.f;
    const float fTopComboHeight = MenuSettings::fPageInlineRowHeight;
    const float fTopComboFirstX = fContentStartX + 140.f;

    ImGui::SetCursorPos(ImVec2(fContentStartX, fHeadCheckboxY));
    ksd::DrawCheckboxIconPopup("Master switch", &aState.isItemsMasterEnabled, 22.f, -2.f, ICON_FA_GEAR, "itemsmasterpopup", 0.f, DrawItemsMasterPopup);
    ImGui::SetCursorPos(ImVec2(fTopComboFirstX, fHeadCheckboxY));
    ksd::DrawCustomCombo("itemsmode", &aState.itemsMode, ppItemsMode, iItemsModeCount, ImVec2(fTopComboWidth, fTopComboHeight));
    ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x - 28.f - 80.f, fHeadCheckboxY));
    ksd::DrawIconTextButton(ICON_FA_CLOUD_ARROW_UP, "Save", ImVec2(80.f, 28.f));
}

void ksd::RenderItemsPageBody(float fContentStartX)
{
    (void)fContentStartX;
    static const char* const ppLeftLabels[] =
    {
        "C4", "Planted C4", "Defuse kit", "Shield", "Snowball", "Health shot",
        "Chicken", "Hostage", "Taser", "Knife", "Pistol", "Rifle",
        "Shotgun", "Sniper", "Machine gun", "Submachine gun"
    };
    static const char* const ppRightLabels[] =
    {
        "Grenade", "Decoy", "Flashbang", "Smoke grenade", "Incendiary grenade", "Tactical grenade",
        "Grenade projectile", "Decoy projectile", "Flashbang projectile", "Smoke projectile", "Molotov projectile"
    };
    static ItemEntryState gaLeftState[16] = {};
    static ItemEntryState gaRightState[11] = {};
    static bool gbItemsStateInitialized = false;
    const int iLeftLabelCount = (int)(sizeof(ppLeftLabels) / sizeof(ppLeftLabels[0]));
    const int iRightLabelCount = (int)(sizeof(ppRightLabels) / sizeof(ppRightLabels[0]));

    const float fBodyWidth = ImGui::GetWindowSize().x;
    const float fColumnWidth = MenuSettings::fPageColumnWidth;
    const float fLeftMargin = MenuSettings::fPageLeftMargin;
    const float fRightMargin = MenuSettings::fPageRightMargin;
    const float fRightColumnX = fBodyWidth - fRightMargin - fColumnWidth;
    const float fHeaderY = 10.f;
    const float fLabelX = 0.f;
    const float fLabelLineY = 36.f;
    if (!gbItemsStateInitialized)
    {
        for (int iRow = 0; iRow < iLeftLabelCount; ++iRow)
        {
            InitializeItemState(&gaLeftState[iRow], iRow, 17);
        }
        for (int iRow = 0; iRow < iRightLabelCount; ++iRow)
        {
            InitializeItemState(&gaRightState[iRow], iRow, 173);
        }
        gbItemsStateInitialized = true;
    }

    ImGui::SetCursorPos(ImVec2(fLeftMargin, 0.f));
    ImGui::BeginChild("itemsleft", ImVec2(fColumnWidth, 0.f), false, ImGuiWindowFlags_NoScrollbar);
    DrawItemsHeader(fColumnWidth, fHeaderY);
    ImGui::SetCursorPosY(fLabelLineY);
    for (int iRow = 0; iRow < iLeftLabelCount; ++iRow)
    {
        char szRowId[64] = {};
        snprintf(szRowId, sizeof(szRowId), "itemleft%d", iRow);
        DrawItemsRow(szRowId, ppLeftLabels[iRow], &gaLeftState[iRow], fColumnWidth, fLabelX);
    }
    ImGui::Dummy(ImVec2(0.f, 1.f));
    ImGui::EndChild();

    ImGui::SetCursorPos(ImVec2(fRightColumnX, 0.f));
    ImGui::BeginChild("itemsright", ImVec2(fColumnWidth, 0.f), false, ImGuiWindowFlags_NoScrollbar);
    DrawItemsHeader(fColumnWidth, fHeaderY);
    ImGui::SetCursorPosY(fLabelLineY);
    for (int iRow = 0; iRow < iRightLabelCount; ++iRow)
    {
        char szRowId[64] = {};
        snprintf(szRowId, sizeof(szRowId), "itemright%d", iRow);
        DrawItemsRow(szRowId, ppRightLabels[iRow], &gaRightState[iRow], fColumnWidth, fLabelX);
    }
    ImGui::Dummy(ImVec2(0.f, 1.f));
    ImGui::EndChild();
}
