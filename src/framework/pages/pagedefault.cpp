#include "pagedefault.h"
#include "../custom_imgui.h"
#include "../custom_settings.h"
#include "../var.h"
#include "imgui.h"

void ksd::RenderDefaultPageHead(const char* pLabel, float fContentStartX, float fHeadTextY)
{
    ImGui::SetCursorPos(ImVec2(fContentStartX, fHeadTextY));
    ImGui::Text("%s", pLabel);
}

void ksd::RenderDefaultPageBody(float fContentStartX)
{
    const float fFirstControlY = MenuSettings::fPageHeadControlY + 3.f;
    const float fSecondControlY = fFirstControlY + 38.f;
    ImGui::SetCursorPos(ImVec2(fContentStartX, fFirstControlY));
    ksd::DrawCheckbox("feature b", &MenuVars::isFeatureBEnabled);
    ImGui::SetCursorPos(ImVec2(fContentStartX, fSecondControlY));
    ksd::DrawFloatSlider("master value", &MenuVars::masterValue, 0.f, 1.f, 240.f);
}
