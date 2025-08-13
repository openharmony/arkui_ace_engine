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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_PAINT_METHOD_H

#include "core/components_ng/pattern/grid/grid_content_modifier.h"
#include "core/components_ng/pattern/scroll/inner/scroll_bar.h"
#include "core/components_ng/pattern/scroll/scroll_edge_effect.h"
#include "core/components_ng/pattern/scrollable/scrollable_paint_method.h"
#include "core/components_ng/pattern/scrollable/scrollable_paint_property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT GridPaintMethod : public ScrollablePaintMethod {
    DECLARE_ACE_TYPE(GridPaintMethod, ScrollablePaintMethod);
public:
    explicit GridPaintMethod(const RefPtr<ScrollBar>& scrollBar) : scrollBar_(scrollBar) {}
    explicit GridPaintMethod(bool vertical, bool isReverse, const RefPtr<ScrollBar>& scrollBar)
        : ScrollablePaintMethod(vertical, isReverse), scrollBar_(scrollBar)
    {}

    ~GridPaintMethod() override = default;

    CanvasDrawFunction GetForegroundDrawFunction(PaintWrapper* paintWrapper) override;
    void PaintEdgeEffect(PaintWrapper* paintWrapper, RSCanvas& canvas);
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
        return scrollBarOverlayModifier_.Upgrade();
    }

    void UpdateOverlayModifier(PaintWrapper* paintWrapper) override;

    RefPtr<Modifier> GetContentModifier(PaintWrapper* paintWrapper) override
    {
        return gridContentModifier_;
    }

    void UpdateContentModifier(PaintWrapper* paintWrapper) override;

    void SetContentModifier(const RefPtr<GridContentModifier>& modify)
    {
        gridContentModifier_ = modify;
    }

private:
    RefPtr<GridContentModifier> gridContentModifier_;
    WeakPtr<ScrollBar> scrollBar_;
    WeakPtr<ScrollEdgeEffect> edgeEffect_;
    WeakPtr<ScrollBarOverlayModifier> scrollBarOverlayModifier_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_PAINT_METHOD_H
