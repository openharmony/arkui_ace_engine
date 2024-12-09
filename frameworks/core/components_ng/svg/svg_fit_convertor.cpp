/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "core/components_ng/svg/svg_fit_convertor.h"
#include "core/common/ace_application_info.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float HALF = 0.5f;
constexpr double SCALE_BASE = 1.0;
constexpr int32_t DEFAULT_FIT_INDEX = static_cast<int32_t>(ImageFit::COVER);
}
const std::vector<void (*)(RSCanvas& canvas,
    const Size& layoutSize, const Size& svgSize)> SvgFitConvertor::FIT_OPERATIONS = {
    ApplyFill,
    ApplyContain,
    ApplyCover,
    ApplyWidth,
    ApplyHeight,
    ApplyNone,
    ApplyScaleDown,
    ApplyAlignmentTopLeft,
    ApplyAlignmentTop,
    ApplyAlignmentTopRight,
    ApplyAlignmentCenterLeft,
    ApplyAlignmentCenter,
    ApplyAlignmentCenterRight,
    ApplyAlignmentBottomLeft,
    ApplyAlignmentBottom,
    ApplyAlignmentBottomRight
};
void SvgFitConvertor::ApplyFit(ImageFit imageFit, RSCanvas& canvas, const Size& layoutSize, const Size& svgSize)
{
    if (NearZero(svgSize.Width()) || NearZero(svgSize.Height())) {
        DrawNothing(canvas);
        return;
    }
    auto fitIndex = static_cast<int32_t>(imageFit);
    fitIndex = (fitIndex < static_cast<int32_t>(FIT_OPERATIONS.size()) && fitIndex >= 0) ?
        fitIndex : DEFAULT_FIT_INDEX;
    FIT_OPERATIONS[fitIndex](canvas, layoutSize, svgSize);
}

void SvgFitConvertor::ApplyFill(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize)
{
    canvas.Scale(layoutSize.Width() / svgSize.Width(), layoutSize.Height() / svgSize.Height());
}

void SvgFitConvertor::ApplyContain(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize)
{
    AdjustContentFit(canvas, layoutSize, svgSize,
        std::min(layoutSize.Width() / svgSize.Width(), layoutSize.Height() / svgSize.Height()), Alignment::CENTER);
}

void SvgFitConvertor::ApplyCover(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize)
{
    AdjustContentFit(canvas, layoutSize, svgSize,
        std::max(layoutSize.Width() / svgSize.Width(), layoutSize.Height() / svgSize.Height()), Alignment::CENTER);
}

void SvgFitConvertor::ApplyWidth(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize)
{
    AdjustContentFit(canvas, layoutSize, svgSize, layoutSize.Width() / svgSize.Width(), Alignment::CENTER);
}

void SvgFitConvertor::ApplyHeight(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize)
{
    AdjustContentFit(canvas, layoutSize, svgSize, layoutSize.Height() / svgSize.Height(), Alignment::CENTER);
}

void SvgFitConvertor::ApplyNone(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize)
{
    AdjustContentFit(canvas, layoutSize, svgSize, SCALE_BASE, Alignment::CENTER);
}

void SvgFitConvertor::ApplyScaleDown(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize)
{
    auto scale = std::min(layoutSize.Width() / svgSize.Width(), layoutSize.Height() / svgSize.Height());
    AdjustContentFit(canvas, layoutSize, svgSize, std::min(scale, SCALE_BASE), Alignment::CENTER);
}

void SvgFitConvertor::ApplyAlignmentTopLeft(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize)
{
    AdjustContentFit(canvas, layoutSize, svgSize, SCALE_BASE,
        AceApplicationInfo::GetInstance().IsRightToLeft() ? Alignment::TOP_RIGHT : Alignment::TOP_LEFT);
}

void SvgFitConvertor::ApplyAlignmentTop(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize)
{
    AdjustContentFit(canvas, layoutSize, svgSize, SCALE_BASE, Alignment::TOP_CENTER);
}

void SvgFitConvertor::ApplyAlignmentTopRight(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize)
{
    AdjustContentFit(canvas, layoutSize, svgSize, SCALE_BASE,
        AceApplicationInfo::GetInstance().IsRightToLeft() ? Alignment::TOP_LEFT : Alignment::TOP_RIGHT);
}

void SvgFitConvertor::ApplyAlignmentCenterLeft(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize)
{
    AdjustContentFit(canvas, layoutSize, svgSize, SCALE_BASE,
        AceApplicationInfo::GetInstance().IsRightToLeft() ? Alignment::CENTER_RIGHT : Alignment::CENTER_LEFT);
}

void SvgFitConvertor::ApplyAlignmentCenter(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize)
{
    AdjustContentFit(canvas, layoutSize, svgSize, SCALE_BASE, Alignment::CENTER);
}

void SvgFitConvertor::ApplyAlignmentCenterRight(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize)
{
    AdjustContentFit(canvas, layoutSize, svgSize, SCALE_BASE,
        AceApplicationInfo::GetInstance().IsRightToLeft() ? Alignment::CENTER_LEFT : Alignment::CENTER_RIGHT);
}

void SvgFitConvertor::ApplyAlignmentBottomLeft(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize)
{
    AdjustContentFit(canvas, layoutSize, svgSize, SCALE_BASE,
        AceApplicationInfo::GetInstance().IsRightToLeft() ? Alignment::BOTTOM_RIGHT : Alignment::BOTTOM_LEFT);
}

void SvgFitConvertor::ApplyAlignmentBottom(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize)
{
    AdjustContentFit(canvas, layoutSize, svgSize, SCALE_BASE, Alignment::BOTTOM_CENTER);
}

void SvgFitConvertor::ApplyAlignmentBottomRight(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize)
{
    AdjustContentFit(canvas, layoutSize, svgSize, SCALE_BASE,
        AceApplicationInfo::GetInstance().IsRightToLeft() ? Alignment::BOTTOM_LEFT : Alignment::BOTTOM_RIGHT);
}

void SvgFitConvertor::AdjustContentFit(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize,
    float svgScale, Alignment alignMent)
{
    auto translateX = (1.0 + alignMent.GetHorizontal()) * (layoutSize.Width() - svgSize.Width() * svgScale) * HALF;
    auto translateY = (1.0 + alignMent.GetVertical()) * (layoutSize.Height() - svgSize.Height() * svgScale) * HALF;
    canvas.Translate(translateX, translateY);
    canvas.Scale(svgScale, svgScale);
}

void SvgFitConvertor::DrawNothing(RSCanvas& canvas)
{
    RSRect clipRect(0.0f, 0.0f, 0.0f, 0.0f);
    canvas.ClipRect(clipRect, RSClipOp::INTERSECT);
}
}