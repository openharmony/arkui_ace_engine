/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/search/search_paint_method.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/point_t.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/color.h"
#include "core/components/theme/theme_manager.h"
#include "core/components_ng/pattern/search/search_pattern.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

CanvasDrawFunction SearchPaintMethod::GetContentDrawFunction(PaintWrapper* paintWrapper)
{
    auto paintFunc = [weak = WeakClaim(this), paintWrapper](RSCanvas& canvas) {
        auto search = weak.Upgrade();
        CHECK_NULL_VOID(search);
        search->PaintSearch(canvas, paintWrapper);
    };
    return paintFunc;
}

void SearchPaintMethod::PaintSearch(RSCanvas& canvas, PaintWrapper* paintWrapper) const
{
    if (!isSearchButtonEnabled_) {
        return;
    }

    auto renderContext = paintWrapper->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto host = renderContext->GetHost();
    CHECK_NULL_VOID(renderContext);
    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto isRTL = layoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto searchTheme = pipeline->GetTheme<SearchTheme>();
    CHECK_NULL_VOID(searchTheme);

    // GetThemeAttributes logic inlined here
    auto [iconHeight, dividerSpace, searchSpace, searchDividerWidth, searchDividerColor] =
        GetThemeAttributes(searchTheme);
    auto searchSize = paintWrapper->GetGeometryNode()->GetFrameSize();
    auto [rightOffset, leftOffset, topPadding, bottomPadding] = GetPaddingOffsets(paintWrapper);

    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        rightOffset = 0.0f;
    }
    DividerOffsetsParams params = { isRTL, searchSize, iconHeight, dividerSpace, searchSpace, searchDividerWidth,
                                    rightOffset, leftOffset, topPadding, bottomPadding };

    // CalculateDividerOffsets logic inlined here
    auto [dividerHorizontalOffset, dividerVerticalOffset, dividerHeight] = CalculateDividerOffsets(params);

    // DrawDivider logic inlined here
    RSRect rect(dividerHorizontalOffset, dividerVerticalOffset, dividerHorizontalOffset + searchDividerWidth,
        dividerVerticalOffset + dividerHeight);
    canvas.Save();
    RSPen pen;
    pen.SetWidth(searchDividerWidth);
    pen.SetColor(ToRSColor(searchDividerColor));
    canvas.AttachPen(pen);
    canvas.DrawRect(rect);
    canvas.DetachPen();
    canvas.Restore();
}

std::tuple<OHOS::Ace::Dimension, double, double, double, OHOS::Ace::Color> SearchPaintMethod::GetThemeAttributes(
    const RefPtr<OHOS::Ace::SearchTheme>& searchTheme) const
{
    OHOS::Ace::Dimension iconHeight = searchTheme->GetIconHeight();
    auto dividerSpace = searchTheme->GetDividerSideSpace().ConvertToPx();
    auto searchSpace = searchTheme->GetSearchButtonSpace().ConvertToPx();
    auto searchDividerWidth = searchTheme->GetSearchDividerWidth().ConvertToPx();
    OHOS::Ace::Color searchDividerColor = searchTheme->GetSearchDividerColor();
    return { iconHeight, dividerSpace, searchSpace, searchDividerWidth, searchDividerColor };
}

std::tuple<float, float, float, float> SearchPaintMethod::GetPaddingOffsets(PaintWrapper* paintWrapper) const
{
    auto rightOffset = 0.0f;
    auto leftOffset = 0.0f;
    auto topPadding = 0.0f;
    auto bottomPadding = 0.0f;
    const auto &padding = paintWrapper->GetGeometryNode()->GetPadding();
    if (padding) {
        rightOffset = padding->right.value_or(0.0f);
        topPadding = padding->top.value_or(0.0f);
        bottomPadding = padding->bottom.value_or(0.0f);
        leftOffset = padding->left.value_or(0.0f);
    }
    return { rightOffset, leftOffset, topPadding, bottomPadding };
}

std::tuple<float, float, float> SearchPaintMethod::CalculateDividerOffsets(const DividerOffsetsParams& params) const
{
    auto dividerVerticalOffset = (params.searchSize.Height() - params.iconHeight.ConvertToPx()) / 2.0f;
    auto dividerHorizontalOffset = 0.0f;
    if (params.isRTL) {
        dividerHorizontalOffset = params.leftOffset + buttonSize_.Width() + params.dividerSpace + params.searchSpace +
            params.searchDividerWidth / 2.0f;
    } else {
        dividerHorizontalOffset = params.searchSize.Width() - buttonSize_.Width() - params.dividerSpace -
            params.searchSpace - params.searchDividerWidth / 2.0f - params.rightOffset;
    }
    dividerHorizontalOffset = std::max(dividerHorizontalOffset, 0.0f);
    auto dividerHeight = std::min(params.searchSize.Height() - params.topPadding - params.bottomPadding,
        static_cast<float>(params.iconHeight.ConvertToPx()));
    dividerVerticalOffset = params.topPadding;
    if (NearEqual(params.iconHeight.ConvertToPx(), dividerHeight)) {
        auto dividerInterval = (params.searchSize.Height() - params.iconHeight.ConvertToPx()) / 2.0f;
        if (params.topPadding <= dividerInterval && params.bottomPadding <= dividerInterval) {
            dividerVerticalOffset = dividerInterval;
        } else if (params.topPadding <= dividerInterval && params.bottomPadding > dividerInterval) {
            dividerVerticalOffset = params.searchSize.Height() - (params.bottomPadding + dividerHeight);
        }
    }
    return { dividerHorizontalOffset, dividerVerticalOffset, dividerHeight };
}
} // namespace OHOS::Ace::NG
