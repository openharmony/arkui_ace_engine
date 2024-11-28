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

#include "core/components_ng/pattern/scrollable/scrollable_paint_method.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/pattern/scrollable/scrollable_paint_property.h"

namespace OHOS::Ace::NG {

constexpr double PERCENT_100 = 100.0;
constexpr float LINEAR_GRADIENT_ANGLE = 90.0f;
constexpr float LINEAR_GRADIENT_DIRECTION_ANGLE = 270.0f;
namespace {
GradientColor CreatePercentGradientColor(float percent, Color color)
{
    NG::GradientColor gredient = GradientColor(color);
    gredient.SetDimension(CalcDimension(percent * PERCENT_100, DimensionUnit::PERCENT));
    return gredient;
}
} // namespace

void ScrollablePaintMethod::UpdateFadingGradient(const RefPtr<RenderContext>& renderContext)
{
    if (!hasFadingEdge_) {
        return;
    }
    CHECK_NULL_VOID(renderContext);
    CHECK_NULL_VOID(overlayRenderContext_);
    NG::Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::LINEAR);
    if (isVerticalReverse_) {
        bool tempFadingValue = isFadingTop_;
        isFadingTop_ = isFadingBottom_;
        isFadingBottom_ = tempFadingValue;
    }
    if (isFadingTop_) {
        gradient.AddColor(CreatePercentGradientColor(startPercent_, Color::TRANSPARENT));
        gradient.AddColor(CreatePercentGradientColor(startPercent_ + percentFading_, Color::WHITE));
    }
    if (isFadingBottom_) {
        gradient.AddColor(CreatePercentGradientColor(endPercent_ - percentFading_, Color::WHITE));
        gradient.AddColor(CreatePercentGradientColor(endPercent_, Color::TRANSPARENT));
    }
    if (vertical_) {
        gradient.GetLinearGradient()->angle = isReverse_
                                                  ? CalcDimension(LINEAR_GRADIENT_DIRECTION_ANGLE, DimensionUnit::PX)
                                                  : CalcDimension(LINEAR_GRADIENT_ANGLE, DimensionUnit::PX);
    }
    renderContext->UpdateBackBlendApplyType(BlendApplyType::OFFSCREEN);

    overlayRenderContext_->UpdateZIndex(INT32_MAX);
    overlayRenderContext_->UpdateLinearGradient(gradient);
    if (!isFadingTop_ && !isFadingBottom_) {
        overlayRenderContext_->UpdateBackBlendMode(BlendMode::SRC_OVER);
        renderContext->UpdateBackBlendMode(BlendMode::NONE);
    } else {
        overlayRenderContext_->UpdateBackBlendMode(BlendMode::DST_IN);
        renderContext->UpdateBackBlendMode(BlendMode::SRC_OVER);
    }
    overlayRenderContext_->UpdateBackBlendApplyType(BlendApplyType::OFFSCREEN);
}

bool ScrollablePaintMethod::TryContentClip(PaintWrapper* wrapper)
{
    CHECK_NULL_RETURN(wrapper, false);
    auto props = DynamicCast<ScrollablePaintProperty>(wrapper->GetPaintProperty());
    CHECK_NULL_RETURN(props, false);
    auto&& clip = props->GetContentClip();
    if (clip.has_value()) {
        auto renderContext = wrapper->GetRenderContext();
        renderContext->SetClipToFrame(false);
        renderContext->SetClipToBounds(false);

        auto mode = clip->first;
        if (mode == ContentClipMode::DEFAULT) {
            mode = props->GetDefaultContentClip();
        }
        auto&& geo = wrapper->GetGeometryNode();
        switch (mode) {
            case ContentClipMode::CUSTOM:
                renderContext->SetContentClip(clip->second);
                break;
            case ContentClipMode::CONTENT_ONLY: {
                auto rect = geo->GetPaddingRect();
                rect.SetOffset(rect.GetOffset() - geo->GetFrameOffset());
                renderContext->SetContentClip(rect);
                break;
            }
            case ContentClipMode::SAFE_AREA: {
                auto host = renderContext->GetHost();
                CHECK_NULL_RETURN(host, false);
                const auto safeAreaPad = host->GetAccumulatedSafeAreaExpand(true);

                auto size = geo->GetPaddingSize();
                AddPaddingToSize(safeAreaPad, size);

                auto offset = geo->GetPaddingOffset() - geo->GetFrameOffset();
                offset -= OffsetF(safeAreaPad.left.value_or(0.0f), safeAreaPad.top.value_or(0.0f));
                renderContext->SetContentClip(RectF { offset, size });
                break;
            }
            case ContentClipMode::BOUNDARY: {
                auto rect = geo->GetFrameRect();
                rect.SetOffset({ 0.0f, 0.0f });
                renderContext->SetContentClip(rect);
                break;
            }
            default:
                break;
        }
        return true;
    }
    return false;
}
} // namespace OHOS::Ace::NG
