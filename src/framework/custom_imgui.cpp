#include "custom_imgui.h"
#include "custom_settings.h"
#include "var.h"
#include "imgui.h"
#include <cfloat>
#include <cstring>
#include <cstdio>

namespace
{
ImFont* iconButtonFont = nullptr;
//kingsleydotDev
}

void ksd::ButtonSpacing()
{
    constexpr float fButtonGapY = 3.f;
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + fButtonGapY);
}

void ksd::Spacing()
{
    constexpr float fButtonSectionGapY = 10.f;
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + fButtonSectionGapY);
}

void ksd::SetIconButtonFont(ImFont* iconFont)
{
    iconButtonFont = iconFont;
}

void ksd::DrawBrandingText(ImFont* titleFont)
{
    ImGui::SetCursorPos(ImVec2(MenuSettings::fBrandX, MenuSettings::fBrandY));
    if (titleFont)
    {
        ImGui::PushFont(titleFont);
    }
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(255.f / 255.f, 40.f / 255.f, 54.f / 255.f, 1.f));
    ImGui::Text("Meme");
    ImGui::PopStyleColor();
    ImGui::SameLine(0.f, 0.f);
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 1.f));
    ImGui::Text("Sense");
    ImGui::PopStyleColor();
    if (titleFont)
    {
        ImGui::PopFont();
    }
}

void ksd::DrawInlineLabel(const char* label, float x, float y)
{
    ImFont* font = ImGui::GetFont();
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    const ImVec2 windowPos = ImGui::GetWindowPos();
    drawList->AddText(font, 15.f, ImVec2(windowPos.x + x, windowPos.y + y), ImGui::GetColorU32(ImVec4(1.f, 1.f, 1.f, 1.f)), label);
}

void ksd::DrawSectionTitle(const char* label, float columnWidth, float sectionTitleY, float sectionTitleSize, ImU32 sectionTitleColor)
{
    ImFont* font = ImGui::GetFont();
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    const ImVec2 windowPos = ImGui::GetWindowPos();
    const ImVec2 titleSize = font->CalcTextSizeA(sectionTitleSize, FLT_MAX, 0.f, label);
    drawList->AddText(font, sectionTitleSize, ImVec2(windowPos.x + ((columnWidth - titleSize.x) * 0.5f), windowPos.y + sectionTitleY), sectionTitleColor, label);
}

bool ksd::DrawSidebarButton(const char* label, const char* icon, bool isActive, ImFont* sidebarFont, ImFont* iconFont)
{
    constexpr float sidebarLabelStartX = 37.f;
    constexpr float buttonHoveredR = 34.f / 255.f;
    constexpr float buttonHoveredG = 35.f / 255.f;
    constexpr float buttonHoveredB = 38.f / 255.f;
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    const float buttonWidth = MenuSettings::fButtonWidth;
    const float buttonHeight = MenuSettings::fButtonHeight;
    char buttonId[128] = {};
    snprintf(buttonId, sizeof(buttonId), "##%s", label);

    ImGui::PushStyleColor(ImGuiCol_Button, isActive ? MenuSettings::activeColor : MenuSettings::inactiveColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(buttonHoveredR, buttonHoveredG, buttonHoveredB, 1.f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, MenuSettings::activeColor);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.f);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(12.f, 6.f));
    ImGui::SetCursorPosX(0.f);
    const bool isPressed = ImGui::Button(buttonId, ImVec2(buttonWidth, buttonHeight));
    ImGui::PopStyleVar(2);
    ImGui::PopStyleColor(3);

    const ImVec2 buttonPos = ImGui::GetItemRectMin();
    const ImVec2 buttonMax = ImGui::GetItemRectMax();
    const bool isHovered = ImGui::IsItemHovered();
    const float centerY = buttonPos.y + ((buttonMax.y - buttonPos.y) * 0.5f);
    const ImU32 whiteColor = ImGui::GetColorU32(ImVec4(1.f, 1.f, 1.f, 1.f));
    const ImU32 accentColor = ImGui::GetColorU32(MenuVars::accentColor);
    const ImU32 iconColor = (isActive || isHovered) ? accentColor : whiteColor;
    if (iconFont && icon)
    {
        const ImVec2 iconSize = iconFont->CalcTextSizeA(MenuSettings::fSidebarTextSize, FLT_MAX, 0.f, icon);
        const float iconAreaStartX = 2.f;
        const float iconAreaEndX = sidebarLabelStartX;
        const float iconCenterX = (iconAreaStartX + iconAreaEndX) * 0.5f;
        const ImVec2 iconPos = ImVec2(buttonPos.x + iconCenterX - (iconSize.x * 0.5f), centerY - (iconSize.y * 0.5f));
        drawList->AddText(iconFont, MenuSettings::fSidebarTextSize, iconPos, iconColor, icon);
    }
    if (sidebarFont)
    {
        const ImVec2 textSize = sidebarFont->CalcTextSizeA(MenuSettings::fSidebarTextSize, FLT_MAX, 0.f, label);
        const ImVec2 textPos = ImVec2(buttonPos.x + sidebarLabelStartX, centerY - (textSize.y * 0.5f));
        drawList->AddText(sidebarFont, MenuSettings::fSidebarTextSize, textPos, whiteColor, label);
    }

    if (isActive || isHovered)
    {
        drawList->AddRectFilled(
            buttonPos,
            ImVec2(buttonPos.x + 2.f, buttonPos.y + buttonHeight),
            accentColor
        );
    }
    return isPressed;
}

