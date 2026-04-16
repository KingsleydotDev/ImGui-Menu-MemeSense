#include "pageview.h"
#include "../custom_imgui.h"
#include "../custom_settings.h"
#include "../var.h"
#include "imgui.h"
#include "../../../ext/fonts/iconsfontawesome/IconsFontAwesome7.h"
#include <cfloat>

namespace
{
static const char* const ppZoomModes[] = { "Hold", "Toggle" };

struct ViewPageState
{
    int aspectPreset = 0;
    bool isMasterEnabled = false;
    bool isOverrideFovEnabled = true;
    bool isViewmodelFovEnabled = true;
    bool isAspectOverrideEnabled = false;
    bool isZoomEnabled = false;
    bool isThirdPersonEnabled = false;
    int fovValue = 90;
    int viewmodelFov = 68;
    float aspectRatio = 1.333f;
    float zoomAmount = 30.f;
    int thirdPersonDistance = 120;
    int zoomMode = 0;
};

ViewPageState gViewPageState;
}

void ksd::RenderViewPageHead(float fContentStartX, float fHeadCheckboxY)
{
    ViewPageState& aState = gViewPageState;
    static const char* const ppAspect[] = { "Native", "4:3", "16:10", "16:9 stretched" };
    const int iAspectCount = (int)(sizeof(ppAspect) / sizeof(ppAspect[0]));
    const float fTopComboWidth = 124.f;
    const float fTopComboHeight = MenuSettings::fPageInlineRowHeight;
    const float fTopComboX = fContentStartX + 140.f;

    ImGui::SetCursorPos(ImVec2(fContentStartX, fHeadCheckboxY));
    ksd::DrawCheckbox("Master switch", &aState.isMasterEnabled);
    ImGui::SetCursorPos(ImVec2(fTopComboX, fHeadCheckboxY));
    ksd::DrawCustomCombo("viewaspectpreset", &aState.aspectPreset, ppAspect, iAspectCount, ImVec2(fTopComboWidth, fTopComboHeight));
    ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x - 28.f - 80.f, fHeadCheckboxY));
    ksd::DrawIconTextButton(ICON_FA_CLOUD_ARROW_UP, "Save", ImVec2(80.f, 28.f));
}

void ksd::RenderViewPageBody(float fContentStartX)
{
    ViewPageState& aState = gViewPageState;
    (void)fContentStartX;
    const int iZoomModeCount = (int)(sizeof(ppZoomModes) / sizeof(ppZoomModes[0]));

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
    ImGui::BeginChild("viewleft", ImVec2(fColumnWidth, 0.f), false, ImGuiWindowFlags_NoScrollbar);
    ksd::DrawSectionTitle("Camera", fColumnWidth, fSectionTitleY, fSectionTitleSize, iSectionTitleColor);
    ImGui::SetCursorPosX(fColumnContentX);
    ImGui::SetCursorPosY(38.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Override FOV", &aState.isOverrideFovEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawIntSlider("Field of view", &aState.fovValue, 60, 120, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Viewmodel FOV", &aState.isViewmodelFovEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawIntSlider("Viewmodel value", &aState.viewmodelFov, 54, 90, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Aspect override", &aState.isAspectOverrideEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawFloatSlider("Aspect ratio", &aState.aspectRatio, 1.f, 2.5f, 240.f);
    ImGui::EndChild();

    ImGui::SetCursorPos(ImVec2(fRightColumnX, 0.f));
    ImGui::BeginChild("viewright", ImVec2(fColumnWidth, 0.f), false, ImGuiWindowFlags_NoScrollbar);
    ksd::DrawSectionTitle("Zoom", fColumnWidth, fSectionTitleY, fSectionTitleSize, iSectionTitleColor);
    ImGui::SetCursorPosX(fColumnContentX);
    ImGui::SetCursorPosY(38.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Zoom key", &aState.isZoomEnabled, 240.f);
    {
        const float fRowY = ImGui::GetCursorPosY();
        ksd::DrawInlineLabel("Zoom mode", fColumnContentX, fRowY + fInlineLabelOffsetY);
        ImGui::SetCursorPos(ImVec2(fInlineComboX, fRowY));
        ksd::DrawCustomCombo("viewzoommode", &aState.zoomMode, ppZoomModes, iZoomModeCount, ImVec2(fInlineComboWidth, fInlineRowHeight));
        ImGui::SetCursorPosY(fRowY + fInlineRowHeight);
    }
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawFloatSlider("Zoom amount", &aState.zoomAmount, 10.f, 60.f, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Third person", &aState.isThirdPersonEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawIntSlider("Third person distance", &aState.thirdPersonDistance, 40, 200, 240.f);
    ImGui::EndChild();
}
