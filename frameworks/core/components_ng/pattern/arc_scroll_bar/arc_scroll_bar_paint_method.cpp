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

#include "core/components_ng/pattern/arc_scroll_bar/arc_scroll_bar_paint_method.h"
#include "core/components_ng/pattern/arc_scroll/inner/arc_scroll_bar.h"
#include "core/components_ng/pattern/arc_scroll/inner/arc_scroll_bar_overlay_modifier.h"

namespace OHOS::Ace::NG {

void ArcScrollBarPaintMethod::UpdateOverlayModifier(PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(paintWrapper);
    auto scrollBarOverlayModifier = GetScrollBarOverlayModifier();
    CHECK_NULL_VOID(scrollBarOverlayModifier);
    auto scrollBar = GetScrollBar();
    CHECK_NULL_VOID(scrollBar);
    if (scrollBar->GetPositionModeUpdate()) {
        scrollBarOverlayModifier->SetPositionMode(scrollBar->GetPositionMode());
    }
    auto arcScrollBarOverlayModifier = AceType::DynamicCast<ArcScrollBarOverlayModifier>(scrollBarOverlayModifier);
    CHECK_NULL_VOID(arcScrollBarOverlayModifier);
    auto arcScrollBar = AceType::DynamicCast<ArcScrollBar>(scrollBar);
    CHECK_NULL_VOID(arcScrollBar);
    arcScrollBarOverlayModifier->SetBackgroundBarColor(arcScrollBar->GetArcBackgroundColor());
    arcScrollBarOverlayModifier->StartArcBarAnimation(arcScrollBar->GetHoverAnimationType(),
        arcScrollBar->GetOpacityAnimationType(), arcScrollBar->GetNeedAdaptAnimation(),
        arcScrollBar->GetArcActiveRect(), arcScrollBar->GetArcBarRect());

    scrollBar->SetHoverAnimationType(HoverAnimationType::NONE);
    scrollBarOverlayModifier->SetBarColor(scrollBar->GetArcForegroundColor());
    scrollBar->SetOpacityAnimationType(OpacityAnimationType::NONE);
}
} // namespace OHOS::Ace::NG