bool ksd::DrawCheckbox(const char* label, bool* value, float maxWidth)
{
    constexpr float fLabelFontSize = MenuSettings::fDefaultTextSize;
    constexpr float fCheckboxSize = 16.f;
    constexpr float fCheckboxElementHeight = 28.f;
    constexpr float fCheckboxRounding = 3.f;
    constexpr float fCheckboxLabelGapX = 9.f;
    constexpr ImVec4 checkboxUncheckedColor = ImVec4(29.f / 255.f, 30.f / 255.f, 34.f / 255.f, 1.f);
    constexpr float fCheckboxHoverAlpha = 0.25f;
    constexpr float fCheckboxTextUnchecked = 128.f / 255.f;
    if (!value)
    {
        return false;
    }

    const ImVec2 labelSize = ImGui::CalcTextSize(label, nullptr, true);
    const float fCheckboxSizeValue = fCheckboxSize;
    const ImVec2 aPos = ImGui::GetCursorScreenPos();
    const float fTotalHeight = fCheckboxElementHeight;
    const float fBoxOffsetY = (fTotalHeight - fCheckboxSizeValue) * 0.5f;
    const ImVec2 aBoxMin = ImVec2(aPos.x, aPos.y + fBoxOffsetY);
    const ImVec2 aBoxMax = ImVec2(aPos.x + fCheckboxSizeValue, aBoxMin.y + fCheckboxSizeValue);
    const float fNaturalWidth = fCheckboxSizeValue + fCheckboxLabelGapX + labelSize.x;
    const float fTotalWidth = maxWidth > 0.f ? maxWidth : fNaturalWidth;
    const bool bPressed = ImGui::InvisibleButton(label, ImVec2(fTotalWidth, fTotalHeight));
    const bool bHovered = ImGui::IsItemHovered();
    if (bPressed)
    {
        *value = !(*value);
    }

    ImDrawList* pDrawList = ImGui::GetWindowDrawList();
    const ImU32 iAccent = ImGui::GetColorU32(MenuVars::accentColor);
    const ImU32 iUnchecked = ImGui::GetColorU32(checkboxUncheckedColor);
    const ImU32 iHover = ImGui::GetColorU32(ImVec4(MenuVars::accentColor.x, MenuVars::accentColor.y, MenuVars::accentColor.z, fCheckboxHoverAlpha));
    const ImU32 iWhite = ImGui::GetColorU32(ImVec4(1.f, 1.f, 1.f, 1.f));
    const ImU32 iTextUnchecked = ImGui::GetColorU32(ImVec4(fCheckboxTextUnchecked, fCheckboxTextUnchecked, fCheckboxTextUnchecked, 1.f));

    ImU32 iBoxColor = iUnchecked;
    if (*value)
    {
        iBoxColor = iAccent;
    }
    else if (bHovered)
    {
        iBoxColor = iHover;
    }

    pDrawList->AddRectFilled(aBoxMin, aBoxMax, iBoxColor, fCheckboxRounding);

    if (*value)
    {
        const ImVec2 aStart = ImVec2(aBoxMin.x + (fCheckboxSizeValue * 0.22f), aBoxMin.y + (fCheckboxSizeValue * 0.54f));
        const ImVec2 aMid = ImVec2(aBoxMin.x + (fCheckboxSizeValue * 0.42f), aBoxMin.y + (fCheckboxSizeValue * 0.74f));
        const ImVec2 aEnd = ImVec2(aBoxMin.x + (fCheckboxSizeValue * 0.78f), aBoxMin.y + (fCheckboxSizeValue * 0.30f));
        pDrawList->PathLineTo(aStart);
        pDrawList->PathLineTo(aMid);
        pDrawList->PathLineTo(aEnd);
        pDrawList->PathStroke(iWhite, 0, 2.6f);
    }

    ImFont* pFont = ImGui::GetFont();
    const ImVec2 aLabelDrawSize = pFont ? pFont->CalcTextSizeA(fLabelFontSize, FLT_MAX, 0.f, label) : labelSize;
    const ImVec2 aTextPos(aBoxMax.x + fCheckboxLabelGapX, aPos.y + ((fTotalHeight - aLabelDrawSize.y) * 0.5f));
    pDrawList->AddText(pFont, fLabelFontSize, aTextPos, *value ? iWhite : iTextUnchecked, label);

    return bPressed;
}

bool ksd::DrawCheckboxIcon(const char* label, bool* value, float maxWidth, const char* icon)
{
    const bool bPressed = ksd::DrawCheckbox(label, value, maxWidth);
    if (!icon || !iconButtonFont)
    {
        return bPressed;
    }

    constexpr float fIconSize = MenuSettings::fDefaultTextSize;
    constexpr float fIconRightPadding = 0.f;
    constexpr float fTextUnchecked = 128.f / 255.f;
    const ImVec2 aItemMin = ImGui::GetItemRectMin();
    const ImVec2 aItemMax = ImGui::GetItemRectMax();
    const ImVec2 aIconTextSize = iconButtonFont->CalcTextSizeA(fIconSize, FLT_MAX, 0.f, icon);
    const ImVec2 aIconPos(
        aItemMax.x - fIconRightPadding - aIconTextSize.x,
        aItemMin.y + ((aItemMax.y - aItemMin.y - aIconTextSize.y) * 0.5f)
    );
    const ImU32 iIconColor = *value
        ? ImGui::GetColorU32(ImVec4(1.f, 1.f, 1.f, 1.f))
        : ImGui::GetColorU32(ImVec4(fTextUnchecked, fTextUnchecked, fTextUnchecked, 1.f));
    ImGui::GetWindowDrawList()->AddText(iconButtonFont, fIconSize, aIconPos, iIconColor, icon);
    return bPressed;
}

bool ksd::DrawColorPickerCheckbox(const char* id, bool* value, ImVec4* color)
{
    constexpr float fSize = 16.f;
    constexpr float fRounding = 3.f;
    constexpr ImVec4 uncheckedColor = ImVec4(29.f / 255.f, 30.f / 255.f, 34.f / 255.f, 1.f);
    constexpr float fHoverAlpha = 0.25f;
    if (!id || !value || !color)
    {
        return false;
    }

    bool bChanged = false;
    char szId[128] = {};
    snprintf(szId, sizeof(szId), "##%s", id);
    const bool bPressed = ImGui::InvisibleButton(szId, ImVec2(fSize, fSize));
    const bool bHovered = ImGui::IsItemHovered();
    if (bPressed)
    {
        *value = !(*value);
        bChanged = true;
    }

    char szPopupId[128] = {};
    snprintf(szPopupId, sizeof(szPopupId), "##popup%s", id);
    if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
    {
        ImGui::OpenPopup(szPopupId);
    }

    const ImVec2 aMin = ImGui::GetItemRectMin();
    const ImVec2 aMax = ImGui::GetItemRectMax();
    ImDrawList* pDrawList = ImGui::GetWindowDrawList();
    const ImU32 iUnchecked = ImGui::GetColorU32(uncheckedColor);
    const ImU32 iHover = ImGui::GetColorU32(ImVec4(MenuVars::accentColor.x, MenuVars::accentColor.y, MenuVars::accentColor.z, fHoverAlpha));
    const ImU32 iColor = ImGui::GetColorU32(*color);
    ImU32 iDrawColor = iUnchecked;
    if (*value)
    {
        iDrawColor = iColor;
    }
    else if (bHovered)
    {
        iDrawColor = iHover;
    }
    pDrawList->AddRectFilled(aMin, aMax, iDrawColor, fRounding);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, fRounding);
    if (ImGui::BeginPopup(szPopupId))
    {
        if (ImGui::ColorPicker4("##picker", (float*)color, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview | ImGuiColorEditFlags_NoInputs))
        {
            if (!*value)
            {
                *value = true;
            }
            bChanged = true;
        }
        ImGui::EndPopup();
    }
    ImGui::PopStyleVar();
    return bChanged;
}

