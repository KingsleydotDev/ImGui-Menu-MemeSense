#include "flowstrip.h"
#include "imgui.h"
#include <cmath>

namespace
{
ImVec4 BlendColor(const ImVec4& aColorA, const ImVec4& aColorB, float fBlend)
{
    return ImVec4(
        aColorA.x + (aColorB.x - aColorA.x) * fBlend,
        aColorA.y + (aColorB.y - aColorA.y) * fBlend,
        aColorA.z + (aColorB.z - aColorA.z) * fBlend,
        1.f
    );
}

float SmoothBlend(float fValue)
{
    //kingsleydotDev
    return fValue * fValue * (3.f - (2.f * fValue));
}

ImVec4 GetFlowColor(float fPoint, float fTime)
{
    const ImVec4 aColorRed = ImVec4(1.00f, 0.06f, 0.16f, 1.f);
    const ImVec4 aColorGreen = ImVec4(0.06f, 0.90f, 0.22f, 1.f);
    const ImVec4 aColorBlue = ImVec4(0.08f, 0.40f, 1.00f, 1.f);

    const float fMoveTime = fTime * 0.85f;
    const float fBlendTime = fTime * 0.02f;
    const float fStretchedPoint = fPoint * 0.12f;
    const float fSmoothPoint = fStretchedPoint + (0.015f * std::sinf((fStretchedPoint * 6.2831853f * 0.45f) + (fBlendTime * 0.15f)));
    const float fPhase = std::fmod(fMoveTime + fSmoothPoint, 1.f);

    if (fPhase < 0.33f)
    {
        return BlendColor(aColorRed, aColorGreen, SmoothBlend(fPhase / 0.33f));
    }
    if (fPhase < 0.66f)
    {
        return BlendColor(aColorGreen, aColorBlue, SmoothBlend((fPhase - 0.33f) / 0.33f));
    }
    return BlendColor(aColorBlue, aColorRed, SmoothBlend((fPhase - 0.66f) / 0.34f));
}
}

namespace ksd
{
void DrawFlowStrip()
{
    ImDrawList* pDrawList = ImGui::GetForegroundDrawList();
    const ImVec2 aWindowPos = ImGui::GetWindowPos();
    const ImVec2 aWindowSize = ImGui::GetWindowSize();
    const float fStripHeight = 3.f;
    const float fTime = (float)ImGui::GetTime();
    const int iSegmentCount = 320;
    //kingsleydotDev

    for (int iSegment = 0; iSegment < iSegmentCount; ++iSegment)
    {
        const float fStart = (float)iSegment / (float)iSegmentCount;
        const float fEnd = (float)(iSegment + 1) / (float)iSegmentCount;
        const float fX0 = aWindowPos.x + (aWindowSize.x * fStart);
        const float fX1 = aWindowPos.x + (aWindowSize.x * fEnd);
        const ImVec4 aColorLeft = GetFlowColor(fStart, fTime);
        const ImVec4 aColorRight = GetFlowColor(fEnd, fTime);

        pDrawList->AddRectFilledMultiColor(
            ImVec2(fX0, aWindowPos.y),
            ImVec2(fX1, aWindowPos.y + fStripHeight),
            ImGui::ColorConvertFloat4ToU32(aColorLeft),
            ImGui::ColorConvertFloat4ToU32(aColorRight),
            ImGui::ColorConvertFloat4ToU32(aColorRight),
            ImGui::ColorConvertFloat4ToU32(aColorLeft)
        );
    }
}
}
