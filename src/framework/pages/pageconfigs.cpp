#include "pageconfigs.h"
#include "../custom_imgui.h"
#include "../custom_settings.h"
#include "../var.h"
#include "imgui.h"
#include "../../../ext/fonts/iconsfontawesome/IconsFontAwesome7.h"
#include <cfloat>

namespace
{
struct ConfigsPageState
{
    int activeConfig = 0;
    bool isAutoSaveEnabled = true;
    bool isCloudSyncEnabled = false;
    bool isLoadOnStartEnabled = true;
};

ConfigsPageState gConfigsPageState;
}

void ksd::RenderConfigsPageHead(float fContentStartX, float fHeadCheckboxY)
{
    ConfigsPageState& aState = gConfigsPageState;
    static const char* const ppConfigs[] = { "Legit main", "HvH beta", "Stream safe", "Blank", "Backup 1" };
    const int iConfigCount = (int)(sizeof(ppConfigs) / sizeof(ppConfigs[0]));
    const float fComboWidth = 160.f;
    const float fComboHeight = MenuSettings::fPageInlineRowHeight;
    const float fComboX = fContentStartX + 8.f;

    ImGui::SetCursorPos(ImVec2(fComboX, fHeadCheckboxY));
    ksd::DrawCustomCombo("configsactive", &aState.activeConfig, ppConfigs, iConfigCount, ImVec2(fComboWidth, fComboHeight));
    ImGui::SetCursorPos(ImVec2(fComboX + fComboWidth + 10.f, fHeadCheckboxY));
    ksd::DrawIconTextButton(ICON_FA_FOLDER_OPEN, "Load", ImVec2(72.f, 28.f));
    ImGui::SetCursorPos(ImVec2(fComboX + fComboWidth + 92.f, fHeadCheckboxY));
    ksd::DrawIconTextButton(ICON_FA_FLOPPY_DISK, "Save", ImVec2(72.f, 28.f));
    ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x - 28.f - 80.f, fHeadCheckboxY));
    ksd::DrawIconTextButton(ICON_FA_FILE_EXPORT, "Export", ImVec2(80.f, 28.f));
}

void ksd::RenderConfigsPageBody(float fContentStartX)
{
    ConfigsPageState& aState = gConfigsPageState;
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
    ImGui::BeginChild("configsleft", ImVec2(fColumnWidth, 0.f), false, ImGuiWindowFlags_NoScrollbar);
    ksd::DrawSectionTitle("Profiles", fColumnWidth, fSectionTitleY, fSectionTitleSize, iSectionTitleColor);
    ImGui::SetCursorPosX(fColumnContentX);
    ImGui::SetCursorPosY(38.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::Button("Duplicate active", ImVec2(240.f, 28.f));
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::Button("Rename", ImVec2(240.f, 28.f));
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawIconTextButton(ICON_FA_TRASH, "Delete", ImVec2(240.f, 28.f));
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawIconTextButton(ICON_FA_FILE_IMPORT, "Import from clipboard", ImVec2(240.f, 28.f));
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Auto save on close", &aState.isAutoSaveEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Load default on start", &aState.isLoadOnStartEnabled, 240.f);
    ImGui::EndChild();

    ImGui::SetCursorPos(ImVec2(fRightColumnX, 0.f));
    ImGui::BeginChild("configsright", ImVec2(fColumnWidth, 0.f), false, ImGuiWindowFlags_NoScrollbar);
    ksd::DrawSectionTitle("Sharing", fColumnWidth, fSectionTitleY, fSectionTitleSize, iSectionTitleColor);
    ImGui::SetCursorPosX(fColumnContentX);
    ImGui::SetCursorPosY(38.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::DrawCheckbox("Cloud sync placeholder", &aState.isCloudSyncEnabled, 240.f);
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::Button("Open configs folder", ImVec2(240.f, 28.f));
    ImGui::SetCursorPosX(fColumnContentX);
    ksd::Button("Reset menu layout", ImVec2(240.f, 28.f));
    ImGui::EndChild();
}