bool ksd::DrawIconTextButton(const char* pIcon, const char* pLabel, const ImVec2& aSize)
{
    constexpr float fCheckboxRounding = 3.f;
    constexpr ImVec4 iconTextButtonColor = ImVec4(39.f / 255.f, 40.f / 255.f, 44.f / 255.f, 1.f);
    constexpr ImVec4 iconTextButtonHoverColor = ImVec4(98.f / 255.f, 101.f / 255.f, 110.f / 255.f, 1.f);
    constexpr float fIconTextButtonIconX = 6.f;
    constexpr float fIconTextButtonLabelX = 33.f;
    constexpr float fIconTextButtonTextSize = MenuSettings::fDefaultTextSize;
    char szButtonId[128] = {};
    snprintf(szButtonId, sizeof(szButtonId), "##%s%s", pIcon ? pIcon : "", pLabel ? pLabel : "");

    ImGui::PushStyleColor(ImGuiCol_Button, iconTextButtonColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, iconTextButtonHoverColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, MenuSettings::activeColor);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, fCheckboxRounding);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.f, 0.f));
    const bool bPressed = ImGui::Button(szButtonId, aSize);
    ImGui::PopStyleVar(2);
    ImGui::PopStyleColor(3);

    ImDrawList* pDrawList = ImGui::GetWindowDrawList();
    const ImVec2 aButtonMin = ImGui::GetItemRectMin();
    const ImVec2 aButtonMax = ImGui::GetItemRectMax();
    const float fCenterY = aButtonMin.y + ((aButtonMax.y - aButtonMin.y) * 0.5f);
    const ImU32 iTextColor = ImGui::GetColorU32(ImVec4(1.f, 1.f, 1.f, 1.f));

    ImFont* pLabelFont = ImGui::GetFont();
    ImFont* pIconFont = iconButtonFont ? iconButtonFont : pLabelFont;
    if (pIcon && pIconFont)
    {
        const ImVec2 aIconSize = pIconFont->CalcTextSizeA(fIconTextButtonTextSize, FLT_MAX, 0.f, pIcon);
        const ImVec2 aIconPos(aButtonMin.x + fIconTextButtonIconX, fCenterY - (aIconSize.y * 0.5f));
        pDrawList->AddText(pIconFont, fIconTextButtonTextSize, aIconPos, iTextColor, pIcon);
    }
    if (pLabel && pLabelFont)
    {
        const ImVec2 aLabelSize = pLabelFont->CalcTextSizeA(fIconTextButtonTextSize, FLT_MAX, 0.f, pLabel);
        const ImVec2 aLabelPos(aButtonMin.x + fIconTextButtonLabelX, fCenterY - (aLabelSize.y * 0.5f));
        pDrawList->AddText(pLabelFont, fIconTextButtonTextSize, aLabelPos, iTextColor, pLabel);
    }

    return bPressed;
}

bool ksd::Button(const char* pLabel, const ImVec2& aSize)
{
    constexpr float fCheckboxRounding = 3.f;
    constexpr ImVec4 iconTextButtonColor = ImVec4(39.f / 255.f, 40.f / 255.f, 44.f / 255.f, 1.f);
    constexpr ImVec4 iconTextButtonHoverColor = ImVec4(98.f / 255.f, 101.f / 255.f, 110.f / 255.f, 1.f);
    constexpr float fButtonLabelX = 6.f;
    constexpr float fButtonTextSize = MenuSettings::fDefaultTextSize;
    char szButtonId[128] = {};
    snprintf(szButtonId, sizeof(szButtonId), "##%s", pLabel ? pLabel : "");

    ImGui::PushStyleColor(ImGuiCol_Button, iconTextButtonColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, iconTextButtonHoverColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, MenuSettings::activeColor);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, fCheckboxRounding);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.f, 0.f));
    const bool bPressed = ImGui::Button(szButtonId, aSize);
    ImGui::PopStyleVar(2);
    ImGui::PopStyleColor(3);

    ImDrawList* pDrawList = ImGui::GetWindowDrawList();
    const ImVec2 aButtonMin = ImGui::GetItemRectMin();
    const ImVec2 aButtonMax = ImGui::GetItemRectMax();
    const float fCenterY = aButtonMin.y + ((aButtonMax.y - aButtonMin.y) * 0.5f);
    const ImU32 iTextColor = ImGui::GetColorU32(ImVec4(1.f, 1.f, 1.f, 1.f));
    ImFont* pLabelFont = ImGui::GetFont();
    if (pLabel && pLabelFont)
    {
        const ImVec2 aLabelSize = pLabelFont->CalcTextSizeA(fButtonTextSize, FLT_MAX, 0.f, pLabel);
        const ImVec2 aLabelPos(aButtonMin.x + fButtonLabelX, fCenterY - (aLabelSize.y * 0.5f));
        pDrawList->AddText(pLabelFont, fButtonTextSize, aLabelPos, iTextColor, pLabel);
    }

    return bPressed;
}

