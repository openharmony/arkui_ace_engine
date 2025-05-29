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

#include "core/components_ng/pattern/scroll_bar/scroll_bar_paint_method.h"
#include "core/components_ng/pattern/scroll_bar/scroll_bar_paint_property.h"

namespace OHOS::Ace::NG {

void ScrollBarPaintMethod::UpdateOverlayModifier(PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(paintWrapper);
    auto scrollBarOverlayModifier = scrollBarOverlayModifier_.Upgrade();
    CHECK_NULL_VOID(scrollBarOverlayModifier);
    auto scrollBar = scrollBar_.Upgrade();
    CHECK_NULL_VOID(scrollBar);
    auto paintProperty = DynamicCast<ScrollBarPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(paintProperty);
    auto barColor = paintProperty->GetBarColor();

    if (scrollBar->GetPositionModeUpdate()) {
        scrollBarOverlayModifier->SetPositionMode(scrollBar->GetPositionMode());
    }

    OffsetF fgOffset(scrollBar->GetActiveRect().Left(), scrollBar->GetActiveRect().Top());
    if (!hasChild_) {
        scrollBarOverlayModifier->StartBarAnimation(scrollBar->GetHoverAnimationType(),
            scrollBar->GetOpacityAnimationType(), scrollBar->GetNeedAdaptAnimation(), scrollBar->GetActiveRect());
    } else {
        auto activeRect = scrollBar->GetActiveRect();
        auto offset = activeRect.GetOffset();
        scrollBarOverlayModifier->StartBarAnimation(scrollBar->GetHoverAnimationType(),
            scrollBar->GetOpacityAnimationType(), scrollBar->GetNeedAdaptAnimation(),
            Rect(offset.GetX(), offset.GetY(), 0.0, 0.0));
    }
    scrollBar->SetHoverAnimationType(HoverAnimationType::NONE);
    scrollBarOverlayModifier->SetBarColor(barColor);
    scrollBar->SetOpacityAnimationType(OpacityAnimationType::NONE);
}
} // namespace OHOS::Ace::NG
