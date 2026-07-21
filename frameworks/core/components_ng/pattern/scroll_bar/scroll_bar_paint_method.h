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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLL_BAR_SCROLL_BAR_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLL_BAR_SCROLL_BAR_PAINT_METHOD_H

#include "core/components_ng/pattern/scroll/inner/scroll_bar.h"
#include "core/components_ng/render/node_paint_method.h"

namespace OHOS::Ace::NG {

class ScrollBarPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(ScrollBarPaintMethod, NodePaintMethod);

public:
    explicit ScrollBarPaintMethod(bool hasChild) : hasChild_(hasChild) {};
    ~ScrollBarPaintMethod() override = default;

    void SetScrollBar(WeakPtr<ScrollBar>&& scrollBar)
    {
        scrollBar_ = scrollBar;
    }

    RefPtr<ScrollBar> GetScrollBar()
    {
        return scrollBar_.Upgrade();
    }

    RefPtr<ScrollBarOverlayModifier> GetScrollBarOverlayModifier()
    {
        return scrollBarOverlayModifier_.Upgrade();
    }

    void SetScrollBarOverlayModifier(WeakPtr<ScrollBarOverlayModifier>&& scrollBarOverlayModifier)
    {
        scrollBarOverlayModifier_ = scrollBarOverlayModifier;
    }

    RefPtr<Modifier> GetOverlayModifier(PaintWrapper* paintWrapper) override
    {
        return scrollBarOverlayModifier_.Upgrade();
    }

    void UpdateOverlayModifier(PaintWrapper* paintWrapper) override;

private:
    bool hasChild_ = false;
    WeakPtr<ScrollBar> scrollBar_;
    WeakPtr<ScrollBarOverlayModifier> scrollBarOverlayModifier_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLL_BAR_SCROLL_BAR_PAINT_METHOD_H