bool ksd::DrawCustomCombo(const char* pId, int* piValue, const char* const* ppItems, int iItemCount, const ImVec2& aSize)
{
    constexpr float fCheckboxRounding = 3.f;
    constexpr float fComboSpaceY = 3.f;
    constexpr float fComboShiftY = -3.f;
    constexpr ImVec4 iconTextButtonColor = ImVec4(39.f / 255.f, 40.f / 255.f, 44.f / 255.f, 1.f);
    constexpr float fIconTextButtonTextSize = MenuSettings::fDefaultTextSize;
    constexpr float fComboTextStartX = 8.f;
    constexpr float fComboItemHeight = 22.f;
    constexpr ImVec4 comboTextColor = ImVec4(115.f / 255.f, 116.f / 255.f, 121.f / 255.f, 1.f);
    constexpr ImVec4 comboTextHoverColor = ImVec4(196.f / 255.f, 198.f / 255.f, 202.f / 255.f, 1.f);
    constexpr float fComboPopupTopPadding = 8.f;
    if (!piValue || !ppItems || iItemCount <= 0)
    {
        return false;
    }

    if (*piValue < 0)
    {
        *piValue = 0;
    }
    if (*piValue >= iItemCount)
    {
        *piValue = iItemCount - 1;
    }

    bool bChanged = false;
    ImGui::PushID(pId);
    const ImVec2 aStartPos = ImGui::GetCursorPos();
    ImGui::SetCursorPos(ImVec2(aStartPos.x, aStartPos.y + fComboSpaceY + fComboShiftY));

    ImGui::PushStyleColor(ImGuiCol_Button, iconTextButtonColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, iconTextButtonColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, iconTextButtonColor);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, fCheckboxRounding);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.f, 0.f));
    const bool bPressed = ImGui::Button("##customcombo", aSize);
    ImGui::PopStyleVar(2);
    ImGui::PopStyleColor(3);

    const ImVec2 aComboMin = ImGui::GetItemRectMin();
    const ImVec2 aComboMax = ImGui::GetItemRectMax();
    const float fComboCenterY = aComboMin.y + ((aComboMax.y - aComboMin.y) * 0.5f);
    ImDrawList* pDrawList = ImGui::GetWindowDrawList();
    ImFont* pFont = ImGui::GetFont();
    const char* pPreview = ppItems[*piValue];
    char szPreview[256] = {};
    const ImU32 iPreviewColor = ImGui::GetColorU32(ImVec4(1.f, 1.f, 1.f, 1.f));
    const ImU32 iArrowColor = ImGui::GetColorU32(comboTextColor);

    if (pFont && pPreview)
    {
        const float fPreviewMaxWidth = (aComboMax.x - aComboMin.x) - fComboTextStartX - 18.f;
        snprintf(szPreview, sizeof(szPreview), "%s", pPreview);
        while (pFont->CalcTextSizeA(fIconTextButtonTextSize, FLT_MAX, 0.f, szPreview).x > fPreviewMaxWidth && strlen(szPreview) > 0)
        {
            const size_t iLen = strlen(szPreview);
            szPreview[iLen - 1] = '\0';
        }
        const ImVec2 aPreviewSize = pFont->CalcTextSizeA(fIconTextButtonTextSize, FLT_MAX, 0.f, szPreview);
        const ImVec2 aPreviewPos(aComboMin.x + fComboTextStartX, fComboCenterY - (aPreviewSize.y * 0.5f));
        pDrawList->AddText(pFont, fIconTextButtonTextSize, aPreviewPos, iPreviewColor, szPreview);
    }

    if (bPressed)
    {
        ImGui::OpenPopup("comboitems");
    }

    const bool bIsOpen = ImGui::IsPopupOpen("comboitems");
    if (bIsOpen)
    {
        const ImVec2 aArrowPointA(aComboMax.x - 14.f, fComboCenterY + 2.f);
        const ImVec2 aArrowPointB(aComboMax.x - 8.f, fComboCenterY + 2.f);
        const ImVec2 aArrowPointC(aComboMax.x - 11.f, fComboCenterY - 2.f);
        pDrawList->AddTriangleFilled(aArrowPointA, aArrowPointB, aArrowPointC, iArrowColor);
    }
    else
    {
        const ImVec2 aArrowPointA(aComboMax.x - 14.f, fComboCenterY - 2.f);
        const ImVec2 aArrowPointB(aComboMax.x - 8.f, fComboCenterY - 2.f);
        const ImVec2 aArrowPointC(aComboMax.x - 11.f, fComboCenterY + 2.f);
        pDrawList->AddTriangleFilled(aArrowPointA, aArrowPointB, aArrowPointC, iArrowColor);
    }

    ImGui::SetNextWindowPos(ImVec2(aComboMin.x, aComboMax.y - fCheckboxRounding - 1.f));
    ImGui::SetNextWindowSize(ImVec2(aSize.x, 0.f));
    ImGui::PushStyleColor(ImGuiCol_PopupBg, iconTextButtonColor);
    ImGui::PushStyleColor(ImGuiCol_Border, iconTextButtonColor);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, fCheckboxRounding);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, fComboPopupTopPadding));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.f, 0.f));
    if (ImGui::BeginPopup("comboitems"))
    {
        ImDrawList* pPopupDrawList = ImGui::GetWindowDrawList();
        for (int iItem = 0; iItem < iItemCount; ++iItem)
        {
            ImGui::PushID(iItem);
            const ImVec2 aItemMin = ImGui::GetCursorScreenPos();
            const bool bItemPressed = ImGui::InvisibleButton("item", ImVec2(aSize.x, fComboItemHeight));
            const bool bItemHovered = ImGui::IsItemHovered();
            const bool bItemSelected = *piValue == iItem;
            const ImU32 iItemTextColor = bItemSelected
                ? ImGui::GetColorU32(ImVec4(1.f, 1.f, 1.f, 1.f))
                : (bItemHovered
                    ? ImGui::GetColorU32(comboTextHoverColor)
                    : ImGui::GetColorU32(comboTextColor));
            if (pFont && ppItems[iItem])
            {
                const ImVec2 aItemTextSize = pFont->CalcTextSizeA(fIconTextButtonTextSize, FLT_MAX, 0.f, ppItems[iItem]);
                const ImVec2 aItemTextPos(aItemMin.x + fComboTextStartX, aItemMin.y + ((fComboItemHeight - aItemTextSize.y) * 0.5f));
                pPopupDrawList->AddText(pFont, fIconTextButtonTextSize, aItemTextPos, iItemTextColor, ppItems[iItem]);
            }
            if (bItemPressed)
            {
                *piValue = iItem;
                bChanged = true;
                ImGui::CloseCurrentPopup();
            }
            ImGui::PopID();
        }
        ImGui::EndPopup();
    }
    ImGui::PopStyleVar(3);
    ImGui::PopStyleColor(2);
    ImGui::SetCursorPos(ImVec2(aStartPos.x, aStartPos.y + fComboSpaceY + aSize.y + fComboSpaceY + fComboShiftY));
    ImGui::PopID();

    return bChanged;
}

