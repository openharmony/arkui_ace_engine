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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_INDICATOR_SWIPER_INDICATOR_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_INDICATOR_SWIPER_INDICATOR_PATTERN_H

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/swiper_indicator/swiper_indicator_layout_algorithm.h"
#include "core/components_ng/pattern/swiper_indicator/swiper_indicator_layout_property.h"
#include "core/components_ng/pattern/swiper_indicator/swiper_indicator_paint_method.h"

namespace OHOS::Ace::NG {

class SwiperIndicatorPattern : public Pattern {
    DECLARE_ACE_TYPE(SwiperIndicatorPattern, Pattern);

public:
    SwiperIndicatorPattern() = default;
    ~SwiperIndicatorPattern() override = default;

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<SwiperIndicatorLayoutProperty>();
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<SwiperIndicatorPaintProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<SwiperIndicatorLayoutAlgorithm>();
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        if (GetPaintMethod()) {
            return GetPaintMethod();
        }
        auto swiperIndicatorPaintMethod =
            MakeRefPtr<SwiperIndicatorPaintMethod>(currentOffset_, axis_, currentIndex_, itemCount_, showIndicator_);
        SetPaintMethod(swiperIndicatorPaintMethod);
        return swiperIndicatorPaintMethod;
    }

    void SetPaintMethod(const RefPtr<SwiperIndicatorPaintMethod>& paintMethod)
    {
        swiperIndicatorPaintMethod_ = paintMethod;
    }

    RefPtr<SwiperIndicatorPaintMethod> GetPaintMethod() const
    {
        return swiperIndicatorPaintMethod_;
    }

    RefPtr<FrameNode> GetSwiperNode() const
    {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, nullptr);
        auto stackNode = host->GetParent();
        CHECK_NULL_RETURN(stackNode, nullptr);
        auto swiperNode = stackNode->GetChildren().front();
        CHECK_NULL_RETURN(swiperNode, nullptr);
        return DynamicCast<FrameNode>(swiperNode);
    }

    void SetCurrentIndex(int32_t currentIndex)
    {
        currentIndex_ = currentIndex;
    }

    int32_t GetCurrentIndex() const
    {
        return currentIndex_;
    }

    void SetItemCount(int32_t itemCount)
    {
        itemCount_ = itemCount;
    }

    int32_t GetItemCount() const
    {
        return itemCount_;
    }

private:
    void OnModifyDone() override;
    void OnAttachToFrameNode() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void SetIndicatorSize();

    RefPtr<SwiperIndicatorPaintMethod> swiperIndicatorPaintMethod_;
    float currentOffset_ = 0.0f;
    int32_t currentIndex_ = 0;
    int32_t itemCount_ = 0;
    bool showIndicator_ = true;
    Axis axis_ = Axis::HORIZONTAL;

    ACE_DISALLOW_COPY_AND_MOVE(SwiperIndicatorPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_INDICATOR_SWIPER_INDICATOR_PATTERN_H
