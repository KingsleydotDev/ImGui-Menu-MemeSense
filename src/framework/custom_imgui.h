#pragma once

#include "imgui.h"

struct ImFont;
struct ImVec2;
struct ImVec4;

namespace ksd
{
typedef void (*PopupContentFunction)();
void ButtonSpacing();
void Spacing();
void SetIconButtonFont(ImFont* iconFont);
void DrawBrandingText(ImFont* titleFont);
void DrawInlineLabel(const char* label, float x, float y);
void DrawSectionTitle(const char* label, float columnWidth, float sectionTitleY, float sectionTitleSize, ImU32 sectionTitleColor);
bool DrawSidebarButton(const char* label, const char* icon, bool isActive, ImFont* sidebarFont, ImFont* iconFont);
bool DrawCheckbox(const char* label, bool* value, float maxWidth = 0.f);
bool DrawCheckboxIcon(const char* label, bool* value, float maxWidth, const char* icon);
bool DrawColorPickerCheckbox(const char* id, bool* value, ImVec4* color);
bool DrawIconTextButton(const char* icon, const char* label, const ImVec2& size);
bool Button(const char* label, const ImVec2& size);
bool DrawCustomCombo(const char* id, int* value, const char* const* items, int itemCount, const ImVec2& size);
bool DrawMultiComboIcon(const char* id, bool* values, const char* const* items, int itemCount, const ImVec2& size, const char* icon, const char* popupId, float popupY, PopupContentFunction popupContentFunction);
bool DrawTextSelector(const char* id, int* value, const char* const* items, int itemCount, float width);
bool DrawIntSlider(const char* label, int* value, int minValue, int maxValue, float width);
bool DrawFloatSlider(const char* label, float* value, float minValue, float maxValue, float width);
bool DrawCheckboxIconPopup(const char* label, bool* value, float iconWidth, float iconOffsetX, const char* icon, const char* popupId, float popupY, PopupContentFunction popupContentFunction);
}