bool ksd::DrawMultiComboIcon(const char* pId, bool* pbValues, const char* const* ppItems, int iItemCount, const ImVec2& aSize, const char* pIcon, const char* pPopupId, float fPopupY, PopupContentFunction pPopupContentFunction)
{
    constexpr float fIconWidth = 16.f;
    constexpr float fIconGap = 6.f;
    constexpr float fIconTextSize = MenuSettings::fDefaultTextSize;
    constexpr float fPopupRounding = 3.f;
    constexpr float fPopupAnchorOffsetY = -10.f;
    constexpr ImVec4 iconTextButtonColor = ImVec4(39.f / 255.f, 40.f / 255.f, 44.f / 255.f, 1.f);
    constexpr float fIconTextButtonTextSize = MenuSettings::fDefaultTextSize;
    constexpr float fComboTextStartX = 8.f;
    constexpr float fComboItemHeight = 22.f;
    constexpr ImVec4 comboTextColor = ImVec4(115.f / 255.f, 116.f / 255.f, 121.f / 255.f, 1.f);
    constexpr ImVec4 comboTextHoverColor = ImVec4(196.f / 255.f, 198.f / 255.f, 202.f / 255.f, 1.f);
    constexpr float fComboPopupTopPadding = 8.f;
    //kingsleydotDev
    if (!pId || !pbValues || !ppItems || iItemCount <= 0)
    {
        return false;
    }

    ImGui::PushID(pId);
    const ImVec2 aStartPos = ImGui::GetCursorPos();
    ImGui::SetCursorPos(aStartPos);
    const bool bIconPressed = ImGui::InvisibleButton("multicomboicontrigger", ImVec2(fIconWidth, aSize.y));
    const bool bIconHovered = ImGui::IsItemHovered();
    const ImVec2 aIconMin = ImGui::GetItemRectMin();
    const ImVec2 aIconMax = ImGui::GetItemRectMax();
    ImFont* pFont = ImGui::GetFont();
    ImFont* pIconFont = iconButtonFont ? iconButtonFont : pFont;
    if (pIcon && pIconFont)
    {
        const ImVec2 aIconSize = pIconFont->CalcTextSizeA(fIconTextSize, FLT_MAX, 0.f, pIcon);
        const ImVec2 aIconPos(
            aIconMin.x + ((fIconWidth - aIconSize.x) * 0.5f),
            aIconMin.y + ((aIconMax.y - aIconMin.y - aIconSize.y) * 0.5f)
        );
        ImGui::GetWindowDrawList()->AddText(pIconFont, fIconTextSize, aIconPos, ImGui::GetColorU32(ImVec4(1.f, 1.f, 1.f, 1.f)), pIcon);
    }

    static bool isIconPopupOpen = false;
    static bool isIconPopupJustOpened = false;
    static char iconPopupId[128] = {};
    static ImVec2 iconPopupAnchor = ImVec2(0.f, 0.f);
    //kingsleydotDev
    if (pPopupId && pPopupContentFunction && bIconPressed)
    {
        isIconPopupOpen = true;
        isIconPopupJustOpened = true;
        snprintf(iconPopupId, sizeof(iconPopupId), "%s", pPopupId);
        iconPopupAnchor = ImVec2(aIconMin.x + ((aIconMax.x - aIconMin.x) * 0.5f), aIconMin.y + fPopupY + fPopupAnchorOffsetY);
    }
    if (pPopupId && pPopupContentFunction && isIconPopupOpen && strcmp(iconPopupId, pPopupId) == 0)
    {
        if (ImGui::IsKeyPressed(ImGuiKey_Escape))
        {
            isIconPopupOpen = false;
        }

        ImGui::SetNextWindowPos(iconPopupAnchor, ImGuiCond_Always, ImVec2(0.5f, 0.f));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, fPopupRounding);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(18.f / 255.f, 20.f / 255.f, 24.f / 255.f, 1.f));
        const ImGuiWindowFlags iWindowFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize;
        bool bWindowHovered = false;
        if (ImGui::Begin(pPopupId, &isIconPopupOpen, iWindowFlags))
        {
            bWindowHovered = ImGui::IsWindowHovered(ImGuiHoveredFlags_RootAndChildWindows);
            pPopupContentFunction();
        }
        ImGui::End();
        if (isIconPopupOpen && !isIconPopupJustOpened && !bWindowHovered && !bIconHovered && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        {
            isIconPopupOpen = false;
        }
        isIconPopupJustOpened = false;
        ImGui::PopStyleColor();
        ImGui::PopStyleVar();
    }

    char szPreview[256] = {};
    int iPreviewLength = 0;
    bool bFirst = true;
    for (int iItem = 0; iItem < iItemCount; ++iItem)
    {
        if (!pbValues[iItem] || !ppItems[iItem])
        {
            continue;
        }
        if (!bFirst)
        {
            const int iWritten = snprintf(szPreview + iPreviewLength, sizeof(szPreview) - iPreviewLength, ", ");
            if (iWritten > 0)
            {
                iPreviewLength += iWritten;
                if (iPreviewLength >= (int)sizeof(szPreview))
                {
                    iPreviewLength = (int)sizeof(szPreview) - 1;
                }
            }
        }
        const int iWritten = snprintf(szPreview + iPreviewLength, sizeof(szPreview) - iPreviewLength, "%s", ppItems[iItem]);
        if (iWritten > 0)
        {
            iPreviewLength += iWritten;
            if (iPreviewLength >= (int)sizeof(szPreview))
            {
                iPreviewLength = (int)sizeof(szPreview) - 1;
            }
        }
        bFirst = false;
    }
    if (bFirst)
    {
        snprintf(szPreview, sizeof(szPreview), "None");
    }

    ImGui::SetCursorPos(ImVec2(aStartPos.x + fIconWidth + fIconGap, aStartPos.y));
    bool bChanged = false;
    ImGui::PushStyleColor(ImGuiCol_Button, iconTextButtonColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, iconTextButtonColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, iconTextButtonColor);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3.f);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.f, 0.f));
    const bool bPressed = ImGui::Button("##multicombo", aSize);
    ImGui::PopStyleVar(2);
    ImGui::PopStyleColor(3);
    if (bPressed)
    {
        ImGui::OpenPopup("multicomboitems");
    }

    const ImVec2 aComboMin = ImGui::GetItemRectMin();
    const ImVec2 aComboMax = ImGui::GetItemRectMax();
    const float fComboCenterY = aComboMin.y + ((aComboMax.y - aComboMin.y) * 0.5f);
    ImDrawList* pDrawList = ImGui::GetWindowDrawList();
    const ImU32 iPreviewColor = ImGui::GetColorU32(ImVec4(1.f, 1.f, 1.f, 1.f));
    const ImU32 iArrowColor = ImGui::GetColorU32(comboTextColor);
    const float fPreviewMaxWidth = (aComboMax.x - aComboMin.x) - fComboTextStartX - 18.f;
    while (pFont->CalcTextSizeA(fIconTextButtonTextSize, FLT_MAX, 0.f, szPreview).x > fPreviewMaxWidth && strlen(szPreview) > 0)
    {
        const size_t iLen = strlen(szPreview);
        szPreview[iLen - 1] = '\0';
    }
    const ImVec2 aPreviewSize = pFont->CalcTextSizeA(fIconTextButtonTextSize, FLT_MAX, 0.f, szPreview);
    pDrawList->AddText(pFont, fIconTextButtonTextSize, ImVec2(aComboMin.x + fComboTextStartX, fComboCenterY - (aPreviewSize.y * 0.5f)), iPreviewColor, szPreview);
    const bool bIsOpen = ImGui::IsPopupOpen("multicomboitems");
    if (bIsOpen)
    {
        pDrawList->AddTriangleFilled(ImVec2(aComboMax.x - 14.f, fComboCenterY + 2.f), ImVec2(aComboMax.x - 8.f, fComboCenterY + 2.f), ImVec2(aComboMax.x - 11.f, fComboCenterY - 2.f), iArrowColor);
    }
    else
    {
        pDrawList->AddTriangleFilled(ImVec2(aComboMax.x - 14.f, fComboCenterY - 2.f), ImVec2(aComboMax.x - 8.f, fComboCenterY - 2.f), ImVec2(aComboMax.x - 11.f, fComboCenterY + 2.f), iArrowColor);
    }

    ImGui::SetNextWindowPos(ImVec2(aComboMin.x, aComboMax.y - 4.f));
    ImGui::SetNextWindowSize(ImVec2(aSize.x, 0.f));
    ImGui::PushStyleColor(ImGuiCol_PopupBg, iconTextButtonColor);
    ImGui::PushStyleColor(ImGuiCol_Border, iconTextButtonColor);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 3.f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, fComboPopupTopPadding));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.f, 0.f));
    if (ImGui::BeginPopup("multicomboitems"))
    {
        ImDrawList* pPopupDrawList = ImGui::GetWindowDrawList();
        for (int iItem = 0; iItem < iItemCount; ++iItem)
        {
            ImGui::PushID(iItem);
            const ImVec2 aItemMin = ImGui::GetCursorScreenPos();
            const bool bItemPressed = ImGui::InvisibleButton("item", ImVec2(aSize.x, fComboItemHeight));
            const bool bItemHovered = ImGui::IsItemHovered();
            const bool bItemSelected = pbValues[iItem];
            const ImU32 iItemTextColor = bItemSelected
                ? ImGui::GetColorU32(ImVec4(1.f, 1.f, 1.f, 1.f))
                : (bItemHovered
                    ? ImGui::GetColorU32(comboTextHoverColor)
                    : ImGui::GetColorU32(comboTextColor));
            const ImVec2 aItemTextSize = pFont->CalcTextSizeA(fIconTextButtonTextSize, FLT_MAX, 0.f, ppItems[iItem]);
            pPopupDrawList->AddText(pFont, fIconTextButtonTextSize, ImVec2(aItemMin.x + fComboTextStartX, aItemMin.y + ((fComboItemHeight - aItemTextSize.y) * 0.5f)), iItemTextColor, ppItems[iItem]);
            if (bItemPressed)
            {
                pbValues[iItem] = !pbValues[iItem];
                bChanged = true;
            }
            ImGui::PopID();
        }
        ImGui::EndPopup();
    }
    ImGui::PopStyleVar(3);
    ImGui::PopStyleColor(2);
    ImGui::PopID();
    return bChanged;
}

