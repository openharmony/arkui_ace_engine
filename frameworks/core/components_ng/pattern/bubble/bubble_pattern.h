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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUBBLE_BUBBLE_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUBBLE_BUBBLE_PATTERN_H

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/referenced.h"
#include "core/components_ng/pattern/bubble//bubble_event_hub.h"
#include "core/components_ng/pattern/bubble/bubble_layout_algorithm.h"
#include "core/components_ng/pattern/bubble/bubble_layout_property.h"
#include "core/components_ng/pattern/bubble/bubble_paint_method.h"
#include "core/components_ng/pattern/bubble/bubble_render_property.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {
class BubblePattern : public Pattern {
    DECLARE_ACE_TYPE(BubblePattern, Pattern);

public:
    BubblePattern() = default;
    explicit BubblePattern(int32_t id, const std::string& tag) : targetNodeId_(id), targetTag_(tag) {}
    ~BubblePattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        auto bubbleMethod = AceType::MakeRefPtr<BubblePaintMethod>();
        bubbleMethod->SetArrowPosition(arrowPosition_);
        bubbleMethod->SetChildOffset(childOffset_);
        bubbleMethod->SetChildSize(childSize_);
        bubbleMethod->SetShowTopArrow(showTopArrow_);
        bubbleMethod->SetShowBottomArrow(showBottomArrow_);
        bubbleMethod->SetShowCustomArrow(showCustomArrow_);
        return bubbleMethod;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        auto bubbleProp = AceType::MakeRefPtr<BubbleLayoutProperty>();
        bubbleProp->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
        return bubbleProp;
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<BubbleLayoutAlgorithm>(targetNodeId_, targetTag_);
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<BubbleRenderProperty>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<BubbleEventHub>();
    }

private:
    void OnModifyDone() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout) override;

    void InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandleTouchEvent(const TouchEventInfo& info);
    void HandleTouchDown(const Offset& clickPosition);
    void PopBubble();

    int32_t targetNodeId_ = -1;
    std::string targetTag_;

    RefPtr<TouchEventImpl> touchEvent_;

    OffsetF childOffset_;
    OffsetF arrowPosition_;
    SizeF childSize_;
    RectF touchRegion_;

    // Is there has enough space for showing arrow.
    bool showTopArrow_ = true;
    bool showBottomArrow_ = true;
    bool showCustomArrow_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(BubblePattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUBBLE_BUBBLE_PATTERN_H