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
        if (search) {
            search->PaintSearch(canvas, paintWrapper);
        }
    };
    return paintFunc;
}

void SearchPaintMethod::PaintSearch(RSCanvas& canvas, PaintWrapper* paintWrapper) const
{
    if (!searchButton_.empty()) {
        constexpr Dimension ICON_HEIGHT = 16.0_vp;
        constexpr double SEARCH_DIVIDER_WIDTH = 1.0;
        constexpr double DIVIDER_SPACE = 7.0;
        const Color SEARCH_DIVIDER_COLOR = Color(0x33000000);

        auto searchSize = paintWrapper->GetGeometryNode()->GetFrameSize();
        // Paint divider.
        double dividerVerticalOffset = (searchSize.Height() - ICON_HEIGHT.ConvertToPx()) / 2.0;
        double dividerHorizontalOffset = searchSize.Width() - buttonSize_.Width() - DIVIDER_SPACE;
        OffsetF dividerOffset = OffsetF(dividerHorizontalOffset, dividerVerticalOffset);
        float originX = dividerOffset.GetX();
        float originY = dividerOffset.GetY();
        RSRect rect(originX, originY, originX + SEARCH_DIVIDER_WIDTH, originY + ICON_HEIGHT.ConvertToPx());
        canvas.Save();
        RSPen pen;
        pen.SetColor(ToRSColor(SEARCH_DIVIDER_COLOR));
        canvas.AttachPen(pen);
        canvas.DrawRect(rect);
        canvas.Restore();
    }
}

} // namespace OHOS::Ace::NG