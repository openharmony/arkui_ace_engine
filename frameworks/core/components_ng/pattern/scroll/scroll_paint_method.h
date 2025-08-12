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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLL_SCROLL_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLL_SCROLL_PAINT_METHOD_H

#include "core/components_ng/pattern/scroll/inner/scroll_bar.h"
#include "core/components_ng/pattern/scroll/inner/scroll_bar_2d.h"
#include "core/components_ng/pattern/scroll/inner/scroll_bar_2d_painter.h"
#include "core/components_ng/pattern/scroll/scroll_content_modifier.h"
#include "core/components_ng/pattern/scroll/scroll_edge_effect.h"
#include "core/components_ng/pattern/scrollable/scrollable_paint_method.h"

namespace OHOS::Ace::NG {

class ScrollPaintMethod : public ScrollablePaintMethod {
    DECLARE_ACE_TYPE(ScrollPaintMethod, ScrollablePaintMethod);

public:
    ScrollPaintMethod() = default;
    ScrollPaintMethod(bool vertical, bool isReverse) : ScrollablePaintMethod(vertical, isReverse) {}
    ~ScrollPaintMethod() override = default;

    CanvasDrawFunction GetForegroundDrawFunction(PaintWrapper* paintWrapper) override;

    void SetScrollBar(WeakPtr<ScrollBar>&& scrollBar)
    {
        scrollBar_ = scrollBar;
    }

    RefPtr<ScrollBar> GetScrollBar()
    {
        return scrollBar_.Upgrade();
    }

    void SetEdgeEffect(WeakPtr<ScrollEdgeEffect>&& edgeEffect)
    {
        edgeEffect_ = edgeEffect;
    }

    void SetScrollBarOverlayModifier(WeakPtr<ScrollBarOverlayModifier>&& scrollBarOverlayModifier)
    {
        scrollBarOverlayModifier_ = scrollBarOverlayModifier;
    }

    RefPtr<Modifier> GetOverlayModifier(PaintWrapper* paintWrapper) override
    {
        if (auto scrollBar2d = scrollBar2d_.Upgrade()) {
            return scrollBar2d->GetPainter();
        }
        return scrollBarOverlayModifier_.Upgrade();
    }

    void UpdateOverlayModifier(PaintWrapper* paintWrapper) override;

    RefPtr<Modifier> GetContentModifier(PaintWrapper* paintWrapper) override
    {
        return scrollContentModifier_;
    }

    void UpdateContentModifier(PaintWrapper* paintWrapper) override;

    void SetContentModifier(const RefPtr<ScrollContentModifier>& modify)
    {
        scrollContentModifier_ = modify;
    }

private:
    RefPtr<ScrollContentModifier> scrollContentModifier_;
    void PaintScrollEffect(RSCanvas& canvas, PaintWrapper* paintWrapper) const;

    WeakPtr<ScrollBar> scrollBar_;
    WeakPtr<ScrollEdgeEffect> edgeEffect_;
    WeakPtr<ScrollBarOverlayModifier> scrollBarOverlayModifier_;

    /* ============================= Free Scroll Enhancements ============================= */
public:
    void Set2DPainter(const WeakPtr<ScrollBar2D>& scrollBar)
    {
        scrollBar2d_ = scrollBar;
    }

private:
    void UpdateOverlayModifier2d(PaintWrapper* paintWrapper);

    WeakPtr<ScrollBar2D> scrollBar2d_;
    /* ============================================================================== */
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLL_SCROLL_PAINT_METHOD_H
