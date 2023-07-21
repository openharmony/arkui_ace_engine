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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_PAINT_METHOD_H

#include "core/components_ng/pattern/list/list_content_modifier.h"
#include "core/components_ng/pattern/scroll/inner/scroll_bar.h"
#include "core/components_ng/pattern/scroll/scroll_edge_effect.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/components_v2/list/list_properties.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ListPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(ListPaintMethod, NodePaintMethod)
public:
    ListPaintMethod(
        const V2::ItemDivider& divider, bool vertical, int32_t lanes, float space)
        : divider_(divider), vertical_(vertical), lanes_(lanes), space_(space)
    {}
    ~ListPaintMethod() override = default;

    CanvasDrawFunction GetForegroundDrawFunction(PaintWrapper* paintWrapper) override;

    RefPtr<Modifier> GetContentModifier(PaintWrapper* paintWrapper) override
    {
        return listContentModifier_;
    }

    void UpdateContentModifier(PaintWrapper* paintWrapper) override;

    void PaintScrollBar(RSCanvas& canvas);
    void PaintEdgeEffect(PaintWrapper* paintWrapper, RSCanvas& canvas);

    void SetScrollBar(WeakPtr<ScrollBar>&& scrollBar)
    {
        scrollBar_ = scrollBar;
    }

    void SetEdgeEffect(WeakPtr<ScrollEdgeEffect>&& edgeEffect)
    {
        edgeEffect_ = edgeEffect;
    }

    void SetTotalItemCount(int32_t totalItemCount)
    {
        totalItemCount_ = totalItemCount;
    }

    void SetContentModifier(const RefPtr<ListContentModifier>& modify)
    {
        listContentModifier_ = modify;
    }

    void SetLaneGutter(float laneGutter)
    {
        laneGutter_ = laneGutter;
    }

    float GetLaneGutter()
    {
        return laneGutter_;
    }

private:
    V2::ItemDivider divider_;
    bool vertical_ = false;
    int32_t lanes_ = 1;
    int32_t totalItemCount_;
    float space_;
    float laneGutter_ = 0.0f;
    RefPtr<ListContentModifier> listContentModifier_;

    WeakPtr<ScrollBar> scrollBar_;
    WeakPtr<ScrollEdgeEffect> edgeEffect_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_PAINT_METHOD_H