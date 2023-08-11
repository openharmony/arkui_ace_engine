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
#include "core/components/search/search_theme.h"
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
        CHECK_NULL_VOID_NOLOG(search);
        search->PaintSearch(canvas, paintWrapper);
    };
    return paintFunc;
}

void SearchPaintMethod::PaintSearch(RSCanvas& canvas, PaintWrapper* paintWrapper) const
{
    if (isSearchButtonEnabled_) {
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto searchTheme = pipeline->GetTheme<SearchTheme>();
        CHECK_NULL_VOID(searchTheme);
        auto iconHeight = searchTheme->GetIconHeight();
        auto dividerSpace = searchTheme->GetDividerSideSpace().ConvertToPx();
        auto searchSpace = searchTheme->GetSearchButtonSpace().ConvertToPx();
        auto searchDividerWidth = searchTheme->GetSearchDividerWidth().ConvertToPx();
        auto searchDividerColor = searchTheme->GetSearchDividerColor();
        auto searchSize = paintWrapper->GetGeometryNode()->GetFrameSize();
        float rightOffset = 0.0f;
        if (paintWrapper->GetGeometryNode()->GetPadding()) {
            rightOffset = paintWrapper->GetGeometryNode()->GetPadding()->right.value_or(0.0f);
        }
        // Paint divider.
        double dividerVerticalOffset = (searchSize.Height() - iconHeight.ConvertToPx()) / 2.0;
        double dividerHorizontalOffset = searchSize.Width() - buttonSize_.Width() - dividerSpace -
                                         searchSpace - searchDividerWidth / 2 - rightOffset;
        dividerHorizontalOffset = std::max(dividerHorizontalOffset, 0.0);
        OffsetF dividerOffset = OffsetF(dividerHorizontalOffset, dividerVerticalOffset);
        float originX = dividerOffset.GetX();
        float originY = dividerOffset.GetY();
        RSRect rect(originX, originY, originX + searchDividerWidth, originY + iconHeight.ConvertToPx());
        canvas.Save();
        RSPen pen;
        pen.SetWidth(searchDividerWidth);
        pen.SetColor(ToRSColor(searchDividerColor));
        canvas.AttachPen(pen);
        canvas.DrawRect(rect);
        canvas.Restore();
    }
}

} // namespace OHOS::Ace::NG