bool ksd::DrawTextSelector(const char* pId, int* piValue, const char* const* ppItems, int iItemCount, float fWidth)
{
    constexpr float fTextSize = MenuSettings::fDefaultTextSize;
    constexpr ImVec4 textDimColor = ImVec4(115.f / 255.f, 116.f / 255.f, 121.f / 255.f, 1.f);
    constexpr float fTopSpace = 4.f;
    constexpr float fBottomSpace = 4.f;
    if (!piValue || !ppItems || iItemCount <= 0 || fWidth <= 0.f)
    {
        return false;
    }

    if (*piValue < 0)
    {
        *piValue = 0;
    }
    if (*piValue >= iItemCount)
    {
        *piValue = iItemCount - 1;
    }

    ImGui::PushID(pId);
    ImFont* pFont = ImGui::GetFont();
    ImDrawList* pDrawList = ImGui::GetWindowDrawList();
    const float fTextHeight = pFont ? pFont->CalcTextSizeA(fTextSize, FLT_MAX, 0.f, "A").y : ImGui::GetTextLineHeight();
    const float fSelectorHeight = fTopSpace + fTextHeight + fBottomSpace;
    const ImVec2 aSelectorMin = ImGui::GetCursorScreenPos();
    const bool bPressed = ImGui::InvisibleButton("selector", ImVec2(fWidth, fSelectorHeight));
    bool bChanged = false;

    if (bPressed)
    {
        const float fRelativeMouseX = ImGui::GetIO().MousePos.x - aSelectorMin.x;
        int iNewValue = 0;
        if (iItemCount <= 1)
        {
            iNewValue = 0;
        }
        else
        {
            const float fNormalized = fRelativeMouseX / fWidth;
            const float fScaled = fNormalized * (float)(iItemCount - 1);
            iNewValue = (int)(fScaled + 0.5f);
        }
        if (iNewValue < 0)
        {
            iNewValue = 0;
        }
        if (iNewValue >= iItemCount)
        {
            iNewValue = iItemCount - 1;
        }
        if (iNewValue != *piValue)
        {
            *piValue = iNewValue;
            bChanged = true;
        }
    }

    const ImU32 iWhite = ImGui::GetColorU32(ImVec4(1.f, 1.f, 1.f, 1.f));
    const ImU32 iDim = ImGui::GetColorU32(textDimColor);
    for (int iItem = 0; iItem < iItemCount; ++iItem)
    {
        const char* pText = ppItems[iItem];
        if (!pText || !pFont)
        {
            continue;
        }
        const ImVec2 aTextSize = pFont->CalcTextSizeA(fTextSize, FLT_MAX, 0.f, pText);
        float fTextX = aSelectorMin.x;
        if (iItemCount <= 1 || iItem == 0)
        {
            fTextX = aSelectorMin.x;
        }
        else if (iItem == iItemCount - 1)
        {
            fTextX = aSelectorMin.x + fWidth - aTextSize.x;
        }
        else
        {
            const float fAnchor = (float)iItem / (float)(iItemCount - 1);
            fTextX = aSelectorMin.x + (fWidth * fAnchor) - (aTextSize.x * 0.5f);
        }
        const float fTextY = aSelectorMin.y + fTopSpace + ((fTextHeight - aTextSize.y) * 0.5f);
        pDrawList->AddText(pFont, fTextSize, ImVec2(fTextX, fTextY), *piValue == iItem ? iWhite : iDim, pText);
    }
    ImGui::PopID();
    return bChanged;
}

