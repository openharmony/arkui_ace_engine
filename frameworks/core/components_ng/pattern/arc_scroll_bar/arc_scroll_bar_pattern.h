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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ARC_SCROLL_BAR_ARC_SCROLL_BAR_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ARC_SCROLL_BAR_ARC_SCROLL_BAR_PATTERN_H

#include "core/components_ng/pattern/arc_scroll/inner/arc_scroll_bar.h"
#include "core/components_ng/pattern/arc_scroll/inner/arc_scroll_bar_overlay_modifier.h"
#include "core/components_ng/pattern/arc_scroll_bar/arc_scroll_bar_layout_algorithm.h"
#include "core/components_ng/pattern/arc_scroll_bar/arc_scroll_bar_paint_method.h"
#include "core/components_ng/pattern/scroll_bar/scroll_bar_pattern.h"

namespace OHOS::Ace::NG {

class ArcScrollBarPattern : public ScrollBarPattern {
    DECLARE_ACE_TYPE(ArcScrollBarPattern, ScrollBarPattern);

public:
    ArcScrollBarPattern() = default;
    ~ArcScrollBarPattern() override = default;

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        auto layoutAlgorithm = MakeRefPtr<ArcScrollBarLayoutAlgorithm>();
        return layoutAlgorithm;
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        auto paint = MakeRefPtr<ArcScrollBarPaintMethod>();
        paint->SetScrollBar(GetScrollBar());
        auto scrollBarOverlayModifier = GetScrollBarOverlayModifier();
        auto scrollBar = GetScrollBar();
        if (scrollBar && scrollBar->NeedPaint() && !scrollBarOverlayModifier) {
            scrollBarOverlayModifier = AceType::MakeRefPtr<ArcScrollBarOverlayModifier>();
            auto arcScrollBar = AceType::DynamicCast<ArcScrollBar>(scrollBar);
            auto arcScrollBarOverlayModifier =
                AceType::DynamicCast<ArcScrollBarOverlayModifier>(scrollBarOverlayModifier);
            if (arcScrollBar && arcScrollBarOverlayModifier) {
                arcScrollBarOverlayModifier->SetPositionMode(arcScrollBar->GetPositionMode());
                arcScrollBarOverlayModifier->SetArcRect(arcScrollBar->GetArcActiveRect());
                arcScrollBarOverlayModifier->SetBackgroundArcRect(arcScrollBar->GetArcBarRect());
            }
            SetScrollBarOverlayModifier(scrollBarOverlayModifier);
        }
        paint->SetScrollBarOverlayModifier(scrollBarOverlayModifier);
        return paint;
    }

    bool UseInnerScrollBar() const override
    {
        return true;
    }

    RefPtr<ScrollBar> CreateScrollBar() const override
    {
        return AceType::MakeRefPtr<ArcScrollBar>();
    }

    void SetBarCollectClickAndLongPressTargetCallback() override {}

private:
    void OnModifyDone() override;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ARC_SCROLL_BAR_ARC_SCROLL_BAR_PATTERN_H
