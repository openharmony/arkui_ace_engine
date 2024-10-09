/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_PAINT_METHOD_H

#include "core/components_ng/pattern/scroll/inner/scroll_bar.h"
#include "core/components_ng/pattern/scroll/scroll_edge_effect.h"
#include "core/components_ng/pattern/scrollable/scrollable_paint_method.h"
#include "core/components_ng/pattern/waterflow/water_flow_content_modifier.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT WaterFlowPaintMethod : public ScrollablePaintMethod {
    DECLARE_ACE_TYPE(WaterFlowPaintMethod, ScrollablePaintMethod)
public:
    WaterFlowPaintMethod() = default;
    WaterFlowPaintMethod(bool vertical, bool isReverse, bool isVerticalReverse)
        : ScrollablePaintMethod(vertical, isReverse, isVerticalReverse)
    {}
    ~WaterFlowPaintMethod() override = default;

    CanvasDrawFunction GetForegroundDrawFunction(PaintWrapper* paintWrapper) override;

    RefPtr<Modifier> GetContentModifier(PaintWrapper* paintWrapper) override
    {
        return contentModifier_;
    }

    void UpdateContentModifier(PaintWrapper* paintWrapper) override;

    void PaintEdgeEffect(PaintWrapper* paintWrapper, RSCanvas& canvas);

    void SetScrollBar(WeakPtr<ScrollBar>&& scrollBar)
    {
        scrollBar_ = scrollBar;
    }

    void SetEdgeEffect(WeakPtr<ScrollEdgeEffect>&& edgeEffect)
    {
        edgeEffect_ = edgeEffect;
    }

    void SetContentModifier(const RefPtr<WaterFlowContentModifier>& modify)
    {
        contentModifier_ = modify;
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
    ContentClipMode GetDefaultContentClip() const override
    {
        return ContentClipMode::CONTENT_ONLY;
    }

    RefPtr<WaterFlowContentModifier> contentModifier_;
    WeakPtr<ScrollBar> scrollBar_;
    WeakPtr<ScrollEdgeEffect> edgeEffect_;
    WeakPtr<ScrollBarOverlayModifier> scrollBarOverlayModifier_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_PAINT_METHOD_H