bool ksd::DrawIntSlider(const char* pLabel, int* piValue, int iMin, int iMax, float fWidth)
{
    constexpr float fTextSize = MenuSettings::fDefaultTextSize;
    constexpr float fBarHeight = 4.f;
    constexpr float fBarOffsetY = 5.f;
    constexpr float fBarRounding = 3.f;
    constexpr float fHitExpandTop = 3.f;
    constexpr float fHitExpandBottom = 2.f;
    constexpr float fSliderBottomGap = 6.f;
    constexpr ImVec4 fillColor = ImVec4(105.f / 255.f, 112.f / 255.f, 122.f / 255.f, 1.f);
    constexpr ImVec4 emptyColor = ImVec4(29.f / 255.f, 30.f / 255.f, 34.f / 255.f, 1.f);

    if (!piValue || iMax <= iMin)
    {
        return false;
    }

    if (*piValue < iMin)
    {
        *piValue = iMin;
    }
    if (*piValue > iMax)
    {
        *piValue = iMax;
    }

    ImFont* pFont = ImGui::GetFont();
    ImDrawList* pDrawList = ImGui::GetWindowDrawList();
    const ImVec2 aStart = ImGui::GetCursorScreenPos();
    const ImVec2 aLabelSize = pFont->CalcTextSizeA(fTextSize, FLT_MAX, 0.f, pLabel);

    char szValue[32] = {};
    if (*piValue == 0)
    {
        snprintf(szValue, sizeof(szValue), "disabled");
    }
    else
    {
        snprintf(szValue, sizeof(szValue), "%d", *piValue);
    }
    const ImVec2 aValueSize = pFont->CalcTextSizeA(fTextSize, FLT_MAX, 0.f, szValue);

    const float fBarMinY = aStart.y + aLabelSize.y + fBarOffsetY;
    const ImVec2 aBarMin(aStart.x, fBarMinY);
    const ImVec2 aBarMax(aStart.x + fWidth, fBarMinY + fBarHeight);
    const float fHitMinY = fBarMinY - fHitExpandTop;
    const float fHitMaxY = (fBarMinY + fBarHeight) + fHitExpandBottom;
    const float fTotalHeight = fHitMaxY - aStart.y;

    ImGui::SetCursorScreenPos(ImVec2(aStart.x, fHitMinY));
    const bool bPressed = ImGui::InvisibleButton(pLabel, ImVec2(fWidth, fHitMaxY - fHitMinY));

    bool bChanged = false;
    if (ImGui::IsItemActive() && ImGui::IsMouseDown(ImGuiMouseButton_Left))
    {
        float fRatio = (ImGui::GetIO().MousePos.x - aBarMin.x) / fWidth;
        if (fRatio < 0.f)
        {
            fRatio = 0.f;
        }
        if (fRatio > 1.f)
        {
            fRatio = 1.f;
        }
        const int iNewValue = iMin + (int)((float)(iMax - iMin) * fRatio + 0.5f);
        if (iNewValue != *piValue)
        {
            *piValue = iNewValue;
            bChanged = true;
        }
    }
    else if (bPressed)
    {
        bChanged = true;
    }

    const ImU32 iWhite = ImGui::GetColorU32(ImVec4(1.f, 1.f, 1.f, 1.f));
    const ImU32 iFill = ImGui::GetColorU32(fillColor);
    const ImU32 iEmpty = ImGui::GetColorU32(emptyColor);

    pDrawList->AddText(pFont, fTextSize, aStart, iWhite, pLabel);
    pDrawList->AddText(pFont, fTextSize, ImVec2(aStart.x + fWidth - aValueSize.x, aStart.y), iWhite, szValue);
    pDrawList->AddRectFilled(aBarMin, aBarMax, iEmpty, fBarRounding);

    const float fFillRatio = (float)(*piValue - iMin) / (float)(iMax - iMin);
    const float fFillWidth = fWidth * fFillRatio;
    pDrawList->AddRectFilled(aBarMin, ImVec2(aBarMin.x + fFillWidth, aBarMax.y), iFill, fBarRounding);

    ImGui::SetCursorScreenPos(ImVec2(aStart.x, aStart.y + fTotalHeight + fSliderBottomGap));
    ImGui::Dummy(ImVec2(0.f, 5.f));
    return bChanged;
}

bool ksd::DrawFloatSlider(const char* pLabel, float* pfValue, float fMin, float fMax, float fWidth)
{
    constexpr float fTextSize = MenuSettings::fDefaultTextSize;
    constexpr float fBarHeight = 4.f;
    constexpr float fBarOffsetY = 5.f;
    constexpr float fBarRounding = 3.f;
    constexpr float fHitExpandTop = 3.f;
    constexpr float fHitExpandBottom = 2.f;
    constexpr float fSliderBottomGap = 6.f;
    constexpr ImVec4 fillColor = ImVec4(105.f / 255.f, 112.f / 255.f, 122.f / 255.f, 1.f);
    constexpr ImVec4 emptyColor = ImVec4(29.f / 255.f, 30.f / 255.f, 34.f / 255.f, 1.f);

    if (!pfValue || fMax <= fMin)
    {
        return false;
    }

    if (*pfValue < fMin)
    {
        *pfValue = fMin;
    }
    if (*pfValue > fMax)
    {
        *pfValue = fMax;
    }

    ImFont* pFont = ImGui::GetFont();
    ImDrawList* pDrawList = ImGui::GetWindowDrawList();
    const ImVec2 aStart = ImGui::GetCursorScreenPos();
    const ImVec2 aLabelSize = pFont->CalcTextSizeA(fTextSize, FLT_MAX, 0.f, pLabel);

    char szValue[32] = {};
    if (strcmp(pLabel, "Minimum hit chance") == 0)
    {
        snprintf(szValue, sizeof(szValue), "%.1f%%", *pfValue);
    }
    else if (strcmp(pLabel, "Radius") == 0)
    {
        snprintf(szValue, sizeof(szValue), "%.3f°", *pfValue);
    }
    else
    {
        snprintf(szValue, sizeof(szValue), "%.3f", *pfValue);
    }
    const ImVec2 aValueSize = pFont->CalcTextSizeA(fTextSize, FLT_MAX, 0.f, szValue);

    const float fBarMinY = aStart.y + aLabelSize.y + fBarOffsetY;
    const ImVec2 aBarMin(aStart.x, fBarMinY);
    const ImVec2 aBarMax(aStart.x + fWidth, fBarMinY + fBarHeight);
    const float fHitMinY = fBarMinY - fHitExpandTop;
    const float fHitMaxY = (fBarMinY + fBarHeight) + fHitExpandBottom;
    const float fTotalHeight = fHitMaxY - aStart.y;

    ImGui::SetCursorScreenPos(ImVec2(aStart.x, fHitMinY));
    const bool bPressed = ImGui::InvisibleButton(pLabel, ImVec2(fWidth, fHitMaxY - fHitMinY));

    bool bChanged = false;
    if (ImGui::IsItemActive() && ImGui::IsMouseDown(ImGuiMouseButton_Left))
    {
        float fRatio = (ImGui::GetIO().MousePos.x - aBarMin.x) / fWidth;
        if (fRatio < 0.f)
        {
            fRatio = 0.f;
        }
        if (fRatio > 1.f)
        {
            fRatio = 1.f;
        }
        const float fNewValue = fMin + ((fMax - fMin) * fRatio);
        if (fNewValue != *pfValue)
        {
            *pfValue = fNewValue;
            bChanged = true;
        }
    }
    else if (bPressed)
    {
        bChanged = true;
    }

    const ImU32 iWhite = ImGui::GetColorU32(ImVec4(1.f, 1.f, 1.f, 1.f));
    const ImU32 iFill = ImGui::GetColorU32(fillColor);
    const ImU32 iEmpty = ImGui::GetColorU32(emptyColor);

    pDrawList->AddText(pFont, fTextSize, aStart, iWhite, pLabel);
    pDrawList->AddText(pFont, fTextSize, ImVec2(aStart.x + fWidth - aValueSize.x, aStart.y), iWhite, szValue);
    pDrawList->AddRectFilled(aBarMin, aBarMax, iEmpty, fBarRounding);

    const float fFillRatio = (*pfValue - fMin) / (fMax - fMin);
    const float fFillWidth = fWidth * fFillRatio;
    pDrawList->AddRectFilled(aBarMin, ImVec2(aBarMin.x + fFillWidth, aBarMax.y), iFill, fBarRounding);

    ImGui::SetCursorScreenPos(ImVec2(aStart.x, aStart.y + fTotalHeight + fSliderBottomGap));
    ImGui::Dummy(ImVec2(0.f, 5.f));
    return bChanged;
}

