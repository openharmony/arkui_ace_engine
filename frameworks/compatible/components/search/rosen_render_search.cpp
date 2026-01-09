/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "compatible/components/search/rosen_render_search.h"

#include "core/components_ng/render/drawing.h"


namespace OHOS::Ace {
namespace {

constexpr Dimension ICON_HEIGHT = 16.0_vp;
constexpr Dimension SEARCH_SPACING = 2.0_vp;
constexpr double SEARCH_DIVIDER_WIDTH = 1.0;
constexpr Dimension OFFSET_FOR_FOCUS = 4.0_vp;
const Color SEARCH_DIVIDER_COLOR = Color(0x33000000);

} // namespace

void RosenRenderSearch::Paint(RenderContext& context, const Offset& offset)
{
    RenderNode::Paint(context, offset);

    // Paint close icon.
    if (showCloseIcon_ && renderCloseIcon_) {
        renderCloseIcon_->Paint(context, offset + closeIconRect_.GetOffset());
    }

    // Paint divider.
    if (renderSearchBox_) {
        RSCanvas* canvas = GetDrawingCanvas(context);
        RSPen pen;
        if (canvas != nullptr) {
            double dividerVerticalOffset = (GetLayoutSize().Height() - NormalizeToPx(ICON_HEIGHT)) / 2.0;
            Offset dividerOffset = Offset(searchTextRect_.GetOffset().GetX(), dividerVerticalOffset);
            if (needReverse_) {
                dividerOffset = searchTextRect_.GetOffset() +
                                Offset(searchTextRect_.Width() - SEARCH_DIVIDER_WIDTH, dividerVerticalOffset);
            }
            dividerOffset += offset;
            Rect rect(dividerOffset, Size(SEARCH_DIVIDER_WIDTH, NormalizeToPx(ICON_HEIGHT)));
            canvas->Save();
            pen.SetColor(SEARCH_DIVIDER_COLOR.GetValue());
            canvas->AttachPen(pen);
            canvas->DrawRect(RSRect(rect.Left(), rect.Top(), rect.Width() + rect.Left(), rect.Height() + rect.Top()));
            canvas->DetachPen();
            canvas->Restore();
        }

        // Paint search text.
        searchBoxOffset_ =
            searchTextRect_.GetOffset() + Offset(NormalizeToPx(SEARCH_SPACING) + SEARCH_DIVIDER_WIDTH, 0.0);
        if (needReverse_) {
            searchBoxOffset_ = searchTextRect_.GetOffset() + Offset(NormalizeToPx(SEARCH_SPACING), 0.0);
        }
        auto buttonText = renderSearchBox_->GetFirstChild();
        if (buttonText) {
            auto textSize = buttonText->GetLayoutSize();
            double yOffset = (searchTextRect_.Height() - textSize.Height()) / 2;
            double xOffset = (searchTextRect_.Width() - textSize.Width()) / 2;
            buttonText->Paint(context, offset + searchBoxOffset_ + Offset(xOffset, yOffset));
        }
    }

    PaintFocus();
    PaintOverlayForHoverAndPress(context, offset);
}

void RosenRenderSearch::PaintFocus()
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }

    Size size;
    Offset offset;
    if (focusRender_ == SearchNodeType::NONE) {
        return;
    }
    if (focusRender_ == SearchNodeType::IMAGE) {
        if (renderCloseIcon_) {
            size = closeIconHotZoneRect_.GetSize();
            offset = closeIconHotZoneRect_.GetOffset();
        }
    } else if (focusRender_ == SearchNodeType::BUTTON) {
        if (renderSearchBox_) {
            size = renderSearchBox_->GetLayoutSize();
            offset = searchBoxOffset_;
        }
    }

    if (SystemProperties::GetDeviceType() == DeviceType::PHONE) {
        double offsetForFocus = NormalizeToPx(OFFSET_FOR_FOCUS);
        size -= Size(offsetForFocus * 2.0, offsetForFocus * 2.0);
        offset += Offset(offsetForFocus, offsetForFocus);
    }
    RRect rrect = RRect::MakeRect(Rect(offset, size));
    Radius radius = Radius(size.Height() / 2.0);
    rrect.SetCorner({ radius, radius, radius, radius });
    context->ShowFocusAnimation(rrect, Color::BLUE, GetGlobalOffset() + offset);
}

void RosenRenderSearch::PaintOverlayForHoverAndPress(RenderContext& context, const Offset& offset)
{
    if (overlayColor_ == Color::TRANSPARENT) {
        return;
    }

    RSCanvas* canvas = GetDrawingCanvas(context);
    if (canvas == nullptr) {
        LOGE("canvas is null!");
        return;
    }
    canvas->Save();
    RSPen pen;
    // Background overlay 10% opacity black when hover.
    pen.SetColor(overlayColor_.GetValue());

    Offset rectOffset;
    Size rectSize;
    double searchSpacing = NormalizeToPx(SEARCH_SPACING);
    if (showCloseIcon_ && hoverOrPressRender_ == SearchNodeType::IMAGE) {
        rectOffset = closeIconHotZoneRect_.GetOffset();
        rectSize = closeIconHotZoneRect_.GetSize();
    } else if (hoverOrPressRender_ == SearchNodeType::BUTTON) {
        rectOffset = searchTextRect_.GetOffset() + Offset(SEARCH_DIVIDER_WIDTH, 0.0) + Offset(searchSpacing, 0.0);
        rectSize = searchTextRect_.GetSize() - Size(SEARCH_DIVIDER_WIDTH, 0.0) - Size(searchSpacing * 2.0, 0.0);
    }

    Border border;
    border.SetBorderRadius(Radius(rectSize.Height() / 2.0));
    canvas->AttachPen(pen);
    canvas->DrawRoundRect(MakeRRect(rectOffset + offset, rectSize, border));
    canvas->DetachPen();
    canvas->Restore();
}

RSRoundRect RosenRenderSearch::MakeRRect(const Offset& offset, const Size& size, const Border& border)
{
    RSRect rect(
        offset.GetX(), offset.GetY(), offset.GetX() + size.Width(), offset.GetY() + size.Height());

    std::vector<RSPoint> rectRadii(4);
    rectRadii.at(RSRoundRect::CornerPos::TOP_LEFT_POS) = RSPoint(
        NormalizeToPx(border.TopLeftRadius().GetX()), NormalizeToPx(border.TopLeftRadius().GetY()));
    rectRadii.at(RSRoundRect::CornerPos::TOP_RIGHT_POS) = RSPoint(
        NormalizeToPx(border.TopRightRadius().GetX()), NormalizeToPx(border.TopRightRadius().GetY()));
    rectRadii.at(RSRoundRect::CornerPos::BOTTOM_RIGHT_POS) = RSPoint(
        NormalizeToPx(border.BottomRightRadius().GetX()), NormalizeToPx(border.BottomRightRadius().GetY()));
    rectRadii.at(RSRoundRect::CornerPos::BOTTOM_LEFT_POS) = RSPoint(
        NormalizeToPx(border.BottomLeftRadius().GetX()), NormalizeToPx(border.BottomLeftRadius().GetY()));

    RSRoundRect rrect(rect, rectRadii);
    return rrect;
}

RSCanvas* RosenRenderSearch::GetDrawingCanvas(RenderContext& context)
{
    auto renderContext = AceType::DynamicCast<RosenRenderContext>(&context);
    if (!renderContext) {
        LOGE("render context is null");
        return nullptr;
    }
    auto canvas = renderContext->GetCanvas();
    if (!canvas) {
        return nullptr;
    }
    return canvas;
}

} // namespace OHOS::Ace