bool ksd::DrawCheckboxIconPopup(const char* pLabel, bool* pValue, float fIconWidth, float fIconOffsetX, const char* pIcon, const char* pPopupId, float fPopupY, PopupContentFunction pPopupContentFunction)
{
    constexpr float fCheckboxRounding = 3.f;
    constexpr float fCheckboxTextUnchecked = 128.f / 255.f;
    constexpr float fIconTextButtonTextSize = MenuSettings::fDefaultTextSize;
    constexpr float fCheckboxPopupGapX = 8.f;
    constexpr float fPopupAnchorOffsetY = -10.f;
    constexpr float fPopupPaddingX = 28.f;
    constexpr float fPopupPaddingY = 16.f;
    if (!pValue || !pPopupId || !pPopupContentFunction)
    {
        return false;
    }

    bool bChanged = false;
    ImGui::PushID(pPopupId);
    const ImVec2 aStartPos = ImGui::GetCursorPos();

    const bool bCheckboxPressed = ksd::DrawCheckbox(pLabel, pValue);
    if (bCheckboxPressed)
    {
        bChanged = true;
    }

    const ImVec2 aCheckboxMin = ImGui::GetItemRectMin();
    const ImVec2 aCheckboxMax = ImGui::GetItemRectMax();
    const float fIconButtonHeight = 28.f;
    const float fIconButtonY = aStartPos.y + ((aCheckboxMax.y - aCheckboxMin.y - fIconButtonHeight) * 0.5f);
    ImGui::SetCursorPos(ImVec2(aStartPos.x + (aCheckboxMax.x - aCheckboxMin.x) + fCheckboxPopupGapX, fIconButtonY));

    const bool bIconPressed = ImGui::InvisibleButton("icontrigger", ImVec2(fIconWidth, fIconButtonHeight));
    const bool bIconHovered = ImGui::IsItemHovered();
    const ImVec2 aIconButtonMin = ImGui::GetItemRectMin();
    const ImVec2 aIconButtonMax = ImGui::GetItemRectMax();
    const float fIconCenterY = aIconButtonMin.y + ((aIconButtonMax.y - aIconButtonMin.y) * 0.5f);
    const float fIconCenterX = aIconButtonMin.x + ((aIconButtonMax.x - aIconButtonMin.x) * 0.5f);
    ImDrawList* pDrawList = ImGui::GetWindowDrawList();
    ImFont* pLabelFont = ImGui::GetFont();
    ImFont* pIconFont = iconButtonFont ? iconButtonFont : pLabelFont;
    if (pIcon && pIconFont)
    {
        const ImVec2 aIconSize = pIconFont->CalcTextSizeA(fIconTextButtonTextSize, FLT_MAX, 0.f, pIcon);
        const ImVec2 aIconPos(aIconButtonMin.x + ((fIconWidth - aIconSize.x) * 0.5f) + fIconOffsetX, fIconCenterY - (aIconSize.y * 0.5f));
        const ImU32 iIconColor = *pValue
            ? ImGui::GetColorU32(ImVec4(1.f, 1.f, 1.f, 1.f))
            : ImGui::GetColorU32(ImVec4(fCheckboxTextUnchecked, fCheckboxTextUnchecked, fCheckboxTextUnchecked, 1.f));
        pDrawList->AddText(pIconFont, fIconTextButtonTextSize, aIconPos, iIconColor, pIcon);
    }

    static bool isPopupOpen = false;
    static bool isPopupJustOpened = false;
    static char popupId[128] = {};
    static ImVec2 popupAnchor = ImVec2(0.f, 0.f);
    if (bIconPressed)
    {
        isPopupOpen = true;
        isPopupJustOpened = true;
        snprintf(popupId, sizeof(popupId), "%s", pPopupId);
        popupAnchor = ImVec2(fIconCenterX, fIconCenterY + fPopupY + fPopupAnchorOffsetY);
    }

    if (isPopupOpen && strcmp(popupId, pPopupId) == 0)
    {
        if (ImGui::IsKeyPressed(ImGuiKey_Escape))
        {
            isPopupOpen = false;
        }

        ImGui::SetNextWindowPos(popupAnchor, ImGuiCond_Always, ImVec2(0.5f, 0.f));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, fCheckboxRounding);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(fPopupPaddingX, fPopupPaddingY));
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(18.f / 255.f, 20.f / 255.f, 24.f / 255.f, 1.f));
        const ImGuiWindowFlags iWindowFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize;
        bool bWindowHovered = false;
        if (ImGui::Begin(pPopupId, &isPopupOpen, iWindowFlags))
        {
            bWindowHovered = ImGui::IsWindowHovered(ImGuiHoveredFlags_RootAndChildWindows);
            pPopupContentFunction();
        }
        ImGui::End();

        if (isPopupOpen && !isPopupJustOpened && !bWindowHovered && !bIconHovered && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        {
            isPopupOpen = false;
        }
        isPopupJustOpened = false;
        ImGui::PopStyleColor();
        ImGui::PopStyleVar(2);
    }

    ImGui::SetCursorPosY(aStartPos.y + 28.f);
    ImGui::PopID();
    return bChanged;
}
